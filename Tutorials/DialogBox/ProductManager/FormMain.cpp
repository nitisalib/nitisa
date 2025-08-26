// Include header file with platform window management class
#include "Platform/Core/Window.h"

// Include header file with platform OpenGL renderer
#include "Platform/Core/Renderer.h"

// Include header file with the form declaration
#include "FormMain.h"

// Include file with product form declaration
#include "FormProduct.h"

// Include file with confirmation form declaration
#include "FormConfirm.h"

// Include header file with confirmation dialog box declaration as we are going to use its methods
#include "DialogBoxConfirm.h"

namespace nitisa
{
	namespace app
	{
		// Global variable for the form instance
		CFormMain *FormMain{ nullptr };

		// In listener's constructor we just store pointer to a form
		CFormMain::CDialogBoxListener::CDialogBoxListener(CFormMain *form) :
			m_pForm{ form }
		{

		}

		// This method of the listener is called when dialog box is closed
		void CFormMain::CDialogBoxListener::OnClose(IDialogBox *sender)
		{
			CDialogBoxProduct *dlg;
			// Check with what result dialog box was closed
			switch (sender->getModalResult())
			{
			case ModalResult::Yes: // We close with this result when user clicks on "Yes" button in the confirmation dialog box
				// Identify what action should be performed by "Tag" property value
				if ((int)sender->Tag == m_pForm->ACTION_DELETE) // We have to delete selected products
				{
					// Run through all products and delete them both from m_aProducts storage and widget
					for (int i = m_pForm->m_pCheckListBoxProducts->getItemCount() - 1; i >= 0; i--)
						if (m_pForm->m_pCheckListBoxProducts->isChecked(i))
						{
							m_pForm->m_aProducts.erase(m_pForm->m_aProducts.begin() + i);
							m_pForm->m_pCheckListBoxProducts->Delete(i);
						}
				}
				else if ((int)sender->Tag == m_pForm->ACTION_CLEAR) // We have to delete all products
				{
					m_pForm->m_aProducts.clear();
					m_pForm->m_pCheckListBoxProducts->Clear();
				}
				break;
			case ModalResult::Ok: // We close with this result when user clicks on "OK" button in the product dialog box
				if ((dlg = cast<CDialogBoxProduct*>(sender))) // Convert "sender" to product dialog box
				{
					// Compose caption displayed in the widget for the product
					String caption{ dlg->getProduct().Name + L" [" + ToString(dlg->getProduct().Quantity) + L" for $" + ToFixed(dlg->getProduct().Price, 2) + L" each]" };
					if (dlg->isNew()) // If it was adding a product, add it
					{
						m_pForm->m_aProducts.push_back(dlg->getProduct());
						m_pForm->m_pCheckListBoxProducts->Add(caption);
					}
					else // Otherwise it was modification of the product
					{
						m_pForm->m_aProducts[(int)dlg->Tag] = dlg->getProduct();
						m_pForm->m_pCheckListBoxProducts->getItem((int)dlg->Tag)->setCaption(caption);
					}
				}
				break;
			}
		}

		void CFormMain::CDialogBoxListener::OnRestore(IDialogBox *sender)
		{
			// We are not interesting in this notification
		}

		void CFormMain::CDialogBoxListener::OnMinimize(IDialogBox *sender)
		{
			// We are not interesting in this notification
		}

		void CFormMain::CDialogBoxListener::OnMaximize(IDialogBox *sender)
		{
			// We are not interesting in this notification
		}

		CFormMain::CFormMain():
			// Call parent constructor with platform window and renderer objects as usual
			IFormMain(CWindow::Create(), CRenderer::Create()),
			// Product dialog box is not created yet, so its pointer is empty
			m_pDialogBoxProduct{ nullptr },
			// Confirmation dialog box is not created yet, so its pointer is empty
			m_pDialogBoxConfirm{ nullptr },
			// Product dialog box was not resized yet
			m_bDialogBoxProductResized{ false },
			// Confirmation dialog box was not resized yet
			m_bDialogBoxConfirmResized{ false },
			// Listener's constructor requires form
			m_cDialogBoxListener{ this }
		{

		}

		CDialogBoxProduct *CFormMain::getDialogBoxProduct()
		{
			// If product dialog box was not created yet
			if (!m_pDialogBoxProduct)
			{
				// Create it
				m_pDialogBoxProduct = new CDialogBoxProduct(this);
				// Assign listener to it
				m_pDialogBoxProduct->setDialogBoxListener(&m_cDialogBoxListener);
				// Set its background color equals to the background color of the main form
				m_pDialogBoxProduct->setBackgroundColor(getBackgroundColor());
			}
			return m_pDialogBoxProduct;
		}

		CDialogBoxConfirm *CFormMain::getDialogBoxConfirm()
		{
			// If confirmation dialog box was not created yet
			if (!m_pDialogBoxConfirm)
			{
				// Create it
				m_pDialogBoxConfirm = new CDialogBoxConfirm(this);
				// Assign listener to it
				m_pDialogBoxConfirm->setDialogBoxListener(&m_cDialogBoxListener);
				// Set its background color equals to the background color of the main form
				m_pDialogBoxConfirm->setBackgroundColor(getBackgroundColor());
			}
			return m_pDialogBoxConfirm;
		}

		void CFormMain::ExecuteDialogBoxProduct(const PRODUCT &product, const bool is_new, const int tag)
		{
			// Assign "tag" to "Tag" property of the dialog box
			getDialogBoxProduct()->Tag = tag;
			// Set dialog box caption depending whether we add or modify a product
			getDialogBoxProduct()->setCaption(is_new ? L"Add product" : L"Edit product");
			// Show dialog box modally
			getDialogBoxProduct()->Execute(product, is_new);
			// If dialog box was not yet resized
			if (!m_bDialogBoxProductResized)
			{
				// Resize it
				getDialogBoxProduct()->AutoResize(true);
				// And set flag indicating it was already resized
				m_bDialogBoxProductResized = true;
			}
		}

		void CFormMain::ExecuteDialogBoxConfirm(const String &message, const int tag)
		{
			// Assign "tag" to "Tag" property of the dialog box
			getDialogBoxConfirm()->Tag = tag;
			// Show dialog box modally
			getDialogBoxConfirm()->Execute(message);
			// If dialog box was not yet resized
			if (!m_bDialogBoxConfirmResized)
			{
				// Resize it
				getDialogBoxConfirm()->AutoResize(true);
				// And set flag indicating it was already resized
				m_bDialogBoxConfirmResized = true;
			}
		}

		void CFormMain::ButtonAdd_OnClick(IControl *sender)
		{
			if (!Application->DialogBoxes) // If regular form mode should be used
			{
				if (FormProduct->Execute(PRODUCT{ L"", 0.0f, 0 }) == ModalResult::Ok) // If user clicked "OK" button on product form
				{
					PRODUCT p{ FormProduct->getProduct() };
					// Add product to storage
					m_aProducts.push_back(p);
					// Add product to widget
					m_pCheckListBoxProducts->Add(p.Name + L" [" + ToString(p.Quantity) + L" for $" + ToFixed(p.Price, 2) + L" each]");
				}
			}
			else // Otherwise use dialog box mode
				// Show product dialog box with empty product, indicating it is new product and any "tag" value as it is not used in adding a product
				ExecuteDialogBoxProduct(PRODUCT{ L"", 0.0f, 0 }, true, 0);
		}

		void CFormMain::ButtonEdit_OnClick(IControl *sender)
		{
			// If there is active row in the widget with products
			if (m_pCheckListBoxProducts->getActiveIndex() >= 0)
			{
				if (!Application->DialogBoxes) // If regular form mode should be used
				{
					if (FormProduct->Execute(m_aProducts[m_pCheckListBoxProducts->getActiveIndex()]) == ModalResult::Ok) // If user clicked "OK" button on product form
					{
						PRODUCT p{ FormProduct->getProduct() };
						// Update product in storage
						m_aProducts[m_pCheckListBoxProducts->getActiveIndex()] = p;
						// Update product in widget
						m_pCheckListBoxProducts->getItem(m_pCheckListBoxProducts->getActiveIndex())->setCaption(p.Name + L" [" + ToString(p.Quantity) + L" for $" + ToFixed(p.Price, 2) + L" each]");
					}
				}
				else // Otherwise use dialog box mode
					// Show product dialog box with product information, indicating it is existing product and "tag" equals to the product index in widget and products storage
					ExecuteDialogBoxProduct(m_aProducts[m_pCheckListBoxProducts->getActiveIndex()], false, m_pCheckListBoxProducts->getActiveIndex());
			}
		}

		void CFormMain::ButtonDelete_OnClick(IControl *sender)
		{
			// Check if at least one product is selected
			bool has_checked{ false };
			for (int i = 0; i < m_pCheckListBoxProducts->getItemCount(); i++)
				if (m_pCheckListBoxProducts->getItem(i)->isChecked())
				{
					has_checked = true;
					break;
				}
			// Only if there is at least one selected product
			if (has_checked)
			{
				if (!Application->DialogBoxes) // If regular form mode should be used
				{
					if (FormConfirm->Execute(L"Are you sure you want to delete selected products?") == ModalResult::Ok) // If user click on "Yes" confirmation button
					{
						// Run through all products and delete them both from m_aProducts storage and widget
						for (int i = m_pCheckListBoxProducts->getItemCount() - 1; i >= 0; i--)
							if (m_pCheckListBoxProducts->isChecked(i))
							{
								m_aProducts.erase(m_aProducts.begin() + i);
								m_pCheckListBoxProducts->Delete(i);
							}
					}
				}
				else // Otherwise use dialog box mode
					// Show delete selected products confirmation dialog box with action indicating deleting selected products
					ExecuteDialogBoxConfirm(L"Are you sure you want to delete selected products?", ACTION_DELETE);
			}
		}

		void CFormMain::ButtonClear_OnClick(IControl *sender)
		{
			// If there are products
			if (m_pCheckListBoxProducts->getItemCount() > 0)
			{
				if (!Application->DialogBoxes) // If regular form mode should be used
				{
					if (FormConfirm->Execute(L"Are you sure you want to delete information about all products?") == ModalResult::Ok) // If user click on "Yes" confirmation button
					{
						m_aProducts.clear();
						m_pCheckListBoxProducts->Clear();
					}
				}
				else // Otherwise use dialog box mode
					// Show delete all products confirmation dialog box with action indicating deleting all products
					ExecuteDialogBoxConfirm(L"Are you sure you want to delete information about all products?", ACTION_CLEAR);
			}
		}
	}
}
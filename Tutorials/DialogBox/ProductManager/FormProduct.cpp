// Include header file with platform window management class
#include "Platform/Core/Window.h"

// Include header file with platform OpenGL renderer
#include "Platform/Core/Renderer.h"

// Include header file with form class declaration
#include "FormProduct.h"

namespace nitisa
{
	namespace app
	{
		// Global varialbe for the form instance
		CFormProduct *FormProduct{ nullptr };

		CFormProduct::CFormProduct() :
			// Call parent constructor with platform window and renderer objects as usual
			IFormProduct(CWindow::Create(), CRenderer::Create())
		{
			
		}

		PRODUCT CFormProduct::getProduct() const
		{
			// Convert input values to PRODUCT structure
			return PRODUCT{ Trim(m_pEditName->getText()), m_pUpDownExPrice->getValue(), m_pUpDownQuantity->getValue() };
		}

		ModalResult CFormProduct::Execute(const PRODUCT &product)
		{
			// Set product information into inputs
			m_pEditName->setText(product.Name);
			m_pUpDownExPrice->setValue(product.Price);
			m_pUpDownQuantity->setValue(product.Quantity);
			// Show dialog box modally
			return ShowModal();
		}

		void CFormProduct::ButtonOk_OnClick(IControl *sender)
		{
			// When user clicks on "OK" button set form showing result to "mrOk"
			// This will close form automatically
			// But before doing so we check whether information in inputs is valid
			if (Validate())
				setModalResult(ModalResult::Ok);
		}

		void CFormProduct::ButtonCancel_OnClick(IControl *sender)
		{
			// When user clicks on "Cancel" button set form showing result to "mrCancel"
			// This will close form automatically
			setModalResult(ModalResult::Cancel);
		}

		bool CFormProduct::Validate()
		{
			// If name of the product is specified as empty string
			if (Trim(m_pEditName->getText()).empty())
			{
				// Select everything in the name input
				m_pEditName->SelectAll();
				// Set name input focused
				m_pEditName->setFocus();
				// Return false as the validation failed
				return false;
			}
			// Validation passed so we return true
			return true;
		}
	}
}
// Include header file with dialog box class declaration
#include "DialogBoxProduct.h"

namespace nitisa
{
	namespace app
	{
		CDialogBoxProduct::CDialogBoxProduct(IForm *parent):
			// In the constructor we should only call parent class constructor. Meaning of its arguments is the same as for the confirmation dialog box
			IDialogBoxProduct(L"DialogBoxProduct", true, false, false, false),
			// Initialize flag to some correct value
			m_bIsNew{ true }
		{
			// Put dialog box onto specified form
			setForm(parent);
		}

		bool CDialogBoxProduct::isNew() const
		{
			// Just return stored value of the flag
			return m_bIsNew;
		}

		PRODUCT CDialogBoxProduct::getProduct() const
		{
			// Convert input values to PRODUCT structure
			return PRODUCT{ Trim(m_pEditName->getText()), m_pUpDownExPrice->getValue(), m_pUpDownQuantity->getValue() };
		}

		void CDialogBoxProduct::Execute(const PRODUCT &product, const bool is_new)
		{
			// Set product information into inputs
			m_pEditName->setText(product.Name);
			m_pUpDownExPrice->setValue(product.Price);
			m_pUpDownQuantity->setValue(product.Quantity);
			// Store specified flag
			m_bIsNew = is_new;
			// Show dialog box modally
			ShowModal();
		}

		void CDialogBoxProduct::ButtonOk_OnClick(IControl *sender)
		{
			// When user clicks on "OK" button set dialog box showing result to "mrOk"
			// This will close dialog box automatically
			// But before doing so we check whether information in inputs is valid
			if (Validate())
				setModalResult(ModalResult::Ok);
		}

		void CDialogBoxProduct::ButtonCancel_OnClick(IControl *sender)
		{
			// When user clicks on "Cancel" button set dialog box showing result to "mrCancel"
			// This will close dialog box automatically
			setModalResult(ModalResult::Cancel);
		}

		bool CDialogBoxProduct::Validate()
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
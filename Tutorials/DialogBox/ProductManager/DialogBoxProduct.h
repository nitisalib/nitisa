#pragma once

// Include header file with form prototype in dialog box mode
#include "IDialogBoxProduct.h"

// Namespace where everything of the Nitisa framework is
namespace nitisa
{
	// Our application namespace. The same namespace where Form Builder put form prototype in
	namespace app
	{
		// Structure containing product information
		struct PRODUCT
		{
			// Product name
			String Name;
			// Product price
			float Price;
			// Product remaining quantity
			int Quantity;
		};

		// Product editing dialog box class derived from product editing dialog box prototype
		class CDialogBoxProduct :public IDialogBoxProduct
		{
		private:
			// This flag will store whether a dialog box is shown in create or edit product mode
			// It will store value of "is_new" parameter of Execute() method
			bool m_bIsNew;

			// This method will validate whether information on dialog box is correct or not
			bool Validate();
		protected:
			// This method will be called when user clicks on "OK" button
			void ButtonOk_OnClick(IControl *sender) override;

			// This method will be called when user clicks on "Cancel" button
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			// Constructor to create dialog box and put it onto a form
			CDialogBoxProduct(IForm *parent);

			// Return flag indicating whether a dialog box is shown in create or edit product mode
			bool isNew() const;
			// Return product information stored in dialog box
			PRODUCT getProduct() const;

			// Method for showing dialog box with specified product information
			void Execute(const PRODUCT &product, const bool is_new);
		};
	}
}
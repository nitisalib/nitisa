#pragma once

// Include header file with form prototype
#include "IFormProduct.h"

// Include header file where PRODUCT structure is declared
#include "DialogBoxProduct.h"

// Namespace where everything of the Nitisa framework is
namespace nitisa
{
	// Our application namespace. The same namespace where Form Builder put form prototype in
	namespace app
	{
		// Product editing form class derived from product editing form prototype
		class CFormProduct :public IFormProduct
		{
		private:
			// This method will validate whether information on form is correct or not
			bool Validate();
		protected:
			// This method will be called when user clicks on "OK" button
			void ButtonOk_OnClick(IControl *sender) override;

			// This method will be called when user clicks on "Cancel" button
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			// Constructor
			CFormProduct();

			// Return product information stored in form
			PRODUCT getProduct() const;

			// Method for showing form with specified product information
			ModalResult Execute(const PRODUCT &product);
		};

		// Variable where we will store form instance
		extern CFormProduct *FormProduct;
	}
}
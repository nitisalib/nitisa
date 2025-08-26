#pragma once

// Include header file with definition of IDialogBoxListener interface
#include "Nitisa/Interfaces/IDialogBoxListener.h"

// Include header file with form prototype
#include "IFormMain.h"

// Include header file where PRODUCT structure is defined as we use it here
#include "DialogBoxProduct.h"

// Namespace where everything of the Nitisa framework is
namespace nitisa
{
	// Our application namespace. The same namespace where Form Builder put form prototype in
	namespace app
	{
		// Inform compiler that such class exists
		class CDialogBoxConfirm;

		// Main form derived from main form prototype class
		class CFormMain :public IFormMain
		{
		private:
			// Dialog box listener we are going to use to get information from dialog boxes
			// It should implement IDialogBoxListener interface
			class CDialogBoxListener :public virtual IDialogBoxListener
			{
			private:
				// Pointer to the form
				CFormMain *m_pForm;
			public:
				// IDialogBoxListener methods we should implement
				void OnClose(IDialogBox *sender) override;
				void OnRestore(IDialogBox *sender) override;
				void OnMinimize(IDialogBox *sender) override;
				void OnMaximize(IDialogBox *sender) override;

				// Listener constructor
				CDialogBoxListener(CFormMain *form);
			};

			// Define some constants for different actions. We will use them with confirmation dialog box
			const int ACTION_DELETE{ -1 }; // Action is "Delete selected products"
			const int ACTION_CLEAR{ -2 }; // Action is "Clear information about all products"
		private:
			// Pointer to product dialog box
			CDialogBoxProduct *m_pDialogBoxProduct;
			// Pointer to confirmation dialog box
			CDialogBoxConfirm *m_pDialogBoxConfirm;
			// Products storage
			std::vector<PRODUCT> m_aProducts;
			// Flag used to automatically resize product dialog box only once
			bool m_bDialogBoxProductResized;
			// Flag used to automatically resize confirmation dialog box only once
			bool m_bDialogBoxConfirmResized;
			// Listener for dialog boxes
			CDialogBoxListener m_cDialogBoxListener;

			// This method return product dialog box creating one if it was not created yet
			CDialogBoxProduct *getDialogBoxProduct();
			// This method return confirmation dialog box creating one if it was not created yet
			CDialogBoxConfirm *getDialogBoxConfirm();
			// This method shows product dialog box with specified product information
			void ExecuteDialogBoxProduct(const PRODUCT &product, const bool is_new, const int tag);
			// This method shows confirmation dialog box with specified message
			void ExecuteDialogBoxConfirm(const String &message, const int tag);
		protected:
			// Method called when user click on "Add product" button
			void ButtonAdd_OnClick(IControl *sender) override;
			// Method called when user click on "Edit product" button
			void ButtonEdit_OnClick(IControl *sender) override;
			// Method called when user click on "Delete products" button
			void ButtonDelete_OnClick(IControl *sender) override;
			// Method called when user click on "Clear" button
			void ButtonClear_OnClick(IControl *sender) override;
		public:
			CFormMain();
		};

		// Variable where we will store form instance
		extern CFormMain *FormMain;
	}
}
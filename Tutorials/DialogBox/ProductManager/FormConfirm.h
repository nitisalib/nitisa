#pragma once

// Include header file with form prototype
#include "IFormConfirm.h"

// Namespace where everything of the Nitisa framework is
namespace nitisa
{
	// Our application namespace. The same namespace where Form Builder put form prototype in
	namespace app
	{
		// Confirmation form class derived from confirmation form prototype
		class CFormConfirm :public IFormConfirm
		{
		protected:
			// This method will be called when user clicks on "Yes" button
			void ButtonYes_OnClick(IControl *sender) override;

			// This method will be called when user clicks on "No" button
			void ButtonNo_OnClick(IControl *sender) override;
		public:
			// Constructor
			CFormConfirm();

			// Method for showing form with specified message
			ModalResult Execute(const String &message);
		};

		// Variable where we will store form instance
		extern CFormConfirm *FormConfirm;
	}
}
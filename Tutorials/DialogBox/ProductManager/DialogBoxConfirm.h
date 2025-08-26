#pragma once

// Include header file with form prototype in dialog box mode
#include "IDialogBoxConfirm.h"

// Namespace where everything of the Nitisa framework is
namespace nitisa
{
	// Our application namespace. The same namespace where Form Builder put form prototype in
	namespace app
	{
		// Confirmation dialog box class derived from confirmation dialog box prototype
		class CDialogBoxConfirm :public IDialogBoxConfirm
		{
		protected:
			// This method will be called when user clicks on "Yes" button
			void ButtonYes_OnClick(IControl *sender) override;

			// This method will be called when user clicks on "No" button
			void ButtonNo_OnClick(IControl *sender) override;
		public:
			// Constructor to create dialog box and put it onto a form
			CDialogBoxConfirm(IForm *parent);

			// Method for showing dialog box with specified message
			void Execute(const String &message);
		};
	}
}
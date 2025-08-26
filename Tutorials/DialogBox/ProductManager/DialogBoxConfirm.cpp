// Include header file with dialog box class declaration
#include "DialogBoxConfirm.h"

namespace nitisa
{
	namespace app
	{
		CDialogBoxConfirm::CDialogBoxConfirm(IForm *parent) :
			// In the constructor we should only call parent class constructor
			IDialogBoxConfirm(
				L"DialogBoxConfirm", // Our dialog box class name
				true, // Dialog box can be placed onto a form directly
				false, // Dialog box cannot be placed onto another widget
				false, // Dialog box cannot be focused
				false) // and as it cannot be focused "tab_stop" has no meaning, just put false
		{
			// Put dialog box onto specified form
			setForm(parent);
		}

		void CDialogBoxConfirm::ButtonYes_OnClick(IControl *sender)
		{
			// When user clicks on "Yes" button set dialog box showing result to "mrYes"
			// This will close dialog box automatically
			setModalResult(ModalResult::Yes);
		}

		void CDialogBoxConfirm::ButtonNo_OnClick(IControl *sender)
		{
			// When user clicks on "No" button set dialog box showing result to "mrNo"
			// This will close dialog box automatically
			setModalResult(ModalResult::No);
		}

		void CDialogBoxConfirm::Execute(const String &message)
		{
			// Show message on the label we added especially for this purpose
			m_pLabelMessage->setCaption(message);
			// Show dialog box modally
			ShowModal();
		}
	}
}
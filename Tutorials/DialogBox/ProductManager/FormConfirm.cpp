// Include header file with platform window management class
#include "Platform/Core/Window.h"

// Include header file with platform OpenGL renderer
#include "Platform/Core/Renderer.h"

// Include header file with form class declaration
#include "FormConfirm.h"

namespace nitisa
{
	namespace app
	{
		// Global varialbe for the form instance
		CFormConfirm *FormConfirm{ nullptr };

		CFormConfirm::CFormConfirm() :
			// Call parent constructor with platform window and renderer objects as usual
			IFormConfirm(CWindow::Create(), CRenderer::Create())
		{
			
		}

		void CFormConfirm::ButtonYes_OnClick(IControl *sender)
		{
			// When user clicks on "Yes" button set form showing result to "mrYes"
			// This will close form automatically
			setModalResult(ModalResult::Yes);
		}

		void CFormConfirm::ButtonNo_OnClick(IControl *sender)
		{
			// When user clicks on "No" button set form showing result to "mrNo"
			// This will close form automatically
			setModalResult(ModalResult::No);
		}

		ModalResult CFormConfirm::Execute(const String &message)
		{
			// Show message on the label we added especially for this purpose
			m_pLabelMessage->setCaption(message);
			// Show form modally
			return ShowModal();
		}
	}
}
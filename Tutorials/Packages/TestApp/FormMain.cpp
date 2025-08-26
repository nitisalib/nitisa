#include "Nitisa/Core/LockRepaint.h"

#include "Platform/Core/Renderer.h"
#include "Platform/Core/Window.h"

#include "CoolWidgets/CoolWidgets.h"

#include "FormMain.h"

namespace nitisa
{
	CFormMain *FormMain{ nullptr };

	CFormMain::CFormMain() :
		CForm(L"FormMain", CWindow::Create(), CRenderer::Create())
	{
		CLockRepaint lock{ this };
		m_pRegistration = new coolwidgets::CRegistration(this);
		m_pRegistration->getTransform()->Translate(100, 100, 0);
	}
}
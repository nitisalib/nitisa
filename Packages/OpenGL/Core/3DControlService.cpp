// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#include "Platform/OpenGL/OpenGL.h"

namespace nitisa
{
	namespace opengl
	{
	#pragma region Constructor & destructor
		C3DControlService::C3DControlService(C3DControl *control) :
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region State change notifications
		void C3DControlService::NotifyOnFreeResources()
		{
			COpenGL *graphics{ nullptr };
			if (m_pControl->getForm() && m_pControl->getForm()->getRenderer())
				graphics = cast<COpenGL*>(m_pControl->getForm()->getRenderer()->NativeGraphics);
			m_pControl->FreeResources(graphics);
		}
	#pragma endregion

	#pragma region Control notifications
		void C3DControlService::NotifyOnControlDetach(IControl *control)
		{
			if (cast<IMaterialControl*>(control) == m_pControl->m_pMaterial)
				m_pControl->m_pMaterial = nullptr;
		}

		void C3DControlService::NotifyOnControlChange(IControl *control)
		{
			if (m_pControl->m_pMaterial && cast<IMaterialControl*>(control) == m_pControl->m_pMaterial)
				SendChangeNotification();
		}
	#pragma endregion

	#pragma region Rendering
		void C3DControlService::NotifyOnRender(COpenGL *graphics, IRenderer *renderer, ICamera *camera)
		{
			switch (m_pControl->m_eRenderMode)
			{
			case I3DControl::RenderMode::Vertices:
				graphics->PolygonMode(GL_FRONT_AND_BACK, GL_POINT);
				graphics->Disable(GL_CULL_FACE);
				m_pControl->Render(graphics, renderer, camera);
				graphics->Enable(GL_CULL_FACE);
				graphics->PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				break;
			case I3DControl::RenderMode::Wireframe:
				graphics->PolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				graphics->Disable(GL_CULL_FACE);
				m_pControl->Render(graphics, renderer, camera);
				graphics->Enable(GL_CULL_FACE);
				graphics->PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				break;
			default:
				m_pControl->Render(graphics, renderer, camera);
			}
		}
	#pragma endregion
	}
}
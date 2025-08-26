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
		CViewService::CViewService(CView *control):
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Control notifications
		void CViewService::NotifyOnControlChange(IControl *control)
		{
			if (cast<I3DControl*>(control) && m_pControl->hasChild(control))
				m_pControl->ForceUpdate();
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CViewService::NotifyOnParentFontChange()
		{
			m_pControl->ForceUpdate();
		}
	#pragma endregion

	#pragma region Notifications from child controls
		void CViewService::NotifyOnChildAttach(IControl *control)
		{
			m_pControl->ForceUpdate();
		}

		void CViewService::NotifyOnChildDetach(IControl *control)
		{
			m_pControl->ForceUpdate();
		}
	#pragma endregion

	#pragma region State change notifications
		void CViewService::NotifyOnFreeResources()
		{
			COpenGL *graphics{ nullptr };
			if (m_pControl->getForm() && m_pControl->getForm()->getRenderer())
				graphics = cast<COpenGL*>(m_pControl->getForm()->getRenderer()->NativeGraphics);
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
			m_pControl->m_cAxes.FreeResources(graphics);
			m_pControl->m_cGrid.FreeResources(graphics);
			if (m_pControl->m_pFramebuffer)
			{
				m_pControl->m_pFramebuffer->Release();
				m_pControl->m_pFramebuffer = nullptr;
			}
			if (m_pControl->m_pDepthTexture)
			{
				m_pControl->m_pDepthTexture->Release();
				m_pControl->m_pDepthTexture = nullptr;
			}
			if (m_pControl->m_pProgram)
			{
				m_pControl->m_pProgram->Release();
				m_pControl->m_pProgram = nullptr;
				m_pControl->m_bProgramValid = false;
			}
		}

		void CViewService::NotifyOnResize()
		{
			m_pControl->ForceUpdate();
		}

		void CViewService::NotifyOnFontChange()
		{
			m_pControl->ForceUpdate();
		}
	#pragma endregion

	#pragma region Paint notifications
		void CViewService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
				m_pControl->Render();
			draw_children = false;
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CViewService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				bool ctrl, alt, shift;
				Application->Keyboard->getControlKeys(ctrl, alt, shift);
				float delta{ m_pControl->m_fMoveSpeed };
				if (ctrl)
					delta *= m_pControl->m_fMoveFastMultiplier;
				if (shift)
					delta *= m_pControl->m_fMoveSlowMultiplier;
				switch (m.Key)
				{
				case Key::W:
					m_pControl->m_pCamera->MoveForward(delta);
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
					break;
				case Key::S:
					m_pControl->m_pCamera->MoveBackward(delta);
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
					break;
				case Key::A:
					m_pControl->m_pCamera->MoveLeft(delta);
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
					break;
				case Key::D:
					m_pControl->m_pCamera->MoveRight(delta);
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
					break;
				case Key::C:
					m_pControl->m_pCamera->MoveDown(delta);
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
					break;
				case Key::Space:
					m_pControl->m_pCamera->MoveUp(delta);
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
					break;
				case Key::M:
					switch (m_pControl->m_pCamera->ProjectionMode)
					{
					case ProjectionMode::Perspective:
						m_fNearPlane = m_pControl->m_pCamera->NearPlane;
						m_pControl->m_pCamera->setProjectionMode(ProjectionMode::Orthographic);
						m_pControl->m_pCamera->setNearPlane(-1000);
						if (m_pControl->m_pCanvas)
							m_pControl->m_pCanvas->setValid(false);
						m_pControl->Repaint(false);
						break;
					case ProjectionMode::Orthographic:
						m_pControl->m_pCamera->setProjectionMode(ProjectionMode::Perspective);
						m_pControl->m_pCamera->setNearPlane(m_fNearPlane);
						if (m_pControl->m_pCanvas)
							m_pControl->m_pCanvas->setValid(false);
						m_pControl->Repaint(false);
						break;
					}
					break;
				}
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CViewService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isCaptureMouse())
			{
				PointF delta{ m.Position - m_sDownPosition };
				if (ntl::IsNotEqual<float>(delta.X, 0) || ntl::IsNotEqual<float>(delta.Y, 0))
				{
					m_pControl->m_pCamera->setPitch(-ntl::Sign<float>(delta.Y) * m_pControl->m_fTurnSpeed, true);
					m_pControl->m_pCamera->setYaw(-ntl::Sign<float>(delta.X) * m_pControl->m_fTurnSpeed, true);
					m_sDownPosition = m.Position;
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
			}
		}

		void CViewService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m_pControl->isCaptureMouse())
			{
				if (m_pControl->isEnabled(true))
				{
					m_sDownPosition = m.Position;
					m_pControl->getForm()->CaptureMouse(m_pControl, true);
				}
			}
			else
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CViewService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CViewService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CViewService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CViewService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CViewService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CViewService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CViewService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CViewService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			if (m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}

		void CViewService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				m_pControl->m_pCamera->setFOV(ntl::Max<float>(0, ntl::Min<float>(ntl::Pi<float>, m_pControl->m_pCamera->FOV + ntl::Sign<int>(m.Delta) * m_pControl->m_fFOVStep)));
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion
	}
}
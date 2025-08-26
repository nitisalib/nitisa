// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace standard
	{
	#pragma region Constructor & destructor
		CSplitterService::CSplitterService(CSplitter *splitter) :
			CControlService(splitter),
			m_pSplitter{ splitter }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CSplitterService::CancelDown(const bool check_capture)
		{
			if (m_pSplitter->m_bActive)
			{
				m_pSplitter->m_bActive = false;
				if (m_pSplitter->m_pCanvas)
					m_pSplitter->m_pCanvas->setValid(false);
				m_pSplitter->Repaint(false);
				if (check_capture && m_pSplitter->isCaptureMouse())
					m_pSplitter->getForm()->ReleaseCaptureMouse();
			}
		}

		bool CSplitterService::UpdateDown(const PointF &position)
		{
			m_pDownControl = nullptr;
			if (m_pSplitter->getParent())
			{
				m_sDownPosition = m_pSplitter->getParent()->FormToLocal((PointF)m_pSplitter->getForm()->ScreenToClient(Point{ ntl::Round<int>(position.X), ntl::Round<int>(position.Y) }));
				int index{ m_pSplitter->getParent()->getControlIndex(m_pSplitter) };
				for (int i = index - 1; i >= 0; i--)
				{
					IControl *control{ m_pSplitter->getParent()->getControl(i) };
					if (control->isVisible(false))
					{
						if (m_pSplitter->getAlign() == Align::Top && (control->getAlign() == Align::Top || control->getAlign() == Align::Client))
							m_pDownControl = control;
						else if (m_pSplitter->getAlign() == Align::Bottom && (control->getAlign() == Align::Bottom || control->getAlign() == Align::Client))
							m_pDownControl = control;
						else if (m_pSplitter->getAlign() == Align::Left && (control->getAlign() == Align::Left || control->getAlign() == Align::Client))
							m_pDownControl = control;
						else if (m_pSplitter->getAlign() == Align::Right && (control->getAlign() == Align::Right || control->getAlign() == Align::Client))
							m_pDownControl = control;
						if (m_pDownControl)
							break;
					}
				}
				if (!m_pDownControl)
					for (int i = index + 1; i < m_pSplitter->getParent()->getControlCount(); i++)
					{
						IControl *control{ m_pSplitter->getParent()->getControl(i) };
						if (control->isVisible(false))
						{
							if (m_pSplitter->getAlign() == Align::Top && (control->getAlign() == Align::Top || control->getAlign() == Align::Client))
								m_pDownControl = control;
							else if (m_pSplitter->getAlign() == Align::Bottom && (control->getAlign() == Align::Bottom || control->getAlign() == Align::Client))
								m_pDownControl = control;
							else if (m_pSplitter->getAlign() == Align::Left && (control->getAlign() == Align::Left || control->getAlign() == Align::Client))
								m_pDownControl = control;
							else if (m_pSplitter->getAlign() == Align::Right && (control->getAlign() == Align::Right || control->getAlign() == Align::Client))
								m_pDownControl = control;
							if (m_pDownControl)
								break;
						}
					}
			}
			else
			{
				m_sDownPosition = (PointF)m_pSplitter->getForm()->ScreenToClient(Point{ ntl::Round<int>(position.X), ntl::Round<int>(position.Y) });
				int index{ m_pSplitter->getForm()->getControlIndex(m_pSplitter) };
				for (int i = index - 1; i >= 0; i--)
				{
					IControl *control{ m_pSplitter->getForm()->getControl(i) };
					if (control->isVisible(false))
					{
						if (m_pSplitter->getAlign() == Align::Top && (control->getAlign() == Align::Top || control->getAlign() == Align::Client))
							m_pDownControl = control;
						else if (m_pSplitter->getAlign() == Align::Bottom && (control->getAlign() == Align::Bottom || control->getAlign() == Align::Client))
							m_pDownControl = control;
						else if (m_pSplitter->getAlign() == Align::Left && (control->getAlign() == Align::Left || control->getAlign() == Align::Client))
							m_pDownControl = control;
						else if (m_pSplitter->getAlign() == Align::Right && (control->getAlign() == Align::Right || control->getAlign() == Align::Client))
							m_pDownControl = control;
						if (m_pDownControl)
							break;
					}
				}
				if (!m_pDownControl)
					for (int i = index + 1; i < m_pSplitter->getForm()->getControlCount(); i++)
					{
						IControl *control{ m_pSplitter->getForm()->getControl(i) };
						if (control->isVisible(false))
						{
							if (m_pSplitter->getAlign() == Align::Top && (control->getAlign() == Align::Top || control->getAlign() == Align::Client))
								m_pDownControl = control;
							else if (m_pSplitter->getAlign() == Align::Bottom && (control->getAlign() == Align::Bottom || control->getAlign() == Align::Client))
								m_pDownControl = control;
							else if (m_pSplitter->getAlign() == Align::Left && (control->getAlign() == Align::Left || control->getAlign() == Align::Client))
								m_pDownControl = control;
							else if (m_pSplitter->getAlign() == Align::Right && (control->getAlign() == Align::Right || control->getAlign() == Align::Client))
								m_pDownControl = control;
							if (m_pDownControl)
								break;
						}
					}
			}
			if (m_pDownControl)
				m_sDownControlSize = m_pDownControl->getSize();
			return m_pDownControl != nullptr;
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CSplitterService::NotifyOnParentStyleChange()
		{
			if (m_pSplitter->getStyle())
			{
				m_pSplitter->UpdateFromStyle(m_pSplitter->getStyle());
				if (m_pSplitter->m_pCanvas)
					m_pSplitter->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CSplitterService::NotifyOnFreeResources()
		{
			if (m_pSplitter->m_pCanvas)
			{
				m_pSplitter->m_pCanvas->Release();
				m_pSplitter->m_pCanvas = nullptr;
			}
		}

		void CSplitterService::NotifyOnEnable()
		{
			if (m_pSplitter->m_pCanvas)
				m_pSplitter->m_pCanvas->setValid(false);
		}

		void CSplitterService::NotifyOnDisable()
		{
			if (m_pSplitter->m_pCanvas)
				m_pSplitter->m_pCanvas->setValid(false);
		}

		void CSplitterService::NotifyOnResize()
		{
			if (m_pSplitter->m_pCanvas)
				m_pSplitter->m_pCanvas->setValid(false);
		}

		void CSplitterService::NotifyOnStyleChange()
		{
			if (m_pSplitter->getStyle())
			{
				m_pSplitter->UpdateFromStyle(m_pSplitter->getStyle());
				if (m_pSplitter->m_pCanvas)
					m_pSplitter->m_pCanvas->setValid(false);
			}
		}

		void CSplitterService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CSplitterService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pSplitter->getWidth(), 0) && ntl::IsGreater<float>(m_pSplitter->getHeight(), 0))
				m_pSplitter->Render();
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CSplitterService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pSplitter->m_pCanvas)
				m_pSplitter->m_pCanvas->setValid(false);
			m_pSplitter->Repaint(false);
		}

		void CSplitterService::NotifyOnMouseLeave()
		{
			if (m_pSplitter->m_pCanvas)
				m_pSplitter->m_pCanvas->setValid(false);
			m_pSplitter->Repaint(false);
		}

		void CSplitterService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pSplitter->m_bActive)
			{
				if (m_pSplitter->getParent())
				{
					PointF p{ m_pSplitter->getParent()->FormToLocal((PointF)m_pSplitter->getForm()->ScreenToClient(Point{ ntl::Round<int>(m.Position.X), ntl::Round<int>(m.Position.Y) })) };
					int index{ m_pSplitter->getParent()->getControlIndex(m_pSplitter) }, index_down{ m_pSplitter->getParent()->getControlIndex(m_pDownControl) };
					if (m_pSplitter->getAlign() == Align::Top || m_pSplitter->getAlign() == Align::Bottom)
					{
						if (index > index_down)
							m_pDownControl->setHeight(m_sDownControlSize.Y - (m_sDownPosition.Y - p.Y));
						else
							m_pDownControl->setHeight(m_sDownControlSize.Y + (m_sDownPosition.Y - p.Y));
					}
					else
					{
						if (index > index_down)
							m_pDownControl->setWidth(m_sDownControlSize.X - (m_sDownPosition.X - p.X));
						else
							m_pDownControl->setWidth(m_sDownControlSize.X + (m_sDownPosition.X - p.X));
					}
				}
				else
				{
					PointF p{ (PointF)m_pSplitter->getForm()->ScreenToClient(Point{ ntl::Round<int>(m.Position.X), ntl::Round<int>(m.Position.Y) }) };
					int index{ m_pSplitter->getForm()->getControlIndex(m_pSplitter) }, index_down{ m_pSplitter->getForm()->getControlIndex(m_pDownControl) };
					if (m_pSplitter->getAlign() == Align::Top || m_pSplitter->getAlign() == Align::Bottom)
					{
						if (index > index_down)
							m_pDownControl->setHeight(m_sDownControlSize.Y - (m_sDownPosition.Y - p.Y));
						else
							m_pDownControl->setHeight(m_sDownControlSize.Y + (m_sDownPosition.Y - p.Y));
					}
					else
					{
						if (index > index_down)
							m_pDownControl->setWidth(m_sDownControlSize.X - (m_sDownPosition.X - p.X));
						else
							m_pDownControl->setWidth(m_sDownControlSize.X + (m_sDownPosition.X - p.X));
					}
				}
			}
		}

		void CSplitterService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m_pSplitter->m_bActive && !m.Middle && !m.Right && m_pSplitter->isEnabled(true) && UpdateDown(m.Position))
			{
				m_pSplitter->m_bActive = true;
				m_pSplitter->getForm()->CaptureMouse(m_pSplitter, true);
				if (m_pSplitter->m_pCanvas)
					m_pSplitter->m_pCanvas->setValid(false);
				m_pSplitter->Repaint(false);
			}
			else
				CancelDown(true);
		}

		void CSplitterService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			CancelDown(true);
		}

		void CSplitterService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CSplitterService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CSplitterService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CSplitterService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CSplitterService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CSplitterService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}

		void CSplitterService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true);
		}
	#pragma endregion
	}
}
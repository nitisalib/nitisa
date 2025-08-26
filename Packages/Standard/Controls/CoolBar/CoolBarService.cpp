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
		CCoolBarService::CCoolBarService(CCoolBar *control):
			CDialogBoxService(control),
			m_pControl{ control },
			m_bIgnoreTransformControls{ false }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CCoolBarService::AlignControls()
		{
			if (!m_pControl->m_bAligning)
				m_pControl->PostClientAreaChange();
		}

		ICoolBar *CCoolBarService::FindPrevBar()
		{
			int index{ m_sDownConfig.ParentBar->getControlIndex(m_pControl) - 1 };
			while (index >= 0)
			{
				IControl *control{ m_sDownConfig.ParentBar->getControl(index) };
				if (control->isVisible(false))
				{
					ICoolBar *result{ cast<ICoolBar*>(control) };
					if (result)
					{
						switch (result->getOrientation())
						{
						case ICoolBar::Orientation::LeftToRight:
						case ICoolBar::Orientation::RightToLeft:
							if (m_sDownConfig.ParentBar->getOrientation() != ICoolBar::Orientation::LeftToRight && m_sDownConfig.ParentBar->getOrientation() != ICoolBar::Orientation::RightToLeft)
								return nullptr;
							break;
						case ICoolBar::Orientation::TopToBottom:
						case ICoolBar::Orientation::BottomToTop:
							if (m_sDownConfig.ParentBar->getOrientation() != ICoolBar::Orientation::TopToBottom && m_sDownConfig.ParentBar->getOrientation() != ICoolBar::Orientation::BottomToTop)
								return nullptr;
							break;
						}
					}
					return result;
				}
				index--;
			}
			return nullptr;
		}

		IControl *CCoolBarService::FindPrevControl()
		{
			int index{ m_sDownConfig.Parent->getControlIndex(m_pControl) - 1 };
			while (index >= 0)
			{
				IControl *control{ m_sDownConfig.Parent->getControl(index) };
				if (control->isVisible(false))
					return control;
				index--;
			}
			return nullptr;
		}

		IControl *CCoolBarService::FindNextControl()
		{
			int index{ m_sDownConfig.Parent->getControlIndex(m_pControl) + 1 };
			while (index < m_sDownConfig.Parent->getControlCount())
			{
				IControl *control{ m_sDownConfig.Parent->getControl(index) };
				if (control->isVisible(false))
					return control;
				index++;
			}
			return nullptr;
		}

		IControl *CCoolBarService::FindPrevAlignedControl(const Align align)
		{
			if (m_sDownConfig.Parent)
			{
				IControl *control;
				int index{ m_sDownConfig.Parent->getControlIndex(m_pControl) - 1 };
				for (int i = index; i >= 0; i--)
				{
					control = m_sDownConfig.Parent->getControl(i);
					if (control->isVisible(false) && control->getAlign() == align)
						return control;
				}
			}
			else
			{
				IForm *parent{ m_pControl->getForm() };
				IControl *control;
				int index{ parent->getControlIndex(m_pControl) - 1 };
				for (int i = index; i >= 0; i--)
				{
					control = parent->getControl(i);
					if (control->isVisible(false) && control->getAlign() == align)
						return control;
				}
			}
			return nullptr;
		}

		IControl *CCoolBarService::FindNextAlignedControl(const Align align)
		{
			if (m_sDownConfig.Parent)
			{
				IControl *control;
				int index{ m_sDownConfig.Parent->getControlIndex(m_pControl) + 1 };
				for (int i = index; i < m_sDownConfig.Parent->getControlCount(); i++)
				{
					control = m_sDownConfig.Parent->getControl(i);
					if (control->isVisible(false) && control->getAlign() == align)
						return control;
				}
			}
			else
			{
				IForm *parent{ m_pControl->getForm() };
				IControl *control;
				int index{ parent->getControlIndex(m_pControl) + 1 };
				for (int i = index; i < parent->getControlCount(); i++)
				{
					control = parent->getControl(i);
					if (control->isVisible(false) && control->getAlign() == align)
						return control;
				}
			}
			return nullptr;
		}

		IControl *CCoolBarService::FindLastAlignedControl(const Align align)
		{
			if (m_sDownConfig.Parent)
			{
				IControl *control;
				for (int i = m_sDownConfig.Parent->getControlCount() - 1; i >= 0; i--)
				{
					control = m_sDownConfig.Parent->getControl(i);
					if (control->isVisible(false) && control->getAlign() == align)
						return control;
				}
			}
			else
			{
				IForm *parent{ m_pControl->getForm() };
				IControl *control;
				for (int i = parent->getControlCount() - 1; i >= 0; i--)
				{
					control = parent->getControl(i);
					if (control->isVisible(false) && control->getAlign() == align)
						return control;
				}
			}
			return nullptr;
		}

		PointF CCoolBarService::CalculateControlPosition(const PointF &pos_on_parent)
		{
			switch (m_pControl->m_eOrientation)
			{
			case ICoolBar::Orientation::TopToBottom:
				return PointF{ pos_on_parent.X - m_pControl->getWidth() + m_sDownConfig.DownShiftControl.Y, pos_on_parent.Y - m_sDownConfig.DownShiftControl.X };
			case ICoolBar::Orientation::RightToLeft:
				return PointF{ pos_on_parent.X - m_pControl->getWidth() + m_sDownConfig.DownShiftControl.X, pos_on_parent.Y - m_sDownConfig.DownShiftControl.Y };
			case ICoolBar::Orientation::BottomToTop:
				return PointF{ pos_on_parent.X - m_sDownConfig.DownShiftControl.Y, pos_on_parent.Y - m_pControl->getHeight() + m_sDownConfig.DownShiftControl.X };
			default: // ICoolBar::Orientation::LeftToRight
				return pos_on_parent - m_sDownConfig.DownShiftControl;
			}
		}

		void CCoolBarService::ProcessMoveOnBarLeftToRight(const PointF &pos_on_parent)
		{
			// Move, change order, change size of nearest bars
			ICoolBar *prev_bar;
			IControl *prev_control, *next_control;
			if (ntl::IsLess<float>(pos_on_parent.X, m_sDownConfig.PrevPosParent.X))
			{
				// Move left
				PointF control_pos{ CalculateControlPosition(pos_on_parent) };
				if ((prev_bar = FindPrevBar()) && prev_bar->isResizable())
				{
					// Previous visible control is a bar
					if (control_pos.X < prev_bar->getTransform()->getTx())
					{
						if (m_sDownConfig.PrevBar)
						{
							m_sDownConfig.PrevBar->setSize(m_sDownConfig.PrevBarSize);
							m_sDownConfig.PrevBar = nullptr;
						}
						m_pControl->BringBefore(prev_bar);
					}
					else
					{
						if (!m_sDownConfig.PrevBar)
						{
							m_sDownConfig.PrevBar = prev_bar;
							m_sDownConfig.PrevBarSize = prev_bar->getSize();
						}
						RectF client{ m_sDownConfig.ParentBar->getClientRect() };
						PointF limits{ prev_bar->getResizeLimits() };
						float max_prev_bar_size{ client.width() - m_pControl->getWidth() - prev_bar->getTransform()->getTx() + client.Left };
						prev_bar->setWidth(ntl::Clamp<float>(control_pos.X - prev_bar->getTransform()->getTx(), limits.X, ntl::Min<float>(max_prev_bar_size, limits.Y)));
					}
				}
				else if ((prev_control = FindPrevControl()) && control_pos.X < prev_control->getTransform()->getTx()) // Previous visible control is not a bar
					m_pControl->BringBefore(prev_control);
				// Else do nothing, the control is the first visible one in the list
			}
			else if (ntl::IsGreater<float>(pos_on_parent.X, m_sDownConfig.PrevPosParent.X))
			{
				// Move right
				PointF control_pos{ CalculateControlPosition(pos_on_parent) };
				if (m_sDownConfig.PrevBar) // Need clean previous bar pointer if it was resized downward before
				{
					RectF client{ m_sDownConfig.ParentBar->getClientRect() };
					PointF limits{ m_sDownConfig.PrevBar->getResizeLimits() };
					float max_prev_bar_size{ client.width() - m_pControl->getWidth() - m_sDownConfig.PrevBar->getTransform()->getTx() + client.Left };
					float new_size{ ntl::Clamp<float>(control_pos.X - m_sDownConfig.PrevBar->getTransform()->getTx(), limits.X, ntl::Min<float>(max_prev_bar_size, limits.Y)) };
					if (new_size >= m_sDownConfig.PrevBarSize.X)
					{
						m_sDownConfig.PrevBar->setSize(m_sDownConfig.PrevBarSize);
						m_sDownConfig.PrevBar = nullptr;
					}
					else
						m_sDownConfig.PrevBar->setWidth(new_size);
				}
				if ((prev_bar = FindPrevBar()) && prev_bar->isResizable()) // Resize previous resizable bar, can be ignored or modified due to constraints
				{
					RectF client{ m_sDownConfig.ParentBar->getClientRect() };
					PointF limits{ prev_bar->getResizeLimits() };
					float max_prev_bar_size{ client.width() - m_pControl->getWidth() - prev_bar->getTransform()->getTx() + client.Left };
					prev_bar->setWidth(ntl::Clamp<float>(control_pos.X - prev_bar->getTransform()->getTx(), limits.X, ntl::Min<float>(max_prev_bar_size, limits.Y)));
				}
				if ((next_control = FindNextControl())) // Move after next control
				{
					if (control_pos.X + m_pControl->getWidth() > next_control->getTransform()->getTx() + next_control->getWidth())
						m_pControl->BringAfter(next_control);
				}
			}
		}

		void CCoolBarService::ProcessMoveOnBarTopToBottom(const PointF &pos_on_parent)
		{
			// Move, change order, change size of nearest bars
			ICoolBar *prev_bar;
			IControl *prev_control, *next_control;
			if (ntl::IsLess<float>(pos_on_parent.Y, m_sDownConfig.PrevPosParent.Y))
			{
				// Move left
				PointF control_pos{ CalculateControlPosition(pos_on_parent) };
				if ((prev_bar = FindPrevBar()) && prev_bar->isResizable())
				{
					// Previous visible control is a bar
					if (control_pos.Y < prev_bar->getTransform()->getTy())
					{
						if (m_sDownConfig.PrevBar)
						{
							m_sDownConfig.PrevBar->setSize(m_sDownConfig.PrevBarSize);
							m_sDownConfig.PrevBar = nullptr;
						}
						m_pControl->BringBefore(prev_bar);
					}
					else
					{
						if (!m_sDownConfig.PrevBar)
						{
							m_sDownConfig.PrevBar = prev_bar;
							m_sDownConfig.PrevBarSize = prev_bar->getSize();
						}
						RectF client{ m_sDownConfig.ParentBar->getClientRect() };
						PointF limits{ prev_bar->getResizeLimits() };
						float max_prev_bar_size{ client.height() - m_pControl->getHeight() - prev_bar->getTransform()->getTy() + client.Top };
						prev_bar->setHeight(ntl::Clamp<float>(control_pos.Y - prev_bar->getTransform()->getTy(), limits.X, ntl::Min<float>(max_prev_bar_size, limits.Y)));
					}
				}
				else if ((prev_control = FindPrevControl()) && control_pos.Y < prev_control->getTransform()->getTy()) // Previous visible control is not a bar
					m_pControl->BringBefore(prev_control);
				// Else do nothing, the control is the first visible one in the list
			}
			else if (ntl::IsGreater<float>(pos_on_parent.Y, m_sDownConfig.PrevPosParent.Y))
			{
				// Move right
				PointF control_pos{ CalculateControlPosition(pos_on_parent) };
				if (m_sDownConfig.PrevBar) // Need clean previous bar pointer if it was resized downward before
				{
					RectF client{ m_sDownConfig.ParentBar->getClientRect() };
					PointF limits{ m_sDownConfig.PrevBar->getResizeLimits() };
					float max_prev_bar_size{ client.height() - m_pControl->getHeight() - m_sDownConfig.PrevBar->getTransform()->getTy() + client.Top };
					float new_size{ ntl::Clamp<float>(control_pos.Y - m_sDownConfig.PrevBar->getTransform()->getTy(), limits.X, ntl::Min<float>(max_prev_bar_size, limits.Y)) };
					if (new_size >= m_sDownConfig.PrevBarSize.Y)
					{
						m_sDownConfig.PrevBar->setSize(m_sDownConfig.PrevBarSize);
						m_sDownConfig.PrevBar = nullptr;
					}
					else
						m_sDownConfig.PrevBar->setHeight(new_size);
				}
				if ((prev_bar = FindPrevBar()) && prev_bar->isResizable()) // Resize previous resizable bar, can be ignored or modified due to constraints
				{
					RectF client{ m_sDownConfig.ParentBar->getClientRect() };
					PointF limits{ prev_bar->getResizeLimits() };
					float max_prev_bar_size{ client.height() - m_pControl->getHeight() - prev_bar->getTransform()->getTy() + client.Top };
					prev_bar->setHeight(ntl::Clamp<float>(control_pos.Y - prev_bar->getTransform()->getTy(), limits.X, ntl::Min<float>(max_prev_bar_size, limits.Y)));
				}
				if ((next_control = FindNextControl())) // Move after next control
				{
					if (control_pos.Y + m_pControl->getHeight() > next_control->getTransform()->getTy() + next_control->getHeight())
						m_pControl->BringAfter(next_control);
				}
			}
		}

		void CCoolBarService::ProcessMoveOnBarRightToLeft(const PointF &pos_on_parent)
		{
			// Move, change order, change size of nearest bars
			ICoolBar *prev_bar;
			IControl *prev_control, *next_control;
			if (ntl::IsGreater<float>(pos_on_parent.X, m_sDownConfig.PrevPosParent.X))
			{
				// Move left
				PointF control_pos{ CalculateControlPosition(pos_on_parent) };
				if ((prev_bar = FindPrevBar()) && prev_bar->isResizable())
				{
					// Previous visible control is a bar
					if (control_pos.X + m_pControl->getWidth() > prev_bar->getTransform()->getTx() + prev_bar->getWidth())
					{
						if (m_sDownConfig.PrevBar)
						{
							m_sDownConfig.PrevBar->setSize(m_sDownConfig.PrevBarSize);
							m_sDownConfig.PrevBar = nullptr;
						}
						m_pControl->BringBefore(prev_bar);
					}
					else
					{
						if (!m_sDownConfig.PrevBar)
						{
							m_sDownConfig.PrevBar = prev_bar;
							m_sDownConfig.PrevBarSize = prev_bar->getSize();
						}
						RectF client{ m_sDownConfig.ParentBar->getClientRect() };
						PointF limits{ prev_bar->getResizeLimits() };
						float max_prev_bar_size{ prev_bar->getTransform()->getTx() - client.Left + prev_bar->getWidth() - m_pControl->getWidth() };
						prev_bar->setWidth(ntl::Clamp<float>(prev_bar->getTransform()->getTx() + prev_bar->getWidth() - control_pos.X - m_pControl->getWidth(), limits.X, ntl::Min<float>(max_prev_bar_size, limits.Y)));
					}
				}
				else if ((prev_control = FindPrevControl()) && control_pos.X + m_pControl->getWidth() > prev_control->getTransform()->getTx() + prev_control->getWidth()) // Previous visible control is not a bar
					m_pControl->BringBefore(prev_control);
				// Else do nothing, the control is the first visible one in the list
			}
			else if (ntl::IsLess<float>(pos_on_parent.X, m_sDownConfig.PrevPosParent.X))
			{
				// Move right
				PointF control_pos{ CalculateControlPosition(pos_on_parent) };
				if (m_sDownConfig.PrevBar) // Need clean previous bar pointer if it was resized downward before
				{
					RectF client{ m_sDownConfig.ParentBar->getClientRect() };
					PointF limits{ m_sDownConfig.PrevBar->getResizeLimits() };
					float max_prev_bar_size{ m_sDownConfig.PrevBar->getTransform()->getTx() - client.Left + m_sDownConfig.PrevBar->getWidth() - m_pControl->getWidth() };
					float new_size{ ntl::Clamp<float>(m_sDownConfig.PrevBar->getTransform()->getTx() + m_sDownConfig.PrevBar->getWidth() - control_pos.X - m_pControl->getWidth(), limits.X, ntl::Min<float>(max_prev_bar_size, limits.Y)) };
					if (new_size >= m_sDownConfig.PrevBarSize.X)
					{
						m_sDownConfig.PrevBar->setSize(m_sDownConfig.PrevBarSize);
						m_sDownConfig.PrevBar = nullptr;
					}
					else
						m_sDownConfig.PrevBar->setWidth(new_size);
				}
				if ((prev_bar = FindPrevBar()) && prev_bar->isResizable()) // Resize previous resizable bar, can be ignored or modified due to constraints
				{
					RectF client{ m_sDownConfig.ParentBar->getClientRect() };
					PointF limits{ prev_bar->getResizeLimits() };
					float max_prev_bar_size{ prev_bar->getTransform()->getTx() - client.Left + prev_bar->getWidth() - m_pControl->getWidth() };
					prev_bar->setWidth(ntl::Clamp<float>(prev_bar->getTransform()->getTx() + prev_bar->getWidth() - control_pos.X - m_pControl->getWidth(), limits.X, ntl::Min<float>(max_prev_bar_size, limits.Y)));
				}
				if ((next_control = FindNextControl())) // Move after next control
				{
					if (control_pos.X < next_control->getTransform()->getTx())
						m_pControl->BringAfter(next_control);
				}
			}
		}

		void CCoolBarService::ProcessMoveOnBarBottomToTop(const PointF &pos_on_parent)
		{
			// Move, change order, change size of nearest bars
			ICoolBar *prev_bar;
			IControl *prev_control, *next_control;
			if (ntl::IsGreater<float>(pos_on_parent.Y, m_sDownConfig.PrevPosParent.Y))
			{
				// Move left
				PointF control_pos{ CalculateControlPosition(pos_on_parent) };
				if ((prev_bar = FindPrevBar()) && prev_bar->isResizable())
				{
					// Previous visible control is a bar
					if (control_pos.Y + m_pControl->getHeight() > prev_bar->getTransform()->getTy() + prev_bar->getHeight())
					{
						if (m_sDownConfig.PrevBar)
						{
							m_sDownConfig.PrevBar->setSize(m_sDownConfig.PrevBarSize);
							m_sDownConfig.PrevBar = nullptr;
						}
						m_pControl->BringBefore(prev_bar);
					}
					else
					{
						if (!m_sDownConfig.PrevBar)
						{
							m_sDownConfig.PrevBar = prev_bar;
							m_sDownConfig.PrevBarSize = prev_bar->getSize();
						}
						RectF client{ m_sDownConfig.ParentBar->getClientRect() };
						PointF limits{ prev_bar->getResizeLimits() };
						float max_prev_bar_size{ prev_bar->getTransform()->getTy() - client.Top + prev_bar->getHeight() - m_pControl->getHeight() };
						prev_bar->setHeight(ntl::Clamp<float>(prev_bar->getTransform()->getTy() + prev_bar->getHeight() - control_pos.Y - m_pControl->getHeight(), limits.X, ntl::Min<float>(max_prev_bar_size, limits.Y)));
					}
				}
				else if ((prev_control = FindPrevControl()) && control_pos.Y + m_pControl->getHeight() > prev_control->getTransform()->getTy() + prev_control->getHeight()) // Previous visible control is not a bar
					m_pControl->BringBefore(prev_control);
				// Else do nothing, the control is the first visible one in the list
			}
			else if (ntl::IsLess<float>(pos_on_parent.Y, m_sDownConfig.PrevPosParent.Y))
			{
				// Move right
				PointF control_pos{ CalculateControlPosition(pos_on_parent) };
				if (m_sDownConfig.PrevBar) // Need clean previous bar pointer if it was resized downward before
				{
					RectF client{ m_sDownConfig.ParentBar->getClientRect() };
					PointF limits{ m_sDownConfig.PrevBar->getResizeLimits() };
					float max_prev_bar_size{ m_sDownConfig.PrevBar->getTransform()->getTy() - client.Top + m_sDownConfig.PrevBar->getHeight() - m_pControl->getHeight() };
					float new_size{ ntl::Clamp<float>(m_sDownConfig.PrevBar->getTransform()->getTy() + m_sDownConfig.PrevBar->getHeight() - control_pos.Y - m_pControl->getHeight(), limits.X, ntl::Min<float>(max_prev_bar_size, limits.Y)) };
					if (new_size >= m_sDownConfig.PrevBarSize.Y)
					{
						m_sDownConfig.PrevBar->setSize(m_sDownConfig.PrevBarSize);
						m_sDownConfig.PrevBar = nullptr;
					}
					else
						m_sDownConfig.PrevBar->setHeight(new_size);
				}
				if ((prev_bar = FindPrevBar()) && prev_bar->isResizable()) // Resize previous resizable bar, can be ignored or modified due to constraints
				{
					RectF client{ m_sDownConfig.ParentBar->getClientRect() };
					PointF limits{ prev_bar->getResizeLimits() };
					float max_prev_bar_size{ prev_bar->getTransform()->getTy() - client.Top + prev_bar->getHeight() - m_pControl->getHeight() };
					prev_bar->setHeight(ntl::Clamp<float>(prev_bar->getTransform()->getTy() + prev_bar->getHeight() - control_pos.Y - m_pControl->getHeight(), limits.X, ntl::Min<float>(max_prev_bar_size, limits.Y)));
				}
				if ((next_control = FindNextControl())) // Move after next control
				{
					if (control_pos.Y < next_control->getTransform()->getTy())
						m_pControl->BringAfter(next_control);
				}
			}
		}

		void CCoolBarService::ProcessMoveOnBar(const PointF &pos)
		{
			// Move, change order, change size of nearest bars
			PointF pos_on_parent{ m_sDownConfig.ParentBar->FormToLocal(pos) };
			switch (m_sDownConfig.ParentBar->getOrientation())
			{
			case CCoolBar::Orientation::LeftToRight:
				ProcessMoveOnBarLeftToRight(pos_on_parent);
				break;
			case CCoolBar::Orientation::TopToBottom:
				ProcessMoveOnBarTopToBottom(pos_on_parent);
				break;
			case CCoolBar::Orientation::RightToLeft:
				ProcessMoveOnBarRightToLeft(pos_on_parent);
				break;
			case CCoolBar::Orientation::BottomToTop:
				ProcessMoveOnBarBottomToTop(pos_on_parent);
				break;
			}
			m_sDownConfig.PrevPosParent = pos_on_parent;
		}

		void CCoolBarService::ProcessMoveOnParentAlignLeft(const PointF &pos_on_parent)
		{
			if (ntl::IsLess<float>(pos_on_parent.X, m_sDownConfig.PrevPosParent.X))
			{
				// Move left
				IControl *prev{ FindPrevAlignedControl(Align::Left) };
				if (prev && pos_on_parent.X <= prev->getTransform()->getTx())
				{
					m_pControl->BringBefore(prev);
					m_pControl->Repaint(false);
				}
			}
			else if (ntl::IsGreater<float>(pos_on_parent.X, m_sDownConfig.PrevPosParent.X))
			{
				// Move right
				IControl *next{ FindNextAlignedControl(Align::Left) };
				if (next)
				{
					if (pos_on_parent.X >= next->getTransform()->getTx() + next->getWidth())
					{
						m_pControl->BringAfter(next);
						m_pControl->Repaint(false);
					}
				}
				else if (m_pControl->m_bAutoAlign && pos_on_parent.X > m_pControl->getTransform()->getTx() + ntl::Max<float>(m_pControl->getWidth(), m_pControl->m_fStickDistance))
				{
					m_pControl->setAlign(Align::None);
					if (m_sDownConfig.OriginalAlign == Align::None)
						m_pControl->setSize(m_sDownConfig.OriginalSize);
					m_pControl->setOrientation(m_sDownConfig.OriginalOrientation);
					PointF control_pos{ CalculateControlPosition(pos_on_parent) };
					m_pControl->getTransform()->Translate(control_pos.X, control_pos.Y, 0);
				}
			}
		}

		void CCoolBarService::ProcessMoveOnParentAlignTop(const PointF &pos_on_parent)
		{
			if (ntl::IsLess<float>(pos_on_parent.Y, m_sDownConfig.PrevPosParent.Y))
			{
				// Move top
				IControl *prev{ FindPrevAlignedControl(Align::Top) };
				if (prev && pos_on_parent.Y <= prev->getTransform()->getTy())
				{
					m_pControl->BringBefore(prev);
					m_pControl->Repaint(false);
				}
			}
			else if (ntl::IsGreater<float>(pos_on_parent.Y, m_sDownConfig.PrevPosParent.Y))
			{
				// Move bottom
				IControl *next{ FindNextAlignedControl(Align::Top) };
				if (next)
				{
					if (pos_on_parent.Y >= next->getTransform()->getTy() + next->getHeight())
					{
						m_pControl->BringAfter(next);
						m_pControl->Repaint(false);
					}
				}
				else if (m_pControl->m_bAutoAlign && pos_on_parent.Y > m_pControl->getTransform()->getTy() + ntl::Max<float>(m_pControl->getHeight(), m_pControl->m_fStickDistance))
				{
					m_pControl->setAlign(Align::None);
					if (m_sDownConfig.OriginalAlign == Align::None)
						m_pControl->setSize(m_sDownConfig.OriginalSize);
					m_pControl->setOrientation(m_sDownConfig.OriginalOrientation);
					PointF control_pos{ CalculateControlPosition(pos_on_parent) };
					m_pControl->getTransform()->Translate(control_pos.X, control_pos.Y, 0);
				}
			}
		}

		void CCoolBarService::ProcessMoveOnParentAlignRight(const PointF &pos_on_parent)
		{
			if (ntl::IsLess<float>(pos_on_parent.X, m_sDownConfig.PrevPosParent.X))
			{
				// Move left
				IControl *next{ FindNextAlignedControl(Align::Right) };
				if (next)
				{
					if (pos_on_parent.X <= next->getTransform()->getTx())
					{
						m_pControl->BringAfter(next);
						m_pControl->Repaint(false);
					}
				}
				else if (m_pControl->m_bAutoAlign && pos_on_parent.X < m_pControl->getTransform()->getTx() - m_pControl->m_fStickDistance)
				{
					m_pControl->setAlign(Align::None);
					if (m_sDownConfig.OriginalAlign == Align::None)
						m_pControl->setSize(m_sDownConfig.OriginalSize);
					m_pControl->setOrientation(m_sDownConfig.OriginalOrientation);
					PointF control_pos{ CalculateControlPosition(pos_on_parent) };
					m_pControl->getTransform()->Translate(control_pos.X, control_pos.Y, 0);
				}
			}
			else if (ntl::IsGreater<float>(pos_on_parent.X, m_sDownConfig.PrevPosParent.X))
			{
				// Move right
				IControl *prev{ FindPrevAlignedControl(Align::Right) };
				if (prev && pos_on_parent.X >= prev->getTransform()->getTx() + prev->getWidth())
				{
					m_pControl->BringBefore(prev);
					m_pControl->Repaint(false);
				}
			}
		}

		void CCoolBarService::ProcessMoveOnParentAlignBottom(const PointF &pos_on_parent)
		{
			if (ntl::IsLess<float>(pos_on_parent.Y, m_sDownConfig.PrevPosParent.Y))
			{
				// Move top
				IControl *next{ FindNextAlignedControl(Align::Bottom) };
				if (next)
				{
					if (pos_on_parent.Y <= next->getTransform()->getTy())
					{
						m_pControl->BringAfter(next);
						m_pControl->Repaint(false);
					}
				}
				else if (m_pControl->m_bAutoAlign && pos_on_parent.Y < m_pControl->getTransform()->getTy() - m_pControl->m_fStickDistance)
				{
					m_pControl->setAlign(Align::None);
					if (m_sDownConfig.OriginalAlign == Align::None)
						m_pControl->setSize(m_sDownConfig.OriginalSize);
					m_pControl->setOrientation(m_sDownConfig.OriginalOrientation);
					PointF control_pos{ CalculateControlPosition(pos_on_parent) };
					m_pControl->getTransform()->Translate(control_pos.X, control_pos.Y, 0);
				}
			}
			else if (ntl::IsGreater<float>(pos_on_parent.Y, m_sDownConfig.PrevPosParent.Y))
			{
				// Move bottom
				IControl *prev{ FindPrevAlignedControl(Align::Bottom) };
				if (prev && pos_on_parent.Y > prev->getTransform()->getTy() + prev->getHeight())
				{
					m_pControl->BringBefore(prev);
					m_pControl->Repaint(false);
				}
			}
		}

		void CCoolBarService::ProcessMoveOnParentAlignNone(const PointF &pos_on_parent)
		{
			IControl *last_left{ FindLastAlignedControl(Align::Left) };
			IControl *last_top{ FindLastAlignedControl(Align::Top) };
			IControl *last_right{ FindLastAlignedControl(Align::Right) };
			IControl *last_bottom{ FindLastAlignedControl(Align::Bottom) };
			RectF client{ // Client area of a parent without area occupied by aligned controls
				last_left ? (last_left->getTransform()->getTx() + last_left->getWidth()) : 0,
				last_top ? (last_top->getTransform()->getTy() + last_top->getHeight()) : 0,
				last_right ? last_right->getTransform()->getTx() : (float)m_pControl->getForm()->getClientWidth(),
				last_bottom ? last_bottom->getTransform()->getTy() : (float)m_pControl->getForm()->getClientHeight()
			};
			PointF control_pos{ CalculateControlPosition(pos_on_parent) }, control_size{ m_pControl->getSize() };
			RectF d{ control_pos.X - client.Left, control_pos.Y - client.Top, client.Right - control_pos.X - control_size.X, client.Bottom - control_pos.Y - control_size.Y };
			if (m_pControl->m_bAutoAlign)
			{
				if (d.Left <= d.Top && d.Left <= d.Right && d.Left <= d.Bottom)
				{
					// Left is the nearest
					if (pos_on_parent.X <= client.Left)
					{
						if (last_left)
							m_pControl->BringAfter(last_left);
						switch (m_pControl->m_eOrientation)
						{
						case ICoolBar::Orientation::LeftToRight:
							m_pControl->setOrientation(ICoolBar::Orientation::TopToBottom);
							m_pControl->setWidth(m_pControl->getHeight());
							break;
						case ICoolBar::Orientation::RightToLeft:
							m_pControl->setOrientation(ICoolBar::Orientation::BottomToTop);
							m_pControl->setWidth(m_pControl->getHeight());
							break;
						default:
							break;
						}
						m_pControl->setAlign(Align::Left);
					}
				}
				else if (d.Top <= d.Right && d.Top <= d.Bottom)
				{
					// Top is the nearest
					if (pos_on_parent.Y <= client.Top)
					{
						if (last_top)
							m_pControl->BringAfter(last_top);
						switch (m_pControl->m_eOrientation)
						{
						case ICoolBar::Orientation::TopToBottom:
							m_pControl->setOrientation(ICoolBar::Orientation::LeftToRight);
							m_pControl->setHeight(m_pControl->getWidth());
							break;
						case ICoolBar::Orientation::BottomToTop:
							m_pControl->setOrientation(ICoolBar::Orientation::RightToLeft);
							m_pControl->setHeight(m_pControl->getWidth());
							break;
						default:
							break;
						}
						m_pControl->setAlign(Align::Top);
					}
				}
				else if (d.Right <= d.Bottom)
				{
					// Right is the nearest
					if (pos_on_parent.X >= client.Right)
					{
						if (last_right)
							m_pControl->BringAfter(last_right);
						switch (m_pControl->m_eOrientation)
						{
						case ICoolBar::Orientation::LeftToRight:
							m_pControl->setOrientation(ICoolBar::Orientation::TopToBottom);
							m_pControl->setWidth(m_pControl->getHeight());
							break;
						case ICoolBar::Orientation::RightToLeft:
							m_pControl->setOrientation(ICoolBar::Orientation::BottomToTop);
							m_pControl->setWidth(m_pControl->getHeight());
							break;
						default:
							break;
						}
						m_pControl->setAlign(Align::Right);
					}
				}
				else
				{
					// Bottom is the nearest
					if (pos_on_parent.Y >= client.Bottom)
					{
						if (last_bottom)
							m_pControl->BringAfter(last_bottom);
						switch (m_pControl->m_eOrientation)
						{
						case ICoolBar::Orientation::TopToBottom:
							m_pControl->setOrientation(ICoolBar::Orientation::LeftToRight);
							m_pControl->setHeight(m_pControl->getWidth());
							break;
						case ICoolBar::Orientation::BottomToTop:
							m_pControl->setOrientation(ICoolBar::Orientation::RightToLeft);
							m_pControl->setHeight(m_pControl->getWidth());
							break;
						default:
							break;
						}
						m_pControl->setAlign(Align::Bottom);
					}
				}
			}
			if (m_pControl->getAlign() == Align::None)
			{
				// Just move, probable with stick
				if (ntl::Abs<float>(d.Left) < m_pControl->m_fStickDistance)
					control_pos.X = client.Left;
				else if (ntl::Abs<float>(d.Right) < m_pControl->m_fStickDistance)
					control_pos.X = client.Right - m_pControl->getWidth();
				if (ntl::Abs<float>(d.Top) < m_pControl->m_fStickDistance)
					control_pos.Y = client.Top;
				else if (ntl::Abs<float>(d.Bottom) < m_pControl->m_fStickDistance)
					control_pos.Y = client.Bottom - m_pControl->getHeight();
				m_pControl->getTransform()->Translate(control_pos.X, control_pos.Y, 0);
			}
		}

		void CCoolBarService::ProcessMoveOnParent(const PointF &pos)
		{
			// Move, change order, change align, change orientation
			PointF pos_on_parent{ m_sDownConfig.Parent? m_sDownConfig.Parent->FormToLocal(pos) : pos };
			switch (m_pControl->getAlign())
			{
			case Align::Left:
				ProcessMoveOnParentAlignLeft(pos_on_parent);
				break;
			case Align::Top:
				ProcessMoveOnParentAlignTop(pos_on_parent);
				break;
			case Align::Right:
				ProcessMoveOnParentAlignRight(pos_on_parent);
				break;
			case Align::Bottom:
				ProcessMoveOnParentAlignBottom(pos_on_parent);
				break;
			case Align::None:
				ProcessMoveOnParentAlignNone(pos_on_parent);
				break;
			default:
				break;
			}
			m_sDownConfig.PrevPosParent = pos_on_parent;
		}

		void CCoolBarService::CancelDown(const bool cancel_capture, const bool cancel_changes)
		{
			switch (m_pControl->m_eDownElement)
			{
			case CCoolBar::Element::Mover:
				m_pControl->m_eDownElement = CCoolBar::Element::None;
				if (cancel_changes)
				{
					m_pControl->getTransform()->Transform(
						m_sDownConfig.OriginalTransform.Tx, m_sDownConfig.OriginalTransform.Ty, m_sDownConfig.OriginalTransform.Tz,
						m_sDownConfig.OriginalTransform.Sz, m_sDownConfig.OriginalTransform.Sy, m_sDownConfig.OriginalTransform.Sz,
						m_sDownConfig.OriginalTransform.Rx, m_sDownConfig.OriginalTransform.Ry, m_sDownConfig.OriginalTransform.Rz);
					m_pControl->setAlign(m_sDownConfig.OriginalAlign);
					m_pControl->BringBefore(m_sDownConfig.OriginalIndex);
					if (m_pControl->getAlign() == Align::None)
						m_pControl->setSize(m_sDownConfig.OriginalSize);
					m_pControl->setOrientation(m_sDownConfig.OriginalOrientation);
				}
				break;
			case CCoolBar::Element::ExtraListScroll:
				m_pControl->m_eDownElement = CCoolBar::Element::None;
				m_pControl->m_pExtraListScroll->NotifyOnMouseDownCancel();
				break;
			case CCoolBar::Element::ToggleListScroll:
				m_pControl->m_eDownElement = CCoolBar::Element::None;
				m_pControl->m_pToggleListScroll->NotifyOnMouseDownCancel();
				break;
			default:
				m_pControl->m_eDownElement = CCoolBar::Element::None;
				break;
			}
			if (cancel_capture && m_pControl->isCaptureMouse())
				m_pControl->getForm()->ReleaseCaptureMouse();
		}
	#pragma endregion

	#pragma region State change notifications
		void CCoolBarService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
			if (m_pControl->m_pCanvasExtraList)
			{
				m_pControl->m_pCanvasExtraList->Release();
				m_pControl->m_pCanvasExtraList = nullptr;
			}
			if (m_pControl->m_pMaskExtraList)
			{
				m_pControl->m_pMaskExtraList->setValid(false);
				m_pControl->m_pMaskExtraList = nullptr;
			}
			if (m_pControl->m_pCanvasToggleList)
			{
				m_pControl->m_pCanvasToggleList->Release();
				m_pControl->m_pCanvasToggleList = nullptr;
			}
			if (m_pControl->m_pExtraListScroll)
				m_pControl->m_pExtraListScroll->NotifyOnFreeResources();
			if (m_pControl->m_pToggleListScroll)
				m_pControl->m_pToggleListScroll->NotifyOnFreeResources();
		}
	#pragma endregion

	#pragma region Application notifications
		void CCoolBarService::NotifyOnTranslateChange()
		{
			if (m_pControl->m_bExtraListVisible && m_pControl->m_pVisibilityManager)
				m_pControl->PostExtraListChange();
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CCoolBarService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				m_pControl->PostClientAreaChange();
			}
		}

		void CCoolBarService::NotifyOnParentFontChange()
		{
			m_pControl->PostExtraListChange();
		}
	#pragma endregion

	#pragma region Notifications from child controls
		void CCoolBarService::NotifyOnChildTransform(IControl *control)
		{
			if (!m_pControl->m_bAligning)
				m_pControl->PostClientAreaChange();
		}

		void CCoolBarService::NotifyOnChildResize(IControl *control)
		{
			if (!m_pControl->m_bAligning)
				m_pControl->PostClientAreaChange();
		}

		void CCoolBarService::NotifyOnChildShow(IControl *control)
		{
			if (!m_pControl->m_bAligning)
				m_pControl->PostClientAreaChange();
		}

		void CCoolBarService::NotifyOnChildHide(IControl *control)
		{
			if (!m_pControl->m_bAligning)
				m_pControl->PostClientAreaChange();
		}

		void CCoolBarService::NotifyOnChildAttach(IControl *control)
		{
			ICoolBar *bar{ cast<ICoolBar*>(control) };
			if (bar && bar->isResizable())
			{
				PointF limits{ bar->getResizeLimits() };
				switch (bar->getOrientation())
				{
				case ICoolBar::Orientation::LeftToRight:
				case ICoolBar::Orientation::RightToLeft:
					bar->setSize(PointF{ ntl::Clamp<float>(bar->getWidth(), limits.X, limits.Y), bar->getHeight() });
					break;
				case ICoolBar::Orientation::TopToBottom:
				case ICoolBar::Orientation::BottomToTop:
					bar->setSize(PointF{ bar->getWidth(), ntl::Clamp<float>(bar->getHeight(), limits.X, limits.Y) });
					break;
				}
			}
			m_pControl->PostClientAreaChange();
		}

		void CCoolBarService::NotifyOnChildDetach(IControl *control)
		{
			if (!m_pControl->m_bAligning)
				m_pControl->PostClientAreaChange();
		}

		void CCoolBarService::NotifyOnChildBeforeTransform(IControl *control, bool &allowed)
		{
			if (!m_pControl->m_bAligning)
				allowed = false;
		}

		void CCoolBarService::NotifyOnChildBeforeShow(IControl *control, bool &allowed)
		{
			if (!m_pControl->m_bAligning)
				allowed = false;
		}

		void CCoolBarService::NotifyOnChildBeforeHide(IControl *control, bool &allowed)
		{
			if (!m_pControl->m_bAligning)
				allowed = false;
		}
	#pragma endregion

	#pragma region State change notifications
		void CCoolBarService::NotifyOnEnable()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CCoolBarService::NotifyOnDisable()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CCoolBarService::NotifyOnResize()
		{
			if (!m_pControl->m_bAligning)
				m_pControl->PostClientAreaChange();
		}

		void CCoolBarService::NotifyOnTransformControls() // Prevents controls transformation change
		{
			if (!m_bIgnoreTransformControls)
			{
				m_bIgnoreTransformControls = true;
				m_pControl->getTransformControls()->Transform(0, 0, 0, 1, 1, 1, 0, 0, 0);
				m_bIgnoreTransformControls = false;
			}
		}

		void CCoolBarService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				m_pControl->PostClientAreaChange();
			}
		}

		void CCoolBarService::NotifyOnFontChange()
		{
			m_pControl->PostExtraListChange();
		}

		void CCoolBarService::NotifyOnKillCaptureMouse()
		{
			CancelDown(false, false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CCoolBarService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass)
			{
				if (ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
				{
					IRenderer *renderer{ m_pControl->getForm()->getRenderer() };
					Mat4f matrix{ m_pControl->getTransformMatrix() };
					m_pControl->Render(renderer, matrix);
					for (int i = 0; i <= m_pControl->m_iLastVisibleControl && i < m_pControl->getControlCount(); i++)
					{
						if (m_pControl->getControl(i)->isVisible(false))
							CNotifier::Render(m_pControl->getControl(i), m, nullptr);
					}
					if (m_pControl->m_bExtraListVisible)
					{
						bool mask{ false };
						m_pControl->RenderExtraList(renderer, matrix);
						if (m_pControl->m_bExtraListScrollVisible)
						{
							m_pControl->RenderExtraListMask(renderer);
							if (m_pControl->m_pMaskExtraList)
							{
								renderer->PushMask(m_pControl->m_pMaskExtraList, matrix * ntl::Mat4Translate<float>(m_pControl->m_sExtraListClientRect.Left, m_pControl->m_sExtraListClientRect.Top, 0));
								mask = true;
							}
						}
						for (int i = m_pControl->m_iLastVisibleControl + 1; i < m_pControl->getControlCount(); i++)
						{
							if (m_pControl->getControl(i)->isVisible(false))
								CNotifier::Render(m_pControl->getControl(i), m, nullptr);
						}
						if (mask)
							m_pControl->getForm()->getRenderer()->PopMask();
					}
					if (m_pControl->m_bToggleListVisible)
						m_pControl->RenderToggleList(renderer, matrix);
				}
				draw_children = false;
			}
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CCoolBarService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m.Key == Key::Escape)
			{
				bool ctrl, alt, shift;
				Application->Keyboard->getControlKeys(ctrl, alt, shift);
				if (!ctrl && !alt && !shift)
				{
					switch (m_pControl->m_eDownElement)
					{
					case CCoolBar::Element::Mover:
						CancelDown(true, true);
						break;
					case CCoolBar::Element::None:
						if (m_pControl->m_bToggleListVisible)
						{
							m_pControl->CloseToggleList();
							m_pControl->UpdateHoveredElement();
						}
						else if (m_pControl->m_bExtraListVisible)
						{
							m_pControl->CloseExtraList();
							m_pControl->UpdateHoveredElement();
						}
					default:
						break;
					}
				}
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CCoolBarService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pControl->isEnabled(true) && m_pControl->UpdateHoveredElement(m_pControl->FormToLocal(m.Position)))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_bExtraListVisible && m_pControl->m_pCanvasExtraList)
					m_pControl->m_pCanvasExtraList->setValid(false);
				if (m_pControl->m_bToggleListVisible && m_pControl->m_pCanvasToggleList)
					m_pControl->m_pCanvasToggleList->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CCoolBarService::NotifyOnMouseLeave()
		{
			if (m_pControl->isEnabled(true) && m_pControl->UpdateHoveredElement())
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				if (m_pControl->m_bExtraListVisible && m_pControl->m_pCanvasExtraList)
					m_pControl->m_pCanvasExtraList->setValid(false);
				if (m_pControl->m_bToggleListVisible && m_pControl->m_pCanvasToggleList)
					m_pControl->m_pCanvasToggleList->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CCoolBarService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true))
			{
				switch (m_pControl->m_eDownElement)
				{
				case CCoolBar::Element::ExtraListScroll:
					if (m_pControl->m_pExtraListScroll->NotifyOnMouseMove(m_pControl->FormToLocal(m.Position) - m_pControl->m_pExtraListScroll->getPosition(), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					{
						if (m_pControl->m_pCanvasExtraList)
							m_pControl->m_pCanvasExtraList->setValid(false);
						m_pControl->Repaint(false);
					}
					break;
				case CCoolBar::Element::ToggleListScroll:
					if (m_pControl->m_pToggleListScroll->NotifyOnMouseMove(m_pControl->FormToLocal(m.Position) - m_pControl->m_pToggleListScroll->getPosition(), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					{
						if (m_pControl->m_pCanvasToggleList)
							m_pControl->m_pCanvasToggleList->setValid(false);
						m_pControl->Repaint(false);
					}
					break;
				case CCoolBar::Element::Mover:
					if (m_sDownConfig.ParentBar)
						ProcessMoveOnBar(m.Position);
					else
						ProcessMoveOnParent(m.Position);
					break;
				default:
					if (m_pControl->UpdateHoveredElement(m_pControl->FormToLocal(m.Position)))
					{
						if (m_pControl->m_pCanvas)
							m_pControl->m_pCanvas->setValid(false);
						if (m_pControl->m_bExtraListVisible && m_pControl->m_pCanvasExtraList)
							m_pControl->m_pCanvasExtraList->setValid(false);
						if (m_pControl->m_bToggleListVisible && m_pControl->m_pCanvasToggleList)
							m_pControl->m_pCanvasToggleList->setValid(false);
						m_pControl->Repaint(false);
					}
					else
					{
						switch (m_pControl->m_eHoveredElement)
						{
						case CCoolBar::Element::ExtraListScroll:
							if (m_pControl->m_pExtraListScroll->NotifyOnMouseMove(m_pControl->FormToLocal(m.Position) - m_pControl->m_pExtraListScroll->getPosition(), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
							{
								if (m_pControl->m_bExtraListVisible && m_pControl->m_pCanvasExtraList)
									m_pControl->m_pCanvasExtraList->setValid(false);
								m_pControl->Repaint(false);
							}
							break;
						case CCoolBar::Element::ToggleListScroll:
							if (m_pControl->m_pToggleListScroll->NotifyOnMouseMove(m_pControl->FormToLocal(m.Position) - m_pControl->m_pToggleListScroll->getPosition(), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
							{
								if (m_pControl->m_bToggleListVisible && m_pControl->m_pCanvasToggleList)
									m_pControl->m_pCanvasToggleList->setValid(false);
								m_pControl->Repaint(false);
							}
							break;
						default:
							break;
						}
					}
					break;
				}
			}
		}

		void CCoolBarService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true) && m_pControl->m_eDownElement == CCoolBar::Element::None && !m.Middle && !m.Right && !m.Ctrl && !m.Alt && !m.Shift)
			{
				switch (m_pControl->m_eHoveredElement)
				{
				case CCoolBar::Element::Mover:
					if (!m_pControl->m_bLocked)
					{
						m_sDownConfig.Parent = m_pControl->getParent();
						m_sDownConfig.ParentBar = cast<ICoolBar*>(m_sDownConfig.Parent);
						m_sDownConfig.DownShiftControl = m_pControl->FormToLocal(m.Position);
						m_sDownConfig.PrevPosParent = m_sDownConfig.Parent ? m_sDownConfig.Parent->FormToLocal(m.Position) : m.Position;
						m_sDownConfig.PrevBar = nullptr;
						m_sDownConfig.OriginalAlign = m_pControl->getAlign();
						m_sDownConfig.OriginalSize = m_pControl->getSize();
						m_sDownConfig.OriginalTransform = m_pControl->getTransform()->getTransform();
						m_sDownConfig.OriginalIndex = m_sDownConfig.Parent ? m_sDownConfig.Parent->getControlIndex(m_pControl) : m_pControl->getForm()->getControlIndex(m_pControl);
						m_sDownConfig.OriginalOrientation = m_pControl->getOrientation();
						switch (m_pControl->m_eOrientation)
						{
						case ICoolBar::Orientation::TopToBottom:
							m_sDownConfig.DownShiftControl = PointF{ m_sDownConfig.DownShiftControl.Y, m_sDownConfig.OriginalSize.X - m_sDownConfig.DownShiftControl.X };
							break;
						case ICoolBar::Orientation::RightToLeft:
							m_sDownConfig.DownShiftControl.X = m_sDownConfig.OriginalSize.X - m_sDownConfig.DownShiftControl.X;
							break;
						case ICoolBar::Orientation::BottomToTop:
							m_sDownConfig.DownShiftControl = PointF{ m_sDownConfig.OriginalSize.Y - m_sDownConfig.DownShiftControl.Y, m_sDownConfig.DownShiftControl.X };
							break;
						default:
							break;
						}
						m_pControl->CloseToggleList();
						m_pControl->CloseExtraList();
						m_pControl->m_eDownElement = CCoolBar::Element::Mover;
						m_pControl->getForm()->CaptureMouse(m_pControl, true);
						if (m_pControl->m_pCanvas)
							m_pControl->m_pCanvas->setValid(false);
						m_pControl->Repaint(false);
					}
					break;
				case CCoolBar::Element::Extra:
					if (m_pControl->m_pVisibilityManager || m_pControl->m_bHasExtraControls)
					{
						if (m_pControl->m_bExtraListVisible)
						{
							m_pControl->CloseToggleList();
							m_pControl->CloseExtraList();
						}
						else
							m_pControl->OpenExtraList();
					}
					break;
				case CCoolBar::Element::ExtraListScroll:
					m_pControl->m_eDownElement = CCoolBar::Element::ExtraListScroll;
					m_pControl->getForm()->CaptureMouse(m_pControl, true);
					m_pControl->m_pExtraListScroll->NotifyOnMouseLeftDown(m_pControl->FormToLocal(m.Position) - m_pControl->m_pExtraListScroll->getPosition(), false, false, false, false, false);
					break;
				case CCoolBar::Element::ExtraListButton:
					m_pControl->m_bToggleListVisible ? m_pControl->CloseToggleList() : m_pControl->OpenToggleList();
					break;
				case CCoolBar::Element::ToggleListScroll:
					m_pControl->m_eDownElement = CCoolBar::Element::ToggleListScroll;
					m_pControl->getForm()->CaptureMouse(m_pControl, true);
					m_pControl->m_pToggleListScroll->NotifyOnMouseLeftDown(m_pControl->FormToLocal(m.Position) - m_pControl->m_pToggleListScroll->getPosition(), false, false, false, false, false);
					break;
				case CCoolBar::Element::ToggleListElement:
					if (m_pControl->m_pVisibilityManager->isTogglable(m_pControl->getControl(m_pControl->m_iHoveredElementIndex), m_pControl->m_iHoveredElementIndex) &&
						m_pControl->m_pVisibilityManager->setVisible(
							m_pControl->getControl(m_pControl->m_iHoveredElementIndex),
							m_pControl->m_iHoveredElementIndex,
							!m_pControl->m_pVisibilityManager->isVisible(m_pControl->getControl(m_pControl->m_iHoveredElementIndex), m_pControl->m_iHoveredElementIndex)))
					{
						// Differs from PostClientAreaChange() by missing UpdateToggleList() call as the toggle list should not be updated
						m_pControl->AlignControls(false);
						m_pControl->UpdateExtraList();
						m_pControl->AlignExtraControls();
						if (m_pControl->m_pCanvas)
							m_pControl->m_pCanvas->setValid(false);
						if (m_pControl->m_pCanvasExtraList)
							m_pControl->m_pCanvasExtraList->setValid(false);
						if (m_pControl->m_pMaskExtraList)
							m_pControl->m_pMaskExtraList->setValid(false);
						if (m_pControl->m_pCanvasToggleList)
							m_pControl->m_pCanvasToggleList->setValid(false);
						m_pControl->UpdateHoveredElement();
						m_pControl->Repaint(false);
					}
					break;
				default:
					if (m_pControl->m_bExtraListVisible)
					{
						m_pControl->CloseToggleList();
						m_pControl->CloseExtraList();
						if (m_pControl->m_pCanvas)
							m_pControl->m_pCanvas->setValid(false);
					}
					break;
				}
			}
			else
				CancelDown(true, true);
		}

		void CCoolBarService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			CancelDown(true, false);
		}

		void CCoolBarService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CCoolBarService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CCoolBarService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CCoolBarService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CCoolBarService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CCoolBarService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CCoolBarService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			CancelDown(true, true);
		}

		void CCoolBarService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			if (m_pControl->isEnabled(true))
			{
				switch (m_pControl->m_eHoveredElement)
				{
				case CCoolBar::Element::ExtraList:
				case CCoolBar::Element::ExtraListScroll:
				case CCoolBar::Element::ExtraListButton:
					if (m_pControl->m_bExtraListScrollVisible)
					{
						processed = true;
						if (m_pControl->m_pExtraListScroll->NotifyOnMouseVerticalWheel(m_pControl->FormToLocal(m.Position) - m_pControl->m_pExtraListScroll->getPosition(), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
						{
							m_pControl->AlignExtraControls();
							if (m_pControl->m_pCanvasExtraList)
								m_pControl->m_pCanvasExtraList->setValid(false);
							m_pControl->Repaint(false);
						}
					}
					break;
				case CCoolBar::Element::ToggleList:
				case CCoolBar::Element::ToggleListScroll:
				case CCoolBar::Element::ToggleListElement:
					if (m_pControl->m_bToggleListScrollVisible)
					{
						processed = true;
						if (m_pControl->m_pToggleListScroll->NotifyOnMouseVerticalWheel(m_pControl->FormToLocal(m.Position) - m_pControl->m_pToggleListScroll->getPosition(), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
						{
							if (m_pControl->m_pCanvasToggleList)
								m_pControl->m_pCanvasToggleList->setValid(false);
							m_pControl->Repaint(false);
						}
					}
					break;
				default:
					break;
				}
			}
		}
	#pragma endregion

	#pragma region DialogBox notifications
		void CCoolBarService::NotifyOnKillActive()
		{
			CancelDown(true, false);
			m_pControl->CloseToggleList();
			m_pControl->CloseExtraList();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
		}
	#pragma endregion
	}
}
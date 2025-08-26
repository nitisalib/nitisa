// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
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
		CTabSheet::CTabSheet() :
			CControl(L"TabSheet", false, true, true, false, false, false),
			m_iIconIndex{ -1 },
			m_bCaptionChanged{ false }
		{
			setService(new CTabSheetService(this), true);
			setTransform(new CTabSheetTransform());
			CControl::setAlign(Align::Client);
		}

		CTabSheet::CTabSheet(IPageControl *parent) :CTabSheet()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		IControl *CTabSheet::getControl(const int index)
		{
			return CControl::getControl(index);
		}

		IControl *CTabSheet::getControl(const String &name)
		{
			return CControl::getControl(name);
		}

		IControl *CTabSheet::getControl(const PointF &position)
		{
			IControl *result{ CControl::getControl(position) };
			if (result && result != this)
			{
				Vec4f v{ ntl::Inversed<float>(getTransformMatrix()) * Vec4f{ position.X, position.Y, 0, 1 } };
				RectF client{ getClientRect() };
				if (v.X < 0 || v.X >= getWidth() || v.Y < 0 || v.Y >= getHeight())
					result = nullptr;
				else if (v.X < client.Left || v.X >= client.Right || v.Y < client.Top || v.Y >= client.Bottom)
					result = this;
			}
			return result;
		}

		IPageControl *CTabSheet::getPageControl()
		{
			return cast<IPageControl*>(getParent());
		}

		int CTabSheet::getIndex()
		{
			IPageControl *parent{ cast<IPageControl*>(getParent()) };
			if (parent)
				for (int i = 0; i < parent->getTabSheetCount(); i++)
					if (parent->getTabSheet(i) == this)
						return i;
			return -1;
		}

		bool CTabSheet::isActive()
		{
			IPageControl *parent{ cast<IPageControl*>(getParent()) };
			return parent && parent->getActiveTabSheet() == this;
		}

		bool CTabSheet::isAcceptControl(IControl *control)
		{
			return cast<IPageControl*>(control) ? true : false;
		}

		String CTabSheet::getCaption()
		{
			return m_sCaption;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CTabSheet::setParent(IControl *value)
		{
			if (!cast<IPageControl*>(value))
				return false;
			return CControl::setParent(value);
		}

		bool CTabSheet::setAlign(const Align value)
		{
			return false;
		}

		bool CTabSheet::setConstraints(const RectF &value)
		{
			return false;
		}

		bool CTabSheet::setSize(const PointF &value)
		{
			return false;
		}

		bool CTabSheet::setZIndex(const int value)
		{
			return false;
		}

		bool CTabSheet::setCaption(const String &value)
		{
			if (value != m_sCaption)
			{
				m_sCaption = value;
				m_bCaptionChanged = true;
				if (getParent())
				{
					CLockRepaint lock{ this };
					IPageControlService *service{ cast<IPageControlService*>(getParent()->QueryService()) };
					if (service)
						service->NotifyOnTabSheetChanged(this);
					getParent()->Repaint(false);
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		int CTabSheet::getIconIndex() const
		{
			return m_iIconIndex;
		}
	#pragma endregion

	#pragma region Setters
		bool CTabSheet::setIconIndex(const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_iIconIndex)
			{
				m_iIconIndex = value;
				if (getParent())
				{
					CLockRepaint lock{ this };
					IPageControlService *service{ cast<IPageControlService*>(getParent()->QueryService()) };
					if (service)
						service->NotifyOnTabSheetChanged(this);
					getParent()->Repaint(false);
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Change position methods
		bool CTabSheet::BringToFront()
		{
			CLockRepaint lock{ this };
			if (CControl::BringToFront())
			{
				IPageControlService *service{ cast<IPageControlService*>(getParent()->QueryService()) };
				if (service)
					service->NotifyOnTabSheetChanged(this);
				return true;
			}
			return false;
		}

		bool CTabSheet::BringUp()
		{
			CLockRepaint lock{ this };
			if (CControl::BringUp())
			{
				IPageControlService *service{ cast<IPageControlService*>(getParent()->QueryService()) };
				if (service)
					service->NotifyOnTabSheetChanged(this);
				return true;
			}
			return false;
		}

		bool CTabSheet::BringDown()
		{
			CLockRepaint lock{ this };
			if (CControl::BringDown())
			{
				IPageControlService *service{ cast<IPageControlService*>(getParent()->QueryService()) };
				if (service)
					service->NotifyOnTabSheetChanged(this);
				return true;
			}
			return false;
		}

		bool CTabSheet::BringBefore(IControl *control)
		{
			CLockRepaint lock{ this };
			if (CControl::BringBefore(control))
			{
				IPageControlService *service{ cast<IPageControlService*>(getParent()->QueryService()) };
				if (service)
					service->NotifyOnTabSheetChanged(this);
				return true;
			}
			return false;
		}

		bool CTabSheet::BringBefore(const int index)
		{
			CLockRepaint lock{ this };
			if (CControl::BringBefore(index))
			{
				IPageControlService *service{ cast<IPageControlService*>(getParent()->QueryService()) };
				if (service)
					service->NotifyOnTabSheetChanged(this);
				return true;
			}
			return false;
		}

		bool CTabSheet::BringAfter(IControl *control)
		{
			CLockRepaint lock{ this };
			if (CControl::BringAfter(control))
			{
				IPageControlService *service{ cast<IPageControlService*>(getParent()->QueryService()) };
				if (service)
					service->NotifyOnTabSheetChanged(this);
				return true;
			}
			return false;
		}

		bool CTabSheet::BringAfter(const int index)
		{
			CLockRepaint lock{ this };
			if (CControl::BringAfter(index))
			{
				IPageControlService *service{ cast<IPageControlService*>(getParent()->QueryService()) };
				if (service)
					service->NotifyOnTabSheetChanged(this);
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}
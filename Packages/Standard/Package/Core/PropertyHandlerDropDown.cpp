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
		CPropertyHandlerDropDown::CPropertyHandlerDropDown(IPackage *package, const String &name) :
			CBuiltInDropDown(false, Compare, GetItemText, Search),
			m_pControl{ nullptr },
			m_pPackage{ package },
			m_cListener{ this },
			m_pListener{ nullptr }
		{
			m_sName = name;
			setListBorderColor(BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } });
			setListMaxHeight(180);
			CBuiltInDropDown::setListener(&m_cListener);
		}

		IControl *CPropertyHandlerDropDown::getControl()
		{
			return m_pControl;
		}

		IPackage *CPropertyHandlerDropDown::getPackage()
		{
			return m_pPackage;
		}

		IBuiltInControlListener *CPropertyHandlerDropDown::getListener()
		{
			return m_pListener;
		}

		bool CPropertyHandlerDropDown::setControl(IControl *value)
		{
			if (value != m_pControl)
			{
				m_pControl = value;
				return true;
			}
			return false;
		}

		void CPropertyHandlerDropDown::setListener(IBuiltInControlListener *value)
		{
			m_pListener = value;
		}

		bool CPropertyHandlerDropDown::Compare(IListItem *a, IListItem *b)
		{
			return cast<IListItemLabel*>(a)->getCaption() < cast<IListItemLabel*>(b)->getCaption();
		}

		String CPropertyHandlerDropDown::GetItemText(IListItem *item)
		{
			return cast<IListItemLabel*>(item)->getCaption();
		}

		int CPropertyHandlerDropDown::Search(IBuiltInDropDown *dropdown, const String &search)
		{
			for (int i = 0; i < dropdown->getItemCount(); i++)
				if (cast<IListItemLabel*>(dropdown->getItem(i))->getCaption().find(search) == 0)
					return i;
			return -1;
		}

		bool CPropertyHandlerDropDown::InsertItem(IListItem *item, const int before)
		{
			if (!cast<IListItemLabel*>(item))
				return false;
			return CBuiltInDropDown::InsertItem(item, before);
		}

		bool CPropertyHandlerDropDown::Add(const String &caption)
		{
			if (!caption.empty())
			{
				CListItemLabel *l{ new CListItemLabel(caption) };
				if (AddItem(l))
					return true;
				l->Release();
			}
			return false;
		}

		bool CPropertyHandlerDropDown::Open()
		{
			if (!isOpened())
				setOpenDirection((CBuiltInDropDown::getTop() > getControl()->getHeight() - 200) ? OpenDirection::Up : OpenDirection::Down);
			return CBuiltInDropDown::Open();
		}
	}
}
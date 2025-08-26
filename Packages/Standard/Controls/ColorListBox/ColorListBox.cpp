// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
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
		CColorListBox::CColorListBox() :
			CCustomListBox(L"ColorListBox", true, true, true),
			m_bHasStandardColors{ true },
			m_bHasExtendedColors{ true },
			m_bHasNoneColor{ true },
			m_bIsCustomItems{ false }
		{
			CCustomListBox::setMultiselect(false);
			BuildList();
		}

		CColorListBox::CColorListBox(IForm *parent) : CColorListBox()
		{
			setForm(parent);
		}

		CColorListBox::CColorListBox(IControl *parent) : CColorListBox()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Helpers
		CCustomListBox::FCompare CColorListBox::getCompareItems()
		{
			return [](IListItem *a, IListItem *b) {return cast<IListItemColor*>(a)->getCaption() < cast<IListItemColor*>(b)->getCaption(); };
		}

		int CColorListBox::Search(const String &search)
		{
			for (int i = 0; i < getItemCount(); i++)
				if (getItem(i)->isEnabled() && ToLower(getItem(i)->getCaption()).find(search, 0) == 0)
					return i;
			return -1;
		}

		void CColorListBox::BuildList()
		{
			LockUpdate();
			Clear();
			CColorListBox *self{ this };
			auto add = [self](const CColor &color) {self->Add(color); };
			if (m_bHasStandardColors)
				CColors::EnumStandardColors(add);
			if (m_bHasNoneColor)
				Add(CColors::None);
			if (m_bHasExtendedColors)
				CColors::EnumExtendedColors(add);
			UnlockUpdate();
			m_bIsCustomItems = false;
		}
	#pragma endregion

	#pragma region Items
		bool CColorListBox::isAcceptItem(IListItem *item)
		{
			return cast<IListItemColor*>(item) != nullptr;
		}

		IListItemColor *CColorListBox::getItem(const int index)
		{
			return cast<IListItemColor*>(CCustomListBox::getItem(index));
		}

		int CColorListBox::getActiveIndex()
		{
			return CCustomListBox::getActiveIndex();
		}

		bool CColorListBox::setActiveIndex(const int value)
		{
			return CCustomListBox::setActiveIndex(value);
		}

		bool CColorListBox::AddItem(IListItem *item)
		{
			m_bIsCustomItems = true;
			return CCustomListBox::AddItem(item);
		}

		bool CColorListBox::InsertItem(IListItem *item, const int before)
		{
			m_bIsCustomItems = true;
			return CCustomListBox::InsertItem(item, before);
		}

		bool CColorListBox::DeleteItem(const int index)
		{
			m_bIsCustomItems = true;
			return CCustomListBox::DeleteItem(index);
		}

		bool CColorListBox::DeleteItem(IListItem *item)
		{
			m_bIsCustomItems = true;
			return CCustomListBox::DeleteItem(item);
		}

		bool CColorListBox::DeleteItems()
		{
			m_bIsCustomItems = true;
			return CCustomListBox::DeleteItems();
		}

		bool CColorListBox::Add(IListItemColor *item)
		{
			return AddItem(item);
		}

		bool CColorListBox::Add(const Color &color, const String &caption)
		{
			return AddItem(new CColorListBoxListItem(color, caption));;
		}

		bool CColorListBox::Add(const CColor &color)
		{
			return AddItem(new CColorListBoxListItem(color, color));
		}

		bool CColorListBox::Insert(IListItemColor *item, const int before)
		{
			return InsertItem(item, before);
		}

		bool CColorListBox::Insert(const Color &color, const String &caption, const int before)
		{
			return InsertItem(new CColorListBoxListItem(color, caption), before);
		}

		bool CColorListBox::Insert(const CColor &color, const int before)
		{
			return InsertItem(new CColorListBoxListItem(color, color), before);
		}

		bool CColorListBox::Delete(const int index)
		{
			return DeleteItem(index);
		}

		bool CColorListBox::Delete(const String &caption)
		{
			CLockRepaint lock{ this };
			LockUpdate();
			bool result{ false };
			int i{ 0 };
			while (i < getItemCount())
				if (getItem(i)->getCaption() == caption)
					result = DeleteItem(i) || result;
				else
					i++;
			UnlockUpdate();
			return result;
		}

		bool CColorListBox::Delete(const CColor &color)
		{
			CLockRepaint lock{ this };
			LockUpdate();
			bool result{ false };
			int i{ 0 };
			while (i < getItemCount())
				if (getItem(i)->getColor() == color)
					result = DeleteItem(i) || result;
				else
					i++;
			UnlockUpdate();
			return result;
		}

		bool CColorListBox::Clear()
		{
			return DeleteItems();
		}
	#pragma endregion

	#pragma region Getters
		bool CColorListBox::hasStandardColors() const
		{
			return m_bHasStandardColors;
		}

		bool CColorListBox::hasExtendedColors() const
		{
			return m_bHasExtendedColors;
		}

		bool CColorListBox::hasNoneColor() const
		{
			return m_bHasNoneColor;
		}

		bool CColorListBox::isCustomItems() const
		{
			return m_bIsCustomItems;
		}
	#pragma endregion

	#pragma region Setters
		bool CColorListBox::setStandardColors(const bool value)
		{
			if (value != m_bHasStandardColors)
			{
				CLockRepaint lock{ this };
				m_bHasStandardColors = value;
				BuildList();
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CColorListBox::setExtendedColors(const bool value)
		{
			if (value != m_bHasExtendedColors)
			{
				CLockRepaint lock{ this };
				m_bHasExtendedColors = value;
				BuildList();
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CColorListBox::setNoneColor(const bool value)
		{
			if (value != m_bHasNoneColor)
			{
				CLockRepaint lock{ this };
				m_bHasNoneColor = value;
				BuildList();
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}
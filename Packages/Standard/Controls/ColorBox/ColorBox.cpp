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
		CColorBox::CColorBox() :
			CCustomDropDown(L"ColorBox", true, true, true, false),
			m_bHasStandardColors{ true },
			m_bHasExtendedColors{ true },
			m_bHasNoneColor{ true },
			m_bIsCustomItems{ false }
		{
			setCompareFunc(Compare);
			setGetItemTextFunc(GetItemText);
			setSearchFunc(Search);

			getBackgroundGradient(CBuiltInDropDown::State::Normal)->setPointCount(0);
			getArrowBackgroundGradient(CBuiltInDropDown::State::Normal)->setPointCount(0);
			getBackgroundGradient(CBuiltInDropDown::State::Hovered)->setPointCount(0);
			getArrowBackgroundGradient(CBuiltInDropDown::State::Hovered)->setPointCount(0);
			getBackgroundGradient(CBuiltInDropDown::State::Focused)->setPointCount(0);
			getArrowBackgroundGradient(CBuiltInDropDown::State::Focused)->setPointCount(0);
			getBackgroundGradient(CBuiltInDropDown::State::FocusedHovered)->setPointCount(0);
			getArrowBackgroundGradient(CBuiltInDropDown::State::FocusedHovered)->setPointCount(0);

			BuildList();
			setActiveIndex(0);
		}

		CColorBox::CColorBox(IForm *parent) :CColorBox()
		{
			setForm(parent);
		}

		CColorBox::CColorBox(IControl *parent) : CColorBox()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Helpers
		bool CColorBox::Compare(IListItem *a, IListItem *b)
		{
			return cast<IListItemColor*>(a)->getCaption() < cast<IListItemColor*>(b)->getCaption();
		}

		String CColorBox::GetItemText(IListItem *item)
		{
			return cast<IListItemColor*>(item)->getCaption();
		}

		int CColorBox::Search(IBuiltInDropDown *dropdown, const String &search)
		{
			if (dropdown->getControl())
				for (int i = 0; i < dropdown->getItemCount(); i++)
					if (dropdown->getItem(i)->isEnabled() && ToLower(Application->Translate->t(TranslateCategoryColors, cast<IListItemColor*>(dropdown->getItem(i))->getCaption())).find(search, 0) == 0)
						return i;
			return -1;
		}
		void CColorBox::BuildList()
		{
			Clear();
			CColorBox *self{ this };
			auto add = [self](const CColor &color) {self->Add(color); };
			if (m_bHasStandardColors)
				CColors::EnumStandardColors(add);
			if (m_bHasNoneColor)
				Add(CColors::None);
			if (m_bHasExtendedColors)
				CColors::EnumExtendedColors(add);
			m_bIsCustomItems = false;
		}
	#pragma endregion

	#pragma region Items
		bool CColorBox::isAcceptItem(IListItem *item)
		{
			return cast<IListItemColor*>(item) != nullptr;
		}

		IListItemColor *CColorBox::getItem(const int index)
		{
			return cast<IListItemColor*>(CCustomDropDown::getItem(index));
		}

		int CColorBox::getActiveIndex()
		{
			return CCustomDropDown::getActiveIndex();
		}

		bool CColorBox::setActiveIndex(const int index)
		{
			return CCustomDropDown::setActiveIndex(index);
		}

		bool CColorBox::AddItem(IListItem *item)
		{
			m_bIsCustomItems = true;
			return CCustomDropDown::AddItem(item);
		}

		bool CColorBox::InsertItem(IListItem *item, const int before)
		{
			m_bIsCustomItems = true;
			return CCustomDropDown::InsertItem(item, before);
		}

		bool CColorBox::DeleteItem(const int index)
		{
			m_bIsCustomItems = true;
			return CCustomDropDown::DeleteItem(index);
		}

		bool CColorBox::DeleteItem(IListItem *item)
		{
			m_bIsCustomItems = true;
			return CCustomDropDown::DeleteItem(item);
		}

		bool CColorBox::DeleteItems()
		{
			m_bIsCustomItems = true;
			return CCustomDropDown::DeleteItems();
		}

		bool CColorBox::Add(IListItemColor *item)
		{
			return AddItem(item);
		}

		bool CColorBox::Add(const Color &color, const String &caption)
		{
			return AddItem(new CListItemColor(color, caption));
		}

		bool CColorBox::Add(const CColor &color)
		{
			return AddItem(new CListItemColor(color, color));
		}

		bool CColorBox::Insert(IListItemColor *item, const int before)
		{
			return InsertItem(item, before);
		}

		bool CColorBox::Insert(const Color &color, const String &caption, const int before)
		{
			return InsertItem(new CListItemColor(color, caption), before);
		}

		bool CColorBox::Insert(const CColor &color, const int before)
		{
			return InsertItem(new CListItemColor(color, color), before);
		}

		bool CColorBox::Delete(const int index)
		{
			return DeleteItem(index);
		}

		bool CColorBox::Delete(const String &caption)
		{
			CLockRepaint lock{ this };
			bool result{ false };
			int i{ 0 };
			while (i < getItemCount())
				if (getItem(i)->getCaption() == caption)
					result = DeleteItem(i) || result;
				else
					i++;
			return result;
		}

		bool CColorBox::Delete(const CColor &color)
		{
			CLockRepaint lock{ this };
			bool result{ false };
			int i{ 0 };
			while (i < getItemCount())
				if (getItem(i)->getColor() == color)
					result = DeleteItem(i) || result;
				else
					i++;
			return result;
		}

		bool CColorBox::Clear()
		{
			return DeleteItems();
		}

		bool CColorBox::Open()
		{
			return CCustomDropDown::Open();
		}

		bool CColorBox::Close()
		{
			return CCustomDropDown::Close();
		}
	#pragma endregion

	#pragma region Getters
		bool CColorBox::hasStandardColors() const
		{
			return m_bHasStandardColors;
		}

		bool CColorBox::hasExtendedColors() const
		{
			return m_bHasExtendedColors;
		}

		bool CColorBox::hasNoneColor() const
		{
			return m_bHasNoneColor;
		}

		bool CColorBox::isCustomItems() const
		{
			return m_bIsCustomItems;
		}
	#pragma endregion

	#pragma region Setters
		bool CColorBox::setStandardColors(const bool value)
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

		bool CColorBox::setExtendedColors(const bool value)
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

		bool CColorBox::setNoneColor(const bool value)
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
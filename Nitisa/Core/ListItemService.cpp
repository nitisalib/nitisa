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
#pragma region Constructor & destructor
	CListItemService::CListItemService(CListItem *listitem) :m_pListItem{ listitem }
	{

	}

	void CListItemService::Release()
	{
		delete this;
	}
#pragma endregion

#pragma region Getters
	IListItemOwner *CListItemService::getOwner()
	{
		return m_pListItem->m_pOwner;
	}

	PointF CListItemService::getRequiredSize()
	{
		return PointF{ 0, 0 };
	}
#pragma endregion

#pragma region Setters
	bool CListItemService::setOwner(IListItemOwner *value)
	{
		if (value != m_pListItem->m_pOwner)
		{
			m_pListItem->m_pOwner = value;
			return true;
		}
		return false;
	}

	bool CListItemService::setParent(IListItem *value)
	{
		if (value != m_pListItem->m_pParent)
		{
			m_pListItem->m_pParent = value;
			return true;
		}
		return false;
	}

	bool CListItemService::setSize(const PointF &value)
	{
		if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, m_pListItem->m_sSize))
		{
			m_pListItem->m_sSize = value;
			return true;
		}
		return false;
	}

	bool CListItemService::setPosition(const PointF &value)
	{
		if (IsNotEqual(value, m_pListItem->m_sPosition))
		{
			m_pListItem->m_sPosition = value;
			return true;
		}
		return false;
	}

	bool CListItemService::setHovered(const bool value)
	{
		if (value != m_pListItem->m_bHovered)
		{
			m_pListItem->m_bHovered = value;
			return true;
		}
		return false;
	}

	bool CListItemService::setDPI(const Point &value)
	{
		return false;
	}
#pragma endregion

#pragma region Render
	void CListItemService::Render(const Mat4f &matrix, const Block *block, const bool last_pass, ITexture **clip)
	{

	}
#pragma endregion

#pragma region Input
	void CListItemService::NotifyOnFreeResources()
	{

	}

	bool CListItemService::NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	bool CListItemService::NotifyOnKeyUp(const Key key, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	bool CListItemService::NotifyOnChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	bool CListItemService::NotifyOnMouseDown(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	void CListItemService::NotifyOnMouseDownCancel()
	{

	}

	bool CListItemService::NotifyOnMouseMove(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	bool CListItemService::NotifyOnMouseUp(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	bool CListItemService::NotifyOnMouseDoubleClick(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	bool CListItemService::NotifyOnMouseVerticalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
	{
		return false;
	}

	bool CListItemService::NotifyOnMouseHorizontalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
	{
		return false;
	}

	bool CListItemService::NotifyOnDropFiles(const PointF &position, const StringArray &filenames)
	{
		return false;
	}
#pragma endregion

#pragma region Helpers
	void CListItemService::UpdateFromStyle()
	{

	}

	bool CListItemService::MoveItem(IListItem *item, const int before)
	{
		return MoveListItem(m_pListItem->m_aItems, m_pListItem, item, before);
	}
#pragma endregion
}
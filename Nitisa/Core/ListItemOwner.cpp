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
#pragma region Constructor & destructor
	CListItemOwner::CListItemOwner() :
		m_bIgnoreSizeChange{ false },
		m_bIgnoreRepaintRequired{ false },
		m_bIgnoreShow{ false },
		m_bIgnoreHide{ false },
		m_bIgnoreEnable{ false },
		m_bIgnoreDisable{ false },
		m_bIgnoreSelect{ false },
		m_bIgnoreDeselect{ false },
		m_bIgnoreActivate{ false },
		m_bIgnoreDeactivate{ false }
	{

	}

	void CListItemOwner::Release()
	{
		delete this;
	}
#pragma endregion

#pragma region Getters
	bool CListItemOwner::isIgnoreSizeChange()
	{
		return m_bIgnoreSizeChange;
	}

	bool CListItemOwner::isIgnoreRepaintRequired()
	{
		return m_bIgnoreRepaintRequired;
	}

	bool CListItemOwner::isIgnoreShow()
	{
		return m_bIgnoreShow;
	}

	bool CListItemOwner::isIgnoreHide()
	{
		return m_bIgnoreHide;
	}

	bool CListItemOwner::isIgnoreEnable()
	{
		return m_bIgnoreEnable;
	}

	bool CListItemOwner::isIgnoreDisable()
	{
		return m_bIgnoreDisable;
	}

	bool CListItemOwner::isIgnoreSelect()
	{
		return m_bIgnoreSelect;
	}

	bool CListItemOwner::isIgnoreDeselect()
	{
		return m_bIgnoreDeselect;
	}

	bool CListItemOwner::isIgnoreActivate()
	{
		return m_bIgnoreActivate;
	}

	bool CListItemOwner::isIgnoreDeactivate()
	{
		return m_bIgnoreDeactivate;
	}
#pragma endregion

#pragma region Setters
	void CListItemOwner::setIgnoreSizeChange(const bool value)
	{
		m_bIgnoreSizeChange = value;
	}

	void CListItemOwner::setIgnoreRepaintRequired(const bool value)
	{
		m_bIgnoreRepaintRequired = value;
	}

	void CListItemOwner::setIgnoreShow(const bool value)
	{
		m_bIgnoreShow = value;
	}

	void CListItemOwner::setIgnoreHide(const bool value)
	{
		m_bIgnoreHide = value;
	}

	void CListItemOwner::setIgnoreEnable(const bool value)
	{
		m_bIgnoreEnable = value;
	}

	void CListItemOwner::setIgnoreDisable(const bool value)
	{
		m_bIgnoreDisable = value;
	}

	void CListItemOwner::setIgnoreSelect(const bool value)
	{
		m_bIgnoreSelect = value;
	}

	void CListItemOwner::setIgnoreDeselect(const bool value)
	{
		m_bIgnoreDeselect = value;
	}

	void CListItemOwner::setIgnoreActivate(const bool value)
	{
		m_bIgnoreActivate = value;
	}

	void CListItemOwner::setIgnoreDeactivate(const bool value)
	{
		m_bIgnoreDeactivate = value;
	}
#pragma endregion
}
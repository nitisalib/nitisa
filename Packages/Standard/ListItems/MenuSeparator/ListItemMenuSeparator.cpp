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
		CListItemMenuSeparator::CListItemMenuSeparator() :
			CListItemMenu(L"ListItemMenuSeparator", false),
			m_pService{ nullptr },
			m_fHeight{ 1 },
			m_sColor{ 225, 225, 225, 255 },
			m_bIgnoreEnabled{ true }
		{
			setEnabledInternal(false);
		}

		CListItemMenuSeparator::~CListItemMenuSeparator()
		{
			if (m_pService)
				m_pService->Release();
		}
	#pragma endregion

	#pragma region Getters
		IListItemService *CListItemMenuSeparator::QueryService()
		{
			if (!m_pService)
				m_pService = new CListItemMenuSeparatorService(this);
			return m_pService;
		}

		float CListItemMenuSeparator::getHeight() const
		{
			return m_fHeight;
		}

		Color CListItemMenuSeparator::getColor() const
		{
			return m_sColor;
		}
	#pragma endregion

	#pragma region Setters
		bool CListItemMenuSeparator::setEnabled(const bool value)
		{
			if (!m_bIgnoreEnabled)
				return CListItemMenu::setEnabled(value);
			return false;
		}

		bool CListItemMenuSeparator::setSelected(const bool value)
		{
			return false;
		}

		bool CListItemMenuSeparator::setActive(const bool value)
		{
			return false;
		}

		bool CListItemMenuSeparator::setHeight(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fHeight))
			{
				m_fHeight = value;
				if (QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnSizeChange(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuSeparator::setColor(const Color &value)
		{
			if (value != m_sColor)
			{
				m_sColor = value;
				if (QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMenuSeparator::setEnabledInternal(const bool value)
		{
			m_bIgnoreEnabled = false;
			bool result{ setEnabled(value) };
			m_bIgnoreEnabled = true;
			return result;
		}
	#pragma endregion

	#pragma region Helpers
		bool CListItemMenuSeparator::AddItem(IListItem *item)
		{
			return false;
		}

		bool CListItemMenuSeparator::InsertItem(IListItem *item, const int before)
		{
			return false;
		}

		bool CListItemMenuSeparator::AddHotkey(const Key key, const bool ctrl, const bool alt, const bool shift, const bool down)
		{
			return false;
		}

		void CListItemMenuSeparator::UpdateFromStyle(IStyle *style)
		{
			bool changed{ false };
			changed = style->getOption(m_sClassName + L".Color", m_sColor) || changed;
			changed = style->getOption(m_sClassName + L".Height", m_fHeight) || changed;
			if (changed && QueryService()->getOwner())
				QueryService()->getOwner()->NotifyOnSizeChange(this);
		}

		IListItem *CListItemMenuSeparator::Clone()
		{
			CListItemMenuSeparator *result{ new CListItemMenuSeparator() };
			Copy(result);
			return result;
		}

		bool CListItemMenuSeparator::Copy(IListItem *dest)
		{
			CListItemMenuSeparator *d{ cast<CListItemMenuSeparator*>(dest) };
			if (d)
			{
				d->m_fHeight = m_fHeight;
				d->m_sColor = m_sColor;
				return CListItemMenu::Copy(dest);
			}
			return false;
		}
	#pragma endregion

	#pragma region Paint
		void CListItemMenuSeparator::Render(const Mat4f &matrix, const Block *block)
		{
			IRenderer *renderer{ QueryService()->getOwner()->getRenderer() };
			CStoreBlock s_block{ renderer };
			CStorePrimitiveMatrix s_matrix{ renderer };
			renderer
				->ActivateBlock(block)
				->ActivatePrimitiveMatrix(matrix)
				->DrawRectangle(RectF{ 0, 0, getSize().X, getSize().Y }, m_sColor);
		}
	#pragma endregion
	}
}
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
		CListItemCheckBoxService::CListItemCheckBoxService(CListItemCheckBox *checkbox) :
			CListItemService(checkbox),
			m_pCheckBox{ checkbox },
			m_sDPI{ DesignDPI }
		{

		}
	#pragma endregion

	#pragma region Getters
		PointF CListItemCheckBoxService::getRequiredSize()
		{
			if (getOwner() && getOwner()->getRenderer() && getOwner()->getFont(m_pCheckBox) && getOwner()->getFont(m_pCheckBox)->getPlatformFont(getOwner()->getRenderer()))
			{
				IPlatformFont *pf{ getOwner()->getFont(m_pCheckBox)->getPlatformFont(getOwner()->getRenderer()) };
				String caption{ Application->Translate->t(TranslateCategoryColors, m_pCheckBox->m_sCaption) };
				PointF size{ pf->getStringSize(caption, getOwner()->getFont(m_pCheckBox)->Distance) };
				if (caption.empty())
					size.Y = pf->getStringSize(L"Wy", 0).Y;
				size.Y += m_pCheckBox->m_sPadding.Top + m_pCheckBox->m_sPadding.Bottom;
				size.X += m_pCheckBox->m_sPadding.Left + m_pCheckBox->m_sPadding.Right + size.Y;
				return size;
			}
			return PointF{ 0, 0 };
		}
	#pragma endregion

	#pragma region Setters
		bool CListItemCheckBoxService::setDPI(const Point &value)
		{
			if (value.X > 0 && value.Y > 0 && value != m_sDPI)
			{
				PointF s{ (float)value.X / (float)m_sDPI.X, (float)value.Y / (float)m_sDPI.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sDPI = value;
				m_pCheckBox->m_sPadding *= s;
				for (int i = 0; i <= (int)CListItemCheckBox::State::Disabled; i++)
				{
					m_pCheckBox->m_aShadowRadius[i] = ntl::Round<int>((float)m_pCheckBox->m_aShadowRadius[i] * avg);
					m_pCheckBox->m_aShadowShift[i] *= s;
					m_pCheckBox->m_aBorderWidth[i] *= s;
					m_pCheckBox->m_aBorderRadius[i] *= avg;
					m_pCheckBox->m_aImagePadding[i] *= s;
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CListItemCheckBoxService::UpdateFromStyle()
		{
			if (getOwner() && getOwner()->getStyle(m_pCheckBox))
				m_pCheckBox->UpdateFromStyle(getOwner()->getStyle(m_pCheckBox));
		}

		void CListItemCheckBoxService::Render(const Mat4f &matrix, const Block *block, const bool last_pass, ITexture **clip)
		{
			m_pCheckBox->Render(matrix, block, clip);
		}
	#pragma endregion

	#pragma region Input
		bool CListItemCheckBoxService::NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift)
		{
			if (m_pCheckBox->isEnabled() && key == Key::Space && !alt)
				return m_pCheckBox->setChecked(!m_pCheckBox->m_bChecked);
			return false;
		}

		bool CListItemCheckBoxService::NotifyOnMouseDown(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			if (position.X >= 0 && position.X < m_pCheckBox->getSize().Y && position.Y >= 0 && position.Y < m_pCheckBox->getSize().Y && m_pCheckBox->isEnabled() && left && !right && !middle)
				return m_pCheckBox->setChecked(!m_pCheckBox->m_bChecked);
			return false;
		}
	#pragma endregion
	}
}
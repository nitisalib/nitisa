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
		CListItemStatusPanelLabelService::CListItemStatusPanelLabelService(CListItemStatusPanelLabel *label) :
			CListItemService(label),
			m_pLabel{ label },
			m_sDPI{ DesignDPI }
		{

		}
	#pragma endregion

	#pragma region Getters
		PointF CListItemStatusPanelLabelService::getRequiredSize()
		{
			if (getOwner() && getOwner()->getRenderer() && getOwner()->getFont(m_pLabel) && getOwner()->getFont(m_pLabel)->getPlatformFont(getOwner()->getRenderer()))
			{
				IPlatformFont *pf{ getOwner()->getFont(m_pLabel)->getPlatformFont(getOwner()->getRenderer()) };
				PointF size{ pf->getStringSize(m_pLabel->m_sCaption, getOwner()->getFont(m_pLabel)->Distance) };
				if (m_pLabel->m_sCaption.empty())
					size.Y = pf->getStringSize(L"Wy", 0).Y;
				if (ntl::IsLessOrEqual<float>(m_pLabel->getWidth(), 0))
					size.X += m_pLabel->m_sPadding.Left + m_pLabel->m_sPadding.Right;
				else
					size.X = m_pLabel->getWidth();
				size.Y += m_pLabel->m_sPadding.Top + m_pLabel->m_sPadding.Bottom;
				return size;
			}
			return PointF{ 0, 0 };
		}
	#pragma endregion

	#pragma region Setters
		bool CListItemStatusPanelLabelService::setDPI(const Point &value)
		{
			if (value.X > 0 && value.Y > 0 && value != m_sDPI)
			{
				PointF s{ (float)value.X / (float)m_sDPI.X, (float)value.Y / (float)m_sDPI.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sDPI = value;
				m_pLabel->m_sPadding *= s;
				for (int i = 0; i <= (int)CListItemStatusPanelLabel::State::Disabled; i++)
				{
					m_pLabel->m_aShadowRadius[i] = ntl::Round<int>((float)m_pLabel->m_aShadowRadius[i] * avg);
					m_pLabel->m_aShadowShift[i] *= s;
					m_pLabel->m_aBorderWidth[i] *= s;
					m_pLabel->m_aBorderRadius[i] *= avg;
				}
				m_pLabel->setWidth(m_pLabel->getWidth() * s.X);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CListItemStatusPanelLabelService::UpdateFromStyle()
		{
			if (getOwner() && getOwner()->getStyle(m_pLabel))
				m_pLabel->UpdateFromStyle(getOwner()->getStyle(m_pLabel));
		}

		void CListItemStatusPanelLabelService::Render(const Mat4f &matrix, const Block *block, const bool last_pass, ITexture **clip)
		{
			m_pLabel->Render(matrix, block, clip);
		}
	#pragma endregion
	}
}
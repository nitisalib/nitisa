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
		CSysColorDialog::CSysColorDialog() :
			CComponent(L"SysColorDialog"),
			m_bAnyColor{ true },
			m_bFullOpen{ true },
			m_bPreventFullOpen{ false },
			m_bOnlySolidColors{ false },
			m_sColor{ 0, 0, 0, 255 }
		{

		}

		CSysColorDialog::CSysColorDialog(IForm *parent) :CSysColorDialog()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		bool CSysColorDialog::isAnyColor()
		{
			return m_bAnyColor;
		}

		bool CSysColorDialog::isFullOpen()
		{
			return m_bFullOpen;
		}

		bool CSysColorDialog::isPreventFullOpen()
		{
			return m_bPreventFullOpen;
		}

		bool CSysColorDialog::isOnlySolidColors()
		{
			return m_bOnlySolidColors;
		}

		Color CSysColorDialog::getColor()
		{
			return m_sColor;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CSysColorDialog::setAnyColor(const bool value)
		{
			if (value != m_bAnyColor)
			{
				m_bAnyColor = value;
				return true;
			}
			return false;
		}

		bool CSysColorDialog::setFullOpen(const bool value)
		{
			if (value != m_bFullOpen)
			{
				m_bFullOpen = value;
				return true;
			}
			return false;
		}

		bool CSysColorDialog::setPreventFullOpen(const bool value)
		{
			if (value != m_bPreventFullOpen)
			{
				m_bPreventFullOpen = value;
				return true;
			}
			return false;
		}

		bool CSysColorDialog::setOnlySolidColors(const bool value)
		{
			if (value != m_bOnlySolidColors)
			{
				m_bOnlySolidColors = value;
				return true;
			}
			return false;
		}

		bool CSysColorDialog::setColor(const Color &value)
		{
			if (value != m_sColor)
			{
				m_sColor = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface helpers
		bool CSysColorDialog::Execute()
		{
			Color color{ m_sColor };
			if (Application->Dialogs->Color(m_bAnyColor, m_bFullOpen, m_bPreventFullOpen, m_bOnlySolidColors, color))
			{
				m_sColor = color;
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}
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
		CSysFontDialog::CSysFontDialog() :
			CComponent(L"SysFontDialog")
		{

		}

		CSysFontDialog::CSysFontDialog(IForm *parent) :CSysFontDialog()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		IFont *CSysFontDialog::getFont()
		{
			return &m_cFont;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CSysFontDialog::setFont(IFont *value)
		{
			if (value && !m_cFont.isEqual(value))
			{
				m_cFont.Copy(value);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface helpers
		bool CSysFontDialog::Execute()
		{
			String name{ m_cFont.FontName };
			int height{ m_cFont.Height };
			FontWeight weight{ m_cFont.Weight };
			bool italic{ m_cFont.Italic }, underline{ m_cFont.Underline }, strikeout{ m_cFont.StrikeOut };
			Color color{ m_cFont.Color };
			if (Application->Dialogs->Font(name, height, weight, italic, underline, strikeout, color))
			{
				m_cFont.setFontName(name);
				m_cFont.setHeight(height);
				m_cFont.setWeight(weight);
				m_cFont.setItalic(italic);
				m_cFont.setUnderline(underline);
				m_cFont.setStrikeOut(strikeout);
				m_cFont.setColor(color);
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}
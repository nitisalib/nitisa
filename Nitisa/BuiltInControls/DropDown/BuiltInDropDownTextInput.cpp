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
	CBuiltInDropDown::CTextInput::CTextInput(CBuiltInDropDown *dropdown) :
		CBuiltInTextInput(),
		m_pDropDown{ dropdown }
	{

	}
#pragma endregion

#pragma region Getters
	IControl *CBuiltInDropDown::CTextInput::getControl()
	{
		return m_pDropDown->getControl();
	}

	CBuiltInTextInput::State CBuiltInDropDown::CTextInput::getState()
	{
		switch (m_pDropDown->getState())
		{
		case CBuiltInDropDown::State::Normal:
			return CBuiltInTextInput::State::Normal;
		case CBuiltInDropDown::State::Hovered:
			return CBuiltInTextInput::State::Hovered;
		case CBuiltInDropDown::State::Focused:
			return CBuiltInTextInput::State::Focused;
		case CBuiltInDropDown::State::FocusedHovered:
			return CBuiltInTextInput::State::FocusedHovered;
		default:
			break;
		}
		return CBuiltInTextInput::State::Disabled;
	}
#pragma endregion
}
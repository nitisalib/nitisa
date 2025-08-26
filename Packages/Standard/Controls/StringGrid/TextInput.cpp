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
		CCustomStringGrid::CTextInput::CTextInput(CCustomStringGrid *control) :
			CBuiltInTextInput(),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl * CCustomStringGrid::CTextInput::getControl()
		{
			return m_pControl;
		}

		CBuiltInTextInput::State CCustomStringGrid::CTextInput::getState()
		{
			if (m_pControl->isCellHovered(m_pControl->m_sFocusedCell.X, m_pControl->m_sFocusedCell.Y))
				return CBuiltInTextInput::State::FocusedHovered;
			return CBuiltInTextInput::State::Focused;
		}
	#pragma endregion
	}
}
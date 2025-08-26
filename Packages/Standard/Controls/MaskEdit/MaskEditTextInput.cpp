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
		CMaskEdit::CMaskEditTextInput::CMaskEditTextInput(CMaskEdit *edit) :
			CBuiltInTextInput(),
			m_pEdit{ edit }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CMaskEdit::CMaskEditTextInput::getControl()
		{
			return m_pEdit;
		}

		CBuiltInTextInput::State CMaskEdit::CMaskEditTextInput::getState()
		{
			return m_pEdit->getState();
		}
	#pragma endregion
	}
}
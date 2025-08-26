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
		CEdit::CEditTextInput::CEditTextInput(CEdit *edit) :
			CBuiltInTextInput(),
			m_pEdit{ edit }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CEdit::CEditTextInput::getControl()
		{
			return m_pEdit;
		}

		CBuiltInTextInput::State CEdit::CEditTextInput::getState()
		{
			return m_pEdit->getState();
		}
	#pragma endregion
	}
}
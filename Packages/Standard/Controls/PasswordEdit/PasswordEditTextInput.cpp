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
		CPasswordEdit::CPasswordEditTextInput::CPasswordEditTextInput(CPasswordEdit *edit) :
			CBuiltInTextInput(),
			m_pEdit{ edit }
		{

		}
	#pragma endregion

	#pragma region Getters
		IControl *CPasswordEdit::CPasswordEditTextInput::getControl()
		{
			return m_pEdit;
		}

		CBuiltInTextInput::State CPasswordEdit::CPasswordEditTextInput::getState()
		{
			return m_pEdit->getState();
		}
	#pragma endregion
	}
}
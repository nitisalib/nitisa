#include "stdafx.h"

namespace nitisa
{
	namespace coolwidgets
	{
		CRegistration::CTextInput::CTextInput(CRegistration *control) :
			CBuiltInTextInput(),
			m_pControl{ control }
		{

		}

		IControl *CRegistration::CTextInput::getControl()
		{
			return m_pControl;
		}
	}
}
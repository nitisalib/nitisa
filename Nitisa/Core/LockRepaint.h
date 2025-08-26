// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IControl.h"
#include "../Interfaces/IForm.h"

namespace nitisa
{
	class CLockRepaint
	{
	private:
		IForm *m_pForm;
	public:
		CLockRepaint(IControl *control) : // Created based on the control
			m_pForm{ control->getForm() }
		{
			if (m_pForm)
				m_pForm->LockRepaint();
		}

		CLockRepaint(IForm *form) : // Create based on the form
			m_pForm{ form }
		{
			if (m_pForm)
				m_pForm->LockRepaint();
		}

		~CLockRepaint()
		{
			if (m_pForm)
				m_pForm->UnlockRepaint();
		}
	};
}
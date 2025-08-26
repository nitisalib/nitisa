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
		CTaskBarProgress::CTaskBarProgress():
			CComponent(L"TaskBarProgress")
		{
			
		}

		CTaskBarProgress::CTaskBarProgress(IForm *parent) :CTaskBarProgress()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Setters
		bool CTaskBarProgress::setType(const IWindow::ProgressType value)
		{
			if (getForm() && getForm()->QueryService()->getWindow())
				return getForm()->QueryService()->getWindow()->setProgressType(value);
			return false;
		}

		bool CTaskBarProgress::setProgress(const float value)
		{
			if (getForm() && getForm()->QueryService()->getWindow())
				return getForm()->QueryService()->getWindow()->setProgressValue(value);
			return false;
		}
	#pragma endregion
	}
}
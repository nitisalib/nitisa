// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IDialogBoxService.h"
#include "ControlService.h"

namespace nitisa
{
	class CDialogBox;

	class CDialogBoxService :public virtual IDialogBoxService, public CControlService
	{
	public:
		void NotifyOnSetActive() override;
		void NotifyOnKillActive() override;

		CDialogBoxService(CDialogBox *control);
	};
}
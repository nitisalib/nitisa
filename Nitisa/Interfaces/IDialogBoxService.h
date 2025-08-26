// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "IControlService.h"

namespace nitisa
{
	class IDialogBoxService :public virtual IControlService
	{
	protected:
		IDialogBoxService() = default;
		~IDialogBoxService() = default;
		IDialogBoxService(const IDialogBoxService &other) = delete;
		IDialogBoxService(IDialogBoxService &&other) = delete;
		IDialogBoxService &operator=(const IDialogBoxService &other) = delete;
		IDialogBoxService &operator=(IDialogBoxService &&other) = delete;
	public:
		virtual void NotifyOnSetActive() = 0; // Called when control become active dialog box
		virtual void NotifyOnKillActive() = 0; // Called when control lose active dialog box state
	};
}
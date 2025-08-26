// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Component.h"
#include "Nitisa/Interfaces/IWindow.h"
#include "../ITaskBarProgress.h"

namespace nitisa
{
	class IForm;

	namespace standard
	{
		class CTaskBarProgress :public virtual ITaskBarProgress, public CComponent
		{
		public:
			bool setType(const IWindow::ProgressType value) override;
			bool setProgress(const float value) override;

			CTaskBarProgress();
			CTaskBarProgress(IForm *parent);
		};
	}
}
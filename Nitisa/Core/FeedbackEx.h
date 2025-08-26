// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IFeedbackEx.h"

namespace nitisa
{
	class CFeedbackEx :public virtual IFeedbackEx
	{
	public:
		bool setListener(IFeedbackExListener *listener) override;

		CFeedbackEx(IFeedbackExListener *listener); // Create with specified listener
	};
}
// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IFeedback.h"

namespace nitisa
{
	class CFeedback :public virtual IFeedback
	{
	public:
		bool setListener(IFeedbackListener *listener) override;

		CFeedback(IFeedbackListener *listener); // Create with specified listener
	};
}
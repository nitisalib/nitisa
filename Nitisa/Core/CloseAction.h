// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	enum class CloseAction // Possible actions when user click on close button of form/window
	{
		None, // No action, remains opened
		Hide, // Only hide the window/form
		Free, // Destroy. Default one
		Minimize // Minimize
	};
}
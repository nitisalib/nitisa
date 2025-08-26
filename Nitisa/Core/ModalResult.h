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
	enum class ModalResult // Form modal result type
	{
		None, // No result
		Ok, // Okay
		Cancel, // Cancelled
		Abort, // Aborted
		Retry, // Retry is required
		Ignore, // Ignored
		Yes, // Yes is answered
		No, // No is answered
		NoToAll, // No to all is selected
		YesToAll, // Yes to all is selected
		Close // Window was closed and probably(if no form assigned or main form) destroyed
	};
}
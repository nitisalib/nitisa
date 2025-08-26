// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Math/Point.h"

namespace nitisa
{
	// Handle mouse related independent actions
	class IMouse
	{
	protected:
		IMouse() = default;
		~IMouse() = default;
		IMouse(const IMouse &other) = delete;
		IMouse(IMouse &&other) = delete;
		IMouse &operator=(const IMouse &other) = delete;
		IMouse &operator=(IMouse &&other) = delete;
	public:
		virtual Point getPosition() = 0; // Return mouse pointer position in screen coordinates. Return {-1, -1} on the platform without mouse support.
		virtual bool setPosition(const Point &value) = 0; // Set mouse pointer new position in screen coordinates. Return false on platform without mouse support.
	};
}
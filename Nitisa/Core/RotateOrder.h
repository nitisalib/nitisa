// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Strings.h"

namespace nitisa
{
	enum class RotateOrder // Rotate order(name defines the axis order)
	{
		XYZ,
		XZY,
		YXZ,
		YZX,
		ZXY,
		ZYX
	};

	String RotateOrderToString(const RotateOrder value);
	RotateOrder StringToRotateOrder(const String &value);
	StringArray RotateOrderItems();
}
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
	enum class TransformOrder // Transformation order
	{
		SRT, // Scale -> rotate -> translate
		STR, // Scale -> translate -> rotate
		RST, // Rotate -> scale -> translate
		RTS, // Rotate -> translate -> scale
		TSR, // Translate -> scale -> rotate
		TRS  // Translate -> rotate -> scale
	};

	String TransformOrderToString(const TransformOrder value);
	TransformOrder StringToTransformOrder(const String &value);
	StringArray TransformOrderItems();
}
// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Math/PointF.h"

namespace nitisa
{
	struct TouchPoint
	{
		PointF Pos; // Position
		int Id; // Identifier
		// Flags
		bool IsMove;
		bool IsDown;
		bool IsUp;
		bool IsInRange;
		bool IsPrimary;
		bool IsNoCoalesce;
		bool IsPalm;
		bool IsContactAreaValid;
		bool IsTimeValid;
		float Time; // Time
		PointF ContactAreaSize; // Area size
	};
}
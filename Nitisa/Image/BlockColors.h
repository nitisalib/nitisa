// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/PointLocation.h"
#include "Color.h"

namespace nitisa
{
	using BlockColors = Color[(int)PointLocation::Outside + 1]; // Array of colors for each parts of Block
}
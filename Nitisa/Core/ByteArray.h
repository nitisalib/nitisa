// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Aliases.h"
#include <vector>

namespace nitisa
{
	using ByteArray = std::vector<byte>;

	ByteArray Merge(const std::vector<ByteArray> &arrays);
}
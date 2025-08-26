// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Variant.h"
#include "Types.h"
#include <utility>
#include <vector>

namespace nitisa
{
	Variant ToVariant(const std::vector<std::pair<String, String>> &value);
	void FromVariant(const Variant &src, std::vector<std::pair<String, String>> &dest);

	Variant ToVariant(const fb::SETTINGS &value);
	void FromVariant(const Variant &src, fb::SETTINGS &dest);
}
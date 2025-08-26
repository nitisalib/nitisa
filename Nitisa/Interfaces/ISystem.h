// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/PlatformType.h"

namespace nitisa
{
	class ISystem
	{
	protected:
		ISystem() = default;
		~ISystem() = default;
		ISystem(const ISystem &other) = delete;
		ISystem(ISystem &&other) = delete;
		ISystem &operator=(const ISystem &other) = delete;
		ISystem &operator=(ISystem &&other) = delete;
	protected:
		PlatformType m_ePlatform;
		wchar_t m_sDirectorySeparator;
	public:
		PlatformType const &Platform{ m_ePlatform }; // Platform information
		wchar_t const &DirectorySeparator{ m_sDirectorySeparator }; // Directory separator(slash or backslash)
	};
}
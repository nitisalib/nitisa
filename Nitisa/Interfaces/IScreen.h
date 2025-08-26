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
	class IScreen
	{
	protected:
		IScreen() = default;
		~IScreen() = default;
		IScreen(const IScreen &other) = delete;
		IScreen(IScreen &&other) = delete;
		IScreen &operator=(const IScreen &other) = delete;
		IScreen &operator=(IScreen &&other) = delete;
	public:
		virtual int getWidth() = 0; // Return screen resolution width. On some platforms, like Android, this will return 0 always because the platform has no api to get this value.
		virtual int getHeight() = 0; // Return screen resolution height. On some platforms, like Android, this will return 0 always because the platform has no api to get this value.
		virtual Point getDPI() = 0; // Return screen DPI
	};
}
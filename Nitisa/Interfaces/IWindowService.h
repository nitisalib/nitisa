// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"

namespace nitisa
{
	class IWindowListener;

	class IWindowService
	{
	protected:
		IWindowService() = default;
		~IWindowService() = default;
		IWindowService(const IWindowService &other) = delete;
		IWindowService(IWindowService &&other) = delete;
		IWindowService &operator=(const IWindowService &other) = delete;
		IWindowService &operator=(IWindowService &&other) = delete;
	public:
		virtual IWindowListener *getListener() = 0; // Return associated listener

		virtual void setHandle(PlatformHandle value) = 0; // Set real window handle
		virtual void setListener(IWindowListener *value) = 0; // Associate listener

		virtual void StartTrackMouseLeave() = 0; // Start tracking mouse leave window events
		virtual void Release() = 0; // Destroy instance
	};
}
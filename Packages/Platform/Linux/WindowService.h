// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#if defined(__linux__) && !defined(__ANDROID__)
#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Interfaces/IWindowListener.h"
#include "Nitisa/Interfaces/IWindowService.h"

#ifdef linux
#undef linux
#endif

namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
			class CWindow;

			class CWindowService :public virtual IWindowService
			{
			private:
				CWindow * m_pWindow;
			public:
				CWindowService(CWindow *window);
				virtual ~CWindowService() = default;

				IWindowListener *getListener() override;

				void setHandle(PlatformHandle value) override;
				void setListener(IWindowListener *value) override;

				void StartTrackMouseLeave() override;
				void Release() override;
			};
		}
	}
}
#endif
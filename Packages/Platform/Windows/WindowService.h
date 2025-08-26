// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Interfaces/IWindowService.h"

namespace nitisa
{
	class IWindowListener;

	namespace platform
	{
		namespace windows
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
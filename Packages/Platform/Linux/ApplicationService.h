// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#if defined(__linux__) && !defined(__ANDROID__)
#include "Nitisa/Interfaces/IApplicationService.h"

#ifdef linux
#undef linux
#endif

namespace nitisa
{
	class IForm;

	namespace platform
	{
		namespace linux
		{
			class CApplication;

			class CApplicationService :public virtual IApplicationService
			{
			private:
				CApplication * m_pApplication;
			public:
				void Release() override;
				void Add(IForm *form) override;
				void Remove(IForm *form) override;
				void SendTranslateChangeNotification() override;

				CApplicationService(CApplication *application);
				virtual ~CApplicationService() = default;
			};
		}
	}
}
#endif
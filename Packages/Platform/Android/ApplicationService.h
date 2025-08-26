// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include "Nitisa/Interfaces/IApplication.h"

namespace nitisa
{
	class IForm;

	namespace platform
	{
		namespace android
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
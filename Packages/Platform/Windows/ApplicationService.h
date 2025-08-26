// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IApplicationService.h"

namespace nitisa
{
	class IForm;
	class IRenderer;

	namespace platform
	{
		namespace windows
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
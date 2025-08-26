// This file is a part of Nitisa framework
// Copyright © 2018 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ControlService.h"

namespace nitisa
{
	namespace standard
	{
		class CTabSheet;

		class CTabSheetService :public CControlService
		{
		private:
			CTabSheet *m_pTabSheet;
		public:
			// State change notifications
			void NotifyOnAttach() override;

			CTabSheetService(CTabSheet *tabsheet);
		};
	}
}
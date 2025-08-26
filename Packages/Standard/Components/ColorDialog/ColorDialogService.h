// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ComponentService.h"

namespace nitisa
{
	namespace standard
	{
		class CColorDialog;

		class CColorDialogService :public CComponentService
		{
		private:
			CColorDialog *m_pControl;
		public:
			CColorDialogService(CColorDialog *control);

			// State change notifications
			void NotifyOnAttach() override;
			void NotifyOnDetaching() override;

			// Control notifications
			void NotifyOnControlDetach(IControl *control) override;
		};
	}
}
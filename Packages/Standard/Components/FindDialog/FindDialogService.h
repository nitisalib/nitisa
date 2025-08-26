// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ComponentService.h"

namespace nitisa
{
	class IControl;

	namespace standard
	{
		class CFindDialog;

		class CFindDialogService :public CComponentService
		{
		private:
			CFindDialog *m_pControl;
		public:
			CFindDialogService(CFindDialog *control);

			// State change notifications
			void NotifyOnAttach() override;
			void NotifyOnDetaching() override;

			// Control notifications
			void NotifyOnControlDetach(IControl *control) override;
		};
	}
}
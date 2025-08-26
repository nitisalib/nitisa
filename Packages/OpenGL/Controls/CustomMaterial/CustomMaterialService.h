// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ControlService.h"

namespace nitisa
{
	namespace opengl
	{
		class CCustomMaterial;

		class CCustomMaterialService :public CControlService
		{
		private:
			CCustomMaterial *m_pControl;
		public:
			// State change notifications
			void NotifyOnFreeResources() override;

			CCustomMaterialService(CCustomMaterial *control);
		};
	}
}
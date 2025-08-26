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
		class CBlinnPhongMaterial;

		class CBlinnPhongMaterialService :public CControlService
		{
		private:
			CBlinnPhongMaterial *m_pControl;
		public:
			// State change notifications
			void NotifyOnFreeResources() override;

			CBlinnPhongMaterialService(CBlinnPhongMaterial *control);
		};
	}
}
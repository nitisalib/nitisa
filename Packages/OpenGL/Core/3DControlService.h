// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ControlService.h"
#include "../Interfaces/I3DControlService.h"

namespace nitisa
{
	class ICamera;
	class IControl;
	class IRenderer;

	class COpenGL;

	namespace opengl
	{
		class C3DControl;

		class C3DControlService :public virtual I3DControlService, public CControlService
		{
		private:
			C3DControl *m_pControl;
		public:
			// State change notifications
			void NotifyOnFreeResources() override;

			// Control notifications
			void NotifyOnControlDetach(IControl *control) override;
			void NotifyOnControlChange(IControl *control) override;

			// Rendering
			void NotifyOnRender(COpenGL *graphics, IRenderer *renderer, ICamera *camera) override;

			C3DControlService(C3DControl *control);
		};
	}
}
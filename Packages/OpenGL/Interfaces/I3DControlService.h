// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControlService.h"

namespace nitisa
{
	class ICamera;
	class IRenderer;

	class COpenGL;

	namespace opengl
	{
		class I3DControlService :public virtual IControlService
		{
		protected:
			I3DControlService() = default;
			~I3DControlService() = default;
			I3DControlService(const I3DControlService &other) = delete;
			I3DControlService(I3DControlService &&other) = delete;
			I3DControlService &operator=(const I3DControlService &other) = delete;
			I3DControlService &operator=(I3DControlService &&other) = delete;
		public:
			// Rendering
			virtual void NotifyOnRender(COpenGL *graphics, IRenderer *renderer, ICamera *camera) = 0; // This notification should be used instead of usual NotifyOnPaint
		};
	}
}
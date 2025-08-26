// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	class ICamera;
	class IModel;

	class COpenGL;

	namespace opengl
	{
		class IMaterialControl :public virtual IControl
		{
		protected:
			IMaterialControl() = default;
			~IMaterialControl() = default;
			IMaterialControl(const IMaterialControl &other) = delete;
			IMaterialControl(IMaterialControl &&other) = delete;
			IMaterialControl &operator=(const IMaterialControl &other) = delete;
			IMaterialControl &operator=(IMaterialControl &&other) = delete;
		public:
			virtual bool Activate(COpenGL *graphics, IModel *model, ICamera *camera) = 0; // Activate material
		};
	}
}
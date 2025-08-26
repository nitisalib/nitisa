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

	namespace opengl
	{
		class IView: public virtual IControl
		{
		protected:
			IView() = default;
			~IView() = default;
			IView(const IView &other) = delete;
			IView(IView &&other) = delete;
			IView &operator=(const IView &other) = delete;
			IView &operator=(IView &&other) = delete;
		public:
			void(*OnRender)(IView *sender); // Event called when rendering is happened

			virtual ICamera *getCamera() = 0; // Return associated camera

			virtual bool setCamera(ICamera *value) = 0; // Set camera, old one will be automatically destroyed
		};
	}
}
// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Image/Color.h"
#include "../Interfaces/IMaterialControl.h"

namespace nitisa
{
	class ITexture;

	namespace opengl
	{
		class ISolidMaterial :public virtual IMaterialControl
		{
		protected:
			ISolidMaterial() = default;
			~ISolidMaterial() = default;
			ISolidMaterial(const ISolidMaterial &other) = delete;
			ISolidMaterial(ISolidMaterial &&other) = delete;
			ISolidMaterial &operator=(const ISolidMaterial &other) = delete;
			ISolidMaterial &operator=(ISolidMaterial &&other) = delete;
		public:
			virtual ITexture *getTexture() = 0; // Return associated texture
			virtual Color getColor() = 0; // Return color

			virtual bool setTexture(ITexture *value) = 0; // Associate texture
			virtual bool setColor(const Color &value) = 0; // Set color
		};
	}
}
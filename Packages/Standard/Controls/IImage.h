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
	class ITexture;

	class Image;

	namespace standard
	{
		class IImage :public virtual IControl
		{
		protected:
			IImage() = default;
			~IImage() = default;
			IImage(const IImage &other) = delete;
			IImage(IImage &&other) = delete;
			IImage &operator=(const IImage &other) = delete;
			IImage &operator=(IImage &&other) = delete;
		public:
			virtual Image *getImage() = 0; // Return image

			virtual void Assign(const Image &data) = 0; // Copy image data from another one
			virtual bool Assign(ITexture *texture) = 0; // Copy image from texture
			virtual void Update() = 0; // Update and repaint after modifying of image data
		};
	}
}
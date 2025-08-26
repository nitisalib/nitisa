// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IComponent.h"

namespace nitisa
{
	class ITexture;

	class Image;

	namespace standard
	{
		class IImageList : public virtual IComponent
		{
		protected:
			IImageList() = default;
			~IImageList() = default;
			IImageList(const IImageList &other) = delete;
			IImageList(IImageList &&other) = delete;
			IImageList &operator=(const IImageList &other) = delete;
			IImageList &operator=(IImageList &&other) = delete;
		public:
			virtual int getImageCount() = 0; // Return image count
			virtual Image *getImage(const int index) = 0; // Return image by index
			virtual ITexture *getTexture(const int index) = 0; // Return(create if necessary and possible) texture for image at specified index

			virtual int AddImage(Image *data) = 0; // Add image to list. Return index or -1
			virtual bool DeleteImage(const int index) = 0; // Delete image by index
			virtual bool DeleteImages() = 0; // Delete all images
			virtual void Update() = 0; // Send update notification. Call after updating images data
		};
	}
}
// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	class Image;

	namespace standard
	{
		class IFormImageList
		{
		protected:
			IFormImageList() = default;
			~IFormImageList() = default;
			IFormImageList(const IFormImageList &other) = delete;
			IFormImageList(IFormImageList &&other) = delete;
			IFormImageList &operator=(const IFormImageList &other) = delete;
			IFormImageList &operator=(IFormImageList &&other) = delete;
		public:
			virtual int getImageCount() = 0; // Return image count
			virtual Image *getImage(const int index) = 0; // Return image by index

			virtual int AddImage(Image *value) = 0; // Add image
			virtual bool DeleteImage(const int index) = 0; // Delete image by index
			virtual bool DeleteImages() = 0; // Delete all images
		};
	}
}
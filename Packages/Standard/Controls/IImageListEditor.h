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
	class Image;

	namespace standard
	{
		class IImageList;

		class IImageListEditor :public virtual IControl
		{
		protected:
			IImageListEditor() = default;
			~IImageListEditor() = default;
			IImageListEditor(const IImageListEditor &other) = delete;
			IImageListEditor(IImageListEditor &&other) = delete;
			IImageListEditor &operator=(const IImageListEditor &other) = delete;
			IImageListEditor &operator=(IImageListEditor &&other) = delete;
		public:
			virtual IImageList *getImageList() = 0; // Return assigned image list
			virtual int getImageCount() = 0; // Return image count
			virtual Image *getImage(const int index) = 0; // Return image by index
			virtual bool isImageSelected(const int index) = 0; // Whether image is selected

			virtual bool setImageList(IImageList *value) = 0; // Assign image list
			virtual bool setImageSelected(const int index, const bool value) = 0; // Set whether specified image is selected or not

			virtual bool DeleteSelectedImages() = 0; // Delete selected images
		};
	}
}
// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "IProperty.h"

namespace nitisa
{
	class Image;

	class IPropertyImageList :public virtual IProperty
	{
	protected:
		IPropertyImageList() = default;
		~IPropertyImageList() = default;
		IPropertyImageList(const IPropertyImageList &other) = delete;
		IPropertyImageList(IPropertyImageList &&other) = delete;
		IPropertyImageList &operator=(const IPropertyImageList &other) = delete;
		IPropertyImageList &operator=(IPropertyImageList &&other) = delete;
	public:
		virtual int getCount() = 0; // Return image count
		virtual Image* getImage(const int index) = 0; // Return image by index

		virtual int Add(Image *data) = 0; // Add image
		virtual bool Delete(const int index) = 0; // Delete image by index
		virtual bool Clear() = 0; // Delete all images
		virtual void Update() = 0; // Call to update owner after image change
	};
}
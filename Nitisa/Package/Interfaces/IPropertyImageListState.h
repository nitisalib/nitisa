// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "IPropertyState.h"

namespace nitisa
{
	class Image;

	class IPropertyImageListState :public virtual IPropertyState
	{
	protected:
		IPropertyImageListState() = default;
		~IPropertyImageListState() = default;
		IPropertyImageListState(const IPropertyImageListState &other) = delete;
		IPropertyImageListState(IPropertyImageListState &&other) = delete;
		IPropertyImageListState &operator=(const IPropertyImageListState &other) = delete;
		IPropertyImageListState &operator=(IPropertyImageListState &&other) = delete;
	public:
		virtual int getCount(const String &state) = 0; // Return image count at state
		virtual Image *getImage(const String &state, const int index) = 0; // Return image by index at state

		virtual bool Add(const String &state, Image *data) = 0; // Add image to state
		virtual bool Delete(const String &state, const int index) = 0; // Delete image by index from state
		virtual bool Clear(const String &state) = 0; // Delete all images from state
		virtual void Update() = 0; // Call to update owner after image change
	};
}
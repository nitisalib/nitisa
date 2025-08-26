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

	class IPropertyImageState :public virtual IPropertyState
	{
	protected:
		IPropertyImageState() = default;
		~IPropertyImageState() = default;
		IPropertyImageState(const IPropertyImageState &other) = delete;
		IPropertyImageState(IPropertyImageState &&other) = delete;
		IPropertyImageState &operator=(const IPropertyImageState &other) = delete;
		IPropertyImageState &operator=(IPropertyImageState &&other) = delete;
	public:
		virtual Image* getValue(const String &state) = 0; // Return value depending on state

		virtual void Update() = 0; // Call to update owner after image change
	};
}
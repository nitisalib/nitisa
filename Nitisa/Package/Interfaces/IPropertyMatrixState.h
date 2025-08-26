// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Math/Mat4f.h"
#include "IPropertyState.h"

namespace nitisa
{
	class IPropertyMatrixState :public virtual IPropertyState
	{
	protected:
		IPropertyMatrixState() = default;
		~IPropertyMatrixState() = default;
		IPropertyMatrixState(const IPropertyMatrixState &other) = delete;
		IPropertyMatrixState(IPropertyMatrixState &&other) = delete;
		IPropertyMatrixState &operator=(const IPropertyMatrixState &other) = delete;
		IPropertyMatrixState &operator=(IPropertyMatrixState &&other) = delete;
	public:
		virtual Mat4f getValue(const String &state) = 0; // Return value depending on state

		virtual bool setValue(const String &state, const Mat4f value) = 0; // Set value of state
	};
}
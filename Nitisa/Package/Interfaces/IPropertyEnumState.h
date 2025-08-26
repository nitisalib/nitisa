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
	class IPropertyEnumState :public virtual IPropertyState
	{
	protected:
		IPropertyEnumState() = default;
		~IPropertyEnumState() = default;
		IPropertyEnumState(const IPropertyEnumState &other) = delete;
		IPropertyEnumState(IPropertyEnumState &&other) = delete;
		IPropertyEnumState &operator=(const IPropertyEnumState &other) = delete;
		IPropertyEnumState &operator=(IPropertyEnumState &&other) = delete;
	public:
		virtual String getValue(const String &state) = 0; // Return value depending on state
		virtual int getItemCount() const = 0; // Return allow values count
		virtual String getItem(const int index) const = 0; // Return allow values count

		virtual bool setValue(const String &state, const String value) = 0; // Set value of state
	};
}
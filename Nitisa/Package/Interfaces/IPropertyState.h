// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../Core/ExportPrefixType.h"
#include "IProperty.h"

namespace nitisa
{
	class IPropertyState : public virtual IProperty
	{
	protected:
		IPropertyState() = default;
		~IPropertyState() = default;
		IPropertyState(const IPropertyState &other) = delete;
		IPropertyState(IPropertyState &&other) = delete;
		IPropertyState &operator=(const IPropertyState &other) = delete;
		IPropertyState &operator=(IPropertyState &&other) = delete;
	public:
		virtual int getStateCount() = 0; // Return state count
		virtual String getState(const int index) = 0; // Return state name by index
		virtual ExportPrefixType getStatePrefixType() = 0; // Return state prefix type
		virtual String getStatePrefix() = 0; // Return state additional prefix
	};
}
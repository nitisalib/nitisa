// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "IListItem.h"

namespace nitisa
{
	class IListItemCaption: public virtual IListItem
	{
	protected:
		IListItemCaption() = default;
		~IListItemCaption() = default;
		IListItemCaption(const IListItemCaption &other) = delete;
		IListItemCaption(IListItemCaption &&other) = delete;
		IListItemCaption &operator=(const IListItemCaption &other) = delete;
		IListItemCaption &operator=(IListItemCaption &&other) = delete;
	public:
		virtual String getCaption() = 0; // Return caption

		virtual bool setCaption(const String &value) = 0; // Set caption
	};
}
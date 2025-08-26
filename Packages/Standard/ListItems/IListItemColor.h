// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IListItemCaption.h"
#include "Nitisa/Image/Color.h"

namespace nitisa
{
	namespace standard
	{
		class IListItemColor :public virtual IListItemCaption
		{
		protected:
			IListItemColor() = default;
			~IListItemColor() = default;
			IListItemColor(const IListItemColor &other) = delete;
			IListItemColor(IListItemColor &&other) = delete;
			IListItemColor &operator=(const IListItemColor &other) = delete;
			IListItemColor &operator=(IListItemColor &&other) = delete;
		public:
			virtual Color getColor() = 0; // Return color

			virtual bool setColor(const Color &value) = 0; // Set color
		};
	}
}
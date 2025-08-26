// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IListItemCaption.h"
#include "Nitisa/Interfaces/IListItemOwner.h"
#include "Nitisa/Math/RectF.h"

namespace nitisa
{
	class ITexture;

	namespace standard
	{
		class IListItemIcon;

		class IListItemIconOwner :public virtual IListItemOwner
		{
		protected:
			IListItemIconOwner() = default;
			~IListItemIconOwner() = default;
			IListItemIconOwner(const IListItemIconOwner &other) = delete;
			IListItemIconOwner(IListItemIconOwner &&other) = delete;
			IListItemIconOwner &operator=(const IListItemIconOwner &other) = delete;
			IListItemIconOwner &operator=(IListItemIconOwner &&other) = delete;
		public:
			virtual ITexture *getIcon(IListItemIcon *item, RectF &part) = 0; // Return icon image and part occupied by icon
		};

		class IListItemIcon :public virtual IListItemCaption
		{
		protected:
			IListItemIcon() = default;
			~IListItemIcon() = default;
			IListItemIcon(const IListItemIcon &other) = delete;
			IListItemIcon(IListItemIcon &&other) = delete;
			IListItemIcon &operator=(const IListItemIcon &other) = delete;
			IListItemIcon &operator=(IListItemIcon &&other) = delete;
		public:
			// No additional properties and methods
		};
	}
}
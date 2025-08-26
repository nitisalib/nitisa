// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Image/Color.h"
#include "Nitisa/Interfaces/IComponent.h"

namespace nitisa
{
	namespace standard
	{
		class ISysColorDialog :public virtual IComponent
		{
		protected:
			ISysColorDialog() = default;
			~ISysColorDialog() = default;
			ISysColorDialog(const ISysColorDialog &other) = delete;
			ISysColorDialog(ISysColorDialog &&other) = delete;
			ISysColorDialog &operator=(const ISysColorDialog &other) = delete;
			ISysColorDialog &operator=(ISysColorDialog &&other) = delete;
		public:
			virtual bool isAnyColor() = 0; // Return whether any color could be selected
			virtual bool isFullOpen() = 0; // Return whether dialog is fully opened
			virtual bool isPreventFullOpen() = 0; // Return whether allow or not open dialog fully
			virtual bool isOnlySolidColors() = 0; // Return whether only predefined set of colors could be selected
			virtual Color getColor() = 0; // Return selected color

			virtual bool setAnyColor(const bool value) = 0; // Set whether any color could be selected
			virtual bool setFullOpen(const bool value) = 0; // Set whether dialog is fully opened
			virtual bool setPreventFullOpen(const bool value) = 0; // Set whether allow or not open dialog fully
			virtual bool setOnlySolidColors(const bool value) = 0; // Set whether only predefined set of colors could be selected
			virtual bool setColor(const Color &value) = 0; // Set selected color

			virtual bool Execute() = 0; // Show dialog
		};
	}
}
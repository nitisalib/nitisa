// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		class IColorDialog;

		class IColorDialogListener
		{
		protected:
			IColorDialogListener() = default;
			~IColorDialogListener() = default;
			IColorDialogListener(const IColorDialogListener &other) = delete;
			IColorDialogListener(IColorDialogListener &&other) = delete;
			IColorDialogListener &operator=(const IColorDialogListener &other) = delete;
			IColorDialogListener &operator=(IColorDialogListener &&other) = delete;
		public:
			virtual void OnApply(IColorDialog *sender) = 0; // Event called when color selection has been successfully finished
		};

		class IColorDialog :public virtual IComponent
		{
		protected:
			IColorDialog() = default;
			~IColorDialog() = default;
			IColorDialog(const IColorDialog &other) = delete;
			IColorDialog(IColorDialog &&other) = delete;
			IColorDialog &operator=(const IColorDialog &other) = delete;
			IColorDialog &operator=(IColorDialog &&other) = delete;
		public:
			void(*OnApply)(IComponent *sender); // Event called when color form or dialog box closed with applying changes

			virtual Color getColor() = 0; // Get selected color
			virtual bool isUseDialogBox() = 0; // Return whether dialog box or regular form should be used
			virtual IColorDialogListener *getColorDialogListener() = 0; // Return assigned listener

			virtual bool setColor(const Color &value) = 0; // Set selected color
			virtual bool setUseDialogBox(const bool value) = 0; // Set whether dialog box or regular form should be used
			virtual void setColorDialogListener(IColorDialogListener *value) = 0; // Assign listener

			virtual bool Execute() = 0; // Show dialog
		};
	}
}
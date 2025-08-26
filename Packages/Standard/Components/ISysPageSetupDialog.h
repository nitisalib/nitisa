// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IComponent.h"
#include "Nitisa/Interfaces/IDialogs.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"

namespace nitisa
{
	namespace standard
	{
		class ISysPageSetupDialog :public virtual IComponent
		{
		protected:
			ISysPageSetupDialog() = default;
			~ISysPageSetupDialog() = default;
			ISysPageSetupDialog(const ISysPageSetupDialog &other) = delete;
			ISysPageSetupDialog(ISysPageSetupDialog &&other) = delete;
			ISysPageSetupDialog &operator=(const ISysPageSetupDialog &other) = delete;
			ISysPageSetupDialog &operator=(ISysPageSetupDialog &&other) = delete;
		public:
			virtual bool isDisableMargins() = 0; // Return whether to disable the margin controls, preventing the user from setting the margins
			virtual bool isDisableOrientation() = 0; // Return whether to disable the orientation controls, preventing the user from setting the page orientation
			virtual bool isDisablePagePainting() = 0; // Return whether to prevent the dialog box from drawing the contents of the sample page
			virtual bool isDisablePaper() = 0; // Return whether to disable the paper controls, preventing the user from setting page parameters such as the paper size and source
			virtual bool isNoNetworkButton() = 0; // Return whether to hide and disable the Network button
			virtual RectF getMinMargins() = 0; // Return minimum allowed margins in millimeters. Used only if there are positive and zero values
			virtual String getDeviceName() = 0; // Return friendly name of the printer
			virtual RectF getMargins() = 0; // Return margins in millimeters. Used only if there are positive and zero values
			virtual bool isLandscape() = 0; // Return whether landscape or portrait orientation has been selected
			virtual IDialogs::PrintPaperSize getPaperSize() = 0; // Return selected paper size
			virtual float getPaperLength() = 0; // Return selected custom paper length in millimeters
			virtual float getPaperWidth() = 0; // Return selected custom paper width in millimeters
			virtual float getScale() = 0; // Return selected scaling factor
			virtual int getCopies() = 0; // Return selected number of copies
			virtual IDialogs::PrintPaperSource getPaperSource() = 0; // Return selected paper source
			virtual IDialogs::PrintQuality getPrintQuality() = 0; // Return selected print quality
			virtual bool isMonochrome() = 0; // Return selected mode: colored or monochrome
			virtual IDialogs::PrintDuplex getDuplex() = 0; // Return selected duplex or double-sided printing
			virtual IDialogs::PrintTTOption getTTOption() = 0; // Return selected methods of how TrueType fonts should be printed
			virtual bool isCollate() = 0; // Return whether collation should be used when printing multiple copies
			virtual IDialogs::PrintMediaType getMediaType() = 0; // Return selected media type to be printed
			virtual IDialogs::PrintDitherType getDitherType() = 0; // Return selected dither method
			virtual PointF getSize() = 0; // Return dimension of the paper selected by the user in millimeters

			virtual bool setDisableMargins(const bool value) = 0; // Set whether to disable the margin controls, preventing the user from setting the margins
			virtual bool setDisableOrientation(const bool value) = 0; // Set whether to disable the orientation controls, preventing the user from setting the page orientation
			virtual bool setDisablePagePainting(const bool value) = 0; // Set whether to prevent the dialog box from drawing the contents of the sample page
			virtual bool setDisablePaper(const bool value) = 0; // Set whether to disable the paper controls, preventing the user from setting page parameters such as the paper size and source
			virtual bool setNoNetworkButton(const bool value) = 0; // Set whether to hide and disable the Network button
			virtual bool setMinMargins(const RectF &value) = 0; // Set minimum allowed margins in millimeters. Used only if there are positive and zero values
			virtual bool setMargins(const RectF &value) = 0; // Set margins in millimeters. Used only if there are positive and zero values

			virtual bool Execute() = 0; // Show dialog
		};
	}
}
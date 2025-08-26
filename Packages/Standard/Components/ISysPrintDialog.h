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
#include "Nitisa/Math/Point.h"

namespace nitisa
{
	namespace standard
	{
		class ISysPrintDialog :public virtual IComponent
		{
		protected:
			ISysPrintDialog() = default;
			~ISysPrintDialog() = default;
			ISysPrintDialog(const ISysPrintDialog &other) = delete;
			ISysPrintDialog(ISysPrintDialog &&other) = delete;
			ISysPrintDialog &operator=(const ISysPrintDialog &other) = delete;
			ISysPrintDialog &operator=(ISysPrintDialog &&other) = delete;
		public:
			virtual bool isSelectCollate() = 0; // Return whether the Collate check box is selected
			virtual bool isSelectCurrentPage() = 0; // Return whether the Current Page radio button is selected
			virtual bool isDisablePrintToFile() = 0; // Return whether to disable the Print to File check box
			virtual bool isHidePrintToFile() = 0; // Return whether to hide the Print to File check box
			virtual bool isDisableCurrentPage() = 0; // Return whether to disable the Current Page radio button
			virtual bool isNoPageNums() = 0; // Return whether to disable the Pages radio button and the associated edit controls
			virtual bool isNoSelection() = 0; // Return whether to disable the Selection radio button
			virtual bool isSelectPageNums() = 0; // Return whether the Pages radio button is selected
			virtual bool isSelectPrintToFile() = 0; // Return whether the Print to File check box is selected
			virtual bool isSelectSelection() = 0; // Return whether the Selection radio button is selected
			virtual int getMinPage() = 0; // Return the minimum value for the page range specified in the From and To page edit controls
			virtual int getMaxPage() = 0; // Return the maximum value for the page range specified in the From and To page edit controls
			virtual int getMaxPageRangeCount() = 0; // Return size of page_ranges array
			virtual int getPageRangeCount() = 0; // Return page range count
			virtual Point getPageRange(const int index) = 0; // Return page range by index
			virtual int getCopies() = 0; // Return number of copies
			virtual String getDeviceName() = 0; // Return friendly name of the printer
			virtual bool isLandscape() = 0; // Return whether landscape or portrait orientation has been selected
			virtual IDialogs::PrintPaperSize getPaperSize() = 0; // Return selected paper size
			virtual float getPaperLength() = 0; // Return selected custom paper length in millimeters
			virtual float getPaperWidth() = 0; // Return selected custom paper width in millimeters
			virtual float getScale() = 0; // Return selected scaling factor
			virtual IDialogs::PrintPaperSource getPaperSource() = 0; // Return selected paper source
			virtual IDialogs::PrintQuality getPrintQuality() = 0; // Return selected print quality
			virtual bool isMonochrome() = 0; // Return selected mode: colored or monochrome
			virtual IDialogs::PrintDuplex getDuplex() = 0; // Return selected duplex or double-sided printing
			virtual IDialogs::PrintTTOption getTTOption() = 0; // Return selected methods of how TrueType fonts should be printed
			virtual bool isCollate() = 0; // Return whether collation should be used when printing multiple copies
			virtual IDialogs::PrintMediaType getMediaType() = 0; // Return selected media type to be printed
			virtual IDialogs::PrintDitherType getDitherType() = 0; // Return selected dither method

			virtual bool setSelectCollate(const bool value) = 0; // Set whether the Collate check box is selected
			virtual bool setSelectCurrentPage(const bool value) = 0; // Set whether the Current Page radio button is selected
			virtual bool setDisablePrintToFile(const bool value) = 0; // Set whether to disable the Print to File check box
			virtual bool setHidePrintToFile(const bool value) = 0; // Set whether to hide the Print to File check box
			virtual bool setDisableCurrentPage(const bool value) = 0; // Set whether to disable the Current Page radio button
			virtual bool setNoPageNums(const bool value) = 0; // Set whether to disable the Pages radio button and the associated edit controls
			virtual bool setNoSelection(const bool value) = 0; // Set whether to disable the Selection radio button
			virtual bool setSelectPageNums(const bool value) = 0; // Set whether the Pages radio button is selected
			virtual bool setSelectPrintToFile(const bool value) = 0; // Set whether the Print to File check box is selected
			virtual bool setSelectSelection(const bool value) = 0; // Set whether the Selection radio button is selected
			virtual bool setMinPage(const int value) = 0; // Set the minimum value for the page range specified in the From and To page edit controls
			virtual bool setMaxPage(const int value) = 0; // Set the maximum value for the page range specified in the From and To page edit controls
			virtual bool setMaxPageRangeCount(const int value) = 0; // Set maximum allowed ranges to be selected by user
			virtual bool setPageRangeCount(const int value) = 0; // Set page range count
			virtual bool setPageRange(const int index, const Point &value) = 0; // Set page range by index
			virtual bool setCopies(const int value) = 0; // Set number of copies

			virtual IDialogs::PrintDialogResult Execute(void **handle) = 0; // Show dialog. Specify pointer where to write printing handle(HDC). Set nullptr to not return handle. You have to free handle after usage
		};
	}
}
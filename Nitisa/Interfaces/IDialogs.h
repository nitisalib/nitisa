// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/FontWeight.h"
#include "../Core/ModalResult.h"
#include "../Core/Strings.h"
#include "../Math/Point.h"
#include "../Math/PointF.h"
#include "../Math/RectF.h"
#include "../Image/Color.h"

namespace nitisa
{
	class IDialogs
	{
	protected:
		IDialogs() = default;
		~IDialogs() = default;
		IDialogs(const IDialogs &other) = delete;
		IDialogs(IDialogs &&other) = delete;
		IDialogs &operator=(const IDialogs &other) = delete;
		IDialogs &operator=(IDialogs &&other) = delete;
	public:
		enum class PrintPaperSize
		{
			Unknown, // System dialog returned some unknown value
			Letter, // Letter, 8 1 / 2 - by 11 - inches
			Legal, // Legal, 8 1 / 2 - by 14 - inches
			Sheet9x11, // 9 - by 11 - inch sheet
			Sheet10x11, // 10 - by 11 - inch sheet
			Sheet10x14, // 10 - by 14 - inch sheet
			Sheet15x11, // 15 - by 11 - inch sheet
			Sheet11x17, // 11 - by 17 - inch sheet
			Sheet12x11, // 12 - by 11 - inch sheet
			A2, // A2 sheet, 420 x 594 - millimeters
			A3, // A3 sheet, 297 - by 420 - millimeters
			A3Extra, // A3 Extra 322 x 445 - millimeters
			A3Rotated, // A3 rotated sheet, 420 - by 297 - millimeters
			A4, // A4 sheet, 210 - by 297 - millimeters
			A4Extra, // A4 sheet, 9.27 x 12.69 inches
			A4Plus, // A4 Plus 210 x 330 - millimeters
			A4Rotated, // A4 rotated sheet, 297 - by 210 - millimeters
			A4Small, // A4 small sheet, 210 - by 297 - millimeters
			A4Transverse, // A4 Transverse 210 x 297 millimeters
			A5, // A5 sheet, 148 - by 210 - millimeters
			A5Extra, // A5 Extra 174 x 235 - millimeters
			A5Rotated, // A5 rotated sheet, 210 - by 148 - millimeters
			A5Transverse, // A5 Transverse 148 x 210 - millimeters
			A6, // A6 sheet, 105 - by 148 - millimeters
			A6Rotated, // A6 rotated sheet, 148 - by 105 - millimeters
			APlus, // SuperA / A4 227 x 356 - millimeters
			B4, // B4 sheet, 250 - by 354 - millimeters
			B4JisRotated, // B4(JIS) rotated sheet, 364 - by 257 - millimeters
			B5, // B5 sheet, 182 - by 257 - millimeter paper
			B5Extra, // B5(ISO) Extra 201 x 276 - millimeters
			B5JisRotated, // B5(JIS) rotated sheet, 257 - by 182 - millimeters
			B6Jis, // B6(JIS) sheet, 128 - by 182 - millimeters
			B6JisRotated, // B6(JIS) rotated sheet, 182 - by 128 - millimeters
			BPlus, // SuperB / A3 305 x 487 - millimeters
			CSheet, // C Sheet, 17 - by 22 - inches
			DblJapanesePostcard, // Double Japanese Postcard, 200 - by 148 - millimeters
			DblJapanesePostcardRotated, // Double Japanese Postcard Rotated, 148 - by 200 - millimeters
			DSheet, // D Sheet, 22 - by 34 - inches
			Env9, // #9 Envelope, 3 7 / 8 - by 8 7 / 8 - inches
			Env10, // #10 Envelope, 4 1 / 8 - by 9 1 / 2 - inches
			Env11, // #11 Envelope, 4 1 / 2 - by 10 3 / 8 - inches
			Env12, // #12 Envelope, 4 3 / 4 - by 11 - inches
			Env14, // #14 Envelope, 5 - by 11 1 / 2 - inches
			EnvC5, // C5 Envelope, 162 - by 229 - millimeters
			EnvC3, // C3 Envelope, 324 - by 458 - millimeters
			EnvC4, // C4 Envelope, 229 - by 324 - millimeters
			EnvC6, // C6 Envelope, 114 - by 162 - millimeters
			EnvC65, // C65 Envelope, 114 - by 229 - millimeters
			EnvB4, // B4 Envelope, 250 - by 353 - millimeters
			EnvB5, // B5 Envelope, 176 - by 250 - millimeters
			EnvB6, // B6 Envelope, 176 - by 125 - millimeters
			EnvDL, // DL Envelope, 110 - by 220 - millimeters
			EnvInvite, // Envelope Invite 220 x 220 mm
			EnvItaly, // Italy Envelope, 110 - by 230 - millimeters
			EnvMonarch, // Monarch Envelope, 3 7 / 8 - by 7 1 / 2 - inches
			EnvPersonal, // 6 3 / 4 Envelope, 3 5 / 8 - by 6 1 / 2 - inches
			ESheet, // E Sheet, 34 - by 44 - inches
			Executive, // Executive, 7 1 / 4 - by 10 1 / 2 - inches
			FanfoldUS, // US Std Fanfold, 14 7 / 8 - by 11 - inches
			FanfoldStdGerman, // German Std Fanfold, 8 1 / 2 - by 12 - inches
			FanfoldLglGerman, // German Legal Fanfold, 8 - by 13 - inches
			Folio, // Folio, 8 1 / 2 - by 13 - inch paper
			ISOB4, // B4(ISO) 250 - by 353 - millimeters paper
			JapanesePostcard, // Japanese Postcard, 100 - by 148 - millimeters
			JapanesePostcardRotated, // Japanese Postcard Rotated, 148 - by 100 - millimeters
			JEnvChou3, // Japanese Envelope Chou #3
			JEnvChou3Rotated, // Japanese Envelope Chou #3 Rotated
			JEnvChou4, // Japanese Envelope Chou #4
			JEnvChou4Rotated, // Japanese Envelope Chou #4 Rotated
			JEnvKaku2, // Japanese Envelope Kaku #2
			JEnvKaku2Rotated, // Japanese Envelope Kaku #2 Rotated
			JEnvKaku3, // Japanese Envelope Kaku #3
			JEnvKaku3Rotated, // Japanese Envelope Kaku #3 Rotated
			JEnvYou4, // Japanese Envelope You #4
			JEnvYou4Rotated, // Japanese Envelope You #4 Rotated
			Ledger, // Ledger, 17 - by 11 - inches
			LegalExtra, // Legal Extra 9 1 / 2 x 15 inches.
			LetterExtra, // Letter Extra 9 1 / 2 x 12 inches.
			LetterExtraTransverse, // Letter Extra Transverse 9 1 / 2 x 12 inches.
			LetterRotated, // Letter Rotated 11 by 8 1 / 2 inches
			LetterSmall, // Letter Small, 8 1 / 2 - by 11 - inches
			LetterTransverse, // Letter Transverse 8 1 / 2 x 11 - inches
			Note, // Note, 8 1 / 2 - by 11 - inches
			P16K, // PRC 16K, 146 - by 215 - millimeters
			P16KRotated, // PRC 16K Rotated, 215 - by 146 - millimeters
			P32K, // PRC 32K, 97 - by 151 - millimeters
			P32KRotated, // PRC 32K Rotated, 151 - by 97 - millimeters
			P32KBig, // PRC 32K(Big) 97 - by 151 - millimeters
			P32KBigRotated, // PRC 32K(Big) Rotated, 151 - by 97 - millimeters
			Penv1, // PRC Envelope #1, 102 - by 165 - millimeters
			Penv1Rotated, // PRC Envelope #1 Rotated, 165 - by 102 - millimeters
			Penv2, // PRC Envelope #2, 102 - by 176 - millimeters
			Penv2Rotated, // PRC Envelope #2 Rotated, 176 - by 102 - millimeters
			Penv3, // PRC Envelope #3, 125 - by 176 - millimeters
			Penv3Rotated, // PRC Envelope #3 Rotated, 176 - by 125 - millimeters
			Penv4, // PRC Envelope #4, 110 - by 208 - millimeters
			Penv4Rotated, // PRC Envelope #4 Rotated, 208 - by 110 - millimeters
			Penv5, // PRC Envelope #5, 110 - by 220 - millimeters
			Penv5Rotated, // PRC Envelope #5 Rotated, 220 - by 110 - millimeters
			Penv6, // PRC Envelope #6, 120 - by 230 - millimeters
			Penv6Rotated, // PRC Envelope #6 Rotated, 230 - by 120 - millimeters
			Penv7, // PRC Envelope #7, 160 - by 230 - millimeters
			Penv7Rotated, // PRC Envelope #7 Rotated, 230 - by 160 - millimeters
			Penv8, // PRC Envelope #8, 120 - by 309 - millimeters
			Penv8Rotated, // PRC Envelope #8 Rotated, 309 - by 120 - millimeters
			Penv9, // PRC Envelope #9, 229 - by 324 - millimeters
			Penv9Rotated, // PRC Envelope #9 Rotated, 324 - by 229 - millimeters
			Penv10, // PRC Envelope #10, 324 - by 458 - millimeters
			Penv10Rotated, // PRC Envelope #10 Rotated, 458 - by 324 - millimeters
			Quarto, // Quarto, 215 - by 275 - millimeter paper
			Statement, // Statement, 5 1 / 2 - by 8 1 / 2 - inches
			Tabloid, // Tabloid, 11 - by 17 - inches
			TabloidExtra // Tabloid, 11.69 x 18 - inches
		};

		enum class PrintPaperSource
		{
			Unknown, // Unknown
			Auto, // Select automatically
			Cassette, // Cassette
			Envelope, // Envelope
			EnvManual, // Manual envelope
			FormSource, // Form source
			LargeCapacity, // Large capacity
			LargeFmt, // Large format
			Lower, // Lower
			Manual, // Manual
			Middle, // Middle
			Tractor, // Tractor
			SmallFmt, // Small format
			Upper // Upper
		};

		enum class PrintQuality
		{
			Unknown, // Unknown
			High, // High
			Medium, // Medium
			Low, // Low
			Draft // Draft
		};

		enum class PrintDuplex
		{
			Unknown, // Unknown
			Simplex, // Normal(nonduplex) printing.
			Horizontal, // Short - edge binding, that is, the long edge of the page is horizontal.
			Vertical // Long - edge binding, that is, the long edge of the page is vertical.
		};

		enum class PrintTTOption
		{
			Unknown, // Unknown
			Bitmap, // Prints TrueType fonts as graphics.This is the default action for dot - matrix printers.
			Download, // Downloads TrueType fonts as soft fonts.This is the default action for Hewlett - Packard printers that use Printer Control Language(PCL).
			DownloadOutline, // Downloads TrueType fonts as outline soft fonts.
			Subdev // Substitutes device fonts for TrueType fonts.This is the default action for PostScript printers.
		};

		enum class PrintMediaType
		{
			Unknown, // Unknown
			Standard, // Plain paper.
			Glossy, // Glossy paper.
			Transparency // Transparent film.
		};

		enum class PrintDitherType
		{
			Unknown, // Unknown
			None, // No dithering.
			Coarse, // Dithering with a coarse brush.
			Fine, // Dithering with a fine brush.
			LineArt, // Line art dithering, a special dithering method that produces well defined borders between black, white, and gray scaling.It is not suitable for images that include continuous graduations in intensity and hue, such as scanned photographs.
			GrayScale // Device does gray scaling.
		};

		enum class PrintDialogResult
		{
			Error, // Invalid parameters specified or dialog is unsupported
			Apply, // "Apply" button was down
			Cancel, // "Cancel" button was down
			Print // "Print" button was down
		};
	public:
		// Messages
		virtual bool Message(const String &message, const String &caption = L"Message") = 0; // Show dialog message
		virtual bool Warning(const String &message, const String &caption = L"Warning") = 0; // Show dialog message with warning icon
		virtual bool Information(const String &message, const String &caption = L"Information") = 0; // Show dialog message with information icon
		virtual bool Question(const String &message, const String &caption = L"Question") = 0; // Show dialog message with question icon
		virtual bool Error(const String &message, const String &caption = L"Error") = 0; // Show dialog message with error icon
		virtual ModalResult Confirm(const String &message, const String &caption = L"Confirm") = 0; // Show confirmation modal dialog and return selected answer

		// Dialogs
		virtual bool Open( // Show platform open file dialog
			const String &filter, // Filter format: "name|filter;filter" + "\n" + "name|filter". For example, "Jpeg images|*.jpg;*.jpeg\nBitmaps|*.bmp"
			const int filter_index, // Index of active filter
			String &filename, // Default file name
			const bool multiselect, // Whether multiple files could be selected
			const bool create_prompt, // Whether to ask about file creation if it doesn't exist
			const bool must_exists, // Whether file must exists to be selected
			const bool show_hidden, // Whether to show hidden files
			const bool hide_readonly, // Whether to hide readonly files
			const bool no_network) = 0; // Whether to hide network
		virtual bool Save( // Show platform save file dialog
			const String &filter, // Filter format: "name|filter;filter" + "\n" + "name|filter". For example, "Jpeg images|*.jpg;*.jpeg\nBitmaps|*.bmp"
			const int filter_index, // Index of active filter
			String &filename, // Default file name
			const String &default_extension, // Default extension
			const bool create_prompt, // Whether to ask about file creation if it doesn't exist
			const bool must_exists, // Whether file must exists to be selected
			const bool show_hidden, // Whether to show hidden files
			const bool hide_readonly, // Whether to hide readonly files
			const bool no_network, // Whether to hide network
			const bool overwrite_prompt) = 0; // Whether to ask about file overwriting when existing file is selected
		virtual bool Font( // Show platform font selection dialog
			String &name, // [in, out] Family name
			int &height, // [in, out] Height
			FontWeight &weight, // [in, out] Weight
			bool &italic, // [in, out] Whether it is italic
			bool &underline, // [in, out] Whether it is underlined
			bool &strikeout, // [in, out] Whether it is striked out
			Color &color) = 0; // [in, out] Color
		virtual bool Color( // Show platform specific choose color dialog
			const bool any_color, // Whether any color could be selected
			const bool full_open, // Whether dialog is fully opened
			const bool prevent_full_open, // Whether dialog could be fully opened
			const bool only_solid_colors, // Whether only predefined colors could be selected
			Color &color) = 0; // [in, out] Color
		virtual bool PageSetup( // Show platform specific page setup dialog
			const bool disable_margins, // Disables the margin controls, preventing the user from setting the margins
			const bool disable_orientation, // Disables the orientation controls, preventing the user from setting the page orientation
			const bool disable_page_painting, // Prevents the dialog box from drawing the contents of the sample page
			const bool disable_paper, // Disables the paper controls, preventing the user from setting page parameters such as the paper size and source
			const bool no_network_button, // Hides and disables the Network button
			const RectF &min_margins, // Minimum allowed margins in millimeters. Used only if there are positive and zero values
			String &device_name, // [out] Friendly name of the printer
			RectF &margins, // [in, out] Margins in millimeters. Used only if there are positive and zero values
			bool &landscape, // [out] Whether landscape or portrait orientation has been selected
			PrintPaperSize &paper_size, // [out] Selected paper size
			float &paper_length, // [out] Selected custom paper length in millimeters
			float &paper_width, // [out] Selected custom paper width in millimeters
			float &scale, // [out] Selected scaling factor
			int &copies, // [out] Selected number of copies
			PrintPaperSource &paper_source, // [out] Selected paper source
			PrintQuality &print_quality, // [out] Selected print quality
			bool &monochrome, // [out] Selected mode: colored or monochrome
			PrintDuplex &duplex, // [out] Selected duplex or double-sided printing
			PrintTTOption &tt_option, // [out] Selected methods of how TrueType fonts should be printed
			bool &collate, // [out] Specifies whether collation should be used when printing multiple copies
			PrintMediaType &media_type, // [out] Selected media type to be printed
			PrintDitherType &dither_type, // [out] Selected dither method
			PointF &size) = 0; // [out] The dimensions of the paper selected by the user in millimeters
		virtual PrintDialogResult Print( // Show platform specific print setup dialog
			const bool select_collate, // If this flag is set, the Collate check box is selected
			const bool select_current_page, // If this flag is set, the Current Page radio button is selected
			const bool disable_print_to_file, // Disables the Print to File check box
			const bool hide_print_to_file, // Hides the Print to File check box
			const bool disable_current_page, // Disables the Current Page radio button
			const bool no_page_nums, // Disables the Pages radio button and the associated edit controls
			const bool no_selection, // Disables the Selection radio button
			const bool select_page_nums, // If this flag is set, the Pages radio button is selected
			const bool select_print_to_file, // If this flag is set, the Print to File check box is selected
			const bool select_selection, // If this flag is set, the Selection radio button is selected
			const int min_page, // The minimum value for the page range specified in the From and To page edit controls
			const int max_page, // The maximum value for the page range specified in the From and To page edit controls
			const int max_page_range_count, // Size of page_ranges array
			int &page_range_count, // [in, out] Input/Selected page range count
			Point *page_ranges, // [in, out] Page ranges
			int &copies, // [in, out] Initial/Selected number of copies
			String &device_name, // [out] Friendly name of the printer
			bool &landscape, // [out] Whether landscape or portrait orientation has been selected
			PrintPaperSize &paper_size, // [out] Selected paper size
			float &paper_length, // [out] Selected custom paper length in millimeters
			float &paper_width, // [out] Selected custom paper width in millimeters
			float &scale, // [out] Selected scaling factor
			PrintPaperSource &paper_source, // [out] Selected paper source
			PrintQuality &print_quality, // [out] Selected print quality
			bool &monochrome, // [out] Selected mode: colored or monochrome
			PrintDuplex &duplex, // [out] Selected duplex or double-sided printing
			PrintTTOption &tt_option, // [out] Selected methods of how TrueType fonts should be printed
			bool &collate, // [out] Specifies whether collation should be used when printing multiple copies
			PrintMediaType &media_type, // [out] Selected media type to be printed
			PrintDitherType &dither_type, // [out] Selected dither method
			void **handle) = 0; // [out] Pointer where to write printing handle(HDC). Set nullptr to not return handle
		virtual bool BrowseFolder( // Show folder browse dialog
			String &folder, // [out] Folder name(with directory character at the end)
			const String &title, // Dialog title
			const bool only_file_system, // Only return file system directories
			const bool no_network, // Do not include network folders below the domain level in the dialog box's tree view control
			const bool only_ancestors, // Only return file system ancestors. An ancestor is a subfolder that is beneath the root folder in the namespace hierarchy. If the user selects an ancestor of the root folder that is not part of the file system, the OK button is grayed
			const bool show_edit_box, // Include an edit control in the browse dialog box that allows the user to type the name of an item
			const bool new_style, // Use the new user interface
			const bool show_hint, // Adds a usage hint to the dialog box, in place of the edit box
			const bool hide_new_folder, // Do not include the New Folder button in the browse dialog box
			const bool dont_translate_targets, // When the selected item is a shortcut, return the name of the shortcut itself rather than its target
			const bool only_computers, // Only return computers
			const bool only_printers, // Only allow the selection of printers
			const bool show_files, // The browse dialog box displays files as well as folders
			const bool show_shareable) = 0; // The browse dialog box can display sharable resources on remote systems
	};
}
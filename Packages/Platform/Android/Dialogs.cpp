// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

#ifdef __ANDROID__
namespace nitisa
{
	namespace platform
	{
		namespace android
		{
		#pragma region Messages
			bool CDialogs::Message(const String &message, const String &caption)
			{
				return false;
			}

			bool CDialogs::Warning(const String &message, const String &caption)
			{
				return false;
			}

			bool CDialogs::Information(const String &message, const String &caption)
			{
				return false;
			}

			bool CDialogs::Question(const String &message, const String &caption)
			{
				return false;
			}

			bool CDialogs::Error(const String &message, const String &caption)
			{
				return false;
			}

			ModalResult CDialogs::Confirm(const String &message, const String &caption)
			{
				return ModalResult::Cancel;
			}
		#pragma endregion

		#pragma region Dialogs
			bool CDialogs::Open(const String &filter, const int filter_index, String &filename, const bool multiselect, const bool create_prompt, const bool must_exists, const bool show_hidden,
				const bool hide_readonly, const bool no_network)
			{
				return false;
			}

			bool CDialogs::Save(const String &filter, const int filter_index, String &filename, const String &default_extension, const bool create_prompt, const bool must_exists,
				const bool show_hidden, const bool hide_readonly, const bool no_network, const bool overwrite_prompt)
			{
				return false;
			}

			bool CDialogs::Font(String &name, int &height, FontWeight &weight, bool &italic, bool &underline, bool &strikeout, nitisa::Color &color)
			{
				return false;
			}

			bool CDialogs::Color(const bool any_color, const bool full_open, const bool prevent_full_open, const bool only_solid_colors, nitisa::Color &color)
			{
				return false;
			}

			bool CDialogs::PageSetup(const bool disable_margins, const bool disable_orientation, const bool disable_page_painting, const bool disable_paper, const bool no_network_button,
				const RectF &min_margins, String &device_name, RectF &margins, bool &landscape, PrintPaperSize &paper_size, float &paper_length, float &paper_width, float &scale, int &copies,
				PrintPaperSource &paper_source, PrintQuality &print_quality, bool &monochrome, PrintDuplex &duplex, PrintTTOption &tt_option, bool &collate, PrintMediaType &media_type,
				PrintDitherType &dither_type, PointF &size)
			{
				return false;
			}

			IDialogs::PrintDialogResult CDialogs::Print(const bool select_collate, const bool select_current_page, const bool disable_print_to_file, const bool hide_print_to_file, const bool disable_current_page,
				const bool no_page_nums, const bool no_selection, const bool select_page_nums, const bool select_print_to_file, const bool select_selection, const int min_page,
				const int max_page, const int max_page_range_count, int &page_range_count, Point *page_ranges, int &copies, String &device_name, bool &landscape,
				PrintPaperSize &paper_size, float &paper_length, float &paper_width, float &scale, PrintPaperSource &paper_source, PrintQuality &print_quality, bool &monochrome,
				PrintDuplex &duplex, PrintTTOption &tt_option, bool &collate, PrintMediaType &media_type, PrintDitherType &dither_type, void **handle)
			{
				return PrintDialogResult::Error;
			}

			bool CDialogs::BrowseFolder(String &folder, const String &title, const bool only_file_system, const bool no_network, const bool only_ancestors, const bool show_edit_box, const bool new_style,
				const bool show_hint, const bool hide_new_folder, const bool dont_translate_targets, const bool only_computers, const bool only_printers, const bool show_files,
				const bool show_shareable)
			{
				return false;
			}
		#pragma endregion
		}
	}
}
#endif
// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include "Nitisa/Core/FontWeight.h"
#include "Nitisa/Core/ModalResult.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Interfaces/IDialogs.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"

namespace nitisa
{
	namespace platform
	{
		namespace android
		{
			// None is supported by Android. All the methods always return false
			class CDialogs :public virtual IDialogs
			{
			public:
				// Messages
				bool Message(const String &message, const String &caption = L"Message") override;
				bool Warning(const String &message, const String &caption = L"Warning") override;
				bool Information(const String &message, const String &caption = L"Information") override;
				bool Question(const String &message, const String &caption = L"Question") override;
				bool Error(const String &message, const String &caption = L"Error") override;
				ModalResult Confirm(const String &message, const String &caption = L"Confirm") override;

				// Dialogs
				bool Open(const String &filter, const int filter_index, String &filename, const bool multiselect, const bool create_prompt, const bool must_exists, const bool show_hidden,
					const bool hide_readonly, const bool no_network) override;
				bool Save(const String &filter, const int filter_index, String &filename, const String &default_extension, const bool create_prompt, const bool must_exists,
					const bool show_hidden, const bool hide_readonly, const bool no_network, const bool overwrite_prompt) override;
				bool Font(String &name, int &height, FontWeight &weight, bool &italic, bool &underline, bool &strikeout, nitisa::Color &color) override;
				bool Color(const bool any_color, const bool full_open, const bool prevent_full_open, const bool only_solid_colors, nitisa::Color &color) override;
				bool PageSetup(const bool disable_margins, const bool disable_orientation, const bool disable_page_painting, const bool disable_paper, const bool no_network_button,
					const RectF &min_margins, String &device_name, RectF &margins, bool &landscape, PrintPaperSize &paper_size, float &paper_length, float &paper_width, float &scale, int &copies,
					PrintPaperSource &paper_source, PrintQuality &print_quality, bool &monochrome, PrintDuplex &duplex, PrintTTOption &tt_option, bool &collate, PrintMediaType &media_type,
					PrintDitherType &dither_type, PointF &size) override;
				PrintDialogResult Print(const bool select_collate, const bool select_current_page, const bool disable_print_to_file, const bool hide_print_to_file, const bool disable_current_page,
					const bool no_page_nums, const bool no_selection, const bool select_page_nums, const bool select_print_to_file, const bool select_selection, const int min_page,
					const int max_page, const int max_page_range_count, int &page_range_count, Point *page_ranges, int &copies, String &device_name, bool &landscape,
					PrintPaperSize &paper_size, float &paper_length, float &paper_width, float &scale, PrintPaperSource &paper_source, PrintQuality &print_quality, bool &monochrome,
					PrintDuplex &duplex, PrintTTOption &tt_option, bool &collate, PrintMediaType &media_type, PrintDitherType &dither_type, void **handle) override;
				bool BrowseFolder(String &folder, const String &title, const bool only_file_system, const bool no_network, const bool only_ancestors, const bool show_edit_box, const bool new_style,
					const bool show_hint, const bool hide_new_folder, const bool dont_translate_targets, const bool only_computers, const bool only_printers, const bool show_files,
					const bool show_shareable) override;
			};
		}
	}
}
#endif
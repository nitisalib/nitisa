// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#if defined(__linux__) && !defined(__ANDROID__)
#include "Nitisa/Core/Form.h"
#include "Nitisa/Core/ModalResult.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Image.h"
#include "Nitisa/Interfaces/IDialogs.h"
#include "Nitisa/Math/RectF.h"

#ifdef linux
#undef linux
#endif

namespace nitisa
{
	class IForm;

	namespace standard
	{
		class CButton;
		class CContainer;
		class CLabel;
		class CImage;
	}

	namespace platform
	{
		namespace linux
		{
			class CApplication;

			class CDialogs :public virtual IDialogs
			{
			private:
				class CFormDialog :public CForm
				{
				private:
					standard::CImage *m_pImage;
					standard::CLabel *m_pLabel;
					standard::CButton *m_pButtonOk;
					standard::CButton *m_pButtonNo;
					standard::CButton *m_pButtonCancel;
					standard::CContainer *m_pContainerButtons;
					standard::CContainer *m_pContainerImage;
					standard::CContainer *m_pContainerMessage;

					size_t SearchWordEnd(const String &message, const size_t start);
				public:
					CFormDialog(IForm *active_form, const String &message, const String &caption, const Image &bmp, const bool confirmation);
				};
			private:
				CApplication * m_pApplication;

				IForm *CreateDialog(const String &message, const String &caption, const Image &bmp, const bool confirmation);
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
					const bool hide_readonly, const bool no_network) override; // Not implemented. Return false
				bool Save(const String &filter, const int filter_index, String &filename, const String &default_extension, const bool create_prompt, const bool must_exists,
					const bool show_hidden, const bool hide_readonly, const bool no_network, const bool overwrite_prompt) override; // Not implemented. Return false
				bool Font(String &name, int &height, FontWeight &weight, bool &italic, bool &underline, bool &strikeout, nitisa::Color &color) override; // Not supported. Return false
				bool Color(const bool any_color, const bool full_open, const bool prevent_full_open, const bool only_solid_colors, nitisa::Color &color) override; // Not implemented. Return false
				bool PageSetup(const bool disable_margins, const bool disable_orientation, const bool disable_page_painting, const bool disable_paper, const bool no_network_button,
					const RectF &min_margins, String &device_name, RectF &margins, bool &landscape, PrintPaperSize &paper_size, float &paper_length, float &paper_width, float &scale, int &copies,
					PrintPaperSource &paper_source, PrintQuality &print_quality, bool &monochrome, PrintDuplex &duplex, PrintTTOption &tt_option, bool &collate, PrintMediaType &media_type,
					PrintDitherType &dither_type, PointF &size) override; // Not supported. Return false
				PrintDialogResult Print(const bool select_collate, const bool select_current_page, const bool disable_print_to_file, const bool hide_print_to_file, const bool disable_current_page,
					const bool no_page_nums, const bool no_selection, const bool select_page_nums, const bool select_print_to_file, const bool select_selection, const int min_page,
					const int max_page, const int max_page_range_count, int &page_range_count, Point *page_ranges, int &copies, String &device_name, bool &landscape,
					PrintPaperSize &paper_size, float &paper_length, float &paper_width, float &scale, PrintPaperSource &paper_source, PrintQuality &print_quality, bool &monochrome,
					PrintDuplex &duplex, PrintTTOption &tt_option, bool &collate, PrintMediaType &media_type, PrintDitherType &dither_type, void **handle) override; // Not supported. Return false
				bool BrowseFolder(String &folder, const String &title, const bool only_file_system, const bool no_network, const bool only_ancestors, const bool show_edit_box, const bool new_style,
					const bool show_hint, const bool hide_new_folder, const bool dont_translate_targets, const bool only_computers, const bool only_printers, const bool show_files,
					const bool show_shareable) override; // Not implemented. Return false

				CDialogs(CApplication *application);
			};
		}
	}
}
#endif
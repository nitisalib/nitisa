// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Math/Point.h"
#include "Strings.h"
#include "WindowPosition.h"
#include "WindowState.h"

namespace nitisa
{
	struct CreateParams // Creation parameters
	{
		// Style
		bool HasBorder;					// false
		bool HasCaption;				// true
		bool IsChild;					// false
		bool IsClipChildren;			// false
		bool IsEnabled;					// true
		bool HasDialogFrame;			// false
		bool HasHorizontalScroll;		// false
		bool HasVerticalScroll;			// false
		bool HasMaximizeBox;			// true
		bool HasMinimizeBox;			// true
		bool HasSizeBox;				// true
		bool HasSystemMenu;				// true
		bool IsPopup;					// false
		bool IsTabStop;					// false
		// StyleEx
		bool IsAcceptFiles;				// false
		bool IsApplicationWindow;		// false
		bool HasClientEdge;				// true
		bool HasContextHelp;			// false
		bool HasDialogModalFrame;		// false
		bool IsMDIChild;				// false
		bool HasStaticEdge;				// false
		bool IsToolWindow;				// false
		bool IsTopMost;					// false
		bool HasWindowEdge;				// true
		// Other
		String Caption;					// "Window"
		Point Position;					// 0x80000000, 0x80000000
		Point Size;						// 1420, 720
		WindowState State;				// Normal
		nitisa::WindowPosition WindowPosition;	// Custom

		CreateParams(); // Create with default values specified in comments above
		CreateParams( // Create with specified values
			const bool has_border,
			const bool has_caption,
			const bool is_child,
			const bool is_clip_children,
			const bool is_enabled,
			const bool has_dialog_frame,
			const bool has_horizontal_scroll,
			const bool has_vertical_scroll,
			const bool has_maximize_box,
			const bool has_minimize_box,
			const bool has_size_box,
			const bool has_system_menu,
			const bool is_popup,
			const bool is_tab_stop,
			const bool is_accept_files,
			const bool is_application_window,
			const bool has_client_edge,
			const bool has_context_help,
			const bool has_dialog_modal_frame,
			const bool is_mdi_child,
			const bool has_static_edge,
			const bool is_tool_window,
			const bool is_top_most,
			const bool has_window_edge,
			const String &caption,
			const Point &position,
			const Point &size,
			const WindowState state,
			const nitisa::WindowPosition window_position
		);
		CreateParams(const CreateParams &other) = default;
		CreateParams(CreateParams &&other) = default;

		bool operator==(const CreateParams &other) const; // Check if it is equal with other structure
		bool operator!=(const CreateParams &other) const; // Check if it is not equal with other structure
		CreateParams &operator=(const CreateParams &other) = default;
		CreateParams &operator=(CreateParams &&other) = default;
	};
}
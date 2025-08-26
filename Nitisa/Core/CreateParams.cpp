// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	CreateParams::CreateParams() :
		HasBorder{ false },
		HasCaption{ true },
		IsChild{ false },
		IsClipChildren{ false },
		IsEnabled{ true },
		HasDialogFrame{ false },
		HasHorizontalScroll{ false },
		HasVerticalScroll{ false },
		HasMaximizeBox{ true },
		HasMinimizeBox{ true },
		HasSizeBox{ true },
		HasSystemMenu{ true },
		IsPopup{ false },
		IsTabStop{ false },
		IsAcceptFiles{ false },
		IsApplicationWindow{ false },
		HasClientEdge{ true },
		HasContextHelp{ false },
		HasDialogModalFrame{ false },
		IsMDIChild{ false },
		HasStaticEdge{ false },
		IsToolWindow{ false },
		IsTopMost{ false },
		HasWindowEdge{ true },
		Caption{ L"Window" },
		Position{ (int)0x80000000, (int)0x80000000 },
		Size{ 1420, 720 },
		State{ WindowState::Normal },
		WindowPosition{ WindowPosition::Custom }
	{

	}

	CreateParams::CreateParams(
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
		const nitisa::WindowPosition window_position)
		:
	HasBorder{ has_border },
		HasCaption{ has_caption },
		IsChild{ is_child },
		IsClipChildren{ is_clip_children },
		IsEnabled{ is_enabled },
		HasDialogFrame{ has_dialog_frame },
		HasHorizontalScroll{ has_horizontal_scroll },
		HasVerticalScroll{ has_vertical_scroll },
		HasMaximizeBox{ has_maximize_box },
		HasMinimizeBox{ has_minimize_box },
		HasSizeBox{ has_size_box },
		HasSystemMenu{ has_system_menu },
		IsPopup{ is_popup },
		IsTabStop{ is_tab_stop },
		IsAcceptFiles{ is_accept_files },
		IsApplicationWindow{ is_application_window },
		HasClientEdge{ has_client_edge },
		HasContextHelp{ has_context_help },
		HasDialogModalFrame{ has_dialog_modal_frame },
		IsMDIChild{ is_mdi_child },
		HasStaticEdge{ has_static_edge },
		IsToolWindow{ is_tool_window },
		IsTopMost{ is_top_most },
		HasWindowEdge{ has_window_edge },
		Caption{ caption },
		Position{ position },
		Size{ size },
		State{ state },
		WindowPosition{ window_position }
	{

	}

	bool CreateParams::operator==(const CreateParams &other) const
	{
		return
			HasBorder == other.HasBorder &&
			HasCaption == other.HasCaption &&
			IsChild == other.IsChild &&
			IsClipChildren == other.IsClipChildren &&
			IsEnabled == other.IsEnabled &&
			HasDialogFrame == other.HasDialogFrame &&
			HasHorizontalScroll == other.HasHorizontalScroll &&
			HasVerticalScroll == other.HasVerticalScroll &&
			HasMaximizeBox == other.HasMaximizeBox &&
			HasMinimizeBox == other.HasMinimizeBox &&
			HasSizeBox == other.HasSizeBox &&
			HasSystemMenu == other.HasSystemMenu &&
			IsPopup == other.IsPopup &&
			IsTabStop == other.IsTabStop &&
			IsAcceptFiles == other.IsAcceptFiles &&
			IsApplicationWindow == other.IsApplicationWindow &&
			HasClientEdge == other.HasClientEdge &&
			HasContextHelp == other.HasContextHelp &&
			HasDialogModalFrame == other.HasDialogModalFrame &&
			IsMDIChild == other.IsMDIChild &&
			HasStaticEdge == other.HasStaticEdge &&
			IsToolWindow == other.IsToolWindow &&
			IsTopMost == other.IsTopMost &&
			HasWindowEdge == other.HasWindowEdge &&
			Caption == other.Caption &&
			Position == other.Position &&
			Size == other.Size &&
			State == other.State &&
			WindowPosition == other.WindowPosition;
	}

	bool CreateParams::operator!=(const CreateParams &other) const
	{
		return
			HasBorder != other.HasBorder ||
			HasCaption != other.HasCaption ||
			IsChild != other.IsChild ||
			IsClipChildren != other.IsClipChildren ||
			IsEnabled != other.IsEnabled ||
			HasDialogFrame != other.HasDialogFrame ||
			HasHorizontalScroll != other.HasHorizontalScroll ||
			HasVerticalScroll != other.HasVerticalScroll ||
			HasMaximizeBox != other.HasMaximizeBox ||
			HasMinimizeBox != other.HasMinimizeBox ||
			HasSizeBox != other.HasSizeBox ||
			HasSystemMenu != other.HasSystemMenu ||
			IsPopup != other.IsPopup ||
			IsTabStop != other.IsTabStop ||
			IsAcceptFiles != other.IsAcceptFiles ||
			IsApplicationWindow != other.IsApplicationWindow ||
			HasClientEdge != other.HasClientEdge ||
			HasContextHelp != other.HasContextHelp ||
			HasDialogModalFrame != other.HasDialogModalFrame ||
			IsMDIChild != other.IsMDIChild ||
			HasStaticEdge != other.HasStaticEdge ||
			IsToolWindow != other.IsToolWindow ||
			IsTopMost != other.IsTopMost ||
			HasWindowEdge != other.HasWindowEdge ||
			Caption != other.Caption ||
			Position != other.Position ||
			Size != other.Size ||
			State != other.State ||
			WindowPosition != other.WindowPosition;
	}
}
// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Math/PointF.h"
#include "../Math/Rect.h"
#include "../Math/RectF.h"
#include "EdgeType.h"
#include "FocusedBy.h"
#include "Key.h"
#include "ScrollType.h"
#include "Strings.h"
#include "TouchPoint.h"

namespace nitisa
{
	class IControl;

	struct MessagePosition
	{
		PointF Position; // Position
	};

	struct MessageMouse
	{
		PointF Position; // Position
		bool Ctrl; // Ctrl down state
		bool Alt; // Alt/Menu down state
		bool Shift; // Shift down state
		bool Left; // Left mouse button down state
		bool Middle; // Middle mouse button down state
		bool Right; // Right mouse button down state
		IControl *Target; // The control where event appears
	};

	struct MessageMouseWheel
	{
		PointF Position;
		bool Ctrl; // Ctrl down state
		bool Alt; // Alt/Menu down state
		bool Shift; // Shift down state
		bool Left; // Left mouse button down state
		bool Middle; // Middle mouse button down state
		bool Right; // Right mouse button down state
		int Delta; // Scroll value
		IControl *Target; // The control where event appears
	};

	struct MessageKey
	{
		nitisa::Key Key; // Key
		IControl *Target; // The control where event appears
	};

	struct MessageChar
	{
		wchar_t Char; // Character
		IControl *Target; // The control where event appears
	};

	struct MessageSize
	{
		PointF Size; // Size
	};

	struct MessageRect
	{
		RectF Rect; // Rectangle
	};

	struct MessageEndSession
	{
		bool Ending; // Whether is ending
	};

	struct MessageDropFiles
	{
		PointF Position; // Position
		StringArray FileNames; // Names of files
		IControl *Target; // The control where event appears
	};

	struct MessageTouch
	{
		std::vector<TouchPoint> Points; // Touch points
	};

	struct MessageWindowActivate
	{
		bool ByClick; // Whether by clicking or not
	};

	struct MessageWindowResizing
	{
		nitisa::Rect Rect; // Rectangle
		EdgeType Edge; // Edge
	};

	struct MessageWindowScroll
	{
		nitisa::ScrollType ScrollType; // Scrolling request
		int ScrollValue; // Scroll value
	};

	struct MessagePaint
	{
		nitisa::Rect Rect; // Repainting rectangle
		bool LastPass; // Whether it is first or last drawing loop
	};

	struct MessageHotkey
	{
		nitisa::Key Key; // Key
		bool Ctrl; // Ctrl down state
		bool Alt; // Alt/Menu down state
		bool Shift; // Shift down state
		bool Down; // Down or release
	};

	struct MessageFocus
	{
		IControl *OldFocusedControl; // Old focused control
		nitisa::FocusedBy FocusedBy; // How has been focused
	};

	struct MessagePasteString
	{
		String Text; // Text to insert
	};
}
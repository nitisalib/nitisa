// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/CursorType.h"
#include "../Core/Key.h"
#include "../Core/Strings.h"
#include "../Math/Mat4f.h"
#include "../Math/Point.h"
#include "../Math/PointF.h"
#include "../Math/RectF.h"
#include "IClass.h"

namespace nitisa
{
	class IBuiltInControlListener;
	class IControl;
	class IStyle;

	struct Block;
	
	// Control methods should be accessed only by owner control. They are not designed to be accessed directly
	class IBuiltInControl : public virtual IClass
	{
	protected:
		IBuiltInControl() = default;
		~IBuiltInControl() = default;
		IBuiltInControl(const IBuiltInControl &other) = delete;
		IBuiltInControl(IBuiltInControl &&other) = delete;
		IBuiltInControl &operator=(const IBuiltInControl &other) = delete;
		IBuiltInControl &operator=(IBuiltInControl &&other) = delete;
	public:
		virtual IControl *getControl() = 0; // Return parent control. Should be implemented by parent. Might be empty. Should be used for accessing only general properties and methods like: get font/style/renderer/caret/interpolation/..., create/delete timer, add/remove hotkeys

		virtual IBuiltInControlListener *getListener() = 0; // Return associated listener
		virtual bool isEnabled() = 0; // Whether control is enabled
		virtual bool isHovered() = 0; // Whether control is hovered
		virtual bool isFocused() = 0; // Whether control is focused
		virtual bool isInside(const PointF &position) = 0; // Return whether specified point(in this control coordinates) is over control area or not
		virtual PointF getSize() = 0; // Return size
		virtual float getWidth() = 0; // Return width
		virtual float getHeight() = 0; // Return height
		virtual RectF getRect() = 0; // Return rectangle
		virtual PointF getPosition() = 0; // Return position
		virtual float getLeft() = 0; // Return X coordinate
		virtual float getTop() = 0; // Return Y coordinate
		virtual RectF getClientRect() = 0; // Return client rectangle
		virtual RectF getRenderRect() = 0; // Return render rectangle
		virtual CursorType getCursor(const PointF &position, const CursorType def) = 0; // Return cursor depending on position
		virtual Point getDPI() = 0; // Return DPI for which the control is adjusted
		virtual bool isDown() = 0; // Return whether the control acquired a mouse button state

		virtual void setListener(IBuiltInControlListener *value) = 0; // Set listener
		virtual bool setEnabled(const bool value) = 0; // Set whether control is enabled
		virtual bool setFocused(const bool value) = 0; // Set whether control is focused
		virtual bool setSize(const PointF &value) = 0; // Set size
		virtual bool setPosition(const PointF &value) = 0; // Set position
		virtual bool setDPI(const Point &value) = 0; // Adjust parameters to specified DPI. Default DPI is { 96, 96 }

		virtual void UpdateFromStyle(IStyle *style, const String &class_name) = 0; // Update properties from specified style using specified class name
		virtual void Render(const bool last_pass, const Mat4f &matrix, const Block *block) = 0; // Draw
		virtual void Update() = 0; // Force to update all
		virtual void Release() = 0; // Destroy
		virtual void Refresh() = 0; // Clear internal canvas(drawing buffer) if used

		// State change notifications
		virtual void NotifyOnAttach() = 0; // Parent control is attached to form or another control
		virtual void NotifyOnDeactivate() = 0; // Parent control become not active
		virtual void NotifyOnFreeResources() = 0; // Free resources

		// Mouse input notifications. Specified position is in this control coordinates
		virtual bool NotifyOnMouseHover(const PointF &position) = 0; // Notify about hovering by mouse pointer
		virtual bool NotifyOnMouseLeave() = 0; // Notify when mouse pointer leaves the control
		virtual bool NotifyOnMouseMove(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) = 0; // Notify about mouse movement
		virtual bool NotifyOnMouseLeftDown(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) = 0; // Notify about left mouse button down
		virtual bool NotifyOnMouseLeftUp(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) = 0; // Notify about left mouse button release
		virtual bool NotifyOnMouseLeftDoubleClick(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) = 0; // Notify about left mouse button double click
		virtual bool NotifyOnMouseMiddleDown(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift) = 0; // Notify about middle mouse button down
		virtual bool NotifyOnMouseMiddleUp(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift) = 0; // Notify about middle mouse button release
		virtual bool NotifyOnMouseMiddleDoubleClick(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift) = 0; // Notify about middle mouse button double click
		virtual bool NotifyOnMouseRightDown(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift) = 0; // Notify about right mouse button down
		virtual bool NotifyOnMouseRightUp(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift) = 0; // Notify about right mouse button release
		virtual bool NotifyOnMouseRightDoubleClick(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift) = 0; // Notify about right mouse button double click
		virtual void NotifyOnMouseDownCancel() = 0; // Cancel any work done on mouse down
		virtual bool NotifyOnMouseVerticalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta) = 0; // Notify about mouse vertical wheel scrolling
		virtual bool NotifyOnMouseHorizontalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta) = 0; // Notify about mouse horizontal wheel scrolling

		// Keyboard input notifications
		virtual bool NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock) = 0; // Notify about keyboard key down
		virtual bool NotifyOnKeyUp(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock) = 0; // Notify about keyboard key release
		virtual bool NotifyOnChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock) = 0; // Notify about receiving character via keyboard input
		virtual bool NotifyOnDeadChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock) = 0; // Notify about receiving combined character via keyboard input(like umlaut-O)

		// Other input notifications
		virtual bool NotifyOnDropFiles(const PointF &position, const StringArray &filenames) = 0; // Notify about dropping files on the control
		virtual bool NotifyOnPasteString(const String &text) = 0; // Notify about pasting a string
	};
}
// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "../Core/TextAlign.h"
#include "../Interfaces/IBuiltInControl.h"
#include "../Math/Point.h"

namespace nitisa
{
	class IBuiltInTextInput :public virtual IBuiltInControl
	{
	protected:
		IBuiltInTextInput() = default;
		~IBuiltInTextInput() = default;
		IBuiltInTextInput(const IBuiltInTextInput &other) = delete;
		IBuiltInTextInput(IBuiltInTextInput &&other) = delete;
		IBuiltInTextInput &operator=(const IBuiltInTextInput &other) = delete;
		IBuiltInTextInput &operator=(IBuiltInTextInput &&other) = delete;
	public:
		virtual String getText() = 0; // Return text
		virtual String getSelectedText() = 0; // Return selected part of the text
		virtual Point getSelection() = 0; // Return selection
		virtual int getCaretPosition() = 0; // Return caret position(in character index)
		virtual float getScroll() = 0; // Return scroll
		virtual int getMaxLength() = 0; // Return maximum allowed length of the text
		virtual int getUndoLimitCount() = 0; // Return maximum allowed undo count
		virtual int getUndoLimitSize() = 0; // Return maximum allowed memory to be used to store text changes history
		virtual bool canUndo() = 0; // Whether undo operation is possible
		virtual bool canRedo() = 0; // Whether redo operation is possible
		virtual TextAlign getAlign() = 0; // Return text horizontal alignment
		virtual bool isMoving() = 0; // Whether mouse button was down inside selection
		virtual bool hasSelection() = 0; // Return whether there is selected text

		virtual bool setText(const String &value) = 0; // Set text
		virtual bool setSelection(const Point &value) = 0; // Set selection
		virtual bool setCaretPosition(const int value) = 0; // Set caret position
		virtual bool setScroll(const float value) = 0; // Set scroll
		virtual bool setMaxLength(const int value) = 0; // Set maximum allowed length of the text
		virtual bool setUndoLimitCount(const int value) = 0; // Set maximum allowed undo operations
		virtual bool setUndoLimitSize(const int value) = 0; // Set maximum allowed size of memory used to store text changes history
		virtual bool setAlign(const TextAlign value) = 0; // Set text horizontal alignment

		virtual bool DeleteSelection() = 0; // Delete selected text
		virtual bool DeleteCharBeforeCaret() = 0; // Delete 1 charachet before caret
		virtual bool DeleteCharAfterCaret() = 0; // Delete 1 character after caret
		virtual bool DeleteWordBeforeCaret() = 0; // Delete word before caret
		virtual bool DeleteWordAfterCaret() = 0; // Delete word after caret
		virtual bool DeleteAllBeforeCaret() = 0; // Delete all up to text start before caret
		virtual bool DeleteAllAfterCaret() = 0; // Delete all up to text length after caret
		virtual bool MoveCaretLeft(const bool select) = 0; // Move caret 1 character left and optionally select it
		virtual bool MoveCaretRight(const bool select) = 0; // Move caret 1 character right and optinally select it
		virtual bool MoveCaretWordLeft(const bool select) = 0; // Move caret word left and optionally select it
		virtual bool MoveCaretWordRight(const bool select) = 0; // Move caret word right and optionally select it
		virtual bool MoveCaretStart(const bool select) = 0; // Move caret to text start and optionally select text
		virtual bool MoveCaretEnd(const bool select) = 0; // Move caret to text end and optionally select text
		virtual bool Undo(bool &text_changed) = 0; // Undo last change
		virtual bool Redo(bool &text_changed) = 0; // Redo last change
		virtual bool Insert(const wchar_t chr) = 0; // Insert character at current caret position. Selection will be deleted
		virtual bool Insert(const String &str) = 0; // Insert string at current caret position. Selection will be deleted
		virtual bool Replace(const wchar_t chr) = 0; // Replace selection with specified character 
		virtual bool Replace(const String &str) = 0; // Replace selection with specifed string
		virtual bool MoveSelection(const int dst_caret_pos) = 0; // Move selection to specified position
		virtual bool CopySelection(const int dst_caret_pos) = 0; // Copy selection to specified position
		virtual bool Copy() = 0; // Copy selection to clipboard
		virtual bool Cut() = 0; // Cut selection to cipboard
		virtual bool Paste() = 0; // Paste from clipboard at current caret position. Selection will be deleted
		virtual bool ScrollToCaret() = 0; // Scroll to current caret position
		virtual bool SelectAll() = 0; // Select all text
		virtual bool DeselectAll() = 0; // Any selected text become unselected
	};
}
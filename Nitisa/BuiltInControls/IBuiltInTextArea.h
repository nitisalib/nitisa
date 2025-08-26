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
#include "../Math/PointB.h"
#include "../Math/PointF.h"

namespace nitisa
{
	class IBuiltInTextArea :public virtual IBuiltInControl
	{
	protected:
		IBuiltInTextArea() = default;
		~IBuiltInTextArea() = default;
		IBuiltInTextArea(const IBuiltInTextArea &other) = delete;
		IBuiltInTextArea(IBuiltInTextArea &&other) = delete;
		IBuiltInTextArea &operator=(const IBuiltInTextArea &other) = delete;
		IBuiltInTextArea &operator=(IBuiltInTextArea &&other) = delete;
	public:
		virtual String getText() = 0; // Return text
		virtual String getSelectedText() = 0; // Return selected part of the text
		virtual Point getSelection() = 0; // Return selection start and end
		virtual int getCaretPosition() = 0; // Return caret position(in character index)
		virtual PointF getScroll() = 0; // Return scroll
		virtual int getMaxLength() = 0; // Return maximum allowed length of the text
		virtual int getUndoLimitCount() = 0; // Return maximum allowed undo count
		virtual int getUndoLimitSize() = 0; // Return maximum allowed memory to be used to store text changes history
		virtual bool canUndo() = 0; // Whether undo operation is possible
		virtual bool canRedo() = 0; // Whether redo operation is possible
		virtual TextAlign getAlign() = 0; // Return text horizontal alignment
		virtual PointB getScrollRequired(const PointF &size) = 0; // Return whether scrollbars are required for specified size of the control
		virtual PointF getTextSize() = 0; // Return text size
		virtual PointF getXScrollRange() = 0; // Return range for the horizontal scroll
		virtual PointF getYScrollRange() = 0; // Return range for the vertical scroll
		virtual bool isWordWrap() = 0; // If true, text will be inside [0, width) area, if false long text will be out of the range
		virtual bool isWordBreak() = 0; // If true words will be breaked immediately, if false - only via separators between them or only if word too long to fit width of textarea
		virtual bool isMoving() = 0; // Whether mouse button was down inside selection
		virtual int getLineCount() = 0; // Return line count
		virtual String getLine(const int index) = 0; // Return line by index
		virtual bool hasSelection() = 0; // Return whether there is selected text

		virtual bool setText(String value) = 0; // Set text
		virtual bool setSelection(const Point &value) = 0; // Set selection
		virtual bool setCaretPosition(const int value) = 0; // Set caret position
		virtual bool setScroll(const PointF &value) = 0; // Set scroll
		virtual bool setMaxLength(const int value) = 0; // Set maximum allowed length of the text
		virtual bool setUndoLimitCount(const int value) = 0; // Set maximum allowed undo operations
		virtual bool setUndoLimitSize(const int value) = 0; // Set maximum allowed size of memory used to store text changes history
		virtual bool setAlign(const TextAlign value) = 0; // Set text horizontal alignment
		virtual bool setWordWrap(const bool value) = 0; // Set whether to wrap long lines
		virtual bool setWordBreak(const bool value) = 0; // Set how to break works in long lines
		virtual bool setLine(const int index, const String &value) = 0; // Set line by index

		virtual bool DeleteSelection() = 0; // Delete selected text
		virtual bool DeleteCharBeforeCaret() = 0; // Delete 1 charachet before caret
		virtual bool DeleteCharAfterCaret() = 0; // Delete 1 character after caret
		virtual bool DeleteWordBeforeCaret() = 0; // Delete word before caret
		virtual bool DeleteWordAfterCaret() = 0; // Delete word after caret
		virtual bool DeleteToLineStart() = 0; // Delete all to the beginning of line where caret is
		virtual bool DeleteToLineEnd() = 0; // Delete all to the end on line where caret is
		virtual bool DeleteAllBeforeCaret() = 0; // Delete all up to text start before caret
		virtual bool DeleteAllAfterCaret() = 0; // Delete all up to text length after caret
		virtual bool MoveCaretLeft(const bool select) = 0; // Move caret 1 character left and optionally select it
		virtual bool MoveCaretRight(const bool select) = 0; // Move caret 1 character right and optinally select it
		virtual bool MoveCaretWordLeft(const bool select) = 0; // Move caret word left and optionally select it
		virtual bool MoveCaretWordRight(const bool select) = 0; // Move caret word right and optionally select it
		virtual bool MoveCaretLineStart(const bool select) = 0; // Move caret to line start and optionally select text
		virtual bool MoveCaretLineEnd(const bool select) = 0; // Move caret to line end and optionally select text
		virtual bool MoveCaretLineUp(const bool select) = 0; // Move caret 1 line up and optionally select text
		virtual bool MoveCaretLineDown(const bool select) = 0; // Move caret 1 line down and optionally select text
		virtual bool MoveCaretPageStart(const bool select) = 0; // Move caret to page start and optionally select text
		virtual bool MoveCaretPageEnd(const bool select) = 0; // Move caret to page end and optionally select text
		virtual bool MoveCaretPageUp(const bool select) = 0; // Move cate 1 page up and optionally select text
		virtual bool MoveCaretPageDown(const bool select) = 0; // Move caret 1 page down and optionally select text
		virtual bool MoveCaretStart(const bool select) = 0; // Move caret to text start and optionally select text
		virtual bool MoveCaretEnd(const bool select) = 0; // Move caret to text end and optionally select text
		virtual bool Undo(bool &text_changed) = 0; // Undo last change
		virtual bool Redo(bool &text_changed) = 0; // Redo last change
		virtual bool Insert(const wchar_t chr) = 0; // Insert character at current caret position. Selection will be deleted
		virtual bool Insert(String str) = 0; // Insert string at current caret position. Selection will be deleted
		virtual bool Replace(const wchar_t chr) = 0; // Replace selection with specified character 
		virtual bool Replace(String str) = 0; // Replace selection with specifed string
		virtual bool MoveSelection(const int dst_caret_pos) = 0; // Move selection to specified position
		virtual bool CopySelection(const int dst_caret_pos) = 0; // Copy selection to specified position
		virtual bool ScrollToCaret() = 0; // Scroll to current caret position
		virtual bool ScrollLineUp() = 0; // Scroll 1 line up
		virtual bool ScrollLineDown() = 0; // Scroll 1 line down
		virtual bool Copy() = 0; // Copy selection to clipboard
		virtual bool Cut() = 0; // Cut selection to cipboard
		virtual bool Paste() = 0; // Paste from clipboard at current caret position. Selection will be deleted
		virtual bool SelectAll() = 0; // Select all text
		virtual bool DeselectAll() = 0; // Any selected text become unselected
		virtual bool AddLine(const String &text) = 0; // Add text to the end
		virtual bool DeleteLine(const int index) = 0; // Delete line by index
	};
}
// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Aliases.h"
#include "../../Core/BuiltInControl.h"
#include "../../Core/CursorType.h"
#include "../../Core/History.h"
#include "../../Core/Key.h"
#include "../../Core/Strings.h"
#include "../../Core/TextAlign.h"
#include "../../Image/Color.h"
#include "../../Interfaces/IFeedbackListener.h"
#include "../../Interfaces/ITimerListener.h"
#include "../../Math/Mat4f.h"
#include "../../Math/Point.h"
#include "../../Math/PointB.h"
#include "../../Math/PointF.h"
#include "../IBuiltInTextArea.h"

namespace nitisa
{
	class IBuiltInControlListener;
	class IPlatformFont;
	class IRenderer;
	class IStyle;
	class ITexture;

	struct Block;

	class CBuiltInTextArea :public virtual IBuiltInTextArea, public CBuiltInControl
	{
	public:
		enum class State // Possible states
		{
			Normal, // Normal
			Hovered, // Control is hovered
			Focused, // Control is focused
			FocusedHovered, // Control is focused and hovered
			Disabled // Control is disabled
		};
	private:
		struct History
		{
			String Text;
			Point Selection;
			int CaretPosition;
		};

		struct Line
		{
			String Text; // With \n at the end if exists
			StringArray FakeLines;
			float Width;
		};

		struct CaretPosition
		{
			int LineIndex;
			int FakeLineIndex;
			int Index;
		};

		struct TextPosition :public CaretPosition
		{
			PointF Position;
		};

		using Lines = std::vector<Line>;

		class CTimerListener :public virtual ITimerListener
		{
		private:
			CBuiltInTextArea *m_pControl;
		public:
			void NotifyOnTimer(const PlatformHandle id) override;

			CTimerListener(CBuiltInTextArea *control);
		};

		class CCaretListener :public virtual IFeedbackListener
		{
		private:
			CBuiltInTextArea *m_pControl;
		public:
			void NotifyOnChange() override;

			CCaretListener(CBuiltInTextArea *control);
		};
	private:
		CCaretListener m_cCaretListener;
		IBuiltInControlListener *m_pListener;
		int m_iMaxLength;
		PointF m_sScroll; // Scroll by X depends on alignment(left: <= 0(scroll from left border), right: >= 0(scroll from right border), center: can be >= & < 0(scroll from center))
		CHistory<History> m_cHistory;
		TextAlign m_eAlign;
		float m_fScrollInterval;
		bool m_bWordWrap;
		bool m_bWordBreak;
		Color m_aTextColor[(int)State::Disabled + 1];
		Color m_aShadowColor[(int)State::Disabled + 1];
		Color m_aSelectionBackgroundColor[(int)State::Disabled + 1];
		Color m_aSelectionTextColor[(int)State::Disabled + 1];
		Color m_aSelectionShadowColor[(int)State::Disabled + 1];
		PointF m_aShadowShift[(int)State::Disabled + 1];
		int m_aShadowRadius[(int)State::Disabled + 1];
		bool m_bReadOnly;
		bool m_bReplacing;
		bool m_bCopyByMouseEnabled;
		bool m_bMoveByMouseEnabled;
		bool m_bSelectWordByDoubleClickEnabled;
		bool m_bKeyLeftEnabled;
		bool m_bKeyRightEnabled;
		bool m_bKeyHomeEnabled;
		bool m_bKeyEndEnabled;
		bool m_bKeyDeleteEnabled;
		bool m_bKeyBackspaceEnabled;
		bool m_bKeyUpEnabled;
		bool m_bKeyDownEnabled;
		bool m_bKeyPageUpEnabled;
		bool m_bKeyPageDownEnabled;
		bool m_bSelectAllByKeyEnabled;
		bool m_bPasteByKeyEnabled;
		bool m_bCopyByKeyEnabled;
		bool m_bCutByKeyEnabled;
		bool m_bHistoryByKeyEnabled;
		bool m_bInsertReplaceChangeByKeyEnabled;
		bool m_bWordWrapChangeByKeyEnabled;
		int m_iCaretPosition; // In fake text
		Point m_sSelection; // In fake text. Last position is not included
		String m_sText;
		Lines m_aLines;

		PointF m_sTextSize;
		int m_iMaxCaretPosition;
		PlatformHandle m_hTimer;
		bool m_bMouseDown;
		bool m_bMoveSelection;
		PointF m_sMousePosition;
		int m_iMouseDownCaretPosition;
		bool m_bHovered;
		CTimerListener m_cTimerListener;
		
		IPlatformFont *getPlatformFont(float &line_height, float &space_width);
		void BuildLines(const String &text, Lines &lines);
		void BuildFakeLines(Line &line, IPlatformFont *pf, const float distance, const float control_width, const float space_width);
		int FakeCaretToReal(const int value) const;
		int RealCaretToFake(const int value) const;
		TextPosition CalculateTextPosition(const int caret_fake, IPlatformFont *pf, const float distance, const float line_height, const float space_width);
		PointF CaretToClient(const int caret_fake, IPlatformFont *pf, const float line_height, const float space_width);
		CaretPosition FindCaretPosition(const int caret_fake);
		bool DeleteSelectionInternal(IPlatformFont *pf, const float distance, const float control_width, const float space_width, const float line_height);
		int CaretPositionToCaret(const CaretPosition &position);
		int FindBestPosition(const CaretPosition &current, const int line_index, const int fake_line_index);
		int HelperDeleteSelection(); // Return -1 if nothing was selected
		void HelperUpdateVars(const float line_height, const float space_width, const float control_width);
		bool HelperInsert(String str);
		void StoreHistory();
		bool ApplyLengthLimit(IPlatformFont *pf, const float space_width, const float distance, const float control_width);
		Point NormalizeSelection();
		int ClientToCaret(const PointF value);

		void RenderShadow(IRenderer *renderer, const State state, ITexture *clip, const float line_height, const float space_width, IPlatformFont *pf);
		void RenderText(IRenderer *renderer, const State state, const float line_height, const float space_width, IPlatformFont *pf);
		void RenderSelectionBackground(IRenderer *renderer, const State state, const float line_height, const float space_width, IPlatformFont *pf);
		void RenderSelectionShadow(IRenderer *renderer, const State state, ITexture *clip, const float line_height, const float space_width, IPlatformFont *pf);
		void RenderSelectionText(IRenderer *renderer, const State state, const float line_height, const float space_width, IPlatformFont *pf);
		void RenderCaret(const State state, IPlatformFont *pf, const float line_height, const float space_width);
	public:
		IBuiltInControlListener * getListener() override;
		bool isHovered() override;
		CursorType getCursor(const PointF &position, const CursorType def) override;
		bool isDown() override;
		bool hasSelection() override;

		void setListener(IBuiltInControlListener *value) override;
		bool setFocused(const bool value) override;
		bool setEnabled(const bool value) override;
		bool setSize(const PointF &value) override;
		bool setDPI(const Point &value) override;

		void UpdateFromStyle(IStyle *style, const String &class_name) override;
		void Render(const bool last_pass, const Mat4f &matrix, const Block *block) override;
		void Update() override;

		// State change notifications
		void NotifyOnAttach() override;
		void NotifyOnDeactivate() override;
		void NotifyOnFreeResources() override;

		// Mouse input notifications
		bool NotifyOnMouseHover(const PointF &position) override;
		bool NotifyOnMouseLeave() override;
		bool NotifyOnMouseMove(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseLeftDown(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseLeftUp(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseLeftDoubleClick(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseMiddleDown(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseMiddleUp(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseMiddleDoubleClick(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseRightDown(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseRightUp(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseRightDoubleClick(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift) override;
		void NotifyOnMouseDownCancel() override;
		bool NotifyOnMouseVerticalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta) override;
		bool NotifyOnMouseHorizontalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta) override;

		// Keyboard input notifications
		bool NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock) override;
		bool NotifyOnKeyUp(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock) override;
		bool NotifyOnChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock) override;
		bool NotifyOnDeadChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock) override;

		// Other input notifications
		bool NotifyOnDropFiles(const PointF &position, const StringArray &filenames) override;

		// Clipboard notifications
		bool NotifyOnPasteString(const String &text) override;

		String getText() override;
		String getSelectedText() override;
		Point getSelection() override;
		int getCaretPosition() override;
		PointF getScroll() override;
		int getMaxLength() override;
		int getUndoLimitCount() override;
		int getUndoLimitSize() override;
		bool canUndo() override;
		bool canRedo() override;
		TextAlign getAlign() override;
		PointB getScrollRequired(const PointF &size) override;
		PointF getTextSize() override;
		PointF getXScrollRange() override;
		PointF getYScrollRange() override;
		bool isWordWrap() override;
		bool isWordBreak() override;
		bool isMoving() override;
		int getLineCount() override;
		String getLine(const int index) override;

		bool setText(String value) override;
		bool setSelection(const Point &value) override;
		bool setCaretPosition(const int value) override;
		bool setScroll(const PointF &value) override;
		bool setMaxLength(const int value) override;
		bool setUndoLimitCount(const int value) override;
		bool setUndoLimitSize(const int value) override;
		bool setAlign(const TextAlign value) override;
		bool setWordWrap(const bool value) override;
		bool setWordBreak(const bool value) override;
		bool setLine(const int index, const String &value) override;

		bool DeleteSelection() override;
		bool DeleteCharBeforeCaret() override;
		bool DeleteCharAfterCaret() override;
		bool DeleteWordBeforeCaret() override;
		bool DeleteWordAfterCaret() override;
		bool DeleteToLineStart() override;
		bool DeleteToLineEnd() override;
		bool DeleteAllBeforeCaret() override;
		bool DeleteAllAfterCaret() override;
		bool MoveCaretLeft(const bool select) override;
		bool MoveCaretRight(const bool select) override;
		bool MoveCaretWordLeft(const bool select) override;
		bool MoveCaretWordRight(const bool select) override;
		bool MoveCaretLineStart(const bool select) override;
		bool MoveCaretLineEnd(const bool select) override;
		bool MoveCaretLineUp(const bool select) override;
		bool MoveCaretLineDown(const bool select) override;
		bool MoveCaretPageStart(const bool select) override;
		bool MoveCaretPageEnd(const bool select) override;
		bool MoveCaretPageUp(const bool select) override;
		bool MoveCaretPageDown(const bool select) override;
		bool MoveCaretStart(const bool select) override;
		bool MoveCaretEnd(const bool select) override;
		bool Undo(bool &text_changed) override;
		bool Redo(bool &text_changed) override;
		bool Insert(const wchar_t chr) override;
		bool Insert(String str) override;
		bool Replace(const wchar_t chr) override;
		bool Replace(String str) override;
		bool MoveSelection(const int dst_caret_pos) override;
		bool CopySelection(const int dst_caret_pos) override;
		bool ScrollToCaret() override;
		bool ScrollLineUp() override;
		bool ScrollLineDown() override;
		bool Copy() override;
		bool Cut() override;
		bool Paste() override;
		bool SelectAll() override;
		bool DeselectAll() override;
		bool AddLine(const String &text) override;
		bool DeleteLine(const int index) override;

		CBuiltInTextArea(); // Constructor

		bool isReadOnly() const; // Whether it is read only or not
		bool isReplacing() const; // Whether control is in replacing or adding mode
		bool isHovered() const; // Whether control is hovered
		float getScrollInterval() const; // Return scroll interval(in seconds)
		virtual State getState(); // Return current state
		Color getTextColor(const State state) const; // Return text color depending on state
		Color getShadowColor(const State state) const; // Return text shadow color depending on state
		Color getSelectionBackgroundColor(const State state) const; // Return selected text background color depending on state
		Color getSelectionTextColor(const State state) const; // Return selected text color depending on state
		Color getSelectionShadowColor(const State state) const; // Return selected text shadow color depending on state
		PointF getShadowShift(const State state) const; // Return shadow shift depending on state
		int getShadowRadius(const State state) const; // Return shadow blur radius depending on state
		bool isCopyByMouseEnabled() const; // Whether copy by mouse is enabled
		bool isMoveByMouseEnabled() const; // Whether move by mouse is enabled
		bool isSelectWordByDoubleClickEnabled() const; // Whether word selection by double click is enabled
		bool isKeyLeftEnabled() const; // Whether left key is enabled
		bool isKeyRightEnabled() const; // Whether right key is enabled
		bool isKeyHomeEnabled() const; // Whether home key is enabled
		bool isKeyEndEnabled() const; // Whether end key is enabled
		bool isKeyDeleteEnabled() const; // Whether delete key is enabled
		bool isKeyBackspaceEnabled() const; // Whether backspace key is enabled
		bool isKeyUpEnabled() const; // Whether up arrow key is enabled
		bool isKeyDownEnabled() const; // Whether down arrow key is enabled
		bool isKeyPageUpEnabled() const; // Whether PageUp key is enabled
		bool isKeyPageDownEnabled() const; // Whether PageDown key is enabled
		bool isSelectAllByKeyEnabled() const; // Whether Ctrl+A key combination is enabled
		bool isPasteByKeyEnabled() const; // Whether Ctrl+V key combination is enabled
		bool isCopyByKeyEnabled() const; // Whether Ctrl+C key combination is enabled
		bool isCutByKeyEnabled() const; // Whether Ctrl+X key combination is enabled
		bool isHistoryByKeyEnabled() const; // Whether Ctrl+Z and Ctrl+Shift+Z are enabled
		bool isInsertReplaceChangeByKeyEnabled() const; // Whether Insert key is enabled
		bool isWordWrapChangeByKeyEnabled() const; // Whether Ctrl+W key combination is enabled

		bool setReadOnly(const bool value); // Set whether control is read only or not
		bool setReplacing(const bool value); // Set replacing or adding mode
		bool setScrollInterval(const float value); // Set scroll interval(in seconds)
		bool setTextColor(const State state, const Color &value); // Set text color depending on state
		bool setShadowColor(const State state, const Color &value); // Set shadow color depending on state
		bool setSelectionBackgroundColor(const State state, const Color &value); // Set selected text background color depending on state
		bool setSelectionTextColor(const State state, const Color &value); // Set selected text color depending on state
		bool setSelectionShadowColor(const State state, const Color &value); // Set selected text shadow color depending on state
		bool setShadowShift(const State state, const PointF &value); // Set shadow shift depending on state
		bool setShadowRadius(const State state, const int value); // Set shadow blur radius depending on state
		bool setCopyByMouseEnabled(const bool value); // Set whether copy by mouse is enabled
		bool setMoveByMouseEnabled(const bool value); // Set whether move by mouse is enabled
		bool setSelectWordByDoubleClickEnabled(const bool value); // Set whether word selection by double click is enabled
		bool setKeyLeftEnabled(const bool value); // Set whether left key is enabled
		bool setKeyRightEnabled(const bool value); // Set whether right key is enabled
		bool setKeyHomeEnabled(const bool value); // Set whether home key is enabled
		bool setKeyEndEnabled(const bool value); // Set whether end key is enabled
		bool setKeyDeleteEnabled(const bool value); // Set whether delete key is enabled
		bool setKeyBackspaceEnabled(const bool value); // Set whether backspace key is enabled
		bool setKeyUpEnabled(const bool value); // Set whether up arrow key is enabled
		bool setKeyDownEnabled(const bool value); // Set whether down arrow key is enabled
		bool setKeyPageUpEnabled(const bool value); // Set whether PageUp key is enabled
		bool setKeyPageDownEnabled(const bool value); // Set whether PageDown key is enabled
		bool setSelectAllByKeyEnabled(const bool value); // Set whether Ctrl+A key combination is enabled
		bool setPasteByKeyEnabled(const bool value); // Set whether Ctrl+V key combination is enabled
		bool setCopyByKeyEnabled(const bool value); // Set whether Ctrl+C key combination is enabled
		bool setCutByKeyEnabled(const bool value); // Set whether Ctrl+X key combination is enabled
		bool setHistoryByKeyEnabled(const bool value); // Set whether Ctrl+Z and Ctrl+Shift+Z are enabled
		bool setInsertReplaceChangeByKeyEnabled(const bool value); // Set whether Insert key is enabled
		bool setWordWrapChangeByKeyEnabled(const bool value); // Set whether Ctrl+W key combination is enabled
	};
}
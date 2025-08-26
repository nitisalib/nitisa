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
#include "../../Core/Strings.h"
#include "../../Core/TextAlign.h"
#include "../../Image/Color.h"
#include "../../Interfaces/IFeedbackListener.h"
#include "../../Interfaces/ITimerListener.h"
#include "../../Math/Mat4f.h"
#include "../../Math/Point.h"
#include "../../Math/PointF.h"
#include "../IBuiltInTextInput.h"

namespace nitisa
{
	class IBuiltInControlListener;
	class IFont;
	class IRenderer;
	class IStyle;
	class ITexture;
	
	struct Block;

	class CBuiltInTextInput :public virtual IBuiltInTextInput, public CBuiltInControl
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

		class CTimerListener :public virtual ITimerListener
		{
		private:
			CBuiltInTextInput *m_pControl;
		public:
			void NotifyOnTimer(const PlatformHandle id) override;

			CTimerListener(CBuiltInTextInput *control);
		};

		class CCaretListener :public virtual IFeedbackListener
		{
		private:
			CBuiltInTextInput *m_pControl;
		public:
			void NotifyOnChange() override;

			CCaretListener(CBuiltInTextInput *control);
		};
	private:
		String m_sText;
		String m_sPlaceholder;
		Point m_sSelection; // Last position is not included
		int m_iCaretPosition;
		int m_iMaxLength;
		float m_fScroll;
		CHistory<History> m_cHistory;
		TextAlign m_eAlign;
		PlatformHandle m_hTimer;
		float m_fScrollInterval;
		bool m_bMouseDown;
		bool m_bMoveSelection;
		int m_iMouseDownCaretPosition;
		bool m_bReadOnly;
		bool m_bReplacing;
		bool m_bHovered;
		Color m_aTextColor[(int)State::Disabled + 1];
		Color m_aPlaceholderColor[(int)State::Disabled + 1];
		Color m_aShadowColor[(int)State::Disabled + 1];
		Color m_aSelectionBackgroundColor[(int)State::Disabled + 1];
		Color m_aSelectionTextColor[(int)State::Disabled + 1];
		Color m_aSelectionShadowColor[(int)State::Disabled + 1];
		PointF m_aShadowShift[(int)State::Disabled + 1];
		int m_aShadowRadius[(int)State::Disabled + 1];
		PointF m_sMousePosition;
		bool m_bCopyByMouseEnabled;
		bool m_bMoveByMouseEnabled;
		bool m_bSelectWordByDoubleClickEnabled;
		bool m_bKeyLeftEnabled;
		bool m_bKeyRightEnabled;
		bool m_bKeyHomeEnabled;
		bool m_bKeyEndEnabled;
		bool m_bKeyDeleteEnabled;
		bool m_bKeyBackspaceEnabled;
		bool m_bSelectAllByKeyEnabled;
		bool m_bPasteByKeyEnabled;
		bool m_bCopyByKeyEnabled;
		bool m_bCutByKeyEnabled;
		bool m_bHistoryByKeyEnabled;
		bool m_bInsertReplaceChangeByKeyEnabled;

		IBuiltInControlListener *m_pListener;
		CTimerListener m_cTimerListener;
		CCaretListener m_cCaretListener;

		void StoreHistory();
		bool ApplyLengthLimit();
		bool DeleteSelectionInternal();
		Point NormalizeSelection();
		float CaretToClient(const int value);
		int ClientToCaret(const float value);
		float CalculateTextX();
		float CalculateTextY();
		float CalculatePlaceholderX();
		float CalculatePlaceholderY();
		void RenderShadow(IRenderer *renderer, const State state, ITexture *clip, const Block *block, IFont *font);
		void RenderText(IRenderer *renderer, const State state, ITexture *clip, const Block *block, IFont *font);
		void RenderPlaceholder(IRenderer *renderer, const State state, ITexture *clip, const Block *block, IFont *font);
		void RenderSelection(IRenderer *renderer, const State state, ITexture *clip, const Block *block, IFont *font);
		void RenderCaret(IRenderer *renderer, const State state, ITexture *clip, const Block *block, IFont *font);
	public:
		IBuiltInControlListener *getListener() override;
		bool isHovered() override;
		CursorType getCursor(const PointF &position, const CursorType def) override;
		bool isDown() override;
		bool hasSelection() override;

		void setListener(IBuiltInControlListener *value) override;
		bool setFocused(const bool value) override;
		bool setEnabled(const bool value) override;
		bool setDPI(const Point &value) override;

		void UpdateFromStyle(IStyle *style, const String &class_name) override;
		void Render(const bool last_pass, const Mat4f &matrix, const Block *block) override;

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
		float getScroll() override;
		int getMaxLength() override;
		int getUndoLimitCount() override;
		int getUndoLimitSize() override;
		bool canUndo() override;
		bool canRedo() override;
		TextAlign getAlign() override;
		bool isMoving() override;

		bool setText(const String &value) override;
		bool setSelection(const Point &value) override;
		bool setCaretPosition(const int value) override;
		bool setScroll(const float value) override;
		bool setMaxLength(const int value) override;
		bool setUndoLimitCount(const int value) override;
		bool setUndoLimitSize(const int value) override;
		bool setAlign(const TextAlign value) override;

		bool DeleteSelection() override;
		bool DeleteCharBeforeCaret() override;
		bool DeleteCharAfterCaret() override;
		bool DeleteWordBeforeCaret() override;
		bool DeleteWordAfterCaret() override;
		bool DeleteAllBeforeCaret() override;
		bool DeleteAllAfterCaret() override;
		bool MoveCaretLeft(const bool select) override;
		bool MoveCaretRight(const bool select) override;
		bool MoveCaretWordLeft(const bool select) override;
		bool MoveCaretWordRight(const bool select) override;
		bool MoveCaretStart(const bool select) override;
		bool MoveCaretEnd(const bool select) override;
		bool Undo(bool &text_changed) override;
		bool Redo(bool &text_changed) override;
		bool Insert(const wchar_t chr) override;
		bool Insert(const String &str) override;
		bool Replace(const wchar_t chr) override;
		bool Replace(const String &str) override;
		bool MoveSelection(const int dst_caret_pos) override;
		bool CopySelection(const int dst_caret_pos) override;
		bool Copy() override;
		bool Cut() override;
		bool Paste() override;
		bool ScrollToCaret() override;
		bool SelectAll() override;
		bool DeselectAll() override;

		CBuiltInTextInput(); // Constructor

		String getPlaceholder() const; // Return placeholder
		bool isReadOnly() const; // Whether it is read only or not
		bool isReplacing() const; // Whether control is in replacing or adding mode
		float getScrollInterval() const; // Return scroll interval(in seconds)
		virtual State getState(); // Return current state
		Color getTextColor(const State state) const; // Return text color depending on state
		Color getPlaceholderColor(const State state) const; // Return placeholder color depending on state
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
		bool isSelectAllByKeyEnabled() const; // Whether Ctrl+A key combination is enabled
		bool isPasteByKeyEnabled() const; // Whether Ctrl+V key combination is enabled
		bool isCopyByKeyEnabled() const; // Whether Ctrl+C key combination is enabled
		bool isCutByKeyEnabled() const; // Whether Ctrl+X key combination is enabled
		bool isHistoryByKeyEnabled() const; // Whether Ctrl+Z and Ctrl+Shift+Z are enabled
		bool isInsertReplaceChangeByKeyEnabled() const; // Whether Insert key is enabled

		bool setPlaceholder(const String &value); // Set placeholder
		bool setReadOnly(const bool value); // Set whether control is read only or not
		bool setReplacing(const bool value); // Set replacing or adding mode
		bool setScrollInterval(const float value); // Set scroll interval(in seconds)
		bool setTextColor(const State state, const Color &value); // Set text color depending on state
		bool setPlaceholderColor(const State state, const Color &value); // Set placeholder color depending on state
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
		bool setSelectAllByKeyEnabled(const bool value); // Set whether Ctrl+A key combination is enabled
		bool setPasteByKeyEnabled(const bool value); // Set whether Ctrl+V key combination is enabled
		bool setCopyByKeyEnabled(const bool value); // Set whether Ctrl+C key combination is enabled
		bool setCutByKeyEnabled(const bool value); // Set whether Ctrl+X key combination is enabled
		bool setHistoryByKeyEnabled(const bool value); // Set whether Ctrl+Z and Ctrl+Shift+Z are enabled
		bool setInsertReplaceChangeByKeyEnabled(const bool value); // Set whether Insert key is enabled
	};
}
// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/Scroll/BuiltInScroll.h"
#include "Nitisa/BuiltInControls/TextArea/BuiltInTextArea.h"
#include "Nitisa/BuiltInControls/IBuiltInScrollListener.h"
#include "Nitisa/BuiltInControls/IBuiltInTextAreaListener.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Core/ScrollVisibility.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/TextAlign.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IMemo.h"
#include "MemoService.h"

namespace nitisa
{
	class IBuiltInControl;
	class IBuiltInScroll;
	class IBuiltInTextArea;
	class IControl;
	class ITexture;

	namespace standard
	{
		class CMemo :public virtual IMemo, public CControl
		{
			friend CMemoService;
		private:
			class CTextArea :public CBuiltInTextArea
			{
			private:
				CMemo *m_pMemo;
			public:
				CTextArea(CMemo *memo);

				IControl *getControl() override;
				State getState() override;
			};

			class CTextAreaListener :public virtual IBuiltInTextAreaListener
			{
			private:
				CMemo *m_pMemo;
			public:
				CTextAreaListener(CMemo *memo);

				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnTextChanged(IBuiltInControl *sender) override;
				void NotifyOnChanged(IBuiltInControl *sender) override;
			};

			class CScroll :public CBuiltInScroll
			{
			private:
				CMemo *m_pMemo;
			public:
				CScroll(CMemo *memo);

				IControl *getControl() override;
			};

			class CScrollListener :public virtual IBuiltInScrollListener
			{
			private:
				CMemo *m_pMemo;
			public:
				CScrollListener(CMemo *memo);

				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnScroll(IBuiltInControl *sender) override;
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CMemo *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CMemo *control);
			};
		private:
			CGradientListener m_cGradientListener;
			IBuiltInTextArea *m_pTextArea;
			IBuiltInScroll *m_pVScroll;
			IBuiltInScroll *m_pHScroll;
			ScrollVisibility m_eVerticalScrollType;
			ScrollVisibility m_eHorizontalScrollType;

			RectF m_sBorderWidth;
			RectF m_sBorderRadius;
			RectF m_sPadding;
			BorderColor m_aBorderColor[(int)CTextArea::State::Disabled + 1];
			Color m_aBackgroundColor[(int)CTextArea::State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)CTextArea::State::Disabled + 1];
			int m_aShadowRadius[(int)CTextArea::State::Disabled + 1];
			PointF m_aShadowShift[(int)CTextArea::State::Disabled + 1];
			Color m_aShadowColor[(int)CTextArea::State::Disabled + 1];
			Color m_aCornerColor[(int)CTextArea::State::Disabled + 1];

			bool m_bVScrollEnabled;
			bool m_bHScrollEnabled;
			bool m_bVScrollVisible;
			bool m_bHScrollVisible;
			PointF m_sTextAreaPosition;
			PointF m_sVScrollPosition;
			PointF m_sHScrollPosition;
			bool m_bIgnoreGradient;
			CMemoService::Element m_eMouseDownElement;
			CMemoService::Element m_eHoveredElement;
			ITexture *m_pCanvas;
			bool m_bTextChanged;
			CScrollListener m_cScrollListener;
			CTextAreaListener m_cTextAreaListener;

			IBuiltInTextArea *getTextArea();
			IBuiltInScroll *getVScroll();
			IBuiltInScroll *getHScroll();
			void UpdateFromStyle();
			void AdjustElements();
			void UpdateScrollPositions();
			RectF getRenderRect(const CTextArea::State state);
			void Render();
			void RenderTextArea(const RectF &rect, const PointF &disp);
			void RenderScrolls(const RectF &rect, const PointF &disp, const CTextArea::State state);
		public:
			void(*OnChange)(IControl *sender); // Event called when text changed

			// IControl methods
			void Refresh(const bool refresh_children) override;

			CMemo();
			CMemo(IControl *parent);
			CMemo(IForm *parent);
			~CMemo() override;

			// CControl getters
			RectF getClientRect() override; // Rectangle with text area and scrolls
			RectF getRenderRect() override;
			CursorType getCursor() override;
			String getText() override;

			bool setDPI(const Point &value) override;
			bool setText(const String &value) override;

			// ITextArea getters
			String getSelectedText();
			Point getSelection();
			int getCaretPosition();
			PointF getScroll();
			int getMaxLength();
			int getUndoLimitCount();
			int getUndoLimitSize();
			bool canUndo();
			bool canRedo();
			TextAlign getTextAlign();
			bool isWordWrap();
			bool isWordBreak();
			int getLineCount();
			String getLine(const int index);

			// CTextArea getters(works only if assocciated ITextInput is instance of CTextArea)
			bool isReadOnly();
			bool isReplacing();
			float getScrollInterval();
			CTextArea::State getState();
			Color getTextColor(const CTextArea::State state);
			Color getTextShadowColor(const CTextArea::State state);
			Color getSelectionBackgroundColor(const CTextArea::State state);
			Color getSelectionTextColor(const CTextArea::State state);
			Color getSelectionTextShadowColor(const CTextArea::State state);
			PointF getTextShadowShift(const CTextArea::State state);
			int getTextShadowRadius(const CTextArea::State state);
			bool isCopyByMouseEnabled();
			bool isMoveByMouseEnabled();
			bool isSelectWordByDoubleClickEnabled();
			bool isKeyLeftEnabled();
			bool isKeyRightEnabled();
			bool isKeyHomeEnabled();
			bool isKeyEndEnabled();
			bool isKeyDeleteEnabled();
			bool isKeyBackspaceEnabled();
			bool isKeyUpEnabled();
			bool isKeyDownEnabled();
			bool isKeyPageUpEnabled();
			bool isKeyPageDownEnabled();
			bool isSelectAllByKeyEnabled();
			bool isPasteByKeyEnabled();
			bool isCopyByKeyEnabled();
			bool isCutByKeyEnabled();
			bool isHistoryByKeyEnabled();
			bool isInsertReplaceChangeByKeyEnabled();
			bool isWordWrapChangeByKeyEnabled();

			// Return layout properties
			ScrollVisibility getVerticalScrollType() const;
			float getVerticalScroll();
			float getMinVerticalScroll();
			float getMaxVerticalScroll();
			ScrollVisibility getHorizontalScrollType() const;
			float getHorizontalScroll();
			float getMinHorizontalScroll();
			float getMaxHorizontalScroll();
			RectF getBorderWidth() const;
			float getLeftBorderWidth() const;
			float getTopBorderWidth() const;
			float getRightBorderWidth() const;
			float getBottomBorderWidth() const;
			RectF getBorderRadius() const;
			float getLeftBorderRadius() const;
			float getTopBorderRadius() const;
			float getRightBorderRadius() const;
			float getBottomBorderRadius() const;
			RectF getPadding() const;
			float getLeftPadding() const;
			float getTopPadding() const;
			float getRightPadding() const;
			float getBottomPadding() const;
			BorderColor getBorderColor(const CTextArea::State state) const;
			Color getLeftBorderColor(const CTextArea::State state) const;
			Color getTopBorderColor(const CTextArea::State state) const;
			Color getRightBorderColor(const CTextArea::State state) const;
			Color getBottomBorderColor(const CTextArea::State state) const;
			Color getBackgroundColor(const CTextArea::State state) const;
			Gradient *getBackgroundGradient(const CTextArea::State state);
			int getShadowRadius(const CTextArea::State state) const;
			PointF getShadowShift(const CTextArea::State state) const;
			Color getShadowColor(const CTextArea::State state) const;
			Color getCornerColor(const CTextArea::State state) const;

			// ITextArea setters
			bool setSelection(const Point &value);
			bool setCaretPosition(const int value);
			bool setScroll(const PointF &value);
			bool setMaxLength(const int value);
			bool setUndoLimitCount(const int value);
			bool setUndoLimitSize(const int value);
			bool setTextAlign(const TextAlign value);
			bool setWordWrap(const bool value);
			bool setWordBreak(const bool value);
			bool setLine(const int index, const String &value);

			// CTextArea setters(works only if assocciated ITextInput is instance of CTextArea)
			bool setReadOnly(const bool value);
			bool setReplacing(const bool value);
			bool setScrollInterval(const float value);
			bool setTextColor(const CTextArea::State state, const Color &value);
			bool setTextShadowColor(const CTextArea::State state, const Color &value);
			bool setSelectionBackgroundColor(const CTextArea::State state, const Color &value);
			bool setSelectionTextColor(const CTextArea::State state, const Color &value);
			bool setSelectionTextShadowColor(const CTextArea::State state, const Color &value);
			bool setTextShadowShift(const CTextArea::State state, const PointF &value);
			bool setTextShadowRadius(const CTextArea::State state, const int value);
			bool setCopyByMouseEnabled(const bool value);
			bool setMoveByMouseEnabled(const bool value);
			bool setSelectWordByDoubleClickEnabled(const bool value);
			bool setKeyLeftEnabled(const bool value);
			bool setKeyRightEnabled(const bool value);
			bool setKeyHomeEnabled(const bool value);
			bool setKeyEndEnabled(const bool value);
			bool setKeyDeleteEnabled(const bool value);
			bool setKeyBackspaceEnabled(const bool value);
			bool setKeyUpEnabled(const bool value);
			bool setKeyDownEnabled(const bool value);
			bool setKeyPageUpEnabled(const bool value);
			bool setKeyPageDownEnabled(const bool value);
			bool setSelectAllByKeyEnabled(const bool value);
			bool setPasteByKeyEnabled(const bool value);
			bool setCopyByKeyEnabled(const bool value);
			bool setCutByKeyEnabled(const bool value);
			bool setHistoryByKeyEnabled(const bool value);
			bool setInsertReplaceChangeByKeyEnabled(const bool value);
			bool setWordWrapChangeByKeyEnabled(const bool value);

			// Set layout properties
			bool setTextArea(IBuiltInTextArea *value);
			bool setVScroll(IBuiltInScroll *value);
			bool setHScroll(IBuiltInScroll *value);
			bool setVerticalScrollType(const ScrollVisibility value);
			bool setVerticalScroll(const float value);
			bool setHorizontalScrollType(const ScrollVisibility value);
			bool setHorizontalScroll(const float value);
			bool setBorderWidth(const RectF &value);
			bool setLeftBorderWidth(const float value);
			bool setTopBorderWidth(const float value);
			bool setRightBorderWidth(const float value);
			bool setBottomBorderWidth(const float value);
			bool setBorderRadius(const RectF &value);
			bool setLeftBorderRadius(const float value);
			bool setTopBorderRadius(const float value);
			bool setRightBorderRadius(const float value);
			bool setBottomBorderRadius(const float value);
			bool setPadding(const RectF &value);
			bool setLeftPadding(const float value);
			bool setTopPadding(const float value);
			bool setRightPadding(const float value);
			bool setBottomPadding(const float value);
			bool setBorderColor(const CTextArea::State state, const BorderColor &value);
			bool setLeftBorderColor(const CTextArea::State state, const Color &value);
			bool setTopBorderColor(const CTextArea::State state, const Color &value);
			bool setRightBorderColor(const CTextArea::State state, const Color &value);
			bool setBottomBorderColor(const CTextArea::State state, const Color &value);
			bool setBackgroundColor(const CTextArea::State state, const Color &value);
			bool setShadowRadius(const CTextArea::State state, const int value);
			bool setShadowShift(const CTextArea::State state, const PointF &value);
			bool setShadowColor(const CTextArea::State state, const Color &value);
			bool setCornerColor(const CTextArea::State state, const Color &value);

			// ITextInput action
			bool DeleteSelection();
			bool DeleteCharBeforeCaret();
			bool DeleteCharAfterCaret();
			bool DeleteWordBeforeCaret();
			bool DeleteWordAfterCaret();
			bool DeleteToLineStart();
			bool DeleteToLineEnd();
			bool DeleteAllBeforeCaret();
			bool DeleteAllAfterCaret();
			bool MoveCaretLeft(const bool select);
			bool MoveCaretRight(const bool select);
			bool MoveCaretWordLeft(const bool select);
			bool MoveCaretWordRight(const bool select);
			bool MoveCaretLineStart(const bool select);
			bool MoveCaretLineEnd(const bool select);
			bool MoveCaretLineUp(const bool select);
			bool MoveCaretLineDown(const bool select);
			bool MoveCaretPageStart(const bool select);
			bool MoveCaretPageEnd(const bool select);
			bool MoveCaretPageUp(const bool select);
			bool MoveCaretPageDown(const bool select);
			bool MoveCaretStart(const bool select);
			bool MoveCaretEnd(const bool select);
			bool Undo();
			bool Redo();
			bool Insert(const wchar_t chr);
			bool Insert(const String &str);
			bool Replace(const wchar_t chr);
			bool Replace(const String &str);
			bool MoveSelection(const int dst_caret_pos);
			bool CopySelection(const int dst_caret_pos);
			bool Copy();
			bool Cut();
			bool Paste();
			bool ScrollLineUp();
			bool ScrollLineDown();
			bool SelectAll();
			bool DeselectAll();
			bool AddLine(const String &text);
			bool DeleteLine(const int index);
		};
	}
}
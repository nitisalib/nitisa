// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/TextInput/BuiltInTextInput.h"
#include "Nitisa/BuiltInControls/IBuiltInTextInputListener.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/TextAlign.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "Nitisa/Modules/Script/ExpressionRunners/Generic/ExpressionRunner.h"
#include "../IEditCalc.h"

namespace nitisa
{
	class IBuiltInControl;
	class IBuiltInTextInput;
	class IControl;
	class IForm;
	class ITexture;

	namespace standard
	{
		class CEditCalc :public virtual IEditCalc, public CControl
		{
			friend class CEditCalcService;
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CEditCalc *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CEditCalc *control);
			};

			class CTextInput :public CBuiltInTextInput
			{
			private:
				CEditCalc *m_pControl;
			public:
				IControl *getControl() override;
				State getState() override;

				CTextInput(CEditCalc *control);
			};

			class CTextInputListener :public virtual IBuiltInTextInputListener
			{
			private:
				CEditCalc *m_pControl;
			public:
				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnTextChanged(IBuiltInControl *sender) override;

				CTextInputListener(CEditCalc *control);
			};
		private:
			CGradientListener m_cGradientListener;
			CTextInputListener m_cTextInputListener;
			bool m_bAutoCalculate;
			bool m_bCalculateOnReturn;
			IBuiltInTextInput *m_pTextInput;
			RectF m_sBorderWidth;
			RectF m_sBorderRadius;
			RectF m_sPadding;
			BorderColor m_aBorderColor[(int)CBuiltInTextInput::State::Disabled + 1];
			Color m_aBackgroundColor[(int)CBuiltInTextInput::State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)CBuiltInTextInput::State::Disabled + 1];
			int m_aShadowRadius[(int)CBuiltInTextInput::State::Disabled + 1];
			PointF m_aShadowShift[(int)CBuiltInTextInput::State::Disabled + 1];
			Color m_aShadowColor[(int)CBuiltInTextInput::State::Disabled + 1];

			bool m_bIgnoreGradient;
			ITexture *m_pCanvas;
			bool m_bTextChanged;
			script::generic::CExpressionRunner m_cExpressionRunner;

			// Helpers
			void UpdateFromStyle();
			void AdjustTextInputSize();
			IBuiltInTextInput *getTextInput();
			RectF getRenderRect(const CBuiltInTextInput::State state);
			// Render
			void Render();
		public:
			void(*OnChange)(IControl *sender); // Event called when text changed

			// IControl getters
			RectF getClientRect() override;
			RectF getRenderRect() override;
			CursorType getCursor() override;

			// IControl setters
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			// IEdit getters
			String getText() override;

			// IEdit setters
			bool setText(const String &value) override;

			// IEditCalc getters
			bool isAutoCalculate() override;
			bool isCalculateOnReturn() override;

			// IEditCalc setters
			bool setAutoCalculate(const bool value) override;
			bool setCalculateOnReturn(const bool value) override;

			// IEditCalc methods
			bool Calculate() override;

			CEditCalc();
			CEditCalc(IControl *parent);
			CEditCalc(IForm *parent);
			~CEditCalc() override;

			// ITextInput getters
			String getSelectedText();
			Point getSelection();
			int getCaretPosition();
			float getScroll();
			int getMaxLength();
			int getUndoLimitCount();
			int getUndoLimitSize();
			bool canUndo();
			bool canRedo();
			TextAlign getTextAlign();
			CBuiltInTextInput::State getState();

			// ITextInput setters
			bool setSelection(const Point &value);
			bool setCaretPosition(const int value);
			bool setScroll(const float value);
			bool setMaxLength(const int value);
			bool setUndoLimitCount(const int value);
			bool setUndoLimitSize(const int value);
			bool setTextAlign(const TextAlign value);

			// ITextInput actions
			bool DeleteSelection();
			bool DeleteCharBeforeCaret();
			bool DeleteCharAfterCaret();
			bool DeleteWordBeforeCaret();
			bool DeleteWordAfterCaret();
			bool DeleteAllBeforeCaret();
			bool DeleteAllAfterCaret();
			bool MoveCaretLeft(const bool select);
			bool MoveCaretRight(const bool select);
			bool MoveCaretWordLeft(const bool select);
			bool MoveCaretWordRight(const bool select);
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
			bool SelectAll();
			bool DeselectAll();

			// TextInput getters (works only with default text input)
			String getPlaceholder();
			bool isReadOnly();
			bool isReplacing();
			float getScrollInterval();
			Color getTextColor(const CBuiltInTextInput::State state);
			Color getPlaceholderColor(const CBuiltInTextInput::State state);
			Color getTextShadowColor(const CBuiltInTextInput::State state);
			Color getSelectionBackgroundColor(const CBuiltInTextInput::State state);
			Color getSelectionTextColor(const CBuiltInTextInput::State state);
			Color getSelectionTextShadowColor(const CBuiltInTextInput::State state);
			PointF getTextShadowShift(const CBuiltInTextInput::State state);
			int getTextShadowRadius(const CBuiltInTextInput::State state);
			bool isCopyByMouseEnabled();
			bool isMoveByMouseEnabled();
			bool isSelectWordByDoubleClickEnabled();
			bool isKeyLeftEnabled();
			bool isKeyRightEnabled();
			bool isKeyHomeEnabled();
			bool isKeyEndEnabled();
			bool isKeyDeleteEnabled();
			bool isKeyBackspaceEnabled();
			bool isSelectAllByKeyEnabled();
			bool isPasteByKeyEnabled();
			bool isCopyByKeyEnabled();
			bool isCutByKeyEnabled();
			bool isHistoryByKeyEnabled();
			bool isInsertReplaceChangeByKeyEnabled();

			// TextInput setters (works only with default text input)
			bool setPlaceholder(const String &value);
			bool setReadOnly(const bool value);
			bool setReplacing(const bool value);
			bool setScrollInterval(const float value);
			bool setTextColor(const CBuiltInTextInput::State state, const Color &value);
			bool setPlaceholderColor(const CBuiltInTextInput::State state, const Color &value);
			bool setTextShadowColor(const CBuiltInTextInput::State state, const Color &value);
			bool setSelectionBackgroundColor(const CBuiltInTextInput::State state, const Color &value);
			bool setSelectionTextColor(const CBuiltInTextInput::State state, const Color &value);
			bool setSelectionTextShadowColor(const CBuiltInTextInput::State state, const Color &value);
			bool setTextShadowShift(const CBuiltInTextInput::State state, const PointF &value);
			bool setTextShadowRadius(const CBuiltInTextInput::State state, const int value);
			bool setCopyByMouseEnabled(const bool value);
			bool setMoveByMouseEnabled(const bool value);
			bool setSelectWordByDoubleClickEnabled(const bool value);
			bool setKeyLeftEnabled(const bool value);
			bool setKeyRightEnabled(const bool value);
			bool setKeyHomeEnabled(const bool value);
			bool setKeyEndEnabled(const bool value);
			bool setKeyDeleteEnabled(const bool value);
			bool setKeyBackspaceEnabled(const bool value);
			bool setSelectAllByKeyEnabled(const bool value);
			bool setPasteByKeyEnabled(const bool value);
			bool setCopyByKeyEnabled(const bool value);
			bool setCutByKeyEnabled(const bool value);
			bool setHistoryByKeyEnabled(const bool value);
			bool setInsertReplaceChangeByKeyEnabled(const bool value);

			// Layout getters
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
			BorderColor getBorderColor(const CBuiltInTextInput::State state) const;
			Color getLeftBorderColor(const CBuiltInTextInput::State state) const;
			Color getTopBorderColor(const CBuiltInTextInput::State state) const;
			Color getRightBorderColor(const CBuiltInTextInput::State state) const;
			Color getBottomBorderColor(const CBuiltInTextInput::State state) const;
			Color getBackgroundColor(const CBuiltInTextInput::State state) const;
			Gradient *getBackgroundGradient(const CBuiltInTextInput::State state);
			int getShadowRadius(const CBuiltInTextInput::State state) const;
			PointF getShadowShift(const CBuiltInTextInput::State state) const;
			Color getShadowColor(const CBuiltInTextInput::State state) const;

			// Layout setters
			bool setTextInput(IBuiltInTextInput *value);
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
			bool setBorderColor(const CBuiltInTextInput::State state, const BorderColor &value);
			bool setLeftBorderColor(const CBuiltInTextInput::State state, const Color &value);
			bool setTopBorderColor(const CBuiltInTextInput::State state, const Color &value);
			bool setRightBorderColor(const CBuiltInTextInput::State state, const Color &value);
			bool setBottomBorderColor(const CBuiltInTextInput::State state, const Color &value);
			bool setBackgroundColor(const CBuiltInTextInput::State state, const Color &value);
			bool setShadowRadius(const CBuiltInTextInput::State state, const int value);
			bool setShadowShift(const CBuiltInTextInput::State state, const PointF &value);
			bool setShadowColor(const CBuiltInTextInput::State state, const Color &value);
		};
	}
}
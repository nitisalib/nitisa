// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/Scroll/BuiltInScroll.h"
#include "Nitisa/BuiltInControls/IBuiltInScrollListener.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IScrollBar.h"

namespace nitisa
{
	class IBuiltInControl;
	class IBuiltInScroll;
	class IControl;
	class IFont;
	class IForm;
	class ITexture;

	namespace standard
	{
		class CScrollBarService;

		class CScrollBar :public virtual IScrollBar, public CControl
		{
			friend CScrollBarService;
		private:
			class CScroll :public CBuiltInScroll
			{
			private:
				CScrollBar *m_pScrollBar;
			public:
				CScroll(CScrollBar *scrollbar);

				IControl *getControl() override;
			};

			class CScrollListener :public virtual IBuiltInScrollListener
			{
			private:
				CScrollBar *m_pScrollBar;
			public:
				CScrollListener(CScrollBar *scrollbar);

				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnScroll(IBuiltInControl *sender) override;
			};
		private:
			IBuiltInScroll *m_pScroll;
			ITexture *m_pCanvas;
			CScrollListener m_cScrollListener;

			IBuiltInScroll *getScroll();
			RectF getRenderRect(const CScroll::State state);
			void Render();
		public:
			void(*OnScroll)(IControl *sender); // Event called when scrolling

			// IControl methods
			void Refresh(const bool refresh_children) override;

			CScrollBar();
			CScrollBar(IControl *parent);
			CScrollBar(IForm *parent);
			~CScrollBar() override;

			IFont *getControlFont() override;
			RectF getRenderRect() override;
			
			bool setFont(IFont *value, const bool copy = true) override;
			bool setWantTabs(const bool value) override;
			bool setTabStop(const bool value) override;
			bool setDeactivateByTab(const bool value) override;
			bool setUseParentFont(const bool value) override;
			bool setDPI(const Point &value) override;

			bool setScroll(IBuiltInScroll *scroll);

			float getMin() override;
			float getMax() override;
			float getPosition() override;
			bool isVertical() override;

			bool setMin(const float value) override;
			bool setMax(const float value) override;
			bool setPosition(const float value) override;
			bool setVertical(const bool value) override;

			float getScrollerSize(); // Return scroller size
			// Return scrolling parameters
			float getDeltaSmall();
			float getDeltaMedium();
			float getDeltaLarge();

			bool setScrollerSize(const float value); // Set scroller size
			// Set scrolling parameters
			bool setDeltaSmall(const float value);
			bool setDeltaMedium(const float value);
			bool setDeltaLarge(const float value);

			// Following getters works only if associated IScroll is instance of CScroll
			CBuiltInScroll::State getState();
			CBuiltInScroll::ElementType getHoveredElement();
			CBuiltInScroll::ElementType getActiveElement();
			float getScrollInterval();
			float getArrowSize();
			float getBorderWidth();
			float getBorderRadius();
			Color getBorderColor(const CBuiltInScroll::State state);
			Color getBackgroundColor(const CBuiltInScroll::State state);
			Gradient *getBackgroundGradient(const CBuiltInScroll::State state);
			int getShadowRadius(const CBuiltInScroll::State state);
			PointF getShadowShift(const CBuiltInScroll::State state);
			Color getShadowColor(const CBuiltInScroll::State state);
			float getStartArrowBorderWidth();
			float getStartArrowBorderRadius();
			Color getStartArrowBorderColor(const CBuiltInScroll::ElementState state);
			Color getStartArrowBackgroundColor(const CBuiltInScroll::ElementState state);
			Gradient *getStartArrowBackgroundGradient(const CBuiltInScroll::ElementState state);
			Color getStartArrowColor1(const CBuiltInScroll::ElementState state);
			Color getStartArrowColor2(const CBuiltInScroll::ElementState state);
			Color getStartArrowColor3(const CBuiltInScroll::ElementState state);
			float getEndArrowBorderWidth();
			float getEndArrowBorderRadius();
			Color getEndArrowBorderColor(const CBuiltInScroll::ElementState state);
			Color getEndArrowBackgroundColor(const CBuiltInScroll::ElementState state);
			Gradient *getEndArrowBackgroundGradient(const CBuiltInScroll::ElementState state);
			Color getEndArrowColor1(const CBuiltInScroll::ElementState state);
			Color getEndArrowColor2(const CBuiltInScroll::ElementState state);
			Color getEndArrowColor3(const CBuiltInScroll::ElementState state);
			float getScrollerBorderWidth();
			float getScrollerBorderRadius();
			Color getScrollerBorderColor(const CBuiltInScroll::ElementState state);
			Color getScrollerBackgroundColor(const CBuiltInScroll::ElementState state);
			Gradient *getScrollerBackgroundGradient(const CBuiltInScroll::ElementState state);
			Color getScrollerLinesBorderColor(const CBuiltInScroll::ElementState state);
			Color getScrollerLinesBackgroundColor(const CBuiltInScroll::ElementState state);
			PointF getScrollerLinesSize();
			float getScrollerLinesDistance();
			float getScrollerLinesBorderWidth();

			// Following setters works only if associated IScroll is instance of CScroll
			bool setScrollInterval(const float value);
			bool setArrowSize(const float value);
			bool setBorderWidth(const float value);
			bool setBorderRadius(const float value);
			bool setBorderColor(const CBuiltInScroll::State state, const Color &value);
			bool setBackgroundColor(const CBuiltInScroll::State state, const Color &value);
			bool setShadowRadius(const CBuiltInScroll::State state, const int value);
			bool setShadowShift(const CBuiltInScroll::State state, const PointF &value);
			bool setShadowColor(const CBuiltInScroll::State state, const Color &value);
			bool setStartArrowBorderWidth(const float value);
			bool setStartArrowBorderRadius(const float value);
			bool setStartArrowBorderColor(const CBuiltInScroll::ElementState state, const Color &value);
			bool setStartArrowBackgroundColor(const CBuiltInScroll::ElementState state, const Color &value);
			bool setStartArrowColor1(const CBuiltInScroll::ElementState state, const Color &value);
			bool setStartArrowColor2(const CBuiltInScroll::ElementState state, const Color &value);
			bool setStartArrowColor3(const CBuiltInScroll::ElementState state, const Color &value);
			bool setEndArrowBorderWidth(const float value);
			bool setEndArrowBorderRadius(const float value);
			bool setEndArrowBorderColor(const CBuiltInScroll::ElementState state, const Color &value);
			bool setEndArrowBackgroundColor(const CBuiltInScroll::ElementState state, const Color &value);
			bool setEndArrowColor1(const CBuiltInScroll::ElementState state, const Color &value);
			bool setEndArrowColor2(const CBuiltInScroll::ElementState state, const Color &value);
			bool setEndArrowColor3(const CBuiltInScroll::ElementState state, const Color &value);
			bool setScrollerBorderWidth(const float value);
			bool setScrollerBorderRadius(const float value);
			bool setScrollerBorderColor(const CBuiltInScroll::ElementState state, const Color &value);
			bool setScrollerBackgroundColor(const CBuiltInScroll::ElementState state, const Color &value);
			bool setScrollerLinesBorderColor(const CBuiltInScroll::ElementState state, const Color &value);
			bool setScrollerLinesBackgroundColor(const CBuiltInScroll::ElementState state, const Color &value);
			bool setScrollerLinesSize(const PointF &value);
			bool setScrollerLinesDistance(const float value);
			bool setScrollerLinesBorderWidth(const float value);
		};
	}
}
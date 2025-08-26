// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IToolBar.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CToolBarService;

		class CToolBar :public virtual IToolBar, public CControl
		{
			friend CToolBarService;
		public:
			enum class ScrollerState // Scroller area states
			{
				Normal,
				Hovered,
				Active,
				ActiveHovered,
				Disabled
			};
		private:
			enum class Element
			{
				None,
				LeftScroller,
				RightScroller
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CToolBar *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CToolBar *control);
			};
		private:
			CGradientListener m_cGradientListener;
			AlignTo m_eAlignTo;
			float m_fDistance; // Distance between controls
			RectF m_sPadding;
			RectF m_sBorderWidth;
			BorderColor m_sBorderColor;
			Color m_sBackgroundColor;
			Gradient m_cBackgroundGradient;
			float m_fScrollerSize;
			float m_fScrollerArrowSize; // 0..1 of width
			RectF m_aScrollerBorderWidth[(int)ScrollerState::Disabled + 1];
			BorderColor m_aScrollerBorderColor[(int)ScrollerState::Disabled + 1];
			Color m_aScrollerBackgroundColor[(int)ScrollerState::Disabled + 1];
			Gradient m_aScrollerBackgroundGradient[(int)ScrollerState::Disabled + 1];
			Color m_aScrollerArrowColor[(int)ScrollerState::Disabled + 1];
			float m_fScrollInterval;
			float m_fScrollDeltaTimer;
			float m_fScrollDeltaWheel;
			bool m_bUseMask;

			bool m_bIgnoreGradient;
			ITexture *m_pCanvas;
			ITexture *m_pMask;
			float m_fScroll;
			float m_fScrollMax;
			Element m_eHoveredElement;
			Element m_eDownElement;

			ScrollerState getLeftScrollerState();
			ScrollerState getRightScrollerState();
			RectF getLeftScrollerRect();
			RectF getRightScrollerRect();
			bool UpdateHoveredElement(const PointF &position);
			void UpdateFromStyle(IStyle *style);
			void Render(IRenderer *renderer, const Mat4f &matrix);
			void RenderScroller(IRenderer *renderer);
			void RenderMask(IRenderer *renderer);
		public:
			IControl *getControl(const int index) override;
			IControl *getControl(const String &name) override;
			IControl *getControl(const PointF &position) override;
			RectF getClientRect() override;
			AlignTo getAlignTo() override;

			bool setDPI(const Point &value) override;
			bool setAlignTo(const AlignTo value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;
			
			CToolBar();
			CToolBar(IForm *parent);
			CToolBar(IControl *parent);

			// Return layout properties
			float getDistance() const;
			RectF getPadding() const;
			RectF getBorderWidth() const;
			BorderColor getBorderColor() const;
			Color getLeftBorderColor() const;
			Color getTopBorderColor() const;
			Color getRightBorderColor() const;
			Color getBottomBorderColor() const;
			Color getBackgroundColor() const;
			Gradient *getBackgroundGradient();
			float getScrollerSize() const;
			float getScrollerArrowSize() const;
			RectF getScrollerBorderWidth(const ScrollerState state) const;
			BorderColor getScrollerBorderColor(const ScrollerState state) const;
			Color getScrollerLeftBorderColor(const ScrollerState state) const;
			Color getScrollerTopBorderColor(const ScrollerState state) const;
			Color getScrollerRightBorderColor(const ScrollerState state) const;
			Color getScrollerBottomBorderColor(const ScrollerState state) const;
			Color getScrollerBackgroundColor(const ScrollerState state) const;
			Gradient *getScrollerBackgroundGradient(const ScrollerState state);
			Color getScrollerArrowColor(const ScrollerState state) const;
			float getScrollInterval() const;
			float getScrollDeltaTimer() const;
			float getScrollDeltaWheel() const;
			bool isUseMask() const; // Whether to use mask
			bool isAcceptBubbledEvents() override;

			// Set layout properties
			bool setDistance(const float value);
			bool setPadding(const RectF &value);
			bool setBorderWidth(const RectF &value);
			bool setBorderColor(const BorderColor &value);
			bool setLeftBorderColor(const Color &value);
			bool setTopBorderColor(const Color &value);
			bool setRightBorderColor(const Color &value);
			bool setBottomBorderColor(const Color &value);
			bool setBackgroundColor(const Color &value);
			bool setScrollerSize(const float value);
			bool setScrollerArrowSize(const float value);
			bool setScrollerBorderWidth(const ScrollerState state, const RectF &value);
			bool setScrollerBorderColor(const ScrollerState state, const BorderColor &value);
			bool setScrollerLeftBorderColor(const ScrollerState state, const Color &value);
			bool setScrollerTopBorderColor(const ScrollerState state, const Color &value);
			bool setScrollerRightBorderColor(const ScrollerState state, const Color &value);
			bool setScrollerBottomBorderColor(const ScrollerState state, const Color &value);
			bool setScrollerBackgroundColor(const ScrollerState state, const Color &value);
			bool setScrollerArrowColor(const ScrollerState state, const Color &value);
			bool setScrollInterval(const float value);
			bool setScrollDeltaTimer(const float value);
			bool setScrollDeltaWheel(const float value);
			bool setUseMask(const bool value); // Set whether to use mask
		};
	}
}
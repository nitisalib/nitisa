// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/ScrollVisibility.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IScrollList.h"

namespace nitisa
{
	class IBuiltInScroll;
	class IControl;
	class IForm;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CScrollList :public virtual IScrollList, public CControl
		{
			friend class CScrollListService;
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CScrollList *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CScrollList *control);
			};

			class CScroll :public CBuiltInScrollLite
			{
			private:
				CScrollList *m_pControl;
			public:
				CScroll(CScrollList *control);

				IControl *getControl() override;
			};

			class CScrollListener :public virtual IBuiltInScrollListener
			{
			private:
				CScrollList *m_pControl;
			public:
				CScrollListener(CScrollList *scrollbar);

				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnScroll(IBuiltInControl *sender) override;
			};
		private:
			CGradientListener m_cGradientListener;
			CScrollListener m_cScrollListener;
			Orientation m_eOrientation;
			float m_fScroll; // Clamped in AlignControls()
			float m_fScrollMax; // Updated in AlignControls()
			float m_fScrollSize;
			ScrollVisibility m_eScrollVisibility;
			IBuiltInScroll *m_pScroll;
			int m_iShadowRadius;
			Color m_sShadowColor;
			PointF m_sShadowShift;
			RectF m_sBorderRadius;
			RectF m_sPadding;
			PointF m_sScrollPadding;
			RectF m_sOuterBorderWidth;
			RectF m_sInnerBorderWidth;
			BorderColor m_sOuterBorderColor;
			BorderColor m_sInnerBorderColor;
			Color m_sBackgroundColor;
			Gradient m_cBackgroundGradient;
			float m_fMargin;

			bool m_bIgnoreGradient;
			ITexture *m_pCanvas;	
			ITexture *m_pMask;

			// Helpers
			void UpdateFromStyle(IStyle *style);
			void UpdateScrollBar();
			RectF CalculateScrollBarRect();
			bool NeedBlock() const;
			bool isScrollBarVisible() const;
			// Render
			void Render(IRenderer *renderer, const Mat4f &matrix);
			void RenderMask(IRenderer *renderer);
		public:
			// IControl getters
			IControl *getControl(const int index) override;
			IControl *getControl(const String &name) override;
			IControl *getControl(const PointF &position) override;
			RectF getClientRect() override;
			RectF getRenderRect() override;
			bool isAcceptBubbledEvents() override;

			// IControl setters
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			// IScrollList getters
			Orientation getOrientation() override;
			IBuiltInScroll *getScrollBar() override;
			float getScroll() override;
			float getScrollMax() override;

			// IScrollList setters
			bool setOrientation(const Orientation value) override;
			bool setScrollBar(IBuiltInScroll *value) override;
			bool setScroll(const float value) override;

			CScrollList();
			CScrollList(IControl *parent);
			CScrollList(IForm *parent);
			~CScrollList() override;

			// Layout getters
			float getScrollSize() const;
			ScrollVisibility getScrollVisibility() const;
			int getShadowRadius() const;
			Color getShadowColor() const;
			PointF getShadowShift() const;
			RectF getBorderRadius() const;
			RectF getPadding() const;
			PointF getScrollPadding() const;
			RectF getOuterBorderWidth() const;
			RectF getInnerBorderWidth() const;
			BorderColor getOuterBorderColor() const;
			BorderColor getInnerBorderColor() const;
			Color getBackgroundColor() const;
			Gradient *getBackgroundGradient();
			float getMargin() const;

			// Layout setters
			bool setScrollSize(const float value);
			bool setScrollVisibility(const ScrollVisibility value);
			bool setShadowRadius(const int value);
			bool setShadowColor(const Color &value);
			bool setShadowShift(const PointF &value);
			bool setBorderRadius(const RectF &value);
			bool setPadding(const RectF &value);
			bool setScrollPadding(const PointF &value);
			bool setOuterBorderWidth(const RectF &value);
			bool setInnerBorderWidth(const RectF &value);
			bool setOuterBorderColor(const BorderColor &value);
			bool setInnerBorderColor(const BorderColor &value);
			bool setBackgroundColor(const Color &value);
			bool setMargin(const float value);

			// ScrollBar layout getters (work with default scrollbar only)
			float getScrollBarDeltaMedium();
			float getScrollBarDeltaLarge();
			float getScrollBarScrollInterval();
			int getScrollBarShadowRadius(const CBuiltInScrollLite::State state);
			Color getScrollBarShadowColor(const CBuiltInScrollLite::State state);
			PointF getScrollBarShadowShift(const CBuiltInScrollLite::State state);
			bool isScrollBarBorderRound();
			float getScrollBarBorderWidth();
			Color getScrollBarBorderColor(const CBuiltInScrollLite::State state);
			Color getScrollBarBackgroundColor(const CBuiltInScrollLite::State state);
			Gradient *getScrollBarBackgroundGradient(const CBuiltInScrollLite::State state);
			bool isScrollBarScrollerRound();
			float getScrollBarScrollerBorderWidth();
			Color getScrollBarScrollerBorderColor(const CBuiltInScrollLite::State state);
			Color getScrollBarScrollerBackgroundColor(const CBuiltInScrollLite::State state);
			Gradient *getScrollBarScrollerBackgroundGradient(const CBuiltInScrollLite::State state);

			// ScrollBar layout setters (work with default scrollbar only)
			bool setScrollBarDeltaMedium(const float value);
			bool setScrollBarDeltaLarge(const float value);
			bool setScrollBarScrollInterval(const float value);
			bool setScrollBarShadowRadius(const CBuiltInScrollLite::State state, const int value);
			bool setScrollBarShadowColor(const CBuiltInScrollLite::State state, const Color &value);
			bool setScrollBarShadowShift(const CBuiltInScrollLite::State state, const PointF &value);
			bool setScrollBarBorderRound(const bool value);
			bool setScrollBarBorderWidth(const float value);
			bool setScrollBarBorderColor(const CBuiltInScrollLite::State state, const Color &value);
			bool setScrollBarBackgroundColor(const CBuiltInScrollLite::State state, const Color &value);
			bool setScrollBarScrollerRound(const bool value);
			bool setScrollBarScrollerBorderWidth(const float value);
			bool setScrollBarScrollerBorderColor(const CBuiltInScrollLite::State state, const Color &value);
			bool setScrollBarScrollerBackgroundColor(const CBuiltInScrollLite::State state, const Color &value);
			bool setScrollBarShadowRadius(const int value);
			bool setScrollBarShadowShift(const PointF &value);
			bool setScrollBarShadowColor(const Color &value);
			bool setScrollBarBorderColor(const Color &value);
			bool setScrollBarBackgroundColor(const Color &value);
			bool setScrollBarScrollerBorderColor(const Color &value);
			bool setScrollBarScrollerBackgroundColor(const Color &value);
		};
	}
}
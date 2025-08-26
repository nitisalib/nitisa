// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h"
#include "Nitisa/BuiltInControls/IBuiltInScrollListener.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IScrollBarLite.h"

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
		class CScrollBarLite :public virtual IScrollBarLite, public CControl
		{
			friend class CScrollBarLiteService;
		private:
			class CScroll :public CBuiltInScrollLite
			{
			private:
				CScrollBarLite *m_pControl;
			public:
				CScroll(CScrollBarLite *control);

				IControl *getControl() override;
			};

			class CScrollListener :public virtual IBuiltInScrollListener
			{
			private:
				CScrollBarLite *m_pControl;
			public:
				CScrollListener(CScrollBarLite *scrollbar);

				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnScroll(IBuiltInControl *sender) override;
			};
		private:
			IBuiltInScroll *m_pScroll;
			ITexture *m_pCanvas;
			CScrollListener m_cScrollListener;

			void Render();
		public:
			void(*OnScroll)(IControl *sender); // Event called when scrolling
			
			// IControl getters
			IFont *getControlFont() override;
			RectF getRenderRect() override;

			// IControl setters
			bool setFont(IFont *value, const bool copy = true) override;
			bool setWantTabs(const bool value) override;
			bool setTabStop(const bool value) override;
			bool setDeactivateByTab(const bool value) override;
			bool setUseParentFont(const bool value) override;
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;
			
			// IScrollBarLite getters
			float getMin() override;
			float getMax() override;
			float getPosition() override;
			bool isVertical() override;

			// IScrollBarLite setters
			bool setMin(const float value) override;
			bool setMax(const float value) override;
			bool setPosition(const float value) override;
			bool setVertical(const bool value) override;

			CScrollBarLite();
			CScrollBarLite(IControl *parent);
			CScrollBarLite(IForm *parent);
			~CScrollBarLite() override;

			// Getters
			IBuiltInScroll *getScroll();

			// Setters
			bool setScroll(IBuiltInScroll *scroll);

			// Following getters works only if associated IScroll is instance of CScroll
			float getScrollerSize(); // Return scroller size
			float getDeltaMedium();
			float getDeltaLarge();
			float getScrollInterval();
			int getShadowRadius(const CBuiltInScrollLite::State state);
			Color getShadowColor(const CBuiltInScrollLite::State state);
			PointF getShadowShift(const CBuiltInScrollLite::State state);
			bool isBorderRound();
			float getBorderWidth();
			Color getBorderColor(const CBuiltInScrollLite::State state);
			Color getBackgroundColor(const CBuiltInScrollLite::State state);
			Gradient *getBackgroundGradient(const CBuiltInScrollLite::State state);
			bool isScrollerRound();
			float getScrollerBorderWidth();
			Color getScrollerBorderColor(const CBuiltInScrollLite::State state);
			Color getScrollerBackgroundColor(const CBuiltInScrollLite::State state);
			Gradient *getScrollerBackgroundGradient(const CBuiltInScrollLite::State state);

			// Following setters works only if associated IScroll is instance of CScroll
			bool setScrollerSize(const float value); // Set scroller size
			bool setDeltaMedium(const float value);
			bool setDeltaLarge(const float value);
			bool setScrollInterval(const float value);
			bool setShadowRadius(const CBuiltInScrollLite::State state, const int value);
			bool setShadowColor(const CBuiltInScrollLite::State state, const Color &value);
			bool setShadowShift(const CBuiltInScrollLite::State state, const PointF &value);
			bool setBorderRound(const bool value);
			bool setBorderWidth(const float value);
			bool setBorderColor(const CBuiltInScrollLite::State state, const Color &value);
			bool setBackgroundColor(const CBuiltInScrollLite::State state, const Color &value);
			bool setScrollerRound(const bool value);
			bool setScrollerBorderWidth(const float value);
			bool setScrollerBorderColor(const CBuiltInScrollLite::State state, const Color &value);
			bool setScrollerBackgroundColor(const CBuiltInScrollLite::State state, const Color &value);
			bool setShadowRadius(const int value);
			bool setShadowShift(const PointF &value);
			bool setShadowColor(const Color &value);
			bool setBorderColor(const Color &value);
			bool setBackgroundColor(const Color &value);
			bool setScrollerBorderColor(const Color &value);
			bool setScrollerBackgroundColor(const Color &value);
		};
	}
}
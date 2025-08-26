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
#include "Nitisa/Core/ScrollVisibility.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IScrollBox.h"

namespace nitisa
{
	class IBuiltInControl;
	class IBuiltInScroll;
	class IControl;
	class IForm;
	class IRenderer;
	class IStyle;
	class ITexture;
	class ITransform;

	namespace standard
	{
		class CScrollBoxService;

		class CScrollBox :public virtual IScrollBox, public CControl
		{
			friend CScrollBoxService;
		private:
			enum class Element
			{
				VScroll,
				HScroll,
				None
			};

			class CScroll :public CBuiltInScroll
			{
			private:
				CScrollBox *m_pScrollBox;
			public:
				IControl *getControl() override;

				CScroll(CScrollBox *scrollbox);
			};

			class CScrollListener :public IBuiltInScrollListener
			{
			private:
				CScrollBox *m_pScrollBox;
			public:
				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnScroll(IBuiltInControl *sender) override;

				CScrollListener(CScrollBox *scrollbox);
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CScrollBox *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CScrollBox *control);
			};
		private:
			CGradientListener m_cGradientListener;
			ScrollVisibility m_eVScroll;
			ScrollVisibility m_eHScroll;
			Color m_sBackgroundColor;
			Color m_sCornerColor;
			Gradient m_cBackgroundGradient;
			PointF m_sPadding;

			CScrollListener m_cScrollListener;
			ITexture *m_pCanvas;
			ITexture *m_pMask;
			IBuiltInScroll *m_pVScroll;
			IBuiltInScroll *m_pHScroll;
			bool m_bIgnoreGradient;
			bool m_bVScroll;
			bool m_bHScroll;
			Element m_eHoveredElement;
			Element m_eDownElement;

			void UpdateFromStyle(IStyle *style);
			IBuiltInScroll *getVScroll();
			IBuiltInScroll *getHScroll();
			bool UpdateTransformControls();
			void Update();
			bool UpdateHoveredElement();
			bool UpdateHoveredElement(const PointF &position);
			void Render(IRenderer *renderer, const Mat4f &matrix);
			void RenderMask(IRenderer *renderer);
		public:
			RectF getClientRect() override;
			IControl *getControl(const int index) override;
			IControl *getControl(const String &name) override;
			IControl *getControl(const PointF &position) override;
			bool isAcceptBubbledEvents() override;

			bool setTransformControls(ITransform *value) override;
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;
			
			ScrollVisibility getVerticalScrollVisibility() override;
			bool isVerticalScrollEnabled() override;
			float getVerticalScrollMax() override;
			float getVerticalScrollPosition() override;
			ScrollVisibility getHorizontalScrollVisibility() override;
			bool isHorizontalScrollEnabled() override;
			float getHorizontalScrollMax() override;
			float getHorizontalScrollPosition() override;

			bool setVerticalScrollVisibility(const ScrollVisibility value) override;
			bool setVerticalScrollPosition(const float value) override;
			bool setHorizontalScrollVisibility(const ScrollVisibility value) override;
			bool setHorizontalScrollPosition(const float value) override;

			CScrollBox();
			CScrollBox(IControl *parent);
			CScrollBox(IForm *parent);
			~CScrollBox() override;

			// Return layout properties
			Color getBackgroundColor() const;
			Gradient *getBackgroundGradient();
			PointF getPadding() const;

			bool setVerticalScroll(IBuiltInScroll *value); // Set vertical scroll
			bool setHorizontalScroll(IBuiltInScroll *value); // Set horizontal scroll
			// Set layout properties
			bool setBackgroundColor(const Color &value);
			bool setPadding(const PointF &value);
		};
	}
}
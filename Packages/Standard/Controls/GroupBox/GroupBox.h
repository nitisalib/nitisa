// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/TextAlign.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IGroupBox.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CGroupBoxService;

		class CGroupBox :public virtual IGroupBox, public CControl
		{
			friend CGroupBoxService;
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CGroupBox *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CGroupBox *control);
			};
		private:
			CGradientListener m_cGradientListener;
			RectF m_sBorderWidth;
			RectF m_sBorderRadius;
			BorderColor m_sBorderColor;
			RectF m_sPadding;
			Color m_sBackgroundColor;
			Gradient m_cBackgroundGradient;
			Color m_sShadowColor;
			PointF m_sShadowShift;
			int m_iShadowRadius;
			String m_sCaption;
			TextAlign m_eCaptionAlign;
			PointF m_sCaptionPadding; // Left|Right, Top
			bool m_bUseMask;

			bool m_bIgnoreGradient;
			ITexture *m_pCanvas;
			ITexture *m_pMask;
			bool m_bCaptionChanged;

			void UpdateFromStyle(IStyle *style);
			RectF getBlockRect(const RectF &caption_rect);
			RectF getCaptionRect();
			void Render(IRenderer *renderer, const Mat4f &matrix);
			void RenderMask(IRenderer *renderer);
		public:
			IControl *getControl(const int index) override;
			IControl *getControl(const String &name) override;
			IControl *getControl(const PointF &position) override;
			RectF getClientRect() override;
			RectF getRenderRect() override;
			String getCaption() override;
			
			bool setDPI(const Point &value) override;
			bool setCaption(const String &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			CGroupBox();
			CGroupBox(IControl *parent);
			CGroupBox(IForm *parent);

			// Return layout properties
			RectF getBorderWidth() const;
			RectF getBorderRadius() const;
			BorderColor getBorderColor() const;
			Color getLeftBorderColor() const;
			Color getTopBorderColor() const;
			Color getRightBorderColor() const;
			Color getBottomBorderColor() const;
			RectF getPadding() const;
			Color getBackgroundColor() const;
			Gradient *getBackgroundGradient();
			Color getShadowColor() const;
			PointF getShadowShift() const;
			int getShadowRadius() const;
			TextAlign getCaptionAlign() const;
			PointF getCaptionPadding() const;
			bool isUseMask() const; // Whether to use mask

			// Set layout properties
			bool setBorderWidth(const RectF &value);
			bool setBorderRadius(const RectF &value);
			bool setBorderColor(const BorderColor &value);
			bool setLeftBorderColor(const Color &value);
			bool setTopBorderColor(const Color &value);
			bool setRightBorderColor(const Color &value);
			bool setBottomBorderColor(const Color &value);
			bool setPadding(const RectF &value);
			bool setBackgroundColor(const Color &value);
			bool setShadowColor(const Color &value);
			bool setShadowShift(const PointF &value);
			bool setShadowRadius(const int value);
			bool setCaptionAlign(const TextAlign value);
			bool setCaptionPadding(const PointF &value);
			bool setUseMask(const bool value); // Set whether to use mask
		};
	}
}
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
#include "Nitisa/Core/VerticalAlign.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IProgressBar.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IPlatformFont;
	class IRenderer;
	class IStyle;
	class ITexture;

	struct Block;

	namespace standard
	{
		class CProgressBarService;

		class CProgressBar :public virtual IProgressBar, public CControl
		{
			friend CProgressBarService;
		public:
			enum class FillDirection // Progress directions
			{
				LeftToRight,
				RightToLeft,
				TopToBottom,
				BottomToTop
			};
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CProgressBar *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CProgressBar *control);
			};
		private:
			CGradientListener m_cGradientListener;
			float m_fMin;
			float m_fMax;
			float m_fProgress;
			String m_sCaption;
			TextAlign m_eCaptionHorizontalAlign;
			VerticalAlign m_eCaptionVerticalAlign;
			bool m_bSmooth;
			float m_fBarSize;
			float m_fBarInterval;
			Color m_sShadowColor;
			PointF m_sShadowShift;
			int m_iShadowRadius;
			RectF m_sOuterBorderWidth;
			RectF m_sInnerBorderWidth;
			RectF m_sBorderRadius;
			BorderColor m_sOuterBorderColor;
			BorderColor m_sInnerBorderColor;
			Color m_sBackgroundColor;
			Gradient m_cBackgroundGradient;
			Color m_sForegroundColor;
			Gradient m_cForegroundGradient;
			RectF m_sBarBorderWidth;
			RectF m_sBarBorderRadius;
			BorderColor m_sBarBorderColor;
			Color m_sBarColor;
			Gradient m_cBarGradient;
			RectF m_sCaptionPadding;
			FillDirection m_eFillDirection;

			bool m_bIgnoreGradient;
			ITexture *m_pCanvas;

			void UpdateFromStyle(IStyle *style);
			PointF CalculateCaptionPosition(IPlatformFont *pf);
			void Render();
			void RenderForeground(IRenderer *renderer, const RectF &rect, const Block *block, const RectF &client);
			void RenderCaption(IRenderer *renderer, const RectF &rect, IPlatformFont *pf, const PointF &caption_position, const Block *block);
		public:
			RectF getClientRect() override;
			RectF getRenderRect() override;
			float getMin() override;
			float getMax() override;
			float getProgress() override;

			bool setDPI(const Point &value) override;
			bool setMin(const float value) override;
			bool setMax(const float value) override;
			bool setProgress(const float value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			CProgressBar();
			CProgressBar(IForm *parent);
			CProgressBar(IControl *parent);

			const String &getCaption() const; // Return caption
			// Return layout properties
			TextAlign getCaptionHorizontalAlign() const;
			VerticalAlign getCaptionVerticalAlign() const;
			bool isSmooth() const;
			float getBarSize() const;
			float getBarInterval() const;
			Color getShadowColor() const;
			PointF getShadowShift() const;
			int getShadowRadius() const;
			RectF getOuterBorderWidth() const;
			RectF getInnerBorderWidth() const;
			RectF getBorderRadius() const;
			BorderColor getOuterBorderColor() const;
			Color getLeftOuterBorderColor() const;
			Color getTopOuterBorderColor() const;
			Color getRightOuterBorderColor() const;
			Color getBottomOuterBorderColor() const;
			BorderColor getInnerBorderColor() const;
			Color getLeftInnerBorderColor() const;
			Color getTopInnerBorderColor() const;
			Color getRightInnerBorderColor() const;
			Color getBottomInnerBorderColor() const;
			Color getBackgroundColor() const;
			Gradient *getBackgroundGradient();
			Color getForegroundColor() const;
			Gradient *getForegroundGradient();
			RectF getBarBorderWidth() const;
			RectF getBarBorderRadius() const;
			BorderColor getBarBorderColor() const;
			Color getBarLeftBorderColor() const;
			Color getBarTopBorderColor() const;
			Color getBarRightBorderColor() const;
			Color getBarBottomBorderColor() const;
			Color getBarColor() const;
			Gradient *getBarGradient();
			RectF getCaptionPadding() const;
			FillDirection getFillDirection() const;

			bool setCaption(const String &value); // Set caption
			// Set layout properties
			bool setCaptionHorizontalAlign(const TextAlign value);
			bool setCaptionVerticalAlign(const VerticalAlign value);
			bool setSmooth(const bool value);
			bool setBarSize(const float value);
			bool setBarInterval(const float value);
			bool setShadowColor(const Color &value);
			bool setShadowShift(const PointF &value);
			bool setShadowRadius(const int value);
			bool setOuterBorderWidth(const RectF &value);
			bool setInnerBorderWidth(const RectF &value);
			bool setBorderRadius(const RectF &value);
			bool setOuterBorderColor(const BorderColor &value);
			bool setLeftOuterBorderColor(const Color &value);
			bool setTopOuterBorderColor(const Color &value);
			bool setRightOuterBorderColor(const Color &value);
			bool setBottomOuterBorderColor(const Color &value);
			bool setInnerBorderColor(const BorderColor &value);
			bool setLeftInnerBorderColor(const Color &value);
			bool setTopInnerBorderColor(const Color &value);
			bool setRightInnerBorderColor(const Color &value);
			bool setBottomInnerBorderColor(const Color &value);
			bool setBackgroundColor(const Color &value);
			bool setForegroundColor(const Color &value);
			bool setBarBorderWidth(const RectF &value);
			bool setBarBorderRadius(const RectF &value);
			bool setBarBorderColor(const BorderColor &value);
			bool setBarLeftBorderColor(const Color &value);
			bool setBarTopBorderColor(const Color &value);
			bool setBarRightBorderColor(const Color &value);
			bool setBarBottomBorderColor(const Color &value);
			bool setBarColor(const Color &value);
			bool setCaptionPadding(const RectF &value);
			bool setFillDirection(const FillDirection value);
		};
	}
}
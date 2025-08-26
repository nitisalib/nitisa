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
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IPanel.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IPlatformFont;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CPanelService;

		class CPanel :public virtual IPanel, public CControl
		{
			friend CPanelService;
		public:
			enum class Bevel // Bevel types
			{
				Raised,
				Lowered
			};
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CPanel *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CPanel *control);
			};
		private:
			CGradientListener m_cGradientListener;
			String m_sCaption;
			TextAlign m_eCaptionHorizontalAlign;
			VerticalAlign m_eCaptionVerticalAlign;
			Bevel m_eOuterBevel;
			Bevel m_eInnerBevel;
			Color m_sBevelRaisedColor;
			Color m_sBevelLoweredColor;
			RectF m_sOuterBevelWidth;
			RectF m_sInnerBevelWidth;
			RectF m_sBorderWidth;
			RectF m_sBorderRadius;
			BorderColor m_sBorderColor;
			RectF m_sPadding;
			Color m_sBackgroundColor;
			Gradient m_cBackgroundGradient;
			Color m_sShadowColor;
			PointF m_sShadowShift;
			int m_iShadowRadius;
			bool m_bUseMask;

			bool m_bIgnoreGradient;
			ITexture *m_pCanvas;
			ITexture *m_pMask;
			bool m_bCaptionChanged;

			void UpdateFromStyle(IStyle *style);
			void Render(IRenderer *renderer, const Mat4f &matrix);
			void RenderBackground(IRenderer *renderer, const RectF &rect);
			void RenderCaption(IRenderer *renderer, IPlatformFont *pf, const RectF &rect, const PointF &disp);
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

			CPanel();
			CPanel(IControl *parent);
			CPanel(IForm *parent);

			// Return layout properties
			TextAlign getCaptionHorizontalAlign() const;
			VerticalAlign getCaptionVerticalAlign() const;
			Bevel getOuterBevel() const;
			Bevel getInnerBevel() const;
			Color getBevelRaisedColor() const;
			Color getBevelLoweredColor() const;
			RectF getOuterBevelWidth() const;
			RectF getInnerBevelWidth() const;
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
			bool isUseMask() const; // Whether to use mask

			// Set layout properties
			bool setCaptionHorizontalAlign(const TextAlign value);
			bool setCaptionVerticalAlign(const VerticalAlign value);
			bool setOuterBevel(const Bevel value);
			bool setInnerBevel(const Bevel value);
			bool setBevelRaisedColor(const Color &value);
			bool setBevelLoweredColor(const Color &value);
			bool setOuterBevelWidth(const RectF &value);
			bool setInnerBevelWidth(const RectF &value);
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
			bool setUseMask(const bool value); // Set whether to use mask
		};
	}
}
// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
#include "Nitisa/Image/Image.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IBitBtn.h"

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
		class CBitBtnService;

		class CBitBtn :public virtual IBitBtn, public CControl
		{
			friend CBitBtnService;
		public:
			enum class State // Possible states
			{
				Normal, // Normal
				Hovered, // Hovered
				Focused, // Focused
				FocusedHovered, // Focused and hovered
				Active, // Active(mouse was down but not released)
				ActiveHovered, // Active and hovered
				Disabled // Disabled
			};
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CBitBtn *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CBitBtn *control);
			};
		private:
			CGradientListener m_cGradientListener;
			String m_sCaption;
			Kind m_eKind;
			RectF m_aOuterBorderWidth[(int)State::Disabled + 1];
			RectF m_aInnerBorderWidth[(int)State::Disabled + 1];
			RectF m_aBorderRadius[(int)State::Disabled + 1];
			BorderColor m_aOuterBorderColor[(int)State::Disabled + 1];
			BorderColor m_aInnerBorderColor[(int)State::Disabled + 1];
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
			Color m_aShadowColor[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];
			int m_aShadowRadius[(int)State::Disabled + 1];
			RectF m_aPadding[(int)State::Disabled + 1];
			TextAlign m_aContentHorizontalAlign[(int)State::Disabled + 1];
			VerticalAlign m_aContentVerticalAlign[(int)State::Disabled + 1];
			Color m_aCaptionColor[(int)State::Disabled + 1];
			Color m_aCaptionShadowColor[(int)State::Disabled + 1];
			PointF m_aCaptionShadowShift[(int)State::Disabled + 1];
			int m_aCaptionShadowRadius[(int)State::Disabled + 1];
			float m_aIconPadding[(int)State::Disabled + 1]; // Distance between icon and caption
			bool m_aIconOnRight[(int)State::Disabled + 1];

			ITexture *m_pCanvas;
			bool m_bKeyDown;
			bool m_bMouseDown;
			bool m_bIgnoreGradient;
			Image m_sBitmap;
			RectF m_aIconsEnabled[8];
			RectF m_aIconsDisabled[8];
			int m_iIconIndex;

			void UpdateFromStyle(IStyle *style);
			RectF getRenderRect(const State state);
			void UpdateHotkeys();
			void UpdateContent();
			void Render();
			void RenderContent(const State state, IRenderer *renderer, IPlatformFont *pf, const RectF &rect);
		public:
			void(*OnClick)(IControl *sender); // Event called when click on the button(or Enter)

			RectF getClientRect() override;
			RectF getRenderRect() override;
			String getCaption() override;
			Kind getKind() override;

			bool setDPI(const Point &value) override;
			bool setCaption(const String &value) override;
			bool setKind(const Kind value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			CBitBtn();
			CBitBtn(IControl *parent);
			CBitBtn(IForm *parent);

			State getState(); // Return state
			// Return layout properties depending on state
			RectF getOuterBorderWidth(const State state) const;
			RectF getInnerBorderWidth(const State state) const;
			RectF getBorderRadius(const State state) const;
			BorderColor getOuterBorderColor(const State state) const;
			Color getLeftOuterBorderColor(const State state) const;
			Color getTopOuterBorderColor(const State state) const;
			Color getRightOuterBorderColor(const State state) const;
			Color getBottomOuterBorderColor(const State state) const;
			BorderColor getInnerBorderColor(const State state) const;
			Color getLeftInnerBorderColor(const State state) const;
			Color getTopInnerBorderColor(const State state) const;
			Color getRightInnerBorderColor(const State state) const;
			Color getBottomInnerBorderColor(const State state) const;
			Color getBackgroundColor(const State state) const;
			Gradient *getBackgroundGradient(const State state);
			Color getShadowColor(const State state) const;
			PointF getShadowShift(const State state) const;
			int getShadowRadius(const State state) const;
			RectF getPadding(const State state) const;
			TextAlign getContentHorizontalAlign(const State state) const;
			VerticalAlign getContentVerticalAlign(const State state) const;
			Color getCaptionColor(const State state) const;
			Color getCaptionShadowColor(const State state) const;
			PointF getCaptionShadowShift(const State state) const;
			int getCaptionShadowRadius(const State state) const;
			float getIconPadding(const State state) const;
			bool isIconOnRight(const State state) const;

			// Set layout properties depending on state
			bool setOuterBorderWidth(const State state, const RectF &value);
			bool setInnerBorderWidth(const State state, const RectF &value);
			bool setBorderRadius(const State state, const RectF &value);
			bool setOuterBorderColor(const State state, const BorderColor &value);
			bool setLeftOuterBorderColor(const State state, const Color &value);
			bool setTopOuterBorderColor(const State state, const Color &value);
			bool setRightOuterBorderColor(const State state, const Color &value);
			bool setBottomOuterBorderColor(const State state, const Color &value);
			bool setInnerBorderColor(const State state, const BorderColor &value);
			bool setLeftInnerBorderColor(const State state, const Color &value);
			bool setTopInnerBorderColor(const State state, const Color &value);
			bool setRightInnerBorderColor(const State state, const Color &value);
			bool setBottomInnerBorderColor(const State state, const Color &value);
			bool setBackgroundColor(const State state, const Color &value);
			bool setShadowColor(const State state, const Color &value);
			bool setShadowShift(const State state, const PointF &value);
			bool setShadowRadius(const State state, const int value);
			bool setPadding(const State state, const RectF &value);
			bool setContentHorizontalAlign(const State state, const TextAlign value);
			bool setContentVerticalAlign(const State state, const VerticalAlign value);
			bool setCaptionColor(const State state, const Color &value);
			bool setCaptionShadowColor(const State state, const Color &value);
			bool setCaptionShadowShift(const State state, const PointF &value);
			bool setCaptionShadowRadius(const State state, const int value);
			bool setIconPadding(const State state, const float value);
			bool setIconOnRight(const State state, const bool value);
			// Set layout properties same for all states
			bool setOuterBorderWidth(const RectF &value);
			bool setInnerBorderWidth(const RectF &value);
			bool setBorderRadius(const RectF &value);
			bool setOuterBorderColor(const BorderColor &value);
			bool setInnerBorderColor(const BorderColor &value);
			bool setBackgroundColor(const Color &value);
			bool setShadowColor(const Color &value);
			bool setShadowShift(const PointF &value);
			bool setShadowRadius(const int value);
			bool setPadding(const RectF &value);
			bool setContentHorizontalAlign(const TextAlign value);
			bool setContentVerticalAlign(const VerticalAlign value);
			bool setCaptionColor(const Color &value);
			bool setCaptionShadowColor(const Color &value);
			bool setCaptionShadowShift(const PointF &value);
			bool setCaptionShadowRadius(const int value);
			bool setIconPadding(const float value);
			bool setIconOnRight(const bool value);

			void Click() override;
		};
	}
}
// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/Hotkey.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IHotKey.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CHotKeyService;

		class CHotKey :public virtual IHotKey, public CControl
		{
			friend CHotKeyService;
		public:
			enum class State // Possible states
			{
				Normal,
				Hovered,
				Focused,
				FocusedHovered,
				Disabled
			};
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CHotKey *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CHotKey *control);
			};
		private:
			CGradientListener m_cGradientListener;
			Hotkey m_sHotkey;
			RectF m_sBorderWidth;
			RectF m_sBorderRadius;
			RectF m_sPadding;
			BorderColor m_aBorderColor[(int)State::Disabled + 1];
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
			int m_aShadowRadius[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];
			Color m_aShadowColor[(int)State::Disabled + 1];
			Color m_aTextColor[(int)State::Disabled + 1];
			Color m_aTextShadowColor[(int)State::Disabled + 1];
			PointF m_aTextShadowShift[(int)State::Disabled + 1];
			int m_aTextShadowRadius[(int)State::Disabled + 1];

			bool m_bIgnoreGradient;
			ITexture *m_pCanvas;

			void UpdateFromStyle(IStyle *style);
			void Render();
		public:
			// IControl methods
			void Refresh(const bool refresh_children) override;

			RectF getClientRect() override;
			RectF getRenderRect() override;
			bool isWantTabs() override;

			bool setWantTabs(const bool value) override;
			bool setDPI(const Point &value) override;

			Hotkey getHotKey() override;

			bool setHotKey(const Hotkey &value) override;

			CHotKey();
			CHotKey(IControl *parent);
			CHotKey(IForm *parent);

			State getState(); // Return current state
			// Return layout properties
			RectF getBorderWidth() const;
			RectF getBorderRadius() const;
			RectF getPadding() const;
			BorderColor getBorderColor(const State state) const;
			Color getBackgroundColor(const State state) const;
			Gradient *getBackgroundGradient(const State state);
			int getShadowRadius(const State state) const;
			PointF getShadowShift(const State state) const;
			Color getShadowColor(const State state) const;
			Color getTextColor(const State state) const;
			Color getTextShadowColor(const State state) const;
			PointF getTextShadowShift(const State state) const;
			int getTextShadowRadius(const State state) const;

			// Set layout properties
			bool setBorderWidth(const RectF &value);
			bool setBorderRadius(const RectF &value);
			bool setPadding(const RectF &value);
			bool setBorderColor(const State state, const BorderColor &value);
			bool setLeftBorderColor(const State state, const Color &value);
			bool setTopBorderColor(const State state, const Color &value);
			bool setRightBorderColor(const State state, const Color &value);
			bool setBottomBorderColor(const State state, const Color &value);
			bool setBackgroundColor(const State state, const Color &value);
			bool setShadowRadius(const State state, const int value);
			bool setShadowShift(const State state, const PointF &value);
			bool setShadowColor(const State state, const Color &value);
			bool setTextColor(const State state, const Color &value);
			bool setTextShadowColor(const State state, const Color &value);
			bool setTextShadowShift(const State state, const PointF &value);
			bool setTextShadowRadius(const State state, const int value);
		};
	}
}
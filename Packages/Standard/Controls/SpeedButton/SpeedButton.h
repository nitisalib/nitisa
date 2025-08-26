// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../ISpeedButton.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class IImageList;

		class CSpeedButtonService;

		class CSpeedButton :public virtual ISpeedButton, public CControl
		{
			friend CSpeedButtonService;
		public:
			enum class State // Possible states
			{
				Normal,
				Hovered,
				Down,
				DownHovered,
				Focused,
				FocusedHovered,
				FocusedDown,
				FocusedDownHovered,
				Disabled
			};
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CSpeedButton *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CSpeedButton *control);
			};
		private:
			CGradientListener m_cGradientListener;
			int m_iGroupIndex;
			bool m_bDown;
			RectF m_aPadding[(int)State::Disabled + 1];
			RectF m_aOuterBorderWidth[(int)State::Disabled + 1];
			RectF m_aInnerBorderWidth[(int)State::Disabled + 1];
			RectF m_aBorderRadius[(int)State::Disabled + 1];
			BorderColor m_aOuterBorderColor[(int)State::Disabled + 1];
			BorderColor m_aInnerBorderColor[(int)State::Disabled + 1];
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
			IImageList *m_aImageList[(int)State::Disabled + 1];
			int m_aIconIndex[(int)State::Disabled + 1];
			Color m_aShadowColor[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];
			int m_aShadowRadius[(int)State::Disabled + 1];

			ITexture *m_pCanvas;
			bool m_bIgnoreGradient;

			bool DownExists();
			void ReleaseDown();
			void UpdateFromStyle(IStyle *style);
			void Render();
		public:
			void(*OnDown)(IControl *sender); // Event called when control becomes down
			void(*OnUp)(IControl *sender); // Event called when control loose down state

			// IControl methods
			void Refresh(const bool refresh_children) override;

			RectF getRenderRect() override;
			bool isFocusByMouse() override;

			int getGroupIndex() override;
			bool isDown() override;

			bool setDPI(const Point &value) override;
			bool setGroupIndex(const int value) override;
			bool setDown(const bool value) override;

			CSpeedButton();
			CSpeedButton(IForm *parent);
			CSpeedButton(IControl *parent);
			
			State getState(); // Return current state
			// Return layout properties
			RectF getPadding(const State state) const;
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
			IImageList *getImageList(const State state);
			int getIconIndex(const State state) const;
			Color getShadowColor(const State state) const;
			PointF getShadowShift(const State state) const;
			int getShadowRadius(const State state) const;

			// Set layout properties
			bool setPadding(const State state, const RectF &value);
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
			bool setImageList(const State state, IImageList *value);
			bool setImageList(IImageList *value);
			bool setIconIndex(const State state, const int value);
			bool setIconIndex(const int value);
			bool setShadowColor(const State state, const Color &value);
			bool setShadowShift(const State state, const PointF &value);
			bool setShadowRadius(const State state, const int value);
		};
	}
}
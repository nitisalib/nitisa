// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Math/PointF.h"
#include "../IToggle.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CToggle :public virtual IToggle, public CControl
		{
			friend class CToggleService;
		public:
			enum class State // Possible states
			{
				On,
				Off,
				Disabled
			};
		private:
			bool m_bOn;
			float m_aBackgroundBorderWidth[(int)State::Disabled + 1];
			Color m_aBackgroundBorderColor[(int)State::Disabled + 1];
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			float m_aBorderWidth[(int)State::Disabled + 1];
			Color m_aBorderColor[(int)State::Disabled + 1];
			Color m_aColor[(int)State::Disabled + 1];
			int m_aShadowRadius[(int)State::Disabled + 1];
			Color m_aShadowColor[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];

			ITexture *m_pCanvas;

			void UpdateFromStyle(IStyle *style);
			State getState();

			void Render();
		public:
			void(*OnToggle)(IControl *sender); // Event called when button is toggled via user input

			// IControl getters
			RectF getRenderRect() override;

			// IControl setters
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			// IToggle getters
			bool isOn() override;

			// IToggle setters
			bool setOn(const bool value) override;

			// IToggle methods
			void Toggle() override;

			CToggle();
			CToggle(IControl *parent);
			CToggle(IForm *parent);

			// Getters
			float getBackgroundBorderWidth(const State state);
			Color getBackgroundBorderColor(const State state);
			Color getBackgroundColor(const State state);
			float getBorderWidth(const State state);
			Color getBorderColor(const State state);
			Color getColor(const State state);
			int getShadowRadius(const State state);
			Color getShadowColor(const State state);
			PointF getShadowShift(const State state);

			// Setters
			bool setBackgroundBorderWidth(const State state, const float value);
			bool setBackgroundBorderColor(const State state, const Color &value);
			bool setBackgroundColor(const State state, const Color &value);
			bool setBorderWidth(const State state, const float value);
			bool setBorderColor(const State state, const Color &value);
			bool setColor(const State state, const Color &value);
			bool setShadowRadius(const State state, const int value);
			bool setShadowColor(const State state, const Color &value);
			bool setShadowShift(const State state, const PointF &value);
		};
	}
}
// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Math/RectF.h"
#include "../IViewH1H2.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IStyle;

	namespace ide
	{
		class CViewH1H2 :public virtual IViewH1H2, public CControl
		{
			friend class CViewH1H2Service;
		public:
			enum class State
			{
				Normal,
				Active
			};

			enum class View
			{
				None,
				Left,
				Right,
				Top
			};
		private:
			enum class Element
			{
				None,
				SeparatorH,
				SeparatorV
			};
		private:
			bool m_bResizable;
			float m_fSeparatorH;
			float m_fSeparatorV;
			View m_eActiveView;
			float m_fBorderWidth;
			float m_fSeparatorWidth;
			Color m_aBorderColor[(int)State::Active + 1];
			Color m_aSeparatorColor[(int)State::Active + 1];

			Element m_eDownElement;
			bool m_bAligningControls;

			// Helpers
			void UpdateFromStyle(IStyle *style);
			void AlignControls();
			RectF CalculateSeparatorHRect();
			RectF CalculateSeparatorVRect();
			RectF CalculateLeftViewRect();
			RectF CalculateRightViewRect();
			RectF CalculateTopViewRect();
			RectF CalculateLeftClientRect();
			RectF CalculateRightClientRect();
			RectF CalculateTopClientRect();

			// Render
			void Render();
		public:
			// IControl getters
			CursorType getCursor() override;

			// IViewControl methods
			bool ActivateView(const int index) override;

			// IViewH1H2 getters
			bool isResizable() override;
			float getSeparatorH() override;
			float getSeparatorV() override;

			// IViewH1H2 setters
			bool setResizable(const bool value) override;
			bool setSeparatorH(const float value) override;
			bool setSeparatorV(const float value) override;

			CViewH1H2();
			CViewH1H2(IForm *parent);
			CViewH1H2(IControl *parent);

			// Getters
			View getActiveView();
			float getBorderWidth();
			float getSeparatorWidth();
			Color getBorderColor(const State state);
			Color getSeparatorColor(const State state);

			// Setters
			bool setActiveView(const View value);
			bool setBorderWidth(const float value);
			bool setSeparatorWidth(const float value);
			bool setBorderColor(const State state, const Color &value);
			bool setSeparatorColor(const State state, const Color &value);
		};
	}
}
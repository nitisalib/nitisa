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
#include "../IViewH1H3.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IStyle;

	namespace ide
	{
		class CViewH1H3 :public virtual IViewH1H3, public CControl
		{
			friend class CViewH1H3Service;
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
				Middle,
				Right,
				Top
			};
		private:
			enum class Element
			{
				None,
				SeparatorV,
				SeparatorH1,
				SeparatorH2
			};
		private:
			bool m_bResizable;
			float m_fSeparatorV;
			float m_fSeparatorH1;
			float m_fSeparatorH2;
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
			RectF CalculateSeparatorVRect();
			RectF CalculateSeparatorH1Rect();
			RectF CalculateSeparatorH2Rect();
			RectF CalculateLeftViewRect();
			RectF CalculateMiddleViewRect();
			RectF CalculateRightViewRect();
			RectF CalculateTopViewRect();
			RectF CalculateLeftClientRect();
			RectF CalculateMiddleClientRect();
			RectF CalculateRightClientRect();
			RectF CalculateTopClientRect();

			// Render
			void Render();
		public:
			// IControl getters
			CursorType getCursor() override;

			// IViewControl methods
			bool ActivateView(const int index) override;

			// IViewH1H3 getters
			bool isResizable() override;
			float getSeparatorV() override;
			float getSeparatorH1() override;
			float getSeparatorH2() override;

			// IViewH1H3 setters
			bool setResizable(const bool value) override;
			bool setSeparatorV(const float value) override;
			bool setSeparatorH1(const float value) override;
			bool setSeparatorH2(const float value) override;

			CViewH1H3();
			CViewH1H3(IForm *parent);
			CViewH1H3(IControl *parent);

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
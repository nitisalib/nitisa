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
#include "../IViewV1V3.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IStyle;

	namespace ide
	{
		class CViewV1V3 :public virtual IViewV1V3, public CControl
		{
			friend class CViewV1V3Service;
		public:
			enum class State
			{
				Normal,
				Active
			};

			enum class View
			{
				None,
				Top,
				Middle,
				Bottom,
				Left
			};
		private:
			enum class Element
			{
				None,
				SeparatorH,
				SeparatorV1,
				SeparatorV2
			};
		private:
			bool m_bResizable;
			float m_fSeparatorH;
			float m_fSeparatorV1;
			float m_fSeparatorV2;
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
			RectF CalculateSeparatorV1Rect();
			RectF CalculateSeparatorV2Rect();
			RectF CalculateTopViewRect();
			RectF CalculateMiddleViewRect();
			RectF CalculateBottomViewRect();
			RectF CalculateLeftViewRect();
			RectF CalculateTopClientRect();
			RectF CalculateMiddleClientRect();
			RectF CalculateBottomClientRect();
			RectF CalculateLeftClientRect();

			// Render
			void Render();
		public:
			// IControl getters
			CursorType getCursor() override;

			// IViewControl methods
			bool ActivateView(const int index) override;

			// IViewV1V3 getters
			bool isResizable() override;
			float getSeparatorH() override;
			float getSeparatorV1() override;
			float getSeparatorV2() override;

			// IViewV1V3 setters
			bool setResizable(const bool value) override;
			bool setSeparatorH(const float value) override;
			bool setSeparatorV1(const float value) override;
			bool setSeparatorV2(const float value) override;

			CViewV1V3();
			CViewV1V3(IForm *parent);
			CViewV1V3(IControl *parent);

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
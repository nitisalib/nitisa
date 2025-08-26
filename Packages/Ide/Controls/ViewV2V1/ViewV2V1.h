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
#include "../IViewV2V1.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IStyle;

	namespace ide
	{
		class CViewV2V1 :public virtual IViewV2V1, public CControl
		{
			friend class CViewV2V1Service;
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
				Bottom,
				Right
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
			RectF CalculateTopViewRect();
			RectF CalculateBottomViewRect();
			RectF CalculateRightViewRect();
			RectF CalculateTopClientRect();
			RectF CalculateBottomClientRect();
			RectF CalculateRightClientRect();

			// Render
			void Render();
		public:
			// IControl getters
			CursorType getCursor() override;

			// IViewControl methods
			bool ActivateView(const int index) override;

			// IViewV2V1 getters
			bool isResizable() override;
			float getSeparatorH() override;
			float getSeparatorV() override;

			// IViewV2V1 setters
			bool setResizable(const bool value) override;
			bool setSeparatorH(const float value) override;
			bool setSeparatorV(const float value) override;

			CViewV2V1();
			CViewV2V1(IForm *parent);
			CViewV2V1(IControl *parent);

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
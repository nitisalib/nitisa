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
#include "../IViewV3.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IStyle;

	namespace ide
	{
		class CViewV3 :public virtual IViewV3, public CControl
		{
			friend class CViewV3Service;
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
				Bottom
			};
		private:
			enum class Element
			{
				None,
				Separator1,
				Separator2
			};
		private:
			bool m_bResizable;
			float m_fSeparator1;
			float m_fSeparator2;
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
			RectF CalculateSeparator1Rect();
			RectF CalculateSeparator2Rect();
			RectF CalculateTopViewRect();
			RectF CalculateMiddleViewRect();
			RectF CalculateBottomViewRect();
			RectF CalculateTopClientRect();
			RectF CalculateMiddleClientRect();
			RectF CalculateBottomClientRect();

			// Render
			void Render();
		public:
			// IControl getters
			CursorType getCursor() override;

			// IViewControl methods
			bool ActivateView(const int index) override;

			// IViewV3 getters
			bool isResizable() override;
			float getSeparator1() override;
			float getSeparator2() override;

			// IViewV3 setters
			bool setResizable(const bool value) override;
			bool setSeparator1(const float value) override;
			bool setSeparator2(const float value) override;

			CViewV3();
			CViewV3(IForm *parent);
			CViewV3(IControl *parent);

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
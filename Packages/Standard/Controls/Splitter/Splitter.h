// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Align.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "../ISplitter.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CSplitterService;

		class CSplitter :public virtual ISplitter, public CControl
		{
			friend CSplitterService;
		public:
			enum class State // Possible states
			{
				Normal,
				Hovered,
				Active,
				Disabled
			};
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CSplitter *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CSplitter *control);
			};
		private:
			CGradientListener m_cGradientListener;
			float m_fDotWidth;
			int m_iDotCount;
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
			Color m_aDotColor[(int)State::Disabled + 1];

			bool m_bIgnoreGradient;
			ITexture *m_pCanvas;
			bool m_bActive;

			void UpdateFromStyle(IStyle *style);
			void Render();
		public:
			bool setAlign(const Align value) override;
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			CSplitter();
			CSplitter(IControl *parent);
			CSplitter(IForm *parent);

			State getState(); // Return current state
			// Return layout properties
			float getDotWidth() const;
			int getDotCount() const;
			Color getBackgroundColor(const State state) const;
			Gradient *getBackgroundGradient(const State state);
			Color getDotColor(const State state) const;

			// Set layout properties
			bool setDotWidth(const float value);
			bool setDotCount(const int value);
			bool setBackgroundColor(const State state, const Color &value);
			bool setDotColor(const State state, const Color &value);
		};
	}
}
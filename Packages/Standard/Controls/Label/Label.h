// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Align.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/TextAlign.h"
#include "Nitisa/Core/VerticalAlign.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../ILabel.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CLabelService;

		class CLabel :public virtual ILabel, public CControl
		{
			friend CLabelService;
		public:
			enum class State // Possible states
			{
				Normal,
				Hovered,
				Disabled
			};
		private:
			String m_sCaption;
			TextAlign m_eCaptionHorizontalAlign;
			VerticalAlign m_eCaptionVerticalAlign;
			bool m_bAutoSize; // For non-aligned label only
			bool m_bMultiline;
			Color m_aColor[(int)State::Disabled + 1];
			Color m_aShadowColor[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];
			int m_aShadowRadius[(int)State::Disabled + 1];

			StringArray m_aLines;
			ITexture *m_pCanvas;
			bool m_bCaptionChanged;

			void UpdateLines();
			void UpdateAutoSize();
			void UpdateFromStyle(IStyle *style);
			RectF getRenderRect(const State state);
			void Render();
		public:
			RectF getRenderRect() override;
			String getCaption() override;

			bool setAlign(const Align value) override;
			bool setConstraints(const RectF &value) override;
			bool setSize(const PointF &value) override;
			bool setCaption(const String &value) override;
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			CLabel();
			CLabel(IControl *parent);
			CLabel(IForm *parent);

			State getState(); // Return current state
			bool isAutoSize() const; // Whether size should be calculated automatically to fit content. By default true
			bool isMultiline() const; // Whether display as multiline text. By default false
			// Return layout properties
			TextAlign getCaptionHorizontalAlign() const;
			VerticalAlign getCaptionVerticalAlign() const;
			Color getColor(const State state) const;
			Color getShadowColor(const State state) const;
			PointF getShadowShift(const State state) const;
			int getShadowRadius(const State state) const;

			bool setAutoSize(const bool value); // Set whether size should be calculated automatically to fit content
			bool setMultiline(const bool value);
			// Set layout properties
			bool setCaptionHorizontalAlign(const TextAlign value);
			bool setCaptionVerticalAlign(const VerticalAlign value);
			bool setColor(const State state, const Color &value);
			bool setShadowColor(const State state, const Color &value);
			bool setShadowShift(const State state, const PointF &value);
			bool setShadowRadius(const State state, const int value);
		};
	}
}
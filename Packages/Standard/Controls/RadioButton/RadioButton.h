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
#include "../IRadioButton.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CRadioButtonService;

		class CRadioButton :public virtual IRadioButton, public CControl
		{
			friend CRadioButtonService;
		public:
			enum class State // Possible states
			{
				Normal,
				Hovered,
				Focused,
				FocusedHovered,
				Active,
				ActiveHovered,
				Disabled
			};
		private:
			String m_sCaption;
			TextAlign m_eContentHorizontalAlign;
			VerticalAlign m_eContentVerticalAlign;
			bool m_bIconOnRight;
			bool m_bAutoSize;
			float m_fIconPadding;
			int m_iGroupIndex;
			bool m_bChecked;
			Color m_aColor[(int)State::Disabled + 1];
			Color m_aShadowColor[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];
			int m_aShadowRadius[(int)State::Disabled + 1];

			bool m_bMouseDown;
			ITexture *m_pCanvas;
			bool m_bCaptionChanged;

			ITexture *FindIcon(const State state, RectF &part);
			void UpdateAutoSize();
			void UpdateFromStyle(IStyle *style);
			bool HaveCheckedOnParent();
			void UncheckAllOnParent();
			RectF getRenderRect(const State state);
			void Render();
		public:
			void(*OnChange)(IControl *sender); // Event called when checked/unchecked state changes

			// IControl methods
			void Refresh(const bool refresh_children) override;

			RectF getRenderRect() override;
			
			bool setAlign(const Align value) override;
			bool setConstraints(const RectF &value) override;
			bool setSize(const PointF &value) override;
			bool setDPI(const Point &value) override;

			String getCaption() override;
			int getGroupIndex() override;
			bool isChecked() override;

			bool setCaption(const String &value) override;
			bool setGroupIndex(const int value) override;
			bool setChecked(const bool value) override;

			CRadioButton();
			CRadioButton(IControl *parent);
			CRadioButton(IForm *parent);

			State getState(); // Return current state
			// Return layout properties
			TextAlign getContentHorizontalAlign() const;
			VerticalAlign getContentVerticalAlign() const;
			bool isIconOnRight() const;
			bool isAutoSize() const;
			float getIconPadding() const;
			Color getColor(const State state) const;
			Color getShadowColor(const State state) const;
			PointF getShadowShift(const State state) const;
			int getShadowRadius(const State state) const;

			// Set layout properties
			bool setContentHorizontalAlign(const TextAlign value);
			bool setContentVerticalAlign(const VerticalAlign value);
			bool setIconOnRight(const bool value);
			bool setAutoSize(const bool value);
			bool setIconPadding(const float value);
			bool setColor(const State state, const Color &value);
			bool setShadowColor(const State state, const Color &value);
			bool setShadowShift(const State state, const PointF &value);
			bool setShadowRadius(const State state, const int value);
		};
	}
}
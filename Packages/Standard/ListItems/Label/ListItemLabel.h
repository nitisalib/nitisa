// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ListItem.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/TextAlign.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IListItemLabel.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class IFont;
	class IListItem;
	class IListItemService;
	class IPlatformFont;
	class IRenderer;
	class IStyle;
	class ITexture;

	struct Block;

	namespace standard
	{
		class CListItemLabelService;

		class CListItemLabel :public virtual IListItemLabel, public CListItem
		{
			friend CListItemLabelService;
		public:
			enum class State // Possible states
			{
				Normal,
				Hovered,
				Selected,
				SelectedHovered,
				Active,
				ActiveHovered,
				ActiveSelected,
				ActiveSelectedHovered,
				Disabled
			};
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CListItemLabel *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CListItemLabel *control);
			};
		private:
			CGradientListener m_cGradientListener;
			IListItemService *m_pService;
			String m_sCaption;
			TextAlign m_eAlign;
			RectF m_sPadding;
			Color m_aColor[(int)State::Disabled + 1];
			Color m_aShadowColor[(int)State::Disabled + 1];
			int m_aShadowRadius[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
			RectF m_aBorderWidth[(int)State::Disabled + 1];
			RectF m_aBorderRadius[(int)State::Disabled + 1];
			BorderColor m_aBorderColor[(int)State::Disabled + 1];

			bool m_bIgnoreGradient;

			PointF CalculateTextPosition();
			void UpdateFromStyle(IStyle *style);
			void Render(const Mat4f &matrix, const Block *block, ITexture **clip);
			void RenderParts(const RectF &rect_clip, IRenderer *renderer, IFont *font, IPlatformFont *pf, const PointF &text_position,
				const Color &text_color, const Color &shadow_color, const int shadow_radius, const PointF &shadow_shift);
		public:
			void(*OnClick)(IListItem *sender); // Event called when clicked

			CListItemLabel();
			CListItemLabel(const String &caption);
			~CListItemLabel() override;

			IListItemService *QueryService() override;

			String getCaption() override;
			bool setCaption(const String &value) override;

			IListItem *Clone() override;
			bool Copy(IListItem *dest) override;

			State getState(); // Return current state
			// Return layout properties
			TextAlign getAlign();
			RectF getPadding() const;
			Color getColor(const State state) const;
			Color getShadowColor(const State state) const;
			int getShadowRadius(const State state) const;
			PointF getShadowShift(const State state) const;
			Color getBackgroundColor(const State state) const;
			Gradient *getBackgroundGradient(const State state);
			RectF getBorderWidth(const State state) const;
			RectF getBorderRadius(const State state) const;
			BorderColor getBorderColor(const State state) const;
			Color getLeftBorderColor(const State state) const;
			Color getTopBorderColor(const State state) const;
			Color getRightBorderColor(const State state) const;
			Color getBottomBorderColor(const State state) const;

			// Set layout properties
			bool setAlign(const TextAlign value);
			bool setPadding(const RectF &value);
			bool setColor(const State state, const Color &value);
			bool setShadowColor(const State state, const Color &value);
			bool setShadowRadius(const State state, const int value);
			bool setShadowShift(const State state, const PointF &value);
			bool setBackgroundColor(const State state, const Color &value);
			bool setBorderWidth(const State state, const RectF &value);
			bool setBorderRadius(const State state, const RectF &value);
			bool setBorderColor(const State state, const BorderColor &value);
			bool setLeftBorderColor(const State state, const Color &value);
			bool setTopBorderColor(const State state, const Color &value);
			bool setRightBorderColor(const State state, const Color &value);
			bool setBottomBorderColor(const State state, const Color &value);
		};
	}
}
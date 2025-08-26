// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../Menu/ListItemMenu.h"
#include "../IListItemRadioButton.h"

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
		class CListItemMenuRadioButtonService;

		class CListItemMenuRadioButton :public virtual IListItemRadioButton, public CListItemMenu
		{
			friend CListItemMenuRadioButtonService;
		public:
			enum class State // Possible states
			{
				Normal,
				Active,
				Disabled
			};
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CListItemMenuRadioButton *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CListItemMenuRadioButton *control);
			};
		private:
			CGradientListener m_cGradientListener;
			int m_iGroupIndex;
			bool m_bChecked;
			RectF m_sIconPadding;
			RectF m_sCaptionPadding;
			RectF m_sHotkeyPadding;
			String m_sCaption;
			Color m_aColor[(int)State::Disabled + 1];
			Color m_aShadowColor[(int)State::Disabled + 1];
			int m_aShadowRadius[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			RectF m_aBorderWidth[(int)State::Disabled + 1];
			RectF m_aBorderRadius[(int)State::Disabled + 1];
			BorderColor m_aBorderColor[(int)State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
			Color m_aIconBackgroundColor[(int)State::Disabled + 1];

			IListItemMenuService *m_pService;
			float m_fIconWidth;
			float m_fHotkeyWidth;
			bool m_bIgnoreGradient;

			void UpdateFromStyle(IStyle *style);
			ITexture *FindIcon(RectF &part);
			bool HaveCheckedOnParent();
			void UncheckAllOnParent();
			void Render(const Mat4f &matrix, const Block *block, ITexture **clip);
			void RenderParts(const State state, const RectF &rect_clip, IRenderer *renderer, IFont *font, IPlatformFont *pf, const String &hotkeys, IListItemMenuOwner *owner,
				const Color &text_color, const Color &shadow_color, const int shadow_radius, const PointF &shadow_shift);
		public:
			void(*OnChange)(IListItem *sender); // Event called when checked state changed

			CListItemMenuRadioButton();
			CListItemMenuRadioButton(const String &caption);
			~CListItemMenuRadioButton() override;

			bool setSelected(const bool value) override;

			bool AddItem(IListItem *item) override;
			bool InsertItem(IListItem *item, const int before) override;

			IListItemService *QueryService() override;

			String getCaption() override;
			bool isChecked() override;
			int getGroupIndex() override;

			bool setCaption(const String &value) override;
			bool setChecked(const bool value) override;
			bool setGroupIndex(const int value) override;

			IListItem *Clone() override;
			bool Copy(IListItem *dest) override;

			State getState(); // Return current state
			// Return layout properties
			RectF getIconPadding() const;
			RectF getCaptionPadding() const;
			RectF getHotkeyPadding() const;
			Color getColor(const State state) const;
			Color getShadowColor(const State state) const;
			int getShadowRadius(const State state) const;
			PointF getShadowShift(const State state) const;
			Color getBackgroundColor(const State state) const;
			RectF getBorderWidth(const State state) const;
			RectF getBorderRadius(const State state) const;
			BorderColor getBorderColor(const State state) const;
			Color getLeftBorderColor(const State state) const;
			Color getTopBorderColor(const State state) const;
			Color getRightBorderColor(const State state) const;
			Color getBottomBorderColor(const State state) const;
			Gradient *getBackgroundGradient(const State state);
			Color getIconBackgroundColor(const State state) const;

			// Set layout properties
			bool setIconPadding(const RectF &value);
			bool setCaptionPadding(const RectF &value);
			bool setHotkeyPadding(const RectF &value);
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
			bool setIconBackgroundColor(const State state, const Color &value);
		};
	}
}
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
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/RectF.h"
#include "../IListItemTreeViewLabel.h"

namespace nitisa
{
	class IListItem;
	class IListItemService;
	class IRenderer;
	class IStyle;
	class ITexture;

	struct Block;

	namespace standard
	{
		class CListItemTreeViewLabelService;

		class CListItemTreeViewLabel :public virtual IListItemTreeViewLabel, public CListItem
		{
			friend CListItemTreeViewLabelService;
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
				CListItemTreeViewLabel *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CListItemTreeViewLabel *control);
			};
		private:
			CGradientListener m_cGradientListener;
			String m_sCaption;
			int m_iIconIndex;
			RectF m_aBorderWidth[(int)State::Disabled + 1];
			RectF m_aBorderRadius[(int)State::Disabled + 1];
			RectF m_aPadding[(int)State::Disabled + 1]; // No border. Left padding is from image, not from bound
			RectF m_aIconPadding[(int)State::Disabled + 1]; // No border. Image width is equal to list item height
			BorderColor m_aBorderColor[(int)State::Disabled + 1];
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
			Color m_aColor[(int)State::Disabled + 1];

			IListItemService *m_pService;
			bool m_bIgnoreGradient;

			void UpdateFromStyle(IStyle *style);
			void Render(const Mat4f &matrix, const Block *block, ITexture **clip);
			void RenderIcon(IRenderer *renderer, const State state);
			void RenderCaption(IRenderer *renderer, const State state);
		protected:
			virtual Color getCustomColor(const State state); // Return color depending on state if its alpha channel is > 0. Otherwise return control font color. May be used to return custom color for item text
		public:
			IListItemTreeViewLabel *getSpecificItem(const int index) override;
			String getCaption() override;
			int getIconIndex() override;

			bool setCaption(const String &value) override;
			bool setIconIndex(const int value) override;

			IListItem *Clone() override;
			bool Copy(IListItem *dest) override;
			IListItemService *QueryService() override;

			bool Add(const String &caption) override;
			bool Add(IListItemTreeViewLabel *item) override;
			bool Insert(const String &caption, const int before) override;
			bool Insert(IListItemTreeViewLabel *item, const int before) override;

			CListItemTreeViewLabel();
			CListItemTreeViewLabel(const String &caption);
			~CListItemTreeViewLabel();

			State getState(); // Return current state
			// Return layout properties
			RectF getBorderWidth(const State state) const;
			RectF getBorderRadius(const State state) const;
			RectF getPadding(const State state) const;
			RectF getIconPadding(const State state) const;
			BorderColor getBorderColor(const State state) const;
			Color getBackgroundColor(const State state) const;
			Gradient *getBackgroundGradient(const State state);
			Color getColor(const State state) const;

			// Set layout properties
			bool setBorderWidth(const State state, const RectF &value);
			bool setBorderRadius(const State state, const RectF &value);
			bool setPadding(const State state, const RectF &value);
			bool setIconPadding(const State state, const RectF &value);
			bool setBorderColor(const State state, const BorderColor &value);
			bool setBackgroundColor(const State state, const Color &value);
			bool setColor(const State state, const Color &value);
		};
	}
}
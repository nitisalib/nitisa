// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IIconButton.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class IImageList;

		class CIconButtonService;

		class CIconButton :public virtual IIconButton, public CControl
		{
			friend CIconButtonService;
		public:
			enum class State // Possible states
			{
				Normal, // Normal
				Hovered, // Hovered
				Focused, // Focused
				FocusedHovered, // Focused and hovered
				Active, // Active(mouse was down but not released)
				ActiveHovered, // Active and hovered
				Disabled // Disabled
			};

			enum class IconSize // How icon should be displayed
			{
				Original, // Show original size image
				Contain, // Show full image scaled without distortions
				Cover, // Show image scaled without distortions to fill entire client area of button
				Stretch // Show stretched image filling entire client area
			};
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CIconButton *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CIconButton *control);
			};
		private:
			CGradientListener m_cGradientListener;
			RectF m_aOuterBorderWidth[(int)State::Disabled + 1];
			RectF m_aInnerBorderWidth[(int)State::Disabled + 1];
			RectF m_aBorderRadius[(int)State::Disabled + 1];
			BorderColor m_aOuterBorderColor[(int)State::Disabled + 1];
			BorderColor m_aInnerBorderColor[(int)State::Disabled + 1];
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
			Color m_aShadowColor[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];
			int m_aShadowRadius[(int)State::Disabled + 1];
			RectF m_aPadding[(int)State::Disabled + 1];
			IImageList *m_aImageList[(int)State::Disabled + 1];
			int m_aIconIndex[(int)State::Disabled + 1];
			unsigned int m_aOutlineMask[(int)State::Disabled + 1];
			Color m_aOutlineColor[(int)State::Disabled + 1];
			IconSize m_eIconSize;
			bool m_bOutlineInEditor;

			ITexture *m_pCanvas;
			bool m_bKeyDown;
			bool m_bMouseDown;
			bool m_bIgnoreGradient;

			void UpdateFromStyle(IStyle *style);
			RectF getRenderRect(const State state);
			void Render();
			void RenderOutline(IRenderer *renderer, const RectF &rect, const State state);
			void RenderContent(const State state, IRenderer *renderer, const RectF &rect);
			void RenderOriginal(IRenderer *renderer, const State state, const RectF &rect, const RectF &client, ITexture *icon);
			void RenderContain(IRenderer *renderer, const State state, const RectF &client, ITexture *icon);
			void RenderCover(IRenderer *renderer, const State state, const RectF &rect, const RectF &client, ITexture *icon);
			void RenderStretch(IRenderer *renderer, const State state, const RectF &client, ITexture *icon);
		public:
			void(*OnClick)(IControl *sender); // Event called when click on the button(or Enter)

			// IControl getters
			RectF getClientRect() override;
			RectF getRenderRect() override;

			// IControl setters
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			// IIconButton methods
			void Click() override;

			CIconButton();
			CIconButton(IControl *parent);
			CIconButton(IForm *parent);

			State getState(); // Return state
			// Return layout properties depending on state
			RectF getOuterBorderWidth(const State state) const;
			RectF getInnerBorderWidth(const State state) const;
			RectF getBorderRadius(const State state) const;
			BorderColor getOuterBorderColor(const State state) const;
			BorderColor getInnerBorderColor(const State state) const;
			Color getBackgroundColor(const State state) const;
			Gradient *getBackgroundGradient(const State state);
			Color getShadowColor(const State state) const;
			PointF getShadowShift(const State state) const;
			int getShadowRadius(const State state) const;
			RectF getPadding(const State state) const;
			IImageList *getImageList(const State state) const; // Return associated image list
			int getIconIndex(const State state) const; // Return icon index from image list to be displayed or -1
			unsigned int getOutlineMask(const State state) const; // Return outline mask depending on state
			Color getOutlineColor(const State state) const; // Return outline color depending on state
			IconSize getIconSize() const;
			bool isOutlineInEditor() const; // Return whether the widget should be outlined in the Form Builder

			// Set layout properties depending on state
			bool setOuterBorderWidth(const State state, const RectF &value);
			bool setInnerBorderWidth(const State state, const RectF &value);
			bool setBorderRadius(const State state, const RectF &value);
			bool setOuterBorderColor(const State state, const BorderColor &value);
			bool setInnerBorderColor(const State state, const BorderColor &value);
			bool setBackgroundColor(const State state, const Color &value);
			bool setShadowColor(const State state, const Color &value);
			bool setShadowShift(const State state, const PointF &value);
			bool setShadowRadius(const State state, const int value);
			bool setPadding(const State state, const RectF &value);
			bool setImageList(const State state, IImageList *value);
			bool setIconIndex(const State state, const int value);
			bool setOutlineMask(const State state, const unsigned int value); // Set outline mask
			bool setOutlineColor(const State state, const Color &value); // Set outline color
			bool setIconSize(const IconSize value);
			bool setOutlineInEditor(const bool value); // Set whether the widget should be outlined in the Form Builder
			// Set layout properties same for all states
			bool setOuterBorderWidth(const RectF &value);
			bool setInnerBorderWidth(const RectF &value);
			bool setBorderRadius(const RectF &value);
			bool setOuterBorderColor(const BorderColor &value);
			bool setInnerBorderColor(const BorderColor &value);
			bool setBackgroundColor(const Color &value);
			bool setShadowColor(const Color &value);
			bool setShadowShift(const PointF &value);
			bool setShadowRadius(const int value);
			bool setPadding(const RectF &value);
			bool setImageList(IImageList *value);
			bool setIconIndex(const int value);
		};
	}
}
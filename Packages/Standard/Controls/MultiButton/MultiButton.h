// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Consts.h"
#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/Align.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/ListItemOwner.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/TextAlign.h"
#include "Nitisa/Core/VerticalAlign.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Interfaces/ITimerListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IMultiButton.h"
#include <vector>

namespace nitisa
{
	class IControl;
	class IForm;
	class IListItem;
	class IListItemOwner;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class IImageList;
		class IListItemButtonList;

		class CMultiButtonService;

		class CMultiButton :public virtual IMultiButton, public CControl
		{
			friend CMultiButtonService;
		public:
			enum class State // Describes possible states
			{
				Normal, // Normal
				Hovered, // Mouse pointer is over
				Focused, // Focused
				FocusedHovered, // Focused and mouse pointer is over
				Down, // Left mouse button or Return key is down and not yet released
				DownHovered, // Down + mouse pointer is over
				DownFocused, // Down and focused
				DownFocusedHovered, // Down, focused and mouse pointer is over
				Active, // Button is active
				ActiveHovered, // Button is active and mouse pointer is over it
				Inactive, // Button is inactive
				InactiveHovered, // Button is inactive and mouse pointer is over it
				Disabled // Disabled
			};

			enum class OpenDirection // Open directions
			{
				Left, // To the left of the widget
				Top, // To the top of the widget
				Right, // To the right of the widget
				Bottom // To the bottom of the widget
			};

			enum class ImageSize // Image sizes
			{
				Original, // Original size. Image is in the center of client area
				Cover, // Image size is changed with saving proportions so it covers a button. Image is in the center of client area
				Contain, // Image size is changed with saving proportions so it completely fit int a button. Image is in the center of client area
				Stretch // Image is stretched without saving proportions and it wills entire client area of a button
			};
		private:
			class COwner :public CListItemOwner
			{
			private:
				CMultiButton *m_pControl;
			public:
				IControl *getControl() override;
				IRenderer *getRenderer() override;
				IFont *getFont(IListItem *item) override;
				IStyle *getStyle(IListItem *item) override;

				void NotifyOnSizeChange(IListItem *item) override;
				void NotifyOnRepaintRequired(IListItem *item) override;
				void NotifyOnBeforeAddItem(IListItem *item, IListItem *parent) override;
				void NotifyOnAddItem(IListItem *item) override;
				void NotifyOnBeforeDeleteItem(IListItem *item) override;
				void NotifyOnDeleteItem(IListItem *item, IListItem *parent) override;
				void NotifyOnBeforeDeleteItems(IListItem *parent) override;
				void NotifyOnDeleteItems(IListItem *parent) override;
				void NotifyOnShow(IListItem *item) override;
				void NotifyOnHide(IListItem *item) override;
				void NotifyOnEnable(IListItem *item) override;
				void NotifyOnDisable(IListItem *item) override;
				void NotifyOnSelect(IListItem *item) override;
				void NotifyOnDeselect(IListItem *item) override;
				void NotifyOnActivate(IListItem *item) override;
				void NotifyOnDeactivate(IListItem *item) override;

				COwner(CMultiButton *control);
			};

			class CTimerListener :public virtual ITimerListener
			{
			private:
				CMultiButton *m_pControl;
			public:
				void NotifyOnTimer(const PlatformHandle id) override;

				CTimerListener(CMultiButton *control);
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CMultiButton *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CMultiButton *control);
			};
		private:
			CGradientListener m_cGradientListener;
			bool m_bHasExtra;
			float m_fDelay;
			int m_iActiveButtonIndex;
			IImageList *m_pImageList;
			OpenDirection m_eOpenDirection;
			unsigned int m_aOutlineMask[(int)State::Disabled + 1];
			Color m_aOutlineColor[(int)State::Disabled + 1];
			float m_aOpenerSize[(int)State::Disabled + 1];
			Color m_aOpenerColor[(int)State::Disabled + 1];
			RectF m_aBorderRadius[(int)State::Disabled + 1];
			RectF m_aOuterBorderWidth[(int)State::Disabled + 1];
			BorderColor m_aOuterBorderColor[(int)State::Disabled + 1];
			RectF m_aInnerBorderWidth[(int)State::Disabled + 1];
			BorderColor m_aInnerBorderColor[(int)State::Disabled + 1];
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
			RectF m_aPadding[(int)State::Disabled + 1];
			ImageSize m_aImageSize[(int)State::Disabled + 1];
			TextAlign m_aCaptionHorizontalAlign[(int)State::Disabled + 1];
			VerticalAlign m_aCaptionVerticalAlign[(int)State::Disabled + 1];
			Color m_aCaptionColor[(int)State::Disabled + 1];
			int m_aShadowRadius[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];
			Color m_aShadowColor[(int)State::Disabled + 1];
						
			COwner m_cOwner;
			ITexture *m_pCanvas;
			ITexture *m_pCanvasExtra;
			bool m_bIgnoreGradient;
			std::vector<IListItem*> m_aButtons;
			PlatformHandle m_hTimer;
			bool m_bEnterDown;
			int m_iHoveredButtonIndex; // -2 = nothing, -1 = control main area, >= 0 - button in list
			CTimerListener m_cTimerListener;

			void UpdateFromStyle(IStyle *style);
			bool UpdateHoveredButtonIndex();
			bool UpdateHoveredButtonIndex(const PointF &p);
			RectF CalculateExtraRect();
			RectF CalculateButtonRect(const int index);
			State CalculateState(); // Main part state
			State CalculateState(const int index); // Button in shown list state
			int CalculateButtonImageIndex(IListItemMultiButton *button, const State state);
			void Render();
			void RenderOutline(IRenderer *renderer, const RectF &rect, const State state);
			void RenderOpener(IRenderer *renderer, const RectF &rect, const State state);
			void RenderButton(IRenderer *renderer, const RectF &rect, const State state, IListItemMultiButton *button);
			void RenderExtra();
		protected:
			void SortItems() override; // No sorting
			void BeforeRelease() override;
		public:
			// IControl getters
			IControl *getControl(const int index) override;
			IControl *getControl(const String &name) override;
			IControl *getControl(const PointF &position) override;
			RectF getRenderRect() override;
			bool hasExtra() override;

			// IControl setters
			bool setAlign(const Align value) override;
			bool setDPI(const Point &value) override;

			// IComponentItemList getters
			int getItemCount() override;
			IListItem *getItem(const int index) override;
			int getItemIndex(IListItem *item) override;
			bool isAcceptItem(IListItem *item) override;

			// IComponentItemList items
			bool AddItem(IListItem *item) override;
			bool InsertItem(IListItem *item, const int before) override;
			bool DeleteItem(const int index) override;
			bool DeleteItem(IListItem *item) override;
			bool DeleteItems() override;

			// IComponentItemList methods
			IListItemOwner *QueryListItemOwner() override;

			// IButtonList getters
			float getDelay() override;
			int getButtonCount() override;
			IListItemMultiButton *getButton(const int index) override;
			int getButtonIndex(IListItemMultiButton *item) override;
			int getActiveButtonIndex() override;
			IListItemMultiButton *getActiveButton() override;

			// IButtonList setters
			bool setDelay(const float value, const float tolerance = ntl::Tolerance<float>) override;
			bool setActiveButtonIndex(const int value) override;
			bool setActiveButton(IListItemMultiButton *value) override;

			// IButtonList buttons
			bool AddButton(IListItemMultiButton *item) override;
			IListItemMultiButton *AddButton(const String &caption) override;
			bool InsertButton(IListItemMultiButton *item, const int before) override;
			IListItemMultiButton *InsertButton(const String &caption, const int before) override;
			bool DeleteButton(const int index) override;
			bool DeleteButton(IListItemMultiButton *item) override;
			bool DeleteButtons() override;

			CMultiButton();
			CMultiButton(IControl *parent);
			CMultiButton(IForm *parent);

			// Getters
			IImageList *getImageList();
			OpenDirection getOpenDirection() const;
			unsigned int getOutlineMask(const State state) const;
			Color getOutlineColor(const State state) const;
			float getOpenerSize(const State state) const;
			Color getOpenerColor(const State state) const;
			RectF getBorderRadius(const State state) const;
			RectF getOuterBorderWidth(const State state) const;
			BorderColor getOuterBorderColor(const State state) const;
			RectF getInnerBorderWidth(const State state) const;
			BorderColor getInnerBorderColor(const State state) const;
			Color getBackgroundColor(const State state) const;
			Gradient *getBackgroundGradient(const State state);
			RectF getPadding(const State state) const;
			ImageSize getImageSize(const State state) const;
			TextAlign getCaptionHorizontalAlign(const State state) const;
			VerticalAlign getCaptionVerticalAlign(const State state) const;
			Color getCaptionColor(const State state) const;
			int getShadowRadius(const State state) const;
			PointF getShadowShift(const State state) const;
			Color getShadowColor(const State state) const;

			// Setters
			bool setImageList(IImageList *value);
			bool setOpenDirection(const OpenDirection value);
			bool setOutlineMask(const State state, const unsigned int value);
			bool setOutlineColor(const State state, const Color &value);
			bool setOpenerSize(const State state, const float value, const float tolerance = ntl::Tolerance<float>);
			bool setOpenerColor(const State state, const Color &value);
			bool setBorderRadius(const State state, const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setOuterBorderWidth(const State state, const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setOuterBorderColor(const State state, const BorderColor &value);
			bool setInnerBorderWidth(const State state, const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setInnerBorderColor(const State state, const BorderColor &value);
			bool setBackgroundColor(const State state, const Color &value);
			bool setPadding(const State state, const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setImageSize(const State state, const ImageSize value);
			bool setCaptionHorizontalAlign(const State state, const TextAlign value);
			bool setCaptionVerticalAlign(const State state, const VerticalAlign value);
			bool setCaptionColor(const State state, const Color &value);
			bool setShadowRadius(const State state, const int value);
			bool setShadowShift(const State state, const PointF &value, const float tolerance = ntl::Tolerance<float>);
			bool setShadowColor(const State state, const Color &value);
			// Layout setters applying to all states at once
			bool setOutlineMask(const unsigned int value);
			bool setOutlineColor(const Color &value);
			bool setOpenerSize(const float value, const float tolerance = ntl::Tolerance<float>);
			bool setOpenerColor(const Color &value);
			bool setBorderRadius(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setOuterBorderWidth(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setOuterBorderColor(const BorderColor &value);
			bool setInnerBorderWidth(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setInnerBorderColor(const BorderColor &value);
			bool setBackgroundColor(const Color &value);
			bool setPadding(const RectF &value, const float tolerance = ntl::Tolerance<float>);
			bool setImageSize(const ImageSize value);
			bool setCaptionHorizontalAlign(const TextAlign value);
			bool setCaptionVerticalAlign(const VerticalAlign value);
			bool setCaptionColor(const Color &value);
			bool setShadowRadius(const int value);
			bool setShadowShift(const PointF &value, const float tolerance = ntl::Tolerance<float>);
			bool setShadowColor(const Color &value);
		};
	}
}
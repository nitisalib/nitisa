// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/Align.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/Hotkey.h"
#include "Nitisa/Core/ListItemOwner.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../../ListItems/Menu/ListItemMenu.h"
#include "../../ListItems/IListItemMenu.h"
#include "../IMainMenu.h"
#include <chrono>
#include <vector>

namespace nitisa
{
	class IControl;
	class IFont;
	class IForm;
	class IListItem;
	class IListItemOwner;
	class IRenderer;
	class IStyle;
	class ITexture;
	class ITransform;

	struct Block;

	namespace standard
	{
		class IImageList;
		class CMainMenuService;

		// This main menu show itself in client area of form, so it cannot be places on another controls and cannot have any transformations except for Tx and Ty
		class CMainMenu :public virtual IMainMenu, public CControl
		{
			friend CMainMenuService;
		public:
			enum class State // Possible states
			{
				Normal,
				Active
			};
		private:
			class CMainMenuListItemOwner :public virtual IListItemMenuOwner, public CListItemOwner
			{
			private:
				CMainMenu *m_pMenu;

				bool DeleteItem(IListItem *item);
				void UpdateAndRepaint(IListItem *parent);
				void UpdateItemOwner(IListItem *item, IListItemOwner *owner);
			public:
				CMainMenuListItemOwner(CMainMenu *menu);

				IControl *getControl() override;
				IRenderer *getRenderer() override;
				IFont *getFont(IListItem *item) override;
				IStyle *getStyle(IListItem *item) override;
				ITexture *getImage(const bool enabled, const bool active, const bool hovered, const int index, RectF &rect) override;

				void NotifyOnSizeChange(IListItem *item) override;
				void NotifyOnRepaintRequired(IListItem *item) override;
				void NotifyOnBeforeAddItem(IListItem *item, IListItem *parent) override;
				void NotifyOnAddItem(IListItem *item) override;
				void NotifyOnBeforeDeleteItem(IListItem *item) override;
				void NotifyOnDeleteItem(IListItem *item, IListItem *parent) override;
				void NotifyOnBeforeDeleteItems(IListItem *parent) override;
				void NotifyOnDeleteItems(IListItem *parent) override;
				void NotifyOnAddHotkey(IListItemMenu *listitem, const Hotkey &hotkey) override;
				void NotifyOnDeleteHotkey(IListItemMenu *listitem, const Hotkey &hotkey) override;
				void NotifyOnShow(IListItem *item) override;
				void NotifyOnHide(IListItem *item) override;
				void NotifyOnEnable(IListItem *item) override;
				void NotifyOnDisable(IListItem *item) override;
				void NotifyOnSelect(IListItem *item) override;
				void NotifyOnDeselect(IListItem *item) override;
				void NotifyOnActivate(IListItem *item) override;
				void NotifyOnDeactivate(IListItem *item) override;
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CMainMenu *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CMainMenu *control);
			};

			struct ITEM
			{
				IListItem *Item;
				bool Opended; // Whether submenu is visible
				float Scroll; // Submenu scroll
				float ScrollMax; // Submenu max scroll
				PointF Size; // Size of submenu
				PointF Position; // Submenu position in form coordinates
				bool RightAligned;
			};

			struct REQUIRED_SIZE
			{
				PointF Size;
				float SizeIcon;
				float SizeHotkey;
				float MaxHeight;
			};
		private:
			CGradientListener m_cGradientListener;
			std::vector<ITEM> m_aItems;
			IImageList *m_pImageListEnabled;
			IImageList *m_pImageListDisabled;
			RectF m_sSubmenuBorderWidth;
			RectF m_sSubmenuBorderRadius;
			BorderColor m_sSubmenuBorderColor;
			RectF m_sSubmenuPadding;
			Color m_sSubmenuBackgroundColor;
			Color m_sSubmenuShadowColor;
			int m_iSubmenuShadowRadius;
			PointF m_sSubmenuShadowShift;
			PointF m_sSubmenuShift;
			float m_fHotkeyMaxInterval; // Max interval to thread several hotkeys as sequence of hotkeys
			float m_fSubmenuScrollHeight; // Height of up and down scrollers if exists
			Color m_sSubmenuScrollArrowColorNormal;
			Color m_sSubmenuScrollArrowColorHovered;
			Color m_sSubmenuScrollArrowColorDisabled;
			float m_fScrollInterval;
			float m_fSubmenuDeltaScrollTimer;
			float m_fSubmenuDeltaScrollWheel;
			float m_fSubmenuMaxHeight;
			Gradient m_cSubmenuBackgroundGradient;
			RectF m_sBorderWidth;
			RectF m_sBorderRadius;
			RectF m_sPadding;
			BorderColor m_aBorderColor[(int)State::Active + 1];
			Color m_aBackgroundColor[(int)State::Active + 1];
			Color m_aShadowColor[(int)State::Active + 1];
			int m_aShadowRadius[(int)State::Active + 1];
			PointF m_aShadowShift[(int)State::Active + 1];
			Gradient m_aBackgroundGradient[(int)State::Active + 1];
			float m_fScrollWidth;
			Color m_sScrollArrowColorNormal;
			Color m_sScrollArrowColorHovered;
			Color m_sScrollArrowColorDisabled;
			PointF m_sRootSubmenuShift;

			IListItemOwner *m_pListItemOwner;
			ITransform *m_pTransform;
			PlatformHandle m_hScrollTimer;
			std::chrono::steady_clock::time_point m_sLastHotkey;
			std::vector<Hotkey> m_aLastHotkeys; // List of hotkeys appeared in hotkey interval(required to process multi hotkeys)
			IListItem *m_pHoveredItem;
			bool m_bHoverStartScroller;
			bool m_bHoverEndScroller;
			IListItem *m_pDownItem; // Item where mouse was down
			CListItemMenu m_cRootItem;
			bool m_bIgnoreGradient;
			ITexture *m_pCanvas;

			void UpdateFromStyle(IStyle *style);
			void UpdateItemFromStyle(IListItem *item);
			int FindItemIndex(IListItem *item) const;
			PointF CalculateRequiredSize(IListItem *parent);
			void UpdateSubmenu(IListItem *parent, const bool recursive);
			void UpdateSubmenuPosition(IListItem *parent);
			void CalculateRenderRect(IListItem *parent, RectF &rect);
			IListItem *getItem(IListItem *parent, bool &start_scroller, bool &end_scroller, const PointF &position); // If topp or bottom scroller is true, then return parent of the submenu where scrollers are(null for root)
			void setOwner(IListItem *item);
			RectF GetClientRect(IListItem *parent); // Return rect without border and padding/scrollers
			void MouseDownCancel();
			bool TestPosition(IListItem *parent, const PointF &position);
			RectF getAbsoluteRenderRect(IListItem *parent);
			RectF getAbsoluteRenderRect(const int parent_index);
			void SetListItemDPI(IListItem *parent);
			void RepaintSubmenus(const int parent_index);
			void Render();
			void RenderMenuScrolls(const PointF &size, const float scroll, const float scroll_max, const Block &block, IRenderer *renderer, const State state, const PointF &disp);
			void RenderBlock(const PointF &size, const BorderColor &border_colors, const Color &background_color, const RectF &border_width, const RectF &border_radius, Gradient &gradient,
				IRenderer *renderer, const PointF &disp);
			void RenderSubmenuScrolls(const PointF &size, const float scroll, const float scroll_max, IListItem *parent, const Block &block, IRenderer *renderer, const PointF &disp);
			void RenderSubmenu(IListItem *parent, IRenderer *renderer, ITexture **clip);
		public:
			void(*OnSelectItem)(IControl *sender, IListItem *item); // Event called when item has been selected
			void(*OnDeselectItem)(IControl *sender, IListItem *item); // Event called when item has been deselected
			void(*OnActivateItem)(IControl *sender, IListItem *item); // Event called when item has been activated
			void(*OnDeactivateItem)(IControl *sender, IListItem *item); // Event called when item has been deactivated
			void(*OnDeleteItem)(IControl *sender, IListItem *item); // Evet called when item has been deleted
			void(*OnDeleteItems)(IControl *sender); // Event called when all items has been deleted

			// IControl methods
			void Refresh(const bool refresh_children) override;

			CMainMenu();
			CMainMenu(IForm *parent);
			CMainMenu(IControl *parent);
			~CMainMenu() override;

			IControl *getControl(const PointF &position) override;
			RectF getRenderRect() override; // Return rect with all opened submenus
			bool hasExtra() override;
			
			bool setAlign(const Align value) override; // Only "None" and "Top" are allowed
			bool setConstraints(const RectF &value) override; // Not allowed
			bool setEnabled(const bool value) override; // Not allowed
			bool setTransform(ITransform *value) override;
			bool setDPI(const Point &value) override;

			IListItemOwner *QueryListItemOwner() override;

			IListItem *getRootItem() override;
			int getItemCount(const bool total = false) override;
			IListItem *getItem(const int index) override;

			bool Add(IListItem *item) override;
			bool Insert(IListItem *item, const int before) override;
			bool Delete(const int index) override;
			bool Clear() override;

			State getState(); // Return current state
			IListItem *getItem(const String &name); // Return item by name
			IListItem *getItem(const PointF &position); // Return item at specified position(in local coordinates)
			IImageList *getImageListEnabled(); // Return assigned image list for enabled state
			IImageList *getImageListDisabled(); // Return assigned image list for disabled state
			// Return layout properties
			RectF getSubmenuBorderWidth() const;
			RectF getSubmenuBorderRadius() const;
			BorderColor getSubmenuBorderColor() const;
			Color getSubmenuLeftBorderColor() const;
			Color getSubmenuTopBorderColor() const;
			Color getSubmenuRightBorderColor() const;
			Color getSubmenuBottomBorderColor() const;
			RectF getSubmenuPadding() const;
			Color getSubmenuBackgroundColor() const;
			Color getSubmenuShadowColor() const;
			int getSubmenuShadowRadius() const;
			PointF getSubmenuShadowShift() const;
			float getScroll() const; // Return scroll of main menu
			float getScrollMax() const; // Return maximum allowed scroll of main menu
			float getSubmenuScroll(IListItem *parent); // Return submenu scroll
			float getSubmenuScrollMax(IListItem *parent); // Return maximum allowed scroll of submenu
			PointF getSubmenuShift() const;
			float getHotkeyMaxInterval() const;
			float getSubmenuScrollHeight() const;
			Color getSubmenuScrollArrowColorNormal() const;
			Color getSubmenuScrollArrowColorHovered() const;
			Color getSubmenuScrollArrowColorDisabled() const;
			float getScrollInterval() const;
			float getSubmenuDeltaScrollTimer() const;
			float getSubmenuDeltaScrollWheel() const;
			float getSubmenuMaxHeight() const;
			Gradient *getSubmenuBackgroundGradient();
			RectF getBorderWidth() const;
			RectF getBorderRadius() const;
			RectF getPadding() const;
			BorderColor getBorderColor(const State state) const;
			Color getLeftBorderColor(const State state) const;
			Color getTopBorderColor(const State state) const;
			Color getRightBorderColor(const State state) const;
			Color getBottomBorderColor(const State state) const;
			Color getBackgroundColor(const State state) const;
			Color getShadowColor(const State state) const;
			int getShadowRadius(const State state) const;
			PointF getShadowShift(const State state) const;
			Gradient *getBackgroundGradient(const State state);
			float getScrollWidth() const;
			Color getScrollArrowColorNormal() const;
			Color getScrollArrowColorHovered() const;
			Color getScrollArrowColorDisabled() const;
			bool isItemRightAligned(const int index); // Whether item is at right or at left of the menu
			bool isItemRightAligned(IListItem *item); // Whether item is at right or at left of the menu
			PointF getRootSubmenuShift() const;

			bool setImageListEnabled(IImageList *value); // Assign new image list for enabled state
			bool setImageListDisabled(IImageList *value); // Assign new image list for disabled state
			// Set layout properties
			bool setSubmenuBorderWidth(const RectF &value);
			bool setSubmenuBorderRadius(const RectF &value);
			bool setSubmenuBorderColor(const BorderColor &value);
			bool setSubmenuLeftBorderColor(const Color &value);
			bool setSubmenuTopBorderColor(const Color &value);
			bool setSubmenuRightBorderColor(const Color &value);
			bool setSubmenuBottomBorderColor(const Color &value);
			bool setSubmenuPadding(const RectF &value);
			bool setSubmenuBackgroundColor(const Color &value);
			bool setSubmenuShadowColor(const Color &value);
			bool setSubmenuShadowRadius(const int value);
			bool setSubmenuShadowShift(const PointF &value);
			bool setScroll(const float value); // Scroll menu
			bool setSubmenuScroll(IListItem *parent, const float value); // Scroll submenu
			bool setSubmenuShift(const PointF &value);
			bool setHotkeyMaxInterval(const float value);
			bool setSubmenuScrollHeight(const float value);
			bool setSubmenuScrollArrowColorNormal(const Color &value);
			bool setSubmenuScrollArrowColorHovered(const Color &value);
			bool setSubmenuScrollArrowColorDisabled(const Color &value);
			bool setScrollInterval(const float value);
			bool setSubmenuDeltaScrollTimer(const float value);
			bool setSubmenuDeltaScrollWheel(const float value);
			bool setSubmenuMaxHeight(const float value);
			bool setBorderWidth(const RectF &value);
			bool setBorderRadius(const RectF &value);
			bool setPadding(const RectF &value);
			bool setBorderColor(const State state, const BorderColor &value);
			bool setLeftBorderColor(const State state, const Color &value);
			bool setTopBorderColor(const State state, const Color &value);
			bool setRightBorderColor(const State state, const Color &value);
			bool setBottomBorderColor(const State state, const Color &value);
			bool setBackgroundColor(const State state, const Color &value);
			bool setShadowColor(const State state, const Color &value);
			bool setShadowRadius(const State state, const int value);
			bool setShadowShift(const State state, const PointF &value);
			bool setScrollWidth(const float value);
			bool setScrollArrowColorNormal(const Color &value);
			bool setScrollArrowColorHovered(const Color &value);
			bool setScrollArrowColorDisabled(const Color &value);
			bool setItemRightAligned(const int index, const bool value);
			bool setItemRightAligned(IListItem *item, const bool value);
			bool setRootSubmenuShift(const PointF &value);

			bool Add(IListItem *item, const bool right_aligned); // Add item
			bool Insert(IListItem *item, const int before, const bool right_aligned); // Insert item before specified one
		};
	}
}
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
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../../ListItems/IListItemMenu.h"
#include "../../ListItems/Menu/ListItemMenu.h"
#include "../IPopupMenu.h"
#include <chrono>
#include <vector>

namespace nitisa
{
	class IControl;
	class IFont;
	class IForm;
	class IListItemOwner;
	class IRenderer;
	class IStyle;
	class ITexture;
	class ITransform;

	struct Block;

	namespace standard
	{
		class IImageList;

		class CPopupMenuService;

		// This popup menu show itself in client area of form, so it cannot be places on another controls and cannot have any transformations except for Tx and Ty
		class CPopupMenu :public virtual IPopupMenu, public CControl
		{
			friend CPopupMenuService;
		private:
			class CPopupMenuListItemOwner :public virtual IListItemMenuOwner, public CListItemOwner
			{
			private:
				CPopupMenu *m_pMenu;

				bool DeleteItem(IListItem *item);
				void UpdateAndRepaint(IListItem *parent);
				void UpdateItemOwner(IListItem *item, IListItemOwner *owner);
			public:
				CPopupMenuListItemOwner(CPopupMenu *menu);

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
				CPopupMenu *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CPopupMenu *control);
			};

			struct ITEM
			{
				IListItem *Item;
				bool Opended; // Whether submenu is visible
				float Scroll; // Submenu scroll
				float ScrollMax; // Submenu max scroll
				PointF Size; // Size of submenu
				PointF Position; // Submenu position in form coordinates
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
			RectF m_sBorderWidth;
			RectF m_sBorderRadius;
			BorderColor m_sBorderColor;
			RectF m_sPadding;
			Color m_sBackgroundColor;
			Color m_sShadowColor;
			int m_iShadowRadius;
			PointF m_sShadowShift;
			PointF m_sSubmenuShift;
			bool m_bIgnoreHotkeys; // Hotkeys processing may depend on popup menu owner. For example, if it belongs to some modal/focusable control hotkeys should be available only if that control active/visible/etc
			float m_fHotkeyMaxInterval; // Max interval to thread several hotkeys as sequence of hotkeys
			float m_fScrollHeight; // Height of up and down scrollers if exists
			Color m_sScrollArrowColorNormal;
			Color m_sScrollArrowColorHovered;
			Color m_sScrollArrowColorDisabled;
			float m_fScrollInterval;
			float m_fDeltaScrollTimer;
			float m_fDeltaScrollWheel;
			Gradient m_cBackgroundGradient;

			IListItemOwner *m_pListItemOwner;
			ITransform *m_pTransform;
			PlatformHandle m_hScrollTimer;
			bool m_bIgnoreVisible;
			std::chrono::steady_clock::time_point m_sLastHotkey;
			std::vector<Hotkey> m_aLastHotkeys; // List of hotkeys appeared in hotkey interval(required to process multi hotkeys)
			IListItem *m_pHoveredItem;
			bool m_bHoverTopScroller;
			bool m_bHoverBottomScroller;
			IListItem *m_pDownItem; // Item where mouse was down
			CListItemMenu m_cRootItem;
			bool m_bIgnoreGradient;

			void UpdateFromStyle(IStyle *style);
			void UpdateItemFromStyle(IListItem *item);
			int FindItemIndex(IListItem *item);
			PointF CalculateRequiredSize(IListItem *parent); // If parent is null, root menu is used
			void UpdateSubmenu(IListItem *parent, const bool recursive);
			void UpdateSubmenuPosition(IListItem *parent);
			void CalculateRenderRect(IListItem *parent, RectF &rect);
			IListItem *getItem(IListItem *parent, const PointF &position, bool &top_scroller, bool &bottom_scroller); // If topp or bottom scroller is true, then return parent of the submenu where scrollers are(null for root)
			void setSizeInternal(const PointF &value);
			bool setVisibleInternal(const bool value);
			void setOwner(IListItem *item);
			RectF getClientRect(IListItem *parent); // Return rect without border and padding/scrollers
			void MouseDownCancel();
			bool TestPosition(IListItem *parent, const PointF &position);
			RectF getAbsoluteRenderRect(IListItem *parent);
			RectF getAbsoluteRenderRect(const int parent_index);
			void SetListItemDPI(IListItem *parent);
			void Render();
			void RenderBlock(const PointF &size, IRenderer *renderer, const PointF &disp);
			void RenderScrollers(const PointF &size, const float scroll, const float scroll_max, IListItem *parent, const Block &block, IRenderer *renderer, const PointF &disp);
			void Render(IListItem *parent, IRenderer *renderer, ITexture **clip);
		public:
			void(*OnSelectItem)(IControl *sender, IListItem *item); // Event called when item has been selected
			void(*OnDeselectItem)(IControl *sender, IListItem *item); // Event called when item has been unselected
			void(*OnActivateItem)(IControl *sender, IListItem *item); // Event called when item has been activated
			void(*OnDeactivateItem)(IControl *sender, IListItem *item); // Event called when item has been deactivated
			void(*OnDeleteItem)(IControl *sender, IListItem *item); // Event called when item has been deleted
			void(*OnDeleteItems)(IControl *sender); // Event called when all items has been deleted

			CPopupMenu();
			CPopupMenu(IForm *parent);
			~CPopupMenu() override;

			IControl *getControl(const PointF &position) override;
			RectF getClientRect() override;
			RectF getRenderRect() override; // Return rect with all opened submenus
			Mat4f getTransformMatrix() override;
			int getItemCount(const bool total = false) override;
			IListItem *getItem(const int index) override;
			bool hasExtra() override;

			bool setAlign(const Align value) override; // Not allowed
			bool setConstraints(const RectF &value) override; // Allow only max height
			bool setSize(const PointF &value) override; // Allowed only when called internally
			bool setVisible(const bool value) override; // Allowed only when added to form
			bool setEnabled(const bool value) override; // Not allowed
			bool setTransform(ITransform *value) override;
			bool setDPI(const Point &value) override;

			IListItemOwner *QueryListItemOwner() override;

			IListItem *getRootItem() override;
			bool Add(IListItem *item) override;
			bool Insert(IListItem *item, const int before) override;
			bool Delete(const int index) override;
			bool Clear() override;

			bool Show(const PointF &position) override;
			bool Hide() override;

			IListItem *getItem(const String &name); // Return item by name
			IListItem *getItem(const PointF &position); // Return item at specified position(in local coordinates)
			IImageList *getImageListEnabled(); // Return assigned image list for enabled state
			IImageList *getImageListDisabled(); // Return assigned image list for disabled state
			// Return layout properties
			RectF getBorderWidth() const;
			RectF getBorderRadius() const;
			BorderColor getBorderColor() const;
			Color getLeftBorderColor() const;
			Color getTopBorderColor() const;
			Color getRightBorderColor() const;
			Color getBottomBorderColor() const;
			RectF getPadding() const;
			Color getBackgroundColor() const;
			Color getShadowColor() const;
			int getShadowRadius() const;
			PointF getShadowShift() const;
			float getScroll() const; // Return scroll value
			float getScrollMax() const; // Return maximum allowed scroll
			float getSubmenuScroll(IListItem *parent); // Return submenu scroll
			float getSubmenuScrollMax(IListItem *parent); // Return maximum allowed scroll of submenu
			PointF getSubmenuShift() const;
			bool getIgnoreHotkeys() const; // Whether hotkeys should be ignored
			float getHotkeyMaxInterval() const;
			float getScrollHeight() const;
			Color getScrollArrowColorNormal() const;
			Color getScrollArrowColorHovered() const;
			Color getScrollArrowColorDisabled() const;
			float getScrollInterval() const; // Return scroll interval(in seconds)
			float getDeltaScrollTimer() const;
			float getDeltaScrollWheel() const;
			Gradient *getBackgroundGradient();

			bool setImageListEnabled(IImageList *value); // Set image list for enabled state
			bool setImageListDisabled(IImageList *value); // Set image list for disabled state
			// Set layout properties
			bool setBorderWidth(const RectF &value);
			bool setBorderRadius(const RectF &value);
			bool setBorderColor(const BorderColor &value);
			bool setLeftBorderColor(const Color &value);
			bool setTopBorderColor(const Color &value);
			bool setRightBorderColor(const Color &value);
			bool setBottomBorderColor(const Color &value);
			bool setPadding(const RectF &value);
			bool setBackgroundColor(const Color &value);
			bool setShadowColor(const Color &value);
			bool setShadowRadius(const int value);
			bool setShadowShift(const PointF &value);
			bool setScroll(const float value); // Set scroll
			bool setSubmenuScroll(IListItem *parent, const float value); // Set submenu scroll
			bool setSubmenuShift(const PointF &value);
			bool setIgnoreHotkeys(const bool value); // Set whether to ignore hotkeys
			bool setHotkeyMaxInterval(const float value);
			bool setScrollHeight(const float value);
			bool setScrollArrowColorNormal(const Color &value);
			bool setScrollArrowColorHovered(const Color &value);
			bool setScrollArrowColorDisabled(const Color &value);
			bool setScrollInterval(const float value); // Set scroll interval(in seconds)
			bool setDeltaScrollTimer(const float value);
			bool setDeltaScrollWheel(const float value);
		};
	}
}
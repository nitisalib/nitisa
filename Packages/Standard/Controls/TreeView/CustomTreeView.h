// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/Scroll/BuiltInScroll.h"
#include "Nitisa/BuiltInControls/IBuiltInScrollListener.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/ListItem.h"
#include "Nitisa/Core/ScrollVisibility.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IComponentItemTree.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include <vector>

namespace nitisa
{
	class IBuiltInControl;
	class IBuiltInScroll;
	class IControl;
	class IListItem;
	class IListItemOwner;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CCustomTreeViewService;
		class CCustomTreeViewListItemOwner;

		class CCustomTreeView :public virtual IComponentItemTree, public CControl
		{
			friend CCustomTreeViewService;
			friend CCustomTreeViewListItemOwner;
		private:
			class CRootListItem :public CListItem
			{
			public:
				IListItem *Clone() override;

				CRootListItem();
			};

			class CScroll :public CBuiltInScroll
			{
			private:
				CCustomTreeView *m_pTreeView;
			public:
				IControl *getControl() override;

				CScroll(CCustomTreeView *treeview);
			};

			class CScrollListener :public virtual IBuiltInScrollListener
			{
			private:
				CCustomTreeView *m_pTreeView;
			public:
				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnScroll(IBuiltInControl *sender) override;

				CScrollListener(CCustomTreeView *treeview);
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CCustomTreeView *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CCustomTreeView *control);
			};
		public:
			static const float ItemHeightAuto; // All items have individual height returned by getRequiredSize()
			static const float ItemHeightText; // All items have same height equal to line height of text "Wy"

			enum class State // Possible states
			{
				Normal,
				Hovered,
				Focused,
				FocusedHovered,
				Disabled
			};

			enum class FolderState // Folder states
			{
				Normal,
				Hovered
			};

			using FItemCallback = void(*)(void *param, IListItem *item); // Function prototype called when enumeration items
		private:
			enum class Element
			{
				None,
				Folder,
				VScroll,
				HScroll,
				Item
			};

			struct ITEM
			{
				IListItem *Item;
				bool Folded;
			};

			CGradientListener m_cGradientListener;
			RectF m_sBorderWidth;
			RectF m_sBorderRadius;
			RectF m_sPadding;
			BorderColor m_aBorderColor[(int)State::Disabled + 1];
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
			Color m_aShadowColor[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];
			int m_aShadowRadius[(int)State::Disabled + 1];
			Color m_aCornerColor[(int)State::Disabled + 1];
			float m_fItemHeight;
			// Folder
			PointF m_sFolderSize;
			Color m_sFolderLinesColor;
			RectF m_aFolderBorderWidth[(int)FolderState::Hovered + 1];
			RectF m_aFolderBorderRadius[(int)FolderState::Hovered + 1];
			BorderColor m_aFolderBorderColor[(int)FolderState::Hovered + 1];
			Color m_aFolderBackgroundColor[(int)FolderState::Hovered + 1];
			Gradient m_aFolderBackgroundGradient[(int)FolderState::Hovered + 1];
			PointF m_aFolderSignSize[(int)FolderState::Hovered + 1]; // Width and height of horizontal line(for vertical x and y are switched
			Color m_aFolderSignColor[(int)FolderState::Hovered + 1];
			// Other
			bool m_bMultiselect;
			bool m_bMovable;
			ScrollVisibility m_eHScrollVisibility;
			ScrollVisibility m_eVScrollVisibility;
			float m_fScrollInterval; // Scroll timer interval when mouse is down
			float m_fScrollDelta;

			ITexture *m_pCanvas;
			IBuiltInScroll *m_pVScroll;
			IBuiltInScroll *m_pHScroll;
			CRootListItem m_cRootItem;
			IListItemOwner *m_pListItemOwner;
			CScrollListener m_cScrollListener;
			bool m_bHScrollVisible;
			bool m_bVScrollVisible;
			int m_iLockUpdate;
			Element m_eHoveredElement;
			Element m_eDownElement;
			IListItem *m_pHoveredItem;
			bool m_bIgnoreGradient;
			std::vector<ITEM> m_aItems;
			bool m_bItemsSorted;

			IBuiltInScroll *getVScroll();
			IBuiltInScroll *getHScroll();
			void Update();
			bool UpdateHoveredElement();
			bool UpdateHoveredElement(const PointF &position);
			void UpdateHoveredItem(IListItem *parent, const PointF &position, PointF &current, Element &element, IListItem **hovered, const float line_height);
			void DeselectAllExceptFirst();
			void DeselectAllExceptFirst(IListItem *parent, bool &first);
			bool DeselectAllExceptItem(IListItem *parent, IListItem *exclude);
			bool DeselectAllExceptParent(IListItem *parent, IListItem *exclude);
			bool DeselectAllExceptParent(IListItem *exclude);
			void DeactivateAllExceptItem(IListItem *parent, IListItem *exclude);
			void EnumItems(IListItem *item, void *param, FItemCallback callback, void(*enumerator)(void *param, IListItem *item, FItemCallback callback));
			void SortItems();
			int FindItemIndex(IListItem *item);
			void CalculateRequiredSize(IListItem *parent, PointF &required_size, const float line_height, const int level);
			void UpdateItemFromStyle(IListItem *parent);
			void UpdateFromStyle(IStyle *style);
			void Render();
			void RenderItems(IRenderer *renderer, const PointF &disp, const State state);
			void RenderItems(IListItem *parent, IRenderer *renderer, PointF &current, const float line_height, const float client_height, ITexture **folder_normal_folded,
				ITexture **folder_hovered_folded, ITexture **folder_normal, ITexture **folder_hovered, ITexture **clip_items);
			ITexture *RenderFolder(IRenderer *renderer, IListItem *item, ITexture **folder_normal_folded, ITexture **folder_hovered_folded, ITexture **folder_normal, ITexture **folder_hovered,
				const bool folded);
			void RenderScrolls(IRenderer *renderer, const PointF &disp);
			void RenderCorner(IRenderer *renderer, const PointF &disp, const State state);
			bool ScrollToActiveItem(IListItem *parent, PointF &current, bool &changed);
			IListItem *FindActiveItem(IListItem *parent);
			void SetListItemDPI(IListItem *parent);
		public:
			void(*OnSelectItem)(IControl *sender, IListItem *item); // Event called when item has been selected
			void(*OnDeselectItem)(IControl *sender, IListItem *item); // Event called when item has been unselected
			void(*OnMovingSelection)(IControl *sender, IListItem *dest); // Event called when moving selected items by move drag and drop
			void(*OnMoveSelection)(IControl *sender, IListItem *dest); // Event called when drop appears in moving items. Dest can be empy if mouse button released out of any item
			void(*OnActivateItem)(IControl *sender, IListItem *item); // Event called when item has been activated
			void(*OnDeactivateItem)(IControl *sender, IListItem *item); // Event called when item has been deactivated

			// IControl methods
			void Refresh(const bool refresh_children) override;

			IListItem *getRootItem() override;

			RectF getClientRect() override;
			RectF getRenderRect() override;

			bool setDPI(const Point &value) override;

			IListItemOwner *QueryListItemOwner() override;

			CCustomTreeView(const String &class_name);
			~CCustomTreeView() override;

			IListItem *getActiveItem(); // Return activate item
			State getState(); // Return current state
			// Return layout properties
			RectF getBorderWidth() const;
			RectF getBorderRadius() const;
			RectF getPadding() const;
			BorderColor getBorderColor(const State state) const;
			Color getBackgroundColor(const State state) const;
			Gradient *getBackgroundGradient(const State state);
			Color getShadowColor(const State state) const;
			PointF getShadowShift(const State state) const;
			int getShadowRadius(const State state) const;
			Color getCornerColor(const State state) const;
			float getItemHeight() const;
			PointF getFolderSize() const;
			Color getFolderLinesColor() const;
			RectF getFolderBorderWidth(const FolderState state) const;
			RectF getFolderBorderRadius(const FolderState state) const;
			BorderColor getFolderBorderColor(const FolderState state) const;
			Color getFolderBackgroundColor(const FolderState state) const;
			Gradient *getFolderBackgroundGradient(const FolderState state);
			PointF getFolderSignSize(const FolderState state) const;
			Color getFolderSignColor(const FolderState state) const;
			bool isMultiselect() const; // Whether multiple items can be selected at the same time
			bool isMovable() const; // Whether selection could be moved by drag and drop
			ScrollVisibility getHScrollVisibility() const;
			ScrollVisibility getVScrollVisibility() const;
			float getScrollInterval() const;
			float getScrollDelta() const;
			bool isFolded(IListItem *item); // Whether specified item is folded(subitems are hidden)

			// Set layout properties
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
			bool setShadowShift(const State state, const PointF &value);
			bool setShadowRadius(const State state, const int value);
			bool setCornerColor(const State state, const Color &value);
			bool setItemHeight(const float value);
			bool setFolderSize(const PointF &value);
			bool setFolderLinesColor(const Color &value);
			bool setFolderBorderWidth(const FolderState state, const RectF &value);
			bool setFolderBorderRadius(const FolderState state, const RectF &value);
			bool setFolderBorderColor(const FolderState state, const BorderColor &value);
			bool setFolderBackgroundColor(const FolderState state, const Color &value);
			bool setFolderSignSize(const FolderState state, const PointF &value);
			bool setFolderSignColor(const FolderState state, const Color &value);
			bool setMultiselect(const bool value); // Set whether multiple items could be selected at the same time
			bool setMovable(const bool value); // Set whether moving of selected items by drag and drop is allowed
			bool setHScrollVisibility(const ScrollVisibility value);
			bool setVScrollVisibility(const ScrollVisibility value);
			bool setScrollInterval(const float value);
			bool setScrollDelta(const float value);
			bool setFolded(IListItem *item, const bool value); // Fold/unfold item
			bool setBorderColor(const BorderColor &value);
			bool setLeftBorderColor(const Color &value);
			bool setTopBorderColor(const Color &value);
			bool setRightBorderColor(const Color &value);
			bool setBottomBorderColor(const Color &value);
			bool setBackgroundColor(const Color &value);
			bool setShadowColor(const Color &value);
			bool setShadowShift(const PointF &value);
			bool setShadowRadius(const int value);
			bool setCornerColor(const Color &value);

			void LockUpdate(); // Lock update and repaint
			void UnlockUpdate(); // Unlock update and repaint
			void EnumSelectedItems(void *param, FItemCallback callback); // Enumerate selected items
			bool ScrollToActiveItem(); // Scroll to active item
			bool FoldAll(); // Fold all
			bool UnfoldAll(); // Unfold all
			bool Fold(IListItem *item); // Fold item
			bool Unfold(IListItem *item); // Unfold item
		};
	}
}
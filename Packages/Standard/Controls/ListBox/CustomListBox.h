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
#include "Nitisa/Core/ControlItemList.h"
#include "Nitisa/Core/ListItemOwner.h"
#include "Nitisa/Core/ScrollVisibility.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "CustomListBoxService.h"
#include <chrono>

namespace nitisa
{
	class IBuiltInControl;
	class IBuiltInScroll;
	class IControl;
	class IFont;
	class IListItem;
	class IListItemOwner;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CCustomListBox :public CControlItemList
		{
			friend CCustomListBoxService;
		public:
			enum class State // Possible states
			{
				Normal,
				Hovered,
				Focused,
				FocusedHovered,
				Disabled
			};

			using FCompare = bool(*)(IListItem *a, IListItem *b); // Items comparing(for sorting) function prototype
		private:
			class CCustomListBoxListItemOwner :public CListItemOwner
			{
			private:
				CCustomListBox *m_pListBox;
			public:
				CCustomListBoxListItemOwner(CCustomListBox *listbox);

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
			};

			class CScroll :public CBuiltInScroll
			{
			private:
				CCustomListBox *m_pListBox;
			public:
				CScroll(CCustomListBox *listbox);

				IControl *getControl() override;
			};

			class CScrollListener :public virtual IBuiltInScrollListener
			{
			private:
				CCustomListBox *m_pListBox;
			public:
				CScrollListener(CCustomListBox *listbox);

				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnScroll(IBuiltInControl *sender) override;
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CCustomListBox *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CCustomListBox *control);
			};
		private:
			CGradientListener m_cGradientListener;
			bool m_bSortable;
			int m_iActiveIndex;
			RectF m_sBorderWidth;
			RectF m_sBorderRadius;
			RectF m_sPadding;
			float m_fSearchResetInterval;
			ScrollVisibility m_eHorizontalScrollBar;
			ScrollVisibility m_eVerticalScrollBar;
			int m_iColumns; // >= 1
			bool m_bMultiselect;
			float m_fScrollInterval;

			Color m_aShadowColor[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];
			int m_aShadowRadius[(int)State::Disabled + 1];
			BorderColor m_aBorderColor[(int)State::Disabled + 1];
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
			Color m_aCornerColor[(int)State::Disabled + 1];

			IBuiltInScroll *m_pHScroll;
			IBuiltInScroll *m_pVScroll;
			bool m_bIgnoreGradient;
			IListItemOwner *m_pListItemOwner;
			CCustomListBoxService::Element m_eHoveredElement;
			CCustomListBoxService::Element m_eDownElement;
			bool m_bSorted;
			String m_sSearch;
			std::chrono::steady_clock::time_point m_sLastSearch;
			Point m_sGrid;
			PointF m_sItemSize;
			bool m_bHScroll;
			bool m_bVScroll;
			int m_iDownIndex; // Index of element wrom which to select
			IListItem *m_pDownItem; // Element which was down by mouse
			int m_iLockUpdate;
			bool m_bUpdateRequired;
			ITexture *m_pCanvas;
			CScrollListener m_cScrollListener;

			IBuiltInScroll *getHScroll();
			IBuiltInScroll *getVScroll();
			RectF getRenderRect(const State state);
			IListItem *getItemAtPoint(const PointF &position);
			Point getGridCell(const PointF &position);
			Point getGridCell(const RectF &client, const PointF &position);
			RectF getRealClientRect();
			Point IndexToGrid(const int value);
			int GridToIndex(const Point &value);
			bool ScrollToActiveItem();
			bool ScrollToItem(const int index);
			void UpdateFromStyle(IStyle *style);
			void UpdateList();
			bool UpdateHoveredItem();
			bool UpdateHoveredItem(const PointF &position);
			void Update();
			void Render();
			void RenderItems(IRenderer *renderer, const PointF &disp, const RectF &rect);
			void RenderScrolls(IRenderer *renderer, const RectF &rect, const PointF &disp);
			void RenderCorner(IRenderer *renderer, const State state, const RectF &rect, const PointF &disp);
		protected:
			void SortItems() override;
			virtual FCompare getCompareItems(); // Return items comparison function. Null by default
			virtual int Search(const String &search); // Return index of first item started by "search" substring. Default -1. Search should be done with applying translation to item captions(not to "search") if translateable items(like color names) are used. Also dont forget to convert to lower case("search" is already converted)
		protected:
			void BeforeRelease() override;
		public:
			void(*OnActivate)(IControl *sender, const int index); // Event called when item has been activated(index is -1 if there is no new active item)
			void(*OnSelect)(IControl *sender, IListItem *item); // Event called when item has been selected
			void(*OnDeselect)(IControl *sender, IListItem *item); // Event called when item has been deselected

			// IControl methods
			void Refresh(const bool refresh_children) override;

			bool InsertItem(IListItem *item, const int before) override;
			bool DeleteItem(const int index) override;
			bool DeleteItem(IListItem *item) override;
			bool DeleteItems() override;

			RectF getClientRect() override;
			RectF getRenderRect() override;

			bool setDPI(const Point &value) override;
			
			IListItemOwner *QueryListItemOwner() override;

			CCustomListBox(const String &class_name, const bool accept_form, const bool accept_control, const bool tab_stop);
			~CCustomListBox() override;

			State getState(); // Return current state
			bool isSortable() const; // Return whether items should be sorted
			int getActiveIndex(); // Return active item index
			float getSearchResetInterval() const; // Return search by typing reset interval(in seconds)
			int getColumns() const; // Return column count
			bool isMultiselect() const; // Whether multiple item could be selected at the same time
			float getScrollInterval() const; // Scroll interval(in seconds)
			// Return layout properties
			RectF getBorderWidth() const;
			RectF getBorderRadius() const;
			RectF getPadding() const;
			ScrollVisibility getHorizontalScrollBar() const;
			ScrollVisibility getVerticalScrollBar() const;
			Color getShadowColor(const State state) const;
			PointF getShadowShift(const State state) const;
			int getShadowRadius(const State state) const;
			BorderColor getBorderColor(const State state) const;
			Color getLeftBorderColor(const State state) const;
			Color getTopBorderColor(const State state) const;
			Color getRightBorderColor(const State state) const;
			Color getBottomBorderColor(const State state) const;
			Color getBackgroundColor(const State state) const;
			Gradient *getBackgroundGradient(const State state);
			Color getCornerColor(const State state) const;

			bool setHScroll(IBuiltInScroll *value); // Assign new horizontal scroll
			bool setVScroll(IBuiltInScroll *value); // Assign new vertical scroll
			bool setSortable(const bool value); // Set whether items should be sorted
			bool setActiveIndex(const int value); // Set active item
			bool setSearchResetInterval(const float value); // Set search reset interval(in seconds)
			bool setColumns(const int value); // Set column count
			bool setMultiselect(const bool value); // Set whether several items could be selected at the same time
			bool setScrollInterval(const float value); // Set scroll interval(in seconds)
			// Set layout properties
			bool setBorderWidth(const RectF &value);
			bool setBorderRadius(const RectF &value);
			bool setPadding(const RectF &value);
			bool setHorizontalScrollBar(const ScrollVisibility value);
			bool setVerticalScrollBar(const ScrollVisibility value);
			bool setShadowColor(const State state, const Color &value);
			bool setShadowShift(const State state, const PointF &value);
			bool setShadowRadius(const State state, const int value);
			bool setBorderColor(const State state, const BorderColor &value);
			bool setLeftBorderColor(const State state, const Color &value);
			bool setTopBorderColor(const State state, const Color &value);
			bool setRightBorderColor(const State state, const Color &value);
			bool setBottomBorderColor(const State state, const Color &value);
			bool setBackgroundColor(const State state, const Color &value);
			bool setCornerColor(const State state, const Color &value);

			void LockUpdate(); // Lock update and repaint
			void UnlockUpdate(); // Unlock update and repaint
		};
	}
}
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
#include "../../ListItems/Label/ListItemLabel.h"
#include "../IFileList.h"
#include <chrono>
#include <vector>

namespace nitisa
{
	class IBuiltInControl;
	class IBuiltInScroll;
	class IControl;
	class IFont;
	class IForm;
	class IListItem;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class IListItemLabel;

		class CFileListService;

		class CFileList :public virtual IFileList, public CControl
		{
			friend CFileListService;
		public:
			enum class State // Possible states
			{
				Normal,
				Hovered,
				Focused,
				FocusedHovered,
				Disabled
			};
		private:
			class COwner :public CListItemOwner
			{
			private:
				CFileList * m_pFileList;
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

				COwner(CFileList *filelist);
			};

			class CScroll :public CBuiltInScroll
			{
			private:
				CFileList * m_pFileList;
			public:
				IControl *getControl() override;

				CScroll(CFileList *filelist);
			};

			class CScrollListener :public virtual IBuiltInScrollListener
			{
			private:
				CFileList * m_pFileList;
			public:
				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnScroll(IBuiltInControl *sender) override;

				CScrollListener(CFileList *filelist);
			};

			class CFileListItem :public CListItemLabel
			{
			public:
				CFileListItem(const String &caption);
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CFileList *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CFileList *control);
			};

			enum class Element
			{
				None,
				List,
				HScroll,
				VScroll
			};
		private:
			CGradientListener m_cGradientListener;
			String m_sDirectory;
			String m_sFilter;
			bool m_bShowArchieved;
			bool m_bShowCompressed;
			bool m_bShowEncrypted;
			bool m_bShowHidden;
			bool m_bShowNormal;
			bool m_bShowOffline;
			bool m_bShowReadOnly;
			bool m_bShowSystem;
			bool m_bShowTemporary;
			std::vector<IListItemLabel*> m_aItems;
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
			COwner m_cOwner;
			Element m_eHoveredElement;
			Element m_eDownElement;
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
			int Search(const String &search); // Return index of first item started by "search" ubscrint. Default -1. Search should be done with applying translation to item captions(not to "search") if translateable items(like color names) are used. Also dont forget to convert to lower case("search" is already converted)
			Element getElement(const PointF &position);
			int getItemIndex(IListItem *item);
			IListItem *getActiveItem();
			bool DeleteItems();
			StringArray FindFiles(const String &filter);
		protected:
			void BeforeRelease() override;
		public:
			void(*OnActivate)(IControl *sender, const String &file); // Event called when file has been activated
			void(*OnDeactivate)(IControl *sender, const String &file); // Event called when file has been deactivated
			void(*OnSelect)(IControl *sender, const String &file); // Event called when file has been selected
			void(*OnDeselect)(IControl *sender, const String &file); // Event called when file has been deselected

			// IControl methods
			void Refresh(const bool refresh_children) override;

			RectF getClientRect() override;
			RectF getRenderRect() override;
			String getDirectory() override;
			String getFilter() override;
			bool isShowArchieved() override;
			bool isShowCompressed() override;
			bool isShowEncrypted() override;
			bool isShowHidden() override;
			bool isShowNormal() override;
			bool isShowOffline() override;
			bool isShowReadOnly() override;
			bool isShowSystem() override;
			bool isShowTemporary() override;
			String getActiveFile() override;
			int getFileCount() override;
			String getFile(const int index) override;
			bool isFileSelected(const int index) override;

			bool setDPI(const Point &value) override;
			bool setDirectory(const String &value) override;
			bool setFilter(const String &value) override;
			bool setShowArchieved(const bool value) override;
			bool setShowCompressed(const bool value) override;
			bool setShowEncrypted(const bool value) override;
			bool setShowHidden(const bool value) override;
			bool setShowNormal(const bool value) override;
			bool setShowOffline(const bool value) override;
			bool setShowReadOnly(const bool value) override;
			bool setShowSystem(const bool value) override;
			bool setShowTemporary(const bool value) override;
			bool setFileSelected(const int index, const bool value) override;

			bool Rescan() override;

			CFileList();
			CFileList(IForm *parent);
			CFileList(IControl *parent);
			~CFileList() override;

			State getState(); // Return current state
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
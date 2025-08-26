// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/Select/BuiltInSelect.h"
#include "Nitisa/BuiltInControls/IBuiltInSelectListener.h"
#include "Nitisa/Core/Consts.h"
#include "Nitisa/Core/ControlItemList.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Core/Font.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../ISelect.h"

namespace nitisa
{
	class IBuiltInControl;
	class IBuiltInDropDown;
	class IControl;
	class IFont;
	class IListItem;
	class IListItemOwner;
	class IStyle;

	namespace standard
	{
		class CSelect :public virtual ISelect, public CControlItemList
		{
			friend class CSelectService;
		private:
			class CBuiltIn :public CBuiltInSelect
			{
			private:
				CSelect *m_pControl;
			public:
				IControl *getControl() override;
				State getState() override;

				CBuiltIn(CSelect *control);
			};

			class CBuiltInListener :public virtual IBuiltInSelectListener
			{
			private:
				CSelect *m_pControl;
			public:
				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnFilterChange(IBuiltInControl *sender) override;
				void NotifyOnSelect(IBuiltInControl *sender, const int index) override;
				void NotifyOnOpen(IBuiltInControl *sender) override;
				void NotifyOnClose(IBuiltInControl *sender) override;

				CBuiltInListener(CSelect *control);
			};

			class CFontListener :public virtual IFeedbackExListener
			{
			private:
				CSelect *m_pControl;
			public:
				void NotifyOnBeforeChange() override;
				void NotifyOnBeforeChange(bool &allowed) override;
				void NotifyOnAfterChange() override;

				CFontListener(CSelect *control);
			};
		private:
			IBuiltInSelect *m_pSelect;
			CBuiltInListener m_cListener;
			CFontListener m_cFontListener;
			CFont m_cCategoryFont;
			bool m_bIgnoreFont;

			bool m_bIgnoreKillCaptureMouse;

			void UpdateSelect();
			void UpdateFromStyle(IStyle *style);
			void Render();
			void RenderList();
		public:
			void(*OnSelect)(IControl *sender, const int index); // Event called when item selected

			// IControl getters
			IControl *getControl(const PointF &position) override;
			RectF getClientRect() override;
			RectF getRenderRect() override;
			CursorType getCursor() override;
			bool hasExtra() override;

			// IControl setters
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			// IComponentItemList getters
			int getItemCount() override;
			IListItem *getItem(const int index) override;
			int getItemIndex(IListItem *item) override;

			// IComponentItemList items
			bool AddItem(IListItem *item) override;
			bool InsertItem(IListItem *item, const int before) override;
			bool DeleteItem(const int index) override;
			bool DeleteItem(IListItem *item) override;
			bool DeleteItems() override;

			// IComponentItemList methods
			IListItemOwner *QueryListItemOwner() override;

			// ISelect getters
			String getFilter() override;
			int getActiveIndex() override;
			IBuiltInSelect *getSelect() override;
			IFont *getCategoryFont() override;

			// ISelect setters
			bool setFilter(const String &value) override;
			bool setActiveIndex(const int value) override;
			bool setSelect(IBuiltInSelect *value) override;
			bool setCategoryFont(IFont *value) override;

			// ISelect methods
			bool Open() override;
			bool Close() override;
			
			CSelect();
			CSelect(IForm *parent);
			CSelect(IControl *parent);
			~CSelect() override;

			// Layout getters (work only if default built-in select is used)
			CBuiltInSelect::State getState();
			bool isOpened();
			bool isArrowAtRight();
			CBuiltInSelect::OpenDirection getOpenDirection();
			CBuiltInSelect::ArrowArea getArrowArea();
			float getListWidth();
			float getListMaxHeight();
			float getArrowAreaSize();
			float getArrowSize();
			RectF getBorderWidth();
			RectF getBorderRadius();
			RectF getPadding();
			RectF getArrowBorderWidth();
			RectF getArrowBorderRadius();
			RectF getListBorderWidth();
			RectF getListBorderRadius();
			RectF getListPadding();
			Color getShadowColor(const CBuiltInSelect::State state);
			PointF getShadowShift(const CBuiltInSelect::State state);
			int getShadowRadius(const CBuiltInSelect::State state);
			BorderColor getBorderColor(const CBuiltInSelect::State state);
			Color getBackgroundColor(const CBuiltInSelect::State state);
			Gradient *getBackgroundGradient(const CBuiltInSelect::State state);
			BorderColor getInputBorderColor(const CBuiltInSelect::State state);
			Color getInputBackgroundColor(const CBuiltInSelect::State state);
			Gradient *getInputBackgroundGradient(const CBuiltInSelect::State state);
			BorderColor getArrowBorderColor(const CBuiltInSelect::State state);
			Color getArrowBackgroundColor(const CBuiltInSelect::State state);
			Gradient *getArrowBackgroundGradient(const CBuiltInSelect::State state);
			Color getArrowColor(const CBuiltInSelect::State state);
			BorderColor getListBorderColor();
			Color getListBackgroundColor();
			Gradient *getListBackgroundGradient();
			Color getListShadowColor();
			PointF getListShadowShift();
			int getListShadowRadius();

			// Layout setters (work only if default built-in select is used)
			bool setArrowAtRight(const bool value);
			bool setOpenDirection(const CBuiltInSelect::OpenDirection value);
			bool setListWidth(const float value);
			bool setListMaxHeight(const float value);
			bool setArrowArea(const CBuiltInSelect::ArrowArea value);
			bool setArrowAreaSize(const float value);
			bool setArrowSize(const float value);
			bool setBorderWidth(const RectF &value);
			bool setBorderRadius(const RectF &value);
			bool setPadding(const RectF &value);
			bool setArrowBorderWidth(const RectF &value);
			bool setArrowBorderRadius(const RectF &value);
			bool setListBorderWidth(const RectF &value);
			bool setListBorderRadius(const RectF &value);
			bool setListPadding(const RectF &value);
			bool setShadowColor(const CBuiltInSelect::State state, const Color &value);
			bool setShadowShift(const CBuiltInSelect::State state, const PointF &value);
			bool setShadowRadius(const CBuiltInSelect::State state, const int value);
			bool setBorderColor(const CBuiltInSelect::State state, const BorderColor &value);
			bool setBackgroundColor(const CBuiltInSelect::State state, const Color &value);
			bool setInputBorderColor(const CBuiltInSelect::State state, const BorderColor &value);
			bool setInputBackgroundColor(const CBuiltInSelect::State state, const Color &value);
			bool setArrowBorderColor(const CBuiltInSelect::State state, const BorderColor &value);
			bool setArrowBackgroundColor(const CBuiltInSelect::State state, const Color &value);
			bool setArrowColor(const CBuiltInSelect::State state, const Color &value);
			bool setListBorderColor(const BorderColor &value);
			bool setListBackgroundColor(const Color &value);
			bool setListShadowColor(const Color &value);
			bool setListShadowShift(const PointF &value);
			bool setListShadowRadius(const int value);

			// Methods
			bool Add(const String &caption, const bool category);
		};
	}
}
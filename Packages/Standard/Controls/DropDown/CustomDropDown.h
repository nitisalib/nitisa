// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h"
#include "Nitisa/BuiltInControls/IBuiltInDropDownListener.h"
#include "Nitisa/Core/Consts.h"
#include "Nitisa/Core/ControlItemList.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include <chrono>

namespace nitisa
{
	class IBuiltInControl;
	class IBuiltInDropDown;
	class IControl;
	class IListItem;
	class IListItemOwner;
	class IStyle;

	namespace standard
	{
		class CCustomDropDownService;

		class CCustomDropDown :public CControlItemList
		{
			friend CCustomDropDownService;
		private:
			class CDropDown :public CBuiltInDropDown
			{
			private:
				CCustomDropDown *m_pDropDown;
			public:
				CDropDown(CCustomDropDown *dropdown);

				IControl *getControl() override;
				State getState() override;
			};

			class CDropDownListener :public virtual IBuiltInDropDownListener
			{
			private:
				CCustomDropDown *m_pDropDown;
			public:
				CDropDownListener(CCustomDropDown *dropdown);

				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnTextChange(IBuiltInControl *sender) override;
				void NotifyOnSelect(IBuiltInControl *sender, const int index) override;
				void NotifyOnOpen(IBuiltInControl *sender) override;
				void NotifyOnClose(IBuiltInControl *sender) override;
			};
		private:
			IBuiltInDropDown *m_pDropDown;
			CDropDownListener m_cListener;

			bool m_bIgnoreKillCaptureMouse;

			IBuiltInDropDown *getDropDown();
			void UpdateDropDown();
			void UpdateFromStyle(IStyle *style);
			void Render();
			void RenderList();
		public:
			void(*OnChange)(IControl *sender); // Event called when text changed
			void(*OnSelect)(IControl *sender, const int index); // Event called when item selected

			// IControl getters
			bool hasExtra() override;

			// IControl setters
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			int getItemCount() override;
			IListItem *getItem(const int index) override;
			int getItemIndex(IListItem *item) override;

			bool AddItem(IListItem *item) override;
			bool InsertItem(IListItem *item, const int before) override;
			bool DeleteItem(const int index) override;
			bool DeleteItem(IListItem *item) override;
			bool DeleteItems() override;

			IControl *getControl(const PointF &position) override;
			RectF getClientRect() override;
			RectF getRenderRect() override;
			CursorType getCursor() override;

			IListItemOwner *QueryListItemOwner() override;

			CCustomDropDown(const String &class_name, const bool accept_form, const bool accept_control, const bool tab_stop, const bool editable, const Point &design_dpi = DesignDPI);
			~CCustomDropDown() override;

			// Return layout properties
			CBuiltInDropDown::State getState();
			bool isEditable();
			bool isOpened();
			bool isArrowAtRight();
			bool isSortable();
			CBuiltInDropDown::OpenDirection getOpenDirection();
			CBuiltInDropDown::ArrowArea getArrowArea();
			float getListWidth();
			float getListMaxHeight();
			String getText();
			int getActiveIndex();
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
			Color getShadowColor(const CBuiltInDropDown::State state);
			Color getShadowColorEditable(const CBuiltInDropDown::State state);
			PointF getShadowShift(const CBuiltInDropDown::State state);
			PointF getShadowShiftEditable(const CBuiltInDropDown::State state);
			int getShadowRadius(const CBuiltInDropDown::State state);
			int getShadowRadiusEditable(const CBuiltInDropDown::State state);
			BorderColor getBorderColor(const CBuiltInDropDown::State state);
			BorderColor getBorderColorEditable(const CBuiltInDropDown::State state);
			Color getLeftBorderColor(const CBuiltInDropDown::State state);
			Color getLeftBorderColorEditable(const CBuiltInDropDown::State state);
			Color getTopBorderColor(const CBuiltInDropDown::State state);
			Color getTopBorderColorEditable(const CBuiltInDropDown::State state);
			Color getRightBorderColor(const CBuiltInDropDown::State state);
			Color getRightBorderColorEditable(const CBuiltInDropDown::State state);
			Color getBottomBorderColor(const CBuiltInDropDown::State state);
			Color getBottomBorderColorEditable(const CBuiltInDropDown::State state);
			Color getBackgroundColor(const CBuiltInDropDown::State state);
			Color getBackgroundColorEditable(const CBuiltInDropDown::State state);
			Gradient *getBackgroundGradient(const CBuiltInDropDown::State state);
			Gradient *getBackgroundGradientEditable(const CBuiltInDropDown::State state);
			BorderColor getArrowBorderColor(const CBuiltInDropDown::State state);
			BorderColor getArrowBorderColorEditable(const CBuiltInDropDown::State state);
			Color getArrowLeftBorderColor(const CBuiltInDropDown::State state);
			Color getArrowLeftBorderColorEditable(const CBuiltInDropDown::State state);
			Color getArrowTopBorderColor(const CBuiltInDropDown::State state);
			Color getArrowTopBorderColorEditable(const CBuiltInDropDown::State state);
			Color getArrowRightBorderColor(const CBuiltInDropDown::State state);
			Color getArrowRightBorderColorEditable(const CBuiltInDropDown::State state);
			Color getArrowBottomBorderColor(const CBuiltInDropDown::State state);
			Color getArrowBottomBorderColorEditable(const CBuiltInDropDown::State state);
			Color getArrowBackgroundColor(const CBuiltInDropDown::State state);
			Color getArrowBackgroundColorEditable(const CBuiltInDropDown::State state);
			Gradient *getArrowBackgroundGradient(const CBuiltInDropDown::State state);
			Gradient *getArrowBackgroundGradientEditable(const CBuiltInDropDown::State state);
			Color getArrowColor(const CBuiltInDropDown::State state);
			Color getArrowColorEditable(const CBuiltInDropDown::State state);
			BorderColor getListBorderColor();
			BorderColor getListBorderColorEditable();
			Color getListLeftBorderColor();
			Color getListLeftBorderColorEditable();
			Color getListTopBorderColor();
			Color getListTopBorderColorEditable();
			Color getListRightBorderColor();
			Color getListRightBorderColorEditable();
			Color getListBottomBorderColor();
			Color getListBottomBorderColorEditable();
			Color getListBackgroundColor();
			Color getListBackgroundColorEditable();
			Gradient *getListBackgroundGradient();
			Gradient *getListBackgroundGradientEditable();
			Color getListShadowColor();
			Color getListShadowColorEditable();
			PointF getListShadowShift();
			PointF getListShadowShiftEditable();
			int getListShadowRadius();
			int getListShadowRadiusEditable();
			float getSearchResetInterval();
			IBuiltInDropDown::FCompare getCompareFunc();
			IBuiltInDropDown::FGetItemText getItemTextFunc();
			IBuiltInDropDown::FSearch getSearchFunc();

			bool setDropDown(IBuiltInDropDown *value); // Assign another built-in dropdown
			// Set layout properties
			bool setEditable(const bool value);
			bool setArrowAtRight(const bool value);
			bool setSortable(const bool value);
			bool setOpenDirection(const CBuiltInDropDown::OpenDirection value);
			bool setListWidth(const float value);
			bool setListMaxHeight(const float value);
			bool setText(const String &value);
			bool setActiveIndex(const int value);
			bool setArrowArea(const CBuiltInDropDown::ArrowArea value);
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
			bool setShadowColor(const CBuiltInDropDown::State state, const Color &value);
			bool setShadowColorEditable(const CBuiltInDropDown::State state, const Color &value);
			bool setShadowShift(const CBuiltInDropDown::State state, const PointF &value);
			bool setShadowShiftEditable(const CBuiltInDropDown::State state, const PointF &value);
			bool setShadowRadius(const CBuiltInDropDown::State state, const int value);
			bool setShadowRadiusEditable(const CBuiltInDropDown::State state, const int value);
			bool setBorderColor(const CBuiltInDropDown::State state, const BorderColor &value);
			bool setBorderColorEditable(const CBuiltInDropDown::State state, const BorderColor &value);
			bool setLeftBorderColor(const CBuiltInDropDown::State state, const Color &value);
			bool setLeftBorderColorEditable(const CBuiltInDropDown::State state, const Color &value);
			bool setTopBorderColor(const CBuiltInDropDown::State state, const Color &value);
			bool setTopBorderColorEditable(const CBuiltInDropDown::State state, const Color &value);
			bool setRightBorderColor(const CBuiltInDropDown::State state, const Color &value);
			bool setRightBorderColorEditable(const CBuiltInDropDown::State state, const Color &value);
			bool setBottomBorderColor(const CBuiltInDropDown::State state, const Color &value);
			bool setBottomBorderColorEditable(const CBuiltInDropDown::State state, const Color &value);
			bool setBackgroundColor(const CBuiltInDropDown::State state, const Color &value);
			bool setBackgroundColorEditable(const CBuiltInDropDown::State state, const Color &value);
			bool setArrowBorderColor(const CBuiltInDropDown::State state, const BorderColor &value);
			bool setArrowBorderColorEditable(const CBuiltInDropDown::State state, const BorderColor &value);
			bool setArrowLeftBorderColor(const CBuiltInDropDown::State state, const Color &value);
			bool setArrowLeftBorderColorEditable(const CBuiltInDropDown::State state, const Color &value);
			bool setArrowTopBorderColor(const CBuiltInDropDown::State state, const Color &value);
			bool setArrowTopBorderColorEditable(const CBuiltInDropDown::State state, const Color &value);
			bool setArrowRightBorderColor(const CBuiltInDropDown::State state, const Color &value);
			bool setArrowRightBorderColorEditable(const CBuiltInDropDown::State state, const Color &value);
			bool setArrowBottomBorderColor(const CBuiltInDropDown::State state, const Color &value);
			bool setArrowBottomBorderColorEditable(const CBuiltInDropDown::State state, const Color &value);
			bool setArrowBackgroundColor(const CBuiltInDropDown::State state, const Color &value);
			bool setArrowBackgroundColorEditable(const CBuiltInDropDown::State state, const Color &value);
			bool setArrowColor(const CBuiltInDropDown::State state, const Color &value);
			bool setArrowColorEditable(const CBuiltInDropDown::State state, const Color &value);
			bool setListBorderColor(const BorderColor &value);
			bool setListBorderColorEditable(const BorderColor &value);
			bool setListLeftBorderColor(const Color &value);
			bool setListLeftBorderColorEditable(const Color &value);
			bool setListTopBorderColor(const Color &value);
			bool setListTopBorderColorEditable(const Color &value);
			bool setListRightBorderColor(const Color &value);
			bool setListRightBorderColorEditable(const Color &value);
			bool setListBottomBorderColor(const Color &value);
			bool setListBottomBorderColorEditable(const Color &value);
			bool setListBackgroundColor(const Color &value);
			bool setListBackgroundColorEditable(const Color &value);
			bool setListShadowColor(const Color &value);
			bool setListShadowColorEditable(const Color &value);
			bool setListShadowShift(const PointF &value);
			bool setListShadowShiftEditable(const PointF &value);
			bool setListShadowRadius(const int value);
			bool setListShadowRadiusEditable(const int value);
			bool setSearchResetInterval(const float value);
			bool setCompareFunc(IBuiltInDropDown::FCompare value);
			bool setGetItemTextFunc(IBuiltInDropDown::FGetItemText value);
			bool setSearchFunc(IBuiltInDropDown::FSearch value);

			bool Open(); // Open list
			bool Close(); // Close list
		};
	}
}
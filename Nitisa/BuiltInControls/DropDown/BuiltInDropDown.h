// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/BuiltInControl.h"
#include "../../Core/CursorType.h"
#include "../../Core/Key.h"
#include "../../Core/Strings.h"
#include "../../Image/BorderColor.h"
#include "../../Image/Color.h"
#include "../../Image/Gradient.h"
#include "../../Interfaces/IFeedbackListener.h"
#include "../../Math/Mat4f.h"
#include "../../Math/Point.h"
#include "../../Math/PointF.h"
#include "../../Math/RectF.h"
#include "../Scroll/BuiltInScroll.h"
#include "../TextInput/BuiltInTextInput.h"
#include "../IBuiltInDropDown.h"
#include "../IBuiltInScrollListener.h"
#include "../IBuiltInTextInputListener.h"
#include <chrono>
#include <vector>

namespace nitisa
{
	class IBuiltInControl;
	class IBuiltInControlListener;
	class IBuiltInScroll;
	class IBuiltInTextInput;
	class IControl;
	class IFont;
	class IListItem;
	class IListItemOwner;
	class IRenderer;
	class IStyle;
	class ITexture;

	class CBuiltInDropDownListItemOwner;

	struct Block;

	class CBuiltInDropDown :public virtual IBuiltInDropDown, public CBuiltInControl
	{
		friend CBuiltInDropDownListItemOwner;
	private:
		class CTextInput :public CBuiltInTextInput
		{
		private:
			CBuiltInDropDown *m_pDropDown;
		public:
			CTextInput(CBuiltInDropDown *dropdown);

			IControl *getControl() override;
			State getState() override;
		};

		class CTextInputListener :public virtual IBuiltInTextInputListener
		{
		private:
			CBuiltInDropDown *m_pDropDown;
		public:
			CTextInputListener(CBuiltInDropDown *dropdown);

			void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
			void NotifyOnTextChanged(IBuiltInControl *sender) override;
		};

		class CScroll :public CBuiltInScroll
		{
		private:
			CBuiltInDropDown *m_pDropDown;
		public:
			CScroll(CBuiltInDropDown *dropdown);

			IControl *getControl() override;
		};

		class CScrollListener :public virtual IBuiltInScrollListener
		{
		private:
			CBuiltInDropDown *m_pDropDown;
		public:
			CScrollListener(CBuiltInDropDown *dropdown);

			void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
			void NotifyOnScroll(IBuiltInControl *sender) override;
		};

		class CGradientListener :public virtual IFeedbackListener
		{
		private:
			CBuiltInDropDown *m_pControl;
		public:
			void NotifyOnChange() override;

			CGradientListener(CBuiltInDropDown *control);
		};

		enum class ElementType
		{
			None,
			Input,
			Arrow,
			List,
			ListScroll
		};
	public:
		enum class State // Possible states
		{
			Normal, // Common, normal state
			Hovered, // Control is hovered
			Focused, // Control is focused
			FocusedHovered, // Control is focused and hovered
			Disabled // Control is disabled
		};

		enum class ArrowArea // How open/close arrow area width should be calculated
		{
			Absolute, // Arrow area width is specified in pixels
			Height, // Arrow area width is equal to control height
			WidthPart // Arrow area width is specified in parts of control width
		};

		enum class OpenDirection // Where list with items should appear in opened dropdown
		{
			Up, // At the top of the control
			Down, // At the bottom of the control
			Auto // Open down if possible (depending on position of a form) or up otherwise
		};
	private:
		CGradientListener m_cGradientListener;
		bool m_bEditable;
		bool m_bOpened;
		bool m_bArrowAtRight;
		bool m_bSortable;
		OpenDirection m_eOpenDirection;
		ArrowArea m_eArrowArea; // Arrow area size calculation type
		float m_fListWidth; // > 0 - specified size, <= 0 - same as getSize()
		float m_fListMaxHeight;
		int m_iActiveIndex;
		float m_fArrowAreaSize; // Arrow area size calculation parameter
		float m_fArrowSize; // Arrow size in parts of arrow area client rect min(width, height)
		RectF m_sBorderWidth;
		RectF m_sBorderRadius;
		RectF m_sPadding;
		RectF m_sArrowBorderWidth;
		RectF m_sArrowBorderRadius;
		RectF m_sListBorderWidth;
		RectF m_sListBorderRadius;
		RectF m_sListPadding;
		float m_fSearchResetInterval;
		FCompare m_fCompare;
		FGetItemText m_fGetItemText;
		FSearch m_fSearch;
		bool m_bLoopActiveItemOnDoubleClick;

		Color m_aShadowColor[(int)State::Disabled + 1][2];
		PointF m_aShadowShift[(int)State::Disabled + 1][2];
		int m_aShadowRadius[(int)State::Disabled + 1][2];
		BorderColor m_aBorderColor[(int)State::Disabled + 1][2];
		Color m_aBackgroundColor[(int)State::Disabled + 1][2];
		Gradient m_aBackgroundGradient[(int)State::Disabled + 1][2];
		BorderColor m_aArrowBorderColor[(int)State::Disabled + 1][2];
		Color m_aArrowBackgroundColor[(int)State::Disabled + 1][2];
		Gradient m_aArrowBackgroundGradient[(int)State::Disabled + 1][2];
		Color m_aArrowColor[(int)State::Disabled + 1][2];
		BorderColor m_aListBorderColor[2];
		Color m_aListBackgroundColor[2];
		Gradient m_aListBackgroundGradient[2];
		Color m_aListShadowColor[2];
		PointF m_aListShadowShift[2];
		int m_aListShadowRadius[2];

		IBuiltInTextInput *m_pTextInput;
		IBuiltInScroll *m_pScroll;
		std::vector<IListItem*> m_aItems;
		bool m_bIgnoreGradient;
		IListItemOwner *m_pListItemOwner;
		RectF m_sListRect;
		float m_fListScroll;
		float m_fListScrollMax;
		ElementType m_eHoveredElement;
		ElementType m_eDownElement;
		bool m_bSorted;
		String m_sSearch;
		std::chrono::steady_clock::time_point m_sLastSearch;
		IBuiltInControlListener *m_pListener;
		CTextInputListener m_cTextInputListener;
		CScrollListener m_cScrollListener;
		ITexture *m_pCanvasControl;
		ITexture *m_pCanvasList;

		IBuiltInScroll *getScroll();
		RectF getRenderRect(const State state); // Control + List
		RectF getListRenderRect();
		RectF getControlRenderRect(const State state);
		RectF getControlRenderRect();
		RectF getArrowAreaRect();
		IListItem *getItem(const PointF &position);
		bool isListHovered(const PointF &position);
		bool ScrollToActiveItem();
		void UpdateList();
		bool UpdateHoveredItem();
		bool UpdateHoveredItem(const PointF &position);
		void UpdateInput();
		void SortItems();
		ElementType getElement(const PointF &position);
		PointF LocalToInput(const PointF &position);
		PointF LocalToScroll(const PointF &position);
		bool ProcessKeyUp();
		bool ProcessKeyDown();
		bool ProcessKeyPageUp();
		bool ProcessKeyPageDown();
		bool ProcessKeyHome();
		bool ProcessKeyEnd();
		void RenderList(IRenderer *renderer, const Mat4f &matrix);
		void RenderListItems(IRenderer *renderer, const RectF &rect);
		void RenderListScroll(IRenderer *renderer, const RectF &rect);
		void RenderControl(IRenderer *renderer, const Mat4f &matrix, const Block *block);
		void RenderControlArrowToCanvas(IRenderer *renderer, const State state, const PointF &disp);
		void RenderControlActiveItemToCanvas(IRenderer *renderer, const State state, const RectF &rect);
		void RenderControlInputToCanvas(IRenderer *renderer, const State state, const RectF &rect);
	public:
		IBuiltInControlListener *getListener() override;
		bool isHovered() override;
		RectF getClientRect() override;
		RectF getRenderRect() override;
		CursorType getCursor(const PointF &position, const CursorType def) override;
		bool isInside(const PointF &position) override;
		bool isDown() override;
		IBuiltInTextInput *getTextInput() override;

		void setListener(IBuiltInControlListener *value) override;
		bool setEnabled(const bool value) override;
		bool setFocused(const bool value) override;
		bool setSize(const PointF &value) override;
		bool setDPI(const Point &value) override;

		void UpdateFromStyle(IStyle *style, const String &class_name) override;
		void Update() override;
		void Render(const bool last_pass, const Mat4f &matrix, const Block *block) override;
		void Refresh() override;

		// State change notifications
		void NotifyOnAttach() override;
		void NotifyOnDeactivate() override;
		void NotifyOnFreeResources() override;

		// Mouse notifications
		bool NotifyOnMouseHover(const PointF &position) override;
		bool NotifyOnMouseLeave() override;
		bool NotifyOnMouseMove(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseLeftDown(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseLeftUp(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseLeftDoubleClick(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseMiddleDown(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseMiddleUp(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseMiddleDoubleClick(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseRightDown(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseRightUp(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift) override;
		bool NotifyOnMouseRightDoubleClick(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift) override;
		void NotifyOnMouseDownCancel() override;
		bool NotifyOnMouseVerticalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta) override;
		bool NotifyOnMouseHorizontalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta) override;

		// Keyboard notifications
		bool NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock) override;
		bool NotifyOnKeyUp(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock) override;
		bool NotifyOnChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock) override;
		bool NotifyOnDeadChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock) override;

		// Other input notifications
		bool NotifyOnDropFiles(const PointF &position, const StringArray &filenames) override;

		// Clipboard notifications
		bool NotifyOnPasteString(const String &text) override;

		int getItemCount() override;
		IListItem *getItem(const int index) override;
		int getItemIndex(IListItem *item) override;
		bool isEditable() override;
		bool isOpened() override;
		bool isSortable() override;
		String getText() override;
		int getActiveIndex() override;
		FCompare getCompareFunc() override;
		FGetItemText getItemTextFunc() override;
		FSearch getSearchFunc() override;
		PointF getMousePosition() override; // Suppose dropdown is only translated. If it's transformed in other way, overwrite the method
		bool isLoopActiveItemOnDoubleClick() override;

		bool setTextInput(IBuiltInTextInput *value) override;
		bool setScroll(IBuiltInScroll *value) override;
		bool setEditable(const bool value) override;
		bool setSortable(const bool value) override;
		bool setText(const String &value) override;
		bool setActiveIndex(const int value) override;
		bool setCompareFunc(FCompare value) override;
		bool setGetItemTextFunc(FGetItemText value) override;
		bool setSearchFunc(FSearch value) override;
		bool setLoopActiveItemOnDoubleClick(const bool value) override;

		bool AddItem(IListItem *item) override;
		bool InsertItem(IListItem *item, const int before) override;
		bool DeleteItem(const int index) override;
		bool DeleteItem(IListItem *item) override;
		bool DeleteItems() override;
		bool MoveItem(IListItem *item, const int before) override;

		bool Open() override;
		bool Close() override;
		IListItemOwner *QueryListItemOwner() override;

		/**
		Constructor
		@param editable Whether dropdown will have text input
		@param compare Item comparison function
		@param get_item_text Function returning item caption or name
		@param search Searching function
		*/
		CBuiltInDropDown(const bool editable, FCompare compare, FGetItemText get_item_text, FSearch search);
		~CBuiltInDropDown();

		virtual State getState(); // Return current state
		bool isArrowAtRight() const; // Return whether arrow area at the right of the control
		OpenDirection getOpenDirection() const; // Return where list of items will be shown when opening the dropdown
		ArrowArea getArrowArea() const; // Return how arrow area is calculated
		float getListWidth() const; // Return width of item list
		float getListMaxHeight() const; // Return maximum height of item list
		float getArrowAreaSize() const; // Return parameter of calculating arrow area width
		float getArrowSize() const; // Return arrow area size
		RectF getBorderWidth() const; // Return border widths
		RectF getBorderRadius() const; // Return border radiuses
		RectF getPadding() const; // Return padding
		RectF getArrowBorderWidth() const; // Return arrow area border widths
		RectF getArrowBorderRadius() const; // Return arrow area corner radiuses
		RectF getListBorderWidth() const; // Return item list border widths
		RectF getListBorderRadius() const; // Return item list corner radiuses
		RectF getListPadding() const; // Return item list padding
		Color getShadowColor(const State state) const; // Return shadow color depending on state in non-editable mode
		Color getShadowColorEditable(const State state) const; // Return shadow color depending on state in editable mode
		PointF getShadowShift(const State state) const; // Return shadow shift depending on state in non-editable mode
		PointF getShadowShiftEditable(const State state) const; // Return shadow shift depending on state in editable mode
		int getShadowRadius(const State state) const; // Return shadow blur radius depending on state in non-editable mode
		int getShadowRadiusEditable(const State state) const; // Return shadow blur radius depending on state in editable mode
		BorderColor getBorderColor(const State state) const; // Return border colours depending on state in non-editable mode
		BorderColor getBorderColorEditable(const State state) const; // Return border colours depending on state in editable mode
		Color getLeftBorderColor(const State state) const; // Return left border colour depending on state in non-editable mode
		Color getLeftBorderColorEditable(const State state) const; // Return left border colour depending on state in editable mode
		Color getTopBorderColor(const State state) const; // Return top border colour depending on state in non-editable mode
		Color getTopBorderColorEditable(const State state) const; // Return top border colour depending on state in editable mode
		Color getRightBorderColor(const State state) const; // Return right border colour depending on state in non-editable mode
		Color getRightBorderColorEditable(const State state) const; // Return right border colour depending on state in editable mode
		Color getBottomBorderColor(const State state) const; // Return bottom border colour depending on state in non-editable mode
		Color getBottomBorderColorEditable(const State state) const; // Return bottom border colour depending on state in editable mode
		Color getBackgroundColor(const State state) const; // Return background colour depending on state in non-editable mode
		Color getBackgroundColorEditable(const State state) const; // Return background colour depending on state in editable mode
		Gradient *getBackgroundGradient(const State state); // Return background gradient depending on state in non-editable mode
		Gradient *getBackgroundGradientEditable(const State state); // Return background gradient depending on state in editable mode
		BorderColor getArrowBorderColor(const State state) const; // Return arrow area border colours depending on state in non-editable mode
		BorderColor getArrowBorderColorEditable(const State state) const; // Return arrow area border colours depending on state in editable mode
		Color getArrowLeftBorderColor(const State state) const; // Return arrow area left border colour depending on state in non-editable mode
		Color getArrowLeftBorderColorEditable(const State state) const; // Return arrow area left border colour depending on state in editable mode
		Color getArrowTopBorderColor(const State state) const; // Return arrow area top border colour depending on state in non-editable mode
		Color getArrowTopBorderColorEditable(const State state) const; // Return arrow area top border colour depending on state in editable mode
		Color getArrowRightBorderColor(const State state) const; // Return arrow area right border colour depending on state in non-editable mode
		Color getArrowRightBorderColorEditable(const State state) const; // Return arrow area right border colour depending on state in editable mode
		Color getArrowBottomBorderColor(const State state) const; // Return arrow area bottom border colour depending on state in non-editable mode
		Color getArrowBottomBorderColorEditable(const State state) const; // Return arrow area bottom border colour depending on state in editable mode
		Color getArrowBackgroundColor(const State state) const; // Return arrow area background colour depending on state in non-editable mode
		Color getArrowBackgroundColorEditable(const State state) const; // Return arrow area background colour depending on state in editable mode
		Gradient *getArrowBackgroundGradient(const State state); // Return arrow area background gradient depending on state in non-editable mode
		Gradient *getArrowBackgroundGradientEditable(const State state); // Return arrow area background gradient depending on state in editable mode
		Color getArrowColor(const State state) const; // Return arrow colour depending on state in non-editable mode
		Color getArrowColorEditable(const State state) const; // Return arrow colour depending on state in editable mode
		BorderColor getListBorderColor() const; // Return list border colours in non-editable mode
		BorderColor getListBorderColorEditable() const; // Return list border colours in editable mode
		Color getListLeftBorderColor() const; // Return list left border colour in non-editable mode
		Color getListLeftBorderColorEditable() const; // Return list left border colour in editable mode
		Color getListTopBorderColor() const; // Return list top border colour in non-editable mode
		Color getListTopBorderColorEditable() const; // Return list top border colour in editable mode
		Color getListRightBorderColor() const; // Return list right border colour in non-editable mode
		Color getListRightBorderColorEditable() const; // Return list right border colour in editable mode
		Color getListBottomBorderColor() const; // Return list bottom border colour in non-editable mode
		Color getListBottomBorderColorEditable() const; // Return list bottom border colour in editable mode
		Color getListBackgroundColor() const; // Return list background colour in non-editable mode
		Color getListBackgroundColorEditable() const; // Return list background colour in editable mode
		Gradient *getListBackgroundGradient(); // Return list background gradient in non-editable mode
		Gradient *getListBackgroundGradientEditable(); // Return list background gradient in editable mode
		Color getListShadowColor() const; // Return list shadow colour in non-editable mode
		Color getListShadowColorEditable() const; // Return list shadow colour in editable mode
		PointF getListShadowShift() const; // Return list shadow shift in non-editable mode
		PointF getListShadowShiftEditable() const; // Return list shadow shift in editable mode
		int getListShadowRadius() const; // Return list shadow blur radius in non-editable mode
		int getListShadowRadiusEditable() const; // Return list shadow blur radius in editable mode
		float getSearchResetInterval() const; // Return reset search interval in seconds

		bool setArrowAtRight(const bool value); // Set whether arrow area should be at right of the control
		bool setOpenDirection(const OpenDirection value); // Set where to show item list
		bool setListWidth(const float value); // Set item list width
		bool setListMaxHeight(const float value); // Set item list maximum height
		bool setArrowArea(const ArrowArea value);  // Set arrow area width calculation type
		bool setArrowAreaSize(const float value); // Set arrow area calculation parameter
		bool setArrowSize(const float value); // Set arrow size
		bool setBorderWidth(const RectF &value); // Set border widths
		bool setBorderRadius(const RectF &value); // Set corner radiuses
		bool setPadding(const RectF &value); // Set padding
		bool setArrowBorderWidth(const RectF &value); // Set arrow area border widths
		bool setArrowBorderRadius(const RectF &value); // Set arrow area corner radiuses
		bool setListBorderWidth(const RectF &value); // Set item list border widths
		bool setListBorderRadius(const RectF &value); // Set item list corner radiuses
		bool setListPadding(const RectF &value); // Set item list padding
		bool setShadowColor(const State state, const Color &value); // Set shadow colour depending on state in non-editable mode
		bool setShadowColorEditable(const State state, const Color &value); // Set shadow colour depending on state in editable mode
		bool setShadowShift(const State state, const PointF &value); // Set shadow shift depending on state in non-editable mode
		bool setShadowShiftEditable(const State state, const PointF &value); // Set shadow shift depending on state in editable mode
		bool setShadowRadius(const State state, const int value); // Set shadow blur radius depending on state in non-editable mode
		bool setShadowRadiusEditable(const State state, const int value); // Set shadow blur radius depending on state in editable mode
		bool setBorderColor(const State state, const BorderColor &value); // Set border colours depending on state in non-editable mode
		bool setBorderColorEditable(const State state, const BorderColor &value); // Set border colours depending on state in editable mode
		bool setLeftBorderColor(const State state, const Color &value); // Set left border colour depending on state in non-editable mode
		bool setLeftBorderColorEditable(const State state, const Color &value); // Set left border colour depending on state in editable mode
		bool setTopBorderColor(const State state, const Color &value); // Set top border colour depending on state in non-editable mode
		bool setTopBorderColorEditable(const State state, const Color &value); // Set top border colour depending on state in editable mode
		bool setRightBorderColor(const State state, const Color &value); // Set right border colour depending on state in non-editable mode
		bool setRightBorderColorEditable(const State state, const Color &value); // Set right border colour depending on state in editable mode
		bool setBottomBorderColor(const State state, const Color &value); // Set bottom border colour depending on state in non-editable mode
		bool setBottomBorderColorEditable(const State state, const Color &value); // Set bottom border colour depending on state in editable mode
		bool setBackgroundColor(const State state, const Color &value); // Set background colour depending on state in non-editable mode
		bool setBackgroundColorEditable(const State state, const Color &value); // Set background colour depending on state in editable mode
		bool setArrowBorderColor(const State state, const BorderColor &value); // Set arrow area border colours depending on state in non-editable mode
		bool setArrowBorderColorEditable(const State state, const BorderColor &value); // Set arrow area border colours depending on state in editable mode
		bool setArrowLeftBorderColor(const State state, const Color &value); // Set arrow area left border colour depending on state in non-editable mode
		bool setArrowLeftBorderColorEditable(const State state, const Color &value); // Set arrow area left border colour depending on state in editable mode
		bool setArrowTopBorderColor(const State state, const Color &value); // Set arrow area top border colour depending on state in non-editable mode
		bool setArrowTopBorderColorEditable(const State state, const Color &value); // Set arrow area top border colour depending on state in editable mode
		bool setArrowRightBorderColor(const State state, const Color &value); // Set arrow area right border colour depending on state in non-editable mode
		bool setArrowRightBorderColorEditable(const State state, const Color &value); // Set arrow area right border colour depending on state in editable mode
		bool setArrowBottomBorderColor(const State state, const Color &value); // Set arrow area bottom border colour depending on state in non-editable mode
		bool setArrowBottomBorderColorEditable(const State state, const Color &value); // Set arrow area bottom border colour depending on state in editable mode
		bool setArrowBackgroundColor(const State state, const Color &value); // Set arrow area background colour depending on state in non-editable mode
		bool setArrowBackgroundColorEditable(const State state, const Color &value); // Set arrow area background colour depending on state in editable mode
		bool setArrowColor(const State state, const Color &value); // Set arrow colour depending on state in non-editable mode
		bool setArrowColorEditable(const State state, const Color &value); // Set arrow colour depending on state in editable mode
		bool setListBorderColor(const BorderColor &value); // Set item list border colours in non-editable mode
		bool setListBorderColorEditable(const BorderColor &value); // Set item list border colours in editable mode
		bool setListLeftBorderColor(const Color &value); // Set item list left border colour in non-editable mode
		bool setListLeftBorderColorEditable(const Color &value); // Set item list left border colour in editable mode
		bool setListTopBorderColor(const Color &value); // Set item list top border colour in non-editable mode
		bool setListTopBorderColorEditable(const Color &value); // Set item list top border colour in editable mode
		bool setListRightBorderColor(const Color &value); // Set item list right border colour in non-editable mode
		bool setListRightBorderColorEditable(const Color &value); // Set item list right border colour in editable mode
		bool setListBottomBorderColor(const Color &value); // Set item list bottom border colour in non-editable mode
		bool setListBottomBorderColorEditable(const Color &value); // Set item list bottom border colour in editable mode
		bool setListBackgroundColor(const Color &value); // Set item list background colour in non-editable mode
		bool setListBackgroundColorEditable(const Color &value); // Set item list background colour in editable mode
		bool setListShadowColor(const Color &value); // Set item list shadow colour in non-editable mode
		bool setListShadowColorEditable(const Color &value); // Set item list shadow colour in editable mode
		bool setListShadowShift(const PointF &value); // Set item list shadow shift in non-editable mode
		bool setListShadowShiftEditable(const PointF &value); // Set item list shadow shift in editable mode
		bool setListShadowRadius(const int value); // Set item list shadow blur radius in non-editable mode
		bool setListShadowRadiusEditable(const int value); // Set item list shadow blur radius in editable mode
		bool setSearchResetInterval(const float value); // Set reset search interval(in seconds)
	};
}
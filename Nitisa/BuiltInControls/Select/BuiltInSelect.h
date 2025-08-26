// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/BuiltInControl.h"
#include "../../Core/CursorType.h"
#include "../../Core/Key.h"
#include "../../Core/ListItemOwner.h"
#include "../../Core/Strings.h"
#include "../../Image/BorderColor.h"
#include "../../Image/Color.h"
#include "../../Image/Gradient.h"
#include "../../Interfaces/IFeedbackListener.h"
#include "../../Math/Mat4f.h"
#include "../../Math/Point.h"
#include "../../Math/PointF.h"
#include "../../Math/RectF.h"
#include "../ScrollLite/BuiltInScrollLite.h"
#include "../TextInput/BuiltInTextInput.h"
#include "../IBuiltInSelect.h"
#include "../IBuiltInScrollListener.h"
#include "../IBuiltInTextInputListener.h"
#include <vector>

namespace nitisa
{
	class IBuiltInControl;
	class IBuiltInControlListener;
	class IBuiltInScroll;
	class IBuiltInSelectListener;
	class IBuiltInTextInput;
	class IControl;
	class IFont;
	class IListItem;
	class IRenderer;
	class IStyle;
	class ITexture;

	struct Block;

	class CBuiltInSelect :public virtual IBuiltInSelect, public CBuiltInControl
	{
	private:
		class CGradientListener :public virtual IFeedbackListener
		{
		private:
			CBuiltInSelect *m_pControl;
		public:
			void NotifyOnChange() override;

			CGradientListener(CBuiltInSelect *control);
		};

		class CTextInput :public CBuiltInTextInput
		{
		private:
			CBuiltInSelect *m_pControl;
		public:
			IControl *getControl() override;
			State getState() override;

			CTextInput(CBuiltInSelect *control);
		};

		class CTextInputListener :public virtual IBuiltInTextInputListener
		{
		private:
			CBuiltInSelect *m_pControl;
		public:
			void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
			void NotifyOnTextChanged(IBuiltInControl *sender) override;

			CTextInputListener(CBuiltInSelect *control);
		};

		class CScroll :public CBuiltInScrollLite
		{
		private:
			CBuiltInSelect *m_pControl;
		public:
			IControl *getControl() override;
			
			CScroll(CBuiltInSelect *control);
		};

		class CScrollListener :public virtual IBuiltInScrollListener
		{
		private:
			CBuiltInSelect *m_pControl;
		public:
			void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
			void NotifyOnScroll(IBuiltInControl *sender) override;

			CScrollListener(CBuiltInSelect *control);
		};

		class COwner :public CListItemOwner
		{
		private:
			CBuiltInSelect * m_pControl;
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

			COwner(CBuiltInSelect *control);
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

		enum class OpenDirection // Where list with items should appear in opened drop-down
		{
			Up, // At the top of the control
			Down, // At the bottom of the control
			Auto // Open down if possible (depending on position of a form) or up otherwise
		};
	private:
		CGradientListener m_cGradientListener;
		CScrollListener m_cScrollListener;
		CTextInputListener m_cTextInputListener;
		COwner m_cOwner;
		IBuiltInControlListener *m_pListener;
		IBuiltInSelectListener *m_pSelectListener;
		bool m_bOpened;
		int m_iActiveIndex;
		bool m_bArrowAtRight;
		OpenDirection m_eOpenDirection;
		ArrowArea m_eArrowArea; // Arrow area size calculation type
		float m_fListWidth; // > 0 - specified size, <= 0 - same as getSize()
		float m_fListMaxHeight;
		float m_fArrowAreaSize; // Arrow area size calculation parameter
		float m_fArrowSize; // Arrow size in parts of arrow area client rectangle min(width, height)
		RectF m_sBorderWidth;
		RectF m_sBorderRadius;
		RectF m_sPadding;
		RectF m_sArrowBorderWidth;
		RectF m_sArrowBorderRadius;
		RectF m_sListBorderWidth;
		RectF m_sListBorderRadius;
		RectF m_sListPadding;

		Color m_aShadowColor[(int)State::Disabled + 1];
		PointF m_aShadowShift[(int)State::Disabled + 1];
		int m_aShadowRadius[(int)State::Disabled + 1];
		BorderColor m_aBorderColor[(int)State::Disabled + 1];
		Color m_aBackgroundColor[(int)State::Disabled + 1];
		Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
		BorderColor m_aInputBorderColor[(int)State::Disabled + 1];
		Color m_aInputBackgroundColor[(int)State::Disabled + 1];
		Gradient m_aInputBackgroundGradient[(int)State::Disabled + 1];
		BorderColor m_aArrowBorderColor[(int)State::Disabled + 1];
		Color m_aArrowBackgroundColor[(int)State::Disabled + 1];
		Gradient m_aArrowBackgroundGradient[(int)State::Disabled + 1];
		Color m_aArrowColor[(int)State::Disabled + 1];
		BorderColor m_sListBorderColor;
		Color m_sListBackgroundColor;
		Gradient m_cListBackgroundGradient;
		Color m_sListShadowColor;
		PointF m_sListShadowShift;
		int m_iListShadowRadius;

		IBuiltInScroll *m_pScroll;
		IBuiltInTextInput *m_pTextInput;
		std::vector<IListItem*> m_aItems;
		bool m_bIgnoreGradient;
		RectF m_sListRect;
		float m_fListScroll;
		float m_fListScrollMax;
		ElementType m_eHoveredElement;
		ElementType m_eDownElement;
		ITexture *m_pCanvasControl;
		ITexture *m_pCanvasList;

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
		ElementType getElement(const PointF &position);
		PointF LocalToInput(const PointF &position);
		PointF LocalToScroll(const PointF &position);
		bool ProcessKeyUp();
		bool ProcessKeyDown();
		bool ProcessKeyPageUp();
		bool ProcessKeyPageDown();
		bool ProcessKeyHome();
		bool ProcessKeyEnd();
		void RenderControl(IRenderer *renderer, const Mat4f &matrix, const Block *block);
		void RenderControlArrow(IRenderer *renderer, const State state, const PointF &disp);
		void RenderControlActiveItem(IRenderer *renderer, const State state, const RectF &rect);
		void RenderControlInput(IRenderer *renderer, const State state, const RectF &rect);
		void RenderList(IRenderer *renderer, const Mat4f &matrix);
		void RenderListItems(IRenderer *renderer, const RectF &rect);
		void RenderListScroll(IRenderer *renderer, const RectF &rect);
	public:
		// IBuiltInControl getters
		IBuiltInControlListener *getListener() override;
		bool isHovered() override;
		RectF getClientRect() override;
		RectF getRenderRect() override;
		CursorType getCursor(const PointF &position, const CursorType def) override;
		bool isInside(const PointF &position) override;
		bool isDown() override;

		// IBuiltInControl setters
		void setListener(IBuiltInControlListener *value) override;
		bool setEnabled(const bool value) override;
		bool setFocused(const bool value) override;
		bool setSize(const PointF &value) override;
		bool setDPI(const Point &value) override;

		// IBuiltInControl methods
		void UpdateFromStyle(IStyle *style, const String &class_name) override;
		void Update() override;
		void Render(const bool last_pass, const Mat4f &matrix, const Block *block) override;
		void Refresh() override;

		// IBuiltInSelect getters
		int getItemCount() override;
		IListItem *getItem(const int index) override;
		int getItemIndex(IListItem *item) override;
		bool isOpened() override;
		String getFilter() override;
		int getActiveIndex() override;
		PointF getMousePosition() override; // Suppose drop-down is only translated. If it's transformed in other way, overwrite the method
		IBuiltInScroll *getScroll() override;
		IBuiltInTextInput *getTextInput() override;

		// IBuiltInSelect setters
		bool setFilter(const String &value) override;
		bool setActiveIndex(const int value) override;
		bool setScroll(IBuiltInScroll *value) override;
		bool setTextInput(IBuiltInTextInput *value) override;

		// IBuiltInSelect items
		bool AddItem(IListItem *item) override;
		bool InsertItem(IListItem *item, const int before) override;
		bool DeleteItem(const int index) override;
		bool DeleteItem(IListItem *item) override;
		bool DeleteItems() override;
		bool MoveItem(IListItem *item, const int before) override;

		// IBuiltInSelect methods
		bool Open() override;
		bool Close() override;
		IListItemOwner *QueryListItemOwner() override;

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

		CBuiltInSelect();
		~CBuiltInSelect();

		// Getters
		virtual State getState(); // Return current state
		bool isArrowAtRight() const; // Return whether arrow area at the right of the control
		OpenDirection getOpenDirection() const; // Return where list of items will be shown when opening the drop-down
		ArrowArea getArrowArea() const; // Return how arrow area is calculated
		float getListWidth() const; // Return width of item list
		float getListMaxHeight() const; // Return maximum height of item list
		float getArrowAreaSize() const; // Return parameter of calculating arrow area width
		float getArrowSize() const; // Return arrow area size
		RectF getBorderWidth() const; // Return border widths
		RectF getBorderRadius() const; // Return border radii
		RectF getPadding() const; // Return padding
		RectF getArrowBorderWidth() const; // Return arrow area border widths
		RectF getArrowBorderRadius() const; // Return arrow area corner radii
		RectF getListBorderWidth() const; // Return item list border widths
		RectF getListBorderRadius() const; // Return item list corner radii
		RectF getListPadding() const; // Return item list padding
		Color getShadowColor(const State state) const; // Return shadow color depending on state
		PointF getShadowShift(const State state) const; // Return shadow shift depending on state
		int getShadowRadius(const State state) const; // Return shadow blur radius depending on state
		BorderColor getBorderColor(const State state) const; // Return border colors depending on state
		Color getBackgroundColor(const State state) const; // Return background color depending on state
		Gradient *getBackgroundGradient(const State state); // Return background gradient depending on state
		BorderColor getInputBorderColor(const State state) const; // Return input border colors depending on state
		Color getInputBackgroundColor(const State state) const; // Return input background color depending on state
		Gradient *getInputBackgroundGradient(const State state); // Return input background gradient depending on state
		BorderColor getArrowBorderColor(const State state) const; // Return arrow area border colors depending on state
		Color getArrowBackgroundColor(const State state) const; // Return arrow area background color depending on state
		Gradient *getArrowBackgroundGradient(const State state); // Return arrow area background gradient depending on state
		Color getArrowColor(const State state) const; // Return arrow color depending on state
		BorderColor getListBorderColor() const; // Return list border colors
		Color getListBackgroundColor() const; // Return list background color
		Gradient *getListBackgroundGradient(); // Return list background gradient
		Color getListShadowColor() const; // Return list shadow color
		PointF getListShadowShift() const; // Return list shadow shift
		int getListShadowRadius() const; // Return list shadow blur radius

		// Setters
		bool setArrowAtRight(const bool value); // Set whether arrow area should be at right of the control
		bool setOpenDirection(const OpenDirection value); // Set where to show item list
		bool setListWidth(const float value); // Set item list width
		bool setListMaxHeight(const float value); // Set item list maximum height
		bool setArrowArea(const ArrowArea value);  // Set arrow area width calculation type
		bool setArrowAreaSize(const float value); // Set arrow area calculation parameter
		bool setArrowSize(const float value); // Set arrow size
		bool setBorderWidth(const RectF &value); // Set border widths
		bool setBorderRadius(const RectF &value); // Set corner radii
		bool setPadding(const RectF &value); // Set padding
		bool setArrowBorderWidth(const RectF &value); // Set arrow area border widths
		bool setArrowBorderRadius(const RectF &value); // Set arrow area corner radii
		bool setListBorderWidth(const RectF &value); // Set item list border widths
		bool setListBorderRadius(const RectF &value); // Set item list corner radii
		bool setListPadding(const RectF &value); // Set item list padding
		bool setShadowColor(const State state, const Color &value); // Set shadow color depending on state
		bool setShadowShift(const State state, const PointF &value); // Set shadow shift depending on state
		bool setShadowRadius(const State state, const int value); // Set shadow blur radius depending on state
		bool setBorderColor(const State state, const BorderColor &value); // Set border colors depending on state
		bool setBackgroundColor(const State state, const Color &value); // Set background color depending on state
		bool setInputBorderColor(const State state, const BorderColor &value); // Set input border colors depending on state
		bool setInputBackgroundColor(const State state, const Color &value); // Set input background color depending on state
		bool setArrowBorderColor(const State state, const BorderColor &value); // Set arrow area border colors depending on state
		bool setArrowBackgroundColor(const State state, const Color &value); // Set arrow area background color depending on state
		bool setArrowColor(const State state, const Color &value); // Set arrow color depending on state
		bool setListBorderColor(const BorderColor &value); // Set item list border colors
		bool setListBackgroundColor(const Color &value); // Set item list background color
		bool setListShadowColor(const Color &value); // Set item list shadow color
		bool setListShadowShift(const PointF &value); // Set item list shadow shift
		bool setListShadowRadius(const int value); // Set item list shadow blur radius
	};
}
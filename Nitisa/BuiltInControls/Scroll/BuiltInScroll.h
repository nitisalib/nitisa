// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Aliases.h"
#include "../../Core/BuiltInControl.h"
#include "../../Core/Key.h"
#include "../../Core/Strings.h"
#include "../../Image/Color.h"
#include "../../Image/Gradient.h"
#include "../../Interfaces/IFeedbackListener.h"
#include "../../Interfaces/ITimerListener.h"
#include "../../Math/Mat4f.h"
#include "../../Math/Point.h"
#include "../../Math/PointF.h"
#include "../../Math/RectF.h"
#include "../IBuiltInScroll.h"

namespace nitisa
{
	class IBuiltInControlListener;
	class IRenderer;
	class IStyle;

	struct Block;

	class CBuiltInScroll :public virtual IBuiltInScroll, public CBuiltInControl
	{
	public:
		enum class ElementType // Describes scroll elements
		{
			StartArrow, // Start or decreasing arrow
			Scroller, // A part which could be used to drag and change position
			EndArrow, // End or increasing arrow
			None // None
		};

		enum class State // Describes possible states
		{
			Normal, // Normal
			Hovered, // Control is hovered
			Active, // Controls is active(user down mouse button over its active element and didn't release it yet)
			Disabled // Control is disabled
		};

		enum class ElementState // States of elements
		{
			NormalNormal, // Control is in normal state and element is in normal state as well
			HoveredNormal, // Control is hovered, element is in normal state
			HoveredHovered, // Control is hovered and element is hovered as well
			ActiveNormal, // Control is active, element is hovered
			ActiveActive, // Control is active and element is active as well
			DisabledDisabled // Both control and element are disabled
		};
	private:
		enum class ScrollBy
		{
			StartArrow,
			BeforeScroller,
			Scroller,
			AfterScroller,
			EndArrow,
			None
		};

		class CTimerListener :public ITimerListener
		{
		private:
			CBuiltInScroll *m_pControl;
		public:
			void NotifyOnTimer(const PlatformHandle id) override;

			CTimerListener(CBuiltInScroll *control);
		};

		class CGradientListener :public virtual IFeedbackListener
		{
		private:
			CBuiltInScroll *m_pControl;
		public:
			void NotifyOnChange() override;

			CGradientListener(CBuiltInScroll *control);
		};
	private:
		CGradientListener m_cGradientListener;
		float m_fMin;
		float m_fMax;
		float m_fScroll;
		float m_fScrollerSize;
		float m_fDeltaSmall;
		float m_fDeltaMedium;
		float m_fDeltaLarge;
		bool m_bVertical;
		bool m_bArrowsVisible;
		ElementType m_eHoveredElement;
		ElementType m_eActiveElement;
		float m_fScrollInterval;
		float m_fArrowSize; // 0..1(size in parts from client area of arrow element)
		// Background
		float m_fBorderWidth;
		float m_fBorderRadius;
		Color m_aBorderColor[(int)State::Disabled + 1];
		Color m_aBackgroundColor[(int)State::Disabled + 1];
		Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
		// Shadow
		int m_aShadowRadius[(int)State::Disabled + 1];
		PointF m_aShadowShift[(int)State::Disabled + 1];
		Color m_aShadowColor[(int)State::Disabled + 1];
		// Start arrow
		float m_fStartArrowBorderWidth;
		float m_fStartArrowBorderRadius;
		Color m_aStartArrowBorderColor[(int)ElementState::DisabledDisabled + 1];
		Color m_aStartArrowBackgroundColor[(int)ElementState::DisabledDisabled + 1];
		Gradient m_aStartArrowBackgroundGradient[(int)ElementState::DisabledDisabled + 1];
		Color m_aStartArrowColor1[(int)ElementState::DisabledDisabled + 1];
		Color m_aStartArrowColor2[(int)ElementState::DisabledDisabled + 1];
		Color m_aStartArrowColor3[(int)ElementState::DisabledDisabled + 1];
		// End arrow
		float m_fEndArrowBorderWidth;
		float m_fEndArrowBorderRadius;
		Color m_aEndArrowBorderColor[(int)ElementState::DisabledDisabled + 1];
		Color m_aEndArrowBackgroundColor[(int)ElementState::DisabledDisabled + 1];
		Gradient m_aEndArrowBackgroundGradient[(int)ElementState::DisabledDisabled + 1];
		Color m_aEndArrowColor1[(int)ElementState::DisabledDisabled + 1];
		Color m_aEndArrowColor2[(int)ElementState::DisabledDisabled + 1];
		Color m_aEndArrowColor3[(int)ElementState::DisabledDisabled + 1];
		// Scroller
		float m_fScrollerBorderWidth;
		float m_fScrollerBorderRadius;
		Color m_aScrollerBorderColor[(int)ElementState::DisabledDisabled + 1];
		Color m_aScrollerBackgroundColor[(int)ElementState::DisabledDisabled + 1];
		Gradient m_aScrollerBackgroundGradient[(int)ElementState::DisabledDisabled + 1];
		Color m_aScrollerLinesBorderColor[(int)ElementState::DisabledDisabled + 1];
		Color m_aScrollerLinesBackgroundColor[(int)ElementState::DisabledDisabled + 1];
		PointF m_sScrollerLinesSize; // X - in range 0..1(size in parts of scroller width for horizontal and height for vertical scroll), Y - size of rectangle and distance between them(absolute values)
		float m_fScrollerLinesDistance; // Distance between scroller rectangles(absolute using)
		float m_fScrollerLinesBorderWidth;

		IBuiltInControlListener *m_pListener;
		bool m_bScrolling;
		ScrollBy m_eScrollBy;
		PointF m_sScrollPosition; // Mouse position when scrolling
		float m_fScrollPosition;
		bool m_bHovered;
		PlatformHandle m_hTimer;
		bool m_bIgnoreGradient;
		CTimerListener m_cTimerListener;

		bool UpdateHoveredElement(const PointF &position);
		RectF getStartArrowRect();
		RectF getEndArrowRect();
		RectF getScrollerRect();
		ElementState getElementState(const ElementType element);
		ScrollBy getScrollElement(const PointF &position);
		float PositionToScroll(const PointF &position);
		void CalculateScroller(float &scroller_size, float &scrolling_area);
		float CalculateDeltaLarge();
		void RenderBackground(IRenderer *renderer, const State state, const RectF &rect);
		void RenderStartArrow(IRenderer *renderer, const PointF &disp);
		void RenderEndArrow(IRenderer *renderer, const PointF &disp);
		void RenderScroller(IRenderer *renderer, const PointF &disp);
	public:
		IBuiltInControlListener *getListener() override;
		bool isHovered() override;
		RectF getRenderRect() override;
		bool isDown() override;

		void setListener(IBuiltInControlListener *value) override;
		bool setEnabled(const bool value) override;
		bool setDPI(const Point &value) override;

		void UpdateFromStyle(IStyle *style, const String &class_name) override;
		void Render(const bool last_pass, const Mat4f &matrix, const Block *block) override;
		void Update() override;

		// State change notifications
		void NotifyOnAttach() override;
		void NotifyOnDeactivate() override;
		void NotifyOnFreeResources() override;

		// Mouse input notifications
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

		// Keyboard input notifications
		bool NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock) override;
		bool NotifyOnKeyUp(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock) override;
		bool NotifyOnChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock) override;
		bool NotifyOnDeadChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock) override;

		// Other input notifications
		bool NotifyOnDropFiles(const PointF &position, const StringArray &filenames) override;

		// Clipboard notifications
		bool NotifyOnPasteString(const String &text) override;

		float getMin() override;
		float getMax() override;
		float getScroll() override;
		float getScrollerSize() override;
		float getDeltaSmall() override;
		float getDeltaMedium() override;
		float getDeltaLarge() override;
		bool isVertical() override;
		bool isArrowsVisible() override;

		bool setMin(const float value) override;
		bool setMax(const float value) override;
		bool setScroll(const float value) override;
		bool setScrollerSize(const float value) override;
		bool setDeltaSmall(const float value) override;
		bool setDeltaMedium(const float value) override;
		bool setDeltaLarge(const float value) override;
		bool setVertical(const bool value) override;
		bool setArrowsVisible(const bool value) override;

		CBuiltInScroll(); // Constructor

		virtual State getState(); // Return current control state
		ElementType getHoveredElement() const; // Return hovered element
		ElementType getActiveElement() const; // Return active element
		float getScrollInterval() const; // Return scroll timer interval in seconds. Scroll happens when user click on scrolling arrows and hold mouse button
		float getArrowSize() const; // Return relative size of the arrows
		// Background
		float getBorderWidth() const; // Return border width
		float getBorderRadius() const; // Return corners radius
		Color getBorderColor(const State state) const; // Return border color depending on state
		Color getBackgroundColor(const State state) const; // Return background color depending on state
		Gradient *getBackgroundGradient(const State state); // Return background gradient depending on state
		// Shadow
		int getShadowRadius(const State state) const; // Return shadow blur radius depending on state
		PointF getShadowShift(const State state) const; // Return shadow shift depending on state
		Color getShadowColor(const State state) const; // Return shadow color depending on state
		// Start arrow
		float getStartArrowBorderWidth() const; // Return start arrow border width
		float getStartArrowBorderRadius() const; // Return start arrow corners radius
		Color getStartArrowBorderColor(const ElementState state) const; // Return start arrow border color depending on state
		Color getStartArrowBackgroundColor(const ElementState state) const; // Return start arrow background color depending on state
		Gradient *getStartArrowBackgroundGradient(const ElementState state); // Return start arrow background gradient depending on state
		Color getStartArrowColor1(const ElementState state) const; // Return start arrow triangle 1st corner color depending on state
		Color getStartArrowColor2(const ElementState state) const; // Return start arrow triangle 2nd corner color depending on state
		Color getStartArrowColor3(const ElementState state) const; // Return start arrow triangle 3rd corner color depending on state
		// End arrow
		float getEndArrowBorderWidth() const; // Return end arrow border width
		float getEndArrowBorderRadius() const; // Return end arrow corners radius
		Color getEndArrowBorderColor(const ElementState state) const; // Return end arrow border color depending on state
		Color getEndArrowBackgroundColor(const ElementState state) const; // Return end arrow background color depending on state
		Gradient *getEndArrowBackgroundGradient(const ElementState state); // Return end arrow background gradient depending on state
		Color getEndArrowColor1(const ElementState state) const; // Return end arrow triangle 1st corner color depending on state
		Color getEndArrowColor2(const ElementState state) const; // Return end arrow triangle 2nd corner color depending on state
		Color getEndArrowColor3(const ElementState state) const; // Return end arrow triangle 3rd corner color depending on state
		// Scroller
		float getScrollerBorderWidth() const; // Return scroller border width
		float getScrollerBorderRadius() const; // Return scroller corners radius
		Color getScrollerBorderColor(const ElementState state) const; // Return scroller border color depending on state
		Color getScrollerBackgroundColor(const ElementState state) const; // Return scroller background color depending on state
		Gradient *getScrollerBackgroundGradient(const ElementState state); // Return scroller background gradient depending on state
		Color getScrollerLinesBorderColor(const ElementState state) const; // Return scroller lines border color depending on state
		Color getScrollerLinesBackgroundColor(const ElementState state) const; // Return scroller lines background color depending on state
		PointF getScrollerLinesSize() const; // Return scroller lines size
		float getScrollerLinesDistance() const; // Return distance between scroller lines
		float getScrollerLinesBorderWidth() const; // Return border width of scroller lines

		bool setScrollInterval(const float value); // Set scroll interval(in seconds)
		bool setArrowSize(const float value); // Set arrow size
		// Background
		bool setBorderWidth(const float value); // Set borders width
		bool setBorderRadius(const float value); // Set corners radius
		bool setBorderColor(const State state, const Color &value); // Set borders color depending on state
		bool setBackgroundColor(const State state, const Color &value); // Set background color depending on state
		// Shadow
		bool setShadowRadius(const State state, const int value); // Set shadow blur radius depending on state
		bool setShadowShift(const State state, const PointF &value); // Set shadow shift depending on state
		bool setShadowColor(const State state, const Color &value); // Set shadow color depending on state
		// Start arrow
		bool setStartArrowBorderWidth(const float value); // Set start arrow borders width
		bool setStartArrowBorderRadius(const float value); // Set start arrow corners radius
		bool setStartArrowBorderColor(const ElementState state, const Color &value); // Set start arrow borders color depending on state
		bool setStartArrowBackgroundColor(const ElementState state, const Color &value); // Set start arrow background color depending on state
		bool setStartArrowColor1(const ElementState state, const Color &value); // Set start arrow triangle 1st corner color depending on state
		bool setStartArrowColor2(const ElementState state, const Color &value); // Set start arrow triangle 2nd corner color depending on state
		bool setStartArrowColor3(const ElementState state, const Color &value); // Set start arrow triangle 3rd corner color depending on state
		// End arrow
		bool setEndArrowBorderWidth(const float value); // Set end arrow borders width
		bool setEndArrowBorderRadius(const float value); // Set end arrow corners radius
		bool setEndArrowBorderColor(const ElementState state, const Color &value); // Set end arrow borders color depending on state
		bool setEndArrowBackgroundColor(const ElementState state, const Color &value); // Set end arrow background color depending on state
		bool setEndArrowColor1(const ElementState state, const Color &value); // Set end arrow triangle 1st corner color depending on state
		bool setEndArrowColor2(const ElementState state, const Color &value); // Set end arrow triangle 2nd corner color depending on state
		bool setEndArrowColor3(const ElementState state, const Color &value); // Set end arrow triangle 3rd corner color depending on state
		// Scroller
		bool setScrollerBorderWidth(const float value); // Set scroller borders width
		bool setScrollerBorderRadius(const float value); // Set scroller corners radius
		bool setScrollerBorderColor(const ElementState state, const Color &value); // Set scroller borders color
		bool setScrollerBackgroundColor(const ElementState state, const Color &value); // Set scroller background color
		bool setScrollerLinesBorderColor(const ElementState state, const Color &value); // Set scroller lines borders color
		bool setScrollerLinesBackgroundColor(const ElementState state, const Color &value); // Set scroller lines background color
		bool setScrollerLinesSize(const PointF &value); // Set scroller lines size
		bool setScrollerLinesDistance(const float value); // Set distance between scroller lines
		bool setScrollerLinesBorderWidth(const float value); // Set borders width of scroller lines

		void SwitchDirection(const bool size); // Vertical become horizontal and wise versa
	};
}
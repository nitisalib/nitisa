// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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

	class CBuiltInScrollLite :public virtual IBuiltInScroll, public CBuiltInControl
	{
	public:
		enum class ElementType // Describes scroll elements
		{
			Scroller, // A part which could be used to drag and change position
			None // None
		};

		enum class State // Describes possible states
		{
			Normal, // Normal
			Hovered, // Control is hovered
			Active, // Controls is active(user down mouse button over its active element and didn't release it yet)
			Disabled // Control is disabled
		};
	private:
		enum class ScrollBy
		{
			BeforeScroller,
			Scroller,
			AfterScroller,
			None
		};

		class CTimerListener :public ITimerListener
		{
		private:
			CBuiltInScrollLite *m_pControl;
		public:
			void NotifyOnTimer(const PlatformHandle id) override;

			CTimerListener(CBuiltInScrollLite *control);
		};

		class CGradientListener :public virtual IFeedbackListener
		{
		private:
			CBuiltInScrollLite *m_pControl;
		public:
			void NotifyOnChange() override;

			CGradientListener(CBuiltInScrollLite *control);
		};
	private:
		CGradientListener m_cGradientListener;
		float m_fMin;
		float m_fMax;
		float m_fScroll;
		float m_fScrollerSize;
		float m_fDeltaMedium;
		float m_fDeltaLarge;
		bool m_bVertical;

		float m_fScrollInterval;
		// Shadow
		int m_aShadowRadius[(int)State::Disabled + 1];
		Color m_aShadowColor[(int)State::Disabled + 1];
		PointF m_aShadowShift[(int)State::Disabled + 1];
		// Background
		bool m_bBorderRound;
		float m_fBorderWidth;
		Color m_aBorderColor[(int)State::Disabled + 1];
		Color m_aBackgroundColor[(int)State::Disabled + 1];
		Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
		// Scroller
		bool m_bScrollerRound;
		float m_fScrollerBorderWidth;
		Color m_aScrollerBorderColor[(int)State::Disabled + 1];
		Color m_aScrollerBackgroundColor[(int)State::Disabled + 1];
		Gradient m_aScrollerBackgroundGradient[(int)State::Disabled + 1];

		ElementType m_eHoveredElement;
		ElementType m_eActiveElement;
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
		RectF getScrollerRect();
		State getElementState(const ElementType element);
		ScrollBy getScrollElement(const PointF &position);
		float PositionToScroll(const PointF &position);
		void CalculateScroller(float &scroller_size, float &scrolling_area);
		float CalculateDeltaLarge();
		void RenderBackground(IRenderer *renderer, const State state, const RectF &rect);
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

		CBuiltInScrollLite(); // Constructor

		virtual State getState(); // Return current control state
		ElementType getHoveredElement() const; // Return hovered element
		ElementType getActiveElement() const; // Return active element
		float getScrollInterval() const; // Return scroll timer interval in seconds. Scroll happens when user click on scrolling arrows and hold mouse button
		// Shadow
		int getShadowRadius(const State state) const; // Return shadow blur radius depending on state
		PointF getShadowShift(const State state) const; // Return shadow shift depending on state
		Color getShadowColor(const State state) const; // Return shadow color depending on state
		// Background
		bool isBorderRound() const; // Return whether border has round borders
		float getBorderWidth() const; // Return border width
		Color getBorderColor(const State state) const; // Return border color depending on state
		Color getBackgroundColor(const State state) const; // Return background color depending on state
		Gradient *getBackgroundGradient(const State state); // Return background gradient depending on state
		// Scroller
		bool isScrollerRound() const; // Return whether scroller has round borders
		float getScrollerBorderWidth() const; // Return scroller border width
		Color getScrollerBorderColor(const State state) const; // Return scroller border color depending on state
		Color getScrollerBackgroundColor(const State state) const; // Return scroller background color depending on state
		Gradient *getScrollerBackgroundGradient(const State state); // Return scroller background gradient depending on state

		bool setScrollInterval(const float value); // Set scroll interval(in seconds)
		// Shadow
		bool setShadowRadius(const State state, const int value); // Set shadow blur radius depending on state
		bool setShadowShift(const State state, const PointF &value); // Set shadow shift depending on state
		bool setShadowColor(const State state, const Color &value); // Set shadow color depending on state
		// Background
		bool setBorderRound(const bool value); // Set whether border has round borders
		bool setBorderWidth(const float value); // Set borders width
		bool setBorderColor(const State state, const Color &value); // Set borders color depending on state
		bool setBackgroundColor(const State state, const Color &value); // Set background color depending on state
		// Scroller
		bool setScrollerRound(const bool value); // Set whether scroller has round borders
		bool setScrollerBorderWidth(const float value); // Set scroller borders width
		bool setScrollerBorderColor(const State state, const Color &value); // Set scroller borders color depending on state
		bool setScrollerBackgroundColor(const State state, const Color &value); // Set scroller background color depending on state

		bool setShadowRadius(const int value); // Set shadow blur radius for all states
		bool setShadowShift(const PointF &value); // Set shadow shift for all states
		bool setShadowColor(const Color &value); // Set shadow color for all states
		bool setBorderColor(const Color &value); // Set borders color for all states
		bool setBackgroundColor(const Color &value); // Set background color for all states
		bool setScrollerBorderColor(const Color &value); // Set scroller borders color for all states
		bool setScrollerBackgroundColor(const Color &value); // Set scroller background color for all states

		void SwitchDirection(const bool size); // Vertical become horizontal and wise versa
	};
}
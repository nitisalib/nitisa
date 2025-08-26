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
#include "../../Core/DateTime.h"
#include "../../Core/Key.h"
#include "../../Core/Strings.h"
#include "../../Core/TextAlign.h"
#include "../../Core/VerticalAlign.h"
#include "../../Image/BorderColor.h"
#include "../../Image/Color.h"
#include "../../Image/Gradient.h"
#include "../../Interfaces/IFeedbackListener.h"
#include "../../Interfaces/ITimerListener.h"
#include "../../Math/Mat4f.h"
#include "../../Math/PointF.h"
#include "../../Math/RectF.h"
#include "../IBuiltInMonthCalendar.h"
#include <chrono>

namespace nitisa
{
	class IBuiltInControlListener;
	class IFont;
	class IPlatformFont;
	class IRenderer;
	class IStyle;
	class ITexture;

	struct Block;

	class CBuiltInMonthCalendar :public virtual IBuiltInMonthCalendar, public CBuiltInControl
	{
	public:
		enum class Mode // Control modes
		{
			Month, // Month is shown
			Year, // Year is shown(list of months)
			Decade, // Decade is shown(list of years)
			Century // Century is shown(list of 10-year intervals)
		};

		enum class ElementState // Element states
		{
			Normal, // Normal
			Hovered, // Mouse pointer is over an element
			Today, // Element corresponds to today date
			TodayHovered, // Element corresponds to today date and mouse pointer is over it
			Active, // Element corresponds to active date
			ActiveHovered, // Element corresponds to active date and mouse pointer is over it
			TodayActive, // Element corresponds to today and to active date as well
			TodayActiveHovered, // Element corresponds to today and to active date as well and mouse pointer is over it
			OtherRange, // Element is another range(previous or next month/decade/century)
			OtherRangeHovered, // Element is another range(previous or next month/decade/century) and mouse pointer is over it
			Disabled // Element is disabled(either because of the control is disabled or the element is out of allowed date range)
		};

		enum class TitleState // Title and today links states
		{
			Normal, // Normal
			Hovered, // Mouse pointer is over the element
			Active, // Mouse pointer was down over an element
			ActiveHovered, // Mouse pointer was down over an element and mouse pointer is over it
			Disabled // Disabled
		};

		enum class DayTitleState // Day title states
		{
			Normal, // Normal
			Disabled // Disabled
		};
	private:
		enum class ElementType
		{
			None,
			Title,
			Next,
			Prev,
			Today,
			Day,
			Month,
			Year,
			Decade
		};

		enum class AnimateType
		{
			SlideLeft,
			SlideRight,
			Fade
		};

		struct Info
		{
			float LineHeight;
			PointF TitleSize;
			PointF DaySize;
			PointF DaysSize;
			PointF ElementSize;
			PointF ElementsSize;
			PointF TodaySize;
			PointF Size;
			IRenderer *Renderer;
			IPlatformFont *PlatformFont;
			IFont *Font;
			float Distance;
		};

		class CTimerListener :public virtual ITimerListener
		{
		public:
			CBuiltInMonthCalendar *m_pControl;
		public:
			void NotifyOnTimer(const PlatformHandle id) override;

			CTimerListener(CBuiltInMonthCalendar *control);
		};

		class CGradientListener :public virtual IFeedbackListener
		{
		private:
			CBuiltInMonthCalendar *m_pControl;
		public:
			void NotifyOnChange() override;

			CGradientListener(CBuiltInMonthCalendar *control);
		};
	private:
		CGradientListener m_cGradientListener;
		// Interface
		CDateTime m_cDate;
		CDateTime m_cMinDate;
		CDateTime m_cMaxDate;
		// General
		Mode m_eMode;
		bool m_bShowToday;
		RectF m_sTitlePadding;
		RectF m_sTodayPadding;
		float m_fTodayMargin; // Distance between rectangle and text
		float m_fTodayRectWidth;
		RectF m_sElementPadding;
		RectF m_sDayPadding;
		// Animation
		bool m_bAnimate;
		float m_fAnimateInterval;
		float m_fAnimateMinScale; // [0..1). When scaling reaches this value, animation stops
		float m_fAnimateTime; // How long animation should take
		float m_fScrollInterval;
		// Title
		TextAlign m_aTitleAlign[(int)TitleState::Disabled + 1];
		RectF m_aTitleBorderRadius[(int)TitleState::Disabled + 1];
		RectF m_aTitleBorderWidth[(int)TitleState::Disabled + 1];
		BorderColor m_aTitleBorderColor[(int)TitleState::Disabled + 1];
		Color m_aTitleBackgroundColor[(int)TitleState::Disabled + 1];
		Gradient m_aTitleBackgroundGradient[(int)TitleState::Disabled + 1];
		Color m_aTitleColor[(int)TitleState::Disabled + 1];
		RectF m_aTitlePrevRangeBorderRadius[(int)TitleState::Disabled + 1];
		RectF m_aTitlePrevRangeBorderWidth[(int)TitleState::Disabled + 1];
		BorderColor m_aTitlePrevRangeBorderColor[(int)TitleState::Disabled + 1];
		Color m_aTitlePrevRangeBackgroundColor[(int)TitleState::Disabled + 1];
		Gradient m_aTitlePrevRangeBackgroundGradient[(int)TitleState::Disabled + 1];
		RectF m_aTitlePrevRangePadding[(int)TitleState::Disabled + 1];
		Color m_aTitlePrevRangeColor1[(int)TitleState::Disabled + 1];
		Color m_aTitlePrevRangeColor2[(int)TitleState::Disabled + 1];
		Color m_aTitlePrevRangeColor3[(int)TitleState::Disabled + 1];
		RectF m_aTitleNextRangeBorderRadius[(int)TitleState::Disabled + 1];
		RectF m_aTitleNextRangeBorderWidth[(int)TitleState::Disabled + 1];
		BorderColor m_aTitleNextRangeBorderColor[(int)TitleState::Disabled + 1];
		Color m_aTitleNextRangeBackgroundColor[(int)TitleState::Disabled + 1];
		Gradient m_aTitleNextRangeBackgroundGradient[(int)TitleState::Disabled + 1];
		RectF m_aTitleNextRangePadding[(int)TitleState::Disabled + 1];
		Color m_aTitleNextRangeColor1[(int)TitleState::Disabled + 1];
		Color m_aTitleNextRangeColor2[(int)TitleState::Disabled + 1];
		Color m_aTitleNextRangeColor3[(int)TitleState::Disabled + 1];
		// Today link
		TextAlign m_aTodayAlign[(int)TitleState::Disabled + 1];
		RectF m_aTodayBorderRadius[(int)TitleState::Disabled + 1];
		RectF m_aTodayBorderWidth[(int)TitleState::Disabled + 1];
		BorderColor m_aTodayBorderColor[(int)TitleState::Disabled + 1];
		Color m_aTodayBackgroundColor[(int)TitleState::Disabled + 1];
		Gradient m_aTodayBackgroundGradient[(int)TitleState::Disabled + 1];
		Color m_aTodayColor[(int)TitleState::Disabled + 1];
		RectF m_aTodayRectBorderRadius[(int)TitleState::Disabled + 1];
		RectF m_aTodayRectBorderWidth[(int)TitleState::Disabled + 1];
		BorderColor m_aTodayRectBorderColor[(int)TitleState::Disabled + 1];
		Color m_aTodayRectBackgroundColor[(int)TitleState::Disabled + 1];
		Gradient m_aTodayRectBackgroundGradient[(int)TitleState::Disabled + 1];
		// Elements
		TextAlign m_aElementHorizontalAlign[(int)ElementState::Disabled + 1];
		VerticalAlign m_aElementVerticalAlign[(int)ElementState::Disabled + 1];
		RectF m_aElementBorderRadius[(int)ElementState::Disabled + 1];
		RectF m_aElementBorderWidth[(int)ElementState::Disabled + 1];
		BorderColor m_aElementBorderColor[(int)ElementState::Disabled + 1];
		Color m_aElementBackgroundColor[(int)ElementState::Disabled + 1];
		Gradient m_aElementBackgroundGradient[(int)ElementState::Disabled + 1];
		Color m_aElementColor[(int)ElementState::Disabled + 1];
		Color m_aElementOutlineColor[(int)ElementState::Disabled + 1];
		unsigned int m_aElementOutlineMask[(int)ElementState::Disabled + 1];
		TextAlign m_aDayHorizontalAlign[(int)ElementState::Disabled + 1];
		VerticalAlign m_aDayVerticalAlign[(int)ElementState::Disabled + 1];
		// Day title
		TextAlign m_aDayTitleHorizontalAlign[(int)DayTitleState::Disabled + 1];
		VerticalAlign m_aDayTitleVerticalAlign[(int)DayTitleState::Disabled + 1];
		RectF m_aDayTitleBorderRadius[(int)DayTitleState::Disabled + 1];
		RectF m_aDayTitleBorderWidth[(int)DayTitleState::Disabled + 1];
		BorderColor m_aDayTitleBorderColor[(int)DayTitleState::Disabled + 1];
		Color m_aDayTitleBackgroundColor[(int)DayTitleState::Disabled + 1];
		Gradient m_aDayTitleBackgroundGradient[(int)DayTitleState::Disabled + 1];
		Color m_aDayTitleColor[(int)ElementState::Disabled + 1];

		IBuiltInControlListener *m_pListener;
		ITexture *m_pCanvas;
		ITexture *m_pCanvas1;
		ITexture *m_pCanvas2;
		PlatformHandle m_hTimerAnimate;
		PlatformHandle m_hTimerScroll;
		bool m_bIgnoreGradient;
		ElementType m_eHoveredElement;
		ElementType m_eDownElement;
		int m_iPageYear;
		int m_iPageMonth;
		AnimateType m_eAnimateType;
		std::chrono::steady_clock::time_point m_sAnimationStart;
		Info m_sInfo;
		int m_iHoveredYear;
		int m_iHoveredMonth;
		int m_iHoveredDay;
		CTimerListener m_cTimerListener;

		bool PrepareRendering();
		bool setDate(const int year, const int month, const int day);
		bool setMinDate(const int year, const int month, const int day);
		bool setMaxDate(const int year, const int month, const int day);
		bool NextMonth();
		bool NextYear();
		bool NextDecade();
		bool NextCentury();
		bool PrevMonth();
		bool PrevYear();
		bool PrevDecade();
		bool PrevCentury();
		void ChangePage(const int new_year, const int new_month, const AnimateType type);
		void ChangeMode(const Mode old_mode, const Mode new_mode);
		void StopAnimation();
		bool UpdateHoveredItem();
		bool UpdateHoveredItem(const PointF &pos);
		ElementState getDayState(const int year, const int month, const int day);
		ElementState getMonthState(const int year, const int month);
		ElementState getYearState(const int year);
		ElementState getDecadeState(const int year);
		TitleState getPrevRangeState();
		TitleState getNextRangeState();
		TitleState getTitleState();
		TitleState getTodayState();
		DayTitleState getDayTitleState();
		bool CancelDown();

		void RenderAnimation(const Mat4f &matrix, const Block *block);
		void RenderTitle(const int page_year, const int page_month);
		void RenderToday();
		void RenderModeMonth(const int page_year, const int page_month);
		void RenderModeYear(const int page_year);
		void RenderModeDecade(const int page_year);
		void RenderModeCentury(const int page_year);
	public:
		// IBuiltInControl getters
		IBuiltInControlListener * getListener() override;
		bool isDown() override;

		// IBuiltInControl setters
		void setListener(IBuiltInControlListener *value) override;
		bool setSize(const PointF &value) override;
		bool setDPI(const Point &value) override;

		// Helpers
		void UpdateFromStyle(IStyle *style, const String &class_name) override;
		void Update() override;
		void Render(const bool last_pass, const Mat4f &matrix, const Block *block) override;
		void Refresh() override;

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

		// IBuiltInMonthCalendar getters
		PointF getRequiredSize() override;
		int getYear() override;
		int getMonth() override;
		int getDay() override;
		int getMinYear() override; // 1600 by default
		int getMinMonth() override; // January by default
		int getMinDay() override; // 1 by default
		int getMaxYear() override; // 3000 by default
		int getMaxMonth() override; // January by default
		int getMaxDay() override; // 1 by default
		bool isAnimating() override;

		// IBuiltInMonthCalendar setters
		bool setYear(const int value) override;
		bool setMonth(const int value) override;
		bool setDay(const int value) override;
		bool setMinYear(const int value) override;
		bool setMinMonth(const int value) override;
		bool setMinDay(const int value) override;
		bool setMaxYear(const int value) override;
		bool setMaxMonth(const int value) override;
		bool setMaxDay(const int value) override;

		// IBuiltInMonthCalendar methods
		bool Next() override;
		bool Prev() override;
		bool Today() override;

		CBuiltInMonthCalendar();

		// Getters
		Mode getMode() const; // Return mode
		bool isShowToday() const; // Return whether "today is" link should be shown
		RectF getTitlePadding() const; // Return title padding
		RectF getTodayPadding() const; // Return "today" link padding
		RectF getElementPadding() const; // Return elements padding
		RectF getDayPadding() const; // Return days padding
		float getTodayMargin() const; // Return distance between rectangle and text
		float getTodayRectWidth() const; // Return width of "today" link rectangle
		bool isAnimate() const; // Return whether range and modes should be changed with or without animation
		float getAnimateInterval() const; // Return paint interval when animating changes
		float getAnimateMinScale() const; // Return minimum scaling in range [0..1) used in animating mode changes
		float getAnimateTime() const; // Return how long animation should take
		float getScrollInterval() const; // Return range change interval when mouse is down over the next/previous range change arrows
		TextAlign getTitleAlign(const TitleState state) const; // Return title alignment
		RectF getTitleBorderRadius(const TitleState state) const; // Return title corner radii
		RectF getTitleBorderWidth(const TitleState state) const; // Return title border widths
		BorderColor getTitleBorderColor(const TitleState state) const; // Return title border colors
		Color getTitleBackgroundColor(const TitleState state) const; // Return title background color
		Gradient *getTitleBackgroundGradient(const TitleState state); // Return title background gradient
		Color getTitleColor(const TitleState state) const; // Return title color
		RectF getTitlePrevRangeBorderRadius(const TitleState state) const; // Return previous range button corner radii
		RectF getTitlePrevRangeBorderWidth(const TitleState state) const; // Return previous range button border widths
		BorderColor getTitlePrevRangeBorderColor(const TitleState state) const; // Return previous range button border colors
		Color getTitlePrevRangeBackgroundColor(const TitleState state) const; // Return previous range button background color
		Gradient *getTitlePrevRangeBackgroundGradient(const TitleState state); // Return previous range button background gradient
		RectF getTitlePrevRangePadding(const TitleState state) const; // Return previous range button arrow padding
		Color getTitlePrevRangeColor1(const TitleState state) const; // Return previous range button arrow first point color
		Color getTitlePrevRangeColor2(const TitleState state) const; // Return previous range button arrow second point color
		Color getTitlePrevRangeColor3(const TitleState state) const; // Return previous range button arrow third point color
		RectF getTitleNextRangeBorderRadius(const TitleState state) const; // Return next range button corner radii
		RectF getTitleNextRangeBorderWidth(const TitleState state) const; // Return next range button border widths
		BorderColor getTitleNextRangeBorderColor(const TitleState state) const; // Return next range button border colors
		Color getTitleNextRangeBackgroundColor(const TitleState state) const; // Return next range button background color
		Gradient *getTitleNextRangeBackgroundGradient(const TitleState state); // Return next range button background gradient
		RectF getTitleNextRangePadding(const TitleState state) const; // Return next range button arrow padding
		Color getTitleNextRangeColor1(const TitleState state) const; // Return next range button arrow first point color
		Color getTitleNextRangeColor2(const TitleState state) const; // Return next range button arrow second point color
		Color getTitleNextRangeColor3(const TitleState state) const; // Return next range button arrow third point color
		TextAlign getTodayAlign(const TitleState state) const; // Return "today" link text align
		RectF getTodayBorderRadius(const TitleState state) const; // Return "today" link corner radii
		RectF getTodayBorderWidth(const TitleState state) const; // Return "today" link border widths
		BorderColor getTodayBorderColor(const TitleState state) const; // Return "today" link border colors
		Color getTodayBackgroundColor(const TitleState state) const; // Return "today" link background color
		Gradient *getTodayBackgroundGradient(const TitleState state); // Return "today" link background gradient
		Color getTodayColor(const TitleState state) const; // Return "today" link text color
		RectF getTodayRectBorderRadius(const TitleState state) const; // Return "today" link rectangle corner radii
		RectF getTodayRectBorderWidth(const TitleState state) const; // Return "today" link rectangle border widths
		BorderColor getTodayRectBorderColor(const TitleState state) const; // Return "today" link rectangle border colors
		Color getTodayRectBackgroundColor(const TitleState state) const; // Return "today" link rectangle background color
		Gradient *getTodayRectBackgroundGradient(const TitleState state); // Return "today" link rectangle background gradient
		TextAlign getElementHorizontalAlign(const ElementState state) const; // Return element horizontal alignment
		VerticalAlign getElementVerticalAlign(const ElementState state) const; // Return element vertical alignment
		RectF getElementBorderRadius(const ElementState state) const; // Return element corner radii
		RectF getElementBorderWidth(const ElementState state) const; // Return element border widths
		BorderColor getElementBorderColor(const ElementState state) const; // Return element border colors
		Color getElementBackgroundColor(const ElementState state) const; // Return element background color
		Gradient *getElementBackgroundGradient(const ElementState state); // Return element background gradient
		Color getElementColor(const ElementState state) const; // Return element text color
		Color getElementOutlineColor(const ElementState state) const; // Return element outline color
		unsigned int getElementOutlineMask(const ElementState state) const; // Return element outline mask
		TextAlign getDayHorizontalAlign(const ElementState state) const; // Return day horizontal alignment
		VerticalAlign getDayVerticalAlign(const ElementState state) const; // Return day vertical alignment
		TextAlign getDayTitleHorizontalAlign(const DayTitleState state) const; // Return day title horizontal alignment
		VerticalAlign getDayTitleVerticalAlign(const DayTitleState state) const; // Return day title vertical alignment
		RectF getDayTitleBorderRadius(const DayTitleState state) const; // Return day title corner radii
		RectF getDayTitleBorderWidth(const DayTitleState state) const; // Return day title border widths
		BorderColor getDayTitleBorderColor(const DayTitleState state) const; // Return day title border colors
		Color getDayTitleBackgroundColor(const DayTitleState state) const; // Return day title background color
		Gradient *getDayTitleBackgroundGradient(const DayTitleState state); // Return day title background gradient
		Color getDayTitleColor(const DayTitleState state) const; // Return day title text color

		// Setters
		bool setMode(const Mode value); // Set mode
		bool setShowToday(const bool value); // Set whether "today is" link should be shown
		bool setTitlePadding(const RectF &value); // Set title padding
		bool setTodayPadding(const RectF &value); // Set "today" link padding
		bool setElementPadding(const RectF &value); // Set elements padding
		bool setDayPadding(const RectF &value); // Set days padding
		bool setTodayMargin(const float value); // Set distance between rectangle and text
		bool setTodayRectWidth(const float value); // Set width of "today" link rectangle
		bool setAnimate(const bool value); // Set whether range and modes should be changed with or without animation
		bool setAnimateInterval(const float value); // Set paint interval when animating changes
		bool setAnimateMinScale(const float value); // Set minimum scaling in range [0..1) used in animating mode changes
		bool setAnimateTime(const float value); // Set how long animation should take
		bool setScrollInterval(const float value); // Set range change interval when mouse is down over the next/previous range change arrows
		bool setTitleAlign(const TitleState state, const TextAlign value); // Set title alignment
		bool setTitleBorderRadius(const TitleState state, const RectF &value); // Set title corner radii
		bool setTitleBorderWidth(const TitleState state, const RectF &value); // Set title border widths
		bool setTitleBorderColor(const TitleState state, const BorderColor &value); // Set title border colors
		bool setTitleBackgroundColor(const TitleState state, const Color &value); // Set title background color
		bool setTitleColor(const TitleState state, const Color &value); // Set title color
		bool setTitlePrevRangeBorderRadius(const TitleState state, const RectF &value); // Set previous range button corner radii
		bool setTitlePrevRangeBorderWidth(const TitleState state, const RectF &value); // Set previous range button border widths
		bool setTitlePrevRangeBorderColor(const TitleState state, const BorderColor &value); // Set previous range button border colors
		bool setTitlePrevRangeBackgroundColor(const TitleState state, const Color &value); // Set previous range button background color
		bool setTitlePrevRangePadding(const TitleState state, const RectF &value); // Set previous range button arrow padding
		bool setTitlePrevRangeColor1(const TitleState state, const Color &value); // Set previous range button arrow first point color
		bool setTitlePrevRangeColor2(const TitleState state, const Color &value); // Set previous range button arrow second point color
		bool setTitlePrevRangeColor3(const TitleState state, const Color &value); // Set previous range button arrow third point color
		bool setTitleNextRangeBorderRadius(const TitleState state, const RectF &value); // Set next range button corner radii
		bool setTitleNextRangeBorderWidth(const TitleState state, const RectF &value); // Set next range button border widths
		bool setTitleNextRangeBorderColor(const TitleState state, const BorderColor &value); // Set next range button border colors
		bool setTitleNextRangeBackgroundColor(const TitleState state, const Color &value); // Set next range button background color
		bool setTitleNextRangePadding(const TitleState state, const RectF &value); // Set next range button arrow padding
		bool setTitleNextRangeColor1(const TitleState state, const Color &value); // Set next range button arrow first point color
		bool setTitleNextRangeColor2(const TitleState state, const Color &value); // Set next range button arrow second point color
		bool setTitleNextRangeColor3(const TitleState state, const Color &value); // Set next range button arrow third point color
		bool setTodayAlign(const TitleState state, const TextAlign value); // Set "today" link text align
		bool setTodayBorderRadius(const TitleState state, const RectF &value); // Set "today" link corner radii
		bool setTodayBorderWidth(const TitleState state, const RectF &value); // Set "today" link border widths
		bool setTodayBorderColor(const TitleState state, const BorderColor &value); // Set "today" link border colors
		bool setTodayBackgroundColor(const TitleState state, const Color &value); // Set "today" link background color
		bool setTodayColor(const TitleState state, const Color &value); // Set "today" link text color
		bool setTodayRectBorderRadius(const TitleState state, const RectF &value); // Set "today" link rectangle corner radii
		bool setTodayRectBorderWidth(const TitleState state, const RectF &value); // Set "today" link rectangle border widths
		bool setTodayRectBorderColor(const TitleState state, const BorderColor &value); // Set "today" link rectangle border colors
		bool setTodayRectBackgroundColor(const TitleState state, const Color &value); // Set "today" link rectangle background color
		bool setElementHorizontalAlign(const ElementState state, const TextAlign value); // Set element horizontal alignment
		bool setElementVerticalAlign(const ElementState state, const VerticalAlign value); // Set element vertical alignment
		bool setElementBorderRadius(const ElementState state, const RectF &value); // Set element corner radii
		bool setElementBorderWidth(const ElementState state, const RectF &value); // Set element border widths
		bool setElementBorderColor(const ElementState state, const BorderColor &value); // Set element border colors
		bool setElementBackgroundColor(const ElementState state, const Color &value); // Set element background color
		bool setElementColor(const ElementState state, const Color &value); // Set element text color
		bool setElementOutlineColor(const ElementState state, const Color &value); // Set element outline color
		bool setElementOutlineMask(const ElementState state, const unsigned int value); // Set element outline mask
		bool setDayHorizontalAlign(const ElementState state, const TextAlign value); // Set day horizontal alignment
		bool setDayVerticalAlign(const ElementState state, const VerticalAlign value); // Set day vertical alignment
		bool setDayTitleHorizontalAlign(const DayTitleState state, const TextAlign value); // Set day title horizontal alignment
		bool setDayTitleVerticalAlign(const DayTitleState state, const VerticalAlign value); // Set day title vertical alignment
		bool setDayTitleBorderRadius(const DayTitleState state, const RectF &value); // Set day title corner radii
		bool setDayTitleBorderWidth(const DayTitleState state, const RectF &value); // Set day title border widths
		bool setDayTitleBorderColor(const DayTitleState state, const BorderColor &value); // Set day title border colors
		bool setDayTitleBackgroundColor(const DayTitleState state, const Color &value); // Set day title background color
		bool setDayTitleColor(const DayTitleState state, const Color &value); // Set day title text color
	};
}
// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h"
#include "Nitisa/BuiltInControls/IBuiltInMonthCalendarListener.h"
#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/TextAlign.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Image/Image.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Interfaces/ITimerListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IDatePicker.h"

namespace nitisa
{
	class IBuiltInControl;
	class IBuiltInMonthCalendar;
	class IControl;
	class IForm;
	class IPlatformFont;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class IImageList;

		class CDatePickerService;

		class CDatePicker :public virtual IDatePicker, public CControl
		{
			friend CDatePickerService;
		public:
			enum class State // Control and elements states
			{
				Normal, // Normal
				Hovered, // Mouse pointer is over the control/element
				Focused, // Control is focused
				FocusedHovered, // Control is focused and mouse pointer is over it
				Active, // Mouse button is down on one of the arrows
				ActiveHovered, // Mouse button is down on one of the arrows and mouse pointer is over the control(or arrow if the state relates to arrow)
				Disabled // Disabled
			};

			enum class DisplayMode // Display mode
			{
				DropDown, // Has a month calendar which could be shown by clicking on coresponding area or pressing F4 key
				UpDown, // Has up and down arrows used to increase and decrese active element(year/month/day) value
				Simple // Has neither up+down arrows no month calendar
			};

			enum class MonthFormat // Month format
			{
				Short, // Show month number(1..12)
				Medium, // Show month short name(like, Jan)
				Long // Show month full name(like January)
			};

			enum class ElementOrder // Element order
			{
				DayMonthYear, // Day, month, year
				DayYearMonth, // Day, year, month
				MonthDayYear, // Month, day, year
				MonthYearDay, // Month, year, day
				YearDayMonth, // Year, day, month
				YearMonthDay // Year, month, day
			};

			enum class OpenDirection // Where month calendar should appear
			{
				Auto, // At the bottom of the control by default but if it is too close to the form bottom it will appear above the control. Works only if there are not rotations in control hierarchy
				Up, // Appear above the control
				Down // Appear under the control
			};

			enum class OpenAlign // How month calendar should be horizontally aligned relative to the control
			{
				Left, // Aligned to the left
				Right, // Aligned to the right
				Center, // Aligned to center
				Justify // Month calendar should have the same width as control(if possible)
			};
		private:
			enum class Element
			{
				None,
				Years,
				Months,
				Days,
				UpArrow,
				DownArrow,
				Arrow,
				Calendar
			};

			class CBuiltIn :public CBuiltInMonthCalendar
			{
			private:
				CDatePicker * m_pControl;
			public:
				IControl * getControl() override;

				CBuiltIn(CDatePicker *control);
			};

			class CListener :public virtual IBuiltInMonthCalendarListener
			{
			private:
				CDatePicker * m_pControl;
			public:
				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnChange(IBuiltInControl *sender) override;

				CListener(CDatePicker *control);
			};

			class CTimerListener :public virtual ITimerListener
			{
			private:
				CDatePicker *m_pControl;
			public:
				void NotifyOnTimer(const PlatformHandle id) override;

				CTimerListener(CDatePicker *control);
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CDatePicker *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CDatePicker *control);
			};

			struct CONTENT
			{
				float LineHeight;
				RectF Rect;
				String ContentDay;
				String ContentMonth;
				String ContentYear;
				PointF Days;
				PointF Months;
				PointF Years;
				PointF Separator1;
				PointF Separator2;
			};
		private:
			CGradientListener m_cGradientListener;
			DisplayMode m_eDisplayMode;
			MonthFormat m_eMonthFormat;
			ElementOrder m_eElementOrder;
			OpenDirection m_eOpenDirection;
			OpenAlign m_eOpenAlign;
			String m_sSeparator1;
			String m_sSeparator2;
			bool m_bShowDayLeadingZeros;
			bool m_bShowMonthLeadingZeros;
			bool m_bShowYearLeadingZeros;
			bool m_bShowIcon;
			float m_fTimerInterval;
			TextAlign m_eContentAlign;
			bool m_bArrowsAtRight;
			// Control background
			int m_aShadowRadius[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];
			Color m_aShadowColor[(int)State::Disabled + 1];
			RectF m_aBorderRadius[(int)State::Disabled + 1];
			RectF m_aOuterBorderWidth[(int)State::Disabled + 1];
			BorderColor m_aOuterBorderColor[(int)State::Disabled + 1];
			RectF m_aInnerBorderWidth[(int)State::Disabled + 1];
			BorderColor m_aInnerBorderColor[(int)State::Disabled + 1];
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
			// UpDown's Up arrow
			RectF m_aUpArrowBorderRadius[(int)State::Disabled + 1];
			RectF m_aUpArrowOuterBorderWidth[(int)State::Disabled + 1];
			RectF m_aUpArrowInnerBorderWidth[(int)State::Disabled + 1];
			BorderColor m_aUpArrowOuterBorderColor[(int)State::Disabled + 1];
			BorderColor m_aUpArrowInnerBorderColor[(int)State::Disabled + 1];
			Color m_aUpArrowBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aUpArrowBackgroundGradient[(int)State::Disabled + 1];
			RectF m_aUpArrowPadding[(int)State::Disabled + 1];
			Color m_aUpArrowColor1[(int)State::Disabled + 1];
			Color m_aUpArrowColor2[(int)State::Disabled + 1];
			Color m_aUpArrowColor3[(int)State::Disabled + 1];
			// UpDown's Down arrow
			RectF m_aDownArrowBorderRadius[(int)State::Disabled + 1];
			RectF m_aDownArrowOuterBorderWidth[(int)State::Disabled + 1];
			RectF m_aDownArrowInnerBorderWidth[(int)State::Disabled + 1];
			BorderColor m_aDownArrowOuterBorderColor[(int)State::Disabled + 1];
			BorderColor m_aDownArrowInnerBorderColor[(int)State::Disabled + 1];
			Color m_aDownArrowBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aDownArrowBackgroundGradient[(int)State::Disabled + 1];
			RectF m_aDownArrowPadding[(int)State::Disabled + 1];
			Color m_aDownArrowColor1[(int)State::Disabled + 1];
			Color m_aDownArrowColor2[(int)State::Disabled + 1];
			Color m_aDownArrowColor3[(int)State::Disabled + 1];
			float m_aArrowDistance[(int)State::Disabled + 1];
			// DropDown's arrow
			RectF m_aArrowBorderRadius[(int)State::Disabled + 1];
			RectF m_aArrowOuterBorderWidth[(int)State::Disabled + 1];
			RectF m_aArrowInnerBorderWidth[(int)State::Disabled + 1];
			BorderColor m_aArrowOuterBorderColor[(int)State::Disabled + 1];
			BorderColor m_aArrowInnerBorderColor[(int)State::Disabled + 1];
			Color m_aArrowBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aArrowBackgroundGradient[(int)State::Disabled + 1];
			RectF m_aArrowPadding[(int)State::Disabled + 1];
			Color m_aArrowColor1[(int)State::Disabled + 1];
			Color m_aArrowColor2[(int)State::Disabled + 1];
			Color m_aArrowColor3[(int)State::Disabled + 1];
			// DropDown's icon
			IImageList *m_pImageList;
			int m_aIconIndex[(int)State::Disabled + 1];
			RectF m_aIconPadding[(int)State::Disabled + 1];
			// Element
			Color m_aElementBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aElementBackgroundGradient[(int)State::Disabled + 1];
			Color m_aElementColor[(int)State::Disabled + 1];
			float m_aElementPadding[(int)State::Disabled + 1]; // Between elements and arrows
			// Calendar
			float m_fCalendarMargin;
			RectF m_sCalendarOuterBorderWidth;
			RectF m_sCalendarInnerBorderWidth;
			RectF m_sCalendarPadding;
			int m_iCalendarShadowRadius;
			PointF m_sCalendarShadowShift;
			Color m_sCalendarShadowColor;
			RectF m_sCalendarBorderRadius;
			BorderColor m_sCalendarOuterBorderColor;
			BorderColor m_sCalendarInnerBorderColor;
			Color m_sCalendarBackgroundColor;
			Gradient m_cCalendarBackgroundGradient;

			ITexture *m_pCanvas;
			ITexture *m_pCanvasCalendar;
			bool m_bIgnoreGradient;
			Element m_eActiveElement;
			Element m_eHoveredElement;
			Element m_eDownElement;
			IBuiltInMonthCalendar *m_pMonthCalendar;
			CListener m_cListener;
			PlatformHandle m_hTimer;
			bool m_bOpened;
			RectF m_sCalendarRect;
			bool m_bFirstDigit;
			CTimerListener m_cTimerListener;

			static const Image m_cIcon;

			void UpdateFromStyle(IStyle *style);
			IBuiltInMonthCalendar *getMonthCalendar();
			bool UpdateHoveredElement();
			bool UpdateHoveredElement(const PointF &pos);
			RectF getArrowsRect(const State state);
			RectF getUpArrowRect(const RectF &rect, const State state);
			RectF getDownArrowRect(const RectF &rect, const State state);
			RectF getArrowRect(const State state);
			String getContentDay();
			String getContentMonth();
			String getContentYear();
			bool CalculateContent(const State state, IPlatformFont *pf, const float distance, CONTENT &content);
			State getUpArrowState();
			State getDownArrowState();
			State getArrowState();
			State getYearsState();
			State getMonthsState();
			State getDaysState();
			Color CalculateElementColor(const State state);
			RectF CalculateClientRect(const State state);
			Element getNextElement() const;
			Element getPrevElement() const;
			void RenderControl();
			void RenderContent(IRenderer *renderer, const State state, const PointF &disp);
			void RenderArrows(IRenderer *renderer, const State state, const PointF &disp);
			void RenderCalendar();
		public:
			// IControl getters
			IControl * getControl(const int index) override;
			IControl *getControl(const String &name) override;
			IControl *getControl(const PointF &position) override;
			RectF getRenderRect() override;
			bool hasExtra() override;

			// IControl setters
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			// IDatePicker getters
			int getYear() override;
			int getMonth() override;
			int getDay() override;
			int getMinYear() override;
			int getMinMonth() override;
			int getMinDay() override;
			int getMaxYear() override;
			int getMaxMonth() override;
			int getMaxDay() override;

			// IDatePicker setters
			bool setYear(const int value) override;
			bool setMonth(const int value) override;
			bool setDay(const int value) override;
			bool setMinYear(const int value) override;
			bool setMinMonth(const int value) override;
			bool setMinDay(const int value) override;
			bool setMaxYear(const int value) override;
			bool setMaxMonth(const int value) override;
			bool setMaxDay(const int value) override;

			CDatePicker(); // Create
			CDatePicker(IForm *parent); // Create and place on the form
			CDatePicker(IControl *parent); // Create and place on the parent control
			~CDatePicker() override;

			// CBuiltInMonthCalendar getters. Available only if associated IBuiltInMonthCalendar is instance of CBuiltInMonthCalendar(which is true by default)
			CBuiltInMonthCalendar::Mode getCalendarMode();
			bool isCalendarShowToday();
			RectF getCalendarTitlePadding();
			RectF getCalendarTodayPadding();
			RectF getCalendarElementPadding();
			RectF getCalendarDayPadding();
			float getCalendarTodayMargin();
			float getCalendarTodayRectWidth();
			bool isCalendarAnimate();
			float getCalendarAnimateInterval();
			float getCalendarAnimateMinScale();
			float getCalendarAnimateTime();
			float getCalendarScrollInterval();
			TextAlign getCalendarTitleAlign(const CBuiltInMonthCalendar::TitleState state);
			RectF getCalendarTitleBorderRadius(const CBuiltInMonthCalendar::TitleState state);
			RectF getCalendarTitleBorderWidth(const CBuiltInMonthCalendar::TitleState state);
			BorderColor getCalendarTitleBorderColor(const CBuiltInMonthCalendar::TitleState state);
			Color getCalendarTitleBackgroundColor(const CBuiltInMonthCalendar::TitleState state);
			Gradient *getCalendarTitleBackgroundGradient(const CBuiltInMonthCalendar::TitleState state);
			Color getCalendarTitleColor(const CBuiltInMonthCalendar::TitleState state);
			RectF getCalendarTitlePrevRangeBorderRadius(const CBuiltInMonthCalendar::TitleState state);
			RectF getCalendarTitlePrevRangeBorderWidth(const CBuiltInMonthCalendar::TitleState state);
			BorderColor getCalendarTitlePrevRangeBorderColor(const CBuiltInMonthCalendar::TitleState state);
			Color getCalendarTitlePrevRangeBackgroundColor(const CBuiltInMonthCalendar::TitleState state);
			Gradient *getCalendarTitlePrevRangeBackgroundGradient(const CBuiltInMonthCalendar::TitleState state);
			RectF getCalendarTitlePrevRangePadding(const CBuiltInMonthCalendar::TitleState state);
			Color getCalendarTitlePrevRangeColor1(const CBuiltInMonthCalendar::TitleState state);
			Color getCalendarTitlePrevRangeColor2(const CBuiltInMonthCalendar::TitleState state);
			Color getCalendarTitlePrevRangeColor3(const CBuiltInMonthCalendar::TitleState state);
			RectF getCalendarTitleNextRangeBorderRadius(const CBuiltInMonthCalendar::TitleState state);
			RectF getCalendarTitleNextRangeBorderWidth(const CBuiltInMonthCalendar::TitleState state);
			BorderColor getCalendarTitleNextRangeBorderColor(const CBuiltInMonthCalendar::TitleState state);
			Color getCalendarTitleNextRangeBackgroundColor(const CBuiltInMonthCalendar::TitleState state);
			Gradient *getCalendarTitleNextRangeBackgroundGradient(const CBuiltInMonthCalendar::TitleState state);
			RectF getCalendarTitleNextRangePadding(const CBuiltInMonthCalendar::TitleState state);
			Color getCalendarTitleNextRangeColor1(const CBuiltInMonthCalendar::TitleState state);
			Color getCalendarTitleNextRangeColor2(const CBuiltInMonthCalendar::TitleState state);
			Color getCalendarTitleNextRangeColor3(const CBuiltInMonthCalendar::TitleState state);
			TextAlign getCalendarTodayAlign(const CBuiltInMonthCalendar::TitleState state);
			RectF getCalendarTodayBorderRadius(const CBuiltInMonthCalendar::TitleState state);
			RectF getCalendarTodayBorderWidth(const CBuiltInMonthCalendar::TitleState state);
			BorderColor getCalendarTodayBorderColor(const CBuiltInMonthCalendar::TitleState state);
			Color getCalendarTodayBackgroundColor(const CBuiltInMonthCalendar::TitleState state);
			Gradient *getCalendarTodayBackgroundGradient(const CBuiltInMonthCalendar::TitleState state);
			Color getCalendarTodayColor(const CBuiltInMonthCalendar::TitleState state);
			RectF getCalendarTodayRectBorderRadius(const CBuiltInMonthCalendar::TitleState state);
			RectF getCalendarTodayRectBorderWidth(const CBuiltInMonthCalendar::TitleState state);
			BorderColor getCalendarTodayRectBorderColor(const CBuiltInMonthCalendar::TitleState state);
			Color getCalendarTodayRectBackgroundColor(const CBuiltInMonthCalendar::TitleState state);
			Gradient *getCalendarTodayRectBackgroundGradient(const CBuiltInMonthCalendar::TitleState state);
			TextAlign getCalendarElementHorizontalAlign(const CBuiltInMonthCalendar::ElementState state);
			VerticalAlign getCalendarElementVerticalAlign(const CBuiltInMonthCalendar::ElementState state);
			RectF getCalendarElementBorderRadius(const CBuiltInMonthCalendar::ElementState state);
			RectF getCalendarElementBorderWidth(const CBuiltInMonthCalendar::ElementState state);
			BorderColor getCalendarElementBorderColor(const CBuiltInMonthCalendar::ElementState state);
			Color getCalendarElementBackgroundColor(const CBuiltInMonthCalendar::ElementState state);
			Gradient *getCalendarElementBackgroundGradient(const CBuiltInMonthCalendar::ElementState state);
			Color getCalendarElementColor(const CBuiltInMonthCalendar::ElementState state);
			Color getCalendarElementOutlineColor(const CBuiltInMonthCalendar::ElementState state);
			unsigned int getCalendarElementOutlineMask(const CBuiltInMonthCalendar::ElementState state);
			TextAlign getCalendarDayHorizontalAlign(const CBuiltInMonthCalendar::ElementState state);
			VerticalAlign getCalendarDayVerticalAlign(const CBuiltInMonthCalendar::ElementState state);
			TextAlign getCalendarDayTitleHorizontalAlign(const CBuiltInMonthCalendar::DayTitleState state);
			VerticalAlign getCalendarDayTitleVerticalAlign(const CBuiltInMonthCalendar::DayTitleState state);
			RectF getCalendarDayTitleBorderRadius(const CBuiltInMonthCalendar::DayTitleState state);
			RectF getCalendarDayTitleBorderWidth(const CBuiltInMonthCalendar::DayTitleState state);
			BorderColor getCalendarDayTitleBorderColor(const CBuiltInMonthCalendar::DayTitleState state);
			Color getCalendarDayTitleBackgroundColor(const CBuiltInMonthCalendar::DayTitleState state);
			Gradient *getCalendarDayTitleBackgroundGradient(const CBuiltInMonthCalendar::DayTitleState state);
			Color getCalendarDayTitleColor(const CBuiltInMonthCalendar::DayTitleState state);

			// CBuiltInMonthCalendar setters. Available only if associated IBuiltInMonthCalendar is instance of CBuiltInMonthCalendar(which is true by default)
			bool setCalendarMode(const CBuiltInMonthCalendar::Mode value);
			bool setCalendarShowToday(const bool value);
			bool setCalendarTitlePadding(const RectF &value);
			bool setCalendarTodayPadding(const RectF &value);
			bool setCalendarElementPadding(const RectF &value);
			bool setCalendarDayPadding(const RectF &value);
			bool setCalendarTodayMargin(const float value);
			bool setCalendarTodayRectWidth(const float value);
			bool setCalendarAnimate(const bool value);
			bool setCalendarAnimateInterval(const float value);
			bool setCalendarAnimateMinScale(const float value);
			bool setCalendarAnimateTime(const float value);
			bool setCalendarScrollInterval(const float value);
			bool setCalendarTitleAlign(const CBuiltInMonthCalendar::TitleState state, const TextAlign value);
			bool setCalendarTitleBorderRadius(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setCalendarTitleBorderWidth(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setCalendarTitleBorderColor(const CBuiltInMonthCalendar::TitleState state, const BorderColor &value);
			bool setCalendarTitleBackgroundColor(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setCalendarTitleColor(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setCalendarTitlePrevRangeBorderRadius(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setCalendarTitlePrevRangeBorderWidth(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setCalendarTitlePrevRangeBorderColor(const CBuiltInMonthCalendar::TitleState state, const BorderColor &value);
			bool setCalendarTitlePrevRangeBackgroundColor(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setCalendarTitlePrevRangePadding(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setCalendarTitlePrevRangeColor1(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setCalendarTitlePrevRangeColor2(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setCalendarTitlePrevRangeColor3(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setCalendarTitleNextRangeBorderRadius(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setCalendarTitleNextRangeBorderWidth(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setCalendarTitleNextRangeBorderColor(const CBuiltInMonthCalendar::TitleState state, const BorderColor &value);
			bool setCalendarTitleNextRangeBackgroundColor(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setCalendarTitleNextRangePadding(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setCalendarTitleNextRangeColor1(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setCalendarTitleNextRangeColor2(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setCalendarTitleNextRangeColor3(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setCalendarTodayAlign(const CBuiltInMonthCalendar::TitleState state, const TextAlign value);
			bool setCalendarTodayBorderRadius(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setCalendarTodayBorderWidth(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setCalendarTodayBorderColor(const CBuiltInMonthCalendar::TitleState state, const BorderColor &value);
			bool setCalendarTodayBackgroundColor(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setCalendarTodayColor(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setCalendarTodayRectBorderRadius(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setCalendarTodayRectBorderWidth(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setCalendarTodayRectBorderColor(const CBuiltInMonthCalendar::TitleState state, const BorderColor &value);
			bool setCalendarTodayRectBackgroundColor(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setCalendarElementHorizontalAlign(const CBuiltInMonthCalendar::ElementState state, const TextAlign value);
			bool setCalendarElementVerticalAlign(const CBuiltInMonthCalendar::ElementState state, const VerticalAlign value);
			bool setCalendarElementBorderRadius(const CBuiltInMonthCalendar::ElementState state, const RectF &value);
			bool setCalendarElementBorderWidth(const CBuiltInMonthCalendar::ElementState state, const RectF &value);
			bool setCalendarElementBorderColor(const CBuiltInMonthCalendar::ElementState state, const BorderColor &value);
			bool setCalendarElementBackgroundColor(const CBuiltInMonthCalendar::ElementState state, const Color &value);
			bool setCalendarElementColor(const CBuiltInMonthCalendar::ElementState state, const Color &value);
			bool setCalendarElementOutlineColor(const CBuiltInMonthCalendar::ElementState state, const Color &value);
			bool setCalendarElementOutlineMask(const CBuiltInMonthCalendar::ElementState state, const unsigned int value);
			bool setCalendarDayHorizontalAlign(const CBuiltInMonthCalendar::ElementState state, const TextAlign value);
			bool setCalendarDayVerticalAlign(const CBuiltInMonthCalendar::ElementState state, const VerticalAlign value);
			bool setCalendarDayTitleHorizontalAlign(const CBuiltInMonthCalendar::DayTitleState state, const TextAlign value);
			bool setCalendarDayTitleVerticalAlign(const CBuiltInMonthCalendar::DayTitleState state, const VerticalAlign value);
			bool setCalendarDayTitleBorderRadius(const CBuiltInMonthCalendar::DayTitleState state, const RectF &value);
			bool setCalendarDayTitleBorderWidth(const CBuiltInMonthCalendar::DayTitleState state, const RectF &value);
			bool setCalendarDayTitleBorderColor(const CBuiltInMonthCalendar::DayTitleState state, const BorderColor &value);
			bool setCalendarDayTitleBackgroundColor(const CBuiltInMonthCalendar::DayTitleState state, const Color &value);
			bool setCalendarDayTitleColor(const CBuiltInMonthCalendar::DayTitleState state, const Color &value);

			// Getters
			State getState(); // Return control state
			DisplayMode getDisplayMode() const; // Return display format
			MonthFormat getMonthFormat() const; // Return month format
			ElementOrder getElementOrder() const; // Return element order
			OpenDirection getOpenDirection() const; // Return month calendar appear direction
			OpenAlign getOpenAlign() const; // Return month calendar horizontal alignment
			String getSeparator1() const; // Return separator value between first and second elements
			String getSeparator2() const; // Return separator value between second and third elements
			bool isShowDayLeadingZeros() const; // Return whether day should have leading zero if day is less than 10
			bool isShowMonthLeadingZeros() const; // Return whether month should have leading zero if month is less than 10(works in mfShort month format mode only)
			bool isShowYearLeadingZeros() const; // Return whether year should have leading zero if year is less than 1000
			bool isShowIcon() const; // Return whether icon should be shown near the down arrow in dmDropDown display mode
			float getTimerInterval() const; // Return update interval when mouse is down over an up or down arrow
			bool isArrowsAtRight() const; // Return whether arrows at the control right or left side
			TextAlign getContentAlign() const; // Return time horizontal alignment inside control area
			int getShadowRadius(const State state) const; // Return control shadow radius. "state" is the control state
			PointF getShadowShift(const State state) const; // Return control shadow shift. "state" is the control state
			Color getShadowColor(const State state) const; // Return control shadow color. "state" is the control state
			RectF getBorderRadius(const State state) const; // Return control corner radiuses. "state" is the control state
			RectF getOuterBorderWidth(const State state) const; // Return control outer border widths. "state" is the control state
			BorderColor getOuterBorderColor(const State state) const; // Return control outer border colors. "state" is the control state
			RectF getInnerBorderWidth(const State state) const; // Return control inner border widths. "state" is the control state
			BorderColor getInnerBorderColor(const State state) const; // Return control inner border colors. "state" is the control state
			Color getBackgroundColor(const State state) const; // Return control background color. "state" is the control state
			Gradient *getBackgroundGradient(const State state); // Return control background gradient. "state" is the control state
			RectF getUpArrowBorderRadius(const State state) const; // Return up-arrow area corner radiuses. "state" is the arrow state. Used in up-down mode only
			RectF getUpArrowOuterBorderWidth(const State state) const; // Return up-arrow area outer border widths. "state" is the arrow state. Used in up-down mode only
			RectF getUpArrowInnerBorderWidth(const State state) const; // Return up-arrow area inner border widths. "state" is the arrow state. Used in up-down mode only
			BorderColor getUpArrowOuterBorderColor(const State state) const; // Return up-arrow area outer border colors. "state" is the arrow state. Used in up-down mode only
			BorderColor getUpArrowInnerBorderColor(const State state) const; // Return up-arrow area inner border colors. "state" is the arrow state. Used in up-down mode only
			Color getUpArrowBackgroundColor(const State state) const; // Return up-arrow area background color. "state" is the arrow state. Used in up-down mode only
			Gradient *getUpArrowBackgroundGradient(const State state); // Return up-arrow area background gradient. "state" is the arrow state. Used in up-down mode only
			RectF getUpArrowPadding(const State state) const; // Return up-arrow area padding. "state" is the arrow state. Used in up-down mode only
			Color getUpArrowColor1(const State state) const; // Return up-arrow first point color. "state" is the arrow state. Used in up-down mode only
			Color getUpArrowColor2(const State state) const; // Return up-arrow second point color. "state" is the arrow state. Used in up-down mode only
			Color getUpArrowColor3(const State state) const; // Return up-arrow third point color. "state" is the arrow state. Used in up-down mode only
			RectF getDownArrowBorderRadius(const State state) const; // Return down-arrow area corner radiuses. "state" is the arrow state. Used in up-down mode only
			RectF getDownArrowOuterBorderWidth(const State state) const; // Return down-arrow area outer border widths. "state" is the arrow state. Used in up-down mode only
			RectF getDownArrowInnerBorderWidth(const State state) const; // Return down-arrow area inner border widths. "state" is the arrow state. Used in up-down mode only
			BorderColor getDownArrowOuterBorderColor(const State state) const; // Return down-arrow area outer border colors. "state" is the arrow state. Used in up-down mode only
			BorderColor getDownArrowInnerBorderColor(const State state) const; // Return down-arrow area inner border colors. "state" is the arrow state. Used in up-down mode only
			Color getDownArrowBackgroundColor(const State state) const; // Return down-arrow area background color. "state" is the arrow state. Used in up-down mode only
			Gradient *getDownArrowBackgroundGradient(const State state); // Return down-arrow area background gradient. "state" is the arrow state. Used in up-down mode only
			RectF getDownArrowPadding(const State state) const; // Return down-arrow area padding. "state" is the arrow state. Used in up-down mode only
			Color getDownArrowColor1(const State state) const; // Return down-arrow first point color. "state" is the arrow state. Used in up-down mode only
			Color getDownArrowColor2(const State state) const; // Return down-arrow second point color. "state" is the arrow state. Used in up-down mode only
			Color getDownArrowColor3(const State state) const; // Return down-arrow third point color. "state" is the arrow state. Used in up-down mode only
			float getArrowDistance(const State state) const; // Return distance between up and down arrows. "state" is the control state. Used in up-down mode only
			RectF getArrowBorderRadius(const State state) const; // Return arrow area corner radiuses. "state" is the arrow state. Used in drop-down mode only
			RectF getArrowOuterBorderWidth(const State state) const; // Return arrow area outer border widths. "state" is the arrow state. Used in drop-down mode only
			RectF getArrowInnerBorderWidth(const State state) const; // Return arrow area inner border widths. "state" is the arrow state. Used in drop-down mode only
			BorderColor getArrowOuterBorderColor(const State state) const; // Return arrow area outer border colors. "state" is the arrow state. Used in drop-down mode only
			BorderColor getArrowInnerBorderColor(const State state) const; // Return arrow area inner border colors. "state" is the arrow state. Used in drop-down mode only
			Color getArrowBackgroundColor(const State state) const; // Return arrow area background color. "state" is the arrow state. Used in drop-down mode only
			Gradient *getArrowBackgroundGradient(const State state); // Return arrow area background gradient. "state" is the arrow state. Used in drop-down mode only
			RectF getArrowPadding(const State state) const; // Return arrow area padding. "state" is the arrow state. Used in drop-down mode only
			Color getArrowColor1(const State state) const; // Return arrow first point color. "state" is the arrow state. Used in drop-down mode only
			Color getArrowColor2(const State state) const; // Return arrow second point color. "state" is the arrow state. Used in drop-down mode only
			Color getArrowColor3(const State state) const; // Return arrow third point color. "state" is the arrow state. Used in drop-down mode only
			IImageList *getImageList(); // Return assocciated image list which is a source of custom icon
			int getIconIndex(const State state) const; // Return icon index
			RectF getIconPadding(const State state) const; // Return icon padding
			Color getElementBackgroundColor(const State state) const; // Return element(years, months, days) background color. "state" is the element state
			Gradient *getElementBackgroundGradient(const State state); // Return element(years, months, days) background gradient. "state" is the element state
			Color getElementColor(const State state) const; // Return element(years, months, days) text color. "state" is the element state
			float getElementPadding(const State state) const; // Return distance between borders/arrows and content. "state" is the control state
			float getCalendarMargin() const; // Return month calendar vertical distance to the control
			RectF getCalendarOuterBorderWidth() const; // Return month calendar outer border widths
			RectF getCalendarInnerBorderWidth() const; // Return month calendar inner border widths
			RectF getCalendarPadding() const; // Return month calendar padding
			int getCalendarShadowRadius() const; // Return month calendar shadow radius
			PointF getCalendarShadowShift() const; // Return month calendar shadow shift
			Color getCalendarShadowColor() const; // Return month calendar shadow color
			RectF getCalendarBorderRadius() const; // Return month calendar corner radiuses
			BorderColor getCalendarOuterBorderColor() const; // Return month calendar outer border colors
			BorderColor getCalendarInnerBorderColor() const; // Return month calendar inner border colors
			Color getCalendarBackgroundColor() const; // Return month calendar background color
			Gradient *getCalendarBackgroundGradient(); // Return month calendar background gradient

			// Setters
			bool setMonthCalendar(IBuiltInMonthCalendar *value); // Set new built-in month calendar
			bool setDisplayMode(const DisplayMode value); // Set display mode
			bool setMonthFormat(const MonthFormat value); // Set month format
			bool setElementOrder(const ElementOrder value); // Set elements order
			bool setOpenDirection(const OpenDirection value); // Set month calendar appear direction
			bool setOpenAlign(const OpenAlign value); // Set month calendar horizontal alignment
			bool setSeparator1(const String &value); // Set separator value between first and second elements
			bool setSeparator2(const String &value); // Set separator value between second and third elements
			bool setShowDayLeadingZeros(const bool value); // Set whether day should have leading zero if day is less than 10
			bool setShowMonthLeadingZeros(const bool value); // Set whether month should have leading zero if month is less than 10(works in mfShort month format mode only)
			bool setShowYearLeadingZeros(const bool value); // Set whether year should have leading zero if year is less than 1000
			bool setShowIcon(const bool value); // Set whether icon should be shown near the down arrow in dmDropDown display mode
			bool setTimerInterval(const float value); // Set update interval when mouse is down over an up or down arrow
			bool setArrowsAtRight(const bool value); // Set whether arrows at the control right or left side
			bool setContentAlign(const TextAlign value); // Set time horizontal alignment inside control area
			bool setShadowRadius(const State state, const int value); // Set control shadow radius. "state" is the control state
			bool setShadowShift(const State state, const PointF &value); // Set control shadow shift. "state" is the control state
			bool setShadowColor(const State state, const Color &value); // Set control shadow color. "state" is the control state
			bool setBorderRadius(const State state, const RectF &value); // Set control corner radiuses. "state" is the control state
			bool setOuterBorderWidth(const State state, const RectF &value); // Set control outer border widths. "state" is the control state
			bool setOuterBorderColor(const State state, const BorderColor &value); // Set control outer border colors. "state" is the control state
			bool setInnerBorderWidth(const State state, const RectF &value); // Set control inner border widths. "state" is the control state
			bool setInnerBorderColor(const State state, const BorderColor &value); // Set control inner border colors. "state" is the control state
			bool setBackgroundColor(const State state, const Color &value); // Set control background color. "state" is the control state
			bool setUpArrowBorderRadius(const State state, const RectF &value); // Set up-arrow area corner radiuses. "state" is the arrow state. Used in up-down mode only
			bool setUpArrowOuterBorderWidth(const State state, const RectF &value); // Set up-arrow area outer border widths. "state" is the arrow state. Used in up-down mode only
			bool setUpArrowInnerBorderWidth(const State state, const RectF &value); // Set up-arrow area inner border widths. "state" is the arrow state. Used in up-down mode only
			bool setUpArrowOuterBorderColor(const State state, const BorderColor &value); // Set up-arrow area outer border colors. "state" is the arrow state. Used in up-down mode only
			bool setUpArrowInnerBorderColor(const State state, const BorderColor &value); // Set up-arrow area inner border colors. "state" is the arrow state. Used in up-down mode only
			bool setUpArrowBackgroundColor(const State state, const Color &value); // Set up-arrow area background color. "state" is the arrow state. Used in up-down mode only
			bool setUpArrowPadding(const State state, const RectF &value); // Set up-arrow area padding. "state" is the arrow state. Used in up-down mode only
			bool setUpArrowColor1(const State state, const Color &value); // Set up-arrow first point color. "state" is the arrow state. Used in up-down mode only
			bool setUpArrowColor2(const State state, const Color &value); // Set up-arrow second point color. "state" is the arrow state. Used in up-down mode only
			bool setUpArrowColor3(const State state, const Color &value); // Set up-arrow third point color. "state" is the arrow state. Used in up-down mode only
			bool setDownArrowBorderRadius(const State state, const RectF &value); // Set down-arrow area corner radiuses. "state" is the arrow state. Used in up-down mode only
			bool setDownArrowOuterBorderWidth(const State state, const RectF &value); // Set down-arrow area outer border widths. "state" is the arrow state. Used in up-down mode only
			bool setDownArrowInnerBorderWidth(const State state, const RectF &value); // Set down-arrow area inner border widths. "state" is the arrow state. Used in up-down mode only
			bool setDownArrowOuterBorderColor(const State state, const BorderColor &value); // Set down-arrow area outer border colors. "state" is the arrow state. Used in up-down mode only
			bool setDownArrowInnerBorderColor(const State state, const BorderColor &value); // Set down-arrow area inner border colors. "state" is the arrow state. Used in up-down mode only
			bool setDownArrowBackgroundColor(const State state, const Color &value); // Set down-arrow area background color. "state" is the arrow state. Used in up-down mode only
			bool setDownArrowPadding(const State state, const RectF &value); // Set down-arrow area padding. "state" is the arrow state. Used in up-down mode only
			bool setDownArrowColor1(const State state, const Color &value); // Set down-arrow first point color. "state" is the arrow state. Used in up-down mode only
			bool setDownArrowColor2(const State state, const Color &value); // Set down-arrow second point color. "state" is the arrow state. Used in up-down mode only
			bool setDownArrowColor3(const State state, const Color &value); // Set down-arrow third point color. "state" is the arrow state. Used in up-down mode only
			bool setArrowDistance(const State state, const float value); // Set distance between up and down arrows. "state" is the control state. Used in up-down mode only
			bool setArrowBorderRadius(const State state, const RectF &value); // Set down-arrow area corner radiuses. "state" is the arrow state. Used in drop-down mode only
			bool setArrowOuterBorderWidth(const State state, const RectF &value); // Set down-arrow area outer border widths. "state" is the arrow state. Used in drop-down mode only
			bool setArrowInnerBorderWidth(const State state, const RectF &value); // Set down-arrow area inner border widths. "state" is the arrow state. Used in drop-down mode only
			bool setArrowOuterBorderColor(const State state, const BorderColor &value); // Set down-arrow area outer border colors. "state" is the arrow state. Used in drop-down mode only
			bool setArrowInnerBorderColor(const State state, const BorderColor &value); // Set down-arrow area inner border colors. "state" is the arrow state. Used in drop-down mode only
			bool setArrowBackgroundColor(const State state, const Color &value); // Set down-arrow area background color. "state" is the arrow state. Used in drop-down mode only
			bool setArrowPadding(const State state, const RectF &value); // Set down-arrow area padding. "state" is the arrow state. Used in drop-down mode only
			bool setArrowColor1(const State state, const Color &value); // Set down-arrow first point color. "state" is the arrow state. Used in drop-down mode only
			bool setArrowColor2(const State state, const Color &value); // Set down-arrow second point color. "state" is the arrow state. Used in drop-down mode only
			bool setArrowColor3(const State state, const Color &value); // Set down-arrow third point color. "state" is the arrow state. Used in drop-down mode only
			bool setImageList(IImageList *value); // Set image list which is a source of custom icon
			bool setIconIndex(const State state, const int value); // Set icon index
			bool setIconPadding(const State state, const RectF &value); // Set icon padding
			bool setElementBackgroundColor(const State state, const Color &value); // Set element(years, months, days) background color. "state" is the element state
			bool setElementColor(const State state, const Color &value); // Set element(years, months, days) text color. "state" is the element state
			bool setElementPadding(const State state, const float value); // Set distance between borders/arrows and content. "state" is the control state
			bool setCalendarMargin(const float value); // Set month calendar vertical distance to the control
			bool setCalendarOuterBorderWidth(const RectF &value); // Set month calendar outer border widths
			bool setCalendarInnerBorderWidth(const RectF &value); // Set month calendar inner border widths
			bool setCalendarPadding(const RectF &value); // Set month calendar padding
			bool setCalendarShadowRadius(const int value); // Set month calendar shadow radius
			bool setCalendarShadowShift(const PointF &value); // Set month calendar shadow shift
			bool setCalendarShadowColor(const Color &value); // Set month calendar shadow color
			bool setCalendarBorderRadius(const RectF &value); // Set month calendar corner radiuses
			bool setCalendarOuterBorderColor(const BorderColor &value); // Set month calendar outer border colors
			bool setCalendarInnerBorderColor(const BorderColor &value); // Set month calendar inner border colors
			bool setCalendarBackgroundColor(const Color &value); // Set month calendar background color

			// Methods
			bool ActivateYears(); // Activate years part
			bool ActivateMonth(); // Activate months part
			bool ActivateDays(); // Activate days part
			bool Open(); // Show month calendar
			bool Close(); // Close month calendar
		};
	}
}
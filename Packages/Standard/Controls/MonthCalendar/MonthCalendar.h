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
#include "Nitisa/Core/Align.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/TextAlign.h"
#include "Nitisa/Core/VerticalAlign.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IMonthCalendar.h"

namespace nitisa
{
	class IBuiltInControl;
	class IBuiltInMonthCalendar;
	class IControl;
	class IForm;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CMonthCalendarService;

		class CMonthCalendar :public virtual IMonthCalendar, public CControl
		{
			friend CMonthCalendarService;
		public:
			enum class State // Control states
			{
				Normal, // Normal
				Hovered, // Hovered
				Disabled // Disabled
			};
		private:
			class CBuiltIn :public CBuiltInMonthCalendar
			{
			private:
				CMonthCalendar * m_pControl;
			public:
				IControl * getControl() override;

				CBuiltIn(CMonthCalendar *control);
			};

			class CListener :public virtual IBuiltInMonthCalendarListener
			{
			private:
				CMonthCalendar * m_pControl;
			public:
				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnChange(IBuiltInControl *sender) override;

				CListener(CMonthCalendar *control);
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CMonthCalendar *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CMonthCalendar *control);
			};
		private:
			CGradientListener m_cGradientListener;
			RectF m_sOuterBorderWidth;
			RectF m_sInnerBorderWidth;
			RectF m_sPadding;
			int m_aShadowRadius[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];
			Color m_aShadowColor[(int)State::Disabled + 1];
			RectF m_aBorderRadius[(int)State::Disabled + 1];
			BorderColor m_aOuterBorderColor[(int)State::Disabled + 1];
			BorderColor m_aInnerBorderColor[(int)State::Disabled + 1];
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];

			ITexture *m_pCanvas;
			IBuiltInMonthCalendar *m_pMonthCalendar;
			bool m_bIgnoreGradient;
			CListener m_cListener;

			IBuiltInMonthCalendar *getMonthCalendar();
			void UpdateFromStyle(IStyle *style);
			void UpdateSize();
			void Render();
		public:
			// IControl getters
			RectF getClientRect() override;
			RectF getRenderRect() override;

			// IControl setters
			bool setAlign(const Align value) override; // Not allowed
			bool setConstraints(const RectF &value) override; // Not allowed
			bool setSize(const PointF &value) override; // Not allowed. Size is always calculated automatically
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			// IMonthCalendar getters
			int getYear() override;
			int getMonth() override;
			int getDay() override;
			int getMinYear() override;
			int getMinMonth() override;
			int getMinDay() override;
			int getMaxYear() override;
			int getMaxMonth() override;
			int getMaxDay() override;

			// IMonthCalendar setters
			bool setYear(const int value) override;
			bool setMonth(const int value) override;
			bool setDay(const int value) override;
			bool setMinYear(const int value) override;
			bool setMinMonth(const int value) override;
			bool setMinDay(const int value) override;
			bool setMaxYear(const int value) override;
			bool setMaxMonth(const int value) override;
			bool setMaxDay(const int value) override;

			// IMonthCalendar methods
			bool Next() override;
			bool Prev() override;
			bool Today() override;

			// Constructors
			CMonthCalendar();
			CMonthCalendar(IForm *parent);
			CMonthCalendar(IControl *parent);
			~CMonthCalendar() override;

			// Getters
			State getState(); // Return control state
			RectF getOuterBorderWidth() const; // Return outer border widths
			RectF getInnerBorderWidth() const; // Return inner border widths
			RectF getPadding() const; // Return padding
			int getShadowRadius(const State state) const; // Return shadow radius
			PointF getShadowShift(const State state) const; // Return shadow shift
			Color getShadowColor(const State state) const; // Return shadow color
			RectF getBorderRadius(const State state) const; // Return corner radiuses
			BorderColor getOuterBorderColor(const State state) const; // Return outer border colors
			BorderColor getInnerBorderColor(const State state) const; // Return inner border colors
			Color getBackgroundColor(const State state) const; // Return background color
			Gradient *getBackgroundGradient(const State state); // Return background gradient

			// Setters
			bool setMonthCalendar(IBuiltInMonthCalendar *value); // Set month calendar
			bool setOuterBorderWidth(const RectF &value); // Set outer border widths
			bool setInnerBorderWidth(const RectF &value); // Set inner border widths
			bool setPadding(const RectF &value); // Set padding
			bool setShadowRadius(const State state, const int value); // Set shadow radius
			bool setShadowShift(const State state, const PointF &value); // Set shadow shift
			bool setShadowColor(const State state, const Color &value); // Set shadow color
			bool setBorderRadius(const State state, const RectF &value); // Set corner radiuses
			bool setOuterBorderColor(const State state, const BorderColor &value); // Set outer border colors
			bool setInnerBorderColor(const State state, const BorderColor &value); // Set inner border colors
			bool setBackgroundColor(const State state, const Color &value); // Set background color

			// CBuiltInMonthCalendar getters. Available only if associated IBuiltInMonthCalendar is instance of CBuiltInMonthCalendar(which is true by default)
			CBuiltInMonthCalendar::Mode getMode();
			bool isShowToday();
			RectF getTitlePadding();
			RectF getTodayPadding();
			RectF getElementPadding();
			RectF getDayPadding();
			float getTodayMargin();
			float getTodayRectWidth();
			bool isAnimate();
			float getAnimateInterval();
			float getAnimateMinScale();
			float getAnimateTime();
			float getScrollInterval();
			TextAlign getTitleAlign(const CBuiltInMonthCalendar::TitleState state);
			RectF getTitleBorderRadius(const CBuiltInMonthCalendar::TitleState state);
			RectF getTitleBorderWidth(const CBuiltInMonthCalendar::TitleState state);
			BorderColor getTitleBorderColor(const CBuiltInMonthCalendar::TitleState state);
			Color getTitleBackgroundColor(const CBuiltInMonthCalendar::TitleState state);
			Gradient *getTitleBackgroundGradient(const CBuiltInMonthCalendar::TitleState state);
			Color getTitleColor(const CBuiltInMonthCalendar::TitleState state);
			RectF getTitlePrevRangeBorderRadius(const CBuiltInMonthCalendar::TitleState state);
			RectF getTitlePrevRangeBorderWidth(const CBuiltInMonthCalendar::TitleState state);
			BorderColor getTitlePrevRangeBorderColor(const CBuiltInMonthCalendar::TitleState state);
			Color getTitlePrevRangeBackgroundColor(const CBuiltInMonthCalendar::TitleState state);
			Gradient *getTitlePrevRangeBackgroundGradient(const CBuiltInMonthCalendar::TitleState state);
			RectF getTitlePrevRangePadding(const CBuiltInMonthCalendar::TitleState state);
			Color getTitlePrevRangeColor1(const CBuiltInMonthCalendar::TitleState state);
			Color getTitlePrevRangeColor2(const CBuiltInMonthCalendar::TitleState state);
			Color getTitlePrevRangeColor3(const CBuiltInMonthCalendar::TitleState state);
			RectF getTitleNextRangeBorderRadius(const CBuiltInMonthCalendar::TitleState state);
			RectF getTitleNextRangeBorderWidth(const CBuiltInMonthCalendar::TitleState state);
			BorderColor getTitleNextRangeBorderColor(const CBuiltInMonthCalendar::TitleState state);
			Color getTitleNextRangeBackgroundColor(const CBuiltInMonthCalendar::TitleState state);
			Gradient *getTitleNextRangeBackgroundGradient(const CBuiltInMonthCalendar::TitleState state);
			RectF getTitleNextRangePadding(const CBuiltInMonthCalendar::TitleState state);
			Color getTitleNextRangeColor1(const CBuiltInMonthCalendar::TitleState state);
			Color getTitleNextRangeColor2(const CBuiltInMonthCalendar::TitleState state);
			Color getTitleNextRangeColor3(const CBuiltInMonthCalendar::TitleState state);
			TextAlign getTodayAlign(const CBuiltInMonthCalendar::TitleState state);
			RectF getTodayBorderRadius(const CBuiltInMonthCalendar::TitleState state);
			RectF getTodayBorderWidth(const CBuiltInMonthCalendar::TitleState state);
			BorderColor getTodayBorderColor(const CBuiltInMonthCalendar::TitleState state);
			Color getTodayBackgroundColor(const CBuiltInMonthCalendar::TitleState state);
			Gradient *getTodayBackgroundGradient(const CBuiltInMonthCalendar::TitleState state);
			Color getTodayColor(const CBuiltInMonthCalendar::TitleState state);
			RectF getTodayRectBorderRadius(const CBuiltInMonthCalendar::TitleState state);
			RectF getTodayRectBorderWidth(const CBuiltInMonthCalendar::TitleState state);
			BorderColor getTodayRectBorderColor(const CBuiltInMonthCalendar::TitleState state);
			Color getTodayRectBackgroundColor(const CBuiltInMonthCalendar::TitleState state);
			Gradient *getTodayRectBackgroundGradient(const CBuiltInMonthCalendar::TitleState state);
			TextAlign getElementHorizontalAlign(const CBuiltInMonthCalendar::ElementState state);
			VerticalAlign getElementVerticalAlign(const CBuiltInMonthCalendar::ElementState state);
			RectF getElementBorderRadius(const CBuiltInMonthCalendar::ElementState state);
			RectF getElementBorderWidth(const CBuiltInMonthCalendar::ElementState state);
			BorderColor getElementBorderColor(const CBuiltInMonthCalendar::ElementState state);
			Color getElementBackgroundColor(const CBuiltInMonthCalendar::ElementState state);
			Gradient *getElementBackgroundGradient(const CBuiltInMonthCalendar::ElementState state);
			Color getElementColor(const CBuiltInMonthCalendar::ElementState state);
			Color getElementOutlineColor(const CBuiltInMonthCalendar::ElementState state);
			unsigned int getElementOutlineMask(const CBuiltInMonthCalendar::ElementState state);
			TextAlign getDayHorizontalAlign(const CBuiltInMonthCalendar::ElementState state);
			VerticalAlign getDayVerticalAlign(const CBuiltInMonthCalendar::ElementState state);
			TextAlign getDayTitleHorizontalAlign(const CBuiltInMonthCalendar::DayTitleState state);
			VerticalAlign getDayTitleVerticalAlign(const CBuiltInMonthCalendar::DayTitleState state);
			RectF getDayTitleBorderRadius(const CBuiltInMonthCalendar::DayTitleState state);
			RectF getDayTitleBorderWidth(const CBuiltInMonthCalendar::DayTitleState state);
			BorderColor getDayTitleBorderColor(const CBuiltInMonthCalendar::DayTitleState state);
			Color getDayTitleBackgroundColor(const CBuiltInMonthCalendar::DayTitleState state);
			Gradient *getDayTitleBackgroundGradient(const CBuiltInMonthCalendar::DayTitleState state);
			Color getDayTitleColor(const CBuiltInMonthCalendar::DayTitleState state);

			// CBuiltInMonthCalendar setters. Available only if associated IBuiltInMonthCalendar is instance of CBuiltInMonthCalendar(which is true by default)
			bool setMode(const CBuiltInMonthCalendar::Mode value);
			bool setShowToday(const bool value);
			bool setTitlePadding(const RectF &value);
			bool setTodayPadding(const RectF &value);
			bool setElementPadding(const RectF &value);
			bool setDayPadding(const RectF &value);
			bool setTodayMargin(const float value);
			bool setTodayRectWidth(const float value);
			bool setAnimate(const bool value);
			bool setAnimateInterval(const float value);
			bool setAnimateMinScale(const float value);
			bool setAnimateTime(const float value);
			bool setScrollInterval(const float value);
			bool setTitleAlign(const CBuiltInMonthCalendar::TitleState state, const TextAlign value);
			bool setTitleBorderRadius(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setTitleBorderWidth(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setTitleBorderColor(const CBuiltInMonthCalendar::TitleState state, const BorderColor &value);
			bool setTitleBackgroundColor(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setTitleColor(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setTitlePrevRangeBorderRadius(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setTitlePrevRangeBorderWidth(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setTitlePrevRangeBorderColor(const CBuiltInMonthCalendar::TitleState state, const BorderColor &value);
			bool setTitlePrevRangeBackgroundColor(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setTitlePrevRangePadding(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setTitlePrevRangeColor1(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setTitlePrevRangeColor2(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setTitlePrevRangeColor3(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setTitleNextRangeBorderRadius(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setTitleNextRangeBorderWidth(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setTitleNextRangeBorderColor(const CBuiltInMonthCalendar::TitleState state, const BorderColor &value);
			bool setTitleNextRangeBackgroundColor(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setTitleNextRangePadding(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setTitleNextRangeColor1(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setTitleNextRangeColor2(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setTitleNextRangeColor3(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setTodayAlign(const CBuiltInMonthCalendar::TitleState state, const TextAlign value);
			bool setTodayBorderRadius(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setTodayBorderWidth(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setTodayBorderColor(const CBuiltInMonthCalendar::TitleState state, const BorderColor &value);
			bool setTodayBackgroundColor(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setTodayColor(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setTodayRectBorderRadius(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setTodayRectBorderWidth(const CBuiltInMonthCalendar::TitleState state, const RectF &value);
			bool setTodayRectBorderColor(const CBuiltInMonthCalendar::TitleState state, const BorderColor &value);
			bool setTodayRectBackgroundColor(const CBuiltInMonthCalendar::TitleState state, const Color &value);
			bool setElementHorizontalAlign(const CBuiltInMonthCalendar::ElementState state, const TextAlign value);
			bool setElementVerticalAlign(const CBuiltInMonthCalendar::ElementState state, const VerticalAlign value);
			bool setElementBorderRadius(const CBuiltInMonthCalendar::ElementState state, const RectF &value);
			bool setElementBorderWidth(const CBuiltInMonthCalendar::ElementState state, const RectF &value);
			bool setElementBorderColor(const CBuiltInMonthCalendar::ElementState state, const BorderColor &value);
			bool setElementBackgroundColor(const CBuiltInMonthCalendar::ElementState state, const Color &value);
			bool setElementColor(const CBuiltInMonthCalendar::ElementState state, const Color &value);
			bool setElementOutlineColor(const CBuiltInMonthCalendar::ElementState state, const Color &value);
			bool setElementOutlineMask(const CBuiltInMonthCalendar::ElementState state, const unsigned int value);
			bool setDayHorizontalAlign(const CBuiltInMonthCalendar::ElementState state, const TextAlign value);
			bool setDayVerticalAlign(const CBuiltInMonthCalendar::ElementState state, const VerticalAlign value);
			bool setDayTitleHorizontalAlign(const CBuiltInMonthCalendar::DayTitleState state, const TextAlign value);
			bool setDayTitleVerticalAlign(const CBuiltInMonthCalendar::DayTitleState state, const VerticalAlign value);
			bool setDayTitleBorderRadius(const CBuiltInMonthCalendar::DayTitleState state, const RectF &value);
			bool setDayTitleBorderWidth(const CBuiltInMonthCalendar::DayTitleState state, const RectF &value);
			bool setDayTitleBorderColor(const CBuiltInMonthCalendar::DayTitleState state, const BorderColor &value);
			bool setDayTitleBackgroundColor(const CBuiltInMonthCalendar::DayTitleState state, const Color &value);
			bool setDayTitleColor(const CBuiltInMonthCalendar::DayTitleState state, const Color &value);
		};
	}
}
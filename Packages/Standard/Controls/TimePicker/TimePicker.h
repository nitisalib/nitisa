// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/TextAlign.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Interfaces/ITimerListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../ITimePicker.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CTimePickerService;

		class CTimePicker :public virtual ITimePicker, public CControl
		{
			friend CTimePickerService;
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
		private:
			enum class Element
			{
				None,
				Hours,
				Minutes,
				Seconds,
				UpArrow,
				DownArrow
			};

			class CTimerListener :public virtual ITimerListener
			{
			private:
				CTimePicker *m_pControl;
			public:
				void NotifyOnTimer(const PlatformHandle id) override;

				CTimerListener(CTimePicker *control);
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CTimePicker *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CTimePicker *control);
			};
		private:
			CGradientListener m_cGradientListener;
			int m_iHour;
			int m_iMinute;
			int m_iSecond;
			int m_iMinHour;
			int m_iMinMinute;
			int m_iMinSecond;
			int m_iMaxHour;
			int m_iMaxMinute;
			int m_iMaxSecond;
			float m_fTimerInterval;
			bool m_bShowSeconds;
			bool m_bShowArrows;
			bool m_bArrowsAtRight;
			TextAlign m_eContentAlign;
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
			Color m_aElementBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aElementBackgroundGradient[(int)State::Disabled + 1];
			Color m_aElementColor[(int)State::Disabled + 1];
			float m_aPadding[(int)State::Disabled + 1];

			ITexture *m_pCanvas;
			bool m_bIgnoreGradient;
			Element m_eActiveElement;
			Element m_eHoveredElement;
			Element m_eDownElement;
			PointF m_sDigitSize;
			float m_fSeparatorWidth;
			PlatformHandle m_hTimer;
			bool m_bFirstDigit;
			CTimerListener m_cTimerListener;

			void UpdateFromStyle(IStyle *style);
			int PackTime(const int hour, const int minute, const int second);
			void UnpackTime(const int value, int &hour, int &minute, int &second);
			bool setTime(const int hour, const int minute, const int second);
			bool UpdateHoveredElement();
			bool UpdateHoveredElement(const PointF &pos);
			void UpdateMetrics();
			RectF getArrowsRect(const State state);
			RectF getUpArrowRect(const RectF &rect, const State state);
			RectF getDownArrowRect(const RectF &rect, const State state);
			RectF getContentRect(const State state);
			RectF getHoursRect(const RectF &rect);
			RectF getMinutesRect(const RectF &rect);
			RectF getSecondsRect(const RectF &rect);
			State getHoursState();
			State getMinutesState();
			State getSecondsState();
			State getUpArrowState();
			State getDownArrowState();
			Color CalculateElementColor(const State state);
			String NumberToString(const int value);
			RectF CalculateClientRect(const State state);
			void Render();
			void RenderContent(IRenderer *renderer, const State state, const PointF &disp);
			void RenderArrows(IRenderer *renderer, const State state, const PointF &disp);
		public:
			// IControl getters
			RectF getRenderRect() override;

			// IControl setters
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			// ITimePicker getters
			int getHour() override; // By default 0
			int getMinute() override; // By default 0
			int getSecond() override; // By default 0
			int getMinHour() override; // By default 0
			int getMinMinute() override; // By default 0
			int getMinSecond() override; // By default 0
			int getMaxHour() override; // By default 23
			int getMaxMinute() override; // By default 59
			int getMaxSecond() override; // By default 59

			// ITimePicker setters
			bool setHour(const int value) override;
			bool setMinute(const int value) override;
			bool setSecond(const int value) override;
			bool setMinHour(const int value) override;
			bool setMinMinute(const int value) override;
			bool setMinSecond(const int value) override;
			bool setMaxHour(const int value) override;
			bool setMaxMinute(const int value) override;
			bool setMaxSecond(const int value) override;

			CTimePicker(); // Create
			CTimePicker(IForm *parent); // Create and place on the form
			CTimePicker(IControl *parent); // Create and place on the parent control

			// Getters
			State getState(); // Return control state
			float getTimerInterval() const; // Return update interval when mouse is down over an arrow
			bool isShowSeconds() const; // Return whether seconds should be shown or not
			bool isShowArrows() const; // Return whether arrows should be shown or not
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
			RectF getUpArrowBorderRadius(const State state) const; // Return up-arrow area corner radiuses. "state" is the arrow state
			RectF getUpArrowOuterBorderWidth(const State state) const; // Return up-arrow area outer border widths. "state" is the arrow state
			RectF getUpArrowInnerBorderWidth(const State state) const; // Return up-arrow area inner border widths. "state" is the arrow state
			BorderColor getUpArrowOuterBorderColor(const State state) const; // Return up-arrow area outer border colors. "state" is the arrow state
			BorderColor getUpArrowInnerBorderColor(const State state) const; // Return up-arrow area inner border colors. "state" is the arrow state
			Color getUpArrowBackgroundColor(const State state) const; // Return up-arrow area background color. "state" is the arrow state
			Gradient *getUpArrowBackgroundGradient(const State state); // Return up-arrow area background gradient. "state" is the arrow state
			RectF getUpArrowPadding(const State state) const; // Return up-arrow area padding. "state" is the arrow state
			Color getUpArrowColor1(const State state) const; // Return up-arrow first point color. "state" is the arrow state
			Color getUpArrowColor2(const State state) const; // Return up-arrow second point color. "state" is the arrow state
			Color getUpArrowColor3(const State state) const; // Return up-arrow third point color. "state" is the arrow state
			RectF getDownArrowBorderRadius(const State state) const; // Return down-arrow area corner radiuses. "state" is the arrow state
			RectF getDownArrowOuterBorderWidth(const State state) const; // Return down-arrow area outer border widths. "state" is the arrow state
			RectF getDownArrowInnerBorderWidth(const State state) const; // Return down-arrow area inner border widths. "state" is the arrow state
			BorderColor getDownArrowOuterBorderColor(const State state) const; // Return down-arrow area outer border colors. "state" is the arrow state
			BorderColor getDownArrowInnerBorderColor(const State state) const; // Return down-arrow area inner border colors. "state" is the arrow state
			Color getDownArrowBackgroundColor(const State state) const; // Return down-arrow area background color. "state" is the arrow state
			Gradient *getDownArrowBackgroundGradient(const State state); // Return down-arrow area background gradient. "state" is the arrow state
			RectF getDownArrowPadding(const State state) const; // Return down-arrow area padding. "state" is the arrow state
			Color getDownArrowColor1(const State state) const; // Return down-arrow first point color. "state" is the arrow state
			Color getDownArrowColor2(const State state) const; // Return down-arrow second point color. "state" is the arrow state
			Color getDownArrowColor3(const State state) const; // Return down-arrow third point color. "state" is the arrow state
			float getArrowDistance(const State state) const; // Return distance between up and down arrows. "state" is the control state
			Color getElementBackgroundColor(const State state) const; // Return element(hours, minutes, seconds) background color. "state" is the element state
			Gradient *getElementBackgroundGradient(const State state); // Return element(hours, minutes, seconds) background gradient. "state" is the element state
			Color getElementColor(const State state) const; // Return element(hours, minutes, seconds) text color. "state" is the element state
			float getPadding(const State state) const; // Return distance between borders/arrows and content. "state" is the control state

			// Setters
			bool setTimerInterval(const float value); // Set update interval when mouse is down over an arrow
			bool setShowSeconds(const bool value); // Set whether seconds should be shown or not
			bool setShowArrows(const bool value); // Set whether arrows should be shown or not
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
			bool setUpArrowBorderRadius(const State state, const RectF &value); // Set up-arrow area corner radiuses. "state" is the arrow state
			bool setUpArrowOuterBorderWidth(const State state, const RectF &value); // Set up-arrow area outer border widths. "state" is the arrow state
			bool setUpArrowInnerBorderWidth(const State state, const RectF &value); // Set up-arrow area inner border widths. "state" is the arrow state
			bool setUpArrowOuterBorderColor(const State state, const BorderColor &value); // Set up-arrow area outer border colors. "state" is the arrow state
			bool setUpArrowInnerBorderColor(const State state, const BorderColor &value); // Set up-arrow area inner border colors. "state" is the arrow state
			bool setUpArrowBackgroundColor(const State state, const Color &value); // Set up-arrow area background color. "state" is the arrow state
			bool setUpArrowPadding(const State state, const RectF &value); // Set up-arrow area padding. "state" is the arrow state
			bool setUpArrowColor1(const State state, const Color &value); // Set up-arrow first point color. "state" is the arrow state
			bool setUpArrowColor2(const State state, const Color &value); // Set up-arrow second point color. "state" is the arrow state
			bool setUpArrowColor3(const State state, const Color &value); // Set up-arrow third point color. "state" is the arrow state
			bool setDownArrowBorderRadius(const State state, const RectF &value); // Set down-arrow area corner radiuses. "state" is the arrow state
			bool setDownArrowOuterBorderWidth(const State state, const RectF &value); // Set down-arrow area outer border widths. "state" is the arrow state
			bool setDownArrowInnerBorderWidth(const State state, const RectF &value); // Set down-arrow area inner border widths. "state" is the arrow state
			bool setDownArrowOuterBorderColor(const State state, const BorderColor &value); // Set down-arrow area outer border colors. "state" is the arrow state
			bool setDownArrowInnerBorderColor(const State state, const BorderColor &value); // Set down-arrow area inner border colors. "state" is the arrow state
			bool setDownArrowBackgroundColor(const State state, const Color &value); // Set down-arrow area background color. "state" is the arrow state
			bool setDownArrowPadding(const State state, const RectF &value); // Set down-arrow area padding. "state" is the arrow state
			bool setDownArrowColor1(const State state, const Color &value); // Set down-arrow first point color. "state" is the arrow state
			bool setDownArrowColor2(const State state, const Color &value); // Set down-arrow second point color. "state" is the arrow state
			bool setDownArrowColor3(const State state, const Color &value); // Set down-arrow third point color. "state" is the arrow state
			bool setArrowDistance(const State state, const float value); // Set distance between up and down arrows. "state" is the control state
			bool setElementBackgroundColor(const State state, const Color &value); // Set element(hours, minutes, seconds) background color. "state" is the element state
			bool setElementColor(const State state, const Color &value); // Set element(hours, minutes, seconds) text color. "state" is the element state
			bool setPadding(const State state, const float value); // Set distance between borders/arrows and content. "state" is the control state

			bool ActivateHours(); // Activate hours part
			bool ActivateMinutes(); // Activate minutes part
			bool ActivateSeconds(); // Activate seconds part
		};
	}
}
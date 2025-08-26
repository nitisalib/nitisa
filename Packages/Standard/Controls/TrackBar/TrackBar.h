// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../ITrackBar.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CTrackBarService;

		class CTrackBar :public virtual ITrackBar, public CControl
		{
			friend CTrackBarService;
		public:
			enum class TrackerStyle // Tracker styles
			{
				Down, // Point down
				Up, // Point up
				Both // Not directional
			};

			enum class State // Control and tracker states
			{
				Normal, // Normal
				Hovered, // Mouse pointer is over the control/tracker
				Focused, // Control is focused
				FocusedHovered, // Control is focused and mouse pointer is over the control/tracker
				Active, // Control is in mouse button down state
				ActiveHovered, // Control is in mouse button down state and mouse pointer is over the control/tracker
				Disabled // Disabled
			};
		private:
			enum class Element
			{
				None,
				Tracker,
				Back
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CTrackBar *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CTrackBar *control);
			};
		private:
			CGradientListener m_cGradientListener;
			int m_iMin;
			int m_iMax;
			int m_iValue;
			TrackerStyle m_eTrackerStyle;
			RectF m_aBackPadding[(int)TrackerStyle::Both + 1];
			float m_aBackMargin[(int)TrackerStyle::Both + 1]; // Distance to ticks
			PointF m_aTickSize[(int)TrackerStyle::Both + 1];
			PointF m_aBigTickSize[(int)TrackerStyle::Both + 1];
			PointF m_aTrackerPadding[(int)TrackerStyle::Both + 1]; // Top and bottom of control
			float m_aTrackerWidth[(int)TrackerStyle::Both + 1];
			int m_iTickInterval; // <= 0 - no ticks
			int m_iBigTickInterval; // In count of regular ticks. <= 0 - no big ticks
			// Control style
			RectF m_aBorderWidth[(int)State::Disabled + 1];
			RectF m_aBorderRadius[(int)State::Disabled + 1];
			BorderColor m_aBorderColor[(int)State::Disabled + 1];
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
			int m_aShadowRadius[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];
			Color m_aShadowColor[(int)State::Disabled + 1];
			// Back part style
			RectF m_aBackBorderWidth[(int)State::Disabled + 1];
			RectF m_aBackBorderRadius[(int)State::Disabled + 1];
			BorderColor m_aBackBorderColor[(int)State::Disabled + 1];
			Color m_aBackBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackBackgroundGradient[(int)State::Disabled + 1];
			// Tracker style
			RectF m_aTrackerBorderWidth[(int)State::Disabled + 1];
			RectF m_aTrackerBorderRadius[(int)State::Disabled + 1];
			BorderColor m_aTrackerBorderColor[(int)State::Disabled + 1];
			Color m_aTrackerBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aTrackerBackgroundGradient[(int)State::Disabled + 1];
			// Ticks style
			Color m_aTickColor[(int)State::Disabled + 1];
			Color m_aBigTickColor[(int)State::Disabled + 1];
			// Outline
			Color m_aOutlineColor[(int)State::Disabled + 1];
			unsigned int m_aOutlineMask[(int)State::Disabled + 1];

			bool m_bIgnoreGradient;
			ITexture *m_pCanvas;
			Element m_eHoveredElement;

			void UpdateFromStyle(IStyle *style);
			State getTrackerState();
			RectF getTrackerRect();
			RectF getBackRect();
			bool UpdateHoveredElement(const PointF &position);
			int ClientToValue(const PointF &position);
			void Render();
			void RenderBack(IRenderer *renderer, const RectF &rect, const State state);
			void RenderTicks(IRenderer *renderer, const RectF &rect, const State state);
			void RenderTracker(IRenderer *renderer, const RectF &rect, const State state);
			void RenderTrackerDown(IRenderer *renderer, const RectF &rect, const State state);
			void RenderTrackerUp(IRenderer *renderer, const RectF &rect, const State state);
			void RenderTrackerBoth(IRenderer *renderer, const RectF &rect, const State state);
			void RenderOutline(IRenderer *renderer, const RectF &rect, const State state);
		public:
			// IControl getters
			RectF getRenderRect() override;

			// IControl setters
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			// ITrackBar getters
			int getMin() override;
			int getMax() override;
			int getValue() override;

			// ITrackBar setters
			bool setMin(const int value) override;
			bool setMax(const int value) override;
			bool setValue(const int value) override;

			CTrackBar();
			CTrackBar(IForm *parent);
			CTrackBar(IControl *parent);

			// Getters
			State getState(); // Return current state
			TrackerStyle getTrackerStyle() const; // Return tracker style
			RectF getBackPadding(const TrackerStyle style) const; // Return back part padding
			float getBackMargin(const TrackerStyle style) const; // Return distance from back part to ticks
			PointF getTickSize(const TrackerStyle style) const; // Return regular tick size
			PointF getBigTickSize(const TrackerStyle style) const; // Return big tick size
			PointF getTrackerPadding(const TrackerStyle style) const; // Return tracker padding
			float getTrackerWidth(const TrackerStyle style) const; // Return tracker width
			int getTickInterval() const; // Return interval of ticks to be drawn(<= 0 - no ticks will be drawn)
			int getBigTickInterval() const; // Return interval of big tick(in count of small ones)
			RectF getBorderWidth(const State state) const; // Return control border widths
			RectF getBorderRadius(const State state) const; // Return control corner radiuses
			BorderColor getBorderColor(const State state) const; // Return control border colors
			Color getBackgroundColor(const State state) const; // Return control background color
			Gradient *getBackgroundGradient(const State state); // Return control background gradient
			int getShadowRadius(const State state) const; // Return control shadow radius
			PointF getShadowShift(const State state) const; // Return control shadow shift
			Color getShadowColor(const State state) const; // Return control shadow color
			RectF getBackBorderWidth(const State state) const; // Return back part border widths
			RectF getBackBorderRadius(const State state) const; // Return back part corner radiuses
			BorderColor getBackBorderColor(const State state) const; // Return back part border colors
			Color getBackBackgroundColor(const State state) const; // Return back part background color
			Gradient *getBackBackgroundGradient(const State state); // Return back part background gradient
			RectF getTrackerBorderWidth(const State state) const; // Return tracker border widths
			RectF getTrackerBorderRadius(const State state) const; // Return tracker corner radiuses
			BorderColor getTrackerBorderColor(const State state) const; // Return tracker border colors
			Color getTrackerBackgroundColor(const State state) const; // Return tracker background color
			Gradient *getTrackerBackgroundGradient(const State state); // Return tracker background gradient
			Color getTickColor(const State state) const; // Return regular tick color
			Color getBigTickColor(const State state) const; // Return big tick color
			Color getOutlineColor(const State state) const; // Return outline color
			unsigned int getOutlineMask(const State state) const; // Return outline binary mask

			// Setters
			bool setTrackerStyle(const TrackerStyle value); // Set tracker style
			bool setBackPadding(const TrackerStyle style, const RectF &value); // Set back part padding
			bool setBackMargin(const TrackerStyle style, const float value); // Set distance from back part to ticks
			bool setTickSize(const TrackerStyle style, const PointF &value); // Set regular tick size
			bool setBigTickSize(const TrackerStyle style, const PointF &value); // Set big tick size
			bool setTrackerPadding(const TrackerStyle style, const PointF &value); // Set tracker padding
			bool setTrackerWidth(const TrackerStyle style, const float value); // Set tracker width
			bool setTickInterval(const int value); // Set interval of ticks to be drawn(<= 0 - no ticks will be drawn)
			bool setBigTickInterval(const int value); // Set interval of big tick(in count of small ones)
			bool setBorderWidth(const State state, const RectF &value); // Set control border widths
			bool setBorderRadius(const State state, const RectF &value); // Set control corner radiuses
			bool setBorderColor(const State state, const BorderColor &value); // Set control border colors
			bool setBackgroundColor(const State state, const Color &value); // Set control background color
			bool setShadowRadius(const State state, const int value); // Set control shadow radius
			bool setShadowShift(const State state, const PointF &value); // Set control shadow shift
			bool setShadowColor(const State state, const Color &value); // Set control shadow color
			bool setBackBorderWidth(const State state, const RectF &value); // Set back part border widths
			bool setBackBorderRadius(const State state, const RectF &value); // Set back part corner radiuses
			bool setBackBorderColor(const State state, const BorderColor &value); // Set back part border colors
			bool setBackBackgroundColor(const State state, const Color &value); // Set back part background color
			bool setTrackerBorderWidth(const State state, const RectF &value); // Set tracker border widths
			bool setTrackerBorderRadius(const State state, const RectF &value); // Set tracker corner radiuses
			bool setTrackerBorderColor(const State state, const BorderColor &value); // Set tracker border colors
			bool setTrackerBackgroundColor(const State state, const Color &value); // Set tracker background color
			bool setTickColor(const State state, const Color &value); // Set regular tick color
			bool setBigTickColor(const State state, const Color &value); // Set big tick color
			bool setOutlineColor(const State state, const Color &value); // Set outline color
			bool setOutlineMask(const State state, const unsigned int value); // Set outline binary mask
		};
	}
}
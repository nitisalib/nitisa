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
#include "Nitisa/Math/PointB.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../ITrackRange.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace standard
	{
		class CTrackRangeService;

		class CTrackRange :public virtual ITrackRange, public CControl
		{
			friend CTrackRangeService;
		public:
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
				Tracker1,
				Tracker2,
				Back
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CTrackRange *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CTrackRange *control);
			};
		private:
			CGradientListener m_cGradientListener;
			int m_iMin;
			int m_iMax;
			Point m_sValue;
			PointB m_sTrackerEnabled;
			PointB m_sTrackerVisible;
			RectF m_sBackPadding;
			float m_fBackMargin; // Distance to ticks
			PointF m_sTickSize;
			PointF m_sBigTickSize;
			PointF m_sTrackerPadding; // Top and bottom of control
			float m_fTrackerWidth;
			bool m_bTopTicksVisible;
			bool m_bBottomTicksVisible;
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
			Color m_aBackSelectionBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackSelectionBackgroundGradient[(int)State::Disabled + 1];
			// Tracker style
			RectF m_aTrackerBorderRadius[(int)State::Disabled + 1];
			RectF m_aTrackerOuterBorderWidth[(int)State::Disabled + 1];
			RectF m_aTrackerInnerBorderWidth[(int)State::Disabled + 1];
			BorderColor m_aTrackerOuterBorderColor[(int)State::Disabled + 1];
			BorderColor m_aTrackerInnerBorderColor[(int)State::Disabled + 1];
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
			Element m_eDownElement;

			void UpdateFromStyle(IStyle *style);
			State getTracker1State();
			State getTracker2State();
			RectF getTracker1Rect();
			RectF getTracker2Rect();
			RectF getBackRect();
			bool UpdateHoveredElement(const PointF &position);
			int ClientToValue(const PointF &position);
			void Render();
			void RenderBack(IRenderer *renderer, const RectF &rect, const State state);
			void RenderTicks(IRenderer *renderer, const RectF &rect, const State state);
			void RenderTrackers(IRenderer *renderer, const RectF &rect);
			void RenderTracker(IRenderer *renderer, const RectF &rect, const State state);
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
			Point getValue() override;
			PointB getTrackerEnabled() override;
			PointB getTrackerVisible() override;

			// ITrackBar setters
			bool setMin(const int value) override;
			bool setMax(const int value) override;
			bool setValue(const Point &value) override;
			bool setTrackerEnabled(const PointB &value) override;
			bool setTrackerVisible(const PointB &value) override;
			bool setValue1(const int value) override;
			bool setValue2(const int value) override;

			CTrackRange();
			CTrackRange(IForm *parent);
			CTrackRange(IControl *parent);

			// Getters
			State getState(); // Return current state
			RectF getBackPadding() const; // Return back part padding
			float getBackMargin() const; // Return distance from back part to ticks
			PointF getTickSize() const; // Return regular tick size
			PointF getBigTickSize() const; // Return big tick size
			PointF getTrackerPadding() const; // Return tracker padding
			float getTrackerWidth() const; // Return tracker width
			bool isTopTicksVisible() const; // Return whether top ticks are visible
			bool isBottomTicksVisible() const; // Return whether bottom ticks are visible
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
			Color getBackSelectionBackgroundColor(const State state) const; // Return back part selection background color
			Gradient *getBackSelectionBackgroundGradient(const State state); // Return back part selection background gradient
			RectF getTrackerBorderRadius(const State state) const; // Return tracker corner radiuses
			RectF getTrackerOuterBorderWidth(const State state) const; // Return tracker outer border width
			RectF getTrackerInnerBorderWidth(const State state) const; // Return tracker inner border width
			BorderColor getTrackerOuterBorderColor(const State state) const; // Return tracker outer border colors
			BorderColor getTrackerInnerBorderColor(const State state) const; // Return tracker inner border colors
			Color getTrackerBackgroundColor(const State state) const; // Return tracker background color
			Gradient *getTrackerBackgroundGradient(const State state); // Return tracker background gradient
			Color getTickColor(const State state) const; // Return regular tick color
			Color getBigTickColor(const State state) const; // Return big tick color
			Color getOutlineColor(const State state) const; // Return outline color
			unsigned int getOutlineMask(const State state) const; // Return outline binary mask

			// Setters
			bool setBackPadding(const RectF &value); // Set back part padding
			bool setBackMargin(const float value); // Set distance from back part to ticks
			bool setTickSize(const PointF &value); // Set regular tick size
			bool setBigTickSize(const PointF &value); // Set big tick size
			bool setTrackerPadding(const PointF &value); // Set tracker padding
			bool setTrackerWidth(const float value); // Set tracker width
			bool setTopTicksVisible(const bool value); // Set whether top ticks are visible
			bool setBottomTicksVisible(const bool value); // Set whether bottom ticks are visible
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
			bool setBackSelectionBackgroundColor(const State state, const Color &value); // Set back part selection background color
			bool setTrackerBorderRadius(const State state, const RectF &value); // Set tracker corner radiuses
			bool setTrackerOuterBorderWidth(const State state, const RectF &value); // Set tracker outer border width
			bool setTrackerInnerBorderWidth(const State state, const RectF &value); // Set tracker inner border width
			bool setTrackerOuterBorderColor(const State state, const BorderColor &value); // Set tracker outer border colors
			bool setTrackerInnerBorderColor(const State state, const BorderColor &value); // Set tracker inner border colors
			bool setTrackerBackgroundColor(const State state, const Color &value); // Set tracker background color
			bool setTickColor(const State state, const Color &value); // Set regular tick color
			bool setBigTickColor(const State state, const Color &value); // Set big tick color
			bool setOutlineColor(const State state, const Color &value); // Set outline color
			bool setOutlineMask(const State state, const unsigned int value); // Set outline binary mask
		};
	}
}
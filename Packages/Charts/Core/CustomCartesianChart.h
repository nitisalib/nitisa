// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Consts.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointB.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../Interfaces/ICartesianChart.h"

namespace nitisa
{
	class IFont;
	class IPlatformFont;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace charts
	{
		class IChartData;
		class IChartDataSet;

		class CCustomCartesianChartService;

		class CCustomCartesianChart :public virtual ICartesianChart, public CControl
		{
			friend CCustomCartesianChartService;
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CCustomCartesianChart *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CCustomCartesianChart *control);
			};
		protected:
			CGradientListener m_cGradientListener;
			IChartDataSet *m_pDataSet; // Assigned data set
			PointB m_sAutoGrid; // Automatic calculation of grid
			PointF m_sDefaultGridStep; // Default grid step(when scale is 1)
			PointB m_sShowAxes; // Whether axes are shown
			PointB m_sShowGrid; // Whether grid is shown
			Color m_sBackgroundColor; // Background color
			Gradient m_cBackgroundGradient; // Background gradient
			Color m_sXAxisColor; // X-axis color
			Color m_sYAxisColor; // Y-axis color
			Color m_sXGridColor; // Vertical grid color
			Color m_sYGridColor; // Horizontal grid color
			PointF m_sGridStep; // Grid steps
			PointF m_sLabelPadding; // Label paddings
			PointB m_sShowLabels; // Whether axes labels are shown
			bool m_bXLabelsAtTop; // Whether X-axis labels are at top or at bottom
			bool m_bYLabelsAtRight; // Whether Y-axis labels are at right or at left
			Point m_sLabelSigns; // Axes labels sign counts
			Color m_sXLabelsColor; // X-axis labels color
			Color m_sYLabelsColor; // Y-axis labels color
			PointF m_sAutoGridStep; // Grid step calculated automatically
			PointF m_sXRange; // Data X range
			PointF m_sYRange; // Data Y range
			PointB m_sAutoRange; // Whether data ranges are calculated automatically
			PointF m_sAutoXRange; // Automatically calculated data X range
			PointF m_sAutoYRange; // Automatically calculated data Y range
			float m_fPointSize; // Point size
			ITexture *m_pCanvas; // Canvas
			IChartData *m_pHoveredData; // Hovered data
			int m_iHoveredPoint; // Hovered point index
			bool m_bIgnoreGradient; // Whether a changes in gradient should be ignored

			virtual bool UpdateHoveredPoint(); // Update hovered point using curren mouse pointer coordinates
			virtual bool UpdateHoveredPoint(const PointF &position); // Update hovered point assuming mouse pointer is at specified position(in form coordinate space)
			virtual void UpdateAutoRanges(); // Update ranges and grids
			virtual void UpdateFromStyle(IStyle *style); // Update from style
			virtual void Render(); // Render all
			virtual void RenderBackground(IRenderer *renderer, const RectF &rect); // Render background only. Called by Render()
			virtual void RenderAxesAndGrid(IRenderer *renderer, const RectF &client, const PointF &xrange, const PointF &yrange, const PointF &grid_step); // Render axes and grids only. Called by Render()
			virtual void RenderLabels(IRenderer *renderer, const RectF &client, IFont *font, IPlatformFont *pf, const PointF &xrange, const PointF &yrange, const PointF &grid_step); // Render axes labels only. Called by Render()
			virtual void RenderDataSet(IRenderer *renderer, const RectF &client, const PointF &xrange, const PointF &yrange); // Render data set only

			virtual void RenderData(IRenderer *renderer, const RectF &client, IChartData *data, const int index, ITexture *target, const PointF &xrange, const PointF &yrange) = 0; // Render specified data only. Called by RenderDataSet()
		public:
			// IControl getters
			RectF getClientRect() override;

			// IControl setters
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			// ICartesianChart getters
			PointF getXRange() override;
			PointF getYRange() override;
			PointB getAutoRange() override;
			IChartDataSet *getDataSet() override;

			// ICartesianChart setters
			bool setXRange(const PointF &value) override;
			bool setYRange(const PointF &value) override;
			bool setAutoRange(const PointB &value) override;
			bool setDataSet(IChartDataSet *value, const bool release_old) override;

			// ICartesianChart methods
			void Update() override;

			CCustomCartesianChart(
				const String &class_name,
				const bool accept_form,
				const bool accept_control,
				const bool accept_controls,
				const bool accept_focus,
				const bool accept_modal,
				const bool tab_stop,
				const Point &design_dpi = DesignDPI);
			~CCustomCartesianChart() override;

			PointB getShowAxes() const; // Return whether axes should be shown
			PointB getShowGrid() const; // Return whether grid should be shown
			Color getBackgroundColor() const; // Return background color
			Gradient *getBackgroundGradient(); // Return background gradient
			Color getXAxisColor() const; // Return X-axis color
			Color getYAxisColor() const; // Return Y-axis color
			Color getXGridColor() const; // Return vertical grid color
			Color getYGridColor() const; // Return horizontal grid color
			PointF getGridStep() const; // Return grid step
			PointF getLabelPadding() const; // Return horizontal and vertical padding. In this area axes labels will be drawn
			PointB getShowLabels() const; // Return whether axes labels should be shown
			bool isXLabelsAtTop() const; // Return whether X-axis labels are at top or at bottom
			bool isYLabelsAtRight() const; // Return whether Y-axis labels are at right or at left
			Point getLabelSigns() const; // Return count of signs shown in axis labels when they are numbers(default)
			float getPointSize() const; // Return size of point used to detect whether mouse pointer is over a data point or not
			PointB getAutoGrid(); // Return whether the grid should be calculated automatically
			PointF getDefaultGridStep(); // Return default grid step(when scale is 1)

			bool setShowAxes(const PointB &value); // Set whether axes should be shown
			bool setShowGrid(const PointB &value); // Set whether grid should be shown
			bool setBackgroundColor(const Color &value); // Set background color
			bool setXAxisColor(const Color &value); // Set X-axis color
			bool setYAxisColor(const Color &value); // Set Y-axis color
			bool setXGridColor(const Color &value); // Set vertical grid color
			bool setYGridColor(const Color &value); // Set horizontal grid color
			bool setGridStep(const PointF &value); // Set grid step
			bool setLabelPadding(const PointF &value); // Set horizontal and vertical padding. In this area axes labels will be drawn
			bool setShowLabels(const PointB &value); // Set whether axes labels should be shown
			bool setXLabelsAtTop(const bool value); // Set whether X-axis labels are at top or at bottom
			bool setYLabelsAtRight(const bool value); // Set whether Y-axis labels are at right or at left
			bool setLabelSigns(const Point &value); // Set count of signs shown in axis labels when they are numbers(default). Should be in range 0..9
			bool setPointSize(const float value); // Set size of point used to detect whether mouse pointer is over a data point or not
			bool setAutoGrid(const PointB &value); // Set whether the grid should be calculated automatically
			bool setDefaultGridStep(const PointF &value); // Set default grid step(when scale is 1)
		};
	}
}
// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/DateTime.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointB.h"
#include "Nitisa/Math/PointD.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IForexChart.h"
#include <vector>

namespace nitisa
{
	class IFont;
	class IPlatformFont;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace charts
	{
		class CForexChartService;

		class CForexChart :public virtual IForexChart, public CControl
		{
			friend CForexChartService;
		public:
			class CForexChartData : public virtual IForexChartData // Default implementation of forex chart data
			{
			public:
				struct ChartData // Point structure
				{
					CDateTime DateTime; // Datetime
					float Open; // Open value
					float Close; // Close value
					float Min; // Minimum value
					float Max; // Maximum value
				};
			private:
				std::vector<ChartData> m_aData;
				CDateTime m_sNow;
			public:
				int getCount() override;
				const CDateTime &getDateTime(const int index) const override;
				float getOpen(const int index) override;
				float getClose(const int index) override;
				float getMin(const int index) override;
				float getMax(const int index) override;
				String getXLabel(const double x, const String &default_label) override;
				String getYLabel(const double y, const String &default_label) override;

				bool setDateTime(const int index, const CDateTime &value) override;
				bool setOpen(const int index, const float value) override;
				bool setClose(const int index, const float value) override;
				bool setMin(const int index, const float value) override;
				bool setMax(const int index, const float value) override;

				void Release() override;
				IForexChartData *Clone() override;

				bool Add(const CDateTime &datetime, const float open, const float close, const float min, const float max) override;
				bool Delete(const int index) override;
				bool Clear() override;

				CForexChartData(); // Create empty
				CForexChartData(const std::vector<ChartData> &data); // Create with specified points
				virtual ~CForexChartData() = default;
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CForexChart *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CForexChart *control);
			};
		private:
			CGradientListener m_cGradientListener;
			IForexChartData *m_pData;
			PointB m_sAutoGrid;
			PointD m_sDefaultGridStep;
			PointB m_sShowAxes;
			PointB m_sShowGrid;
			Color m_sBackgroundColor;
			Gradient m_cBackgroundGradient;
			Color m_sXAxisColor;
			Color m_sYAxisColor;
			Color m_sXGridColor;
			Color m_sYGridColor;
			PointD m_sGridStep;
			PointF m_sLabelPadding;
			PointB m_sShowLabels;
			bool m_bXLabelsAtTop;
			bool m_bYLabelsAtRight;
			Point m_sLabelSigns;
			Color m_sXLabelsColor;
			Color m_sYLabelsColor;
			PointD m_sAutoGridStep;
			PointD m_sXRange;
			PointD m_sYRange;
			PointB m_sAutoRange;
			PointD m_sAutoXRange;
			PointD m_sAutoYRange;
			float m_fBarWidth;
			Color m_sNormalPositiveBarBorderColor;
			Color m_sActivePositiveBarBorderColor;
			Color m_sNormalNegativeBarBorderColor;
			Color m_sActiveNegativeBarBorderColor;
			Color m_sNormalPositiveBarBackgroundColor;
			Color m_sActivePositiveBarBackgroundColor;
			Color m_sNormalNegativeBarBackgroundColor;
			Color m_sActiveNegativeBarBackgroundColor;
			bool m_bCandlestick;

			ITexture *m_pCanvas;
			int m_iHoveredPoint;
			bool m_bIgnoreGradient;
			long long m_iMinTime;

			void UpdateFromStyle(IStyle *style);
			bool UpdateHoveredPoint();
			bool UpdateHoveredPoint(const PointF &position);
			void UpdateAutoRanges();
			String XToTime(const long long x);
			double DataXToViewD(const double x, const PointD &xrange, const double view_width);
			double DataYToViewD(const double y, const PointD &yrange, const double view_height);
			void Render();
			void RenderBackground(IRenderer *renderer, const RectF &rect);
			void RenderAxesAndGrid(IRenderer *renderer, const RectF &client, const PointD &xrange, const PointD &yrange, const PointD &grid_step);
			void RenderLabels(IRenderer *renderer, const RectF &client, IFont *font, IPlatformFont *pf, const PointD &xrange, const PointD &yrange, const PointD &grid_step);
			void RenderDataSet(IRenderer *renderer, const RectF &client, const PointD &xrange, const PointD &yrange);
			void RenderData(IRenderer *renderer, ITexture *target, IForexChartData *data, const PointD &xrange, const PointD &yrange);
		public:
			// IControl getters
			RectF getClientRect() override;

			// IControl setters
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			// IForexChart getters
			PointD getXRange() override;
			PointD getYRange() override;
			PointB getAutoRange() override;
			IForexChartData *getData() override;

			// IForexChart setters
			bool setXRange(const PointD &value) override;
			bool setYRange(const PointD &value) override;
			bool setAutoRange(const PointB &value) override;
			bool setData(IForexChartData *value, const bool release_old) override;

			// IForexChart methods
			void Update() override;

			CForexChart();
			CForexChart(IForm *parent);
			CForexChart(IControl *parent);
			~CForexChart() override;

			PointB getShowAxes() const; // Return whether axes should be shown
			PointB getShowGrid() const; // Return whether grid should be shown
			Color getBackgroundColor() const; // Return background color
			Gradient *getBackgroundGradient(); // Return background gradient
			Color getXAxisColor() const; // Return X-axis color
			Color getYAxisColor() const; // Return Y-axis color
			Color getXGridColor() const; // Return vertical grid color
			Color getYGridColor() const; // Return horizontal grid color
			PointD getGridStep() const; // Return grid step
			PointF getLabelPadding() const; // Return horizontal and vertical padding. In this area axes labels will be drawn
			PointB getShowLabels() const; // Return whether axes labels should be shown
			bool isXLabelsAtTop() const; // Return whether X-axis labels are at top or at bottom
			bool isYLabelsAtRight() const; // Return whether Y-axis labels are at right or at left
			Point getLabelSigns() const; // Return count of signs shown in axis labels when they are numbers(default)
			Color getXLabelsColor() const; // Return X direction labels color
			Color getYLabelsColor() const; // Return Y direction labels color
			PointB getAutoGrid(); // Return whether the grid should be calculated automatically
			PointD getDefaultGridStep(); // Return default grid step(when scale is 1)
			float getBarWidth() const; // Return bar width
			Color getNormalPositiveBarBorderColor() const; // Return normal positive bar border color
			Color getActivePositiveBarBorderColor() const; // Return active positive bar border color
			Color getNormalNegativeBarBorderColor() const; // Return normal negative bar border color
			Color getActiveNegativeBarBorderColor() const; // Return active negative bar border color
			Color getNormalPositiveBarBackgroundColor() const; // Return normal positive bar background color
			Color getActivePositiveBarBackgroundColor() const; // Return active positive bar background color
			Color getNormalNegativeBarBackgroundColor() const; // Return normal negative bar background color
			Color getActiveNegativeBarBackgroundColor() const; // Return active negative bar background color
			bool isCandleStick() const; // Return whether draw bars in candlestick mode or not

			bool setShowAxes(const PointB &value); // Set whether axes should be shown
			bool setShowGrid(const PointB &value); // Set whether grid should be shown
			bool setBackgroundColor(const Color &value); // Set background color
			bool setXAxisColor(const Color &value); // Set X-axis color
			bool setYAxisColor(const Color &value); // Set Y-axis color
			bool setXGridColor(const Color &value); // Set vertical grid color
			bool setYGridColor(const Color &value); // Set horizontal grid color
			bool setGridStep(const PointD &value); // Set grid step
			bool setLabelPadding(const PointF &value); // Set horizontal and vertical padding. In this area axes labels will be drawn
			bool setShowLabels(const PointB &value); // Set whether axes labels should be shown
			bool setXLabelsAtTop(const bool value); // Set whether X-axis labels are at top or at bottom
			bool setYLabelsAtRight(const bool value); // Set whether Y-axis labels are at right or at left
			bool setLabelSigns(const Point &value); // Set count of signs shown in axis labels when they are numbers(default). Should be in range 0..9
			bool setXLabelsColor(const Color &value); // Set X direction labels color
			bool setYLabelsColor(const Color &value); // Set Y direction labels color
			bool setAutoGrid(const PointB &value); // Set whether the grid should be calculated automatically
			bool setDefaultGridStep(const PointD &value); // Set default grid step(when scale is 1)
			bool setBarWidth(const float value); // Set bar width
			bool setNormalPositiveBarBorderColor(const Color &value); // Set normal positive bar border color
			bool setActivePositiveBarBorderColor(const Color &value); // Set active positive bar border color
			bool setNormalNegativeBarBorderColor(const Color &value); // Set normal negative bar border color
			bool setActiveNegativeBarBorderColor(const Color &value); // Set active negative bar border color
			bool setNormalPositiveBarBackgroundColor(const Color &value); // Set normal positive bar background color
			bool setActivePositiveBarBackgroundColor(const Color &value); // Set active positive bar background color
			bool setNormalNegativeBarBackgroundColor(const Color &value); // Set normal negative bar background color
			bool setActiveNegativeBarBackgroundColor(const Color &value); // Set active negative bar background color
			bool setCandlestick(const bool value); // Set whether draw bars in candlestick mode or not
		};
	}
}
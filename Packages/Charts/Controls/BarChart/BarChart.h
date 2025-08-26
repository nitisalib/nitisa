// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Image/Color.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../../Core/BarChartRenderer.h"
#include "../../Core/CustomCartesianChart.h"
#include "../IBarChart.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace charts
	{
		class IChartData;

		class CBarChart :public virtual IBarChart, public CCustomCartesianChart
		{
		private:
			CBarChartRenderer *m_pRenderer;
		protected:
			bool UpdateHoveredPoint(const PointF &position) override;
			void UpdateFromStyle(IStyle *style) override;
			void RenderData(IRenderer *renderer, const RectF &client, IChartData *data, const int index, ITexture *target, const PointF &xrange, const PointF &yrange) override;
		public:
			// IControl setters
			bool setDPI(const Point &value) override;

			CBarChart();
			CBarChart(IForm *parent);
			CBarChart(IControl *parent);
			~CBarChart() override;

			bool isDrawBorder(const CBarChartRenderer::PointState state) const; // Return whether bar border should be drawn(depending on point state)
			bool isDrawBackground(const CBarChartRenderer::PointState state) const; // Return whether bar background should be drawn(depending on point state)
			float getBorderWidth(const CBarChartRenderer::PointState state) const; // Return bar border width depending on point state
			Color getBorderColor(const CBarChartRenderer::PointState state) const; // Return bar border color depending on point state
			Color getBackgroundColor(const CBarChartRenderer::PointState state) const; // Return bar background color depending on point state
			bool isVertical() const; // Return whether in vertical mode
			float getBarWidth() const; // Return bar width

			bool setDrawBorder(const CBarChartRenderer::PointState state, const bool value); // Set whether bar border should be drawn(depending on point state)
			bool setDrawBackground(const CBarChartRenderer::PointState state, const bool value); // Set whether bar background should be drawn(depending on point state)
			bool setBorderWidth(const CBarChartRenderer::PointState state, const float value); // Set bar border width depending on point state
			bool setBorderColor(const CBarChartRenderer::PointState state, const Color &value); // Set bar border color depending on point state
			bool setBackgroundColor(const CBarChartRenderer::PointState state, const Color &value); // Set bar background color depending on point state
			bool setVertical(const bool value); // Set whether in vertical mode
			bool setBarWidth(const float value); // Set bar width
		};
	}
}
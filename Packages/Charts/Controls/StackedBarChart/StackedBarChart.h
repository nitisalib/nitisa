// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Image/ColorArray.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../../Core/CustomCartesianChart.h"
#include "../IStackedBarChart.h"

namespace nitisa
{
	class IControl;
	class IFont;
	class IForm;
	class IPlatformFont;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace charts
	{
		class IChartData;

		class CStackedBarChart :public virtual IStackedBarChart, public CCustomCartesianChart
		{
		public:
			enum class PointState // Point states
			{
				Normal, // Normal
				Active // Mouse pointer is over the point
			};
		private:
			ColorArray m_aNormalBackgroundColors;
			ColorArray m_aActiveBackgroundColors;
			bool m_bVertical;
			float m_fBarSize;

			IChartData *FindBestData() const;
			void RenderAxesAndGridEx(IRenderer *renderer, const RectF &client, const PointF &xrange, const PointF &yrange, const PointF &grid_step, IChartData *best, const PointF &view_size);
			void RenderLabelsEx(IRenderer *renderer, const RectF &client, IFont *font, IPlatformFont *pf, const PointF &xrange, const PointF &yrange, const PointF &grid_step, IChartData *best, const PointF &view_size);
			void RenderDataSetEx(IRenderer *renderer, const RectF &client, const PointF &xrange, const PointF &yrange, IChartData *best, const PointF &view_size);
		protected:
			void UpdateFromStyle(IStyle *style) override;
			void UpdateAutoRanges() override;
			bool UpdateHoveredPoint(const PointF &position) override;
			void Render() override;
			void RenderBackground(IRenderer *renderer, const RectF &rect) override;
			void RenderData(IRenderer *renderer, const RectF &client, IChartData *data, const int index, ITexture *target, const PointF &xrange, const PointF &yrange) override;
		public:
			CStackedBarChart();
			CStackedBarChart(IForm *parent);
			CStackedBarChart(IControl *parent);

			bool isVertical() const; // Return whether in vertical mode
			float getBarSize() const; // Return bar size
			const ColorArray &getNormalBackgroundColors() const; // Return normal background colors
			const ColorArray &getActiveBackgroundColors() const; // Return active background colors

			bool setVertical(const bool value); // Set whether in vertical mode
			bool setBarSize(const float value); // Set bar size
			bool setNormalBackgroundColors(const ColorArray &values); // Set normal background colors
			bool setActiveBackgroundColors(const ColorArray &values); // Set active background colors
		};
	}
}
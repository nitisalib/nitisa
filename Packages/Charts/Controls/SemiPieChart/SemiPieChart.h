// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Image/ColorArray.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../../Core/CustomRadialChart.h"
#include "../ISemiPieChart.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IStyle;

	namespace charts
	{
		class IChartData;

		class CSemiPieChart :public virtual ISemiPieChart, public CCustomRadialChart
		{
		private:
			float m_fBorderWidth;
			float m_fQuality;
			bool m_bRestartColors;
			ColorArray m_aNormalColors;
			ColorArray m_aActiveColors;
			ColorArray m_aNormalBorderColors;
			ColorArray m_aActiveBorderColors;

			void RenderData(IRenderer *renderer, const PointF &center, const float r_outer, const float r_inner, IChartData *data, const int color_index);
			void RenderBorders(IRenderer *renderer, const PointF &center, const float r_outer, const float r_inner, IChartData *data, const int color_index);
		protected:
			bool UpdateHoveredPoint(const PointF &position) override;
			void UpdateFromStyle(IStyle *style) override;
			void RenderDataSet(IRenderer *renderer, const RectF &rect) override;
		public:
			// IControl setters
			bool setDPI(const Point &value) override;

			CSemiPieChart();
			CSemiPieChart(IForm *parent);
			CSemiPieChart(IControl *parent);

			float getBorderWidth() const; // Return border width
			float getQuality() const; // Return drawing quality(0..1)
			bool isRestartColors() const; // Return whether colors should be restarted at each data
			const ColorArray &getNormalColors() const; // Return normal colors
			const ColorArray &getActiveColors() const; // Return active colors
			const ColorArray &getNormalBorderColors() const; // Return normal border colors
			const ColorArray &getActiveBorderColors() const; // Return active border colors

			bool setBorderWidth(const float value); // Set border width
			bool setQuality(const float value); // Set drawing quality(0..1)
			bool setRestartColors(const bool value); // Set whether colors should be restarted at each data
			bool setNormalColors(const ColorArray &values); // Set normal colors
			bool setActiveColors(const ColorArray &values); // Set active colors
			bool setNormalBorderColors(const ColorArray &values); // Set normal border colors
			bool setActiveBorderColors(const ColorArray &values); // Set active border colors
		};
	}
}
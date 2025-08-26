// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/BoolArray.h"
#include "Nitisa/Image/ColorArray.h"
#include "Nitisa/Math/FloatArray.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../../Core/CustomCartesianChart.h"
#include "../../Core/Enums.h"
#include "../ISteppedLineChart.h"
#include <vector>

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IStyle;

	namespace charts
	{
		class IChartData;

		class CSteppedLineChartRenderer;

		class CSteppedLineChart :public virtual ISteppedLineChart, public CCustomCartesianChart
		{
		private:
			// Default chart drawing options
			BoolArray m_aChartDrawPoints;
			BoolArray m_aChartDrawLines;
			BoolArray m_aChartDrawBackgrounds;
			FloatArray m_aChartNormalPointSizes;
			FloatArray m_aChartActivePointSizes;
			FloatArray m_aChartNormalPointHoles;
			FloatArray m_aChartActivePointHoles;
			ColorArray m_aChartNormalPointColors;
			ColorArray m_aChartActivePointColors;
			ColorArray m_aChartNormalPointHoleColors;
			ColorArray m_aChartActivePointHoleColors;
			FloatArray m_aChartLineWidthes;
			ColorArray m_aChartLineColors;
			ColorArray m_aChartBackgroundColors;
			BoolArray m_aChartVerticals;
			std::vector<LineInterpolationPosition> m_aChartInterpolationPositions;

			CSteppedLineChartRenderer *m_pRenderer;
		protected:
			void UpdateFromStyle(IStyle *style) override;
			void RenderData(IRenderer *renderer, const RectF &client, IChartData *data, const int index, ITexture *target, const PointF &xrange, const PointF &yrange) override;
		public:
			// IControl setters
			bool setDPI(const Point &value) override;

			CSteppedLineChart();
			CSteppedLineChart(IForm *parent);
			CSteppedLineChart(IControl *parent);
			~CSteppedLineChart() override;

			const BoolArray &getChartDrawPoints() const; // Return whether points should be drawn
			const BoolArray &getChartDrawLines() const; // Return whether lines should be drawn
			const BoolArray &getChartDrawBackgrounds() const; // Return whether backgrounds should be drawn
			const FloatArray &getChartNormalPointSizes() const; // Return normal point sizes
			const FloatArray &getChartActivePointSizes() const; // Return active point sizes
			const FloatArray &getChartNormalPointHoles() const; // Return normal point hole sizes
			const FloatArray &getChartActivePointHoles() const; // Return active point hole sizes
			const ColorArray &getChartNormalPointColors() const; // Return normal point colors
			const ColorArray &getChartActivePointColors() const; // Return active point colors
			const ColorArray &getChartNormalPointHoleColors() const; // Return normal point hole colors
			const ColorArray &getChartActivePointHoleColors() const; // Return active point hole colors
			const FloatArray &getChartLineWidthes() const; // Return line widthes
			const ColorArray &getChartLineColors() const; // Return line colors
			const ColorArray &getChartBackgroundColors() const; // Return background colors
			const BoolArray &getChartVerticals() const; // Return whether draw in vertical mode
			const std::vector<LineInterpolationPosition> &getChartInterpolationPositions() const; // Return line interpolation positions

			bool setChartDrawPoints(const BoolArray &values); // Set whether points should be drawn
			bool setChartDrawLines(const BoolArray &values); // Set whether lines should be drawn
			bool setChartDrawBackgrounds(const BoolArray &values); // Set whether backgrounds should be drawn
			bool setChartNormalPointSizes(const FloatArray &values); // Set normal point sizes
			bool setChartActivePointSizes(const FloatArray &values); // Set active point sizes
			bool setChartNormalPointHoles(const FloatArray &values); // Set normal point hole sizes
			bool setChartActivePointHoles(const FloatArray &values); // Set active point hole sizes
			bool setChartNormalPointColors(const ColorArray &values); // Set normal point colors
			bool setChartActivePointColors(const ColorArray &values); // Set active point colors
			bool setChartNormalPointHoleColors(const ColorArray &values); // Set normal point hole colors
			bool setChartActivePointHoleColors(const ColorArray &values); // Set active point hole colors
			bool setChartLineWidthes(const FloatArray &values); // Set line widthes
			bool setChartLineColors(const ColorArray &values); // Set line colors
			bool setChartBackgroundColors(const ColorArray &values); // Set background colors
			bool setChartVerticals(const BoolArray &values); // Set whether draw in vertical mode
			bool setChartInterpolationPositions(const std::vector<LineInterpolationPosition> &values); // Set line interpolation positions
		};
	}
}
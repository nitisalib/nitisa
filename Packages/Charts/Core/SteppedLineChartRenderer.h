// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Image/Color.h"
#include "Nitisa/Math/PointF.h"
#include "../Interfaces/IChartRenderer.h"
#include "Enums.h"
#include <vector>

namespace nitisa
{
	class IRenderer;
	class ITexture;

	namespace charts
	{
		class IChartData;

		class CSteppedLineChartRenderer :public virtual IChartRenderer
		{
		public:
			enum class PointState // Point states
			{
				Normal, // Normal
				Active // Mouse pointer is over the point
			};
		private:
			struct POINT_DATA
			{
				PointF P1;
				PointF P2;
				PointF P0;
			};
		private:
			bool m_bDrawPoints;
			bool m_bDrawLine;
			bool m_bDrawBackground;
			float m_aPointSize[(int)PointState::Active + 1];
			float m_aPointHole[(int)PointState::Active + 1];
			Color m_aPointColor[(int)PointState::Active + 1];
			Color m_aPointHoleColor[(int)PointState::Active + 1];
			float m_fLineWidth;
			Color m_sLineColor;
			Color m_sBackgroundColor;
			int m_iActivePoint;
			bool m_bVertical;
			LineInterpolationPosition m_eInterpolationPosition;

			void TransformBeforeH(IChartData *data, const PointF &xrange, const PointF &yrange, const PointF &view_size, std::vector<POINT_DATA> &point_data);
			void TransformMiddleH(IChartData *data, const PointF &xrange, const PointF &yrange, const PointF &view_size, std::vector<POINT_DATA> &point_data);
			void TransformAfterH(IChartData *data, const PointF &xrange, const PointF &yrange, const PointF &view_size, std::vector<POINT_DATA> &point_data);
			void TransformBeforeV(IChartData *data, const PointF &xrange, const PointF &yrange, const PointF &view_size, std::vector<POINT_DATA> &point_data);
			void TransformMiddleV(IChartData *data, const PointF &xrange, const PointF &yrange, const PointF &view_size, std::vector<POINT_DATA> &point_data);
			void TransformAfterV(IChartData *data, const PointF &xrange, const PointF &yrange, const PointF &view_size, std::vector<POINT_DATA> &point_data);
			void CalculatePointData(std::vector<POINT_DATA> &point_data);
			void RenderPoints(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange);
			void RenderSpline(IRenderer *renderer, std::vector<POINT_DATA> &point_data);
			void RenderBackgroundV(IRenderer *renderer, const PointF &view_size, IChartData *data, const PointF &xrange, const PointF &yrange, const std::vector<POINT_DATA> &point_data);
			void RenderBackgroundH(IRenderer *renderer, const PointF &view_size, IChartData *data, const PointF &xrange, const PointF &yrange, const std::vector<POINT_DATA> &point_data);
		public:
			void Release() override;
			void Render(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange) override;

			CSteppedLineChartRenderer();
			virtual ~CSteppedLineChartRenderer() = default;

			bool isDrawPoints() const; // Return whether points should be drawn
			bool isDrawLine() const; // Return whether lines should be drawn
			bool isDrawBackground() const; // Return whether background should be drawn
			float getPointSize(const PointState state) const; // Return point size depending on state
			float getPointHole(const PointState state) const; // Return point hole size depending on state
			Color getPointColor(const PointState state) const; // Return point color depending on state
			Color getPointHoleColor(const PointState state) const; // Return point hole color depending on state
			float getLineWidth() const; // Return line width
			Color getLineColor() const; // Return line color
			Color getBackgroundColor() const; // Return background color
			int getActivePoint() const; // Return index of active(hovered) point
			bool isVertical() const; // Return whether drawing should be vertical
			LineInterpolationPosition getInterpolationPosition() const; // Return line interpolation position

			bool setDrawPoints(const bool value); // Set whether points should be drawn
			bool setDrawLine(const bool value); // Set whether lines should be drawn
			bool setDrawBackground(const bool value); // Set whether background should be drawn
			bool setPointSize(const PointState state, const float value); // Set point size depending on state
			bool setPointHole(const PointState state, const float value); // Set point hole size depending on state
			bool setPointColor(const PointState state, const Color &value); // Set point color depending on state
			bool setPointHoleColor(const PointState state, const Color &value); // Set point hole color depending on state
			bool setLineWidth(const float value); // Set line width
			bool setLineColor(const Color &value); // Set line color
			bool setBackgroundColor(const Color &value); // Set background color
			bool setActivePoint(const int value); // Set index of active(hovered) point
			bool setVertical(const bool value); // Set whether drawing should be vertical
			bool setInterpolationPosition(const LineInterpolationPosition value); // Set line interpolation position
		};
	}
}
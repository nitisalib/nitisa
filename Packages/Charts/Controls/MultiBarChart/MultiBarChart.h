// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
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
#include "../IMultiBarChart.h"

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

		class CMultiBarChart :public virtual IMultiBarChart, public CCustomCartesianChart
		{
		public:
			enum class PointState // Point states
			{
				Normal, // Normal
				Active // Mouse pointer is over the point
			};
		private:
			BoolArray m_aDrawNormalBorders;
			BoolArray m_aDrawActiveBorders;
			BoolArray m_aDrawNormalBackgrounds;
			BoolArray m_aDrawActiveBackgrounds;
			FloatArray m_aNormalBorderWidthes;
			FloatArray m_aActiveBorderWidthes;
			ColorArray m_aNormalBorderColors;
			ColorArray m_aActiveBorderColors;
			ColorArray m_aNormalBackgroundColors;
			ColorArray m_aActiveBackgroundColors;
			bool m_bVertical;
			float m_fContentSize;
			float m_fBarDistance;

			IChartData *FindBestData() const;
			void RenderAxesAndGridEx(IRenderer *renderer, const RectF &client, const PointF &xrange, const PointF &yrange, const PointF &grid_step, IChartData *best, const PointF &view_size);
			void RenderLabelsEx(IRenderer *renderer, const RectF &client, IFont *font, IPlatformFont *pf, const PointF &xrange, const PointF &yrange, const PointF &grid_step, IChartData *best, const PointF &view_size);
			void RenderDataSetEx(IRenderer *renderer, const RectF &client, const PointF &xrange, const PointF &yrange, IChartData *best, const PointF &view_size);
		protected:
			void UpdateFromStyle(IStyle *style) override;
			bool UpdateHoveredPoint(const PointF &position) override;
			void Render() override;
			void RenderBackground(IRenderer *renderer, const RectF &rect) override;
			void RenderData(IRenderer *renderer, const RectF &client, IChartData *data, const int index, ITexture *target, const PointF &xrange, const PointF &yrange) override;
		public:
			// IControl setters
			bool setDPI(const Point &value) override;

			CMultiBarChart();
			CMultiBarChart(IForm *parent);
			CMultiBarChart(IControl *parent);

			bool isVertical() const; // Return whether drawing should be vertical
			float getContentSize() const; // Return content size(0..1)
			float getBarDistance() const; // Return distance between bars relative to bar size(0..1)
			const BoolArray &getDrawNormalBorders() const; // Return whether normal bar borders should be drawn
			const BoolArray &getDrawActiveBorders() const; // Return whether active bar borders should be drawn
			const BoolArray &getDrawNormalBackgrounds() const; // Return whether normal bar backgrounds should be drawn
			const BoolArray &getDrawActiveBackgrounds() const; // Return whether active bar backgrounds should be drawn
			const FloatArray &getNormalBorderWidthes() const; // Return normal bar border widthes
			const FloatArray &getActiveBorderWidthes() const; // Return active bar border widthes
			const ColorArray &getNormalBorderColors() const; // Return normal bar border colors
			const ColorArray &getActiveBorderColors() const; // Return active bar border colors
			const ColorArray &getNormalBackgroundColors() const; // Return normal bar background colors
			const ColorArray &getActiveBackgroundColors() const; // Return active bar background colors

			bool setVertical(const bool value); // Set whether drawing should be vertical
			bool setContentSize(const float value); // Set content size(0..1)
			bool setBarDistance(const float value); // Set distance between bars relative to bar size(0..1)
			bool setDrawNormalBorders(const BoolArray &values); // Set whether normal bar borders should be drawn
			bool setDrawActiveBorders(const BoolArray &values); // Set whether active bar borders should be drawn
			bool setDrawNormalBackgrounds(const BoolArray &values); // Set whether normal bar backgrounds should be drawn
			bool setDrawActiveBackgrounds(const BoolArray &values); // Set whether active bar backgrounds should be drawn
			bool setNormalBorderWidthes(const FloatArray &values); // Set normal bar border widthes
			bool setActiveBorderWidthes(const FloatArray &values); // Set active bar border widthes
			bool setNormalBorderColors(const ColorArray &values); // Set normal bar border colors
			bool setActiveBorderColors(const ColorArray &values); // Set active bar border colors
			bool setNormalBackgroundColors(const ColorArray &values); // Set normal bar background colors
			bool setActiveBackgroundColors(const ColorArray &values); // Set active bar background colors
		};
	}
}
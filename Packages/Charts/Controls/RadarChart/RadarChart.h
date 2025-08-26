// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/BoolArray.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/ColorArray.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/FloatArray.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IRadarChart.h"

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
		class IChartDataSet;

		class CRadarChartService;

		class CRadarChart :public virtual IRadarChart, public CControl
		{
			friend CRadarChartService;
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CRadarChart *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CRadarChart *control);
			};
		private:
			CGradientListener m_cGradientListener;
			IChartDataSet *m_pDataSet;
			bool m_bAutoRange;
			float m_fRange;
			float m_fAutoRange;
			Color m_sBackgroundColor;
			Gradient m_cBackgroundGradient;
			bool m_bDrawGrid;
			bool m_bAutoGridStep;
			float m_fGridStep;
			float m_fDefaultGridStep;
			float m_fAutoGridStep;
			Color m_sGridColor;
			bool m_bDrawLabels;
			Color m_sLabelsColor;
			int m_iLabelSigns;
			float m_fQuality;
			RectF m_sPadding;
			float m_fPointSize;
			bool m_bDrawLegend;
			Color m_sLegendColor;
			ColorArray m_aBackgroundColors;
			FloatArray m_aLineWidthes;
			ColorArray m_aLineColors;
			FloatArray m_aNormalPointSizes;
			FloatArray m_aActivePointSizes;
			FloatArray m_aNormalPointHoles;
			FloatArray m_aActivePointHoles;
			ColorArray m_aNormalPointColors;
			ColorArray m_aActivePointColors;
			ColorArray m_aNormalHoleColors;
			ColorArray m_aActiveHoleColors;
			BoolArray m_aDrawPoints;

			ITexture *m_pCanvas;
			bool m_bIgnoreGradient;
			IChartData *m_pHoveredData;
			int m_iHoveredPoint;

			void UpdateFromStyle(IStyle *style);
			bool UpdateHoveredPoint();
			bool UpdateHoveredPoint(const PointF &position);
			IChartData *FindBestData() const;
			void UpdateAutoRanges();
			void Render();
			void RenderBackground(IRenderer *renderer, const RectF &client);
			void RenderGrid(IRenderer *renderer, const PointF &center, const float radius, const float grid_step, IChartData *best);
			void RenderLabels(IRenderer *renderer, const PointF &center, const float radius, const float grid_step, const float scale, IPlatformFont *pf, IFont *f);
			void RenderLegends(IRenderer *renderer, const PointF &center, const float radius, IPlatformFont *pf, IFont *f, IChartData *best);
			void RenderBackgrounds(IRenderer *renderer, const PointF &center, const float radius, const float scale, IChartData *data, const int index, IChartData *best);
			void RenderLines(IRenderer *renderer, const PointF &center, const float radius, const float scale, IChartData *data, const int index, IChartData *best);
			void RenderPoints(IRenderer *renderer, const PointF &center, const float radius, const float scale, IChartData *data, const int index, IChartData *best);
		public:
			// IControl getters
			RectF getClientRect() override;

			// IControl setters
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			// IRadialChart getters
			IChartDataSet *getDataSet() override;

			// IRadialChart setters
			bool setDataSet(IChartDataSet *value, const bool release_old) override;

			// IRadialChart methods
			void Update() override;

			// IRadarChart getters
			bool isAutoRange() override;
			float getRange() override;

			// IRadarChart setters
			bool setAutoRange(const bool value) override;
			bool setRange(const float value) override;

			CRadarChart();
			CRadarChart(IForm *parent);
			CRadarChart(IControl *parent);
			~CRadarChart() override;

			Color getBackgroundColor() const; // Return background color
			Gradient *getBackgroundGradient(); // Return background gradient
			bool isDrawGrid() const; // Return whether a grid should be drawn
			bool isAutoGridStep() const; // Return whether grid step should be calculated automatically
			float getGridStep() const; // Return grid step
			float getDefaultGridStep() const; // Return default grid step(when scale is 1)
			Color getGridColor() const; // Return grid color
			bool isDrawLabels() const; // Return whether labels should be drawn
			Color getLabelsColor() const; // Return labels color
			int getLabelSigns() const; // Return count of signs after point in labels(0..9)
			float getQuality() const; // Return quality(0..1)
			RectF getPadding() const; // Return padding
			float getPointSize() const; // Return point size
			bool isDrawLegend() const; // Return whether legend should be drawn
			Color getLegendColor() const; // Return legend color
			const ColorArray &getBackgroundColors() const; // Return background colors
			const FloatArray &getLineWidthes() const; // Return line widthes
			const ColorArray &getLineColors() const; // Return line colors
			const FloatArray &getNormalPointSizes() const; // Return normal point sizes
			const FloatArray &getActivePointSizes() const; // Return active point sizes
			const FloatArray &getNormalPointHoles() const; // Return normal point hole sizes
			const FloatArray &getActivePointHoles() const; // Return active point hole sizes
			const ColorArray &getNormalPointColors() const; // Return normal point colors
			const ColorArray &getActivePointColors() const; // Return active point colors
			const ColorArray &getNormalHoleColors() const; // Return normal point hole colors
			const ColorArray &getActiveHoleColors() const; // Return active point hole colors
			const BoolArray &getDrawPoints() const; // Return whether points should be drawn

			bool setBackgroundColor(const Color &value); // Set background color
			bool setDrawGrid(const bool value); // Set whether a grid should be drawn
			bool setAutoGridStep(const bool value); // Set whether grid step should be calculated automatically
			bool setGridStep(const float value); // Set grid step
			bool setDefaultGridStep(const float value); // Set default grid step(when scale is 1)
			bool setGridColor(const Color &value); // Set grid color
			bool setDrawLabels(const bool value); // Set whether labels should be drawn
			bool setLabelsColor(const Color &value); // Set labels color
			bool setLabelSigns(const int value); // Set count of signs after point in labels(0..9)
			bool setQuality(const float value); // Set quality(0..1)
			bool setPadding(const RectF &value); // Set padding
			bool setPointSize(const float value); // Set point size
			bool setDrawLegend(const bool value); // Set whether legend should be drawn
			bool setLegendColor(const Color &value); // Set legend color
			bool setBackgroundColors(const ColorArray &values); // Set background colors
			bool setLineWidthes(const FloatArray &values); // Set line widthes
			bool setLineColors(const ColorArray &values); // Set line colors
			bool setNormalPointSizes(const FloatArray &values); // Set normal point sizes
			bool setActivePointSizes(const FloatArray &values); // Set active point sizes
			bool setNormalPointHoles(const FloatArray &values); // Set normal point hole sizes
			bool setActivePointHoles(const FloatArray &values); // Set active point hole sizes
			bool setNormalPointColors(const ColorArray &values); // Set normal point colors
			bool setActivePointColors(const ColorArray &values); // Set active point colors
			bool setNormalHoleColors(const ColorArray &values); // Set normal point hole colors
			bool setActiveHoleColors(const ColorArray &values); // Set active point hole colors
			bool setDrawPoints(const BoolArray &values); // Set whether points should be drawn
		};
	}
}
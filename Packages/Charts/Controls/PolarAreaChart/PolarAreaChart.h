// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Control.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/ColorArray.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IPolarAreaChart.h"

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

		class CPolarAreaChartService;

		class CPolarAreaChart :public virtual IPolarAreaChart, public CControl
		{
			friend CPolarAreaChartService;
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CPolarAreaChart *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CPolarAreaChart *control);
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
			float m_fBorderWidth;
			float m_fQuality;
			int m_iLabelSigns;
			ColorArray m_aNormalColors;
			ColorArray m_aActiveColors;
			ColorArray m_aNormalBorderColors;
			ColorArray m_aActiveBorderColors;

			ITexture *m_pCanvas;
			bool m_bIgnoreGradient;
			int m_iHoveredPoint;

			void UpdateFromStyle(IStyle *style);
			bool UpdateHoveredPoint();
			bool UpdateHoveredPoint(const PointF &position);
			void UpdateAutoRanges();
			void Render();
			void RenderBackground(IRenderer *renderer, const RectF &client);
			void RenderGrid(IRenderer *renderer, const PointF &center, const float radius, const float grid_step);
			void RenderLabels(IRenderer *renderer, const PointF &center, const float radius, const float grid_step, const float scale, IPlatformFont *pf, IFont *f);
			void RenderData(IRenderer *renderer, const PointF &center, const float radius, const float scale, IChartData *data);
			void RenderBorders(IRenderer *renderer, const PointF &center, const float radius, const float scale, IChartData *data);
		public:
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

			// IPolarAreaChart getters
			bool isAutoRange() override;
			float getRange() override;

			// IPolarAreaChart setters
			bool setAutoRange(const bool value) override;
			bool setRange(const float value) override;

			CPolarAreaChart();
			CPolarAreaChart(IForm *parent);
			CPolarAreaChart(IControl *parent);
			~CPolarAreaChart() override;

			Color getBackgroundColor() const; // Return background color
			Gradient *getBackgroundGradient(); // Return background gradient
			bool isDrawGrid() const; // Return whether a grid should be drawn
			bool isAutoGridStep() const; // Return whether grid step should be calculated automatically
			float getGridStep() const; // Return grid step
			float getDefaultGridStep() const; // Return default grid step(when scale is 1)
			Color getGridColor() const; // Return grid color
			bool isDrawLabels() const; // Return whether labels should be drawn
			Color getLabelsColor() const; // Return labels color
			float getBorderWidth() const; // Return border width
			float getQuality() const; // Return quality(0..1)
			int getLabelSigns() const; // Return count of signs after point in labels(0..9)
			const ColorArray &getNormalColors() const; // Return normal colors
			const ColorArray &getActiveColors() const; // Return active colors
			const ColorArray &getNormalBorderColors() const; // Return normal border colors
			const ColorArray &getActiveBorderColors() const; // Return active border colors

			bool setBackgroundColor(const Color &value); // Set background color
			bool setDrawGrid(const bool value); // Set whether a grid should be drawn
			bool setAutoGridStep(const bool value); // Set whether grid step should be calculated automatically
			bool setGridStep(const float value); // Set grid step
			bool setDefaultGridStep(const float value); // Set default grid step(when scale is 1)
			bool setGridColor(const Color &value); // Set grid color
			bool setDrawLabels(const bool value); // Set whether labels should be drawn
			bool setLabelsColor(const Color &value); // Set labels color
			bool setBorderWidth(const float value); // Set border width
			bool setQuality(const float value); // Set quality(0..1)
			bool setLabelSigns(const int value); // Set count of signs after point in labels(0..9)
			bool setNormalColors(const ColorArray &values); // Set normal colors
			bool setActiveColors(const ColorArray &values); // Set active colors
			bool setNormalBorderColors(const ColorArray &values); // Set normal border colors
			bool setActiveBorderColors(const ColorArray &values); // Set active border colors
		};
	}
}
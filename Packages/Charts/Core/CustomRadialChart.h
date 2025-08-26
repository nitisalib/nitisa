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
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../Interfaces/IRadialChart.h"

namespace nitisa
{
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace charts
	{
		class IChartData;
		class IChartDataSet;

		class CCustomRadialChartService;

		class CCustomRadialChart :public virtual IRadialChart, public CControl
		{
			friend CCustomRadialChartService;
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CCustomRadialChart *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CCustomRadialChart *control);
			};
		protected:
			CGradientListener m_cGradientListener;
			IChartDataSet *m_pDataSet; // Data set
			Color m_sBackgroundColor; // Background color
			Gradient m_cBackgroundGradient; // Background gradient

			ITexture *m_pCanvas; // Canvas
			IChartData *m_pHoveredData; // Hovered data
			int m_iHoveredPoint; // Hovered point index
			bool m_bIgnoreGradient; // Whether gradient changes should be ignored

			virtual bool UpdateHoveredPoint(); // Update hovered point using curren mouse pointer coordinates
			virtual bool UpdateHoveredPoint(const PointF &position) = 0; // Update hovered point assuming mouse pointer is at specified position(in form coordinate space)
			virtual void UpdateFromStyle(IStyle *style); // Update from style
			virtual void Render(); // Render all
			virtual void RenderBackground(IRenderer *renderer, const RectF &rect); // Render background only. Called by Render()
			virtual void RenderDataSet(IRenderer *renderer, const RectF &rect) = 0; // Render data set only
		public:
			// IControl methods
			void Refresh(const bool refresh_children) override;

			// IRadialChart getters
			IChartDataSet *getDataSet() override;

			// IRadialChart setters
			bool setDataSet(IChartDataSet *value, const bool release_old) override;

			// IRadialChart methods
			void Update() override;

			CCustomRadialChart(
				const String &class_name,
				const bool accept_form,
				const bool accept_control,
				const bool accept_controls,
				const bool accept_focus,
				const bool accept_modal,
				const bool tab_stop,
				const Point &design_dpi = DesignDPI);
			~CCustomRadialChart() override;

			Color getBackgroundColor() const; // Return background color
			Gradient *getBackgroundGradient(); // Return background gradient

			bool setBackgroundColor(const Color &value); // Set background color
		};
	}
}
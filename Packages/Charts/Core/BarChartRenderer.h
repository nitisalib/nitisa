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

namespace nitisa
{
	class IRenderer;
	class ITexture;

	namespace charts
	{
		class IChartData;

		class CBarChartRenderer :public virtual IChartRenderer
		{
		public:
			enum class PointState // Point states
			{
				Normal, // Normal
				Active // Mouse pointer is over the point
			};
		private:
			bool m_aDrawBorder[(int)PointState::Active + 1];
			bool m_aDrawBackground[(int)PointState::Active + 1];
			float m_aBorderWidth[(int)PointState::Active + 1];
			Color m_aBorderColor[(int)PointState::Active + 1];
			Color m_aBackgroundColor[(int)PointState::Active + 1];
			int m_iActivePoint;
			bool m_bVertical;
			float m_fBarWidth;

			void RenderBarsH(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange);
			void RenderBarsV(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange);
		public:
			void Release() override;
			void Render(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange) override;

			CBarChartRenderer();
			virtual ~CBarChartRenderer() = default;

			bool isDrawBorder(const PointState state) const; // Return whether borders should be drawn or not(depending on state)
			bool isDrawBackground(const PointState state) const; // Return whether background should be drawn or not(depending on state)
			float getBorderWidth(const PointState state) const; // Return borders width depending on state
			Color getBorderColor(const PointState state) const; // Return borders color depending on state
			Color getBackgroundColor(const PointState state) const; // Return background color depending on state
			int getActivePoint() const; // Return index of active(hovered) point
			bool isVertical() const; // Return whether drawing should be vertical
			float getBarWidth() const; // Return bar width

			bool setDrawBorder(const PointState state, const bool value); // Set whether borders should be drawn or not(depending on state)
			bool setDrawBackground(const PointState state, const bool value); // Set whether background should be drawn or not(depending on state)
			bool setBorderWidth(const PointState state, const float value); // Set borders width depending on state
			bool setBorderColor(const PointState state, const Color &value); // Set borders color depending on state
			bool setBackgroundColor(const PointState state, const Color &value); // Set background color depending on state
			bool setActivePoint(const int value); // Set index of active(hovered) point
			bool setVertical(const bool value); // Set whether drawing should be vertical
			bool setBarWidth(const float value); // Set bar width
		};
	}
}
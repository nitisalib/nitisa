// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Math/PointF.h"

namespace nitisa
{
	class IRenderer;
	class ITexture;
	
	namespace charts
	{
		class IChartData;

		class IChartRenderer
		{
		protected:
			IChartRenderer() = default;
			~IChartRenderer() = default;
			IChartRenderer(const IChartRenderer &other) = delete;
			IChartRenderer(IChartRenderer &&other) = delete;
			IChartRenderer &operator=(const IChartRenderer &other) = delete;
			IChartRenderer &operator=(IChartRenderer &&other) = delete;
		public:
			virtual void Release() = 0; // Destroy
			virtual void Render(IRenderer *renderer, ITexture *texture, IChartData *data, const PointF &xrange, const PointF &yrange) = 0; // Render specified data. Texture is already set as render target(no need to set is as render target again)
		};
	}
}
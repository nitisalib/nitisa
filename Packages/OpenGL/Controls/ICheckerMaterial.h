// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Image/Color.h"
#include "Nitisa/Math/PointF.h"
#include "../Interfaces/IMaterialControl.h"

namespace nitisa
{
	namespace opengl
	{
		class ICheckerMaterial :public virtual IMaterialControl
		{
		protected:
			ICheckerMaterial() = default;
			~ICheckerMaterial() = default;
			ICheckerMaterial(const ICheckerMaterial &other) = delete;
			ICheckerMaterial(ICheckerMaterial &&other) = delete;
			ICheckerMaterial &operator=(const ICheckerMaterial &other) = delete;
			ICheckerMaterial &operator=(ICheckerMaterial &&other) = delete;
		public:
			virtual Color getColor1() = 0; // Return first color
			virtual Color getColor2() = 0; // Return second color
			virtual PointF getScale() = 0; // Return checker texture scale factor

			virtual bool setColor1(const Color &value) = 0; // Set first color
			virtual bool setColor2(const Color &value) = 0; // Set second color
			virtual bool setScale(const PointF &value) = 0; // Set checker texture scale factor
		};
	}
}
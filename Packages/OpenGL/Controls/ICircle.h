// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/I3DControl.h"

namespace nitisa
{
	namespace opengl
	{
		class ICircle :public virtual I3DControl
		{
		protected:
			ICircle() = default;
			~ICircle() = default;
			ICircle(const ICircle &other) = delete;
			ICircle(ICircle &&other) = delete;
			ICircle &operator=(const ICircle &other) = delete;
			ICircle &operator=(ICircle &&other) = delete;
		public:
			virtual float getCircleRadius() = 0; // Return circle radius
			virtual int getCircleSides() = 0; // Return side count
			virtual int getCapSegments() = 0; // Return cap segment count

			virtual bool setCircleRadius(const float value) = 0; // Set circle radius
			virtual bool setCircleSides(const int value) = 0; // Set side count
			virtual bool setCircleSize(const float radius, const int sides) = 0; // Set radius and side count
			virtual bool setCapSegments(const int value) = 0; // Set cap segment count
		};
	}
}
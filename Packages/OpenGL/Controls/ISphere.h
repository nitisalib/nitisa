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
		class ISphere :public virtual I3DControl
		{
		protected:
			ISphere() = default;
			~ISphere() = default;
			ISphere(const ISphere &other) = delete;
			ISphere(ISphere &&other) = delete;
			ISphere &operator=(const ISphere &other) = delete;
			ISphere &operator=(ISphere &&other) = delete;
		public:
			virtual float getSphereRadius() = 0; // Return sphere radius
			virtual int getSphereSides() = 0; // Return side count
			virtual int getSphereYSides() = 0; // Return side count in vertical direction

			virtual bool setSphereRadius(const float value) = 0; // Set sphere radius
			virtual bool setSphereSides(const int value) = 0; // Set side count
			virtual bool setSphereYSides(const int value) = 0; // Set side count in vertical direction
			virtual bool setSphereSize(const float radius, const int sides, const int y_sides) = 0; // Set sphere radius and side count in horizontal and vertical directions
		};
	}
}
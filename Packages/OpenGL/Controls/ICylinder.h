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
		class ICylinder :public virtual I3DControl
		{
		protected:
			ICylinder() = default;
			~ICylinder() = default;
			ICylinder(const ICylinder &other) = delete;
			ICylinder(ICylinder &&other) = delete;
			ICylinder &operator=(const ICylinder &other) = delete;
			ICylinder &operator=(ICylinder &&other) = delete;
		public:
			virtual float getCylinderRadius() = 0; // Return cylinder radius
			virtual float getCylinderHeight() = 0; // Return cylinder height
			virtual int getCylinderSides() = 0; // Return side count
			virtual int getCapSegments() = 0; // Return cap segment count
			virtual int getHeightSegments() = 0; // Return height segment count

			virtual bool setCylinderRadius(const float value) = 0; // Set cylinder radius
			virtual bool setCylinderHeight(const float value) = 0; // Set cylinder height
			virtual bool setCylinderSides(const int value) = 0; // Set side count
			virtual bool setCylinderSize(const float radius, const float height, const int sides) = 0; // Set cylinder radius, height, and side count
			virtual bool setCapSegments(const int value) = 0; // Set cap segment count
			virtual bool setHeightSegments(const int value) = 0; // Set height segment count
			virtual bool setSegments(const int cap, const int height) = 0; // Set cap and height segment count
		};
	}
}
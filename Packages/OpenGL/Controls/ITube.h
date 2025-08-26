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
		class ITube :public virtual I3DControl
		{
		protected:
			ITube() = default;
			~ITube() = default;
			ITube(const ITube &other) = delete;
			ITube(ITube &&other) = delete;
			ITube &operator=(const ITube &other) = delete;
			ITube &operator=(ITube &&other) = delete;
		public:
			virtual float getTubeOuterRadius() = 0; // Return tube outer radius
			virtual float getTubeInnerRadius() = 0; // Return tube inner radius
			virtual float getTubeHeight() = 0; // Return tube height
			virtual int getTubeSides() = 0; // Return side count
			virtual int getCapSegments() = 0; // Return cap segment count
			virtual int getHeightSegments() = 0; // Return height segment count

			virtual bool setTubeOuterRadius(const float value) = 0; // Set tube outer radius
			virtual bool setTubeInnerRadius(const float value) = 0; // Set tube inner radius
			virtual bool setTubeHeight(const float value) = 0; // Set tube height
			virtual bool setTubeSides(const int value) = 0; // Set side count
			virtual bool setTubeSize(const float outer_radius, const float inner_radius, const float height, const int sides) = 0; // Set tube radiuses, height, and side count
			virtual bool setCapSegments(const int value) = 0; // Set cap segment count
			virtual bool setHeightSegments(const int value) = 0; // Set height segment count
			virtual bool setSegments(const int cap, const int height) = 0; // Set cap and height segment count
		};
	}
}
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
		class ICone :public virtual I3DControl
		{
		protected:
			ICone() = default;
			~ICone() = default;
			ICone(const ICone &other) = delete;
			ICone(ICone &&other) = delete;
			ICone &operator=(const ICone &other) = delete;
			ICone &operator=(ICone &&other) = delete;
		public:
			virtual float getConeRadius1() = 0; // Return cone basement radius
			virtual float getConeRadius2() = 0; // Return cone top radius
			virtual float getConeHeight() = 0; // Return cone height
			virtual int getConeSides() = 0; // Return side count
			virtual int getCapSegments() = 0; // Return cap segment count
			virtual int getHeightSegments() = 0; // Return height segment count

			virtual bool setConeRadius1(const float value) = 0; // Set cone basement radius
			virtual bool setConeRadius2(const float value) = 0; // Set cone top radius. Could be 0
			virtual bool setConeHeight(const float value) = 0; // Set cone height
			virtual bool setConeSides(const int value) = 0; // Set cone side count
			virtual bool setConeSize(const float radius1, const float radius2, const float height, const int sides) = 0; // Set cone basement radius, top radius, and side count
			virtual bool setCapSegments(const int value) = 0; // Set cap segment count
			virtual bool setHeightSegments(const int value) = 0; // Set height segment count
			virtual bool setSegments(const int cap, const int height) = 0; // Set cap and height segment count
		};
	}
}
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
		class IBox :public virtual I3DControl
		{
		protected:
			IBox() = default;
			~IBox() = default;
			IBox(const IBox &other) = delete;
			IBox(IBox &&other) = delete;
			IBox &operator=(const IBox &other) = delete;
			IBox &operator=(IBox &&other) = delete;
		public:
			virtual float getBoxWidth() = 0; // Return box width
			virtual float getBoxHeight() = 0; // Return box height
			virtual float getBoxDepth() = 0; // Return box depth
			virtual int getWidthSegments() = 0; // Return width segment count
			virtual int getHeightSegments() = 0; // Return height segment count
			virtual int getDepthSegments() = 0; // Return depth segment count

			virtual bool setBoxWidth(const float value) = 0; // Set box width
			virtual bool setBoxHeight(const float value) = 0; // Set box height
			virtual bool setBoxDepth(const float value) = 0; // Set box depth
			virtual bool setBoxSize(const float width, const float height, const float depth) = 0; // Set box width, height, and depth
			virtual bool setWidthSegments(const int value) = 0; // Set width segment count
			virtual bool setHeightSegments(const int value) = 0; // Set height segment count
			virtual bool setDepthSegments(const int value) = 0; // Set depth segment count
			virtual bool setSegments(const int width, const int height, const int depth) = 0; // Set width, height, and depth segment count
		};
	}
}
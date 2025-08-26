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
		class IPlane :public virtual I3DControl
		{
		protected:
			IPlane() = default;
			~IPlane() = default;
			IPlane(const IPlane &other) = delete;
			IPlane(IPlane &&other) = delete;
			IPlane &operator=(const IPlane &other) = delete;
			IPlane &operator=(IPlane &&other) = delete;
		public:
			virtual float getPlaneWidth() = 0; // Return plane width
			virtual float getPlaneDepth() = 0; // Return plane depth
			virtual int getWidthSegments() = 0; // Return width segment count
			virtual int getDepthSegments() = 0; // Return depth segment count

			virtual bool setPlaneWidth(const float value) = 0; // Set plane width
			virtual bool setPlaneDepth(const float value) = 0; // Set plane depth
			virtual bool setPlaneSize(const float width, const float depth) = 0; // Set plane width and depth
			virtual bool setWidthSegments(const int value) = 0; // Set width segment count
			virtual bool setDepthSegments(const int value) = 0; // Set depth segment count
			virtual bool setSegments(const int width, const int depth) = 0; // Set width and depth segment count
		};
	}
}
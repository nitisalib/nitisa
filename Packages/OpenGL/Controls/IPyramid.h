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
		class IPyramid :public virtual I3DControl
		{
		protected:
			IPyramid() = default;
			~IPyramid() = default;
			IPyramid(const IPyramid &other) = delete;
			IPyramid(IPyramid &&other) = delete;
			IPyramid &operator=(const IPyramid &other) = delete;
			IPyramid &operator=(IPyramid &&other) = delete;
		public:
			virtual float getPyramidWidth() = 0; // Return pyramid basement width
			virtual float getPyramidDepth() = 0; // Return pyramid basement depth
			virtual float getPyramidHeight() = 0; // Return pyramid height
			virtual int getHeightSegments() = 0; // Return height segment count

			virtual bool setPyramidWidth(const float value) = 0; // Set pyramid basement width
			virtual bool setPyramidDepth(const float value) = 0; // Set pyramid basement depth
			virtual bool setPyramidHeight(const float value) = 0; // Set pyramid height
			virtual bool setPyramidSize(const float width, const float depth, const float height) = 0; // Set pyramid dimensions
			virtual bool setHeightSegments(const int value) = 0; // Set height segment count
		};
	}
}
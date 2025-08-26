// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Math/Point.h"
#include "../Interfaces/I3DControl.h"

namespace nitisa
{
	namespace opengl
	{
		class IHeightmap :public virtual I3DControl
		{
		protected:
			IHeightmap() = default;
			~IHeightmap() = default;
			IHeightmap(const IHeightmap &other) = delete;
			IHeightmap(IHeightmap &&other) = delete;
			IHeightmap &operator=(const IHeightmap &other) = delete;
			IHeightmap &operator=(IHeightmap &&other) = delete;
		public:
			virtual float getCellWidth() = 0; // Return image pixel width to 3D space conversion scale factor
			virtual float getCellHeight() = 0; // Return image color to 3D space conversion scale factor
			virtual float getCellDepth() = 0; // Return image pixel height to 3D space conversion scale factor
			virtual String getFilename() = 0; // Return image file name
			virtual Point getHeightmapSize() = 0; // Return count of polygons(int X and Z directions) after converting from image. It is equal to { ImageWidth - 1, ImageHeight - 1 }

			virtual bool setCellWidth(const float value) = 0; // Set image pixel width to 3D space conversion scale factor
			virtual bool setCellHeight(const float value) = 0; // Set image color to 3D space conversion scale factor
			virtual bool setCellDepth(const float value) = 0; // Set image pixel height to 3D space conversion scale factor
			virtual bool setCellSize(const float width, const float height, const float depth) = 0; // Set image to 3D geometry scaling factors
			virtual bool setFilename(const String &value) = 0; // Set image file name
		};
	}
}
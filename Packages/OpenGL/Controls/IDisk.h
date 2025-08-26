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
		class IDisk :public virtual I3DControl
		{
		protected:
			IDisk() = default;
			~IDisk() = default;
			IDisk(const IDisk &other) = delete;
			IDisk(IDisk &&other) = delete;
			IDisk &operator=(const IDisk &other) = delete;
			IDisk &operator=(IDisk &&other) = delete;
		public:
			virtual float getDiskOuterRadius() = 0; // Return disk outer radius
			virtual float getDiskInnerRadius() = 0; // Return disk inner radius
			virtual int getDiskSides() = 0; // Return side count
			virtual int getCapSegments() = 0; // Return cap segment count
			
			virtual bool setDiskOuterRadius(const float value) = 0; // Set disk outer radius
			virtual bool setDiskInnerRadius(const float value) = 0; // Set disk inner radius
			virtual bool setDiskSides(const int value) = 0; // Set disk side count
			virtual bool setDiskSize(const float outer_radius, const float inner_radius, const int sides) = 0; // Set disk outer radius, inner radius, and side count
			virtual bool setCapSegments(const int value) = 0; // Set cap segment count
		};
	}
}
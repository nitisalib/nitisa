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
		class ITorus :public virtual I3DControl
		{
		protected:
			ITorus() = default;
			~ITorus() = default;
			ITorus(const ITorus &other) = delete;
			ITorus(ITorus &&other) = delete;
			ITorus &operator=(const ITorus &other) = delete;
			ITorus &operator=(ITorus &&other) = delete;
		public:
			virtual float getTorusRadius1() = 0; // Return torus radius
			virtual float getTorusRadius2() = 0; // Return torus small radius
			virtual int getTorusSides1() = 0; // Return side count
			virtual int getTorusSides2() = 0; // Return vertical side count

			virtual bool setTorusRadius1(const float value) = 0; // Set torus radius
			virtual bool setTorusRadius2(const float value) = 0; // Set torus small radius
			virtual bool setTorusSides1(const int value) = 0; // Set side count
			virtual bool setTorusSides2(const int value) = 0; // Set vertical side count
			virtual bool setTorusSize(const float radius1, const float radius2, const int sides1, const int sides2) = 0; // Set torus dimensions
		};
	}
}
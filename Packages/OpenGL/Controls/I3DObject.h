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
	class IVertexArray;

	namespace opengl
	{
		class I3DObject :public virtual I3DControl
		{
		protected:
			I3DObject() = default;
			~I3DObject() = default;
			I3DObject(const I3DObject &other) = delete;
			I3DObject(I3DObject &&other) = delete;
			I3DObject &operator=(const I3DObject &other) = delete;
			I3DObject &operator=(I3DObject &&other) = delete;
		public:
			enum class PrimitiveType
			{
				Point,
				Line,
				Wire,
				Polygon
			};
		public:
			virtual IVertexArray *getVertexArray() = 0; // Return vertex array. After changing geometry Repaint should be called manually
			virtual PrimitiveType getPrimitiveType() const = 0;

			virtual bool setPrimitiveType(const PrimitiveType &value) = 0;
		};
	}
}
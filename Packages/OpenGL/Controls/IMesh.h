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
		class IMesh :public virtual I3DControl
		{
		protected:
			IMesh() = default;
			~IMesh() = default;
			IMesh(const IMesh &other) = delete;
			IMesh(IMesh &&other) = delete;
			IMesh &operator=(const IMesh &other) = delete;
			IMesh &operator=(IMesh &&other) = delete;
		public:
			virtual IVertexArray *getVertexArray() = 0; // Return vertex array. After changing geometry Repaint should be called manually
		};
	}
}
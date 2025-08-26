// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	namespace standard
	{
		class IFormStyleSolid :public virtual IControl
		{
		protected:
			IFormStyleSolid() = default;
			~IFormStyleSolid() = default;
			IFormStyleSolid(const IFormStyleSolid &other) = delete;
			IFormStyleSolid(IFormStyleSolid &&other) = delete;
			IFormStyleSolid &operator=(const IFormStyleSolid &other) = delete;
			IFormStyleSolid &operator=(IFormStyleSolid &&other) = delete;
		public:
			// No additional properties and methods
		};
	}
}
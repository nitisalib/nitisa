// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControl.h"
#include "../Interfaces/IViewControl.h"

namespace nitisa
{
	namespace ide
	{
		/*
			-------------------------------------------
			|            |               |            |
			|            |               |            |
			|            |               |            |
			|            |               |            |
			|            1               2            |
			|            |               |            |
			|            |               |            |
			|            |               |            |
			|            |               |            |
			-------------------------------------------
		*/
		class IViewH3 :public virtual IViewControl, public virtual IControl
		{
		protected:
			IViewH3() = default;
			~IViewH3() = default;
			IViewH3(const IViewH3 &other) = delete;
			IViewH3(IViewH3 &&other) = delete;
			IViewH3 &operator=(const IViewH3 &other) = delete;
			IViewH3 &operator=(IViewH3 &&other) = delete;
		public:
			virtual bool isResizable() = 0;
			virtual float getSeparator1() = 0;
			virtual float getSeparator2() = 0;

			virtual bool setResizable(const bool value) = 0;
			virtual bool setSeparator1(const float value) = 0;
			virtual bool setSeparator2(const float value) = 0;
		};
	}
}
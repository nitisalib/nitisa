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
			|                    |                    |
			|                    |                    |
			|                    |                    |
			|                    |                    |
			|                    |                    |
			|                    |                    |
			|                    |                    |
			|                    |                    |
			|                    |                    |
			-------------------------------------------
		*/
		class IViewH2 :public virtual IViewControl, public virtual IControl
		{
		protected:
			IViewH2() = default;
			~IViewH2() = default;
			IViewH2(const IViewH2 &other) = delete;
			IViewH2(IViewH2 &&other) = delete;
			IViewH2 &operator=(const IViewH2 &other) = delete;
			IViewH2 &operator=(IViewH2 &&other) = delete;
		public:
			virtual bool isResizable() = 0;
			virtual float getSeparator() = 0;

			virtual bool setResizable(const bool value) = 0;
			virtual bool setSeparator(const float value) = 0;
		};
	}
}
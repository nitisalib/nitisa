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
			|                                         |
			|                                         |
			|--------------------1--------------------|
			|                                         |
			|                                         |
			|                                         |
			|--------------------2--------------------|
			|                                         |
			|                                         |
			-------------------------------------------
		*/
		class IViewV3 :public virtual IViewControl, public virtual IControl
		{
		protected:
			IViewV3() = default;
			~IViewV3() = default;
			IViewV3(const IViewV3 &other) = delete;
			IViewV3(IViewV3 &&other) = delete;
			IViewV3 &operator=(const IViewV3 &other) = delete;
			IViewV3 &operator=(IViewV3 &&other) = delete;
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
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
			|                                         |
			|                                         |
			|-----------------------------------------|
			|                                         |
			|                                         |
			|                                         |
			|                                         |
			-------------------------------------------
		*/
		class IViewV2 :public virtual IViewControl, public virtual IControl
		{
		protected:
			IViewV2() = default;
			~IViewV2() = default;
			IViewV2(const IViewV2 &other) = delete;
			IViewV2(IViewV2 &&other) = delete;
			IViewV2 &operator=(const IViewV2 &other) = delete;
			IViewV2 &operator=(IViewV2 &&other) = delete;
		public:
			virtual bool isResizable() = 0;
			virtual float getSeparator() = 0;

			virtual bool setResizable(const bool value) = 0;
			virtual bool setSeparator(const float value) = 0;
		};
	}
}
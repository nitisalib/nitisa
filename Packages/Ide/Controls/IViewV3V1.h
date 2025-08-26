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
			|---V1---------------|                    |
			|                    |                    |
			|                    H                    |
			|                    |                    |
			|---V2---------------|                    |
			|                    |                    |
			|                    |                    |
			-------------------------------------------
		*/
		class IViewV3V1 :public virtual IViewControl, public virtual IControl
		{
		protected:
			IViewV3V1() = default;
			~IViewV3V1() = default;
			IViewV3V1(const IViewV3V1 &other) = delete;
			IViewV3V1(IViewV3V1 &&other) = delete;
			IViewV3V1 &operator=(const IViewV3V1 &other) = delete;
			IViewV3V1 &operator=(IViewV3V1 &&other) = delete;
		public:
			virtual bool isResizable() = 0;
			virtual float getSeparatorH() = 0;
			virtual float getSeparatorV1() = 0;
			virtual float getSeparatorV2() = 0;

			virtual bool setResizable(const bool value) = 0;
			virtual bool setSeparatorH(const float value) = 0;
			virtual bool setSeparatorV1(const float value) = 0;
			virtual bool setSeparatorV2(const float value) = 0;
		};
	}
}
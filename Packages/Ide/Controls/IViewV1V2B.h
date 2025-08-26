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
			|                     |                   |
			|                     V                   |
			|                     |                   |
			|                     |                   |
			|                     |---H---------------|
			|                     |         |         |
			|                     |         X         |
			|                     |         |         |
			|                     |         |         |
			-------------------------------------------
		*/
		class IViewV1V2B :public virtual IViewControl, public virtual IControl
		{
		protected:
			IViewV1V2B() = default;
			~IViewV1V2B() = default;
			IViewV1V2B(const IViewV1V2B &other) = delete;
			IViewV1V2B(IViewV1V2B &&other) = delete;
			IViewV1V2B &operator=(const IViewV1V2B &other) = delete;
			IViewV1V2B &operator=(IViewV1V2B &&other) = delete;
		public:
			virtual bool isResizable() = 0;
			virtual float getSeparatorH() = 0;
			virtual float getSeparatorV() = 0;
			virtual float getSeparatorX() = 0;

			virtual bool setResizable(const bool value) = 0;
			virtual bool setSeparatorH(const float value) = 0;
			virtual bool setSeparatorV(const float value) = 0;
			virtual bool setSeparatorX(const float value) = 0;
		};
	}
}
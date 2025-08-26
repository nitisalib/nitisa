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
			|                     |         |         |
			|                     V         X         |
			|                     |         |         |
			|                     |         |         |
			|                     |---H---------------|
			|                     |                   |
			|                     |                   |
			|                     |                   |
			|                     |                   |
			-------------------------------------------
		*/
		class IViewV1V2T :public virtual IViewControl, public virtual IControl
		{
		protected:
			IViewV1V2T() = default;
			~IViewV1V2T() = default;
			IViewV1V2T(const IViewV1V2T &other) = delete;
			IViewV1V2T(IViewV1V2T &&other) = delete;
			IViewV1V2T &operator=(const IViewV1V2T &other) = delete;
			IViewV1V2T &operator=(IViewV1V2T &&other) = delete;
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
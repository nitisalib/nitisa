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
			|          |          |                   |
			|          X          H                   |
			|          |          |                   |
			|          |          |                   |
			|---V-----------------|                   |
			|                     |                   |
			|                     |                   |
			|                     |                   |
			|                     |                   |
			-------------------------------------------
		*/
		class IViewV2TV1 :public virtual IViewControl, public virtual IControl
		{
		protected:
			IViewV2TV1() = default;
			~IViewV2TV1() = default;
			IViewV2TV1(const IViewV2TV1 &other) = delete;
			IViewV2TV1(IViewV2TV1 &&other) = delete;
			IViewV2TV1 &operator=(const IViewV2TV1 &other) = delete;
			IViewV2TV1 &operator=(IViewV2TV1 &&other) = delete;
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
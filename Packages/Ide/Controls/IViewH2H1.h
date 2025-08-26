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
			|                    H                    |
			|                    |                    |
			|                    |                    |
			|---V-------------------------------------|
			|                                         |
			|                                         |
			|                                         |
			|                                         |
			-------------------------------------------
		*/
		class IViewH2H1 :public virtual IViewControl, public virtual IControl
		{
		protected:
			IViewH2H1() = default;
			~IViewH2H1() = default;
			IViewH2H1(const IViewH2H1 &other) = delete;
			IViewH2H1(IViewH2H1 &&other) = delete;
			IViewH2H1 &operator=(const IViewH2H1 &other) = delete;
			IViewH2H1 &operator=(IViewH2H1 &&other) = delete;
		public:
			virtual bool isResizable() = 0;
			virtual float getSeparatorH() = 0;
			virtual float getSeparatorV() = 0;

			virtual bool setResizable(const bool value) = 0;
			virtual bool setSeparatorH(const float value) = 0;
			virtual bool setSeparatorV(const float value) = 0;
		};
	}
}
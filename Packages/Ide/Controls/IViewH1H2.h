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
			|--V--------------------------------------|
			|                    |                    |
			|                    H                    |
			|                    |                    |
			|                    |                    |
			-------------------------------------------
		*/
		class IViewH1H2 :public virtual IViewControl, public virtual IControl
		{
		protected:
			IViewH1H2() = default;
			~IViewH1H2() = default;
			IViewH1H2(const IViewH1H2 &other) = delete;
			IViewH1H2(IViewH1H2 &&other) = delete;
			IViewH1H2 &operator=(const IViewH1H2 &other) = delete;
			IViewH1H2 &operator=(IViewH1H2 &&other) = delete;
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
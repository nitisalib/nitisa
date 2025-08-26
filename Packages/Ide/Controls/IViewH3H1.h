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
			|          |                  |           |
			|          H1                 H2          |
			|          |                  |           |
			|          |                  |           |
			|--V--------------------------------------|
			|                                         |
			|                                         |
			|                                         |
			|                                         |
			-------------------------------------------
		*/
		class IViewH3H1 :public virtual IViewControl, public virtual IControl
		{
		protected:
			IViewH3H1() = default;
			~IViewH3H1() = default;
			IViewH3H1(const IViewH3H1 &other) = delete;
			IViewH3H1(IViewH3H1 &&other) = delete;
			IViewH3H1 &operator=(const IViewH3H1 &other) = delete;
			IViewH3H1 &operator=(IViewH3H1 &&other) = delete;
		public:
			virtual bool isResizable() = 0;
			virtual float getSeparatorV() = 0;
			virtual float getSeparatorH1() = 0;
			virtual float getSeparatorH2() = 0;

			virtual bool setResizable(const bool value) = 0;
			virtual bool setSeparatorV(const float value) = 0;
			virtual bool setSeparatorH1(const float value) = 0;
			virtual bool setSeparatorH2(const float value) = 0;
		};
	}
}
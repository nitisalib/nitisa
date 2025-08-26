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
			|          |                  |           |
			|          H1                 H2          |
			|          |                  |           |
			|          |                  |           |
			-------------------------------------------
		*/
		class IViewH1H3 :public virtual IViewControl, public virtual IControl
		{
		protected:
			IViewH1H3() = default;
			~IViewH1H3() = default;
			IViewH1H3(const IViewH1H3 &other) = delete;
			IViewH1H3(IViewH1H3 &&other) = delete;
			IViewH1H3 &operator=(const IViewH1H3 &other) = delete;
			IViewH1H3 &operator=(IViewH1H3 &&other) = delete;
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
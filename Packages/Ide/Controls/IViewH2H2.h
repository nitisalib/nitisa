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
			|          |                              |
			|          H1                             |
			|          |                              |
			|          |                              |
			|---V-------------------------------------|
			|                               |         |
			|                               H2        |
			|                               |         |
			|                               |         |
			-------------------------------------------
		*/
		class IViewH2H2 :public virtual IViewControl, public virtual IControl
		{
		protected:
			IViewH2H2() = default;
			~IViewH2H2() = default;
			IViewH2H2(const IViewH2H2 &other) = delete;
			IViewH2H2(IViewH2H2 &&other) = delete;
			IViewH2H2 &operator=(const IViewH2H2 &other) = delete;
			IViewH2H2 &operator=(IViewH2H2 &&other) = delete;
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
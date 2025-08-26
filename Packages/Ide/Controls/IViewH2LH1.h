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
			|                     H                   |
			|                     |                   |
			|--X------------------|                   |
			|                     |                   |
			|--V--------------------------------------|
			|                                         |
			|                                         |
			|                                         |
			|                                         |
			-------------------------------------------
		*/
		class IViewH2LH1 :public virtual IViewControl, public virtual IControl
		{
		protected:
			IViewH2LH1() = default;
			~IViewH2LH1() = default;
			IViewH2LH1(const IViewH2LH1 &other) = delete;
			IViewH2LH1(IViewH2LH1 &&other) = delete;
			IViewH2LH1 &operator=(const IViewH2LH1 &other) = delete;
			IViewH2LH1 &operator=(IViewH2LH1 &&other) = delete;
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
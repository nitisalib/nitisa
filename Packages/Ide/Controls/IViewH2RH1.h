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
			|                     |---X---------------|
			|                     |                   |
			|---V-------------------------------------|
			|                                         |
			|                                         |
			|                                         |
			|                                         |
			-------------------------------------------
		*/
		class IViewH2RH1 :public virtual IViewControl, public virtual IControl
		{
		protected:
			IViewH2RH1() = default;
			~IViewH2RH1() = default;
			IViewH2RH1(const IViewH2RH1 &other) = delete;
			IViewH2RH1(IViewH2RH1 &&other) = delete;
			IViewH2RH1 &operator=(const IViewH2RH1 &other) = delete;
			IViewH2RH1 &operator=(IViewH2RH1 &&other) = delete;
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
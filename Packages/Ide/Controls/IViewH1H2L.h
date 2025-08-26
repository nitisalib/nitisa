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
			|---V-------------------------------------|
			|                    H                    |
			|                    |                    |
			|---X----------------|                    |
			|                    |                    |
			-------------------------------------------
		*/
		class IViewH1H2L :public virtual IViewControl, public virtual IControl
		{
		protected:
			IViewH1H2L() = default;
			~IViewH1H2L() = default;
			IViewH1H2L(const IViewH1H2L &other) = delete;
			IViewH1H2L(IViewH1H2L &&other) = delete;
			IViewH1H2L &operator=(const IViewH1H2L &other) = delete;
			IViewH1H2L &operator=(IViewH1H2L &&other) = delete;
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
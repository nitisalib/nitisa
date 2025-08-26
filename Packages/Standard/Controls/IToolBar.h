// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	namespace standard
	{
		class IToolBar :public virtual IControl
		{
		protected:
			IToolBar() = default;
			~IToolBar() = default;
			IToolBar(const IToolBar &other) = delete;
			IToolBar(IToolBar &&other) = delete;
			IToolBar &operator=(const IToolBar &other) = delete;
			IToolBar &operator=(IToolBar &&other) = delete;
		public:
			enum class AlignTo // How to align child controls
			{
				Left, // To the left of the toolbar
				Right // To the right of the toolbar
			};
		public:
			virtual AlignTo getAlignTo() = 0; // Return child controls alignment

			virtual bool setAlignTo(const AlignTo value) = 0; // Set child controls alignment
		};
	}
}
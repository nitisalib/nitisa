// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "IEdit.h"

namespace nitisa
{
	namespace standard
	{
		class IEditCalc :public virtual IEdit
		{
		protected:
			IEditCalc() = default;
			~IEditCalc() = default;
			IEditCalc(const IEditCalc &other) = delete;
			IEditCalc(IEditCalc &&other) = delete;
			IEditCalc &operator=(const IEditCalc &other) = delete;
			IEditCalc &operator=(IEditCalc &&other) = delete;
		public:
			virtual bool isAutoCalculate() = 0; // Return whether value should be automatically calculated or only after "Return" pressed
			virtual bool isCalculateOnReturn() = 0; // Return whether value should be calculated after "Return" pressed

			virtual bool setAutoCalculate(const bool value) = 0; // Set whether value should be automatically calculated or only after "Return" pressed
			virtual bool setCalculateOnReturn(const bool value) = 0; // Set whether value should be calculated after "Return" pressed

			virtual bool Calculate() = 0; // Calculate value
		};
	}
}
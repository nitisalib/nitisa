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
		class IEdit;

		class IUpDown :public virtual IControl
		{
		protected:
			IUpDown() = default;
			~IUpDown() = default;
			IUpDown(const IUpDown &other) = delete;
			IUpDown(IUpDown &&other) = delete;
			IUpDown &operator=(const IUpDown &other) = delete;
			IUpDown &operator=(IUpDown &&other) = delete;
		public:
			void(*OnChange)(IUpDown *sender); // Event called when value changed by user

			virtual int getMin() = 0; // Return minimum allowed value
			virtual int getMax() = 0; // Return maximum allowed value
			virtual int getValue() = 0; // Return current value
			virtual int getStep() = 0; // Return step value
			virtual IEdit *getAssignedTo() = 0; // Return assigned edit control

			virtual bool setMin(const int value) = 0; // Set minimum allowed value
			virtual bool setMax(const int value) = 0; // Set maximum allowed value
			virtual bool setValue(const int value) = 0; // Set current value
			virtual bool setStep(const int value) = 0; // Set step value. 1 is minimum
			virtual bool setAssignedTo(IEdit *value) = 0; // Assign to edit control

			virtual bool Up() = 0; // Increase value by step
			virtual bool Down() = 0; // Decrease value by step
		};
	}
}
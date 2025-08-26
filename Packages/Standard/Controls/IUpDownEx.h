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

		class IUpDownEx :public virtual IControl
		{
		protected:
			IUpDownEx() = default;
			~IUpDownEx() = default;
			IUpDownEx(const IUpDownEx &other) = delete;
			IUpDownEx(IUpDownEx &&other) = delete;
			IUpDownEx &operator=(const IUpDownEx &other) = delete;
			IUpDownEx &operator=(IUpDownEx &&other) = delete;
		public:
			void(*OnChange)(IUpDownEx *sender); // Event called when value changed by user

			virtual float getMin() = 0; // Return minimum allowed value
			virtual float getMax() = 0; // Return maximum allowed value
			virtual float getValue() = 0; // Return current value
			virtual float getStep() = 0; // Return step value
			virtual IEdit *getAssignedTo() = 0; // Return assigned edit control

			virtual bool setMin(const float value) = 0; // Set minimum allowed value
			virtual bool setMax(const float value) = 0; // Set maximum allowed value
			virtual bool setValue(const float value) = 0; // Set current value
			virtual bool setStep(const float value) = 0; // Set step value. Should be greater than zero
			virtual bool setAssignedTo(IEdit *value) = 0; // Assign to edit control

			virtual bool Up() = 0; // Increase value by step
			virtual bool Down() = 0; // Decrease value by step
		};
	}
}
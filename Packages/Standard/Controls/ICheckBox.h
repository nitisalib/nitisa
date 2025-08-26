// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IControl.h"
#include "Nitisa/Interfaces/IControlService.h"

namespace nitisa
{
	namespace standard
	{
		class ICheckBox :public virtual IControl
		{
		protected:
			ICheckBox() = default;
			~ICheckBox() = default;
			ICheckBox(const ICheckBox &other) = delete;
			ICheckBox(ICheckBox &&other) = delete;
			ICheckBox &operator=(const ICheckBox &other) = delete;
			ICheckBox &operator=(ICheckBox &&other) = delete;
		public:
			enum class CheckedState // Checked states
			{
				Unchecked, // Unchecked
				Grayed, // Both checked and unchecked
				Checked // Checked
			};
		public:
			virtual String getCaption() = 0; // Return caption
			virtual CheckedState getChecked() = 0; // Return checked state

			virtual bool setCaption(const String &value) = 0; // Set caption
			virtual bool setChecked(const CheckedState value) = 0; // Set checked state
		};

		class ICheckBoxService :public virtual IControlService
		{
		protected:
			ICheckBoxService() = default;
			~ICheckBoxService() = default;
			ICheckBoxService(const ICheckBoxService &other) = delete;
			ICheckBoxService(ICheckBoxService &&other) = delete;
			ICheckBoxService &operator=(const ICheckBoxService &other) = delete;
			ICheckBoxService &operator=(ICheckBoxService &&other) = delete;
		public:
			virtual bool setChecked(const ICheckBox::CheckedState value) = 0;
		};
	}
}
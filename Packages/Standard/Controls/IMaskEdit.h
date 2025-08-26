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

namespace nitisa
{
	namespace standard
	{
		class IMaskEdit;

		class IMaskValidator
		{
		protected:
			IMaskValidator() = default;
			~IMaskValidator() = default;
			IMaskValidator(const IMaskValidator &other) = delete;
			IMaskValidator(IMaskValidator &&other) = delete;
			IMaskValidator &operator=(const IMaskValidator &other) = delete;
			IMaskValidator &operator=(IMaskValidator &&other) = delete;
		public:
			/**
			Validate specified text via specified mask. Allowed to change text and edit properties. The method should not set text or caret position in specified MaskEdit control
			@param edit MaskEdit control called the method
			@param mask Mask stored in MaskEdit control. Validator may or mat not use it
			@param original Original text before changes
			@param text Text to be validated. Could be changed
			@param caret_position Has current caret position. Could be changed by validator
			@return true if text is okay and can be set into MaskEdit control.
			*/
			virtual bool Validate(IMaskEdit *edit, const String &mask, const String &original, String &text, int &caret_position) = 0;
		};

		// Validator won't be destroyed automatic
		class IMaskEdit :public virtual IControl
		{
		protected:
			IMaskEdit() = default;
			~IMaskEdit() = default;
			IMaskEdit(const IMaskEdit &other) = delete;
			IMaskEdit(IMaskEdit &&other) = delete;
			IMaskEdit &operator=(const IMaskEdit &other) = delete;
			IMaskEdit &operator=(IMaskEdit &&other) = delete;
		public:
			virtual String getText() = 0; // Return text
			virtual String getMask() = 0; // Return mask(used in default validator and may be used in other ones). # - number symbol, * - character, all other symbols are set as is. For example, short phone number mask could be ##########, ###-###-####, (095) ### ### #### and so on
			virtual IMaskValidator *getValidator() = 0; // Return mask validator

			virtual bool setText(const String &value) = 0; // Set text
			virtual bool setMask(const String &value) = 0; // Set mask
			virtual bool setValidator(IMaskValidator *value) = 0; // Set mask validator. If nullptr, default one will be used
		};
	}
}
// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "IReleasable.h"

namespace nitisa
{
	class IDbAttribute;
	
	class CDbModel;

	class IDbValidator :public virtual IReleasable
	{
	public:
		using FWhen = bool(*)(CDbModel *model, IDbAttribute *attribute);
	protected:
		IDbValidator() = default;
		~IDbValidator() = default;
		IDbValidator(const IDbValidator &other) = delete;
		IDbValidator(IDbValidator &&other) = delete;
		IDbValidator &operator=(const IDbValidator &other) = delete;
		IDbValidator &operator=(IDbValidator &&other) = delete;
	protected:
		int m_iCode; // Error code of this validator. Has no internal meaning. Can be used to distinguish errors not only by message but by code as well
	public:
		int const &iCode{ m_iCode }; // Error code of this validator. Has no internal meaning. Can be used to distinguish errors not only by message but by code as well

		virtual IDbValidator *setCode(const int value) = 0; // Set error code of this validator
		virtual IDbValidator *setMessage(const String &value) = 0; // Set error message of this validator
		virtual IDbValidator *setOn(const StringArray &value) = 0; // Set scenarios at which validator is active. Empty list means the validator is active always
		virtual IDbValidator *setExcept(const StringArray &value) = 0; // Set scenarios at which validator should be skipped
		virtual IDbValidator *setSkipOnError(const bool &value) = 0; // Set whether the validation should be skipped if attribute already has errors
		virtual IDbValidator *setSkipOnEmpty(const bool &value) = 0; // Set whether the validation should be skipped if attribute is empty/null
		virtual IDbValidator *setWhen(FWhen value) = 0; // Set custom function to be used to check whether validation should be skipped

		virtual bool Validate(CDbModel *model, IDbAttribute *attribute, String &error) = 0; // Should provide actual validation
	};
}
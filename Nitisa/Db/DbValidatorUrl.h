// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/ReleasablePtr.h"
#include "../Core/Strings.h"
#include "DbValidator.h"

namespace nitisa
{
	class IDbAttribute;

	class CDbModel;

	class CDbValidatorUrl :public CDbValidator
	{
	private:
		String m_sPattern;
		String m_sDefaultScheme;
		StringArray m_aValidSchemes;
	public:
		// IDbValidator methods
		bool Validate(CDbModel *model, IDbAttribute *attribute, String &error) override;

		CDbValidatorUrl();

		CDbValidatorUrl *setPattern(const String &value); // Set pattern (regular expression) to compare against
		CDbValidatorUrl *setDefaultScheme(const String &value); // Set scheme to be used in validation if it is not specified in attribute value
		CDbValidatorUrl *setValidSchemes(const StringArray &value); // Set default valid schemes. By default "http" and "https" are only valid ones

		static ReleasablePtr<CDbValidatorUrl> Create(); // Helper static method to create validator in form used in model rule adding methods
	};
}
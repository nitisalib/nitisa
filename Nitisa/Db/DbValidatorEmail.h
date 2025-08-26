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

	class CDbValidatorEmail :public CDbValidator
	{
	private:
		String m_sPattern;
		String m_sFullPattern;
		bool m_bAllowName;
	public:
		// IDbValidator methods
		bool Validate(CDbModel *model, IDbAttribute *attribute, String &error) override;

		CDbValidatorEmail();

		CDbValidatorEmail *setPattern(const String &value); // Set email pattern (regular expression)
		CDbValidatorEmail *setFullPattern(const String &value); // Set email full pattern (regular expression)
		CDbValidatorEmail *setAllowName(const bool &value); // Set whether name is allowed in email. If true, full pattern is used, otherwise pattern is used

		static ReleasablePtr<CDbValidatorEmail> Create(); // Helper static method to create validator in form used in model rule adding methods
	};
}
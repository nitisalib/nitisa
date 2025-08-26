// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Releasable.h"
#include "../Core/Strings.h"
#include "../Interfaces/IDbValidator.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class IDbAttribute;

	class CDbModel;

	class CDbValidator :public virtual IDbValidator, public CReleasable
	{
	protected:
		String m_sMessage; // Error message
		StringArray m_aOn; // Array of scenarios the validator to be active in
		StringArray m_aExcept; // Array of scenarios the validator should be turned off
		bool m_bSkipOnError; // Whether to skip validation if attribute already has an error
		bool m_bSkipOnEmpty; // Whether to skip validation if attribute is empty (Null)
		FWhen m_fWhen; // Custom function to check whether validation is required
	protected:
		bool ShouldSkip(CDbModel *model, IDbAttribute *attribute); // Check whether attribute validation should be skipped depending on On/Except/SkipOnError/SkipOnEmpty/When properties
	public:
		// IDbValidator setters
		IDbValidator *setCode(const int value) override;
		IDbValidator *setMessage(const String &value) override;
		IDbValidator *setOn(const StringArray &value) override;
		IDbValidator *setExcept(const StringArray &value) override;
		IDbValidator *setSkipOnError(const bool &value) override;
		IDbValidator *setSkipOnEmpty(const bool &value) override;
		IDbValidator *setWhen(FWhen value) override;

		CDbValidator();
	};
}
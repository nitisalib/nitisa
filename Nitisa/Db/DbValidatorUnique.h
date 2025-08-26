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

	class CDbValidatorUnique :public CDbValidator
	{
	private:
		String m_sTargetTable;
		StringArray m_aTargetAttributes;
	public:
		// IDbValidator methods
		bool Validate(CDbModel *model, IDbAttribute *attribute, String &error) override;

		CDbValidatorUnique();

		CDbValidatorUnique *setTarget(const String &table, const String &attribute); // Set table and attribute name used to check if corresponding value is unique in database
		CDbValidatorUnique *setTarget(const String &table, const StringArray &attributes); // Set table and attribute names used to check if corresponding value is unique in database
		CDbValidatorUnique *setTargetTable(const String &value); // Set table used to check if corresponding value is unique in database
		CDbValidatorUnique *setTargetAttribute(const String &value); // Set attribute name used to check if corresponding value is unique in database
		CDbValidatorUnique *setTargetAttribute(const StringArray &value); // Set attribute names used to check if corresponding value is unique in database

		static ReleasablePtr<CDbValidatorUnique> Create(); // Helper static method to create validator in form used in model rule adding methods

		template<class Model>
		CDbValidatorUnique *setTarget() // Set table to compare using it from specified Active Record model
		{
			Model model;
			m_sTargetTable = model.getTable();
			return this;
		}
	};
}
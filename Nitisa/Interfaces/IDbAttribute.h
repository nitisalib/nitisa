// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "../Db/DbValue.h"

namespace nitisa
{
	class IDbAttribute
	{
		friend class IDbQuery;
		friend class IDbRelation;
		friend class CDbBaseActiveRecord;
	protected:
		String m_sName; // Name of the column in database
		bool m_bNull; // Whether the attribute value is supposed to be treated as empty/null
		bool m_bChanged; // Whether attribute value was changed

		virtual void SetInternal(const DbValue &value, const bool &changed) = 0; // Set attribute value and mark it as changed/unchanged
	public:
		String const &sName{ m_sName }; // Name of the column in database
		bool const &bNull{ m_bNull }; // Whether the attribute value is supposed to be treated as empty/null
		bool const &bChanged{ m_bChanged }; // Whether attribute value was changed

		IDbAttribute(const String &name) : // Constructor. "name" is the name of the corresponding column in database table
			m_sName{ name },
			m_bNull{ true },
			m_bChanged{ false }
		{

		}

		virtual void Set(const DbValue &value) = 0; // Set attribute value
		virtual DbValue Get() const = 0; // Return attribute value in form of DbValue
		virtual DbValue Old() const = 0; // Return old attribute value in form of DbValue. If attribute was not changed yet, return current value

		void SetNull() // Set to treat attribute value as empty/null
		{
			m_bNull = true;
		}
	};
}
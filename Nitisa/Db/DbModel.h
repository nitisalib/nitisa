// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Consts.h"
#include "../Core/ErrorInfo.h"
#include "../Core/Releasable.h"
#include "../Core/ReleasablePtr.h"
#include "../Core/Strings.h"
#include "../Interfaces/IDbAttribute.h"
#include "../Interfaces/IDbValidator.h"
#include "DbSet.h"
#include "DbValue.h"
#include <map>
#include <utility>
#include <vector>

namespace nitisa
{
	class CDbModel :public CReleasable
	{
		friend class IDbQuery;
	public:
		using ErrorInfos = std::vector<ErrorInfo>;
		using ErrorList = std::map<String, ErrorInfos>;
	private:
		class CAttributes
		{
			template<class Type> friend class TDbAttribute;
		private:
			std::vector<IDbAttribute*> m_aItems;

			void Add(IDbAttribute* item);
		public:
			IDbAttribute* operator[](const size_t index);

			CAttributes &operator=(const DbSet &attributes);
			template<class Type> CAttributes &operator=(Type) = delete;

			std::vector<IDbAttribute*>::iterator begin();
			std::vector<IDbAttribute*>::iterator end();
			std::vector<IDbAttribute*>::const_iterator begin() const;
			std::vector<IDbAttribute*>::const_iterator end() const;
			std::vector<IDbAttribute*>::const_iterator cbegin() const;
			std::vector<IDbAttribute*>::const_iterator cend() const;
			std::vector<IDbAttribute*>::reverse_iterator rbegin();
			std::vector<IDbAttribute*>::reverse_iterator rend();
			std::vector<IDbAttribute*>::const_reverse_iterator rbegin() const;
			std::vector<IDbAttribute*>::const_reverse_iterator rend() const;
			std::vector<IDbAttribute*>::const_reverse_iterator crbegin() const;
			std::vector<IDbAttribute*>::const_reverse_iterator crend() const;
			std::vector<IDbAttribute*>::size_type size() const;
			bool empty() const;
		};
	private:
		String m_sScenario;
		ErrorList m_aErrors;
		std::vector<std::pair<IDbAttribute *, ReleasablePtr<IDbValidator>>> m_aRules;
	protected:
		bool AddError(const String& attribute, const String& error, const int code); // Add error to specified attribute
		virtual bool BeforeValidate(); // Called before validation. Return false to fail validation
		virtual void AfterValidate(); // Called after successful validation
		
		template<class ValidatorType>
		ReleasablePtr<ValidatorType> Rule(IDbAttribute *attribute, ReleasablePtr<ValidatorType> validator) // Add validator to an attribute
		{
			if (!attribute || !validator)
				return nullptr;
			validator->AddRef();
			m_aRules.push_back(std::pair<IDbAttribute *, ReleasablePtr<IDbValidator>>{ attribute, ReleasablePtr<IDbValidator>{ validator } });
			return validator;
		}

		template<class ValidatorType>
		ReleasablePtr<ValidatorType> Rule(const String &attribute, ReleasablePtr<ValidatorType> validator) // Add validator to an attribute (by attribute name)
		{
			if (attribute.empty() || !validator)
				return nullptr;
			for (auto attr : Attributes)
				if (attr->sName == attribute)
					return Rule(attr, validator);
			return nullptr;
		}

		template<class ValidatorType>
		ReleasablePtr<ValidatorType> Rule(const StringArray &attributes, ReleasablePtr<ValidatorType> validator) // Add validator to attributes (by attribute names)
		{
			if (attributes.empty() || !validator)
				return nullptr;
			for (auto const &attr : attributes)
				if (!Rule(attr, validator))
					return nullptr;
			return validator;
		}

		CDbModel();
	public:
		String const &Scenario{ m_sScenario }; // Current scenario. "DEFAULT" by default

		CAttributes Attributes; // Collection of model attributes

		bool hasAttribute(const String& name) const; // Check whether attribute with specified name exists
		DbValue getAttribute(const String& name) const; // Return attribute value by name. If not found, results Type is Null
		DbValue getOldAttribute(const String& name) const; // Return attribute old value by name. If not found, results Type is Null
		bool hasErrors() const; // Return whether there are any errors after the last validation
		bool hasErrors(const String &attribute) const; // Return whether there are any errors related to the specified attribute after the last validation
		const ErrorList& getErrors() const; // Return list of all errors
		ErrorInfos getErrors(const String& attribute) const; // Return list of all errors related to specified attribute
		ErrorInfo getFirstError() const; // Return first error. If not found returns ErrorInfo{ 0, L"" }
		ErrorInfo getFirstError(const String &attribute) const; // Return first error for specified attribute.If not found returns ErrorInfo{ 0, L"" }

		bool setAttribute(const String& name, const DbValue& value); // Set attribute by name. If not found, returns false
		bool setScenario(const String &value); // Set scenario name

		virtual bool Validate(const StringArray& attributes = EmptyStringArray); // Run validation. "attributes" argument may be used to specify which attributes should be validated. If it is empty, all attributes will be validated. Return false is any validation fails
	};
}
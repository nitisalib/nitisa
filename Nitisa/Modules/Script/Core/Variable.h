// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Aliases.h"
#include "../../../Core/Strings.h"
#include "VariableType.h"
#include <map>
#include <vector>

namespace nitisa
{
	namespace script
	{
		class Variable
		{
		public:
			using Array = std::vector<Variable>;
			using Object = std::map<String, Variable>;
		private:
			VariableType m_eType;
			bool m_bValue;
			int64 m_iValue;
			double m_fValue;
			String m_sValue;
			Array m_aValue;
			Object m_oValue;
		public:
			// Constructors
			Variable();
			Variable(const VariableType type);
			Variable(const bool value);
			Variable(const int64 value);
			Variable(const double value);
			Variable(const String &value);
			Variable(const wchar_t *value);
			Variable(const Array &value);
			Variable(const Object &value);
			Variable(const Variable &other);
			Variable(Variable &&other);
			template<class T> Variable(T) = delete;

			// Assignment operators
			Variable &operator=(const Pointer value);
			Variable &operator=(const bool value);
			Variable &operator=(const int64 value);
			Variable &operator=(const double value);
			Variable &operator=(const String &value);
			Variable &operator=(const wchar_t *value);
			Variable &operator=(const Variable &other);
			Variable &operator=(Variable &&other);
			template<class T> Variable &operator=(T) = delete;

			// Conversion operators
			explicit operator Pointer() const;
			explicit operator bool() const;
			explicit operator int64() const;
			explicit operator double() const;
			explicit operator String() const; // Convert to string representation. Array and object do not have string representation in this operator

			// Array and object members access operators
			Variable &operator[](const String &key); // Return object member by name. Convert variable to object if it's not
			Variable &operator[](const wchar_t *key); // Return object member by name. Convert variable to object if it's not
			Variable &operator[](const size_t index); // Return array member by index. Don't check whether index is out of bounds. Convert variable to array if it's not
			const Variable &operator[](const size_t index) const; // Return array member by index. Don't check whether index is out of bounds or variable is an array
			template<class T> Variable &operator[](T) = delete;

			// Comparison operators
			bool operator==(const Variable &other) const;
			bool operator!=(const Variable &other) const;
			bool operator>(const Variable &other) const;
			bool operator<(const Variable &other) const;
			bool operator>=(const Variable &other) const;
			bool operator<=(const Variable &other) const;

			VariableType type() const; // Return variable type
			bool type(const VariableType value); // Set variable type
			bool has(const String &key) const; // Check whether there is a member of object with specified name
			size_t size() const; // Return size
			size_t count() const; // Return element count
			bool empty() const; // Check whether variable is empty
			void push_back(const Variable &value); // Convert variable to array and add element to it
			void clear(); // Clear variable and sets type to Null
			void erase(const size_t index); // Erase element of array at specified index. Convert to array if necessary
			void erase(const size_t index, const size_t count); // Erase multiple elements of array. Convert to array if necessary
			Object::iterator erase(Object::iterator where); // Erase element of object. Convert to object if necessary
			Object::iterator erase(Object::iterator first, Object::iterator last); // Erase multiple elements of object. Convert to object if necessary
			Object::iterator find(const String &key); // Find element of object by specified name. Convert to object if necessary
			const Variable *get(const String &key) const; // Return pointer to object or nullptr

			Object::iterator begin(); // Return object begin iterator. Convert to object if necessary
			Object::iterator end(); // Return object end iterator. Convert to object if necessary
			Object::reverse_iterator rbegin(); // Return object reverse begin iterator. Convert to object if necessary
			Object::reverse_iterator rend(); // Return object reverse end iterator. Convert to object if necessary
			Object::const_iterator begin() const; // Return constant object begin iterator. Do not convert to object
			Object::const_iterator end() const; // Return constant object end iterator. Do not convert to object
			Object::const_reverse_iterator rbegin() const; // Return constant object reverse begin iterator. Do not convert to object
			Object::const_reverse_iterator rend() const; // Return constant object reverse end iterator. Do not convert to object

			String toString() const; // Convert to string representation. Array and object also have string representation in this method
		};
	}
}
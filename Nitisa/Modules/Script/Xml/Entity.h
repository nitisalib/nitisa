// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Strings.h"
#include "EntityType.h"
#include <map>
#include <vector>

namespace nitisa
{
	namespace script
	{
		namespace xml
		{
			class Entity
			{
			private:
				using Attributes = std::map<String, String>;
				using Entities = std::vector<Entity>;
			private:
				EntityType m_eType;
				String m_sName;
				String m_sValue;
				Attributes m_aAttributes;
				Entities m_aEntities;

				String EncodeAttributes() const;
				String EncodeValue() const;
			public:
				// Constructors
				Entity();
				Entity(const String &name);
				Entity(const wchar_t *name);
				Entity(const String &name, const String &value);
				Entity(const wchar_t *name, const wchar_t *value);
				Entity(const Entity &other);
				Entity(Entity &&other);
				template<class T> Entity(T value) = delete;

				// Assignment operators
				Entity &operator=(const String &value); // Set type to value and assign value, clear entities
				Entity &operator=(const Entity &other);
				Entity &operator=(Entity &&other);
				template<class T> Entity &operator=(T value) = delete;

				explicit operator String() const; // Convert to compact string

				String &operator[](const String &key); // Return attribute by name
				String &operator[](const wchar_t *key); // Return attribute by name
				Entity &operator[](const size_t index); // Return child entity by index
				const Entity &operator[](const size_t index) const; // Return child entity by index
				template<typename T> Entity &operator[](T type) = delete;

				EntityType type() const; // Return type
				void type(const EntityType &value); // Set type
				const String &name() const; // Return name
				void name(const String &value); // Set name
				const String &value() const; // Return value
				void value(const String &data); // Set value
				size_t attribute_count() const; // Return attribute count
				bool has(const String &name) const; // Check whether attribute with specified name exists
				Attributes::const_iterator begin() const; // Return constant begin attributes iterator
				Attributes::const_iterator end() const; // Return constant end attributes iterator
				Attributes::iterator begin(); // Return begin attributes iterator
				Attributes::iterator end(); // Return end attributes iterator
				Attributes::const_reverse_iterator rbegin() const; // Return constant reverse begin attributes iterator
				Attributes::const_reverse_iterator rend() const; // Return constant reverse end attributes iterator
				Attributes::reverse_iterator rbegin(); // Return reverse begin attributes iterator
				Attributes::reverse_iterator rend(); // Return reverse end attributes iterator
				Attributes::iterator find(const String &name); // Find attribute by name
				Attributes::iterator erase(Attributes::iterator where); // Erase attribute
				Attributes::iterator erase(Attributes::iterator first, Attributes::iterator last); // Erase attributes
				size_t size(const bool entities = true) const; // Return count of entities (if entities = true) or count of attributes (if entities = false)
				bool empty(const bool entities = true) const; // Return true if there are no entities (if entities = true) or there no attributes (if entities = false)
				size_t count() const; // Return total count of entities where array count() equals to sum of count() of each element + 1 for array itself and count() of other types is one
				void push_back(const Entity &obj); // Add object to list
				void clear(const bool entities = true, const bool attributes = true); // Clear
				void erase(const size_t index); // Erase entity
				void erase(const size_t index, const size_t count); // Erase entities
			};
		}
	}
}
// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace script
	{
		namespace xml
		{
		#pragma region Constructor & destructor
			Entity::Entity():
				m_eType{ EntityType::Element }
			{

			}

			Entity::Entity(const String &name):
				m_eType{ EntityType::Element },
				m_sName{ name }
			{

			}

			Entity::Entity(const wchar_t *name) :
				m_eType{ EntityType::Element },
				m_sName{ name }
			{

			}

			Entity::Entity(const String &name, const String &value) :
				m_eType{ EntityType::Element },
				m_sName{ name },
				m_sValue{ value }
			{

			}

			Entity::Entity(const wchar_t *name, const wchar_t *value) :
				m_eType{ EntityType::Element },
				m_sName{ name },
				m_sValue{ value }
			{

			}

			Entity::Entity(const Entity &other):
				m_eType{ other.m_eType },
				m_sName{ other.m_sName },
				m_sValue{ other.m_sValue },
				m_aAttributes{ other.m_aAttributes }
			{
				m_aEntities = other.m_aEntities;
			}

			Entity::Entity(Entity &&other) :
				m_eType{ other.m_eType },
				m_sName{ std::move(other.m_sName) },
				m_sValue{ std::move(other.m_sValue) },
				m_aAttributes{ std::move(other.m_aAttributes) }
			{
				m_aEntities = std::move(other.m_aEntities);
			}
		#pragma endregion

		#pragma region Assignment operators
			Entity &Entity::operator=(const String &value)
			{
				m_eType = EntityType::Element;
				m_sValue = value;
				m_aEntities.clear();
				return *this;
			}

			Entity &Entity::operator=(const Entity &other)
			{
				m_eType = other.m_eType;
				m_sName = other.m_sName;
				m_sValue = other.m_sValue;
				m_aAttributes = other.m_aAttributes;
				m_aEntities = other.m_aEntities;
				return *this;
			}

			Entity &Entity::operator=(Entity &&other)
			{
				m_eType = other.m_eType;
				m_sName = std::move(other.m_sName);
				m_sValue = std::move(other.m_sValue);
				m_aAttributes = std::move(other.m_aAttributes);
				m_aEntities = std::move(other.m_aEntities);
				return *this;
			}
		#pragma endregion

		#pragma region Convert operators
			Entity::operator String() const
			{
				String result;
				switch (m_eType)
				{
				case EntityType::Prolog:
					result = L"<?" + m_sName + EncodeAttributes() + L"?>";
					break;
				case EntityType::Doctype:
					if (m_sValue.empty())
						result = L"<!DOCTYPE>";
					else
						result = L"<!DOCTYPE" + m_sValue + L">";
					break;
				case EntityType::Data:
					if (m_sValue.empty())
						result = L"<" + m_sName + EncodeAttributes() + L"/>";
					else
						result = L"<" + m_sName + EncodeAttributes() + L"><![CDATA[" + m_sValue + L"]]></" + m_sName + L">";
					break;
				case EntityType::Array:
					if (m_aEntities.empty())
						result = L"<" + m_sName + EncodeAttributes() + L"/>";
					else
					{
						result = L"<" + m_sName + EncodeAttributes() + L">";
						for (auto pos = m_aEntities.begin(); pos != m_aEntities.end(); pos++)
							result += (String)(*pos);
						result += L"</" + m_sName + L">";
					}
					break;
				default:
					if (m_sValue.empty())
						result = L"<" + m_sName + EncodeAttributes() + L"/>";
					else
						result = L"<" + m_sName + EncodeAttributes() + L">" + EncodeValue() + L"</" + m_sName + L">";
				}
				return result;
			}
		#pragma endregion

		#pragma region Access operators
			String &Entity::operator[](const String &key)
			{
				return m_aAttributes[key];
			}

			String &Entity::operator[](const wchar_t *key)
			{
				return m_aAttributes[key];
			}

			Entity &Entity::operator[](const size_t index)
			{
				m_eType = EntityType::Array;
				m_sValue.clear();
				return m_aEntities[index];
			}

			const Entity &Entity::operator[](const size_t index) const
			{
				return m_aEntities[index];
			}
		#pragma endregion

		#pragma region Methods
			EntityType Entity::type() const
			{
				return m_eType;
			}

			void Entity::type(const EntityType &value)
			{
				if (value != m_eType)
				{
					m_eType = value;
					switch (m_eType)
					{
					case EntityType::Array:
						m_sValue.clear();
						break;
					default:
						m_aEntities.clear();
						break;
					}
				}
			}

			const String &Entity::name() const
			{
				return m_sName;
			}

			void Entity::name(const String &value)
			{
				m_sName = value;
			}

			const String &Entity::value() const
			{
				return m_sValue;
			}

			void Entity::value(const String &data)
			{
				m_sValue = data;
			}

			size_t Entity::attribute_count() const
			{
				return m_aAttributes.size();
			}

			bool Entity::has(const String &name) const
			{
				return m_aAttributes.find(name) != m_aAttributes.end();
			}

			Entity::Attributes::const_iterator Entity::begin() const
			{
				return m_aAttributes.begin();
			}

			Entity::Attributes::const_iterator Entity::end() const
			{
				return m_aAttributes.end();
			}

			Entity::Attributes::iterator Entity::begin()
			{
				return m_aAttributes.begin();
			}

			Entity::Attributes::iterator Entity::end()
			{
				return m_aAttributes.end();
			}

			Entity::Attributes::const_reverse_iterator Entity::rbegin() const
			{
				return m_aAttributes.rbegin();
			}

			Entity::Attributes::const_reverse_iterator Entity::rend() const
			{
				return m_aAttributes.rend();
			}

			Entity::Attributes::reverse_iterator Entity::rbegin()
			{
				return m_aAttributes.rbegin();
			}

			Entity::Attributes::reverse_iterator Entity::rend()
			{
				return m_aAttributes.rend();
			}

			Entity::Attributes::iterator Entity::find(const String &name)
			{
				return m_aAttributes.find(name);
			}

			Entity::Attributes::iterator Entity::erase(Attributes::iterator where)
			{
				return m_aAttributes.erase(where);
			}

			Entity::Attributes::iterator Entity::erase(Attributes::iterator first, Attributes::iterator last)
			{
				return m_aAttributes.erase(first, last);
			}

			size_t Entity::size(const bool entities) const
			{
				return entities ? m_aEntities.size() : m_aAttributes.size();
			}

			bool Entity::empty(const bool entities) const
			{
				return entities ? m_aEntities.empty() : m_aAttributes.empty();
			}

			size_t Entity::count() const
			{
				if (m_eType == EntityType::Array)
				{
					size_t result{ 1 };
					for (auto pos = m_aEntities.begin(); pos != m_aEntities.end(); pos++)
						result += pos->count();
					return result;
				}
				return 1;
			}

			void Entity::push_back(const Entity &obj)
			{
				m_eType = EntityType::Array;
				m_sValue.clear();
				m_aEntities.push_back(obj);
			}

			void Entity::clear(const bool entities, const bool attributes)
			{
				if (entities)
					m_aEntities.clear();
				if (attributes)
					m_aAttributes.clear();
			}

			void Entity::erase(const size_t index)
			{
				m_aEntities.erase(m_aEntities.begin() + index);
			}

			void Entity::erase(const size_t index, const size_t count)
			{
				m_aEntities.erase(m_aEntities.begin() + index, m_aEntities.begin() + index + count);
			}
		#pragma endregion

		#pragma region Helpers
			String Entity::EncodeAttributes() const
			{
				String result;
				for (auto pos = m_aAttributes.begin(); pos != m_aAttributes.end(); pos++)
					result += L" " + pos->first + L"=\"" + ReplaceAll(pos->second, StringKeyValue{ L"\"", L"\\\"" }) + L"\"";
				return result;
			}

			String Entity::EncodeValue() const
			{
				if (m_sValue.empty())
					return L"";
				return ReplaceAll(m_sValue, StringKeyValueArray{ StringKeyValue{ L">", L"&gt;" }, StringKeyValue{ L"<", L"&lt;" } });
			}
		#pragma endregion
		}
	}
}
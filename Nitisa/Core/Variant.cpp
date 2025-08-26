// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	Variant::Variant() :
		vPointer{ nullptr },
		m_eType{ VariantType::Pointer }
	{

	}

	Variant::Variant(void *value) :
		vPointer{ value },
		m_eType{ VariantType::Pointer }
	{

	}

	Variant::Variant(const bool value) :
		vBool{ value },
		m_eType{ VariantType::Bool }
	{

	}

	Variant::Variant(const int value) :
		vInteger{ value },
		m_eType{ VariantType::Integer }
	{

	}

	Variant::Variant(const unsigned int value) :
		vUnsignedInteger{ value },
		m_eType{ VariantType::UnsignedInteger }
	{

	}

	Variant::Variant(const float value) :
		vFloat{ value },
		m_eType{ VariantType::Float }
	{

	}

	Variant::Variant(const String &value) :
		vPointer{ nullptr },
		vString{ value },
		m_eType{ VariantType::String }
	{

	}
#pragma endregion

#pragma region Getters
	Variant::VariantType Variant::getType() const
	{
		return m_eType;
	}

	bool Variant::isSet(const String &key) const
	{
		if (m_eType != VariantType::Array && m_eType != VariantType::Map)
			return false;
		for (auto item : vArray)
			if (item.first == key)
				return true;
		return false;
	}

	bool Variant::inArray(const Variant &value) const
	{
		if (m_eType != VariantType::Array && m_eType != VariantType::Map)
			return false;
		for (auto item : vArray)
			if (item.second == value)
				return true;
		return false;
	}
#pragma endregion

#pragma region Comparison operators
	bool Variant::operator==(const Variant &other) const
	{
		if (other.m_eType != m_eType)
			return false;
		switch (m_eType)
		{
		case VariantType::Pointer:
			return other.vPointer == vPointer;
		case VariantType::Bool:
			return other.vBool == vBool;
		case VariantType::Integer:
			return other.vInteger == vInteger;
		case VariantType::UnsignedInteger:
			return other.vUnsignedInteger == vUnsignedInteger;
		case VariantType::Float:
			return ntl::IsEqual<float>(other.vFloat, vFloat);
		case VariantType::String:
			return other.vString == vString;
		case VariantType::Array:
		case VariantType::Map:
			return other.vArray == vArray;
		}
		return false;
	}

	bool Variant::operator!=(const Variant &other) const
	{
		if (other.m_eType != m_eType)
			return true;
		switch (m_eType)
		{
		case VariantType::Pointer:
			return other.vPointer != vPointer;
		case VariantType::Bool:
			return other.vBool != vBool;
		case VariantType::Integer:
			return other.vInteger != vInteger;
		case VariantType::UnsignedInteger:
			return other.vUnsignedInteger != vUnsignedInteger;
		case VariantType::Float:
			return ntl::IsNotEqual<float>(other.vFloat, vFloat);
		case VariantType::String:
			return other.vString != vString;
		case VariantType::Array:
		case VariantType::Map:
			return other.vArray != vArray;
		}
		return true;
	}
#pragma endregion

#pragma region Get operators
	void Variant::operator=(void *value)
	{
		vString.clear();
		vArray.clear();
		m_eType = VariantType::Pointer;
		vPointer = value;
	}

	void Variant::operator=(const bool value)
	{
		vString.clear();
		vArray.clear();
		m_eType = VariantType::Bool;
		vBool = value;
	}

	void Variant::operator=(const int value)
	{
		vString.clear();
		vArray.clear();
		m_eType = VariantType::Integer;
		vInteger = value;
	}

	void Variant::operator=(const unsigned int value)
	{
		vString.clear();
		vArray.clear();
		m_eType = VariantType::UnsignedInteger;
		vUnsignedInteger = value;
	}

	void Variant::operator=(const float value)
	{
		vString.clear();
		vArray.clear();
		m_eType = VariantType::Float;
		vFloat = value;
	}

	void Variant::operator=(const String &value)
	{
		vArray.clear();
		m_eType = VariantType::String;
		vString = value;
	}
#pragma endregion

#pragma region Set operators
	Variant::operator void*() const
	{
		switch (m_eType)
		{
		case VariantType::Pointer:
			return vPointer;
		default:
			return nullptr;
		}
	}

	Variant::operator bool() const
	{
		switch (m_eType)
		{
		case VariantType::Pointer:
			return vPointer ? true : false;
		case VariantType::Bool:
			return vBool;
		case VariantType::Integer:
			return vInteger ? true : false;
		case VariantType::UnsignedInteger:
			return vUnsignedInteger ? true : false;
		case VariantType::Float:
			return vFloat ? true : false;
		case VariantType::String:
			return !vString.empty();
		case VariantType::Array:
		case VariantType::Map:
			return !vArray.empty();
		default:
			return false;
		}
	}

	Variant::operator int() const
	{
		switch (m_eType)
		{
		case VariantType::Pointer:
			return (int)(long long)vPointer;
		case VariantType::Bool:
			return (int)vBool;
		case VariantType::Integer:
			return vInteger;
		case VariantType::UnsignedInteger:
			return (int)vUnsignedInteger;
		case VariantType::Float:
			return (int)vFloat;
		case VariantType::String:
		{
			int v;
			if (TryStringToInt(vString, v))
				return v;
		}
		break;
		default:
			break;
		}
		return 0;
	}

	Variant::operator unsigned int() const
	{
		switch (m_eType)
		{
		case VariantType::Pointer:
			return (unsigned int)(long long)vPointer;
		case VariantType::Bool:
			return (unsigned int)vBool;
		case VariantType::Integer:
			return (unsigned int)vInteger;
		case VariantType::UnsignedInteger:
			return vUnsignedInteger;
		case VariantType::Float:
			return (unsigned int)vFloat;
		case VariantType::String:
		{
			unsigned int v;
			if (TryStringToUInt(vString, v))
				return v;
		}
		break;
		default:
			break;
		}
		return 0;
	}

	Variant::operator float() const
	{
		switch (m_eType)
		{
		case VariantType::Pointer:
			return (float)(long long)vPointer;
		case VariantType::Bool:
			return (float)vBool;
		case VariantType::Integer:
			return (float)vInteger;
		case VariantType::UnsignedInteger:
			return (float)vUnsignedInteger;
		case VariantType::Float:
			return vFloat;
		case VariantType::String:
		{
			float v;
			if (TryStringToFloat(vString, v))
				return v;
		}
		break;
		default:
			break;
		}
		return 0;
	}

	Variant::operator String() const
	{
		switch (m_eType)
		{
		case VariantType::Pointer:
		{
			if (!vPointer)
				return L"";
			std::wstringstream ss;
			ss << std::hex << vPointer;
			return ss.str();
		}
		break;
		case VariantType::Bool:
			return ToString(vBool);
		case VariantType::Integer:
			return ToString(vInteger);
		case VariantType::UnsignedInteger:
			return ToString(vUnsignedInteger);
		case VariantType::Float:
			return ToString(vFloat);
		case VariantType::String:
			return vString;
		default:
			break;
		}
		return L"";
	}
#pragma endregion

#pragma endregion Arry operators
	Variant &Variant::operator[](const wchar_t *key)
	{
		vString.clear();
		m_eType = VariantType::Map;
		for (auto &item : vArray)
			if (item.first == key)
				return item.second;
		vArray.push_back({ key, Variant{ nullptr } });
		return vArray[vArray.size() - 1].second;
	}

	Variant Variant::operator[](const int index)
	{
		if ((m_eType == VariantType::Array || m_eType == VariantType::Map) && index >= 0 && index < (int)vArray.size())
			return vArray[index].second;
		return (Variant)nullptr;
	}
#pragma endregion

#pragma region STL
	Variant::Map::iterator Variant::begin()
	{
		return vArray.begin();
	}

	Variant::Map::iterator Variant::end()
	{
		return vArray.end();
	}

	Variant::Map::const_iterator Variant::begin() const
	{
		return vArray.begin();
	}

	Variant::Map::const_iterator Variant::end() const
	{
		return vArray.end();
	}

	Variant::Map::const_iterator Variant::cbegin() const
	{
		return vArray.cbegin();
	}

	Variant::Map::const_iterator Variant::cend() const
	{
		return vArray.cend();
	}

	Variant::Map::reverse_iterator Variant::rbegin()
	{
		return vArray.rbegin();
	}

	Variant::Map::reverse_iterator Variant::rend()
	{
		return vArray.rend();
	}

	Variant::Map::const_reverse_iterator Variant::rbegin() const
	{
		return vArray.rbegin();
	}

	Variant::Map::const_reverse_iterator Variant::rend() const
	{
		return vArray.rend();
	}

	Variant::Map::const_reverse_iterator Variant::crbegin() const
	{
		return vArray.crbegin();
	}

	Variant::Map::const_reverse_iterator Variant::crend() const
	{
		return vArray.crend();
	}

	Variant::Map::size_type Variant::size() const
	{
		return vArray.size();
	}

	bool Variant::empty() const
	{
		return vArray.empty();
	}

	Variant::Map::iterator Variant::erase(Map::const_iterator _Where)
	{
		return vArray.erase(_Where);
	}

	Variant::Map::iterator Variant::erase(Map::const_iterator _First, Map::const_iterator _Last)
	{
		return vArray.erase(_First, _Last);
	}

	void Variant::clear()
	{
		return vArray.clear();
	}

	Variant::Map::const_iterator Variant::find(const String &_Keyval) const
	{
		for (auto pos = vArray.cbegin(); pos != vArray.cend(); pos++)
			if (pos->first == _Keyval)
				return pos;
		return vArray.cend();
	}

	void Variant::push_back(const Variant &value)
	{
		vString.clear();
		if (vArray.size() == 0)
			m_eType = VariantType::Array;
		else if (m_eType != VariantType::Map && m_eType != VariantType::Array)
			m_eType = VariantType::Map;
		vArray.push_back({ ToString((int)vArray.size()), value });
	}
#pragma endregion

#pragma region Safe get items
	Variant Variant::get(const wchar_t *key) const
	{
		for (auto pos = vArray.cbegin(); pos != vArray.cend(); pos++)
			if (pos->first == key)
				return pos->second;
		return (Variant)nullptr;
	}

	Variant Variant::get(const int index) const
	{
		if (index >= 0 && index < (int)vArray.size())
			return vArray[index].second;
		return (Variant)nullptr;
	}
#pragma endregion

#pragma region Helpers
	void Variant::Reset()
	{
		m_eType = VariantType::Pointer;
		vPointer = nullptr;
		vString.clear();
		vArray.clear();
	}

	String Variant::Stringify(const int level)
	{
		switch (m_eType)
		{
		case VariantType::Pointer:
		{
			std::wstringstream ss;
			ss << std::hex << vPointer;
			return ss.str();
		}
		case VariantType::Bool:
			return vBool ? L"true" : L"false";
		case VariantType::Integer:
			return ToString(vInteger);
		case VariantType::UnsignedInteger:
			return ToString(vUnsignedInteger);
		case VariantType::Float:
		{
			std::wstringstream ss;
			ss.precision(1);
			ss << std::fixed << vFloat;
			return ss.str();
		}
		case VariantType::String:
			return vString;
		case VariantType::Map:
		{
			String result;
			if (level > 0)
				result += L"{";
			bool first{ true };
			for (auto pos : vArray)
			{
				if (!first)
					result += L", ";
				first = false;
				result += pos.first + L": " + pos.second.Stringify(level + 1);
			}
			if (level > 0)
				result += L"}";
			return result;
		}
		case VariantType::Array:
		{
			String result;
			if (level > 0)
				result += L"[";
			bool first{ true };
			for (auto pos : vArray)
			{
				if (!first)
					result += L", ";
				first = false;
				result += pos.second.Stringify(level + 1);
			}
			if (level > 0)
				result += L"]";
			return result;
		}
		default:
			break;
		}
		return L"";
	}

	String Variant::Stringify()
	{
		return Stringify(0);
	}
#ifdef _DEBUG
	void Variant::Print(const AnsiString& spaces) const
	{
		switch (m_eType)
		{
		case VariantType::Pointer:
			std::cout << "(ptr)" << vPointer << std::endl;
			break;
		case VariantType::Bool:
			std::cout << "(bool)" << vBool << std::endl;
			break;
		case VariantType::Integer:
			std::cout << "(int)" << vInteger << std::endl;
			break;
		case VariantType::UnsignedInteger:
			std::cout << "(uint)" << vUnsignedInteger << std::endl;
			break;
		case VariantType::Float:
			std::cout << "(float)" << vFloat << std::endl;
			break;
		case VariantType::String:
			std::cout << "(wstring)" << StringToAnsi(vString) << std::endl;
			break;
		case VariantType::Array:
			std::cout << spaces << "[" << std::endl;
			for (auto pos : vArray)
				pos.second.Print(spaces + "  ");
			std::cout << spaces << "]" << std::endl;
			break;
		case VariantType::Map:
			std::cout << spaces << "{" << std::endl;
			for (auto pos : vArray)
			{
				std::cout << spaces << "  " << StringToAnsi(pos.first) << ": ";
				pos.second.Print(spaces + "  ");
			}
			std::cout << spaces << "}" << std::endl;
			break;
		}
	}
#endif
#pragma endregion
}
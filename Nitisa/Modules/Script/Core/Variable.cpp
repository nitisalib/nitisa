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
	#pragma region Constructor & destructor
		Variable::Variable() :
			m_eType{ VariableType::Null }
		{

		}

		Variable::Variable(const VariableType type) :
			m_eType{ type },
			m_bValue{ false },
			m_iValue{ 0 },
			m_fValue{ 0 }
		{

		}

		Variable::Variable(const bool value) :
			m_eType{ VariableType::Bool },
			m_bValue{ value }
		{

		}

		Variable::Variable(const int64 value) :
			m_eType{ VariableType::Integer },
			m_iValue{ value }
		{

		}

		Variable::Variable(const double value) :
			m_eType{ VariableType::Float },
			m_fValue{ value }
		{

		}

		Variable::Variable(const String &value) :
			m_eType{ VariableType::String },
			m_sValue{ value }
		{

		}

		Variable::Variable(const wchar_t *value) :
			m_eType{ VariableType::String },
			m_sValue{ value }
		{

		}

		Variable::Variable(const Array &value) :
			m_eType{ VariableType::Array }
		{
			m_aValue = value;
		}

		Variable::Variable(const Object &value) :
			m_eType{ VariableType::Object },
			m_oValue{ value }
		{

		}

		Variable::Variable(const Variable &other) :
			m_eType{ other.m_eType },
			m_bValue{ other.m_bValue },
			m_iValue{ other.m_iValue },
			m_fValue{ other.m_fValue },
			m_sValue{ other.m_sValue },
			m_oValue{ other.m_oValue }
		{
			m_aValue = other.m_aValue;
		}

		Variable::Variable(Variable &&other) :
			m_eType{ other.m_eType },
			m_bValue{ other.m_bValue },
			m_iValue{ other.m_iValue },
			m_fValue{ other.m_fValue },
			m_sValue{ std::move(other.m_sValue) },
			m_oValue{ std::move(other.m_oValue) }
		{
			m_aValue = std::move(other.m_aValue);
		}
	#pragma endregion

	#pragma region Assign operators
		Variable &Variable::operator=(const Pointer value)
		{
			if (m_eType != VariableType::Null)
			{
				m_eType = VariableType::Null;
				m_sValue.clear();
				m_aValue.clear();
				m_oValue.clear();
			}
			return *this;
		}

		Variable &Variable::operator=(const bool value)
		{
			m_bValue = value;
			if (m_eType != VariableType::Bool)
			{
				m_eType = VariableType::Bool;
				m_sValue.clear();
				m_aValue.clear();
				m_oValue.clear();
			}
			return *this;
		}

		Variable &Variable::operator=(const int64 value)
		{
			m_iValue = value;
			if (m_eType != VariableType::Integer)
			{
				m_eType = VariableType::Integer;
				m_sValue.clear();
				m_aValue.clear();
				m_oValue.clear();
			}
			return *this;
		}

		Variable &Variable::operator=(const double value)
		{
			m_fValue = value;
			if (m_eType != VariableType::Float)
			{
				m_eType = VariableType::Float;
				m_sValue.clear();
				m_aValue.clear();
				m_oValue.clear();
			}
			return *this;
		}

		Variable &Variable::operator=(const String &value)
		{
			m_sValue = value;
			if (m_eType != VariableType::String)
			{
				m_eType = VariableType::String;
				m_aValue.clear();
				m_oValue.clear();
			}
			return *this;
		}

		Variable &Variable::operator=(const wchar_t *value)
		{
			m_sValue = value;
			if (m_eType != VariableType::String)
			{
				m_eType = VariableType::String;
				m_aValue.clear();
				m_oValue.clear();
			}
			return *this;
		}

		Variable &Variable::operator=(const Variable &other)
		{
			m_eType = other.m_eType;
			m_bValue = other.m_bValue;
			m_iValue = other.m_iValue;
			m_fValue = other.m_fValue;
			m_sValue = other.m_sValue;
			m_aValue = other.m_aValue;
			m_oValue = other.m_oValue;
			return *this;
		}

		Variable &Variable::operator=(Variable &&other)
		{
			m_eType = other.m_eType;
			m_bValue = other.m_bValue;
			m_iValue = other.m_iValue;
			m_fValue = other.m_fValue;
			m_sValue = std::move(other.m_sValue);
			m_aValue = std::move(other.m_aValue);
			m_oValue = std::move(other.m_oValue);
			return *this;
		}
	#pragma endregion

	#pragma region Convert operators
		Variable::operator Pointer() const
		{
			return nullptr;
		}

		Variable::operator bool() const
		{
			switch (m_eType)
			{
			case VariableType::Bool:
				return m_bValue;
			case VariableType::Integer:
				return m_iValue ? true : false;
			case VariableType::Float:
				return ntl::IsNotZero<double>(m_fValue);
			case VariableType::String:
				return !m_sValue.empty();
			case VariableType::Array:
				return !m_aValue.empty();
			case VariableType::Object:
				return !m_oValue.empty();
			default:
				return false;
			}
		}

		Variable::operator int64() const
		{
			switch (m_eType)
			{
			case VariableType::Bool:
				return m_bValue ? 1 : 0;
			case VariableType::Integer:
				return m_iValue;
			case VariableType::Float:
				return (int64)m_fValue;
			case VariableType::String:
			{
				int64 i;
				if (TryStringToInt64(m_sValue, i))
					return i;
				return 0;
			}
			default:
				return 0;
			}
		}

		Variable::operator double() const
		{
			switch (m_eType)
			{
			case VariableType::Bool:
				return m_bValue ? 1 : 0;
			case VariableType::Integer:
				return (double)m_iValue;
			case VariableType::Float:
				return m_fValue;
			case VariableType::String:
			{
				double f;
				if (TryStringToDouble(m_sValue, f))
					return f;
				return 0;
			}
			default:
				return 0;
			}
		}

		Variable::operator String() const
		{
			switch (m_eType)
			{
			case VariableType::Null:
				return L"nullptr";
			case VariableType::Bool:
				return m_bValue ? L"true" : L"false";
			case VariableType::Integer:
				return ToString(m_iValue);
			case VariableType::Float:
				return ToStringCompact(m_fValue);
			case VariableType::String:
				return m_sValue;
			default:
				return L"";
			}
		}
	#pragma endregion

	#pragma region Access operators
		Variable &Variable::operator[](const String &key)
		{
			if (m_eType == VariableType::Array)
			{
				for (size_t i = 0; i < m_aValue.size(); i++)
					m_oValue[ToString(uint64(i))] = m_aValue[i];
				m_aValue.clear();
			}
			m_eType = VariableType::Object;
			return m_oValue[key];
		}

		Variable &Variable::operator[](const wchar_t *key)
		{
			if (m_eType == VariableType::Array)
			{
				for (size_t i = 0; i < m_aValue.size(); i++)
					m_oValue[ToString(uint64(i))] = m_aValue[i];
				m_aValue.clear();
			}
			m_eType = VariableType::Object;
			return m_oValue[key];
		}

		Variable &Variable::operator[](const size_t index)
		{
			if (m_eType != VariableType::Array)
			{
				m_eType = VariableType::Array;
				m_sValue.clear();
				m_oValue.clear();
			}
			return m_aValue[index];
		}

		const Variable &Variable::operator[](const size_t index) const
		{
			return m_aValue[index];
		}
	#pragma endregion

	#pragma region Comparison operators
		bool Variable::operator==(const Variable &other) const
		{
			switch (m_eType)
			{
			case VariableType::Array:
				switch (other.m_eType)
				{
				case VariableType::Array: return m_aValue == other.m_aValue;
				case VariableType::Bool: return false;
				case VariableType::Float: return false;
				case VariableType::Integer: return false;
				case VariableType::Null: return false;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Bool:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return m_bValue == other.m_bValue;
				case VariableType::Float: return m_bValue == (bool)other.m_fValue;
				case VariableType::Integer: return m_bValue == (bool)other.m_iValue;
				case VariableType::Null: return m_bValue == false;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Float:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return (bool)m_fValue == other.m_bValue;
				case VariableType::Float: return m_fValue == other.m_fValue;
				case VariableType::Integer: return (int64)m_fValue == other.m_iValue;
				case VariableType::Null: return false;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Integer:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return (bool)m_iValue == other.m_bValue;
				case VariableType::Float: return m_iValue == (int64)other.m_fValue;
				case VariableType::Integer: return m_iValue == other.m_iValue;
				case VariableType::Null: return m_iValue == 0;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Null:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return false == other.m_bValue;
				case VariableType::Float: return false;
				case VariableType::Integer: return 0 == other.m_iValue;
				case VariableType::Null: return true;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Object:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return false;
				case VariableType::Float: return false;
				case VariableType::Integer: return false;
				case VariableType::Null: return false;
				case VariableType::Object: return m_oValue == other.m_oValue;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::String:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return false;
				case VariableType::Float: return false;
				case VariableType::Integer: return false;
				case VariableType::Null: return false;
				case VariableType::Object: return false;
				case VariableType::String: return m_sValue == other.m_sValue;
				default: return false;
				}
			default: return false;
			}
		}

		bool Variable::operator!=(const Variable &other) const
		{
			switch (m_eType)
			{
			case VariableType::Array:
				switch (other.m_eType)
				{
				case VariableType::Array: return m_aValue != other.m_aValue;
				case VariableType::Bool: return true;
				case VariableType::Float: return true;
				case VariableType::Integer: return true;
				case VariableType::Null: return true;
				case VariableType::Object: return true;
				case VariableType::String: return true;
				default: return true;
				}
			case VariableType::Bool:
				switch (other.m_eType)
				{
				case VariableType::Array: return true;
				case VariableType::Bool: return m_bValue != other.m_bValue;
				case VariableType::Float: return m_bValue != (bool)other.m_fValue;
				case VariableType::Integer: return m_bValue != (bool)other.m_iValue;
				case VariableType::Null: return m_bValue != false;
				case VariableType::Object: return true;
				case VariableType::String: return true;
				default: return true;
				}
			case VariableType::Float:
				switch (other.m_eType)
				{
				case VariableType::Array: return true;
				case VariableType::Bool: return (bool)m_fValue != other.m_bValue;
				case VariableType::Float: return m_fValue != other.m_fValue;
				case VariableType::Integer: return (int64)m_fValue != other.m_iValue;
				case VariableType::Null: return true;
				case VariableType::Object: return true;
				case VariableType::String: return true;
				default: return true;
				}
			case VariableType::Integer:
				switch (other.m_eType)
				{
				case VariableType::Array: return true;
				case VariableType::Bool: return (bool)m_iValue != other.m_bValue;
				case VariableType::Float: return m_iValue != (int64)other.m_fValue;
				case VariableType::Integer: return m_iValue != other.m_iValue;
				case VariableType::Null: return m_iValue != 0;
				case VariableType::Object: return true;
				case VariableType::String: return true;
				default: return true;
				}
			case VariableType::Null:
				switch (other.m_eType)
				{
				case VariableType::Array: return true;
				case VariableType::Bool: return false != other.m_bValue;
				case VariableType::Float: return true;
				case VariableType::Integer: return 0 != other.m_iValue;
				case VariableType::Null: return false;
				case VariableType::Object: return true;
				case VariableType::String: return true;
				default: return true;
				}
			case VariableType::Object:
				switch (other.m_eType)
				{
				case VariableType::Array: return true;
				case VariableType::Bool: return true;
				case VariableType::Float: return true;
				case VariableType::Integer: return true;
				case VariableType::Null: return true;
				case VariableType::Object: return m_oValue != other.m_oValue;
				case VariableType::String: return true;
				default: return true;
				}
			case VariableType::String:
				switch (other.m_eType)
				{
				case VariableType::Array: return true;
				case VariableType::Bool: return true;
				case VariableType::Float: return true;
				case VariableType::Integer: return true;
				case VariableType::Null: return true;
				case VariableType::Object: return true;
				case VariableType::String: return m_sValue != other.m_sValue;
				default: return true;
				}
			default: return true;
			}
		}

		bool Variable::operator>(const Variable &other) const
		{
			switch (m_eType)
			{
			case VariableType::Array:
				switch (other.m_eType)
				{
				case VariableType::Array: return m_aValue > other.m_aValue;
				case VariableType::Bool: return false;
				case VariableType::Float: return false;
				case VariableType::Integer: return false;
				case VariableType::Null: return false;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Bool:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return m_bValue > other.m_bValue;
				case VariableType::Float: return m_bValue > (bool)other.m_fValue;
				case VariableType::Integer: return m_bValue > (bool)other.m_iValue;
				case VariableType::Null: return m_bValue > false;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Float:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return (bool)m_fValue > other.m_bValue;
				case VariableType::Float: return m_fValue > other.m_fValue;
				case VariableType::Integer: return (int64)m_fValue > other.m_iValue;
				case VariableType::Null: return false;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Integer:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return (bool)m_iValue > other.m_bValue;
				case VariableType::Float: return m_iValue > (int64)other.m_fValue;
				case VariableType::Integer: return m_iValue > other.m_iValue;
				case VariableType::Null: return m_iValue > 0;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Null:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return false;
				case VariableType::Float: return false;
				case VariableType::Integer: return 0 > other.m_iValue;
				case VariableType::Null: return false;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Object:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return false;
				case VariableType::Float: return false;
				case VariableType::Integer: return false;
				case VariableType::Null: return false;
				case VariableType::Object: return m_oValue > other.m_oValue;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::String:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return false;
				case VariableType::Float: return false;
				case VariableType::Integer: return false;
				case VariableType::Null: return false;
				case VariableType::Object: return false;
				case VariableType::String: return m_sValue > other.m_sValue;
				default: return false;
				}
			default: return false;
			}
		}

		bool Variable::operator<(const Variable &other) const
		{
			switch (m_eType)
			{
			case VariableType::Array:
				switch (other.m_eType)
				{
				case VariableType::Array: return m_aValue < other.m_aValue;
				case VariableType::Bool: return false;
				case VariableType::Float: return false;
				case VariableType::Integer: return false;
				case VariableType::Null: return false;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Bool:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return m_bValue < other.m_bValue;
				case VariableType::Float: return m_bValue < (bool)other.m_fValue;
				case VariableType::Integer: return m_bValue < (bool)other.m_iValue;
				case VariableType::Null: return false;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Float:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return (bool)m_fValue < other.m_bValue;
				case VariableType::Float: return m_fValue < other.m_fValue;
				case VariableType::Integer: return (int64)m_fValue < other.m_iValue;
				case VariableType::Null: return false;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Integer:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return (bool)m_iValue < other.m_bValue;
				case VariableType::Float: return m_iValue < (int64)other.m_fValue;
				case VariableType::Integer: return m_iValue < other.m_iValue;
				case VariableType::Null: return m_iValue < 0;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Null:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return false < other.m_bValue;
				case VariableType::Float: return false;
				case VariableType::Integer: return 0 < other.m_iValue;
				case VariableType::Null: return false;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Object:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return false;
				case VariableType::Float: return false;
				case VariableType::Integer: return false;
				case VariableType::Null: return false;
				case VariableType::Object: return m_oValue < other.m_oValue;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::String:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return false;
				case VariableType::Float: return false;
				case VariableType::Integer: return false;
				case VariableType::Null: return false;
				case VariableType::Object: return false;
				case VariableType::String: return m_sValue < other.m_sValue;
				default: return false;
				}
			default: return false;
			}
		}

		bool Variable::operator>=(const Variable &other) const
		{
			switch (m_eType)
			{
			case VariableType::Array:
				switch (other.m_eType)
				{
				case VariableType::Array: return m_aValue >= other.m_aValue;
				case VariableType::Bool: return false;
				case VariableType::Float: return false;
				case VariableType::Integer: return false;
				case VariableType::Null: return false;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Bool:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return m_bValue >= other.m_bValue;
				case VariableType::Float: return m_bValue >= (bool)other.m_fValue;
				case VariableType::Integer: return m_bValue >= (bool)other.m_iValue;
				case VariableType::Null: return true;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Float:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return (bool)m_fValue >= other.m_bValue;
				case VariableType::Float: return m_fValue >= other.m_fValue;
				case VariableType::Integer: return (int64)m_fValue >= other.m_iValue;
				case VariableType::Null: return false;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Integer:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return (bool)m_iValue >= other.m_bValue;
				case VariableType::Float: return m_iValue >= (int64)other.m_fValue;
				case VariableType::Integer: return m_iValue >= other.m_iValue;
				case VariableType::Null: return m_iValue >= 0;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Null:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return false >= other.m_bValue;
				case VariableType::Float: return false;
				case VariableType::Integer: return 0 >= other.m_iValue;
				case VariableType::Null: return true;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Object:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return false;
				case VariableType::Float: return false;
				case VariableType::Integer: return false;
				case VariableType::Null: return false;
				case VariableType::Object: return m_oValue >= other.m_oValue;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::String:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return false;
				case VariableType::Float: return false;
				case VariableType::Integer: return false;
				case VariableType::Null: return false;
				case VariableType::Object: return false;
				case VariableType::String: return m_sValue >= other.m_sValue;
				default: return false;
				}
			default: return false;
			}
		}

		bool Variable::operator<=(const Variable &other) const
		{
			switch (m_eType)
			{
			case VariableType::Array:
				switch (other.m_eType)
				{
				case VariableType::Array: return m_aValue <= other.m_aValue;
				case VariableType::Bool: return false;
				case VariableType::Float: return false;
				case VariableType::Integer: return false;
				case VariableType::Null: return false;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Bool:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return m_bValue <= other.m_bValue;
				case VariableType::Float: return m_bValue <= (bool)other.m_fValue;
				case VariableType::Integer: return m_bValue <= (bool)other.m_iValue;
				case VariableType::Null: return m_bValue <= false;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Float:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return (bool)m_fValue <= other.m_bValue;
				case VariableType::Float: return m_fValue <= other.m_fValue;
				case VariableType::Integer: return (int64)m_fValue <= other.m_iValue;
				case VariableType::Null: return false;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Integer:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return (bool)m_iValue <= other.m_bValue;
				case VariableType::Float: return m_iValue <= (int64)other.m_fValue;
				case VariableType::Integer: return m_iValue <= other.m_iValue;
				case VariableType::Null: return m_iValue <= 0;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Null:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return true;
				case VariableType::Float: return false;
				case VariableType::Integer: return 0 <= other.m_iValue;
				case VariableType::Null: return true;
				case VariableType::Object: return false;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::Object:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return false;
				case VariableType::Float: return false;
				case VariableType::Integer: return false;
				case VariableType::Null: return false;
				case VariableType::Object: return m_oValue <= other.m_oValue;
				case VariableType::String: return false;
				default: return false;
				}
			case VariableType::String:
				switch (other.m_eType)
				{
				case VariableType::Array: return false;
				case VariableType::Bool: return false;
				case VariableType::Float: return false;
				case VariableType::Integer: return false;
				case VariableType::Null: return false;
				case VariableType::Object: return false;
				case VariableType::String: return m_sValue <= other.m_sValue;
				default: return false;
				}
			default: return false;
			}
		}
	#pragma endregion

	#pragma region Methods
		VariableType Variable::type() const
		{
			return m_eType;
		}

		bool Variable::type(const VariableType value)
		{
			if (value != m_eType)
			{
				m_eType = value;
				m_bValue = false;
				m_iValue = 0;
				m_fValue = 0;
				m_sValue.clear();
				m_aValue.clear();
				m_oValue.clear();
				return true;
			}
			return false;
		}

		bool Variable::has(const String &key) const
		{
			return m_eType == VariableType::Object && m_oValue.find(key) != m_oValue.end();
		}

		size_t Variable::size() const
		{
			switch (m_eType)
			{
			case VariableType::String:
				return m_sValue.size();
			case VariableType::Array:
				return m_aValue.size();
			case VariableType::Object:
				return m_oValue.size();
			default:
				return 0;
			}
		}

		size_t Variable::count() const
		{
			size_t result{ 1 };
			switch (m_eType)
			{
			case VariableType::Array:
				for (auto const &e : m_aValue)
					result += e.count();
				break;
			case VariableType::Object:
				for (auto const &e : m_oValue)
					result += e.second.count();
				break;
			default:
				break;
			}
			return result;
		}

		bool Variable::empty() const
		{
			switch (m_eType)
			{
			case VariableType::String:
				return m_sValue.empty();
			case VariableType::Array:
				return m_aValue.empty();
			case VariableType::Object:
				return m_oValue.empty();
			default:
				return true;
			}
		}

		void Variable::push_back(const Variable &value)
		{
			if (m_eType != VariableType::Array)
			{
				m_eType = VariableType::Array;
				m_sValue.clear();
				m_oValue.clear();
			}
			m_aValue.push_back(value);
		}

		void Variable::clear()
		{
			if (m_eType != VariableType::Null)
			{
				m_eType = VariableType::Null;
				m_sValue.clear();
				m_aValue.clear();
				m_oValue.clear();
			}
		}

		void Variable::erase(const size_t index)
		{
			if (m_eType != VariableType::Array)
			{
				m_eType = VariableType::Array;
				m_sValue.clear();
				m_oValue.clear();
			}
			else
				m_aValue.erase(m_aValue.begin() + index);
		}

		void Variable::erase(const size_t index, const size_t count)
		{
			if (m_eType != VariableType::Array)
			{
				m_eType = VariableType::Array;
				m_sValue.clear();
				m_oValue.clear();
			}
			else
				m_aValue.erase(m_aValue.begin() + index, m_aValue.begin() + index + count);
		}

		Variable::Object::iterator Variable::erase(Object::iterator where)
		{
			if (m_eType != VariableType::Object)
			{
				m_eType = VariableType::Object;
				m_sValue.clear();
				m_aValue.clear();
			}
			return m_oValue.erase(where);
		}

		Variable::Object::iterator Variable::erase(Object::iterator first, Object::iterator last)
		{
			if (m_eType != VariableType::Object)
			{
				m_eType = VariableType::Object;
				m_sValue.clear();
				m_aValue.clear();
			}
			return m_oValue.erase(first, last);
		}

		Variable::Object::iterator Variable::find(const String &key)
		{
			if (m_eType != VariableType::Object)
			{
				m_eType = VariableType::Object;
				m_sValue.clear();
				m_aValue.clear();
			}
			return m_oValue.find(key);
		}

		const Variable *Variable::get(const String &key) const
		{
			if (m_eType == VariableType::Object)
			{
				for (auto const &o : m_oValue)
					if (o.first == key)
						return &o.second;
			}
			return nullptr;
		}
	#pragma endregion

	#pragma region Iterators
		Variable::Object::iterator Variable::begin()
		{
			if (m_eType != VariableType::Object)
			{
				m_eType = VariableType::Object;
				m_sValue.clear();
				m_aValue.clear();
			}
			return m_oValue.begin();
		}

		Variable::Object::iterator Variable::end()
		{
			if (m_eType != VariableType::Object)
			{
				m_eType = VariableType::Object;
				m_sValue.clear();
				m_aValue.clear();
			}
			return m_oValue.end();
		}

		Variable::Object::reverse_iterator Variable::rbegin()
		{
			if (m_eType != VariableType::Object)
			{
				m_eType = VariableType::Object;
				m_sValue.clear();
				m_aValue.clear();
			}
			return m_oValue.rbegin();
		}

		Variable::Object::reverse_iterator Variable::rend()
		{
			if (m_eType != VariableType::Object)
			{
				m_eType = VariableType::Object;
				m_sValue.clear();
				m_aValue.clear();
			}
			return m_oValue.rend();
		}

		Variable::Object::const_iterator Variable::begin() const
		{
			return m_oValue.begin();
		}

		Variable::Object::const_iterator Variable::end() const
		{
			return m_oValue.end();
		}

		Variable::Object::const_reverse_iterator Variable::rbegin() const
		{
			return m_oValue.rbegin();
		}

		Variable::Object::const_reverse_iterator Variable::rend() const
		{
			return m_oValue.rend();
		}
	#pragma endregion

	#pragma region Helpers
		String Variable::toString() const
		{
			switch (m_eType)
			{
			case VariableType::Null:
				return L"nullptr";
			case VariableType::Bool:
				return m_bValue ? L"true" : L"false";
			case VariableType::Integer:
				return ToString(m_iValue);
			case VariableType::Float:
				return ToStringCompact(m_fValue);
			case VariableType::String:
				return m_sValue;
			case VariableType::Array:
			{
				String result{ L"[" };
				for (size_t i = 0; i < m_aValue.size(); i++)
				{
					if (i > 0)
						result += L", ";
					result += m_aValue[i].toString();
				}
				return result + L"]";
			}
			case VariableType::Object:
			{
				String result{ L"{ " };
				size_t i{ 0 };
				for (auto o : m_oValue)
				{
					if (i++ > 0)
						result += L", ";
					result += o.first + L": " + o.second.toString();
				}
				if (!m_oValue.empty())
					result += L" ";
				return result + L"}";
			}
			default:
				return L"";
			}
		}
	#pragma endregion
	}
}
// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "../Interfaces/IDbAttribute.h"
#include "DbModel.h"
#include "DbValue.h"
#include "DbValueType.h"

namespace nitisa
{
	template<class Type>
	class TDbAttribute : public virtual IDbAttribute
	{
	private:
		struct OldValue
		{
			bool Null;
			Type Value;
		};
	private:
		Type m_tValue;
		OldValue m_sOldValue;
	protected:
		void SetInternal(const DbValue &value, const bool &changed) override // Change value marking as changed or unchanged
		{
			if (changed)
			{
				if (!m_bChanged)
				{
					m_sOldValue.Null = m_bNull;
					m_sOldValue.Value = m_tValue;
					m_bChanged = true;
				}
			}
			else
				m_bChanged = false;
			m_bNull = value.Type == DbValueType::Null;
			m_tValue = (Type)value;
		}
	public:
		TDbAttribute(CDbModel *model, const String &name) : // Constructor specifying parent model and attribute name
			IDbAttribute(name)
		{
			model->Attributes.Add(this);
		}

		TDbAttribute(CDbModel *model, const String &name, const Type &value) : // Constructor specifying parent model, attribute name and attribute value
			IDbAttribute(name)
		{
			model->Attributes.Add(this);
			m_tValue = value;
			m_bNull = false;
		}

		TDbAttribute(CDbModel *model, const wchar_t *name) : // Constructor specifying parent model and attribute name
			IDbAttribute(name)
		{
			model->Attributes.Add(this);
		}

		TDbAttribute(CDbModel *model, const wchar_t *name, const Type &value) : // Constructor specifying parent model, attribute name and attribute value
			IDbAttribute(name)
		{
			model->Attributes.Add(this);
			m_tValue = value;
			m_bNull = false;
		}

		template<class T> TDbAttribute(T) = delete;

		TDbAttribute &operator=(const Type &value) // Attribute value assignment operator
		{
			if (!m_bChanged)
			{
				m_sOldValue.Null = m_bNull;
				m_sOldValue.Value = m_tValue;
				m_bChanged = true;
			}
			m_tValue = value;
			m_bNull = false;
			return *this;
		}

		TDbAttribute &operator=(void *) // Assigning any pointer value will mark attribute as Null
		{
			if (!m_bChanged)
			{
				m_sOldValue.Null = m_bNull;
				m_sOldValue.Value = m_tValue;
				m_bChanged = true;
			}
			m_bNull = true;
			return *this;
		}

		template<class T> TDbAttribute &operator=(T type) = delete;

		operator Type() // Getting value operator
		{
			return m_tValue;
		}

		void Set(const DbValue &value) override // Set attribute value from specified DbValue
		{
			SetInternal(value, true);
		}

		DbValue Get() const override // Return attribute value in form of DbValue
		{
			if (m_bNull)
				return DbValue{ };
			return DbValue{ m_tValue };
		}

		DbValue Old() const override // Return old attribute value in form of DbValue
		{
			if (!m_bChanged)
				return Get();
			if (m_sOldValue.Null)
				return DbValue{ };
			return DbValue{ m_sOldValue.Value };
		}
	};
}
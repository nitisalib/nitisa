// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	CPropertyMatrixState::CPropertyMatrixState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerMatrix, skip, read_only, states, state_prefix_type, state_prefix),
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false }
	{
		AddHeaderFile(L"Nitisa/Math/Mat4f.h");
		AddHeaderFile(L"Nitisa/Math/Vec4f.h");
		for (int i = 0; i < getStateCount(); i++)
		{
			m_aOld[getState(i)] = m_fGetter(m_pParent, getState(i));
			m_aValue[getState(i)] = m_fGetter(m_pParent, getState(i));
		}
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyMatrixState::getPreview()
	{
		return L"";
	}

	String CPropertyMatrixState::getPreview(const String &state)
	{
		return ToString(getValue(state));
	}

	bool CPropertyMatrixState::isChanged()
	{
		if (m_bChanged)
			return true;
		for (int i = 0; i < getStateCount(); i++)
			if (ntl::IsNotEqual<float>(getValue(getState(i)), m_aOld[getState(i)]))
				return true;
		return false;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyMatrixState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyMatrixState::Copy(IProperty *dest)
	{
		IPropertyMatrixState *d{ cast<IPropertyMatrixState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyMatrixState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			dest[getState(i).c_str()] = ToVariant(getValue(getState(i)));
	}

	void CPropertyMatrixState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			Mat4f v;
			FromVariant(src.get(getState(i).c_str()), v);
			setValue(getState(i), v);
		}
	}

	void CPropertyMatrixState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
		{
			if (control.empty())
				f << shift << L"set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(" << state_prefix << getState(i) << L", " << AsSourceCode(getValue(getState(i))) << L");" << std::endl;
		}
	}
#pragma endregion

#pragma region IPropertyMatrixState getters
	Mat4f CPropertyMatrixState::getValue(const String &state)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent, state);
		return m_aValue[state];
	}
#pragma endregion

#pragma region IPropertyMatrixState setters
	bool CPropertyMatrixState::setValue(const String &state, const Mat4f value)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, state, value);
		if (ntl::IsNotEqual<float>(value, m_aValue[state]))
		{
			m_aValue[state] = value;
			return true;
		}
		return false;
	}
#pragma endregion
}
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
	CPropertyHotkeyState::CPropertyHotkeyState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix,
		FSkip skip,
		FGetter getter,
		FSetter setter) : CPropertyState(list, parent, name, PropertyHandlerHotkey, skip, read_only, states, state_prefix_type, state_prefix),
		m_fGetter{ getter },
		m_fSetter{ setter },
		m_bChanged{ false }
	{
		AddHeaderFile(L"Nitisa/Core/Hotkey.h");
		AddHeaderFile(L"Nitisa/Core/Key.h");
		for (int i = 0; i < getStateCount(); i++)
		{
			m_aOld[getState(i)] = m_fGetter(m_pParent, getState(i));
			m_aValue[getState(i)] = m_fGetter(m_pParent, getState(i));
		}
	}
#pragma endregion

#pragma region IProperty getters
	String CPropertyHotkeyState::getPreview()
	{
		return L"";
	}

	String CPropertyHotkeyState::getPreview(const String &state)
	{
		return CTranslate::Hotkey(getValue(state));
	}

	bool CPropertyHotkeyState::isChanged()
	{
		if (m_bChanged)
			return true;
		for (int i = 0; i < getStateCount(); i++)
			if (getValue(getState(i)) != m_aOld[getState(i)])
				return true;
		return false;
	}
#pragma endregion

#pragma region IProperty setters
	IProperty *CPropertyHotkeyState::setChanged(const bool value)
	{
		m_bChanged = value;
		return this;
	}
#pragma endregion

#pragma region IProperty methods
	bool CPropertyHotkeyState::Copy(IProperty *dest)
	{
		IPropertyHotkeyState *d{ cast<IPropertyHotkeyState*>(dest) };
		if (d && d->getStateCount() == getStateCount())
		{
			for (int i = 0; i < getStateCount(); i++)
				d->setValue(getState(i), getValue(getState(i)));
			return true;
		}
		return false;
	}

	void CPropertyHotkeyState::Save(Variant &dest)
	{
		dest.Reset();
		for (int i = 0; i < getStateCount(); i++)
			dest[getState(i).c_str()] = ToVariant(getValue(getState(i)));
	}

	void CPropertyHotkeyState::Load(const Variant &src)
	{
		for (int i = 0; i < getStateCount(); i++)
		{
			Hotkey v;
			FromVariant(src.get(getState(i).c_str()), v);
			setValue(getState(i), v);
		}
	}

	void CPropertyHotkeyState::Export(std::wofstream &f, const String &shift, const String &control)
	{
		String state_prefix{ Prefix(getStatePrefixType(), getStatePrefix()) };
		for (int i = 0; i < getStateCount(); i++)
		{
			Hotkey v{ getValue(getState(i)) };
			if (control.empty())
				f << shift << L"set" << m_sName << L"(" << state_prefix + getState(i) + L", " << AsSourceCode(v) << L");" << std::endl;
			else
				f << shift << control << L"->set" << m_sName << L"(" << state_prefix + getState(i) + L", " << AsSourceCode(v) << L");" << std::endl;
		}
	}
#pragma endregion

#pragma region IPropertyHotkeyState getters
	Hotkey CPropertyHotkeyState::getValue(const String &state)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fGetter(m_pParent, state);
		return m_aValue[state];
	}
#pragma endregion

#pragma region IPropertyHotkeyState setters
	bool CPropertyHotkeyState::setValue(const String &state, const Hotkey value)
	{
		if (!isReadOnly() || !Application->Editor)
			return m_fSetter(m_pParent, state, value);
		if (value != m_aValue[state])
		{
			m_aValue[state] = value;
			return true;
		}
		return false;
	}
#pragma endregion
}
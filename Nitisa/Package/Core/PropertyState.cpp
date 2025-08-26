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
	CPropertyState::CPropertyState(
		IPropertyList *list,
		IClass *parent,
		const String &name,
		const String &handler,
		FSkip skip,
		const bool read_only,
		const StringArray &states,
		const ExportPrefixType state_prefix_type,
		const String &state_prefix) : CProperty(list, parent, name, handler, skip, read_only),
		m_aStates{ states },
		m_eStatePrefixType{ state_prefix_type },
		m_sStatePrefix{ state_prefix }
	{

	}

	int CPropertyState::getStateCount()
	{
		return (int)m_aStates.size();
	}

	String CPropertyState::getState(const int index)
	{
		if (index >= 0 && index < (int)m_aStates.size())
			return m_aStates[index];
		return L"";
	}

	ExportPrefixType CPropertyState::getStatePrefixType()
	{
		return m_eStatePrefixType;
	}

	String CPropertyState::getStatePrefix()
	{
		return m_sStatePrefix;
	}
}
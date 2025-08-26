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
	CProperty::CProperty(IPropertyList *list, IClass *parent, const String &name, const String &handler, FSkip skip, const bool read_only) :
		m_fSkip{ skip },
		m_bReadOnly{ read_only }
	{
		m_sName = name;
		m_sPropertyHandlerName = handler;
		m_pParent = parent;
		m_pPropertyList = list;
		m_bAffectItems = false;
	}

	void CProperty::Release()
	{
		delete this;
	}
#pragma endregion

#pragma region Getters
	bool CProperty::isSkip()
	{
		return m_fSkip && m_fSkip(m_pParent);
	}

	bool CProperty::isReadOnly() const
	{
		return m_bReadOnly;
	}

	int CProperty::getHeaderFileCount()
	{
		return (int)m_aHeaderFiles.size();
	}

	String CProperty::getHeaderFile(const int index)
	{
		if (index >= 0 && index < (int)m_aHeaderFiles.size())
			return m_aHeaderFiles[index];
		return L"";
	}

	int CProperty::getForwardDeclarationCount()
	{
		return (int)m_aForwardDeclarations.size();
	}

	IProperty::ForwardDeclaration CProperty::getForwardDeclaration(const int index)
	{
		if (index >= 0 && index < (int)m_aForwardDeclarations.size())
			return m_aForwardDeclarations[index];
		return ForwardDeclaration{ L"", L"" };
	}
#pragma endregion

#pragma region Setters
	void CProperty::setParent(IClass *parent)
	{
		m_pParent = parent;
	}

	IProperty *CProperty::setAffectItems(const bool value)
	{
		m_bAffectItems = value;
		return this;
	}
#pragma endregion

#pragma region Helpers
	String CProperty::Prefix(const ExportPrefixType prefix_type, const String &prefix)
	{
		switch (prefix_type)
		{
		case ExportPrefixType::Parent:
			if (m_pParent)
				return L"C" + m_pParent->ClassName + L"::" + prefix;
			return prefix;
		case ExportPrefixType::Namespace:
			if (m_pPropertyList && m_pPropertyList->getEntity())
			{
				String result{ m_pPropertyList->getEntity()->getNamespace() };
				if (!result.empty())
					return result + L"::" + prefix;
			}
			return prefix;
		case ExportPrefixType::NamespaceParent:
			if (m_pPropertyList && m_pPropertyList->getEntity())
			{
				String result{ m_pPropertyList->getEntity()->getNamespace() };
				if (!result.empty())
					result += L"::";
				if (m_pParent)
					result += L"C" + m_pParent->ClassName + L"::";
				return result + prefix;
			}
			return prefix;
		default:
			return prefix;
		}
	}

	CProperty *CProperty::AddHeaderFile(const String &value)
	{
		m_aHeaderFiles.push_back(value);
		return this;
	}
	
	CProperty *CProperty::AddForwardDeclaration(const String &value, const String &header_file, const String &ns)
	{
		m_aForwardDeclarations.push_back(ForwardDeclaration{ value, header_file, ns });
		return this;
	}
#pragma endregion
}
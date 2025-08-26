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
	CEvent::CEvent(IEventList *list, IClass *parent, const String &name, const String &signature, const String &arguments) :
		m_pEventList{ list },
		m_pParent{ parent },
		m_sName{ name },
		m_sSignature{ signature },
		m_sArguments{ arguments }
	{

	}

	void CEvent::Release()
	{
		delete this;
	}
#pragma endregion

#pragma region Getters
	IEventList *CEvent::getEventList()
	{
		return m_pEventList;
	}

	IClass *CEvent::getParent()
	{
		return m_pParent;
	}

	String CEvent::getName()
	{
		return m_sName;
	}

	String CEvent::getSignature()
	{
		return m_sSignature;
	}

	String CEvent::getArguments()
	{
		return m_sArguments;
	}

	String CEvent::getValue()
	{
		return m_sValue;
	}

	bool CEvent::isChanged()
	{
		return !m_sValue.empty();
	}

	int CEvent::getHeaderFileCount()
	{
		return (int)m_aHeaderFiles.size();
	}

	String CEvent::getHeaderFile(const int index)
	{
		if (index >= 0 && index < (int)m_aHeaderFiles.size())
			return m_aHeaderFiles[index];
		return L"";
	}

	int CEvent::getForwardDeclarationCount()
	{
		return (int)m_aForwardDeclarations.size();
	}

	IEvent::ForwardDeclaration CEvent::getForwardDeclaration(const int index)
	{
		if (index >= 0 && index < (int)m_aForwardDeclarations.size())
			return m_aForwardDeclarations[index];
		return ForwardDeclaration{ L"", L"" };
	}
#pragma endregion

#pragma region Setters
	bool CEvent::setValue(const String &value)
	{
		if (value != m_sValue)
		{
			m_sValue = value;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Helpers
	void CEvent::Save(Variant &dest)
	{
		dest = m_sValue;
	}

	void CEvent::Load(const Variant &src)
	{
		m_sValue = (String)src;
	}

	void CEvent::Export(std::wofstream &f, const String &shift, const String &control, const String &form, const String &dialog_box)
	{
		String ns{ (m_pEventList && m_pEventList->getEntity()) ? m_pEventList->getEntity()->getNamespace() : L"" };
		if (!ns.empty())
			ns += L"::";
		if (!dialog_box.empty())
		{
			if (control.empty())
				f << shift << m_sName << L" = [](" << ReplaceAll(m_sSignature, L"{namespace}", ns) << L")->void { cast<I" << dialog_box << L"*>(sender)->"
				<< m_sValue << L"(" << m_sArguments << L"); };" << std::endl;
			else
			{
				if (cast<IControl*>(getParent()))
				{
					f << shift << control << L"->" << m_sName << L" = [](" << ReplaceAll(m_sSignature, L"{namespace}", ns) << L")->void { parent<I" << dialog_box << L"*, false>(sender)->"
						<< m_sValue << L"(" << m_sArguments << L"); };" << std::endl;
				}
				else
				{
					f << shift << control << L"->Tag = (void*)this;" << std::endl;
					f << shift << control << L"->" << m_sName << L" = [](" << ReplaceAll(m_sSignature, L"{namespace}", ns) << L")->void { ((I" << dialog_box << L"*)(void*)sender->Tag)->"
						<< m_sValue << L"(" << m_sArguments << L"); };" << std::endl;
				}
			}
		}
		else if (control.empty())
			f << shift << m_sName << L" = [](" << ReplaceAll(m_sSignature, L"{namespace}", ns) << L")->void { cast<I" << form << L"*>(sender)->"
				<< m_sValue << L"(" << m_sArguments << L"); };" << std::endl;
		else
			f << shift << control << L"->" << m_sName << L" = [](" << ReplaceAll(m_sSignature, L"{namespace}", ns) << L")->void { cast<I" << form << L"*>(sender->getForm())->"
				<< m_sValue << L"(" << m_sArguments << L"); };" << std::endl;
	}

	CEvent *CEvent::AddHeaderFile(const String &value)
	{
		m_aHeaderFiles.push_back(value);
		return this;
	}

	CEvent *CEvent::AddForwardDeclaration(const String &value, const String &header_file, const String &ns)
	{
		m_aForwardDeclarations.push_back(ForwardDeclaration{ value, header_file, ns });
		return this;
	}
#pragma endregion
}
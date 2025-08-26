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
	namespace standard
	{
		CPackageFormHotkeyList::CPackageFormHotkeyList(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/HotkeyList/FormHotkeyList.h");
		}

		String CPackageFormHotkeyList::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormHotkeyList::getClassName()
		{
			return CFormHotkeyList::ClassName;
		}

		String CPackageFormHotkeyList::getTitle()
		{
			return L"FormHotkeyList";
		}

		String CPackageFormHotkeyList::getDescription()
		{
			return L"HotkeyList";
		}

		String CPackageFormHotkeyList::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormHotkeyList::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormHotkeyList::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormHotkeyList::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormHotkeyList(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormHotkeyList::CreatePropertyList(IForm *form)
		{
			CFormHotkeyList *f{ cast<CFormHotkeyList*>(form) };
			if (f)
				return new CFormHotkeyListPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormHotkeyList::CreateEventList(IForm *form)
		{
			CFormHotkeyList *f{ cast<CFormHotkeyList*>(form) };
			if (f)
				return new CFormHotkeyListEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}
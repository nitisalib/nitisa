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
		CPackageFormHotkey::CPackageFormHotkey(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/Hotkey/FormHotkey.h");
		}

		String CPackageFormHotkey::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormHotkey::getClassName()
		{
			return CFormHotkey::ClassName;
		}

		String CPackageFormHotkey::getTitle()
		{
			return L"FormHotkey";
		}

		String CPackageFormHotkey::getDescription()
		{
			return L"Hotkey";
		}

		String CPackageFormHotkey::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormHotkey::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormHotkey::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormHotkey::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormHotkey(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormHotkey::CreatePropertyList(IForm *form)
		{
			CFormHotkey *f{ cast<CFormHotkey*>(form) };
			if (f)
				return new CFormHotkeyPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormHotkey::CreateEventList(IForm *form)
		{
			CFormHotkey *f{ cast<CFormHotkey*>(form) };
			if (f)
				return new CFormHotkeyEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}
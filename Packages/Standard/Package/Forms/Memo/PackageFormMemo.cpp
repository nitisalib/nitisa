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
		CPackageFormMemo::CPackageFormMemo(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/Memo/FormMemo.h");
		}

		String CPackageFormMemo::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormMemo::getClassName()
		{
			return CFormMemo::ClassName;
		}

		String CPackageFormMemo::getTitle()
		{
			return L"FormMemo";
		}

		String CPackageFormMemo::getDescription()
		{
			return L"Memo";
		}

		String CPackageFormMemo::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormMemo::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormMemo::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormMemo::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormMemo(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormMemo::CreatePropertyList(IForm *form)
		{
			CFormMemo *f{ cast<CFormMemo*>(form) };
			if (f)
				return new CFormMemoPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormMemo::CreateEventList(IForm *form)
		{
			CFormMemo *f{ cast<CFormMemo*>(form) };
			if (f)
				return new CFormMemoEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}
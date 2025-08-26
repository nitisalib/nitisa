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
		CPackageFormRect::CPackageFormRect(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/Rect/FormRect.h");
		}

		String CPackageFormRect::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormRect::getClassName()
		{
			return CFormRect::ClassName;
		}

		String CPackageFormRect::getTitle()
		{
			return L"FormRect";
		}

		String CPackageFormRect::getDescription()
		{
			return L"Rect";
		}

		String CPackageFormRect::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormRect::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormRect::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormRect::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormRect(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormRect::CreatePropertyList(IForm *form)
		{
			CFormRect *f{ cast<CFormRect*>(form) };
			if (f)
				return new CFormRectPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormRect::CreateEventList(IForm *form)
		{
			CFormRect *f{ cast<CFormRect*>(form) };
			if (f)
				return new CFormRectEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}
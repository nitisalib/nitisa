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
		CPackageFormBorderColor::CPackageFormBorderColor(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/BorderColor/FormBorderColor.h");
		}

		String CPackageFormBorderColor::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormBorderColor::getClassName()
		{
			return CFormBorderColor::ClassName;
		}

		String CPackageFormBorderColor::getTitle()
		{
			return L"FormBorderColor";
		}

		String CPackageFormBorderColor::getDescription()
		{
			return L"BorderColor";
		}

		String CPackageFormBorderColor::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormBorderColor::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormBorderColor::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormBorderColor::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormBorderColor(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormBorderColor::CreatePropertyList(IForm *form)
		{
			CFormBorderColor *f{ cast<CFormBorderColor*>(form) };
			if (f)
				return new CFormBorderColorPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormBorderColor::CreateEventList(IForm *form)
		{
			CFormBorderColor *f{ cast<CFormBorderColor*>(form) };
			if (f)
				return new CFormBorderColorEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}
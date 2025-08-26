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
		CPackageFormRectL::CPackageFormRectL(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/RectL/FormRectL.h");
		}

		String CPackageFormRectL::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormRectL::getClassName()
		{
			return CFormRectL::ClassName;
		}

		String CPackageFormRectL::getTitle()
		{
			return L"FormRectL";
		}

		String CPackageFormRectL::getDescription()
		{
			return L"RectL";
		}

		String CPackageFormRectL::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormRectL::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormRectL::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormRectL::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormRectL(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormRectL::CreatePropertyList(IForm *form)
		{
			CFormRectL *f{ cast<CFormRectL*>(form) };
			if (f)
				return new CFormRectLPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormRectL::CreateEventList(IForm *form)
		{
			CFormRectL *f{ cast<CFormRectL*>(form) };
			if (f)
				return new CFormRectLEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}
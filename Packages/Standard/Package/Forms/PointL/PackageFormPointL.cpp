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
		CPackageFormPointL::CPackageFormPointL(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/PointL/FormPointL.h");
		}

		String CPackageFormPointL::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormPointL::getClassName()
		{
			return CFormPointL::ClassName;
		}

		String CPackageFormPointL::getTitle()
		{
			return L"FormPointL";
		}

		String CPackageFormPointL::getDescription()
		{
			return L"PointL";
		}

		String CPackageFormPointL::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormPointL::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormPointL::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormPointL::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormPointL(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormPointL::CreatePropertyList(IForm *form)
		{
			CFormPointL *f{ cast<CFormPointL*>(form) };
			if (f)
				return new CFormPointLPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormPointL::CreateEventList(IForm *form)
		{
			CFormPointL *f{ cast<CFormPointL*>(form) };
			if (f)
				return new CFormPointLEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}
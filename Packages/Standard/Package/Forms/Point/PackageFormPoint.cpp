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
		CPackageFormPoint::CPackageFormPoint(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/Point/FormPoint.h");
		}

		String CPackageFormPoint::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormPoint::getClassName()
		{
			return CFormPoint::ClassName;
		}

		String CPackageFormPoint::getTitle()
		{
			return L"FormPoint";
		}

		String CPackageFormPoint::getDescription()
		{
			return L"Point";
		}

		String CPackageFormPoint::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormPoint::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormPoint::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormPoint::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormPoint(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormPoint::CreatePropertyList(IForm *form)
		{
			CFormPoint *f{ cast<CFormPoint*>(form) };
			if (f)
				return new CFormPointPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormPoint::CreateEventList(IForm *form)
		{
			CFormPoint *f{ cast<CFormPoint*>(form) };
			if (f)
				return new CFormPointEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}
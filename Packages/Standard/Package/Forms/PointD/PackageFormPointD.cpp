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
		CPackageFormPointD::CPackageFormPointD(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/PointD/FormPointD.h");
		}

		String CPackageFormPointD::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormPointD::getClassName()
		{
			return CFormPointD::ClassName;
		}

		String CPackageFormPointD::getTitle()
		{
			return L"FormPointD";
		}

		String CPackageFormPointD::getDescription()
		{
			return L"PointD";
		}

		String CPackageFormPointD::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormPointD::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormPointD::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormPointD::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormPointD(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormPointD::CreatePropertyList(IForm *form)
		{
			CFormPointD *f{ cast<CFormPointD*>(form) };
			if (f)
				return new CFormPointDPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormPointD::CreateEventList(IForm *form)
		{
			CFormPointD *f{ cast<CFormPointD*>(form) };
			if (f)
				return new CFormPointDEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}
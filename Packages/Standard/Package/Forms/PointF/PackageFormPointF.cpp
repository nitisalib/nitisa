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
		CPackageFormPointF::CPackageFormPointF(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/PointF/FormPointF.h");
		}

		String CPackageFormPointF::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormPointF::getClassName()
		{
			return CFormPointF::ClassName;
		}

		String CPackageFormPointF::getTitle()
		{
			return L"FormPointF";
		}

		String CPackageFormPointF::getDescription()
		{
			return L"PointF";
		}

		String CPackageFormPointF::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormPointF::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormPointF::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormPointF::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormPointF(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormPointF::CreatePropertyList(IForm *form)
		{
			CFormPointF *f{ cast<CFormPointF*>(form) };
			if (f)
				return new CFormPointFPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormPointF::CreateEventList(IForm *form)
		{
			CFormPointF *f{ cast<CFormPointF*>(form) };
			if (f)
				return new CFormPointFEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}
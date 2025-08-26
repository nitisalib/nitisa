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
		CPackageFormRectF::CPackageFormRectF(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/RectF/FormRectF.h");
		}

		String CPackageFormRectF::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormRectF::getClassName()
		{
			return CFormRectF::ClassName;
		}

		String CPackageFormRectF::getTitle()
		{
			return L"FormRectF";
		}

		String CPackageFormRectF::getDescription()
		{
			return L"RectF";
		}

		String CPackageFormRectF::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormRectF::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormRectF::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormRectF::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormRectF(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormRectF::CreatePropertyList(IForm *form)
		{
			CFormRectF *f{ cast<CFormRectF*>(form) };
			if (f)
				return new CFormRectFPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormRectF::CreateEventList(IForm *form)
		{
			CFormRectF *f{ cast<CFormRectF*>(form) };
			if (f)
				return new CFormRectFEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}
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
		CPackageFormTransform::CPackageFormTransform(IPackage *package) : CPackageForm(package, L"standard"),
			m_pForm{ nullptr }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/Transform/FormTransform.h");
		}

		String CPackageFormTransform::getCategory()
		{
			return L"Standard";
		}

		String CPackageFormTransform::getClassName()
		{
			return CFormTransform::ClassName;
		}

		String CPackageFormTransform::getTitle()
		{
			return L"FormTransform";
		}

		String CPackageFormTransform::getDescription()
		{
			return L"Transform";
		}

		String CPackageFormTransform::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormTransform::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormTransform::getInstance()
		{
			return m_pForm;
		}

		IForm *CPackageFormTransform::Create(IWindow *window, IRenderer *renderer)
		{
			IForm *result{ new CFormTransform(window, renderer) };
			if (!m_pForm)
				m_pForm = result;
			return result;
		}

		IPropertyList *CPackageFormTransform::CreatePropertyList(IForm *form)
		{
			CFormTransform *f{ cast<CFormTransform*>(form) };
			if (f)
				return new CFormTransformPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormTransform::CreateEventList(IForm *form)
		{
			CFormTransform *f{ cast<CFormTransform*>(form) };
			if (f)
				return new CFormTransformEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}
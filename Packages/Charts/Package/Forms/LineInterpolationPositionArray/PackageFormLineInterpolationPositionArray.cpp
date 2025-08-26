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
	namespace charts
	{
		CPackageFormLineInterpolationPositionArray::CPackageFormLineInterpolationPositionArray(IPackage *package) : CPackageForm(package, L"charts")
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Forms/LineInterpolationPositionArray/FormLineInterpolationPositionArray.h");
		}

		String CPackageFormLineInterpolationPositionArray::getCategory()
		{
			return L"Charts";
		}

		String CPackageFormLineInterpolationPositionArray::getClassName()
		{
			return CFormLineInterpolationPositionArray::ClassName;
		}

		String CPackageFormLineInterpolationPositionArray::getTitle()
		{
			return L"FormLineInterpolationPositionArray";
		}

		String CPackageFormLineInterpolationPositionArray::getDescription()
		{
			return L"LineInterpolationPositionArray";
		}

		String CPackageFormLineInterpolationPositionArray::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageFormLineInterpolationPositionArray::getIcon()
		{
			return nullptr;
		}

		IForm *CPackageFormLineInterpolationPositionArray::getInstance()
		{
			return CFormLineInterpolationPositionArray::getInstance();
		}

		IForm *CPackageFormLineInterpolationPositionArray::Create(IWindow *window, IRenderer *renderer)
		{
			return new CFormLineInterpolationPositionArray(window, renderer);
		}

		IPropertyList *CPackageFormLineInterpolationPositionArray::CreatePropertyList(IForm *form)
		{
			CFormLineInterpolationPositionArray *f{ cast<CFormLineInterpolationPositionArray*>(form) };
			if (f)
				return new CFormLineInterpolationPositionArrayPropertyList(getPackage(), form, this);
			return nullptr;
		}

		IEventList *CPackageFormLineInterpolationPositionArray::CreateEventList(IForm *form)
		{
			CFormLineInterpolationPositionArray *f{ cast<CFormLineInterpolationPositionArray*>(form) };
			if (f)
				return new CFormLineInterpolationPositionArrayEventList(getPackage(), form, this);
			return nullptr;
		}
	}
}
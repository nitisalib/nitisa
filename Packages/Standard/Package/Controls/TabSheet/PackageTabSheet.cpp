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
		CPackageTabSheet::CPackageTabSheet(IPackage *package) : CPackageControl(package, L"standard")
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Controls/PageControl/TabSheet.h");
		}

		IControl *CPackageTabSheet::Create(IPropertyList **properties, IEventList **events)
		{
			IControl *result{ new CTabSheet() };
			if (properties)
				*properties = new CTabSheetPropertyList(getPackage(), result, this);
			if (events)
				*events = new CTabSheetEventList(getPackage(), result, this);
			if (properties || events)
				getPackage()->QueryService()->NotifyOnCreateControl(result, this, *properties, *events);
			return result;
		}

		IPropertyList *CPackageTabSheet::CreatePropertyList(IControl *control)
		{
			if (isInstance(control))
				return new CTabSheetPropertyList(getPackage(), control, this);
			return nullptr;
		}

		IEventList *CPackageTabSheet::CreateEventList(IControl *control)
		{
			if (isInstance(control))
				return new CTabSheetEventList(getPackage(), control, this);
			return nullptr;
		}

		String CPackageTabSheet::getCategory()
		{
			return L"Standard";
		}

		String CPackageTabSheet::getClassName()
		{
			return L"TabSheet";
		}

		String CPackageTabSheet::getTitle()
		{
			return L"TabSheet";
		}

		String CPackageTabSheet::getDescription()
		{
			return L"TabSheet";
		}

		String CPackageTabSheet::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageTabSheet::getIcon()
		{
			return nullptr;
		}

		bool CPackageTabSheet::isVisible()
		{
			return false;
		}

		bool CPackageTabSheet::isDisplayIcon()
		{
			return false;
		}

		bool CPackageTabSheet::isInstance(IControl *control)
		{
			return cast<CTabSheet*>(control) != nullptr;
		}

		bool CPackageTabSheet::isTransformable()
		{
			return false;
		}
	}
}
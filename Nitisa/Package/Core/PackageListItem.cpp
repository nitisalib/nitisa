// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	CPackageListItem::CPackageListItem(IPackage *package, const String &ns) : CPackageEntity(package, ns)
	{

	}

	void CPackageListItem::Save(Variant &dest, IPropertyList *properties)
	{
		dest.Reset();
		dest[L"Package"] = getPackage()->getName();
		dest[L"ClassName"] = getClassName();
		properties->Save(dest);
	}

	void CPackageListItem::Load(const Variant &src, IPropertyList *properties)
	{
		properties->Load(src);
	}

	void CPackageListItem::Load(const String &src, IPropertyList *properties)
	{
		Variant dest;
		if (json_decode(src, dest))
			Load(dest, properties);
	}

	void CPackageListItem::Export(std::wofstream &f, const String &shift, const String &owner, IPropertyList *properties)
	{
		f << shift << L"{" << std::endl;
		f << shift << L"\tC" << getClassName() << L" *item{ new C" << getClassName() << L"() };" << std::endl;
		properties->Export(f, shift + L"\t", L"item");
		f << shift << L"\t" << owner << L"->AddItem(item);" << std::endl;
		f << shift << L"}" << std::endl;
	}
}
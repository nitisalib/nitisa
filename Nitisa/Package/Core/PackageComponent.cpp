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
	CPackageComponent::CPackageComponent(IPackage *package, const String &ns) : CPackageEntity(package, ns)
	{

	}

	void CPackageComponent::Save(Variant &dest, IPropertyList *properties, IEventList *events)
	{
		dest.Reset();
		dest[L"Package"] = getPackage()->getName();
		dest[L"ClassName"] = getClassName();
		properties->Save(dest);
		events->Save(dest);
	}

	void CPackageComponent::Load(const Variant &src, IPropertyList *properties, IEventList *events)
	{
		properties->Load(src);
		events->Load(src);
	}

	void CPackageComponent::Export(std::wofstream &f, const String &shift, const String &owner, IPropertyList *properties, IEventList *events, const String &form, const String &dialog_box)
	{
		properties->Export(f, shift, owner);
		events->Export(f, shift, owner, form, dialog_box);
	}

	void CPackageComponent::ExportExtra(std::wofstream &f, const String &shift, IComponent *component)
	{
		// Nothing
	}

	bool CPackageComponent::CreateListItem(IComponent *component, IListItem *parent, IListItem **item, IPackageComponentListener *listener)
	{
		return false;
	}
}
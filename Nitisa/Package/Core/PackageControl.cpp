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
	CPackageControl::CPackageControl(IPackage *package, const String &ns) :CPackageEntity(package, ns)
	{

	}

	bool CPackageControl::isDialogBox()
	{
		return false;
	}

	void CPackageControl::Save(Variant &dest, IPropertyList *properties, IEventList *events)
	{
		dest.Reset();
		dest[L"Package"] = getPackage()->getName();
		dest[L"ClassName"] = getClassName();
		properties->Save(dest);
		events->Save(dest);
	}

	void CPackageControl::Load(const Variant &src, IPropertyList *properties, IEventList *events)
	{
		properties->Load(src);
		events->Load(src);
	}

	void CPackageControl::Export(std::wofstream &f, const String &shift, const String &owner, IPropertyList *properties, IEventList *events, const String &form, const String &dialog_box)
	{
		properties->Export(f, shift, owner);
		events->Export(f, shift, owner, form, dialog_box);
	}

	void CPackageControl::ExportExtra(std::wofstream &f, const String &shift, IControl *control)
	{
		// Nothing
	}

	bool CPackageControl::CreateChild(IControl *parent, IControl **child, IPackageControlListener *listener)
	{
		if (parent && (child || listener))
		{
			IControlCreateChild *cc{ cast<IControlCreateChild*>(parent) };
			if (cc)
			{
				IControl *ctrl{ cc->CreateChild() };
				if (ctrl)
				{
					if (child)
						*child = cc->CreateChild();
					if (listener)
						listener->OnCreateChild(this, parent, ctrl);
					return true;
				}
			}
		}
		return false;
	}

	bool CPackageControl::CreateListItem(IComponent *component, IListItem *parent, IListItem **item, IPackageControlListener *listener)
	{
		return false;
	}
}
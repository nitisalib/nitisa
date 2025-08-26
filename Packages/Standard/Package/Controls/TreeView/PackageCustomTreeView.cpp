// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
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
		CPackageCustomTreeView::CPackageCustomTreeView(IPackage *package, const String &ns) : CPackageControl(package, ns)
		{
			AddHeaderFile(L"Standard/Controls/TreeView/CustomTreeView.h");
		}

		void CPackageCustomTreeView::SaveListItem(Variant &dest, IListItem *item)
		{
			IPackageListItem *package_item{ Application->Editor->getListItem(item) };
			Variant data;
			if (package_item)
			{
				data[L"Package"] = package_item->getPackage()->getName();
				data[L"ClassName"] = package_item->getClassName();
				IPropertyList *properties;
				IListItem *test{ package_item->Create(&properties) };
				properties->setParent(item, this);
				test->Release();
				properties->Save(data);
				properties->Release();
			}
			for (int i = 0; i < item->getItemCount(); i++)
				SaveListItem(data[L"Items"], item->getItem(i));
			dest.push_back(data);
		}

		void CPackageCustomTreeView::Save(Variant &dest, IPropertyList *properties, IEventList *events)
		{
			CPackageControl::Save(dest, properties, events);
			CCustomTreeView *control{ cast<CCustomTreeView*>(properties->getParent()) };
			if (Application->Editor && control && control->getRootItem()->getItemCount() > 0)
				for (int i = 0; i < control->getRootItem()->getItemCount(); i++)
					SaveListItem(dest[L"Items"], control->getRootItem()->getItem(i));
		}

		void CPackageCustomTreeView::LoadListItem(const Variant &src, IListItem *parent)
		{
			if (src.isSet(L"Package") && src.isSet(L"ClassName"))
			{
				IPackageListItem *package_item{ Application->Editor->getListItem((String)src.get(L"Package"), (String)src.get(L"ClassName")) };
				if (package_item)
				{
					IPropertyList *properties;
					IListItem *item{ package_item->Create(&properties) };
					properties->Load(src);
					properties->Release();
					if (parent->AddItem(item))
					{
						if (src.isSet(L"Items") && src.get(L"Items").getType() == Variant::VariantType::Array)
							for (auto pos : src.get(L"Items"))
								LoadListItem(pos.second, item);
					}
					else
						item->Release();
				}
			}
		}

		void CPackageCustomTreeView::Load(const Variant &src, IPropertyList *properties, IEventList *events)
		{
			CCustomTreeView *control{ cast<CCustomTreeView*>(properties->getParent()) };
			if (Application->Editor && control && src.isSet(L"Items") && src.get(L"Items").getType() == Variant::VariantType::Array)
				for (auto pos : src.get(L"Items"))
					LoadListItem(pos.second, control->getRootItem());
			CPackageControl::Load(src, properties, events);
		}

		void CPackageCustomTreeView::ExportListItem(std::wofstream &f, const String &shift, const String &parent, IListItem *item, const int level)
		{
			IPackageListItem *package_item{ Application->Editor->getListItem(item) };
			if (package_item)
			{
				IPropertyList *properties;
				IListItem *tmp{ package_item->Create(&properties) };
				properties->setParent(item, this);
				tmp->Release();
				String ns{ package_item->getNamespace() };
				if (!ns.empty())
					ns += L"::";
				f << shift << L"{" << std::endl;
				f << shift << L"\t" << ns << L"C" << item->ClassName << L" *item" << level << L"{ new " << ns << L"C" << item->ClassName << L"() };" << std::endl;
				properties->Export(f, shift + L"\t", L"item" + ToString(level));
				for (int i = 0; i < item->getItemCount(); i++)
					ExportListItem(f, shift + L"\t", L"item" + ToString(level), item->getItem(i), level + 1);
				f << shift << L"\t" << parent << L"->AddItem(item" << level << L");" << std::endl;
				f << shift << L"}" << std::endl;
				properties->Release();
			}
		}

		void CPackageCustomTreeView::Export(std::wofstream &f, const String &shift, const String &owner, IPropertyList *properties, IEventList *events, const String &form, const String &dialog_box)
		{
			CCustomTreeView *control{ cast<CCustomTreeView*>(properties->getParent()) };
			if (Application->Editor && control && control->getRootItem()->getItemCount() > 0)
				for (int i = 0; i < control->getRootItem()->getItemCount(); i++)
					ExportListItem(f, shift, owner + L"->getRootItem()", control->getRootItem()->getItem(i), 0);
			CPackageControl::Export(f, shift, owner, properties, events, form, dialog_box);
		}
	}
}
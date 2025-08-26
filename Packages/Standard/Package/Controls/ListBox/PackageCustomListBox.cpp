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
		CPackageCustomListBox::CPackageCustomListBox(IPackage *package, const String &ns) : CPackageControl(package, ns)
		{
			AddHeaderFile(L"Standard/Controls/ListBox/CustomListBox.h");
		}

		void CPackageCustomListBox::Save(Variant &dest, IPropertyList *properties, IEventList *events)
		{
			CPackageControl::Save(dest, properties, events);
			CCustomListBox *control{ cast<CCustomListBox*>(properties->getParent()) };
			if (Application->Editor && control)
				for (int i = 0; i < control->getItemCount(); i++)
				{
					IListItem *item{ control->getItem(i) };
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
					dest[L"Items"].push_back(data);
				}
		}

		void CPackageCustomListBox::Load(const Variant &src, IPropertyList *properties, IEventList *events)
		{
			CCustomListBox *control{ cast<CCustomListBox*>(properties->getParent()) };
			if (Application->Editor && control && src.isSet(L"Items") && src.get(L"Items").getType() == Variant::VariantType::Array)
			{
				control->DeleteItems();
				for (auto pos : src.get(L"Items"))
					if (pos.second.isSet(L"Package") && pos.second.isSet(L"ClassName"))
					{
						IPackageListItem *package_item{ Application->Editor->getListItem((String)pos.second.get(L"Package"), (String)pos.second.get(L"ClassName")) };
						if (package_item)
						{
							IPropertyList *properties;
							IListItem *item{ package_item->Create(&properties) };
							properties->Load(pos.second);
							properties->Release();
							if (!control->AddItem(item))
								item->Release();
						}
					}
			}
			CPackageControl::Load(src, properties, events);
		}

		void CPackageCustomListBox::Export(std::wofstream &f, const String &shift, const String &owner, IPropertyList *properties, IEventList *events, const String &form, const String &dialog_box)
		{
			CCustomListBox *control{ cast<CCustomListBox*>(properties->getParent()) };
			if (Application->Editor && control)
				for (int i = 0; i < control->getItemCount(); i++)
				{
					IListItem *item{ control->getItem(i) };
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
						f << shift << L"\t" << ns << L"C" << item->ClassName << L" *item{ new " << ns << L"C" << item->ClassName << L"() };" << std::endl;
						properties->Export(f, shift + L"\t", L"item");
						f << shift << L"\t" << owner << L"->AddItem(item);" << std::endl;
						f << shift << L"}" << std::endl;
						properties->Release();
					}
				}
			CPackageControl::Export(f, shift, owner, properties, events, form, dialog_box);
		}
	}
}
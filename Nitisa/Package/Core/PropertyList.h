// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Core/Variant.h"
#include "../Interfaces/IPropertyList.h"
#include <iostream>
#include <vector>

namespace nitisa
{
	class IClass;
	class IPackage;
	class IPackageEntity;
	class IProperty;

	class CPropertyList :public virtual IPropertyList
	{
	private:
		IPackage *m_pPackage;
		IClass *m_pParent;
		std::vector<IProperty*> m_aItems;
		IPackageEntity *m_pEntity;
	public:
		IPackage *getPackage() override;
		IClass *getParent() override;
		int getCount() override;
		IProperty *getProperty(const int index) override;
		IProperty *getProperty(const String &name) override;
		IPackageEntity *getEntity() override;

		void setParent(IClass *parent, IPackageEntity *entity) override;

		void Release() override;
		void Save(Variant &dest) override;
		void Load(const Variant &src) override;
		void Export(std::wofstream &f, const String &shift, const String &owner) override;

		CPropertyList(IPackage *package, IClass *parent, IPackageEntity *entity);
		virtual ~CPropertyList();

		void Delete(const int index); // Delete property by index
		void Delete(IProperty *item); // Delete specified property
		void Delete(const String &name); // Delete property by name
		void Clear(); // Delete all properties

		template<class Type> Type *Add(Type *item) // Add new property
		{
			if (item)
				m_aItems.push_back(item);
			return item;
		}
	};
}
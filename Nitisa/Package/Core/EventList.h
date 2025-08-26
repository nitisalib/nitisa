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
#include "../Interfaces/IEventList.h"
#include <iostream>
#include <vector>

namespace nitisa
{
	class IClass;
	class IEvent;
	class IPackage;
	class IPackageEntity;

	class CEventList :public virtual IEventList
	{
	private:
		IPackage *m_pPackage;
		IClass *m_pParent;
		std::vector<IEvent*> m_aItems;
		IPackageEntity *m_pEntity;
	public:
		IPackage *getPackage() override;
		IClass *getParent() override;
		int getCount() override;
		IEvent *getEvent(const int index) override;
		IEvent *getEvent(const String &name) override;
		IPackageEntity *getEntity() override;

		void Release() override;
		void Save(Variant &dest) override;
		void Load(const Variant &src) override;
		void Export(std::wofstream &f, const String &shift, const String &owner, const String &form, const String &dialog_box) override;

		CEventList(IPackage *package, IClass *parent, IPackageEntity *entity); // Create empty event list
		virtual ~CEventList();

		void Delete(const int index); // Delete event by index
		void Delete(IEvent *item); // Delete event
		void Delete(const String &name); // Delete event by name
		void Clear(); // Delete all events

		template<class Type> Type *Add(Type *item) // Add new property
		{
			if (item)
				m_aItems.push_back(item);
			return item;
		}
	};
}
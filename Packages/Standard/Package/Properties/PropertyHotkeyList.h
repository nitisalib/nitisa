// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Hotkey.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Variant.h"
#include "Nitisa/Package/Core/Property.h"
#include "../Interfaces/IPropertyHotkeyList.h"
#include <iostream>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	namespace standard
	{
		class CPropertyHotkeyList :public virtual IPropertyHotkeyList, public CProperty
		{
		public:
			using FGetCount = int(*)(IClass *parent);
			using FGetHotkey = Hotkey(*)(IClass *parent, const int index);
			using FAdd = bool(*)(IClass *parent, Hotkey value);
			using FDelete = bool(*)(IClass *parent, const int index);
			using FClear = bool(*)(IClass *parent);
		private:
			FGetCount m_fGetCount;
			FGetHotkey m_fGetHotkey;
			FAdd m_fAdd;
			FDelete m_fDelete;
			FClear m_fClear;
			bool m_bChanged;
		public:
			// IProperty getters
			String getPreview() override;
			String getPreview(const String &state) override;
			bool isChanged() override;

			// IProperty setters
			IProperty *setChanged(const bool value) override;

			// IProperty methods
			bool Copy(IProperty *dest) override;
			void Save(Variant &dest) override;
			void Load(const Variant &src) override;
			void Export(std::wofstream &f, const String &shift, const String &control) override;

			// IPropertyHotkeyList getters
			int getCount() override;
			Hotkey getHotkey(const int index) override;

			// IPropertyHotkeyList methods
			int Add(Hotkey value) override;
			bool Delete(const int index) override;
			bool Clear() override;

			CPropertyHotkeyList(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetCount get_count, FGetHotkey get_hotkey, FAdd add, FDelete del, FClear clear); // See parent class constructor for more information
		};
	}
}
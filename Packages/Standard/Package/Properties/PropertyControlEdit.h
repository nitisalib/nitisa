// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Variant.h"
#include "Nitisa/Package/Core/Property.h"
#include "../Interfaces/IPropertyControlEdit.h"
#include <iostream>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	namespace standard
	{
		class IEdit;

		class CPropertyControlEdit :public virtual IPropertyControlEdit, public CProperty
		{
		public:
			using FGetter = IEdit * (*)(IClass *parent);
			using FSetter = bool(*)(IClass *parent, IEdit *value);
		private:
			FGetter m_fGetter;
			FSetter m_fSetter;
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

			// IPropertyControlEdit getters
			IEdit *getValue() override;

			// IPropertyControlEdit setters
			bool setValue(IEdit *value) override;

			CPropertyControlEdit(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetter getter, FSetter setter); // See parent class constructor for more information
		};
	}
}
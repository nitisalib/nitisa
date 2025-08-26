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
#include "Nitisa/Package/Core/ExportPrefixType.h"
#include "Nitisa/Package/Core/PropertyState.h"
#include "../Interfaces/IPropertyComponentImageListState.h"
#include <iostream>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	namespace standard
	{
		class IImageList;

		class CPropertyComponentImageListState :public virtual IPropertyComponentImageListState, public CPropertyState
		{
		public:
			using FGetter = IImageList * (*)(IClass *parent, const String &state);
			using FSetter = bool(*)(IClass *parent, const String &state, IImageList *value);
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

			// IPropertyComponentImageListState getters
			IImageList *getValue(const String &state) override;

			// IPropertyComponentImageListState setters
			bool setValue(const String &state, IImageList *value) override;

			CPropertyComponentImageListState(
				IPropertyList *list,
				IClass *parent,
				const String &name,
				const StringArray &states,
				const ExportPrefixType state_prefix_type,
				const String &state_prefix,
				FSkip skip,
				FGetter getter,
				FSetter setter); // See parent class constructor for more information
		};
	}
}
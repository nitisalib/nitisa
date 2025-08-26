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
#include "../Interfaces/IPropertyControlMaterial.h"
#include <iostream>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	namespace opengl
	{
		class IMaterialControl;

		class CPropertyControlMaterial :public virtual IPropertyControlMaterial, public CProperty
		{
		public:
			using FGetter = IMaterialControl * (*)(IClass *parent);
			using FSetter = bool(*)(IClass *parent, IMaterialControl *value);
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

			// IPropertyControlMaterial getters
			IMaterialControl *getValue() override;

			// IPropertyControlMaterial setters
			bool setValue(IMaterialControl *value) override;

			CPropertyControlMaterial(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetter getter, FSetter setter); // See parent class constructor for more information
		};
	}
}
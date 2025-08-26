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
#include "../../Image/Image.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyImage.h"
#include <iostream>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyImage :public virtual IPropertyImage, public CProperty
	{
	public:
		using FGetter = Image*(*)(IClass *parent);
		using FUpdate = void(*)(IClass *parent);
	private:
		Image m_tOld;
		FGetter m_fGetter;
		FUpdate m_fUpdate;
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

		// IPropertyImage getters
		Image *getValue() override;

		// IPropertyImage methods
		void Update() override;

		CPropertyImage(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetter getter, FUpdate update); // See parent class constructor for more information
	};
}
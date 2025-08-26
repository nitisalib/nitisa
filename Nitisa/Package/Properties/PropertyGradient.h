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
#include "../../Image/Gradient.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyGradient.h"
#include <iostream>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyGradient :public virtual IPropertyGradient, public CProperty
	{
	public:
		using FGetter = Gradient*(*)(IClass *parent);
	private:
		Gradient m_tOld;
		FGetter m_fGetter;
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

		// IPropertyGradient getters
		Gradient *getValue() override;

		CPropertyGradient(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetter getter); // See parent class constructor for more information
	};
}
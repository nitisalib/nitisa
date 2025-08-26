// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Font.h"
#include "../../Core/Strings.h"
#include "../../Core/Variant.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyFont.h"
#include <iostream>

namespace nitisa
{
	class IClass;
	class IFont;
	class IProperty;
	class IPropertyList;

	class CPropertyFont :public virtual IPropertyFont, public CProperty
	{
	public:
		using FGetter = IFont*(*)(IClass *parent);
		using FSetter = bool(*)(IClass *parent, IFont *value);
	private:
		CFont m_tOld;
		CFont m_tValue;
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

		// IPropertyFont getters
		IFont *getValue() override;

		// IPropertyFont setters
		bool setValue(IFont *value) override;

		CPropertyFont(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter); // See parent class constructor for more information
	};
}
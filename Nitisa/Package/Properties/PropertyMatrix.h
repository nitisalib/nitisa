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
#include "../../Math/Mat4f.h"
#include "../Core/PropertyState.h"
#include "../Interfaces/IPropertyMatrix.h"
#include <iostream>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	class CPropertyMatrix :public virtual IPropertyMatrix, public CProperty
	{
	public:
		using FGetter = Mat4f(*)(IClass *parent);
		using FSetter = bool(*)(IClass *parent, Mat4f value);
	private:
		Mat4f m_tOld;
		Mat4f m_tValue;
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

		// IPropertyMatrix getters
		Mat4f getValue() override;

		// IPropertyMatrix setters
		bool setValue(const Mat4f value) override;

		CPropertyMatrix(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter); // See parent class constructor for more information
	};
}
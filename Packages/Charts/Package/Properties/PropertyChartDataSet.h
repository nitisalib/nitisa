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
#include <iostream>

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	namespace charts
	{
		class IChartData;

		class CPropertyChartDataSet :public virtual IPropertyChartDataSet, public CProperty
		{
		public:
			using FGetter = IChartDataSet * (*)(IClass *parent);
			using FSetter = bool(*)(IClass *parent, IChartDataSet *value);
			using FUpdate = void(*)(IClass *parent);
		private:
			FGetter m_fGetter;
			FSetter m_fSetter;
			FUpdate m_fUpdate;
			bool m_bChanged;

			String DataToString(IChartData *data);
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

			// IPropertyChartDataSet getters
			IChartDataSet *getValue() override;

			// IPropertyChartDataSet setters
			bool setValue(IChartDataSet *value) override;

			// IPropertyChartDataSet methods
			void Update() override;

			CPropertyChartDataSet(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetter getter, FSetter setter, FUpdate update); // See parent class constructor for more information
		};
	}
}
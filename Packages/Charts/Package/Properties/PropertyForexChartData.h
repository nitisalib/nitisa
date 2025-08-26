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
#include "../../Controls/IForexChart.h"
#include "../Interfaces/IPropertyForexChartData.h"
#include <iostream>
#include <vector>

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	namespace charts
	{
		class CPropertyForexChartData :public virtual IPropertyForexChartData, public CProperty
		{
		public:
			using FGetter = IForexChart::IForexChartData * (*)(IClass *parent);
			using FSetter = bool(*)(IClass *parent, IForexChart::IForexChartData *value);
			using FUpdate = void(*)(IClass *parent);
		private:
			FGetter m_fGetter;
			FSetter m_fSetter;
			FUpdate m_fUpdate;
			bool m_bChanged;

			String DataToString(IForexChart::IForexChartData *data, const String &shift);
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

			// IPropertyForexChartData getters
			IForexChart::IForexChartData *getValue() override;

			// IPropertyForexChartData setters
			bool setValue(IForexChart::IForexChartData *value) override;

			// IPropertyForexChartData methods
			void Update() override;

			CPropertyForexChartData(IPropertyList *list, IClass *parent, const String &name, FSkip skip, FGetter getter, FSetter setter, FUpdate update); // See parent class constructor for more information
		};
	}
}
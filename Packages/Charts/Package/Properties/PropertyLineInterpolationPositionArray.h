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
#include "../../Core/Enums.h"
#include "../Interfaces/IPropertyLineInterpolationPositionArray.h"
#include <iostream>
#include <vector>

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	namespace charts
	{
		class CPropertyLineInterpolationPositionArray :public virtual IPropertyLineInterpolationPositionArray, public CProperty
		{
		public:
			using FGetter = std::vector<LineInterpolationPosition>(*)(IClass *parent);
			using FSetter = bool(*)(IClass *parent, std::vector<LineInterpolationPosition> value);
		private:
			std::vector<LineInterpolationPosition> m_tOld;
			std::vector<LineInterpolationPosition> m_tValue;
			FGetter m_fGetter;
			FSetter m_fSetter;
			bool m_bChanged;
			int m_iMinCount;
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

			// IPropertyLineInterpolationPositionArray getters
			std::vector<LineInterpolationPosition> getValue() override;
			int getMinCount() override;

			// IPropertyLineInterpolationPositionArray setters
			bool setValue(const std::vector<LineInterpolationPosition> value) override;
			IPropertyLineInterpolationPositionArray *setMinCount(const int value) override;

			CPropertyLineInterpolationPositionArray(IPropertyList *list, IClass *parent, const String &name, const bool read_only, FSkip skip, FGetter getter, FSetter setter); // See parent class constructor for more information
		};
	}
}
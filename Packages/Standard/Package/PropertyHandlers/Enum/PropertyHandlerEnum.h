// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h"
#include "Nitisa/Core/Strings.h"
#include "../../Core/PropertyHandlerDropDown.h"

namespace nitisa
{
	class IPackage;
	class IProperty;
	class IPropertyEnum;
	class IPropertyEnumState;

	namespace standard
	{
		class CPropertyHandlerEnum :public CPropertyHandlerDropDown
		{
		private:
			using CBuiltInDropDown::isEditable;

			IProperty *m_pProperty;
			String m_sState;
			String m_sPrefix;
			StringArray m_sValues;

			bool RemovePrefixes(IPropertyEnum *p);
			bool RemovePrefixes(IPropertyEnumState *p);
		protected:
			void NotifyOnSelect(const int index) override;
		public:
			CPropertyHandlerEnum(IPackage *package);

			bool isEditable(IProperty *property) override;
			IProperty *getProperty() override;
			String getPropertyState() override;

			bool setProperty(IProperty *value) override;
			bool setPropertyState(const String &value) override;
		};
	}
}
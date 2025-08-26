// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Standard/Package/Core/PropertyHandlerDropDown.h"

namespace nitisa
{
	class IPackage;
	class IProperty;

	namespace opengl
	{
		class CPropertyHandlerControlMaterial :public standard::CPropertyHandlerDropDown
		{
		private:
			IProperty *m_pProperty;
			String m_sState;
		protected:
			void NotifyOnSelect(const int index) override;
		public:
			CPropertyHandlerControlMaterial(IPackage *package);

			bool isEditable(IProperty *property) override;
			IProperty *getProperty() override;
			String getPropertyState() override;

			bool setProperty(IProperty *value) override;
			bool setPropertyState(const String &value) override;
		};
	}
}
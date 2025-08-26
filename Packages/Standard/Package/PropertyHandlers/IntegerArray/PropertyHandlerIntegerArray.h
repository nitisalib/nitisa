// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Math/IntegerArray.h"
#include "../../Core/PropertyHandlerModal.h"

namespace nitisa
{
	class IPackage;
	class IProperty;

	namespace standard
	{
		class IFormIntegerArray;

		class CDialogBoxIntegerArray;

		class CPropertyHandlerIntegerArray :public standard::CPropertyHandlerModal
		{
		private:
			IProperty *m_pProperty;
			String m_sState;
			bool m_bDialogBoxAdjusted;

			IFormIntegerArray *getForm();
			CDialogBoxIntegerArray *getDialogBox();
			void setDialogValue(const IntegerArray &value, const int min_count, const bool has_min, const bool has_max, const int min, const int max);
		protected:
			void NotifyOnActivateModal() override;
		public:
			String getPropertyState() override;
			IProperty *getProperty() override;
			bool isEditable(IProperty *property) override;

			bool setProperty(IProperty *value) override;
			bool setPropertyState(const String &value) override;

			CPropertyHandlerIntegerArray(IPackage *package);
		};
	}
}
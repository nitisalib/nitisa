// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Standard/Package/Core/PropertyHandlerModal.h"
#include "../../../Core/Enums.h"
#include <vector>

namespace nitisa
{
	class IPackage;
	class IProperty;

	namespace charts
	{
		class IFormLineInterpolationPositionArray;

		class CDialogBoxLineInterpolationPositionArray;

		class CPropertyHandlerLineInterpolationPositionArray :public standard::CPropertyHandlerModal
		{
		private:
			IProperty *m_pProperty;
			bool m_bDialogBoxAdjusted;

			IFormLineInterpolationPositionArray *getForm();
			CDialogBoxLineInterpolationPositionArray *getDialogBox();
			void setDialogValue(const std::vector<LineInterpolationPosition> &value, const int min_count);
		protected:
			void NotifyOnActivateModal() override;
		public:
			String getPropertyState() override;
			IProperty *getProperty() override;
			bool isEditable(IProperty *property) override;

			bool setProperty(IProperty *value) override;
			bool setPropertyState(const String &value) override;

			CPropertyHandlerLineInterpolationPositionArray(IPackage *package);
		};
	}
}
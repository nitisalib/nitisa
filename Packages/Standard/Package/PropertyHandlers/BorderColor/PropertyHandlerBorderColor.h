// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BorderColor.h"
#include "../../Core/PropertyHandlerModal.h"

namespace nitisa
{
	class IPackage;
	class IProperty;

	namespace standard
	{
		class IFormBorderColor;

		class CDialogBoxBorderColor;

		class CPropertyHandlerBorderColor :public CPropertyHandlerModal
		{
		private:
			IProperty *m_pProperty;
			String m_sState;
			bool m_bDialogBoxAdjusted;

			IFormBorderColor *getForm();
			CDialogBoxBorderColor *getDialogBox();
			void setDialogData(const BorderColor &value);
		protected:
			void NotifyOnActivateModal() override;
		public:
			String getPropertyState() override;
			IProperty *getProperty() override;
			bool isEditable(IProperty *property) override;

			bool setProperty(IProperty *value) override;
			bool setPropertyState(const String &value) override;

			CPropertyHandlerBorderColor(IPackage *package);
		};
	}
}
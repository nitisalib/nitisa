// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Math/Mat4f.h"
#include "../../Core/PropertyHandlerModal.h"

namespace nitisa
{
	class IPackage;
	class IProperty;

	namespace standard
	{
		class IFormMatrix;

		class CDialogBoxMatrix;

		class CPropertyHandlerMatrix :public CPropertyHandlerModal
		{
		private:
			IProperty *m_pProperty;
			String m_sState;
			bool m_bDialogBoxAdjusted;

			IFormMatrix *getForm();
			CDialogBoxMatrix *getDialogBox();
			void setDialogMatrix(const Mat4f &value);
		protected:
			void NotifyOnActivateModal() override;
		public:
			String getPropertyState() override;
			IProperty *getProperty() override;
			bool isEditable(IProperty *property) override;

			bool setProperty(IProperty *value) override;
			bool setPropertyState(const String &value) override;

			CPropertyHandlerMatrix(IPackage *package);
		};
	}
}
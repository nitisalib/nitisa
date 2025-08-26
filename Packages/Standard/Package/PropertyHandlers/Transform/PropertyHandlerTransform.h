// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Math/Transform.h"
#include "../../Core/PropertyHandlerModal.h"

namespace nitisa
{
	class IPackage;
	class IProperty;

	namespace standard
	{
		class IFormTransform;

		class CDialogBoxTransform;

		class CPropertyHandlerTransform :public CPropertyHandlerModal
		{
		private:
			IProperty *m_pProperty;
			String m_sState;
			bool m_bDialogBoxAdjusted;

			IFormTransform *getForm();
			CDialogBoxTransform *getDialogBox();
			void setDialogData(const Transform &value,
				const bool allowed_tx, const bool allowed_ty, const bool allowed_tz,
				const bool allowed_sx, const bool allowed_sy, const bool allowed_sz,
				const bool allowed_rx, const bool allowed_ry, const bool allowed_rz,
				const bool allowed_ro, const bool allowed_to,
				const bool has_min_tx, const bool has_min_ty, const bool has_min_tz,
				const bool has_min_sx, const bool has_min_sy, const bool has_min_sz,
				const bool has_min_rx, const bool has_min_ry, const bool has_min_rz,
				const bool has_max_tx, const bool has_max_ty, const bool has_max_tz,
				const bool has_max_sx, const bool has_max_sy, const bool has_max_sz,
				const bool has_max_rx, const bool has_max_ry, const bool has_max_rz,
				const float min_tx, const float min_ty, const float min_tz,
				const float min_sx, const float min_sy, const float min_sz,
				const float min_rx, const float min_ry, const float min_rz,
				const float max_tx, const float max_ty, const float max_tz,
				const float max_sx, const float max_sy, const float max_sz,
				const float max_rx, const float max_ry, const float max_rz
			);
		protected:
			void NotifyOnActivateModal() override;
		public:
			String getPropertyState() override;
			IProperty *getProperty() override;
			bool isEditable(IProperty *property) override;

			bool setProperty(IProperty *value) override;
			bool setPropertyState(const String &value) override;

			CPropertyHandlerTransform(IPackage *package);
		};
	}
}
// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Component.h"
#include "Nitisa/Image/Color.h"
#include "../ISysColorDialog.h"

namespace nitisa
{
	class IForm;

	namespace standard
	{
		// Alpha channel remains unchanged
		class CSysColorDialog :public virtual ISysColorDialog, public CComponent
		{
		private:
			bool m_bAnyColor;
			bool m_bFullOpen;
			bool m_bPreventFullOpen;
			bool m_bOnlySolidColors;
			Color m_sColor;
		public:
			bool isAnyColor() override;
			bool isFullOpen() override;
			bool isPreventFullOpen() override;
			bool isOnlySolidColors() override;
			Color getColor() override;

			bool setAnyColor(const bool value) override;
			bool setFullOpen(const bool value) override;
			bool setPreventFullOpen(const bool value) override;
			bool setOnlySolidColors(const bool value) override;
			bool setColor(const Color &value) override;

			bool Execute() override;

			CSysColorDialog();
			CSysColorDialog(IForm *parent);
		};
	}
}
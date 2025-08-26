// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Component.h"
#include "Nitisa/Core/Font.h"
#include "../ISysFontDialog.h"

namespace nitisa
{
	class IFont;
	class IForm;

	namespace standard
	{
		class CSysFontDialog :public virtual ISysFontDialog, public CComponent
		{
		private:
			CFont m_cFont;
		public:
			IFont *getFont() override;

			bool setFont(IFont *value) override;

			bool Execute() override;

			CSysFontDialog();
			CSysFontDialog(IForm *parent);
		};
	}
}
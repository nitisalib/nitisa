// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Component.h"
#include "Nitisa/Core/Strings.h"
#include "../IAdminRights.h"

namespace nitisa
{
	class IForm;

	namespace standard
	{
		class CAdminRights :public virtual IAdminRights, public CComponent
		{
		private:
			bool m_bHasAdminRights;
		public:
			bool hasAdminRights() override;

			bool Request(const String &params = L"") override;

			CAdminRights();
			CAdminRights(IForm *parent);
		};
	}
}
// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IHintService.h"

namespace nitisa
{
	class IForm;

	class CHint;

	class CHintService :public virtual IHintService
	{
	private:
		CHint *m_pHint;
	public:
		void setForm(IForm *value) override;

		void Release() override;

		CHintService(CHint *hint);
		virtual ~CHintService() = default;
	};
}
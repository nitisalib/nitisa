// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Platform/Core/Application.h"

namespace nitisa
{
	namespace fb
	{
		class CApplication :public nitisa::CApplication
		{
		public:
			CApplication();
			~CApplication() override;

			void setEditor(IEditor *editor);
		};
	}
}
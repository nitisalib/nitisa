// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/List.h"
#include "TokenEx.h"

namespace nitisa
{
	namespace script
	{
		struct Token;

		namespace cppdoc
		{
			using List = ntl::TList<TokenEx>;
			using ntl::Append;
			using ntl::Copy;
			using ntl::Count;
			using ntl::Delete;
			using ntl::Free;
			using ntl::Head;
			using ntl::Tail;
		}
	}
}
// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include <exception>

namespace nitisa
{
	class DbExceptionRevertNotImplemented :public std::exception
	{
	public:
		const char *what() const noexcept override
		{
			return "The Revert() methods of the migration is not implemented";
		}

		DbExceptionRevertNotImplemented() :
			std::exception()
		{

		}
	};
}
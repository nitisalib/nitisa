// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include <exception>

namespace nitisa
{
	class DbExceptionRelationNotFound :public std::exception
	{
	private:
		AnsiString m_sMessage;
	public:
		const char *what() const noexcept override
		{
			return m_sMessage.c_str();
		}

		DbExceptionRelationNotFound(const String &model, const String &relation) :
			std::exception(),
			m_sMessage{ StringToAnsi(L"Model '" + model + L"' has no relation '" + relation + L"'") }
		{

		}
	};
}
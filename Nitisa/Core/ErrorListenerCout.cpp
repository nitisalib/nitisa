// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	void CErrorListenerCout::NotifyOnError(const AnsiString &function, const int line, const ErrorInfo &info, const StringKeyValueArray &args)
	{
		std::wcout << L"ERROR[" << info.Code << "] at line " << line << L":" << std::endl;
		std::wcout << L"\tlocation: " << AnsiToString(function) << std::endl;
		std::wcout << L"\tmessage : " << Application->Translate->t(L"errors", info.Message, args) << std::endl;
	}
}
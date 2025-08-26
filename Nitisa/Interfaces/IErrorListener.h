// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Consts.h"
#include "../Core/ErrorInfo.h"
#include "../Core/Strings.h"

namespace nitisa
{
	class IErrorListener
	{
	protected:
		IErrorListener() = default;
		~IErrorListener() = default;
		IErrorListener(const IErrorListener &other) = delete;
		IErrorListener(IErrorListener &&other) = delete;
		IErrorListener &operator=(const IErrorListener &other) = delete;
		IErrorListener &operator=(IErrorListener &&other) = delete;
	public:
		virtual void NotifyOnError(const AnsiString &function, const int line, const ErrorInfo &info, const StringKeyValueArray &args = EmptyStringKeyValueArray) = 0; // Called when error is detected
	};
}
// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
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
	class IWarningListener
	{
	protected:
		IWarningListener() = default;
		~IWarningListener() = default;
		IWarningListener(const IWarningListener &other) = delete;
		IWarningListener(IWarningListener &&other) = delete;
		IWarningListener &operator=(const IWarningListener &other) = delete;
		IWarningListener &operator=(IWarningListener &&other) = delete;
	public:
		virtual void NotifyOnWarning(const AnsiString &function, const int line, const ErrorInfo &info, const StringKeyValueArray &args = EmptyStringKeyValueArray) = 0; // Called when warning is detected
	};
}
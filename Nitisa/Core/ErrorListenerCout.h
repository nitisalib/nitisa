// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IErrorListener.h"
#include "Consts.h"
#include "ErrorInfo.h"
#include "Strings.h"

namespace nitisa
{
	class CErrorListenerCout :public virtual IErrorListener
	{
	public:
		void NotifyOnError(const AnsiString &function, const int line, const ErrorInfo &info, const StringKeyValueArray &args = EmptyStringKeyValueArray) override;
	};
}
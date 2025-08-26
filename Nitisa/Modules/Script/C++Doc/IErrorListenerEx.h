// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Strings.h"
#include "../../../Interfaces/IErrorListener.h"

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			class IErrorListenerEx :public virtual IErrorListener
			{
			protected:
				IErrorListenerEx() = default;
				~IErrorListenerEx() = default;
				IErrorListenerEx(const IErrorListenerEx &other) = delete;
				IErrorListenerEx(IErrorListenerEx &&other) = delete;
				IErrorListenerEx &operator=(const IErrorListenerEx &other) = delete;
				IErrorListenerEx &operator=(IErrorListenerEx &&other) = delete;
			public:
				String Dump; // Dump of tokens near the one specified in error
				String Before; // Put this before error token
				String After; // Put this after error token
				size_t BeforeCount; // How much token before error one to add into dump
				size_t AfterCount; // How much tokens after error one to add into dump
			};
		}
	}
}
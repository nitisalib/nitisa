// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Interfaces/IReleasable.h"
#include "../Core/Token.h"

namespace nitisa
{
	namespace script
	{
		class IParser :public virtual IReleasable
		{
		protected:
			IParser() = default;
			~IParser() = default;
			IParser(const IParser &other) = delete;
			IParser(IParser &&other) = delete;
			IParser &operator=(const IParser &other) = delete;
			IParser &operator=(IParser &&other) = delete;
		public:
			virtual bool Parse(size_t &index, Token &token) = 0; // Parse token at specified index. Update "index" and store token information in "token"
		};
	}
}
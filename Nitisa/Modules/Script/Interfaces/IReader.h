// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Strings.h"
#include "../../../Interfaces/IReleasable.h"

namespace nitisa
{
	namespace script
	{
		class IReader :public virtual IReleasable
		{
		protected:
			IReader() = default;
			~IReader() = default;
			IReader(const IReader &other) = delete;
			IReader(IReader &&other) = delete;
			IReader &operator=(const IReader &other) = delete;
			IReader &operator=(IReader &&other) = delete;
		protected:
			size_t m_iMin;
			size_t m_iMax;
		public:
			size_t const &Min{ m_iMin }; // Source minimum boundary
			size_t const &Max{ m_iMax }; // Source maximum boundary

			virtual void setSource(const String &value) = 0; // Set new source
			virtual void setSource(const String &value, const size_t &min, const size_t &max) = 0; // Set new source with bounds

			virtual wchar_t Read(const size_t index) = 0; // Read character from source at specified index. Return 0 character if index is out of bounds
			virtual String Read(const size_t index, const size_t length) = 0; // Read substring from source
		};
	}
}
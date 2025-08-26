// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Releasable.h"
#include "../../../Core/Strings.h"
#include "../Interfaces/IReader.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	namespace script
	{
		class CReaderSensitive :public virtual IReader, public CReleasable
		{
		private:
			String m_sSource;
		public:
			// IReader setters
			void setSource(const String &value) override;
			void setSource(const String &value, const size_t &min, const size_t &max) override;

			// IReader methods
			wchar_t Read(const size_t index) override;
			String Read(const size_t index, const size_t length) override;

			CReaderSensitive();
			CReaderSensitive(const String &source);
			CReaderSensitive(const String &source, const size_t min, const size_t max);
		};
	}
}
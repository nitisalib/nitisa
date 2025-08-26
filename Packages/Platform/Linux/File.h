// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#if defined(__linux__) && !defined(__ANDROID__)
#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IFile.h"

#ifdef linux
#undef linux
#endif

namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
			class CFile :public virtual IFile
			{
			private:
				PlatformHandle m_hHandle;
			public:
				long long getSize() override;
				long long getPointer() override;

				bool setPointer(const long long value, const SeekFrom seek_from) override;

				bool Read(const unsigned int size, unsigned char *buffer, unsigned long &read) override;
				bool Write(const unsigned int size, unsigned char *buffer, unsigned long &written) override;

				void Release() override;

				CFile(PlatformHandle handle, const String &filename);
				virtual ~CFile() = default;
			};
		}
	}
}
#endif
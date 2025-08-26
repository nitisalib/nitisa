// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef _WIN32
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IFile.h"

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
			// This class uses WinAPI file access functions to work with file system
			class CFile :public virtual IFile
			{
			private:
				void *m_pHandle;
			public:
				long long getSize() override;
				long long getPointer() override;

				bool setPointer(const long long value, const SeekFrom seek_from) override;

				bool Read(const unsigned int size, unsigned char *buffer, unsigned long &read) override;
				bool Write(const unsigned int size, unsigned char *buffer, unsigned long &written) override;

				void Release() override;

				CFile(void *handle, const String &filename);
				virtual ~CFile() = default;
			};
		}
	}
}
#endif
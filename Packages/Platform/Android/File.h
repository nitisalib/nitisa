// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IFile.h"
#include <stdio.h>

struct AAsset;

namespace nitisa
{
	namespace platform
	{
		namespace android
		{
			class CFile :public virtual IFile
			{
			private:
				FILE *m_pFile;
				AAsset *m_pAsset;
			public:
				long long getSize() override;
				long long getPointer() override;

				bool setPointer(const long long value, const SeekFrom seek_from) override;

				bool Read(const unsigned int size, unsigned char *buffer, unsigned long &read) override;
				bool Write(const unsigned int size, unsigned char *buffer, unsigned long &written) override;

				void Release() override;

				CFile(FILE *file, const String &filename);
				CFile(AAsset *asset, const String &filename);
				virtual ~CFile() = default;
			};
		}
	}
}
#endif
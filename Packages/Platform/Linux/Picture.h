// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#if defined(__linux__) && !defined(__ANDROID__)
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/Image.h"
#include "Nitisa/Interfaces/IPicture.h"
#include <vector>

#ifdef linux
#undef linux
#endif

namespace nitisa
{
	class ITexture;

	namespace platform
	{
		namespace linux
		{
			class CApplication;

			class CPicture :public virtual IPicture
			{
			private:
				CApplication * m_pApplication;
				std::vector<Format> m_aFormats;
				StringArray m_aExtensions;

				void LoadJpeg(unsigned char *data, const int size, Image &result);
				bool LoadJpeg(unsigned char *data, const int size, ITexture *dest);
				void LoadPng(const void *data, const int size, Image &result);
				bool LoadPng(const void *data, const int size, ITexture *dest);
				bool SaveJpeg(const String &filename, const Image &bmp, const int quality);
				bool SavePng(const String &filename, const Image &bmp);
			public:
				int getSupportedFormatCount() override;
				Format getSupportedFormat(const int index) override;

				Image Load(const String &filename) override;
				bool Load(const String &filename, ITexture *dest) override;
				bool Save(const String &filename, const Image &bmp, const void *options = nullptr) override;
				bool Save(const String &filename, ITexture *texture, const void *options = nullptr) override;

				CPicture(CApplication *application);
			};
		}
	}
}
#endif
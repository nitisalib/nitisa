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
#include "Nitisa/Image/Image.h"
#include "Nitisa/Interfaces/IPicture.h"
#include <vector>

namespace nitisa
{
	class ITexture;

	namespace platform
	{
		namespace windows
		{
			class CPicture :public virtual IPicture
			{
			private:
				std::vector<Format> m_aFormats;
			public:
				int getSupportedFormatCount() override;
				Format getSupportedFormat(const int index) override;

				Image Load(const String &filename) override;
				bool Load(const String &filename, ITexture *dest) override;
				bool Save(const String &filename, const Image &bmp, const void *options = nullptr) override;
				bool Save(const String &filename, ITexture *texture, const void *options = nullptr) override;

				CPicture();
				~CPicture();
			};
		}
	}
}
#endif
// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "../Image/Image.h"

namespace nitisa
{
	class ITexture;

	class IPicture
	{
	protected:
		IPicture() = default;
		~IPicture() = default;
		IPicture(const IPicture &other) = delete;
		IPicture(IPicture &&other) = delete;
		IPicture &operator=(const IPicture &other) = delete;
		IPicture &operator=(IPicture &&other) = delete;
	public:
		struct Format // Describe file format
		{
			String Name; // Format name
			String Extension; // Format file extension
		};

		struct SaveOptionsJpeg // Jpeg image options
		{
			int Quality; // Compression quality. 0..100
		};
	protected:
		String m_sFilter;
	public:
		String const &Filter{ m_sFilter }; // Filter to be used in Open/Save dialogs to allow select all supported formats

		virtual int getSupportedFormatCount() = 0; // Return count of supported image formats
		virtual Format getSupportedFormat(const int index) = 0; // Return supported image format by index. Members are empty strings if index is out of bounds

		virtual Image Load(const String &filename) = 0; // Load image from file. If it's failed, result bitmap size is zero
		virtual bool Load(const String &filename, ITexture *dest) = 0; // Load image from file directly into texture
		virtual bool Save(const String &filename, const Image &bmp, const void *options = nullptr) = 0; // Save bitmap into file. Format depends on extension
		virtual bool Save(const String &filename, ITexture *texture, const void *options = nullptr) = 0; // Save texture into file. Format depends on extension
	};
}
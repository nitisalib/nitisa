// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Variant.h"
#include "Color.h"
#include <iostream>

namespace nitisa
{
	// All drawing operations SHOULDN'T include last points(right and bottom edges)
	class Image
	{
	private:
		struct COLUMN
		{
		private:
			Color Data;
		public:
			const Color &operator[](const int index) const
			{
				return *reinterpret_cast<const Color*>(&Data + index);
			}

			Color &operator[](const int index)
			{
				return *reinterpret_cast<Color*>(&Data + index);
			}
		};

		int m_iWidth;
		int m_iHeight;
		Color *m_pData;
		const Color *m_pConstData;
		bool m_bDestroyable;
	public:
		int const &Width{ m_iWidth };
		int const &Height{ m_iHeight };
		const Color* const &Data{ m_pConstData };

		Image(); // Create empty
		Image(const int w, const int h); // Create with specified size
		Image(const int w, const int h, const Color *data); // Create with specified size and data.
		Image(const Image &other); // Copy
		Image(Image &&other); // Move
		~Image(); // Destructor

		const COLUMN &operator[](const int x) const // Return bitmap column. You can access pixel as bmp[x][y]. This is the fastest access pixel method but it is unsafe, so be sure you are not accessing pixel outside of bitmap
		{
			return *reinterpret_cast<const COLUMN*>(&m_pConstData[x * m_iHeight]);
		}

		COLUMN &operator[](const int x) // Return bitmap column. You can access pixel as bmp[x][y]. This is the fastest access pixel method but it is unsafe, so be sure you are not accessing pixel outside of bitmap
		{
			return *reinterpret_cast<COLUMN*>(&m_pData[x * m_iHeight]);
		}

		Image &operator=(const Image &other); // Copy
		Image &operator=(Image &&other); // Move
		bool operator==(const Image &other) const; // Check if bitmaps are equal
		bool operator!=(const Image &other) const; // Check if bitmaps are not equal

		Color getPixel(const int x, const int y) const // Return pixel from specified position. It is safe method of accessing pixel as it checks whether specified coordinates are inside the bitmap. If bitmap is empty, zero pixel will be returned. If coordinates are outside the bitmap, nearest border pixel will be returned. This method is slower than corresponding operators because it check coordinates first
		{
			if (m_iWidth > 0)
				return m_pConstData[((x < 0) ? 0 : ((x >= m_iWidth) ? (m_iWidth - 1) : x)) * m_iHeight + ((y < 0) ? 0 : ((y >= m_iHeight) ? (m_iHeight - 1) : y))];
			return Color{ 0, 0, 0, 0 };
		}

		Color getPixel(const int x, const int y, const Color &def) const // Return pixel from specified position or def one if position is outside the bitmap
		{
			if (x >= 0 && x < m_iWidth && y >= 0 && y < m_iHeight)
				return m_pConstData[x * m_iHeight + y];
			return def;
		}

		const bool isEmpty() const // Check whether it is empty
		{
			return m_iWidth <= 0 || m_iHeight <= 0;
		}

		bool setWidth(const int value) // Set width
		{
			return setSize(value, m_iHeight);
		}

		bool setHeight(const int value) // Set height
		{
			return setSize(m_iWidth, value);
		}

		bool setSize(const int w, const int h); // Set size
		bool setPixel(const int x, const int y, const Color &value); // Set pixel at specified position. It is safe method for setting pixel as it checks whether specified coordinates are inside the bitmap. If coordinates are invalid, no changes will be made. This method is slower than corresponding operators because it check coordinates first
		bool setData(const int w, const int h, const Color *data); // Set size and data
	};

	std::wostream &operator<<(std::wostream &stream, const Image &a); // Output as source code

	void ImageToVariant(const Image &bmp, Variant &dest);
	void VariantToImage(Image &bmp, const Variant &value);
}
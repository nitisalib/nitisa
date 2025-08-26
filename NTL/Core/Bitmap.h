// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Pixel.h"
#include <cstring>

namespace ntl
{
	template<class TYPE, size_t CHANNELS = 4>
	class TBitmap
	{
	private:
		struct COLUMN
		{
		private:
			TPixel<TYPE, CHANNELS> Data;
		public:
			const TPixel<TYPE, CHANNELS> &operator[](const size_t index) const
			{
				return *reinterpret_cast<const TPixel<TYPE, CHANNELS>*>(&Data + index);
			}

			TPixel<TYPE, CHANNELS> &operator[](const size_t index)
			{
				return *reinterpret_cast<TPixel<TYPE, CHANNELS>*>(&Data + index);
			}
		};
	private:
		size_t m_iWidth;
		size_t m_iHeight;
		TPixel<TYPE, CHANNELS> *m_pData;
		const TPixel<TYPE, CHANNELS> *m_pConstData;
		bool m_bDestroyable;
	public:
		size_t const &Width{ m_iWidth }; // Width of the bitmap. Read only
		size_t const &Height{ m_iHeight }; // Height of the bitmap. Read only
		const TPixel<TYPE, CHANNELS>* const &Data{ m_pConstData }; // Pointer to pixels array. Read only
		bool const &Destroyable{ m_bDestroyable }; // Whether bitmap is constant one or not(destroyable)

		TBitmap() : // Create empty bitmap
			m_iWidth{ 0 },
			m_iHeight{ 0 },
			m_pData{ nullptr },
			m_pConstData{ nullptr },
			m_bDestroyable{ true }
		{

		}

		TBitmap(const size_t w, const size_t h) : // Create bitmap of specified size
			m_bDestroyable{ true }
		{
			if (w > 0 && h > 0)
			{
				m_iWidth = w;
				m_iHeight = h;
				m_pData = new TPixel<TYPE, CHANNELS>[m_iWidth * m_iHeight];
				m_pConstData = m_pData;
			}
			else
			{
				m_iWidth = m_iHeight = 0;
				m_pData = nullptr;
				m_pConstData = nullptr;
			}
		}

		TBitmap(const size_t w, const size_t h, const TPixel<TYPE, CHANNELS> *data) // Create constant bitmap of specified size and pixels
		{
			if (w > 0 && h > 0 && data)
			{
				m_iWidth = w;
				m_iHeight = h;
				m_pData = nullptr;
				m_pConstData = data;
				m_bDestroyable = false;
			}
			else
			{
				m_iWidth = m_iHeight = 0;
				m_pData = nullptr;
				m_pConstData = nullptr;
				m_bDestroyable = true;
			}
		}

		TBitmap(const TBitmap &other) : // Copy constructor
			m_iWidth{ other.m_iWidth },
			m_iHeight{ other.m_iHeight },
			m_pData{ nullptr },
			m_pConstData{ nullptr },
			m_bDestroyable{ true }
		{
			if (m_iWidth > 0)
			{
				size_t size{ m_iWidth * m_iHeight };
				m_pData = new TPixel<TYPE, CHANNELS>[size];
				m_pConstData = m_pData;
				memcpy(m_pData, other.m_pConstData, size * sizeof(TPixel<TYPE, CHANNELS>));
			}
		}

		TBitmap(TBitmap &&other) : // Move constructor
			m_iWidth{ other.m_iWidth },
			m_iHeight{ other.m_iHeight },
			m_pData{ other.m_pData },
			m_pConstData{ other.m_pConstData },
			m_bDestroyable{ other.m_bDestroyable }
		{
			other.m_iWidth = other.m_iHeight = 0;
			other.m_pData = nullptr;
			other.m_pConstData = nullptr;
		}

		~TBitmap() // Destructor
		{
			if (m_bDestroyable && m_pData)
				delete[]m_pData;
		}

		const COLUMN &operator[](const size_t x) const // Return constant reference to specified column of bitmap
		{
			return *reinterpret_cast<const COLUMN*>(&m_pConstData[x * m_iHeight]);
		}

		COLUMN &operator[](const size_t x) // Return reference to specified column of bitmap
		{
			return *reinterpret_cast<COLUMN*>(&m_pData[x * m_iHeight]);
		}

		TBitmap &operator=(const TBitmap &other) // Copy assignement
		{
			if (m_bDestroyable)
			{
				if (m_pData && (m_iWidth != other.m_iWidth || m_iHeight != other.m_iHeight))
				{
					delete[] m_pData;
					m_pData = nullptr;
					m_pConstData = nullptr;
				}
			}
			else
			{
				m_pData = nullptr;
				m_pConstData = nullptr;
				m_bDestroyable = true;
			}
			m_iWidth = other.m_iWidth;
			m_iHeight = other.m_iHeight;
			if (m_iWidth > 0)
			{
				size_t size{ m_iWidth * m_iHeight };
				if (!m_pData)
					m_pData = new TPixel<TYPE, CHANNELS>[size];
				m_pConstData = m_pData;
				memcpy(m_pData, other.m_pConstData, size * sizeof(TPixel<TYPE, CHANNELS>));
			}
			return *this;
		}

		TBitmap &operator=(TBitmap &&other) // Move assignement
		{
			if (m_bDestroyable && m_pData)
				delete[] m_pData;
			m_iWidth = other.m_iWidth;
			m_iHeight = other.m_iHeight;
			m_pData = other.m_pData;
			m_pConstData = other.m_pConstData;
			m_bDestroyable = other.m_bDestroyable;
			other.m_iWidth = other.m_iHeight = 0;
			other.m_pData = nullptr;
			other.m_pConstData = nullptr;
			return *this;
		}

		TPixel<TYPE, CHANNELS> getPixel(const size_t x, const size_t y) const // Return pixel at specified position
		{
			if (m_iWidth > 0)
				return m_pConstData[((x >= m_iWidth) ? (m_iWidth - 1) : x) * m_iHeight + ((y >= m_iHeight) ? (m_iHeight - 1) : y)];
			return TPixel<TYPE, CHANNELS>{ };
		}

		TPixel<TYPE, CHANNELS> getPixel(const size_t x, const size_t y, const TPixel<TYPE, CHANNELS> &def) const // Return pixel at specified position or specified one("def" argument) if specified position is out of bitmap dimentions
		{
			if (x < m_iWidth && y < m_iHeight)
				return m_pConstData[x * m_iHeight + y];
			return def;
		}

		bool isEmpty() const // Return whether bitmap has pixels or it empty
		{
			return m_iWidth == 0 || m_iHeight == 0;
		}

		bool setWidth(const size_t value) // Set new width. Return false and do nothing if bitmap already has specified width
		{
			return setSize(value, m_iHeight);
		}

		bool setHeight(const size_t value) // Set new height. Return false and do nothing if bitmap already has specified height
		{
			return setSize(m_iWidth, value);
		}

		bool setSize(const size_t w, const size_t h) // Set new size. Return false and do nothing if bitmap already has specified size
		{
			if (w != m_iWidth || h != m_iHeight)
			{
				if (m_bDestroyable && m_pData)
				{
					delete[] m_pData;
					m_pData = nullptr;
					m_pConstData = nullptr;
				}
				if (w > 0 && h > 0)
				{
					m_iWidth = w;
					m_iHeight = h;
					m_pData = new TPixel<TYPE, CHANNELS>[m_iWidth * m_iHeight];
					m_pConstData = m_pData;
				}
				else
				{
					m_iWidth = m_iHeight = 0;
					m_pData = nullptr;
					m_pConstData = nullptr;
				}
				m_bDestroyable = true;
				return true;
			}
			return false;
		}

		bool setPixel(const size_t x, const size_t y, const TPixel<TYPE, CHANNELS> &value) // Set pixel at specified position. Return false if position is out of bitmap bounds
		{
			if (m_bDestroyable && x < m_iWidth && y < m_iHeight)
			{
				m_pData[x * m_iHeight + y] = value;
				return true;
			}
			return false;
		}

		bool setData(const size_t w, const size_t h, const TPixel<TYPE, CHANNELS> *data) // Makes constant bitmap
		{
			if (w != m_iWidth || h != m_iHeight || data != m_pConstData || m_bDestroyable)
			{
				if (m_bDestroyable && m_pData)
				{
					delete[] m_pData;
					m_pData = nullptr;
					m_pConstData = nullptr;
				}
				if (w > 0 && h > 0 && data)
				{
					m_iWidth = w;
					m_iHeight = h;
					m_pData = nullptr;
					m_pConstData = data;
					m_bDestroyable = false;
				}
				else
				{
					m_iWidth = m_iHeight = 0;
					m_pData = nullptr;
					m_pConstData = nullptr;
				}
				return true;
			}
			return false;
		}
	};

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator==(const TBitmap<TYPE, CHANNELS> &a, const TBitmap<TYPE, CHANNELS> &b) // Compare if bitmaps are equal
	{
		if (b.Width != a.Width || b.Height != a.Height)
			return false;
		size_t size{ a.Width * a.Height };
		for (size_t i = 0; i < size; i++)
			if (a.Data[i] != b.Data[i])
				return false;
		return true;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator!=(const TBitmap<TYPE, CHANNELS> &a, const TBitmap<TYPE, CHANNELS> &b) // Compare if bitmaps aren't equal
	{
		if (b.Width != a.Width || b.Height != a.Height)
			return true;
		size_t size{ a.Width * a.Height };
		for (size_t i = 0; i < size; i++)
			if (a.Data[i] != b.Data[i])
				return true;
		return false;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsEqual(const TBitmap<TYPE, CHANNELS> &a, const TBitmap<TYPE, CHANNELS> &b) // Compare if bitmaps are equal
	{
		if (b.Width != a.Width || b.Height != a.Height)
			return false;
		size_t size{ a.Width * a.Height };
		for (size_t i = 0; i < size; i++)
			if (a.Data[i] != b.Data[i])
				return false;
		return true;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsEqual(const TBitmap<TYPE, CHANNELS> &a, const TBitmap<TYPE, CHANNELS> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare if bitmaps are equal(for float data types)
	{
		if (b.Width != a.Width || b.Height != a.Height)
			return false;
		size_t size{ a.Width * a.Height };
		for (size_t i = 0; i < size; i++)
			if (IsNotEqual<TYPE>(a.Data[i], b.Data[i], tolerance))
				return false;
		return true;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TBitmap<TYPE, CHANNELS> &a, const TBitmap<TYPE, CHANNELS> &b) // Compare if bitmaps aren't equal
	{
		if (b.Width != a.Width || b.Height != a.Height)
			return true;
		size_t size{ a.Width * a.Height };
		for (size_t i = 0; i < size; i++)
			if (a.Data[i] != b.Data[i])
				return true;
		return false;
	}

	template<class TYPE, size_t CHANNELS = 4>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TBitmap<TYPE, CHANNELS> &a, const TBitmap<TYPE, CHANNELS> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare if bitmaps aren't equal(for float data types)
	{
		if (b.Width != a.Width || b.Height != a.Height)
			return true;
		size_t size{ a.Width * a.Height };
		for (size_t i = 0; i < size; i++)
			if (IsNotEqual<TYPE>(a.Data[i], b.Data[i], tolerance))
				return true;
		return false;
	}

	template<class TO, class FROM, size_t CHANNELS = 4>
	TBitmap<TO, CHANNELS> Convert(const TBitmap<FROM, CHANNELS> &b) // Convert to bitmap with another data type
	{
		TBitmap<TO, CHANNELS> r{ b.Width, b.Height };
		for (size_t i = 0; i < b.Width; i++)
			for (size_t j = 0; j < b.Height; j++)
			r[i][j] = Convert<TO, FROM, CHANNELS>(b[i][j]);
		return r;
	}
}
// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	ImageMask::ImageMask() :
		m_iWidth{ 0 },
		m_iHeight{ 0 },
		m_pData{ nullptr },
		m_pConstData{ nullptr },
		m_bDestroyable{ true }
	{

	}

	ImageMask::ImageMask(const int w, const int h) :
		m_bDestroyable{ true }
	{
		if (w > 0 && h > 0)
		{
			m_iWidth = w;
			m_iHeight = h;
			m_pData = new unsigned char[m_iWidth * m_iHeight];
			m_pConstData = m_pData;
		}
		else
		{
			m_iWidth = m_iHeight = 0;
			m_pData = nullptr;
			m_pConstData = nullptr;
		}
	}

	ImageMask::ImageMask(const int w, const int h, const unsigned char *data)
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

	ImageMask::ImageMask(const ImageMask &other) :
		m_iWidth{ other.m_iWidth },
		m_iHeight{ other.m_iHeight },
		m_pData{ nullptr },
		m_pConstData{ nullptr },
		m_bDestroyable{ true }
	{
		if (m_iWidth > 0)
		{
			int size{ m_iWidth * m_iHeight };
			m_pData = new unsigned char[size];
			m_pConstData = m_pData;
			memcpy(m_pData, other.m_pConstData, size);
		}
	}

	ImageMask::ImageMask(ImageMask &&other) :
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

	ImageMask::~ImageMask()
	{
		if (m_bDestroyable && m_pData)
			delete[]m_pData;
	}
#pragma endregion

#pragma region Operators
	ImageMask &ImageMask::operator=(const ImageMask &other)
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
			int size{ m_iWidth * m_iHeight };
			if (!m_pData)
				m_pData = new unsigned char[size];
			m_pConstData = m_pData;
			memcpy(m_pData, other.m_pConstData, size);
		}
		return *this;
	}

	ImageMask &ImageMask::operator=(ImageMask &&other)
	{
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

	bool ImageMask::operator==(const ImageMask &other) const
	{
		if (other.Width != Width || other.Height != Height)
			return false;
		int size{ Width * Height };
		for (int i = 0; i < size; i++)
			if (other.Data[i] != Data[i])
				return false;
		return true;
	}

	bool ImageMask::operator!=(const ImageMask &other) const
	{
		if (other.Width != Width || other.Height != Height)
			return true;
		int size{ Width * Height };
		for (int i = 0; i < size; i++)
			if (other.Data[i] != Data[i])
				return true;
		return false;
	}
#pragma endregion

#pragma region Setters
	bool ImageMask::setSize(const int w, const int h)
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
				m_pData = new unsigned char[m_iWidth * m_iHeight];
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

	bool ImageMask::setPixel(const int x, const int y, const unsigned char value)
	{
		if (m_bDestroyable && x >= 0 && x < m_iWidth && y >= 0 && y < m_iHeight)
		{
			m_pData[x * m_iHeight + y] = value;
			return true;
		}
		return false;
	}

	bool ImageMask::setData(const int w, const int h, const unsigned char *data)
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
#pragma endregion

#pragma region Operators
	std::wostream &operator<<(std::wostream &stream, const ImageMask &a)
	{
		stream << L"{" << std::endl;
		for (int x = 0; x < a.Width; x++)
		{
			for (int y = 0; y < a.Height; y++)
				stream << a[x][y] << L", ";
			stream << std::endl;
		}
		stream << L"}";
		return stream;
	}
#pragma endregion
}
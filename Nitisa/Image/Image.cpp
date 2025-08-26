// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	Image::Image() :
		m_iWidth{ 0 },
		m_iHeight{ 0 },
		m_pData{ nullptr },
		m_pConstData{ nullptr },
		m_bDestroyable{ true }
	{

	}

	Image::Image(const int w, const int h) :
		m_bDestroyable{ true }
	{
		if (w > 0 && h > 0)
		{
			m_iWidth = w;
			m_iHeight = h;
			m_pData = new Color[m_iWidth * m_iHeight];
			m_pConstData = m_pData;
		}
		else
		{
			m_iWidth = m_iHeight = 0;
			m_pData = nullptr;
			m_pConstData = nullptr;
		}
	}

	Image::Image(const int w, const int h, const Color *data)
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

	Image::Image(const Image &other) :
		m_iWidth{ other.m_iWidth },
		m_iHeight{ other.m_iHeight },
		m_pData{ nullptr },
		m_pConstData{ nullptr },
		m_bDestroyable{ true }
	{
		if (m_iWidth > 0)
		{
			int size{ m_iWidth * m_iHeight };
			m_pData = new Color[size];
			m_pConstData = m_pData;
			memcpy(m_pData, other.m_pConstData, size * sizeof(Color));
		}
	}

	Image::Image(Image &&other) :
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

	Image::~Image()
	{
		if (m_bDestroyable && m_pData)
			delete[]m_pData;
	}
#pragma endregion

#pragma region Operators
	Image &Image::operator=(const Image &other)
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
				m_pData = new Color[size];
			m_pConstData = m_pData;
			memcpy(m_pData, other.m_pConstData, size * sizeof(Color));
		}
		return *this;
	}

	Image &Image::operator=(Image &&other)
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

	bool Image::operator==(const Image &other) const
	{
		if (other.Width != Width || other.Height != Height)
			return false;
		int size{ Width * Height };
		for (int i = 0; i < size; i++)
			if (other.Data[i] != Data[i])
				return false;
		return true;
	}

	bool Image::operator!=(const Image &other) const
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
	bool Image::setSize(const int w, const int h)
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
				m_pData = new Color[m_iWidth * m_iHeight];
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

	bool Image::setPixel(const int x, const int y, const Color &value)
	{
		if (m_bDestroyable && x >= 0 && x < m_iWidth && y >= 0 && y < m_iHeight)
		{
			m_pData[x * m_iHeight + y] = value;
			return true;
		}
		return false;
	}

	bool Image::setData(const int w, const int h, const Color *data)
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
	std::wostream &operator<<(std::wostream &stream, const Image &a)
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

#pragma region Functions
	void ImageToVariant(const Image &bmp, Variant &dest)
	{
		dest[L"Width"] = bmp.Width;
		dest[L"Height"] = bmp.Height;
		String data;
		data.resize(bmp.Width * bmp.Height * 8);
		int index{ 0 };
		Color pixel;
		for (int y = 0; y < bmp.Height; y++)
			for (int x = 0; x < bmp.Width; x++)
			{
				pixel = bmp[x][y];
				data[index++] = ByteHiToHex(pixel.R);
				data[index++] = ByteLoToHex(pixel.R);
				data[index++] = ByteHiToHex(pixel.G);
				data[index++] = ByteLoToHex(pixel.G);
				data[index++] = ByteHiToHex(pixel.B);
				data[index++] = ByteLoToHex(pixel.B);
				data[index++] = ByteHiToHex(pixel.A);
				data[index++] = ByteLoToHex(pixel.A);
			}
		dest[L"Data"] = data;
	}

	void VariantToImage(Image &bmp, const Variant &value)
	{
		bmp.setSize((int)value.get(L"Width"), (int)value.get(L"Height"));
		String data{ (String)value.get(L"Data") };
		if (!bmp.isEmpty() && (int)data.length() >= bmp.Width * bmp.Height * 8)
		{
			int index{ 0 };
			for (int y = 0; y < bmp.Height; y++)
				for (int x = 0; x < bmp.Width; x++)
				{
					Color c;
					c.R = (unsigned char)((HexToByte(data[index]) << 4) + HexToByte(data[index + 1])); index += 2;
					c.G = (unsigned char)((HexToByte(data[index]) << 4) + HexToByte(data[index + 1])); index += 2;
					c.B = (unsigned char)((HexToByte(data[index]) << 4) + HexToByte(data[index + 1])); index += 2;
					c.A = (unsigned char)((HexToByte(data[index]) << 4) + HexToByte(data[index + 1])); index += 2;
					bmp[x][y] = c;
				}
		}
	}
#pragma endregion
}
// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
		#pragma region Constructor & destructor
			CPlatformFont::CPlatformFont(IRenderer *renderer) :
				CBasePlatformFont(),
				m_pRenderer{ renderer },
				m_pTexture{ nullptr }
			{
				*reinterpret_cast<HFONT*>(&m_hHandle) = 0;
				*reinterpret_cast<HDC*>(&m_hDC) = 0;
			}

			void CPlatformFont::BeforeRelease()
			{
				if (m_pTexture)
					m_pTexture->Release();
				DeleteDC(*reinterpret_cast<HDC*>(&m_hDC));
				DeleteObject(*reinterpret_cast<HFONT*>(&m_hHandle));
			}
		#pragma endregion

		#pragma region Helpers
			CBasePlatformFont::Char *CPlatformFont::getChar(const wchar_t chr)
			{
				return CBasePlatformFont::GetChar(chr);
			}

			CBasePlatformFont::Char *CPlatformFont::CreateChar(const wchar_t chr)
			{
				// Set font
				HFONT old_font{ (HFONT)SelectObject(*reinterpret_cast<HDC*>(&m_hDC), *reinterpret_cast<HFONT*>(&m_hHandle)) };
				// Try get char sizes
				SIZE size;
				if (!GetTextExtentPoint32W(*reinterpret_cast<HDC*>(&m_hDC), &chr, 1, &size))
				{
					SelectObject(*reinterpret_cast<HDC*>(&m_hDC), old_font);
					return nullptr;
				}
				// Create bitmap where to paint
				HBITMAP bmp = CreateCompatibleBitmap(*reinterpret_cast<HDC*>(&m_hDC), size.cx * 2, size.cy);
				if (!bmp)
				{
					SelectObject(*reinterpret_cast<HDC*>(&m_hDC), old_font);
					return nullptr;
				}
				HBITMAP old_bmp = (HBITMAP)SelectObject(*reinterpret_cast<HDC*>(&m_hDC), bmp);
				// Prepare painting
				SetTextColor(*reinterpret_cast<HDC*>(&m_hDC), 0x00FFFFFF);
				SetBkColor(*reinterpret_cast<HDC*>(&m_hDC), 0x00000000);
				HBRUSH brush = CreateSolidBrush(0x00000000);
				RECT rect = { 0, 0, size.cx * 2, size.cy };
				FillRect(*reinterpret_cast<HDC*>(&m_hDC), &rect, brush);
				DeleteObject(brush);
				// Draw text & select old font and bmp
				TextOutW(*reinterpret_cast<HDC*>(&m_hDC), 0, 0, &chr, 1);
				SelectObject(*reinterpret_cast<HDC*>(&m_hDC), old_bmp);
				SelectObject(*reinterpret_cast<HDC*>(&m_hDC), old_font);
				// Try get bitmap data
				BITMAPINFO info;
				info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
				info.bmiHeader.biWidth = size.cx * 2;
				info.bmiHeader.biHeight = size.cy;
				info.bmiHeader.biPlanes = 1;
				info.bmiHeader.biBitCount = 24;
				info.bmiHeader.biCompression = BI_RGB;
				info.bmiHeader.biSizeImage = 0;
				info.bmiHeader.biXPelsPerMeter = 0;
				info.bmiHeader.biYPelsPerMeter = 0;
				info.bmiHeader.biClrImportant = 0;
				info.bmiHeader.biClrUsed = 0;
				int pitch = ((size.cx * 2 * 3 + 3) / sizeof(DWORD)) * sizeof(DWORD);
				unsigned char *bits = new unsigned char[pitch * size.cy];
				int lines = GetDIBits(*reinterpret_cast<HDC*>(&m_hDC), bmp, 0, size.cy, bits, &info, DIB_RGB_COLORS);
				DeleteObject(bmp);
				// Check data was received
				if (!lines)
				{
					delete[] bits;
					return nullptr;
				}
				if (m_pTexture)
				{
					m_pTexture->Release();
					m_pTexture = nullptr;
				}
				// Calc real width;
				int x1{ size.cx * 2 - 1 }, x2{ 0 }, x, y, w;
				unsigned char *scanline;
				for (y = 0; y < lines; y++)
				{
					scanline = &bits[pitch * (lines - y - 1)];
					for (x = 0; x < size.cx * 2; x++)
						if (scanline[x * 3] > 0)
						{
							x1 = ntl::Min<int>(x1, x);
							x2 = ntl::Max<int>(x2, x);
						}
				}
				w = ntl::Max<int>(0, x2 + 1 - x1);
				Char *image{ new Char };
				image->Char = chr;
				image->Width = (float)size.cx;
				image->Height = (float)lines;
				image->Data.setSize(w, lines);
				for (x = 0; x < image->Data.Width; x++)
					for (y = 0; y < image->Data.Height; y++)
						image->Data[x][y] = 0;
				for (y = 0; y < lines; y++)
				{
					scanline = &bits[pitch * (lines - y - 1)];
					for (x = 0; x < w; x++)
						image->Data[x][y] = scanline[(x + x1) * 3];
				}
				delete[] bits;
				return image;
			}

			ITexture *CPlatformFont::getTexture()
			{
				if (!m_pTexture)
				{
					Point size{ 0, 0 };
					for (auto pos : m_aChars)
					{
						size.X += pos->Data.Width + 1; // Add 1px distance between glyphs to avoid intersections
						size.Y = ntl::Max<int>(size.Y, pos->Data.Height);
					}
					if (size.X > 0 && size.Y > 0 && (m_pTexture = m_pRenderer->CreateTexture(size.X + 2, size.Y + 2, 1, TextureFormat::Alpha, false)))
					{
						size.X += 2;
						size.Y += 2;
						ITexture::IData *data{ m_pTexture->Lock(TextureFormat::Alpha, 0, false) };
						if (data)
						{
							int dx{ 1 }, tx, ty, x, y, w, h;
							// Clear
							for (ty = 0; ty < size.Y; ty++)
								for (tx = 0; tx < size.X; tx++)
									data->setColor(tx, ty, Color{ 0, 0, 0, 0 });
							// Draw chars
							for (auto pos : m_aChars)
							{
								w = pos->Data.Width;
								h = pos->Data.Height;
								for (y = 0; y < h; y++)
									for (x = 0; x < w; x++)
										data->setColor(x + dx, y + 1, Color{ 0, 0, 0, pos->Data[x][y] });
								pos->Tx1 = dx / (float)size.X;
								pos->Ty1 = 1.0f - 1.0f / size.Y;
								dx += w;
								pos->Tx2 = dx / (float)size.X;
								pos->Ty2 = 1.0f - (1.0f + h) / size.Y;
								dx++; // 1px distance
							}
							data->Release();
						}
					}
				}
				return m_pTexture;
			}
		#pragma endregion
		}
	}
}
#endif
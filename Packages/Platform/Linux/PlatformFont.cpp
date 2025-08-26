// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#if defined(__linux__) && !defined(__ANDROID__)
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
		#pragma region Constructor & destructor
			CPlatformFont::CPlatformFont(IRenderer *renderer) :
				CBasePlatformFont(),
				m_pRenderer{ renderer },
				m_pTexture{ nullptr }
			{

			}

			void CPlatformFont::BeforeRelease()
			{
				if (m_pTexture)
					m_pTexture->Release();
				cast<CApplication*>(Application)->FreeFontFace(*reinterpret_cast<CApplication::FONT_FACE**>(&m_hHandle));
			}
		#pragma endregion

		#pragma region Helpers
			CBasePlatformFont::Char *CPlatformFont::getChar(const wchar_t chr)
			{
				return CBasePlatformFont::GetChar(chr);
			}

			CBasePlatformFont::Char *CPlatformFont::CreateChar(const wchar_t chr)
			{
				if (!m_pRenderer)
					return nullptr;
				if (m_pTexture)
				{
					m_pTexture->Release();
					m_pTexture = nullptr;
				}

				Point resolution{ Application->Screen->getDPI() };

				FT_Face face{ FT_Face((*reinterpret_cast<CApplication::FONT_FACE**>(&m_hHandle))->Face) };
				FT_Set_Char_Size(face, 0, ntl::Abs<int>(m_iHeight) * 64, resolution.X, resolution.Y); // "std::abs()" is probably should be managed in another way
				if (FT_Load_Char(face, chr, FT_LOAD_RENDER) != 0)
					return nullptr;

				CBasePlatformFont::Char *image{ new CBasePlatformFont::Char };
				image->Char = chr;
				image->Width = float(face->glyph->metrics.horiAdvance >> 6);
				image->Height = float(face->size->metrics.height >> 6);
				image->Data.setSize(face->glyph->bitmap.width, ntl::Round<int>(image->Height));
				for (int x = 0; x < image->Data.Width; x++)
					for (int y = 0; y < image->Data.Height; y++)
						image->Data[x][y] = 0;

				int base_line{ -int(face->size->metrics.descender) >> 6 };
				for (int y = 0; y < (int)face->glyph->bitmap.rows; y++)
					for (int x = 0; x < (int)face->glyph->bitmap.width; x++)
						image->Data[x][y + image->Data.Height - 1 - face->glyph->bitmap_top - base_line] = face->glyph->bitmap.buffer[y * face->glyph->bitmap.width + x];

				if (m_bUnderline)
				{
					int underline{ -face->underline_position * m_iHeight / face->units_per_EM };
					int thickness{ face->underline_thickness * m_iHeight / face->units_per_EM };
					for (int y = 0; y < thickness; y++)
						for (int x = 0; x < image->Data.Width; x++)
							image->Data[x][y + image->Data.Height - 1 - underline] = 255;
				}

				if (m_bStrikeOut)
				{
					int strikeout{ int(face->size->metrics.ascender - face->size->metrics.descender) >> 7 };
					int thickness{ face->underline_thickness * m_iHeight / face->units_per_EM };
					for (int y = 0; y < thickness; y++)
						for (int x = 0; x < image->Data.Width; x++)
							image->Data[x][y + image->Data.Height - 1 - strikeout] = 255;
				}

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
								pos->Tx1 = (float)dx / (float)size.X;
								pos->Ty1 = 1 - 1 / (float)size.Y;
								dx += w;
								pos->Tx2 = (float)dx / (float)size.X;
								pos->Ty2 = 1 - (1 + (float)h) / (float)size.Y;
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
// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef __ANDROID__
#include "ft2build.h"
#include FT_FREETYPE_H
#include <Android/configuration.h>

namespace nitisa
{
	namespace platform
	{
		namespace android
		{
		#pragma region Constructor & destructor
			CPlatformFont::CPlatformFont(IRenderer *renderer) :
				CBasePlatformFont(),
				m_pRenderer{ renderer },
				m_pTexture{ nullptr },
				m_pApplication{ cast<CApplication*>(Application) }
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
				/*
				Working code:

				#include "stdafx.h"
				#include "ft2build.h"
				#include FT_FREETYPE_H
				#include "freetype/ftglyph.h"
				#include <iostream>

				#pragma comment(lib, "FTTest.lib")

				#include "M:/Dic/C++/Nitisa/Packages/Standard/Platform/Android/DefaultFontData.inc"

				int main()
				{
					FT_Library FreeTypeLibrary{ nullptr };
					FT_Init_FreeType(&FreeTypeLibrary);

					const FT_Byte *data{ nullptr };
					int size{ 0 };
					data = DefaultFontData_Regular;
					size = DefaultFontDataSize_Regular;

					FT_Face face;
					if (FT_New_Memory_Face(FreeTypeLibrary, (const FT_Byte*)&data[0], size, 0, &face) != 0)
						//if (FT_New_Face(FreeTypeLibrary, "m:\\Dic\\C++\\Nitisa\\Packages\\Standard\\Media\\Fonts\\LiberationSans-Bold.ttf", 0, &face) == 0)
						std::cout << "ERROR" << std::endl;

					const int font_size{ 48 };
					FT_Set_Char_Size(face, 0, font_size * 64, 72, 72);

					int line_height{ face->size->metrics.height >> 6 }, bitmap_width{ 100 };
					int base_line{ -face->size->metrics.descender >> 6 };
					int underline{ -face->underline_position * font_size / face->units_per_EM };
					int thickness{ face->underline_thickness * font_size / face->units_per_EM };
					int strikeout{ (face->size->metrics.ascender - face->size->metrics.descender) >> 7 };
					std::cout << "Line Height: " << line_height << std::endl;
					std::cout << "Base: " << base_line << std::endl;
					std::cout << "Underline: " << underline << std::endl;
					std::cout << "Tickness: " << thickness << std::endl;
					std::cout << "Strikeout: " << strikeout << std::endl;

					char *bitmap{ new char[bitmap_width * line_height] };
					for (int y = 0; y < line_height; y++)
						for (int x = 0; x < bitmap_width; x++)
							bitmap[y * bitmap_width + x] = '.';

					int d{ 0 };
					const wchar_t str[]{ L"Lg-" };
					for (auto c : str)
					{
						if (c == L'\0')
							continue;
						if (FT_Load_Char(face, c, FT_LOAD_RENDER) != 0)
						{
							std::cout << "ERROR" << std::endl;
							continue;
						}
						for (int y = 0; y < (int)face->glyph->bitmap.rows; y++)
							for (int x = 0; x < (int)face->glyph->bitmap.width; x++)
								if (face->glyph->bitmap.buffer[y * face->glyph->bitmap.width + x] > 0)
									bitmap[(y + line_height - 1 - face->glyph->bitmap_top - base_line) * bitmap_width + x + d + face->glyph->bitmap_left] = '0';

						for (int y = 0; y < thickness; y++)
							for (int x = 0; x < (face->glyph->metrics.horiAdvance >> 6); x++)
								bitmap[(y + line_height - 1 - underline) * bitmap_width + x + d] = '=';

						for (int y = 0; y < thickness; y++)
							for (int x = 0; x < face->glyph->metrics.horiAdvance >> 6; x++)
								bitmap[(y + line_height - 1 - strikeout) * bitmap_width + x + d] = 's';

						d += face->glyph->metrics.horiAdvance >> 6;
					}

					// Show image
					for (int y = 0; y < line_height; y++)
					{
						for (int x = 0; x < bitmap_width; x++)
							std::cout << bitmap[y * bitmap_width + x];
						std::cout << std::endl;
					}
					delete[] bitmap;

					if (FreeTypeLibrary)
						FT_Done_FreeType(FreeTypeLibrary);
					std::system("pause");
					return 0;
				}
				*/

				if (!m_pRenderer)
					return nullptr;
				if (m_pTexture)
				{
					m_pTexture->Release();
					m_pTexture = nullptr;
				}

				Point resolution{ DesignDPI };
				if (m_pApplication->getConfiguration())
				{
					resolution.X = AConfiguration_getScreenWidthDp(m_pApplication->getConfiguration());
					resolution.Y = AConfiguration_getScreenHeightDp(m_pApplication->getConfiguration());
				}

				FT_Face face{ (FT_Face)(*reinterpret_cast<CApplication::FONT_FACE**>(&m_hHandle))->Face };
				FT_Set_Char_Size(face, 0, ntl::Abs<float>(m_iHeight) * 64, resolution.X, resolution.Y); // "std::abs()" is probably should be managed in another way
				if (FT_Load_Char(face, chr, FT_LOAD_RENDER) != 0)
					return nullptr;

				CBasePlatformFont::Char *image = new CBasePlatformFont::Char;
				image->Char = chr;
				image->Width = face->glyph->metrics.horiAdvance >> 6;
				image->Height = face->size->metrics.height >> 6;
				image->Data.setSize(face->glyph->bitmap.width, image->Height);
				for (int x = 0; x < image->Data.Width; x++)
					for (int y = 0; y < image->Data.Height; y++)
						image->Data[x][y] = 0;

				int base_line{ -int(face->size->metrics.descender) >> 6 };
				for (int y = 0; y < face->glyph->bitmap.rows; y++)
					for (int x = 0; x < face->glyph->bitmap.width; x++)
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
								pos->Tx1 = dx / (float)size.X;
								pos->Ty1 = 1 - 1.0f / size.Y;
								dx += w;
								pos->Tx2 = dx / (float)size.X;
								pos->Ty2 = 1 - (1.0f + h) / size.Y;
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
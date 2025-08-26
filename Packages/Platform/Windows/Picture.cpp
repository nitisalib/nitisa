// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>

#pragma comment(lib, "Gdiplus.lib")

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
			ULONG_PTR GdiplusToken;

		#pragma region Helper functions
			bool GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
			{
				UINT num{ 0 };
				UINT size{ 0 };
				Gdiplus::ImageCodecInfo* pImageCodecInfo{ nullptr };
				Gdiplus::GetImageEncodersSize(&num, &size);
				if (size == 0)
					return false;
				pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
				if (!pImageCodecInfo)
					return false;
				GetImageEncoders(num, size, pImageCodecInfo);
				for (UINT j = 0; j < num; ++j)
				{
					if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
					{
						*pClsid = pImageCodecInfo[j].Clsid;
						free(pImageCodecInfo);
						return true;
					}
				}

				free(pImageCodecInfo);
				return false;
			}
		#pragma endregion

		#pragma region Constructor & destructor
			CPicture::CPicture()
			{
				m_aFormats.push_back({ L"Bitmap", L"bmp" });
				m_aFormats.push_back({ L"Graphics Interchange Format", L"gif" });
				m_aFormats.push_back({ L"Joint Photographic Experts Group", L"jpg" });
				m_aFormats.push_back({ L"Joint Photographic Experts Group", L"jpeg" });
				m_aFormats.push_back({ L"Portable Network Graphics", L"png" });
				m_aFormats.push_back({ L"Tag Image File Format", L"tiff" });
				m_sFilter = L"All Supported Formats|*.bmp;*.gif;*.jpg;*.jpeg;*.png;*.tiff\n"
					L"Bitmap(*.bmp)|*.bmp\n"
					L"Graphics Interchange Format(*.gif)|*.gif\n"
					L"Joint Photographic Experts Group(*.jpg;*.jpeg)|*.jpg;*.jpeg\n"
					L"Portable Network Graphics(*.png)|*.png\n"
					L"Tag Image File Format(*.tiff)|*.tiff";

				Gdiplus::GdiplusStartupInput startup_input;
				Gdiplus::GdiplusStartup(&GdiplusToken, &startup_input, nullptr);
			}

			CPicture::~CPicture()
			{
				Gdiplus::GdiplusShutdown(GdiplusToken);
			}
		#pragma endregion

		#pragma region Getters
			int CPicture::getSupportedFormatCount()
			{
				return (int)m_aFormats.size();
			}

			CPicture::Format CPicture::getSupportedFormat(const int index)
			{
				if (index >= 0 && index < (int)m_aFormats.size())
					return m_aFormats[index];
				return Format{ L"", L"" };
			}
		#pragma endregion

		#pragma region Helpers
			Image CPicture::Load(const String &filename)
			{
				Gdiplus::Bitmap image{ filename.c_str() };
				Image result;
				if (image.GetWidth() > 0 && image.GetHeight() > 0)
				{
					Gdiplus::Color color;
					result.setSize(image.GetWidth(), image.GetHeight());
					for (int y = 0; y < result.Height; y++)
						for (int x = 0; x < result.Width; x++)
						{
							image.GetPixel(x, y, &color);
							result[x][y] = Color{ color.GetR(), color.GetG(), color.GetB(), color.GetA() };
						}
				}
				return result;
			}

			bool CPicture::Load(const String &filename, ITexture *dest)
			{
				if (dest)
				{
					Gdiplus::Bitmap image{ filename.c_str() };
					if (image.GetWidth() > 0 && image.GetHeight() > 0)
					{
						Gdiplus::Color color;
						dest->setSize(image.GetWidth(), image.GetHeight());
						ITexture::IData *data{ dest->Lock(TextureFormat::RGBA, 0, false) };
						if (data)
						{
							int w{ dest->Width }, h{ dest->Height };
							for (int y = 0; y < h; y++)
								for (int x = 0; x < w; x++)
								{
									image.GetPixel(x, y, &color);
									data->setColor( x, y, Color{ color.GetR(), color.GetG(), color.GetB(), color.GetA() });
								}
							data->Release();
							return true;
						}
					}
				}
				return false;
			}

			bool CPicture::Save(const String &filename, const Image &bmp, const void *options)
			{
				if (filename.empty() || bmp.Width == 0 || bmp.Height == 0)
					return false;
				String ext{ ToLower(ExtractFileExtension(filename)) };
				CLSID encoder_clsid;
				Gdiplus::EncoderParameters encoder_params, *params{ nullptr };
				Gdiplus::Bitmap *img{ nullptr };
				ULONG quality;
				if (ext == L"bmp")
				{
					if (!GetEncoderClsid(L"image/bmp", &encoder_clsid))
						return false;
					img = new Gdiplus::Bitmap(bmp.Width, bmp.Height, PixelFormat32bppARGB);
				}
				else if (ext == L"jpg" || ext == L"jpeg")
				{
					if (!GetEncoderClsid(L"image/jpeg", &encoder_clsid))
						return false;
					if (options)
					{
						quality = ntl::Clamp<int>(((SaveOptionsJpeg*)options)->Quality, 0, 100);
						encoder_params.Count = 1;
						encoder_params.Parameter[0].Guid = Gdiplus::EncoderQuality;
						encoder_params.Parameter[0].Type = Gdiplus::EncoderParameterValueTypeLong;
						encoder_params.Parameter[0].NumberOfValues = 1;
						encoder_params.Parameter[0].Value = &quality;
						params = &encoder_params;
					}
					img = new Gdiplus::Bitmap(bmp.Width, bmp.Height, PixelFormat32bppARGB);
				}
				else if (ext == L"png")
				{
					if (!GetEncoderClsid(L"image/bmp", &encoder_clsid))
						return false;
					img = new Gdiplus::Bitmap(bmp.Width, bmp.Height, PixelFormat32bppARGB);
				}
				else if (ext == L"gif")
				{
					if (!GetEncoderClsid(L"image/bmp", &encoder_clsid))
						return false;
					img = new Gdiplus::Bitmap(bmp.Width, bmp.Height, PixelFormat32bppARGB);
				}
				else if (ext == L"tiff")
				{
					if (!GetEncoderClsid(L"image/bmp", &encoder_clsid))
						return false;
					img = new Gdiplus::Bitmap(bmp.Width, bmp.Height, PixelFormat32bppARGB);
				}
				if (!img)
					return false;
				for (int y = 0; y < bmp.Height; y++)
					for (int x = 0; x < bmp.Width; x++)
					{
						Color p{ bmp[x][y] };
						Gdiplus::Color c{ p.A, p.R, p.G, p.B };
						img->SetPixel(x, y, c);
					}
				bool result{ img->Save(filename.c_str(), &encoder_clsid, params) == Gdiplus::Ok };
				delete img;
				return result;
			}

			bool CPicture::Save(const String &filename, ITexture *texture, const void *options)
			{
				if (filename.empty() || !texture || texture->Width == 0 || texture->Height == 0)
					return false;
				String ext{ ToLower(ExtractFileExtension(filename)) };
				CLSID encoder_clsid;
				Gdiplus::EncoderParameters encoder_params, *params{ nullptr };
				Gdiplus::Bitmap *img{ nullptr };
				ULONG quality;
				if (ext == L"bmp")
				{
					if (!GetEncoderClsid(L"image/bmp", &encoder_clsid))
						return false;
					img = new Gdiplus::Bitmap(texture->Width, texture->Height, PixelFormat32bppARGB);
				}
				else if (ext == L"jpg" || ext == L"jpeg")
				{
					if (!GetEncoderClsid(L"image/jpeg", &encoder_clsid))
						return false;
					if (options)
					{
						quality = ntl::Clamp<int>(((SaveOptionsJpeg*)options)->Quality, 0, 100);
						encoder_params.Count = 1;
						encoder_params.Parameter[0].Guid = Gdiplus::EncoderQuality;
						encoder_params.Parameter[0].Type = Gdiplus::EncoderParameterValueTypeLong;
						encoder_params.Parameter[0].NumberOfValues = 1;
						encoder_params.Parameter[0].Value = &quality;
						params = &encoder_params;
					}
					img = new Gdiplus::Bitmap(texture->Width, texture->Height, PixelFormat32bppARGB);
				}
				else if (ext == L"png")
				{
					if (!GetEncoderClsid(L"image/png", &encoder_clsid))
						return false;
					img = new Gdiplus::Bitmap(texture->Width, texture->Height, PixelFormat32bppARGB);
				}
				else if (ext == L"gif")
				{
					if (!GetEncoderClsid(L"image/gif", &encoder_clsid))
						return false;
					img = new Gdiplus::Bitmap(texture->Width, texture->Height, PixelFormat32bppARGB);
				}
				else if (ext == L"tiff")
				{
					if (!GetEncoderClsid(L"image/tiff", &encoder_clsid))
						return false;
					img = new Gdiplus::Bitmap(texture->Width, texture->Height, PixelFormat32bppARGB);
				}
				if (!img)
					return false;
				ITexture::IData *data{ texture->Lock(TextureFormat::RGBA, 0, true) };
				if (!data)
				{
					delete img;
					return false;
				}
				Point size{ texture->Size };
				for (int y = 0; y < size.Y; y++)
					for (int x = 0; x < size.X; x++)
					{
						Color p{ data->getColor(x, y) };
						img->SetPixel(x, y, Gdiplus::Color{ p.A, p.R, p.G, p.B });
					}
				data->Release();
				bool result{ img->Save(filename.c_str(), &encoder_clsid, params) == Gdiplus::Ok };
				delete img;
				return result;
			}
		#pragma endregion
		}
	}
}
#endif
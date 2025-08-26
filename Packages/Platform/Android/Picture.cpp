// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef __ANDROID__

#ifndef HAVE_PROTOTYPES
#define HAVE_PROTOTYPES
#endif
#include "jpeglib.h"
#include "png.h"

namespace nitisa
{
	namespace platform
	{
		namespace android
		{
		#pragma region Constructor & destrictor
			CPicture::CPicture(CApplication *application) :
				m_pApplication{ application }
			{
				m_aFormats.push_back(Format{ L"Joint Photographic Experts Group", L"jpg" });
				m_aFormats.push_back(Format{ L"Joint Photographic Experts Group", L"jpeg" });
				m_aFormats.push_back(Format{ L"Portable Network Graphics", L"png" });

				m_sFilter = L"All Supported Formats|*.jpg;*.jpeg;*.png\n"
					L"Joint Photographic Experts Group(*.jpg;*.jpeg)|*.jpg;*.jpeg\n"
					L"Portable Network Graphics(*.png)|*.png";

				m_aExtensions.push_back(L"jpg");
				m_aExtensions.push_back(L"jpeg");
				m_aExtensions.push_back(L"png");
			}
		#pragma endregion

		#pragma region Getters
			int CPicture::getSupportedFormatCount()
			{
				return (int)m_aFormats.size();
			}

			IPicture::Format CPicture::getSupportedFormat(const int index)
			{
				if (index >= 0 && index < (int)m_aFormats.size())
					return m_aFormats[index];
				return Format{ L"", L"" };
			}
		#pragma endregion

		#pragma region Helpers
			Image CPicture::Load(const String &filename)
			{
				Image result;
				// Asset manager is required
				if (!m_pApplication->getAssetManager())
					return result;
				// Validate file extension
				String ext{ ToLower(ExtractFileExtension(filename)) };
				if (!in<String>(ext, m_aExtensions))
					return result;
				IFile *file{ m_pApplication->FileSystem->FileOpen(filename, IFileSystem::OpenMode::OpenExisting, true, false) };
				if (!file)
					return result;
				unsigned int size{ (unsigned int)file->getSize() };
				if (size > 0)
				{
					unsigned char *data{ new unsigned char[size] };
					if (ext == L"jpg" || ext == L"jpeg")
						LoadJpeg(data, size, result);
					else if (ext == L"png")
						LoadPng(data, size, result);
				}
				file->Release();
				return result;
			}

			bool CPicture::Load(const String &filename, ITexture *dest)
			{
				if (dest && m_pApplication->getAssetManager())
				{
					// Validate file extension
					String ext{ ToLower(ExtractFileExtension(filename)) };
					if (in<String>(ext, m_aExtensions))
					{
						IFile *file{ m_pApplication->FileSystem->FileOpen(filename, IFileSystem::OpenMode::OpenExisting, true, false) };
						if (file)
						{
							unsigned int size{ (unsigned int)file->getSize() };
							bool result{ false };
							if (size > 0)
							{
								unsigned char *data{ new unsigned char[size] };
								if (ext == L"jpg" || ext == L"jpeg")
									result = LoadJpeg(data, size, dest);
								else if (ext == L"png")
									result = LoadPng(data, size, dest);
							}
							file->Release();
							return result;
						}
					}
				}
				return false;
			}

			void CPicture::LoadJpeg(const unsigned char *data, const int size, Image &result)
			{
				struct jpeg_decompress_struct cinfo;
				struct jpeg_error_mgr jerr;
				JSAMPARRAY buffer;
				jpeg_create_decompress(&cinfo);
				cinfo.err = jpeg_std_error(&jerr);
				jpeg_mem_src(&cinfo, data, size);
				if (jpeg_read_header(&cinfo, TRUE) == JPEG_HEADER_OK)
				{
					jpeg_start_decompress(&cinfo);
					if (cinfo.output_width > 0 && cinfo.output_height > 0 && (cinfo.out_color_components == 1 || cinfo.out_color_components == 3))
					{
						result.setSize(cinfo.output_width, cinfo.output_height);
						buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, cinfo.output_width * cinfo.output_components, 1);
						int y{ 0 };
						while (cinfo.output_scanline < cinfo.output_height)
						{
							jpeg_read_scanlines(&cinfo, buffer, 1);
							if (cinfo.out_color_components == 3)
							{
								for (int x = 0; x < cinfo.output_width; x++)
									result[x][y] = Color{ (unsigned char)buffer[0][x * 3], (unsigned char)buffer[0][x * 3 + 1], (unsigned char)buffer[0][x * 3 + 2], 255 };
							}
							else
							{
								for (int x = 0; x < cinfo.output_width; x++)
									result[x][y] = Color{ (unsigned char)buffer[0][x * 3], (unsigned char)buffer[0][x * 3], (unsigned char)buffer[0][x * 3], 255 };
							}
						}
					}
					jpeg_finish_decompress(&cinfo);
				}
				jpeg_destroy_decompress(&cinfo);
			}

			bool CPicture::LoadJpeg(const unsigned char *data, const int size, ITexture *dest)
			{
				bool result{ false };
				struct jpeg_decompress_struct cinfo;
				struct jpeg_error_mgr jerr;
				JSAMPARRAY buffer;
				jpeg_create_decompress(&cinfo);
				cinfo.err = jpeg_std_error(&jerr);
				jpeg_mem_src(&cinfo, data, size);
				if (jpeg_read_header(&cinfo, TRUE) == JPEG_HEADER_OK)
				{
					jpeg_start_decompress(&cinfo);
					if (cinfo.output_width > 0 && cinfo.output_height > 0 && (cinfo.out_color_components == 1 || cinfo.out_color_components == 3))
					{
						dest->setSize(cinfo.output_width, cinfo.output_height);
						ITexture::IData *data{ dest->Lock(TextureFormat::RGBA, 0, false) };
						if (data)
						{
							buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, cinfo.output_width * cinfo.output_components, 1);
							int y{ 0 };
							while (cinfo.output_scanline < cinfo.output_height)
							{
								jpeg_read_scanlines(&cinfo, buffer, 1);
								if (cinfo.out_color_components == 3)
								{
									for (int x = 0; x < cinfo.output_width; x++)
										data->setColor(x, y, Color{ (unsigned char)buffer[0][x * 3], (unsigned char)buffer[0][x * 3 + 1], (unsigned char)buffer[0][x * 3 + 2], 255 });
								}
								else
								{
									for (int x = 0; x < cinfo.output_width; x++)
										data->setColor(x, y, Color{ (unsigned char)buffer[0][x * 3], (unsigned char)buffer[0][x * 3], (unsigned char)buffer[0][x * 3], 255 });
								}
							}
							data->Release();
							result = true;
						}
					}
					jpeg_finish_decompress(&cinfo);
				}
				jpeg_destroy_decompress(&cinfo);
				return result;
			}

			void CPicture::LoadPng(const void *data, const int size, Image &result)
			{
				png_image image; /* The control structure used by libpng */

				/* Initialize the 'png_image' structure. */
				memset(&image, 0, (sizeof image));
				image.version = PNG_IMAGE_VERSION;

				/* The first argument is the file to read: */
				if (png_image_begin_read_from_memory(&image, (png_const_voidp)data, (png_size_t)size))
				{
					if (image.width > 0 && image.height > 0)
					{
						image.format = PNG_FORMAT_RGBA;
						png_bytep buffer{ (png_bytep)malloc(PNG_IMAGE_SIZE(image)) };
						if (buffer)
						{
							if (png_image_finish_read(&image, nullptr, buffer, 0, nullptr) != 0)
							{
								result.setSize(image.width, image.height);
								for (int y = 0; y < image.height; y++)
								{
									unsigned char *p{ buffer + y * image.width * 4 };
									for (int x = 0; x < image.width; x++)
										result[x][y] = Color{ p[x * 4], p[x * 4 + 1], p[x * 4 + 2], p[x * 4 + 3] };
								}
							}
							free(buffer);
						}
					}
					png_image_free(&image);
				}
			}

			bool CPicture::LoadPng(const void *data, const int size, ITexture *dest)
			{
				bool result{ false };
				png_image image; /* The control structure used by libpng */

				/* Initialize the 'png_image' structure. */
				memset(&image, 0, (sizeof image));
				image.version = PNG_IMAGE_VERSION;

				/* The first argument is the file to read: */
				if (png_image_begin_read_from_memory(&image, (png_const_voidp)data, (png_size_t)size))
				{
					if (image.width > 0 && image.height > 0)
					{
						image.format = PNG_FORMAT_RGBA;
						png_bytep buffer{ (png_bytep)malloc(PNG_IMAGE_SIZE(image)) };
						if (buffer)
						{
							if (png_image_finish_read(&image, nullptr, buffer, 0, nullptr) != 0)
							{
								dest->setSize(image.width, image.height);
								ITexture::IData *data{ dest->Lock(TextureFormat::RGBA, 1, false) };
								if (data)
								{
									for (int y = 0; y < image.height; y++)
									{
										unsigned char *p{ buffer + y * image.width * 4 };
										for (int x = 0; x < image.width; x++)
											data->setColor(x, y, Color{ p[x * 4], p[x * 4 + 1], p[x * 4 + 2], p[x * 4 + 3] });
									}
									data->Release();
									result = true;
								}
							}
							free(buffer);
						}
					}
					png_image_free(&image);
				}
				return result;
			}

			bool CPicture::Save(const String &filename, const Image &bmp, const void *options)
			{
				if (filename.empty() || bmp.Width == 0 || bmp.Height == 0)
					return false;
				String ext{ ToLower(ExtractFileExtension(filename)) };
				if (ext == L"jpg" || ext == L"jpeg")
					return SaveJpeg(filename, bmp, options ? ((SaveOptionsJpeg*)options)->Quality : 50);
				if (ext == L"png")
					return SavePng(filename, bmp);
				return false;
			}

			bool CPicture::Save(const String &filename, ITexture *texture, const void *options)
			{
				if (filename.empty() || !texture || texture->Width == 0 || texture->Height == 0)
					return false;
				String ext{ ToLower(ExtractFileExtension(filename)) };
				if (!in(ext, StringArray{ L"jpg", L"jpeg", L"png" }))
					return false;
				ITexture::IData *data{ texture->Lock(TextureFormat::RGBA, 0, true) };
				if (data)
				{
					Image bmp{ data->Width, data->Height };
					for (int y = 0; y < data->Height; y++)
						for (int x = 0; x < data->Width; x++)
							bmp[x][y] = data->getColor(x, y);
					data->Release();
					if (ext == L"jpg" || ext == L"jpeg")
						return SaveJpeg(filename, bmp, options ? ((SaveOptionsJpeg*)options)->Quality : 50);
					if (ext == L"png")
						return SavePng(filename, bmp);
				}
				return false;
			}

			bool CPicture::SaveJpeg(const String &filename, const Image &bmp, const int quality)
			{
				struct jpeg_compress_struct cinfo;
				struct jpeg_error_mgr jerr;
				FILE * outfile;
				JSAMPROW row_pointer[1];

				cinfo.err = jpeg_std_error(&jerr);
				jpeg_create_compress(&cinfo);
				if ((outfile = fopen(StringToAnsi(filename).c_str(), "wb")) == nullptr)
					return false;
				jpeg_stdio_dest(&cinfo, outfile);
				cinfo.image_width = bmp.Width;
				cinfo.image_height = bmp.Height;
				cinfo.input_components = 3;
				cinfo.in_color_space = JCS_RGB;
				jpeg_set_defaults(&cinfo);
				jpeg_set_quality(&cinfo, quality, TRUE);
				jpeg_start_compress(&cinfo, TRUE);

				unsigned char *row{ new unsigned char[bmp.Width * 3] };
				row_pointer[0] = (JSAMPROW)row;
				while (cinfo.next_scanline < cinfo.image_height)
				{
					for (int x = 0; x < bmp.Width; x++)
					{
						Color c{ bmp[x][(int)cinfo.next_scanline] };
						row[x * 3 + 0] = c.R;
						row[x * 3 + 1] = c.G;
						row[x * 3 + 2] = c.B;
					}
					jpeg_write_scanlines(&cinfo, row_pointer, 1);
				}
				delete[] row;
				jpeg_finish_compress(&cinfo);
				fclose(outfile);
				jpeg_destroy_compress(&cinfo);
				return true;
			}

			bool CPicture::SavePng(const String &filename, const Image &bmp)
			{
				FILE *fp;
				fp = fopen(StringToAnsi(filename).c_str(), "wb");
				if (fp == nullptr)
					return false;
				png_structp png_ptr{ png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr) };
				if (png_ptr == nullptr)
				{
					fclose(fp);
					return false;
				}
				png_infop info_ptr{ png_create_info_struct(png_ptr) };
				if (info_ptr == nullptr)
				{
					fclose(fp);
					png_destroy_write_struct(&png_ptr, nullptr);
					return false;
				}
				if (setjmp(png_jmpbuf(png_ptr)))
				{
					fclose(fp);
					png_destroy_write_struct(&png_ptr, &info_ptr);
					return false;
				}
				png_init_io(png_ptr, fp);
				png_set_IHDR(png_ptr, info_ptr, bmp.Width, bmp.Height, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_ADAM7, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
				png_write_info(png_ptr, info_ptr);
				png_set_interlace_handling(png_ptr);
				png_byte *image{ new png_byte[bmp.Width * bmp.Height * 4] };
				for (int y = 0; y < bmp.Height; y++)
					for (int x = 0; x < bmp.Width; x++)
					{
						Color c{ bmp[x][y] };
						image[y * bmp.Width * 4 + x * 4 + 0] = c.R;
						image[y * bmp.Width * 4 + x * 4 + 1] = c.G;
						image[y * bmp.Width * 4 + x * 4 + 2] = c.B;
						image[y * bmp.Width * 4 + x * 4 + 3] = c.A;
					}
				png_bytep *row_pointers{ new png_bytep[bmp.Height] };
				for (int y = 0; y < bmp.Height; y++)
					row_pointers[y] = image + y * bmp.Width * 4;
				png_write_image(png_ptr, row_pointers);
				png_write_end(png_ptr, info_ptr);
				delete[] image;
				delete[] row_pointers;
				png_destroy_write_struct(&png_ptr, &info_ptr);
				fclose(fp);
				return true;
			}
		#pragma endregion
		}
	}
}
#endif
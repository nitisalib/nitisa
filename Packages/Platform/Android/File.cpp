// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef __ANDROID__
#include <android/asset_manager.h>

namespace nitisa
{
	namespace platform
	{
		namespace android
		{
		#pragma region Constructor & destructor
			CFile::CFile(FILE *file, const String &filename) :
				m_pFile{ file },
				m_pAsset{ nullptr }
			{
				m_sFilename = filename;
			}

			CFile::CFile(AAsset *asset, const String &filename) :
				m_pFile{ nullptr },
				m_pAsset{ asset }
			{
				m_sFilename = filename;
			}

			void CFile::Release()
			{
				if (m_pFile)
					fclose(m_pFile);
				if (m_pAsset)
					AAsset_close(m_pAsset);
				delete this;
			}
		#pragma endregion

		#pragma region Getters
			long long CFile::getSize()
			{
				if (m_pFile)
				{
					long current{ ftell(m_pFile) };
					fseek(m_pFile, 0, SEEK_END);
					long long result{ ftell(m_pFile) };
					if (result != current)
						fseek(m_pFile, current, SEEK_SET);
					return result;
				}
				return AAsset_getLength64(m_pAsset);
			}

			long long CFile::getPointer()
			{
				if (m_pFile)
					return ftell(m_pFile);
				return AAsset_seek64(m_pAsset, 0, SEEK_END);
			}
		#pragma endregion

		#pragma region Setters
			bool CFile::setPointer(const long long value, const SeekFrom seek_from)
			{
				if (m_pFile)
					return fseek(m_pFile, value, seek_from == SeekFrom::Current ? SEEK_CUR : (seek_from == SeekFrom::End ? SEEK_END : SEEK_SET)) == 0;
				return AAsset_seek64(m_pAsset, value, seek_from == SeekFrom::Current ? SEEK_CUR : (seek_from == SeekFrom::End ? SEEK_END : SEEK_SET)) != -1;
			}
		#pragma endregion

		#pragma region Methods
			bool CFile::Read(const unsigned int size, unsigned char *buffer, unsigned long &read)
			{
				if (size <= 0 || !buffer)
					return false;
				if (m_pFile)
				{
					read = fread((void*)buffer, 1, size, m_pFile);
					return true;
				}
				read = AAsset_read(m_pAsset, (void*)buffer, size);
				return true;
			}

			bool CFile::Write(const unsigned int size, unsigned char *buffer, unsigned long &written)
			{
				if (m_pFile && size > 0 && buffer)
				{
					written = fwrite((void*)buffer, 1, size, m_pFile);
					return true;
				}
				return false;
			}
		#pragma endregion
		}
	}
}
#endif
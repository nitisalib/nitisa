// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

#if defined(__linux__) && !defined(__ANDROID__)
namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
		#pragma region Constructor & destructor
			CFile::CFile(PlatformHandle handle, const String &filename) :
				m_hHandle{ handle }
			{
				m_sFilename = filename;
			}

			void CFile::Release()
			{
				if (*reinterpret_cast<FILE**>(&m_hHandle))
					fclose(*reinterpret_cast<FILE**>(&m_hHandle));
				delete this;
			}
		#pragma endregion

		#pragma region Getters
			long long CFile::getSize()
			{
				if (*reinterpret_cast<FILE**>(&m_hHandle))
				{
					long current{ ftell(*reinterpret_cast<FILE**>(&m_hHandle)) };
					fseek(*reinterpret_cast<FILE**>(&m_hHandle), 0, SEEK_END);
					long long result{ ftell(*reinterpret_cast<FILE**>(&m_hHandle)) };
					if (result != current)
						fseek(*reinterpret_cast<FILE**>(&m_hHandle), current, SEEK_SET);
					return result;
				}
				return 0;
			}

			long long CFile::getPointer()
			{
				if (*reinterpret_cast<FILE**>(&m_hHandle))
					return ftell(*reinterpret_cast<FILE**>(&m_hHandle));
				return 0;
			}
		#pragma endregion

		#pragma region Setters
			bool CFile::setPointer(const long long value, const SeekFrom seek_from)
			{
				if (*reinterpret_cast<FILE**>(&m_hHandle))
					return fseek(*reinterpret_cast<FILE**>(&m_hHandle), (long)value, seek_from == SeekFrom::Current ? SEEK_CUR : (seek_from == SeekFrom::End ? SEEK_END : SEEK_SET)) == 0;
				return false;
			}
		#pragma endregion

		#pragma region Methods
			bool CFile::Read(const unsigned int size, unsigned char *buffer, unsigned long &read)
			{
				if (size <= 0 || !buffer)
					return false;
				if (*reinterpret_cast<FILE**>(&m_hHandle))
				{
					read = fread((void*)buffer, 1, size, *reinterpret_cast<FILE**>(&m_hHandle));
					return true;
				}
				read = 0;
				return false;
			}

			bool CFile::Write(const unsigned int size, unsigned char *buffer, unsigned long &written)
			{
				if (*reinterpret_cast<FILE**>(&m_hHandle) && size > 0 && buffer)
				{
					written = fwrite((void*)buffer, 1, size, *reinterpret_cast<FILE**>(&m_hHandle));
					return true;
				}
				return false;
			}
		#pragma endregion
		}
	}
}
#endif
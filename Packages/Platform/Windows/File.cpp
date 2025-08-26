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

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
		#pragma region Constructor & destructor
			CFile::CFile(void *handle, const String &filename):
				m_pHandle{ handle }
			{
				m_sFilename = filename;
			}

			void CFile::Release()
			{
				CloseHandle((HANDLE)m_pHandle);
				delete this;
			}
		#pragma endregion

		#pragma region Getters
			long long CFile::getSize()
			{
				LARGE_INTEGER i;
				if (GetFileSizeEx((HANDLE)m_pHandle, &i))
					return i.QuadPart;
				return 0;
			}

			long long CFile::getPointer()
			{
				LARGE_INTEGER i, d;
				d.QuadPart = 0;
				if (SetFilePointerEx((HANDLE)m_pHandle, d, &i, FILE_CURRENT))
					return i.QuadPart;
				return 0;
			}
		#pragma endregion

		#pragma region Setters
			bool CFile::setPointer(const long long value, const SeekFrom seek_from)
			{
				LARGE_INTEGER d;
				d.QuadPart = value;
				if (SetFilePointerEx((HANDLE)m_pHandle, d, nullptr, seek_from == SeekFrom::Current ? FILE_CURRENT : (seek_from == SeekFrom::End ? FILE_END : FILE_BEGIN)))
					return true;
				return false;
			}
		#pragma endregion

		#pragma region Methods
			bool CFile::Read(const unsigned int size, unsigned char *buffer, unsigned long &read)
			{
				if (size > 0 && buffer && ReadFile((HANDLE)m_pHandle, (LPVOID)buffer, size, &read, nullptr))
					return true;
				return false;
			}

			bool CFile::Write(const unsigned int size, unsigned char *buffer, unsigned long &written)
			{
				if (size > 0 && buffer && WriteFile((HANDLE)m_pHandle, (LPVOID)buffer, size, &written, nullptr))
					return true;
				return false;
			}
		#pragma endregion
		}
	}
}
#endif
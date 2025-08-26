// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#include <wininet.h>

#pragma comment(lib, "wininet.lib")

namespace nitisa
{
	namespace fb
	{
	#ifdef VS_INTEGRATION
		#ifdef _WIN64
			#ifdef _DEBUG
				const String UserAgent{ L"Nitisa Form Builder Extension(Debug, x64) " + FB_VERSION };
			#else
				const String UserAgent{ L"Nitisa Form Builder Extension(Release, x64) " + FB_VERSION };
			#endif
		#else
			#ifdef _DEBUG
				const String UserAgent{ L"Nitisa Form Builder Extension(Debug, x32) " + FB_VERSION };
			#else
				const String UserAgent{ L"Nitisa Form Builder Extension(Release, x32) " + FB_VERSION };
			#endif
		#endif
	#else
		#ifdef USE_DIALOGBOXES
			#ifdef _WIN64
				#ifdef _DEBUG
					const String UserAgent{ L"Nitisa Form Builder(Debug, x64) " + FB_VERSION };
				#else
					const String UserAgent{ L"Nitisa Form Builder(Release, x64) " + FB_VERSION };
				#endif
			#else
				#ifdef _DEBUG
					const String UserAgent{ L"Nitisa Form Builder(Debug, x32) " + FB_VERSION };
				#else
					const String UserAgent{ L"Nitisa Form Builder(Release, x32) " + FB_VERSION };
				#endif
			#endif
		#else
			#ifdef _WIN64
				#ifdef _DEBUG
					const String UserAgent{ L"Nitisa Form Builder(Debug, x64, RT) " + FB_VERSION };
				#else
					const String UserAgent{ L"Nitisa Form Builder(Release, x64, RT) " + FB_VERSION };
				#endif
			#else
				#ifdef _DEBUG
					const String UserAgent{ L"Nitisa Form Builder(Debug, x32, RT) " + FB_VERSION };
				#else
					const String UserAgent{ L"Nitisa Form Builder(Release, x32, RT) " + FB_VERSION };
				#endif
			#endif
		#endif
	#endif

		String Version{ L"" };
		std::mutex Mutex;

		void EntryPoint()
		{
			HINTERNET connection{ InternetOpen(UserAgent.c_str(), INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0) };
			if (!connection)
			{
				Version = L"0";
				return;
			}
			HINTERNET address{ InternetOpenUrl(connection, L"http://nitisa.com/api/version", nullptr, 0, INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_KEEP_CONNECTION, 0) };
			if (!address)
			{
				Version = L"0";
				InternetCloseHandle(connection);
				return;
			}
			{
				char data[16] = { 0 };
				DWORD number_of_bytes_read{ 0 };
				InternetReadFile(address, data, 16, &number_of_bytes_read);
				std::lock_guard<std::mutex> lock{ Mutex };
				Version += AnsiToString(data);
			}
			InternetCloseHandle(address);
			InternetCloseHandle(connection);
		}

		void UpdateChecker_Run()
		{
			std::thread thread{ EntryPoint };
			thread.detach();
		}

		bool UpdateChecker_IsInProgress()
		{
			std::lock_guard<std::mutex> lock{ Mutex };
			return Version.empty();
		}

		bool UpdateChecker_IsFailed()
		{
			std::lock_guard<std::mutex> lock{ Mutex };
			return Version == L"0";
		}

		String UpdateChecker_GetVersion()
		{
			std::lock_guard<std::mutex> lock{ Mutex };
			return Version;
		}
	}
}
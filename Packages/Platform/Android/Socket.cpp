// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef __ANDROID__
#include <sys/socket.h>

namespace nitisa
{
	namespace platform
	{
		namespace android
		{
		#pragma region Constructor & destructor
			CSocket::CSocket(PlatformHandle handle, const AnsiString &local_ip, const AnsiString &remote_ip, const int local_port, const int remote_port) :
				m_sLocalIp{ local_ip },
				m_sRemoteIp{ remote_ip },
				m_iLocalPort{ local_port },
				m_iRemotePort{ remote_port },
				m_hHandle{ handle }
			{
				
			}

			CSocket::~CSocket()
			{
				shutdown(*reinterpret_cast<int*>(&m_hHandle), SHUT_RDWR);
			}

			void CSocket::Release()
			{
				delete this;
			}
		#pragma endregion

		#pragma region Getters
			AnsiString CSocket::getLocalIp()
			{
				return m_sLocalIp;
			}

			AnsiString CSocket::getRemoteIp()
			{
				return m_sRemoteIp;
			}

			int CSocket::getLocalPort()
			{
				return m_iLocalPort;
			}

			int CSocket::getRemotePort()
			{
				return m_iRemotePort;
			}
		#pragma endregion
		}
	}
}
#endif
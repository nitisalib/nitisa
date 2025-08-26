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
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
		#pragma region Constructor & destructor
			CNetwork::CNetwork()
			{
				WSADATA data;
				m_bInitialized = WSAStartup(MAKEWORD(2, 2), &data) == 0;
			}

			CNetwork::~CNetwork()
			{
				if (m_bInitialized)
					WSACleanup();
			}
		#pragma endregion

		#pragma region Methods
			IClientSocket *CNetwork::TCPConnect(const String &server, const int port, const float timeout)
			{
				// Check wsa is initialized & server name is specified
				if (!m_bInitialized || server.empty() || port <= 0 || ntl::IsLessOrEqual<float>(timeout, 0))
					return nullptr;
				// Get address in required format
				ADDRINFOT hints, *addresses;
				wchar_t port_name[11];
				memset(&hints, 0, sizeof(addrinfo));
				hints.ai_family = AF_UNSPEC;
				hints.ai_socktype = SOCK_STREAM;
				hints.ai_protocol = IPPROTO_TCP;
				_itow_s(port, port_name, 11, 10);
				if (GetAddrInfo(server.c_str(), port_name, &hints, &addresses) != 0)
					return nullptr;
				// Create socket & connect
				SOCKET s{ socket(addresses->ai_family, addresses->ai_socktype, addresses->ai_protocol) };
				if (s == INVALID_SOCKET)
				{
					FreeAddrInfo(addresses);
					return nullptr;
				}
				// Set nonblocking mode
				unsigned long nonblocking{ 1 };
				if (ioctlsocket(s, FIONBIO, &nonblocking) != 0)
				{
					FreeAddrInfo(addresses);
					closesocket(s);
					return nullptr;
				}
				fd_set check_set;
				int res{ connect(s, addresses->ai_addr, (int)addresses->ai_addrlen) };
				if (res == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK)
				{
					timeval time;
					time.tv_sec = (long)timeout;
					time.tv_usec = long((timeout - time.tv_sec) * 1000);
					FD_ZERO(&check_set);
					FD_SET(s, &check_set);
					res = select(0, nullptr, &check_set, nullptr, &time);
					if (res <= 0)
					{
						FreeAddrInfo(addresses);
						closesocket(s);
						return nullptr;
					}
				}
				FreeAddrInfo(addresses);

				sockaddr_in addr;
				AnsiString local_ip, remote_ip;
				int local_port{ 0 }, remote_port{ 0 }, size = sizeof(sockaddr_in);
				char buffer[16] = { 0 };
				if (getsockname(s, (sockaddr*)(&addr), &size) == 0 && InetNtopA(AF_INET, &addr.sin_addr, buffer, 16))
				{
					local_ip = buffer;
					local_port = addr.sin_port;
				}
				if (getpeername(s, (sockaddr*)(&addr), &size) == 0 && InetNtopA(AF_INET, &addr.sin_addr, buffer, 16))
				{
					remote_ip = buffer;
					remote_port = addr.sin_port;
				}
				return new CClientSocket((void*)s, local_ip, remote_ip, local_port, remote_port);
			}

			IServerSocket *CNetwork::TCPListen(const int port)
			{
				// Check if initialized
				if (!m_bInitialized || port <= 0)
					return nullptr;
				// Get address in required format
				ADDRINFOT *addresses, hints;
				wchar_t port_name[11];
				memset(&hints, 0, sizeof(addrinfo));
				hints.ai_family = AF_INET;
				hints.ai_socktype = SOCK_STREAM;
				hints.ai_protocol = IPPROTO_TCP;
				hints.ai_flags = AI_PASSIVE;
				_itow_s(port, port_name, 11, 10);
				if (GetAddrInfo(0, port_name, &hints, &addresses) != 0)
					return nullptr;
				// Create socket
				SOCKET s{ socket(addresses->ai_family, addresses->ai_socktype, addresses->ai_protocol) };
				if (s == INVALID_SOCKET)
				{
					FreeAddrInfo(addresses);
					return nullptr;
				}
				// Bind
				if (::bind(s, addresses->ai_addr, (int)addresses->ai_addrlen) == SOCKET_ERROR)
				{
					FreeAddrInfo(addresses);
					closesocket(s);
					return nullptr;
				}
				FreeAddrInfo(addresses);
				// Set nonblocking mode
				unsigned long nonblocking = 1;
				if (ioctlsocket(s, FIONBIO, &nonblocking) != 0)
				{
					closesocket(s);
					return nullptr;
				}
				sockaddr_in addr;
				AnsiString local_ip, remote_ip;
				int local_port{ 0 }, remote_port{ 0 }, size = sizeof(sockaddr_in);
				char buffer[16] = { 0 };
				if (getsockname(s, (sockaddr*)(&addr), &size) == 0 && InetNtopA(AF_INET, &addr.sin_addr, buffer, 16))
				{
					local_ip = buffer;
					local_port = addr.sin_port;
				}
				if (getpeername(s, (sockaddr*)(&addr), &size) == 0 && InetNtopA(AF_INET, &addr.sin_addr, buffer, 16))
				{
					remote_ip = buffer;
					remote_port = addr.sin_port;
				}
				return new CServerSocket((void*)s, local_ip, remote_ip, local_port, remote_port);
			}
		#pragma endregion
		}
	}
}
#endif
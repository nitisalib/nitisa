// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#if defined(__linux__) && !defined(__ANDROID__)
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <string.h>

namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
		#pragma region Methods
			IClientSocket *CNetwork::TCPConnect(const String &server, const int port, const float timeout)
			{
				// Check wsa is initialized & server name is specified
				if (server.empty() || port <= 0 || ntl::IsLessOrEqual<float>(timeout, 0))
					return nullptr;
				// Get address in required format
				addrinfo hints, *addresses;
				memset(&hints, 0, sizeof(addrinfo));
				hints.ai_family = AF_UNSPEC;
				hints.ai_socktype = SOCK_STREAM;
				hints.ai_protocol = IPPROTO_TCP;
				if (getaddrinfo(StringToAnsi(server).c_str(), ToAnsi(port).c_str(), &hints, &addresses) != 0)
					return nullptr;
				// Create socket & connect
				int s{ socket(addresses->ai_family, addresses->ai_socktype, addresses->ai_protocol) };
				if (s < 0)
				{
					freeaddrinfo(addresses);
					return nullptr;
				}
				// Set nonblocking mode
				if (fcntl(s, F_SETFL, O_NONBLOCK) < 0)
				{
					freeaddrinfo(addresses);
					shutdown(s, SHUT_RDWR);
					return nullptr;
				}
				fd_set check_set;
				int res{ connect(s, addresses->ai_addr, (int)addresses->ai_addrlen) };
				if (res < 0 && errno == EWOULDBLOCK)
				{
					timeval time;
					time.tv_sec = (long)timeout;
					time.tv_usec = long((timeout - (float)time.tv_sec) * 1000);
					FD_ZERO(&check_set);
					FD_SET(s, &check_set);
					res = select(0, nullptr, &check_set, nullptr, &time);
					if (res <= 0)
					{
						shutdown(s, SHUT_RDWR);
						freeaddrinfo(addresses);
						return nullptr;
					}
				}
				freeaddrinfo(addresses);

				sockaddr_in addr;
				AnsiString local_ip, remote_ip;
				int local_port{ 0 }, remote_port{ 0 };
				socklen_t size{ sizeof(sockaddr_in) };
				char buffer[16] = { 0 };
				if (getsockname(s, (sockaddr*)(&addr), &size) == 0 && inet_ntop(AF_INET, &addr.sin_addr, buffer, 16))
				{
					local_ip = buffer;
					local_port = addr.sin_port;
				}
				if (getpeername(s, (sockaddr*)(&addr), &size) == 0 && inet_ntop(AF_INET, &addr.sin_addr, buffer, 16))
				{
					remote_ip = buffer;
					remote_port = addr.sin_port;
				}
				return new CClientSocket(*reinterpret_cast<PlatformHandle*>(&s), local_ip, remote_ip, local_port, remote_port);
			}

			IServerSocket *CNetwork::TCPListen(const int port)
			{
				// Check if initialized
				if (port <= 0)
					return nullptr;
				// Get address in required format
				addrinfo *addresses, hints;
				memset(&hints, 0, sizeof(addrinfo));
				hints.ai_family = AF_INET;
				hints.ai_socktype = SOCK_STREAM;
				hints.ai_protocol = IPPROTO_TCP;
				hints.ai_flags = AI_PASSIVE;
				if (getaddrinfo(0, ToAnsi(port).c_str(), &hints, &addresses) != 0)
					return nullptr;
				// Create socket
				int s{ socket(addresses->ai_family, addresses->ai_socktype, addresses->ai_protocol) };
				if (s < 0)
				{
					freeaddrinfo(addresses);
					return nullptr;
				}
				// Bind
				if (::bind(s, addresses->ai_addr, (int)addresses->ai_addrlen) < 0)
				{
					freeaddrinfo(addresses);
					shutdown(s, SHUT_RDWR);
					return nullptr;
				}
				freeaddrinfo(addresses);
				// Set nonblocking mode
				if (fcntl(s, F_SETFL, O_NONBLOCK) < 0)
				{
					freeaddrinfo(addresses);
					shutdown(s, SHUT_RDWR);
					return nullptr;
				}
				sockaddr_in addr;
				AnsiString local_ip, remote_ip;
				int local_port{ 0 }, remote_port{ 0 };
				socklen_t size{ sizeof(sockaddr_in) };
				char buffer[16] = { 0 };
				if (getsockname(s, (sockaddr*)(&addr), &size) == 0 && inet_ntop(AF_INET, &addr.sin_addr, buffer, 16))
				{
					local_ip = buffer;
					local_port = addr.sin_port;
				}
				if (getpeername(s, (sockaddr*)(&addr), &size) == 0 && inet_ntop(AF_INET, &addr.sin_addr, buffer, 16))
				{
					remote_ip = buffer;
					remote_port = addr.sin_port;
				}
				return new CServerSocket(*reinterpret_cast<PlatformHandle*>(&s), local_ip, remote_ip, local_port, remote_port);
			}
		#pragma endregion
		}
	}
}
#endif
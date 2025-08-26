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
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

namespace nitisa
{
	namespace platform
	{
		namespace android
		{
		#pragma region Constructor & destructor
			CServerSocket::CServerSocket(PlatformHandle handle, const AnsiString &local_ip, const AnsiString &remote_ip, const int local_port, const int remote_port) :
				CSocket(handle, local_ip, remote_ip, local_port, remote_port),
				m_pListener{ nullptr }
			{

			}
		#pragma endregion

		#pragma region Getters
			IServerSocketListener *CServerSocket::getListener()
			{
				return m_pListener;
			}
		#pragma endregion

		#pragma region Setters
			void CServerSocket::setListener(IServerSocketListener *value)
			{
				m_pListener = value;
			}
		#pragma endregion

		#pragma region Helpers
			ISocket::ErrorType CServerSocket::DecodeError(const int error)
			{
				switch (error)
				{
				case EINTR:				return ErrorType::InterruptedCall;
				case EBADF:				return ErrorType::InvalidFileHandle;
				case EACCES:			return ErrorType::PermissionDenied;
				case EFAULT:			return ErrorType::BadAddress;
				case EINVAL:			return ErrorType::InvalidArgument;
				case EMFILE:			return ErrorType::TooManyOpenedFiles;
				case EINPROGRESS:		return ErrorType::OperationInProgress;
				case EALREADY:			return ErrorType::OperationInProgress;
				case ENOTSOCK:			return ErrorType::OperationOnNonSocket;
				case EDESTADDRREQ:		return ErrorType::DestinationAddressRequird;
				case EMSGSIZE:			return ErrorType::MessageTooLong;
				case EPROTOTYPE:		return ErrorType::WrongProtocolType;
				case ENOPROTOOPT:		return ErrorType::BadProtocolOption;
				case EPROTONOSUPPORT:	return ErrorType::ProtocolNotSupported;
				case ESOCKTNOSUPPORT:	return ErrorType::SocketTypeNotSupported;
				case EOPNOTSUPP:		return ErrorType::OperationNotSupported;
				case EPFNOSUPPORT:		return ErrorType::ProtocolFamilyNotSupported;
				case EAFNOSUPPORT:		return ErrorType::AddressfamilyNotSupported;
				case EADDRINUSE:		return ErrorType::AddressInUse;
				case EADDRNOTAVAIL:		return ErrorType::CannotAssignAddress;
				case ENETDOWN:			return ErrorType::NetworkDown;
				case ENETUNREACH:		return ErrorType::NetworkUnreachable;
				case ENETRESET:			return ErrorType::NetwordDropConnection;
				case ECONNABORTED:		return ErrorType::SoftwareConnectionAbort;
				case ECONNRESET:		return ErrorType::ConnectionResetByPeer;
				case ENOBUFS:			return ErrorType::NoBufferSpaceAvailable;
				case EISCONN:			return ErrorType::SocketAlreadyConnected;
				case ENOTCONN:			return ErrorType::SocketNotConnected;
				case ESHUTDOWN:			return ErrorType::CannotSendAfterShutdown;
				case ETOOMANYREFS:		return ErrorType::TooManyReferences;
				case ETIMEDOUT:			return ErrorType::ConnectionTimeout;
				case ECONNREFUSED:		return ErrorType::ConnectionRefused;
				case ELOOP:				return ErrorType::CannotTranslateName;
				case ENAMETOOLONG:		return ErrorType::NameTooLong;
				case EHOSTDOWN:			return ErrorType::HostDown;
				case EHOSTUNREACH:		return ErrorType::NoRouteToHost;
				case ENOTEMPTY:			return ErrorType::DirectoryNotEmpty;
				case EUSERS:			return ErrorType::UserQuotaExceeded;
				case EDQUOT:			return ErrorType::DiskQuotaExceeded;
				case ESTALE:			return ErrorType::StaleFileHandleReference;
				case EREMOTE:			return ErrorType::ItemIsRemote;
				}
				return ErrorType::Unknown;
			}
		#pragma endregion

		#pragma region Methods
			bool CServerSocket::Listen()
			{
				m_bTerminated = false;
				while (!m_bTerminated)
				{
					if (listen(*reinterpret_cast<int*>(&m_hHandle), SOMAXCONN) < 0)
					{
						if (m_pListener)
							m_pListener->NotifyOnError(this, DecodeError(errno));
						return false;
					}
					int client_socket;
					sockaddr addr;
					client_socket = accept(*reinterpret_cast<int*>(&m_hHandle), &addr, 0);
					if (client_socket <= 0)
					{
						if (errno == EWOULDBLOCK)
						{
							usleep(50000);
							continue;
						}
						if (m_pListener)
							m_pListener->NotifyOnError(this, DecodeError(errno));
						return false;
					}
					// Set nonblocking mode
					if (fcntl(client_socket, F_SETFL, O_NONBLOCK) < 0)
					{
						shutdown(client_socket, SHUT_RDWR);
						continue;
					}
					// Create client thread
					bool accept{ false };
					if (m_pListener)
						m_pListener->NotifyOnConnect(this, accept);
					if (accept)
					{
						sockaddr_in addr;
						AnsiString local_ip, remote_ip;
						int local_port{ 0 }, remote_port{ 0 };
						socklen_t size{ sizeof(sockaddr_in) };
						char buffer[16] = { 0 };
						if (getsockname(client_socket, (sockaddr*)&addr, &size) == 0 && inet_ntop(AF_INET, &addr.sin_addr, buffer, 16))
						{
							local_ip = buffer;
							local_port = addr.sin_port;
						}
						if (getpeername(client_socket, (sockaddr*)(&addr), &size) == 0 && inet_ntop(AF_INET, &addr.sin_addr, buffer, 16))
						{
							remote_ip = buffer;
							remote_port = addr.sin_port;
						}
						// If callback exists, call it to check if connection can be accepted
						accept = true;
						m_pListener->NotifyOnConnect(this, remote_ip, remote_port, accept);
						if (accept)
							m_pListener->NotifyOnConnect(this, new CClientSocket(*reinterpret_cast<PlatformHandle*>(&client_socket), local_ip, remote_ip, local_port, remote_port));
						else
							shutdown(client_socket, SHUT_RDWR);
					}
					else
						shutdown(client_socket, SHUT_RDWR);
				}
				return true;
			}

			void CServerSocket::Terminate()
			{
				m_bTerminated = true;
			}
		#pragma endregion
		}
	}
}
#endif
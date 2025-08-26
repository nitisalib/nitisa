// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <WS2tcpip.h>

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
		#pragma region Constructor & destructor
			CServerSocket::CServerSocket(void *socket, const AnsiString &local_ip, const AnsiString &remote_ip, const int local_port, const int remote_port) :
				CSocket(socket, local_ip, remote_ip, local_port, remote_port),
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
				case WSA_INVALID_HANDLE:			return ISocket::ErrorType::InvalidHandle;
				case WSA_NOT_ENOUGH_MEMORY:			return ISocket::ErrorType::NotEnoughMemory;
				case WSA_INVALID_PARAMETER:			return ISocket::ErrorType::InvalidParameter;
				case WSA_OPERATION_ABORTED:			return ISocket::ErrorType::OperationAborted;
				case WSA_IO_INCOMPLETE:				return ISocket::ErrorType::IOIncomplete;
				case WSA_IO_PENDING:				return ISocket::ErrorType::IOPending;
				case WSAEINTR:						return ISocket::ErrorType::InterruptedCall;
				case WSAEBADF:						return ISocket::ErrorType::InvalidFileHandle;
				case WSAEACCES:						return ISocket::ErrorType::PermissionDenied;
				case WSAEFAULT:						return ISocket::ErrorType::BadAddress;
				case WSAEINVAL:						return ISocket::ErrorType::InvalidArgument;
				case WSAEMFILE:						return ISocket::ErrorType::TooManyOpenedFiles;
				case WSAEINPROGRESS:				return ISocket::ErrorType::OperationInProgress;
				case WSAEALREADY:					return ISocket::ErrorType::OperationInProgress;
				case WSAENOTSOCK:					return ISocket::ErrorType::OperationOnNonSocket;
				case WSAEDESTADDRREQ:				return ISocket::ErrorType::DestinationAddressRequird;
				case WSAEMSGSIZE:					return ISocket::ErrorType::MessageTooLong;
				case WSAEPROTOTYPE:					return ISocket::ErrorType::WrongProtocolType;
				case WSAENOPROTOOPT:				return ISocket::ErrorType::BadProtocolOption;
				case WSAEPROTONOSUPPORT:			return ISocket::ErrorType::ProtocolNotSupported;
				case WSAESOCKTNOSUPPORT:			return ISocket::ErrorType::SocketTypeNotSupported;
				case WSAEOPNOTSUPP:					return ISocket::ErrorType::OperationNotSupported;
				case WSAEPFNOSUPPORT:				return ISocket::ErrorType::ProtocolFamilyNotSupported;
				case WSAEAFNOSUPPORT:				return ISocket::ErrorType::AddressfamilyNotSupported;
				case WSAEADDRINUSE:					return ISocket::ErrorType::AddressInUse;
				case WSAEADDRNOTAVAIL:				return ISocket::ErrorType::CannotAssignAddress;
				case WSAENETDOWN:					return ISocket::ErrorType::NetworkDown;
				case WSAENETUNREACH:				return ISocket::ErrorType::NetworkUnreachable;
				case WSAENETRESET:					return ISocket::ErrorType::NetwordDropConnection;
				case WSAECONNABORTED:				return ISocket::ErrorType::SoftwareConnectionAbort;
				case WSAECONNRESET:					return ISocket::ErrorType::ConnectionResetByPeer;
				case WSAENOBUFS:					return ISocket::ErrorType::NoBufferSpaceAvailable;
				case WSAEISCONN:					return ISocket::ErrorType::SocketAlreadyConnected;
				case WSAENOTCONN:					return ISocket::ErrorType::SocketNotConnected;
				case WSAESHUTDOWN:					return ISocket::ErrorType::CannotSendAfterShutdown;
				case WSAETOOMANYREFS:				return ISocket::ErrorType::TooManyReferences;
				case WSAETIMEDOUT:					return ISocket::ErrorType::ConnectionTimeout;
				case WSAECONNREFUSED:				return ISocket::ErrorType::ConnectionRefused;
				case WSAELOOP:						return ISocket::ErrorType::CannotTranslateName;
				case WSAENAMETOOLONG:				return ISocket::ErrorType::NameTooLong;
				case WSAEHOSTDOWN:					return ISocket::ErrorType::HostDown;
				case WSAEHOSTUNREACH:				return ISocket::ErrorType::NoRouteToHost;
				case WSAENOTEMPTY:					return ISocket::ErrorType::DirectoryNotEmpty;
				case WSAEPROCLIM:					return ISocket::ErrorType::TooManyProcesses;
				case WSAEUSERS:						return ISocket::ErrorType::UserQuotaExceeded;
				case WSAEDQUOT:						return ISocket::ErrorType::DiskQuotaExceeded;
				case WSAESTALE:						return ISocket::ErrorType::StaleFileHandleReference;
				case WSAEREMOTE:					return ISocket::ErrorType::ItemIsRemote;
				case WSASYSNOTREADY:				return ISocket::ErrorType::NetworkSubsystemUnavailable;
				case WSAVERNOTSUPPORTED:			return ISocket::ErrorType::LibraryVersionOutOfRange;
				case WSANOTINITIALISED:				return ISocket::ErrorType::NoStartup;
				case WSAEDISCON:					return ISocket::ErrorType::GracefulShutdownInProgress;
				case WSAENOMORE:					return ISocket::ErrorType::NoMoreResults;
				case WSAECANCELLED:					return ISocket::ErrorType::Callcancelled;
				case WSAEINVALIDPROCTABLE:			return ISocket::ErrorType::ProcedureCallTableInvalid;
				case WSAEINVALIDPROVIDER:			return ISocket::ErrorType::ServiceProviderInvalid;
				case WSAEPROVIDERFAILEDINIT:		return ISocket::ErrorType::ServiceProviderFailedToInitialize;
				case WSASYSCALLFAILURE:				return ISocket::ErrorType::SystemCallFailed;
				case WSASERVICE_NOT_FOUND:			return ISocket::ErrorType::ServiceNotFound;
				case WSATYPE_NOT_FOUND:				return ISocket::ErrorType::ClassTypeNotFound;
				case WSA_E_NO_MORE:					return ISocket::ErrorType::NoMoreResults;
				case WSA_E_CANCELLED:				return ISocket::ErrorType::CallCancelled;
				case WSAEREFUSED:					return ISocket::ErrorType::DatabaseQueryRefused;
				case WSAHOST_NOT_FOUND:				return ISocket::ErrorType::HostNotFound;
				case WSATRY_AGAIN:					return ISocket::ErrorType::NonAuthoritativeHostNotFound;
				case WSANO_RECOVERY:				return ISocket::ErrorType::NonRecoverableError;
				case WSANO_DATA:					return ISocket::ErrorType::NoDataRecord;
				case WSA_QOS_RECEIVERS:				return ISocket::ErrorType::QoSReceivers;
				case WSA_QOS_SENDERS:				return ISocket::ErrorType::QoSSenders;
				case WSA_QOS_NO_SENDERS:			return ISocket::ErrorType::NoQoSSenders;
				case WSA_QOS_NO_RECEIVERS:			return ISocket::ErrorType::NoQoSReceivers;
				case WSA_QOS_REQUEST_CONFIRMED:		return ISocket::ErrorType::QoSRequestConfirmed;
				case WSA_QOS_ADMISSION_FAILURE:		return ISocket::ErrorType::QoSAdmissionError;
				case WSA_QOS_POLICY_FAILURE:		return ISocket::ErrorType::QoSPolicyFailed;
				case WSA_QOS_BAD_STYLE:				return ISocket::ErrorType::QoSBadStyle;
				case WSA_QOS_BAD_OBJECT:			return ISocket::ErrorType::QoSBadObject;
				case WSA_QOS_TRAFFIC_CTRL_ERROR:	return ISocket::ErrorType::QoSTrafficControlError;
				case WSA_QOS_GENERIC_ERROR:			return ISocket::ErrorType::QoSGenericError;
				case WSA_QOS_ESERVICETYPE:			return ISocket::ErrorType::QoSServiceTypeError;
				case WSA_QOS_EFLOWSPEC:				return ISocket::ErrorType::QoSFlowspecError;
				case WSA_QOS_EPROVSPECBUF:			return ISocket::ErrorType::InvalidQoSProviderBuffer;
				case WSA_QOS_EFILTERSTYLE:			return ISocket::ErrorType::InvalidQoSFilterStyle;
				case WSA_QOS_EFILTERTYPE:			return ISocket::ErrorType::InvalidQoSFilterType;
				case WSA_QOS_EFILTERCOUNT:			return ISocket::ErrorType::IncorrectQoSFilterCount;
				case WSA_QOS_EOBJLENGTH:			return ISocket::ErrorType::InvalidQoSObjectLength;
				case WSA_QOS_EFLOWCOUNT:			return ISocket::ErrorType::InvalidQoSFlowCount;
				case WSA_QOS_EUNKOWNPSOBJ:			return ISocket::ErrorType::UnrecognizedQoSObject;
				case WSA_QOS_EPOLICYOBJ:			return ISocket::ErrorType::InvalidQoSPolicyObject;
				case WSA_QOS_EFLOWDESC:				return ISocket::ErrorType::InvalidQoSFlowDescriptor;
				case WSA_QOS_EPSFLOWSPEC:			return ISocket::ErrorType::InvalidQoSProviderFlowSpec;
				case WSA_QOS_EPSFILTERSPEC:			return ISocket::ErrorType::InvalidQoSProviderFilterSpec;
				case WSA_QOS_ESDMODEOBJ:			return ISocket::ErrorType::InvalidQoSShapeDiscardModeObject;
				case WSA_QOS_ESHAPERATEOBJ:			return ISocket::ErrorType::InvalidQoSShapingRateObject;
				case WSA_QOS_RESERVED_PETYPE:		return ISocket::ErrorType::ReservedPolicyQoSElementType;
				}
				return ISocket::ErrorType::Unknown;
			}
		#pragma endregion

		#pragma region Methods
			bool CServerSocket::Listen()
			{
				m_bTerminated = false;
				while (!m_bTerminated)
				{
					if (listen((SOCKET)m_pSocket, SOMAXCONN) == SOCKET_ERROR)
					{
						if (m_pListener)
							m_pListener->NotifyOnError(this, DecodeError(WSAGetLastError()));
						return false;
					}
					SOCKET client_socket;
					sockaddr addr;
					client_socket = accept((SOCKET)m_pSocket, &addr, 0);
					if (client_socket == INVALID_SOCKET)
					{
						int error = WSAGetLastError();
						if (error == WSAEWOULDBLOCK)
						{
							Sleep(10);
							continue;
						}
						if (m_pListener)
							m_pListener->NotifyOnError(this, DecodeError(WSAGetLastError()));
						return false;
					}
					// Set nonblocking mode
					unsigned long nonblocking = 1;
					if (ioctlsocket(client_socket, FIONBIO, &nonblocking) != 0)
					{
						closesocket(client_socket);
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
						int local_port{ 0 }, remote_port{ 0 }, size = sizeof(sockaddr_in);
						char buffer[16] = { 0 };
						if (getsockname(client_socket, (sockaddr*)(&addr), &size) == 0 && InetNtopA(AF_INET, &addr.sin_addr, buffer, 16))
						{
							local_ip = buffer;
							local_port = addr.sin_port;
						}
						if (getpeername(client_socket, (sockaddr*)(&addr), &size) == 0 && InetNtopA(AF_INET, &addr.sin_addr, buffer, 16))
						{
							remote_ip = buffer;
							remote_port = addr.sin_port;
						}
						// If callback exists, call it to check if connection can be accepted
						m_pListener->NotifyOnConnect(this, remote_ip, remote_port, accept);
						if (accept)
							m_pListener->NotifyOnConnect(this, new CClientSocket((void*)client_socket, local_ip, remote_ip, local_port, remote_port));
						else
							closesocket(client_socket);
					}
					else
						closesocket(client_socket);
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
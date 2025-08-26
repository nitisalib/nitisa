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
#include <WinSock2.h>

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
		#pragma region Constructor & destructor
			CClientSocket::CClientSocket(void *socket, const AnsiString &local_ip, const AnsiString &remote_ip, const int local_port, const int remote_port) :
				CSocket(socket, local_ip, remote_ip, local_port, remote_port),
				m_fTimeout{ 5 },
				m_bBuffer{ false }
			{
				m_sLastAction = std::chrono::steady_clock::now();
			}
		#pragma endregion

		#pragma region Getters
			float CClientSocket::getTimeout()
			{
				return m_fTimeout;
			}

			int CClientSocket::getAvailableByteCount()
			{
				u_long available;
				if (ioctlsocket((SOCKET)m_pSocket, FIONREAD, &available) != 0)
					return 0;
				return (int)available;
			}
		#pragma endregion

		#pragma region Setters
			bool CClientSocket::setTimeout(const float value)
			{
				if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fTimeout))
				{
					m_fTimeout = value;
					return true;
				}
				return false;
			}
		#pragma endregion

		#pragma region Methods
			bool CClientSocket::OpenWriteBuffer()
			{
				if (!m_bBuffer)
				{
					m_bBuffer = true;
					return true;
				}
				return false;
			}

			bool CClientSocket::CloseWriteBuffer()
			{
				if (m_bBuffer)
				{
					m_bBuffer = false;
					bool result{ true };
					if (m_aBuffer.size() > 0)
					{
						result = Send(m_aBuffer.data(), (int)m_aBuffer.size(), false);
						m_aBuffer.clear();
					}
					return result;
				}
				return false;
			}

			bool CClientSocket::Send(const char *data, const int size, const bool inverse)
			{
				if (data && size > 0)
				{
					char *arr{ (char*)data };
					if (inverse)
					{
						arr = new char[size];
						for (int i = 0; i < size; i++)
							arr[i] = data[size - i - 1];
					}
					if (m_bBuffer)
					{
						for (int i = 0; i < size; i++)
							m_aBuffer.push_back(arr[i]);
					}
					else
					{
						m_sLastAction = std::chrono::steady_clock::now();
						int sent{ 0 }, ret;
						while (sent < size)
						{
							ret = send((SOCKET)m_pSocket, &arr[sent], size - sent, 0);
							if (ret == SOCKET_ERROR)
							{
								if (inverse)
									delete[] arr;
								return false;
							}
							if (ret > 0)
							{
								m_sLastAction = std::chrono::steady_clock::now();
								sent += ret;
							}
							else if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_sLastAction).count() * 0.001f > m_fTimeout)
							{
								if (inverse)
									delete[] arr;
								return false;
							}
							else
								Sleep(0);
						}
					}
					if (inverse)
						delete[] arr;
					return true;
				}
				return false;
			}

			bool CClientSocket::Receive(char *buffer, const int size, const bool inverse)
			{
				if (buffer && size > 0)
				{
					m_sLastAction = std::chrono::steady_clock::now();
					int received{ 0 }, ret;
					while (received < size)
					{
						ret = recv((SOCKET)m_pSocket, &buffer[received], size - received, 0);
						if (ret == SOCKET_ERROR)
						{
							if (WSAGetLastError() != WSAEWOULDBLOCK)
								return false;
							ret = 0;
						}
						if (ret > 0)
						{
							m_sLastAction = std::chrono::steady_clock::now();
							received += ret;
						}
						else if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_sLastAction).count() * 0.001f > m_fTimeout)
							return false;
						else
							Sleep(0);
					}
					if (inverse && size > 1)
						for (int i = 0; i < size / 2; i++)
						{
							char tmp{ buffer[i] };
							buffer[i] = buffer[size - i - 1];
							buffer[size - i - 1] = tmp;
						}
					return true;
				}
				return false;
			}

			bool CClientSocket::Peek(char *buffer, const int size, const bool inverse)
			{
				if (buffer && size > 0)
				{
					m_sLastAction = std::chrono::steady_clock::now();
					int received{ 0 }, ret;
					while (received < size)
					{
						ret = recv((SOCKET)m_pSocket, &buffer[received], size - received, MSG_PEEK);
						if (ret == SOCKET_ERROR)
						{
							if (WSAGetLastError() != WSAEWOULDBLOCK)
								return false;
							ret = 0;
						}
						if (ret > 0)
						{
							m_sLastAction = std::chrono::steady_clock::now();
							received += ret;
						}
						else if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_sLastAction).count() * 0.001f > m_fTimeout)
							return false;
						else
							Sleep(0);
					}
					if (inverse && size > 1)
						for (int i = 0; i < size / 2; i++)
						{
							char tmp{ buffer[i] };
							buffer[i] = buffer[size - i - 1];
							buffer[size - i - 1] = tmp;
						}
					return true;
				}
				return false;
			}

			bool CClientSocket::Write(const bool data)
			{
				return Send(reinterpret_cast<const char*>(&data), sizeof(data), false);
			}

			bool CClientSocket::Write(const int data, const bool inverse)
			{
				return Send(reinterpret_cast<const char*>(&data), sizeof(data), inverse);
			}

			bool CClientSocket::Write(const float data, const bool inverse)
			{
				return Send(reinterpret_cast<const char*>(&data), sizeof(data), inverse);
			}

			bool CClientSocket::Write(const String &data, const bool inverse)
			{
				int length{ (int)data.length() };
				if (!Send(reinterpret_cast<const char*>(&length), sizeof(length), inverse))
					return false;
				if (length > 0)
					return Send((char*)(data.c_str()), (int)sizeof(wchar_t) * (int)data.length(), inverse);
				return true;
			}

			bool CClientSocket::Write(const AnsiString &data, const bool inverse)
			{
				int length{ (int)data.length() };
				if (!Send(reinterpret_cast<const char*>(&length), sizeof(length), inverse))
					return false;
				if (length > 0)
					return Send((char*)(data.c_str()), (int)sizeof(char) * (int)data.length(), inverse);
				return true;
			}

			bool CClientSocket::Read(bool &data)
			{
				return Receive(reinterpret_cast<char*>(&data), sizeof(data), false);
			}

			bool CClientSocket::Read(int &data, const bool inverse)
			{
				return Receive(reinterpret_cast<char*>(&data), sizeof(data), inverse);
			}

			bool CClientSocket::Read(float &data, const bool inverse)
			{
				return Receive(reinterpret_cast<char*>(&data), sizeof(data), inverse);
			}

			bool CClientSocket::Read(String &data, const bool inverse)
			{
				int length;
				if (!Receive(reinterpret_cast<char*>(&length), sizeof(length), inverse))
					return false;
				data = L"";
				if (length == 0)
					return true;
				wchar_t *a{ new wchar_t[length + 1] };
				bool result{ Receive(reinterpret_cast<char*>(a), (int)sizeof(wchar_t) * length, inverse) };
				if (result)
					data.append(a, length);
				delete[] a;
				return result;
			}

			bool CClientSocket::Read(AnsiString &data, const bool inverse)
			{
				int length;
				if (!Receive(reinterpret_cast<char*>(&length), sizeof(length), inverse))
					return false;
				data = "";
				if (length == 0)
					return true;
				char *a{ new char[length + 1] };
				bool result{ Receive(a, (int)sizeof(char) * length, inverse) };
				if (result)
					data.append(a, length);
				delete[] a;
				return result;
			}

			ISocket::DataExist CClientSocket::isDataExist(ISocket::ErrorType &error)
			{
				fd_set check;
				int ret;
				timeval time{ 0, 100 };
				FD_ZERO(&check);
				FD_SET((SOCKET)m_pSocket, &check);
				ret = select(0, &check, nullptr, nullptr, &time);
				if (ret < 0)
				{
					// Error happened
					error = CServerSocket::DecodeError(WSAGetLastError());
					return DataExist::Error;
				}
				if (ret == 1 && FD_ISSET((SOCKET)m_pSocket, &check)) // Socket is ready
				{
					// Check whether data exists
					char buf;
					ret = recv((SOCKET)m_pSocket, &buf, 1, MSG_PEEK);
					if (ret == 0) // Connection has been closed, disconned
						return DataExist::Disconnected;
					return DataExist::Exist;
				}
				return DataExist::None;
			}
		#pragma endregion
		}
	}
}
#endif
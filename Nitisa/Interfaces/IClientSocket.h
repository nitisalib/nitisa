// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "ISocket.h"

namespace nitisa
{
	class IClientSocket :public virtual ISocket
	{
	protected:
		IClientSocket() = default;
		~IClientSocket() = default;
		IClientSocket(const IClientSocket &other) = delete;
		IClientSocket(IClientSocket &&other) = delete;
		IClientSocket &operator=(const IClientSocket &other) = delete;
		IClientSocket &operator=(IClientSocket &&other) = delete;
	public:
		virtual float getTimeout() = 0; // Return IO operations timeout
		virtual int getAvailableByteCount() = 0; // Return count of bytes available for reading

		virtual bool setTimeout(const float value) = 0; // Set IO operations timeout

		virtual bool OpenWriteBuffer() = 0; // Start performing all write/send operations on buffer instead on network
		virtual bool CloseWriteBuffer() = 0; // Finish performing all write/send operation on buffer and send all data from buffer to network

		virtual bool Send(const char *data, const int size, const bool inverse = false) = 0; // Send data
		virtual bool Receive(char *buffer, const int size, const bool inverse = false) = 0; // Receive data
		virtual bool Peek(char *buffer, const int size, const bool inverse = false) = 0; // Receive data without removing it from buffer

		virtual bool Write(const bool data) = 0; // Send boolean value
		virtual bool Write(const int data, const bool inverse = false) = 0; // Send integer value
		virtual bool Write(const float data, const bool inverse = false) = 0; // Send float value
		virtual bool Write(const String &data, const bool inverse = false) = 0; // Send string
		virtual bool Write(const AnsiString &data, const bool inverse = false) = 0; // Send ansi string

		virtual bool Read(bool &data) = 0; // Receive boolean value
		virtual bool Read(int &data, const bool inverse = false) = 0; // Receive integer value
		virtual bool Read(float &data, const bool inverse = false) = 0; // Receive float value
		virtual bool Read(String &data, const bool inverse = false) = 0; // Receive string
		virtual bool Read(AnsiString &data, const bool inverse = false) = 0; // Receive ansi string

		virtual ISocket::DataExist isDataExist(ISocket::ErrorType &error) = 0; // Check whether there is incoming data
	};
}
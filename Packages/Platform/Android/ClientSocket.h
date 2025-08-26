// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IClientSocket.h"
#include "Socket.h"
#include <chrono>
#include <vector>

namespace nitisa
{
	namespace platform
	{
		namespace android
		{
			class CClientSocket :public virtual IClientSocket, public CSocket
			{
			private:
				float m_fTimeout;

				bool m_bBuffer;
				std::vector<char> m_aBuffer;
				std::chrono::steady_clock::time_point m_sLastAction;
			public:
				float getTimeout() override; // By default 5 seconds
				int getAvailableByteCount() override;

				bool setTimeout(const float value) override;

				bool OpenWriteBuffer() override;
				bool CloseWriteBuffer() override;

				bool Send(const char *data, const int size, const bool inverse = false) override;
				bool Receive(char *buffer, const int size, const bool inverse = false) override;
				bool Peek(char *buffer, const int size, const bool inverse = false) override;

				bool Write(const bool data) override;
				bool Write(const int data, const bool inverse = false) override;
				bool Write(const float data, const bool inverse = false) override;
				bool Write(const String &data, const bool inverse = false) override;
				bool Write(const AnsiString &data, const bool inverse = false) override;

				bool Read(bool &data) override;
				bool Read(int &data, const bool inverse = false) override;
				bool Read(float &data, const bool inverse = false) override;
				bool Read(String &data, const bool inverse = false) override;
				bool Read(AnsiString &data, const bool inverse = false) override;

				DataExist isDataExist(ErrorType &error) override;

				CClientSocket(PlatformHandle handle, const AnsiString &local_ip, const AnsiString &remote_ip, const int local_port, const int remote_port);
			};
		}
	}
}
#endif
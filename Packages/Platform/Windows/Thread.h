// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef _WIN32
#include "Nitisa/Interfaces/IThread.h"
#include <atomic>

namespace nitisa
{
	class IThreadListener;

	namespace platform
	{
		namespace windows
		{
			class CThread :public virtual IThread
			{
			private:
				std::atomic<bool> m_bTerminated;
				std::atomic<bool> m_bPaused;
				IThreadListener *m_pListener;
			public:
				bool isCreated() override;
				bool isTerminated() override;
				bool isPaused() override;
				ThreadPriority getPriority() override;
				IThreadListener *getListener() override;

				bool setPriority(const ThreadPriority value) override;

				void Release() override;
				bool Terminate() override;
				bool Pause() override;
				bool Resume() override;
				bool Wait(const float interval) override;

				CThread(const bool paused, IThreadListener *listener); // "listener" is required
				virtual ~CThread();
			};
		}
	}
}
#endif
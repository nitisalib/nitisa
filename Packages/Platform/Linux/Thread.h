// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#if defined(__linux__) && !defined(__ANDROID__)
#include "Nitisa/Interfaces/IThread.h"
#include "Nitisa/Interfaces/IThreadListener.h"

#ifdef linux
#undef linux
#endif

namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
			class CThread :public virtual IThread
			{
			private:
				bool m_bTerminated;
				bool m_bPaused;
				IThreadListener *m_pListener;
				bool m_bFinished;
			public:
				bool isCreated() override; // Always return true
				bool isTerminated() override;
				bool isPaused() override;
				ThreadPriority getPriority() override; // Always return tpNormal
				IThreadListener *getListener() override;

				bool setPriority(const ThreadPriority value) override; // Not supported

				void Release() override;
				bool Terminate() override;
				bool Pause() override; // Not supported
				bool Resume() override; // Can be called only ones if thread was created in paused mode
				bool Wait(const float interval) override;

				CThread(const bool paused, IThreadListener *listener); // "listener" is required
				virtual ~CThread();
			};
		}
	}
}
#endif
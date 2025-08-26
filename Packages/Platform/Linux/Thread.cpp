// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#if defined(__linux__) && !defined(__ANDROID__)
#include <thread>
#include <unistd.h>

namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
		#pragma region Constructor & destructor
			CThread::CThread(const bool paused, IThreadListener *listener) :
				m_bTerminated{ false },
				m_bPaused{ paused },
				m_pListener{ listener },
				m_bFinished{ true }
			{
				*reinterpret_cast<std::thread**>(&m_hHandle) = nullptr;
				if (m_pListener && !m_bPaused)
				{
					IThreadListener *l{ m_pListener };
					IThread *t{ this };
					bool *f{ &m_bFinished };
					*reinterpret_cast<std::thread**>(&m_hHandle) = new std::thread([l, t, f]() {
						*f = false;
						l->NotifyOnProcess(t);
						*f = true;
					});
					(*reinterpret_cast<std::thread**>(&m_hHandle))->detach();
				}
			}

			CThread::~CThread()
			{
				if (*reinterpret_cast<std::thread**>(&m_hHandle))
					delete *reinterpret_cast<std::thread**>(&m_hHandle);
			}

			void CThread::Release()
			{
				delete this;
			}
		#pragma endregion

		#pragma region Getters
			bool CThread::isCreated()
			{
				return true;
			}

			bool CThread::isTerminated()
			{
				return m_bTerminated;
			}

			bool CThread::isPaused()
			{
				return m_bPaused;
			}

			IThread::ThreadPriority CThread::getPriority()
			{
				return ThreadPriority::Normal;
			}

			IThreadListener *CThread::getListener()
			{
				return m_pListener;
			}
		#pragma endregion

		#pragma region Setters
			bool CThread::setPriority(const ThreadPriority value)
			{
				return false;
			}
		#pragma endregion

		#pragma region Methods
			bool CThread::Terminate()
			{
				if (!m_bTerminated)
				{
					m_bTerminated = true;
					return true;
				}
				return false;
			}

			bool CThread::Pause()
			{
				return false;
			}

			bool CThread::Resume()
			{
				if (!(*reinterpret_cast<std::thread**>(&m_hHandle)) && m_pListener)
				{
					m_bPaused = false;
					IThreadListener *l{ m_pListener };
					IThread *t{ this };
					bool *f{ &m_bFinished };
					*reinterpret_cast<std::thread**>(&m_hHandle) = new std::thread([l, t, f]() {
						*f = false;
						l->NotifyOnProcess(t);
						*f = true;
					});
					(*reinterpret_cast<std::thread**>(&m_hHandle))->detach();
					return true;
				}
				return false;
			}

			bool CThread::Wait(const float interval)
			{
				if (*reinterpret_cast<std::thread**>(&m_hHandle) && interval > 0)
				{
					if (m_bFinished)
						return true;
					std::chrono::steady_clock::time_point start{ std::chrono::steady_clock::now() };
					while (!m_bFinished && std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < int(interval * 1000))
						usleep(5000);
					return m_bFinished;
				}
				return false;
			}
		#pragma endregion
		}
	}
}
#endif
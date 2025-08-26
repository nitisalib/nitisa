// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef _WIN32
#include <Windows.h>

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
			DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter)
			{
				CThread *thread{ (CThread*)lpParameter };
				thread->getListener()->NotifyOnProcess(thread);
				return 0;
			}

		#pragma region Constructor & destructor
			CThread::CThread(const bool paused, IThreadListener *listener) :
				m_bTerminated{ false },
				m_bPaused{ paused },
				m_pListener{ listener }
			{
				*reinterpret_cast<HANDLE*>(&m_hHandle) = 0;
				if (m_pListener)
					*reinterpret_cast<HANDLE*>(&m_hHandle) = CreateThread(nullptr, 0, ThreadProc, this, paused ? CREATE_SUSPENDED : 0, nullptr);
			}

			CThread::~CThread()
			{
				if (*reinterpret_cast<HANDLE*>(&m_hHandle))
				{
					TerminateThread(*reinterpret_cast<HANDLE*>(&m_hHandle), 0);
					CloseHandle(*reinterpret_cast<HANDLE*>(&m_hHandle));
				}
			}

			void CThread::Release()
			{
				delete this;
			}
		#pragma endregion

		#pragma region Getters
			bool CThread::isCreated()
			{
				return *reinterpret_cast<HANDLE*>(&m_hHandle) ? true : false;
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
				if (*reinterpret_cast<HANDLE*>(&m_hHandle))
				{
					switch (GetThreadPriority(*reinterpret_cast<HANDLE*>(&m_hHandle)))
					{
					case THREAD_PRIORITY_IDLE: return ThreadPriority::Idle;
					case THREAD_PRIORITY_LOWEST: return ThreadPriority::Lowest;
					case THREAD_PRIORITY_BELOW_NORMAL: return ThreadPriority::Low;
					case THREAD_PRIORITY_NORMAL: return ThreadPriority::Normal;
					case THREAD_PRIORITY_ABOVE_NORMAL: return ThreadPriority::High;
					case THREAD_PRIORITY_HIGHEST: return ThreadPriority::Highest;
					case THREAD_PRIORITY_TIME_CRITICAL: return ThreadPriority::TimeCritical;
					}
				}
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
				if (*reinterpret_cast<HANDLE*>(&m_hHandle))
				{
					int v;
					switch (value)
					{
					case ThreadPriority::Idle:
						v = THREAD_PRIORITY_IDLE;
						break;
					case ThreadPriority::Lowest:
						v = THREAD_PRIORITY_LOWEST;
						break;
					case ThreadPriority::Low:
						v = THREAD_PRIORITY_BELOW_NORMAL;
						break;
					case ThreadPriority::High:
						v = THREAD_PRIORITY_ABOVE_NORMAL;
						break;
					case ThreadPriority::Highest:
						v = THREAD_PRIORITY_HIGHEST;
						break;
					case ThreadPriority::TimeCritical:
						v = THREAD_PRIORITY_TIME_CRITICAL;
						break;
					default:
						v = THREAD_PRIORITY_NORMAL;
					}
					return SetThreadPriority(*reinterpret_cast<HANDLE*>(&m_hHandle), v);
				}
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
				if (*reinterpret_cast<HANDLE*>(&m_hHandle) && SuspendThread(*reinterpret_cast<HANDLE*>(&m_hHandle)) != DWORD(-1))
				{
					m_bPaused = true;
					return true;
				}
				return false;
			}

			bool CThread::Resume()
			{
				if (*reinterpret_cast<HANDLE*>(&m_hHandle) && ResumeThread(*reinterpret_cast<HANDLE*>(&m_hHandle)) != DWORD(-1))
				{
					m_bPaused = false;
					return true;
				}
				return false;
			}

			bool CThread::Wait(const float interval)
			{
				if (*reinterpret_cast<HANDLE*>(&m_hHandle) && ntl::IsGreater<float>(interval, 0))
					return WaitForSingleObject(*reinterpret_cast<HANDLE*>(&m_hHandle), DWORD(interval * 1000)) == WAIT_OBJECT_0;
				return false;
			}
		#pragma endregion
		}
	}
}
#endif
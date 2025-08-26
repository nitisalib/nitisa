// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef __ANDROID__
#include "NativeApplication.h"
#include <unistd.h>
#include <android/configuration.h>
#include <thread>

extern "C"
{
	ANativeWindow * NativeApplication::m_pPendingWindow{ nullptr };
	AInputQueue *NativeApplication::m_pPendingInputQueue{ nullptr };
	std::mutex NativeApplication::m_cMutex;
	int NativeApplication::m_hPipeRead{ 0 };
	int NativeApplication::m_hPipeWrite{ 0 };
	ANativeActivity *NativeApplication::m_pActivity{ nullptr };
	ANativeWindow *NativeApplication::m_pWindow{ nullptr };
	AInputQueue *NativeApplication::m_pInputQueue{ nullptr };
	ALooper *NativeApplication::m_pLooper{ nullptr };
	AConfiguration *NativeApplication::m_pConfiguration{ nullptr };
	ACTIVITY_STATE NativeApplication::m_eActivityState{ asUnknown };
	bool NativeApplication::m_bRunning{ false };
	bool NativeApplication::m_bDestroyed{ false };
	bool NativeApplication::m_bDestroyRequested{ false };
	int NativeApplication::m_hFDMain{ liMain };
	int NativeApplication::m_hFDInput{ liInput };

	extern "C"
	{
		void NativeApplication::SetWindow(ANativeWindow *window)
		{
			{
				std::lock_guard<std::mutex> lock{ m_cMutex };
				if (m_pPendingWindow)
					WriteCommand(acTerminate);
				m_pPendingWindow = window;
				if (window)
					WriteCommand(acInitialize);
			}
			while (true)
			{
				{
					std::lock_guard<std::mutex> lock{ m_cMutex };
					if (m_pWindow == m_pPendingWindow)
						break;
				}
			}
		}

		void NativeApplication::SetInput(AInputQueue* queue)
		{
			{
				std::lock_guard<std::mutex> lock{ m_cMutex };
				m_pPendingInputQueue = queue;
				WriteCommand(acInputChanged);
			}
			while (true)
			{
				{
					std::lock_guard<std::mutex> lock{ m_cMutex };
					if (m_pInputQueue == m_pPendingInputQueue)
						break;
				}
			}
		}

		void NativeApplication::SetState(const ACTIVITY_STATE state)
		{
			{
				std::lock_guard<std::mutex> lock{ m_cMutex };
				WriteCommand(state);
			}
			while (true)
			{
				{
					std::lock_guard<std::mutex> lock{ m_cMutex };
					if (m_eActivityState == state)
						break;
				}
				std::this_thread::yield();
			}
		}

	#pragma region Callbacks
		void NativeApplication::OnDestroy(ANativeActivity *activity)
		{
			{
				std::lock_guard<std::mutex> lock{ m_cMutex };
				WriteCommand(acDestroy); // Send to thread
			}
			while (true) // Wait until thread finished(it sets Destroyed = true)
			{
				{
					std::lock_guard<std::mutex> lock{ m_cMutex };
					if (m_bDestroyed)
						break;
				}
				std::this_thread::yield();
			}
			close(m_hPipeRead);
			close(m_hPipeWrite);
		}

		void NativeApplication::OnStart(ANativeActivity *activity)
		{
			SetState(asStart);
		}

		void NativeApplication::OnResume(ANativeActivity *activity)
		{
			SetState(asResume);
		}

		void NativeApplication::OnPause(ANativeActivity *activity)
		{
			SetState(asPause);
		}

		void NativeApplication::OnStop(ANativeActivity *activity)
		{
			SetState(asStop);
		}

		void* NativeApplication::OnSaveInstanceState(ANativeActivity *activity, size_t *size)
		{
			std::lock_guard<std::mutex> lock{ m_cMutex };
			WriteCommand(acSaveState);
			return nullptr;
		}

		void NativeApplication::OnWindowFocusChanged(ANativeActivity *activity, int has_focus)
		{
			std::lock_guard<std::mutex> lock{ m_cMutex };
			WriteCommand(has_focus ? acSetFocus : acKillFocus);
		}

		void NativeApplication::OnNativeWindowCreated(ANativeActivity *activity, ANativeWindow *window)
		{
			SetWindow(window);
		}

		void NativeApplication::OnNativeWindowDestroyed(ANativeActivity *activity, ANativeWindow *window)
		{
			SetWindow(nullptr);
		}

		void NativeApplication::OnNativeWindowResized(ANativeActivity *activity, ANativeWindow *window)
		{
			std::lock_guard<std::mutex> lock{ m_cMutex };
			WriteCommand(acResize);
		}

		void NativeApplication::OnNativeWindowRedrawNeeded(ANativeActivity *activity, ANativeWindow *window)
		{
			std::lock_guard<std::mutex> lock{ m_cMutex };
			WriteCommand(acPaint);
		}

		void NativeApplication::OnInputQueueCreated(ANativeActivity *activity, AInputQueue *queue)
		{
			SetInput(queue);
		}

		void NativeApplication::OnInputQueueDestroyed(ANativeActivity *activity, AInputQueue *queue)
		{
			SetInput(nullptr);
		}

		void NativeApplication::OnContentRectChanged(ANativeActivity *activity, const ARect *rect)
		{
			std::lock_guard<std::mutex> lock{ m_cMutex };
			WriteCommand(acRectChanged);
		}

		void NativeApplication::OnConfigurationChanged(ANativeActivity *activity)
		{
			std::lock_guard<std::mutex> lock{ m_cMutex };
			WriteCommand(acConfigChanged);
		}

		void NativeApplication::OnLowMemory(ANativeActivity *activity)
		{
			std::lock_guard<std::mutex> lock{ m_cMutex };
			WriteCommand(acLowMemory);
		}
	#pragma endregion

	#pragma region Init and thread entry point
		void NativeApplication::Init(ANativeActivity* activity, void* state, size_t size)
		{
			m_pActivity = activity;

			activity->callbacks->onStart = OnStart;
			activity->callbacks->onResume = OnResume;
			activity->callbacks->onSaveInstanceState = OnSaveInstanceState;
			activity->callbacks->onPause = OnPause;
			activity->callbacks->onStop = OnStop;
			activity->callbacks->onDestroy = OnDestroy;
			activity->callbacks->onWindowFocusChanged = OnWindowFocusChanged;
			activity->callbacks->onNativeWindowCreated = OnNativeWindowCreated;
			activity->callbacks->onNativeWindowResized = OnNativeWindowResized;
			activity->callbacks->onNativeWindowRedrawNeeded = OnNativeWindowRedrawNeeded;
			activity->callbacks->onNativeWindowDestroyed = OnNativeWindowDestroyed;
			activity->callbacks->onInputQueueCreated = OnInputQueueCreated;
			activity->callbacks->onInputQueueDestroyed = OnInputQueueDestroyed;
			activity->callbacks->onContentRectChanged = OnContentRectChanged;
			activity->callbacks->onConfigurationChanged = OnConfigurationChanged;
			activity->callbacks->onLowMemory = OnLowMemory;

			int pipes[2];
			if (pipe(pipes))
			{
				m_pActivity = nullptr;
				return;
			}
			m_hPipeRead = pipes[0];
			m_hPipeWrite = pipes[1];

			std::thread thread{ EntryPoint };
			thread.detach();

			// Wait for thread to start???
			while (true)
			{
				{
					std::lock_guard<std::mutex> lock{ m_cMutex };
					if (m_bRunning)
						break;
				}
				std::this_thread::yield();
			}
		}

		void NativeApplication::EntryPoint()
		{
			{
				std::lock_guard<std::mutex> lock{ m_cMutex };
				m_pConfiguration = AConfiguration_new();
				AConfiguration_fromAssetManager(m_pConfiguration, m_pActivity->assetManager);
				m_pLooper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
				ALooper_addFd(m_pLooper, m_hPipeRead, liMain, ALOOPER_EVENT_INPUT, nullptr, &m_hFDMain);
				m_bRunning = true;
			}

			nitisa::platform::android::CApplication app;
			app.Run();

			{
				std::lock_guard<std::mutex> lock{ m_cMutex };
				if (m_pInputQueue)
				{
					AInputQueue_detachLooper(m_pInputQueue);
					m_pInputQueue = nullptr;
				}
				AConfiguration_delete(m_pConfiguration);
				m_pConfiguration = nullptr;
				m_bDestroyed = true;
			}
		}
	#pragma endregion		

		int8_t NativeApplication::ReadCommand()
		{
			int8_t cmd;
			if (read(m_hPipeRead, &cmd, sizeof(cmd)) == sizeof(cmd))
			{
				switch (cmd)
				{
				case acInputChanged:
				{
					std::lock_guard<std::mutex> lock{ m_cMutex };
					if (m_pInputQueue)
						AInputQueue_detachLooper(m_pInputQueue);
					m_pInputQueue = m_pPendingInputQueue;
					if (m_pInputQueue)
						AInputQueue_attachLooper(m_pInputQueue, m_pLooper, liInput, nullptr, &m_hFDInput);
				}
				break;

				case acInitialize:
				{
					std::lock_guard<std::mutex> lock{ m_cMutex };
					m_pWindow = m_pPendingWindow;
				}
				break;

				case acResume:
				case acStart:
				case acPause:
				case acStop:
				{
					std::lock_guard<std::mutex> lock{ m_cMutex };
					m_eActivityState = (ACTIVITY_STATE)cmd;
				}
				break;

				case acConfigChanged:
				{
					std::lock_guard<std::mutex> lock{ m_cMutex };
					AConfiguration_fromAssetManager(m_pConfiguration, m_pActivity->assetManager);
				}
				break;

				case acDestroy:
				{
					std::lock_guard<std::mutex> lock{ m_cMutex };
					m_bDestroyRequested = true;
				}
				break;
				}
				return cmd;
			}
			return -1;
		}

		void NativeApplication::WriteCommand(int8_t cmd)
		{
			write(m_hPipeWrite, &cmd, sizeof(cmd));
		}

		void NativeApplication::PostProcess(int8_t cmd)
		{
			switch (cmd)
			{
			case acTerminate:
			{
				std::lock_guard<std::mutex> lock{ m_cMutex };
				m_pWindow = nullptr;
			}
			break;
			}
		}

		AInputQueue *NativeApplication::getInputQueue()
		{
			std::lock_guard<std::mutex> lock{ m_cMutex };
			return m_pInputQueue;
		}

		ANativeWindow *NativeApplication::getWindow()
		{
			std::lock_guard<std::mutex> lock{ m_cMutex };
			return m_pWindow;
		}

		ACTIVITY_STATE NativeApplication::getActivityState()
		{
			std::lock_guard<std::mutex> lock{ m_cMutex };
			return m_eActivityState;
		}

		bool NativeApplication::isTerminated()
		{
			std::lock_guard<std::mutex> lock{ m_cMutex };
			return m_bDestroyed || m_bDestroyRequested;
		}

		AConfiguration *NativeApplication::getConfiguration()
		{
			std::lock_guard<std::mutex> lock{ m_cMutex };
			return m_pConfiguration;
		}

		AAssetManager *NativeApplication::getAssetManager()
		{
			std::lock_guard<std::mutex> lock{ m_cMutex };
			return m_pActivity ? m_pActivity->assetManager : nullptr;
		}

		void NativeApplication::Finish()
		{
			std::lock_guard<std::mutex> lock{ m_cMutex };
			if (m_pActivity)
				ANativeActivity_finish(m_pActivity);
		}
	}

	void ANativeActivity_onCreate(ANativeActivity* activity, void* state, size_t size)
	{
		NativeApplication::Init(activity, state, size);
	}
}
#endif
// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include <Android/native_activity.h>
#include <Android/configuration.h>
#include <mutex>

extern "C"
{
	enum APP_COMMAND
	{
		acDestroy = 0,
		acStart = 1,
		acResume = 2,
		acPause = 3,
		acStop = 4,
		acConfigChanged = 5,
		acSetFocus = 6,
		acKillFocus = 7,
		acTerminate = 8,
		acInitialize = 9,
		acInputChanged = 10,
		acResize = 11,
		acPaint = 12,
		acRectChanged = 13,
		acSaveState = 14,
		acLowMemory = 15
	};

	enum ACTIVITY_STATE
	{
		asUnknown = 0,
		asStart = 1,
		asResume = 2,
		asPause = 3,
		asStop = 4,
		asDestroyed = 5
	};

	enum LOOPER_ID
	{
		liMain = 1,
		liInput = 2
	};

	class NativeApplication
	{
		friend void ANativeActivity_onCreate(ANativeActivity* activity, void* state, size_t size);
	private:
		static ANativeWindow * m_pPendingWindow;
		static AInputQueue *m_pPendingInputQueue;
		static std::mutex m_cMutex;
		static int m_hPipeRead;
		static int m_hPipeWrite;
		static ANativeActivity *m_pActivity;
		static ANativeWindow *m_pWindow;
		static AInputQueue *m_pInputQueue;
		static ALooper *m_pLooper;
		static AConfiguration *m_pConfiguration;
		static ACTIVITY_STATE m_eActivityState;
		static bool m_bRunning;
		static bool m_bDestroyed;
		static bool m_bDestroyRequested;
		static int m_hFDMain;
		static int m_hFDInput;

		static void WriteCommand(int8_t cmd);
		static void SetWindow(ANativeWindow *window);
		static void SetInput(AInputQueue* queue);
		static void SetState(const ACTIVITY_STATE state);

		static void OnDestroy(ANativeActivity *activity);
		static void OnStart(ANativeActivity *activity);
		static void OnResume(ANativeActivity *activity);
		static void* OnSaveInstanceState(ANativeActivity *activity, size_t *size);
		static void OnPause(ANativeActivity *activity);
		static void OnStop(ANativeActivity *activity);
		static void OnWindowFocusChanged(ANativeActivity *activity, int has_focus);
		static void OnNativeWindowCreated(ANativeActivity *activity, ANativeWindow *window);
		static void OnNativeWindowResized(ANativeActivity *activity, ANativeWindow *window);
		static void OnNativeWindowRedrawNeeded(ANativeActivity *activity, ANativeWindow *window);
		static void OnNativeWindowDestroyed(ANativeActivity *activity, ANativeWindow *window);
		static void OnInputQueueCreated(ANativeActivity *activity, AInputQueue *queue);
		static void OnInputQueueDestroyed(ANativeActivity *activity, AInputQueue *queue);
		static void OnContentRectChanged(ANativeActivity *activity, const ARect *rect);
		static void OnConfigurationChanged(ANativeActivity *activity);
		static void OnLowMemory(ANativeActivity *activity);

		static void EntryPoint();
		static void Init(ANativeActivity* activity, void* state, size_t size);
	public:
		static AInputQueue *getInputQueue();
		static ANativeWindow *getWindow();
		static ACTIVITY_STATE getActivityState();
		static bool isTerminated();
		static AConfiguration *getConfiguration();
		static AAssetManager *getAssetManager();

		static int8_t ReadCommand();
		static void PostProcess(int8_t cmd);
		static void Finish();
	};
}

/*#define Initialize \
	extern "C" \
	{ \
		void ANativeActivity_onCreate(ANativeActivity* activity, void* state, size_t size) \
		{ \
			NativeApplication::Init(activity, state, size); \
		} \
	}
	*/
extern "C"
{
	void ANativeActivity_onCreate(ANativeActivity* activity, void* state, size_t size);
}

extern void android_main();
#endif
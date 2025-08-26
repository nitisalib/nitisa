// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"

namespace nitisa
{
	class IThreadListener;

	// Pause(), Resume(), and thread priority is optional features and may not be supported by all platforms
	class IThread
	{
	protected:
		IThread() = default;
		~IThread() = default;
		IThread(const IThread &other) = delete;
		IThread(IThread &&other) = delete;
		IThread &operator=(const IThread &other) = delete;
		IThread &operator=(IThread &&other) = delete;
	public:
		enum class ThreadPriority // Thread priorities
		{
			Idle, // Idle
			Lowest, // Lowest
			Low, // Below normal
			Normal, // Normal
			High, // Above normal
			Highest, // Highest
			TimeCritical // Time critical
		};
	protected:
		PlatformHandle m_hHandle;
	public:
		PlatformHandle const &Handle{ m_hHandle };

		virtual bool isCreated() = 0; // Return whether thread was created successfully or it failed and cannot be used
		virtual bool isTerminated() = 0; // Return whether thread should terminate its job. Listener should check this property and cancel a job
		virtual bool isPaused() = 0; // Return whether thread is paused or active
		virtual ThreadPriority getPriority() = 0; // Return thread priority
		virtual IThreadListener *getListener() = 0; // Return associated listener

		virtual bool setPriority(const ThreadPriority value) = 0; // Set thread priority

		virtual void Release() = 0; // Delete itself. Should be called only after job completion(or successful termination)
		virtual bool Terminate() = 0; // Terminate execution. Usually some time will ellapse before thread stops
		virtual bool Pause() = 0; // Pause the thread
		virtual bool Resume() = 0; // Resume paused thread
		virtual bool Wait(const float interval) = 0; // Wait until thread finish its job but no longer than specified interval
	};
}
// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	class IThread;

	class IThreadListener
	{
	protected:
		IThreadListener() = default;
		~IThreadListener() = default;
		IThreadListener(const IThreadListener &other) = delete;
		IThreadListener(IThreadListener &&other) = delete;
		IThreadListener &operator=(const IThreadListener &other) = delete;
		IThreadListener &operator=(IThreadListener &&other) = delete;
	public:
		virtual void NotifyOnProcess(IThread *sender) = 0; // Called to start thread job
	};
}
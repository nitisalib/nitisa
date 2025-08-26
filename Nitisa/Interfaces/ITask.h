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
	class ITask
	{
	protected:
		ITask() = default;
		~ITask() = default;
		ITask(const ITask &other) = delete;
		ITask(ITask &&other) = delete;
		ITask &operator=(const ITask &other) = delete;
		ITask &operator=(ITask &&other) = delete;
	public:
		virtual void Run() = 0; // Run task
		virtual void Release() = 0; // Destroy task
	};
}
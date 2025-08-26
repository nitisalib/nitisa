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
	class IReleasable;

	class IReleasableListener
	{
	protected:
		IReleasableListener() = default;
		~IReleasableListener() = default;
		IReleasableListener(const IReleasableListener &other) = delete;
		IReleasableListener(IReleasableListener &&other) = delete;
		IReleasableListener &operator=(const IReleasableListener &other) = delete;
		IReleasableListener &operator=(IReleasableListener &&other) = delete;
	public:
		virtual void NotifyOnRelease(IReleasable *sender) = 0; // Notification called when releasable object is about to be destroyed
	};
}
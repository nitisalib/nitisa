// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	class IReleasableListener;

	class IReleasable
	{
	protected:
		IReleasable() = default;
		~IReleasable() = default;
		IReleasable(const IReleasable &other) = delete;
		IReleasable(IReleasable &&other) = delete;
		IReleasable &operator=(const IReleasable &other) = delete;
		IReleasable &operator=(IReleasable &&other) = delete;
	protected:
		int m_iRefCount;
	public:
		int const &RefCount{ m_iRefCount }; // Reference counter

		virtual bool RegisterReleaseListener(IReleasableListener *listener) = 0; // Add release listener used to detect final release of the manager
		virtual bool UnregisterReleaseListener(IReleasableListener *listener) = 0; // Remove release listener from list

		virtual int AddRef() = 0; // Increase reference counter and return its new value
		virtual bool Release(const bool force = false) = 0; // Decrease reference counter and destroy object if counter becomes zero. If force is true, destroy object anyway. Return true if object is destroyed and false if not
	};
}
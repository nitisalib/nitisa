// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IReleasable.h"
#include <vector>

namespace nitisa
{
	class IReleasableListener;

	class CReleasable :public virtual IReleasable
	{
	protected:
		std::vector<IReleasableListener *> m_aReleaseListeners;

		virtual void BeforeRelease(); // Called before releasing object
	public:
		// IReleasable listeners
		bool RegisterReleaseListener(IReleasableListener *listener) override;
		bool UnregisterReleaseListener(IReleasableListener *listener) override;
		
		// IReleasable methods
		int AddRef() override;
		bool Release(const bool force = false) override;

		CReleasable();
		virtual ~CReleasable() = default;
	};
}
// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Constructor & destructor
	CReleasable::CReleasable()
	{
		m_iRefCount = 1;
	}

	void CReleasable::BeforeRelease()
	{

	}
#pragma endregion

#pragma region IReleasable listeners
	bool CReleasable::RegisterReleaseListener(IReleasableListener *listener)
	{
		if (listener)
		{
			m_aReleaseListeners.push_back(listener);
			return true;
		}
		return false;
	}

	bool CReleasable::UnregisterReleaseListener(IReleasableListener *listener)
	{
		if (listener)
		{
			for (auto pos = m_aReleaseListeners.begin(); pos != m_aReleaseListeners.end(); pos++)
				if (*pos == listener)
				{
					m_aReleaseListeners.erase(pos);
					return true;
				}
		}
		return false;
	}
#pragma endregion

#pragma region IReleasable methods
	int CReleasable::AddRef()
	{
		return ++m_iRefCount;
	}

	bool CReleasable::Release(const bool force)
	{
		if (force || --m_iRefCount <= 0)
		{
			for (auto listener : m_aReleaseListeners)
				listener->NotifyOnRelease(this);
			BeforeRelease();
			delete this;
			return true;
		}
		return false;
	}
#pragma endregion
}
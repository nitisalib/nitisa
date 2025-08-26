// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IReleasableListener.h"

namespace nitisa
{
	class IReleasable;

	// TReleasable should be derived from IReleasable
	template<class TReleasable>
	class ReleasablePtr
	{
	private:
		class CListener :public virtual IReleasableListener
		{
		private:
			ReleasablePtr *m_pReleasablePtr;
		public:
			void NotifyOnRelease(IReleasable *sender) override
			{
				m_pReleasablePtr->m_pReleasable = nullptr;
			}

			CListener(ReleasablePtr *releasable_ptr) :
				m_pReleasablePtr{ releasable_ptr }
			{

			}
		};
	private:
		CListener m_cListener;
		TReleasable *m_pReleasable;
	public:
		ReleasablePtr() : // Create without releasable object attached
			m_cListener{ this },
			m_pReleasable{ nullptr }
		{

		}

		ReleasablePtr(TReleasable *releasable) : // Create with specified releasable object attached
			m_cListener{ this },
			m_pReleasable{ releasable }
		{
			if (m_pReleasable)
				m_pReleasable->RegisterReleaseListener(&m_cListener);
		}

		ReleasablePtr(const ReleasablePtr &other) : // Copy constructor
			m_cListener{ this }
		{
			if ((m_pReleasable = other.m_pReleasable))
			{
				m_pReleasable->AddRef();
				m_pReleasable->RegisterReleaseListener(&m_cListener);
			}
		}

		ReleasablePtr(ReleasablePtr &&other) : // Move constructor
			m_cListener{ this },
			m_pReleasable{ other.m_pReleasable }
		{
			other.m_pReleasable = nullptr;
			if (m_pReleasable)
			{
				m_pReleasable->UnregisterReleaseListener(&other.m_cListener);
				m_pReleasable->RegisterReleaseListener(&m_cListener);
			}
		}

		~ReleasablePtr() // Destructor
		{
			if (m_pReleasable)
			{
				m_pReleasable->UnregisterReleaseListener(&m_cListener);
				m_pReleasable->Release();
			}
		}

		ReleasablePtr &operator=(const ReleasablePtr &other) // Copy assignment operator
		{
			if (&other != this)
			{
				if (m_pReleasable)
				{
					m_pReleasable->UnregisterReleaseListener(&m_cListener);
					m_pReleasable->Release();
				}
				if ((m_pReleasable = other.m_pReleasable))
				{
					m_pReleasable->AddRef();
					m_pReleasable->RegisterReleaseListener(&m_cListener);
				}
			}
			return *this;
		}

		ReleasablePtr &operator=(ReleasablePtr &&other) // Move assignment operator
		{
			if (&other != this)
			{
				if (m_pReleasable)
				{
					m_pReleasable->UnregisterReleaseListener(&m_cListener);
					if (other.m_pReleasable != m_pReleasable)
						m_pReleasable->Release();
				}
				if ((m_pReleasable = other.m_pReleasable))
				{
					m_pReleasable->UnregisterReleaseListener(&other.m_cListener);
					m_pReleasable->RegisterReleaseListener(&m_cListener);
				}
				other.m_pReleasable = nullptr;
			}
			return *this;
		}

		ReleasablePtr &operator=(TReleasable *releasable) // Assign releasable object
		{
			if (m_pReleasable)
			{
				m_pReleasable->UnregisterReleaseListener(&m_cListener);
				if (releasable != m_pReleasable)
					m_pReleasable->Release();
			}
			if ((m_pReleasable = releasable))
				m_pReleasable->RegisterReleaseListener(&m_cListener);
			return *this;
		}

		TReleasable *operator->()
		{
			return m_pReleasable;
		}

		const TReleasable* operator->() const
		{
			return m_pReleasable;
		}

		operator TReleasable*()
		{
			return m_pReleasable;
		}

		operator const TReleasable* () const
		{
			return m_pReleasable;
		}

		TReleasable *move() // Return assigned releasable object and clear internal reference to it so it is not released during class instance destruction
		{
			TReleasable *result{ m_pReleasable };
			if (m_pReleasable)
			{
				m_pReleasable->UnregisterReleaseListener(&m_cListener);
				m_pReleasable = nullptr;
			}
			return result;
		}
	};
}
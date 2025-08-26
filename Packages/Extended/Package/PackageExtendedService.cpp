// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace extended
	{
	#pragma region Constructor & destructor
		CPackageExtendedService::CPackageExtendedService(CPackageExtended *package) :
			m_pPackage{ package }
		{

		}

		void CPackageExtendedService::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Notifications
		void CPackageExtendedService::NotifyOnCreateComponent(IComponent *component, IPackageComponent *package_component, IPropertyList *properties, IEventList *events)
		{
			m_pPackage->m_aCreatedComponents.push_back(CPackageExtended::COMPONENT{ component, package_component, properties, events });
			m_pPackage->m_bCreatedComponentsSorted = false;
		}

		void CPackageExtendedService::NotifyOnCreateControl(IControl *control, IPackageControl *package_control, IPropertyList *properties, IEventList *events)
		{
			m_pPackage->m_aCreatedControls.push_back(CPackageExtended::CONTROL{ control, package_control, properties, events });
			m_pPackage->m_bCreatedControlsSorted = false;
		}

		void CPackageExtendedService::NotifyOnDestroyComponent(IComponent *component)
		{
			for (auto pos = m_pPackage->m_aCreatedComponents.begin(); pos != m_pPackage->m_aCreatedComponents.end(); pos++)
				if (pos->Component == component)
				{
					m_pPackage->m_aCreatedComponents.erase(pos);
					break;
				}
		}

		void CPackageExtendedService::NotifyOnDestroyControl(IControl *control)
		{
			for (auto pos = m_pPackage->m_aCreatedControls.begin(); pos != m_pPackage->m_aCreatedControls.end(); pos++)
				if (pos->Control == control)
				{
					m_pPackage->m_aCreatedControls.erase(pos);
					break;
				}
		}
	#pragma endregion
	}
}
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
	namespace charts
	{
	#pragma region Constructor & destructor
		CPackageChartsService::CPackageChartsService(CPackageCharts *package) :
			m_pPackage{ package }
		{

		}

		void CPackageChartsService::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Notifications
		void CPackageChartsService::NotifyOnCreateComponent(IComponent *component, IPackageComponent *package_component, IPropertyList *properties, IEventList *events)
		{
			m_pPackage->m_aCreatedComponents.push_back(CPackageCharts::COMPONENT{ component, package_component, properties, events });
			m_pPackage->m_bCreatedComponentsSorted = false;
		}

		void CPackageChartsService::NotifyOnCreateControl(IControl *control, IPackageControl *package_control, IPropertyList *properties, IEventList *events)
		{
			m_pPackage->m_aCreatedControls.push_back(CPackageCharts::CONTROL{ control, package_control, properties, events });
			m_pPackage->m_bCreatedControlsSorted = false;
		}

		void CPackageChartsService::NotifyOnDestroyComponent(IComponent *component)
		{
			for (auto pos = m_pPackage->m_aCreatedComponents.begin(); pos != m_pPackage->m_aCreatedComponents.end(); pos++)
				if (pos->Component == component)
				{
					m_pPackage->m_aCreatedComponents.erase(pos);
					break;
				}
		}

		void CPackageChartsService::NotifyOnDestroyControl(IControl *control)
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
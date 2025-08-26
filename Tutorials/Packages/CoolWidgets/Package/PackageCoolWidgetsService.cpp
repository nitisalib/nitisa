#include "stdafx.h"

namespace nitisa
{
	namespace coolwidgets
	{
	#pragma region Constructor & destructor
		CPackageCoolWidgetsService::CPackageCoolWidgetsService(CPackageCoolWidgets *package) :
			m_pPackage{ package }
		{

		}

		void CPackageCoolWidgetsService::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Notifications
		void CPackageCoolWidgetsService::NotifyOnCreateComponent(IComponent *component, IPackageComponent *package_component, IPropertyList *properties, IEventList *events)
		{
			
		}

		void CPackageCoolWidgetsService::NotifyOnCreateControl(IControl *control, IPackageControl *package_control, IPropertyList *properties, IEventList *events)
		{
			m_pPackage->m_aCreatedControls.push_back(CPackageCoolWidgets::CONTROL{ control, package_control, properties, events });
			m_pPackage->m_bCreatedControlsSorted = false;
		}

		void CPackageCoolWidgetsService::NotifyOnDestroyComponent(IComponent *component)
		{
			
		}

		void CPackageCoolWidgetsService::NotifyOnDestroyControl(IControl *control)
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
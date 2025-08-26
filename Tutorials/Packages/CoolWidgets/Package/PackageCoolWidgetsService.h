#pragma once

#include "Nitisa/Package/Interfaces/IPackageService.h"

namespace nitisa
{
	class IComponent;
	class IControl;
	class IEventList;
	class IPackageComponent;
	class IPackageControl;
	class IPropertyList;

	namespace coolwidgets
	{
		class CPackageCoolWidgets;

		class CPackageCoolWidgetsService :public virtual IPackageService
		{
		private:
			CPackageCoolWidgets *m_pPackage;
		public:
			void NotifyOnCreateComponent(IComponent *component, IPackageComponent *package_component, IPropertyList *properties, IEventList *events) override;
			void NotifyOnCreateControl(IControl *control, IPackageControl *package_control, IPropertyList *properties, IEventList *events) override;
			void NotifyOnDestroyComponent(IComponent *component) override;
			void NotifyOnDestroyControl(IControl *control) override;

			void Release() override;

			CPackageCoolWidgetsService(CPackageCoolWidgets *package);
			virtual ~CPackageCoolWidgetsService() = default;
		};
	}
}
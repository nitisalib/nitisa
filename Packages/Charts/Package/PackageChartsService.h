// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

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

	namespace charts
	{
		class CPackageCharts;

		class CPackageChartsService :public virtual IPackageService
		{
		private:
			CPackageCharts *m_pPackage;
		public:
			void NotifyOnCreateComponent(IComponent *component, IPackageComponent *package_component, IPropertyList *properties, IEventList *events) override;
			void NotifyOnCreateControl(IControl *control, IPackageControl *package_control, IPropertyList *properties, IEventList *events) override;
			void NotifyOnDestroyComponent(IComponent *component) override;
			void NotifyOnDestroyControl(IControl *control) override;

			void Release() override;

			CPackageChartsService(CPackageCharts *package);
			virtual ~CPackageChartsService() = default;
		};
	}
}
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
	class IComponent;
	class IControl;
	class IEventList;
	class IPackageComponent;
	class IPackageControl;
	class IPropertyList;

	class IPackageService
	{
	protected:
		IPackageService() = default;
		~IPackageService() = default;
		IPackageService(const IPackageService &other) = delete;
		IPackageService(IPackageService &&other) = delete;
		IPackageService &operator=(const IPackageService &other) = delete;
		IPackageService &operator=(IPackageService &&other) = delete;
	public:
		virtual void NotifyOnCreateComponent(IComponent *component, IPackageComponent *package_component, IPropertyList *properties, IEventList *events) = 0; // Should be called to notify package about component creation
		virtual void NotifyOnCreateControl(IControl *control, IPackageControl *package_control, IPropertyList *properties, IEventList *events) = 0; // Should be called to notify package about control creation
		virtual void NotifyOnDestroyComponent(IComponent *component) = 0; // Should be called to notify package about component destruction
		virtual void NotifyOnDestroyControl(IControl *control) = 0; // Should be called to notify package about control destruction

		virtual void Release() = 0; // Destroy instance
	};
}
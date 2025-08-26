// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/PlatformVersion.h"
#include "../../Core/Strings.h"

namespace nitisa
{
	class IComponent;
	class IControl;
	class IEventList;
	class IListItem;
	class IPackageComponent;
	class IPackageControl;
	class IPackageForm;
	class IPackageListItem;
	class IPackageRenderer;
	class IPackageService;
	class IPackageStyle;
	class IPackagePropertyHandler;
	class IPropertyList;
	class IStyle;

	class IPackage
	{
	protected:
		IPackage() = default;
		~IPackage() = default;
		IPackage(const IPackage &other) = delete;
		IPackage(IPackage &&other) = delete;
		IPackage &operator=(const IPackage &other) = delete;
		IPackage &operator=(IPackage &&other) = delete;
	public:
		enum class LicenseType // Package license type
		{
			Free, // Free without any conditions
			FreeHome, // Free for non-commercial usage
			FreeLimited, // Free until maximum profit
			Trial, // User may use it for some days but should pay after if he wants to use it
			Demo, // Demo
			Commercial // User should pay before using
		};

		struct Dependency // Describe package dependency on another package
		{
			String Vendor; // Dependency package vendor
			String Name; // Dependency package name
			String Version; // Dependency package version
		};
	public:
		// Common information
		virtual String getVendor() = 0; // Return vendor
		virtual String getName() = 0; // Return package name
		virtual String getVersion() = 0; // Return version
		virtual String getDescription() = 0; // Return description
		virtual String getVendorUrl() = 0; // Return vendor site or page URL
		virtual String getReferenceUrl() = 0; // Return package documentation main page URL
		virtual String getLicenseText() = 0; // Return license agreement text
		virtual LicenseType getLicense() = 0; // Return license type
		virtual bool hasStaticLinking() = 0; // Whether static linking is allowed or not
		virtual bool hasDynamicLinking() = 0; // Whether dynamic linking is allowed or not
		virtual bool hasSourceCode() = 0; // Whether package contains also a source code
		virtual int getDependencyCount() = 0; // Return count of external dependencies
		virtual Dependency getDependency(const int index) = 0; // Return external dependency description by index

		// Supported platforms by components & controls(may be overwritten in control and components if they have another supported platform set)
		virtual int getPlatformCount() = 0; // Return supported platform count. If 0, all platforms are supported
		virtual PlatformVersion getPlatform(const int index) = 0; // Return supported platform description by index

		// Components
		virtual int getComponentCount() = 0; // Return component description count
		virtual IPackageComponent *getComponent(const int index) = 0; // Return component description by index
		virtual IPackageComponent *getComponent(const String &class_name) = 0; // Return component description by component class name
		virtual IPackageComponent *getComponent(IComponent *component) = 0; // Return component description corresponding to specified component

		// Created components
		virtual int getCreatedComponentCount() = 0; // Return created component count
		virtual IComponent *getCreatedComponent(const int index) = 0; // Return created component by index
		/**
		Find created component and its related information
		@param index Created component index
		@param[out] component Found component
		@param[out] package_component Component description
		@param[out] properties Component property list
		@param[out] events Component event list
		@return True if component exists
		*/
		virtual bool getCreatedComponent(const int index, IComponent **component, IPackageComponent **package_component, IPropertyList **properties, IEventList **events) = 0;

		// Controls
		virtual int getControlCount() = 0; // Return control description count
		virtual IPackageControl *getControl(const int index) = 0; // Return control description by index
		virtual IPackageControl *getControl(const String &class_name) = 0; // Return control description by control class name
		virtual IPackageControl *getControl(IControl *control) = 0; // Return control description for specified control

		// Created controls
		virtual int getCreatedControlCount() = 0; // Return created control count
		virtual IControl *getCreatedControl(const int index) = 0; // Return created control by index
		/**
		Find created control and its related information
		@param index Created control index
		@param[out] control Found control
		@param[out] package_control Control description
		@param[out] properties Control property list
		@param[out] events Control event list
		@return True if control exists
		*/
		virtual bool getCreatedControl(const int index, IControl **control, IPackageControl **package_control, IPropertyList **properties, IEventList **events) = 0;

		// List items
		virtual int getListItemCount() = 0; // Return list item description count
		virtual IPackageListItem *getListItem(const int index) = 0; // Return list item description by index
		virtual IPackageListItem *getListItem(const String &class_name) = 0; // Return list item description by list item class name
		virtual IPackageListItem *getListItem(IListItem *listitem) = 0; // Return list item description for specified list item

		// Forms
		virtual int getFormCount() = 0; // Return form description count
		virtual IPackageForm *getForm(const int index) = 0; // Return form description by index
		virtual IPackageForm *getForm(const String &class_name) = 0; // Return form description by form class name

		// Renderers
		virtual int getRendererCount() = 0; // Return renderer description count
		virtual IPackageRenderer *getRenderer(const int index) = 0; // Return renderer description by index
		virtual IPackageRenderer *getRenderer(const String &class_name) = 0; // Return renderer description by renderer class name

		// Property handlers
		virtual int getPropertyHandlerCount() = 0; // Return property handler description count
		virtual IPackagePropertyHandler *getPropertyHandler(const int index) = 0; // Return property handler description by index
		virtual IPackagePropertyHandler *getPropertyHandler(const String &name) = 0; // Return property handler description by name

		// Styles
		virtual int getStyleCount() = 0; // Return style description count
		virtual IPackageStyle *getStyle(const int index) = 0; // Return style description by index
		virtual IPackageStyle *getStyle(const String &class_name) = 0; // Return style description by style class name
		virtual IPackageStyle *getStyle(IStyle *style) = 0; // Return style description for specified style

		virtual void Release() = 0; // Destroy instance
		virtual IPackageService *QueryService() = 0; // Return service
	};
}
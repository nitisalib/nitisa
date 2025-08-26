// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"

namespace nitisa
{
	class IComponent;
	class IControl;
	class IEvent;
	class IListItem;
	class IPackage;
	class IPackageComponent;
	class IPackageControl;
	class IPackageForm;
	class IPackageListItem;
	class IPackagePropertyHandler;
	class IPackageRenderer;
	class IPackageStyle;
	class IProperty;
	class IStyle;

	class IEditor
	{
	protected:
		IEditor() = default;
		~IEditor() = default;
		IEditor(const IEditor &other) = delete;
		IEditor(IEditor &&other) = delete;
		IEditor &operator=(const IEditor &other) = delete;
		IEditor &operator=(IEditor &&other) = delete;
	public:
		// All registered packages
		virtual int getPackageCount() = 0;
		virtual IPackage *getPackage(const int index) = 0;
		virtual IPackage *getPackage(const String &name) = 0;
		virtual bool isPackageVisible(const int index) = 0;
		virtual bool isPackageVisible(const String &name) = 0;

		// All registered package components
		virtual int getComponentCount() = 0;
		virtual IPackageComponent *getComponent(const int index) = 0;
		virtual IPackageComponent *getComponent(const String &package, const String &class_name) = 0;
		virtual IPackageComponent *getComponent(IComponent *component) = 0;
		virtual bool isComponentVisible(const int index) = 0;
		virtual bool isComponentVisible(const String &package, const String &class_name) = 0;

		// All registered package controls
		virtual int getControlCount() = 0;
		virtual IPackageControl *getControl(const int index) = 0;
		virtual IPackageControl *getControl(const String &package, const String &class_name) = 0;
		virtual IPackageControl *getControl(IControl *control) = 0;
		virtual bool isControlVisible(const int index) = 0;
		virtual bool isControlVisible(const String &package, const String &class_name) = 0;

		// All registered list items
		virtual int getListItemCount() = 0;
		virtual IPackageListItem *getListItem(const int index) = 0;
		virtual IPackageListItem *getListItem(const String &package, const String &class_name) = 0;
		virtual IPackageListItem *getListItem(IListItem *listitem) = 0;

		// All registered package forms
		virtual int getFormCount() = 0;
		virtual IPackageForm *getForm(const int index) = 0;
		virtual IPackageForm *getForm(const String &package, const String &class_name) = 0;
		virtual bool isFormVisible(const int index) = 0;
		virtual bool isFormVisible(const String &package, const String &class_name) = 0;

		// All registered package renderers
		virtual int getRendererCount() = 0;
		virtual IPackageRenderer *getRenderer(const int index) = 0;
		virtual IPackageRenderer *getRenderer(const String &package, const String &class_name) = 0;
		virtual bool isRendererVisible(const int index) = 0;
		virtual bool isRendererVisible(const String &package, const String &class_name) = 0;

		// All registered property handlers
		virtual int getPropertyHandlerCount() = 0;
		virtual IPackagePropertyHandler *getPropertyHandler(const int index) = 0;
		virtual IPackagePropertyHandler* getPropertyHandler(const String &package, const String &name) = 0;
		virtual IPackagePropertyHandler* getPropertyHandler(const String &name) = 0; // Find enabled by name. Search in last-to-first order
		virtual bool isPropertyHandlerEnabled(const int index) = 0;
		virtual bool isPropertyHandlerEnabled(const String &package, const String &name) = 0;

		// All registered package styles
		virtual int getStyleCount() = 0;
		virtual IPackageStyle *getStyle(const int index) = 0;
		virtual IPackageStyle *getStyle(const String &package, const String &class_name) = 0;
		virtual IPackageStyle *getStyle(IStyle *style) = 0;
		virtual bool isStyleVisible(const int index) = 0;
		virtual bool isStyleVisible(const String &package, const String &class_name) = 0;

		virtual bool Register(IPackageComponent *component) = 0;
		virtual bool Register(IPackageControl *control) = 0;
		virtual bool Register(IPackageListItem *listitem) = 0;
		virtual bool Register(IPackageForm *form) = 0;
		virtual bool Register(IPackageStyle *style) = 0;
		virtual bool Register(IPackageRenderer *renderer) = 0;
		virtual bool Register(IPackagePropertyHandler *handler) = 0;

		virtual void Release() = 0; // Release itself(maybe only decreasing internal counter in case of singleton pattern)
	};
}
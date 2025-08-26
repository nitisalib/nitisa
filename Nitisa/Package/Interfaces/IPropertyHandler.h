// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Interfaces/IBuiltInControl.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IProperty;

	// Property handler is used only to work with one property and it's one state. All other should be handled by PropertyEditor
	// When property changed, property handler should call QueryService()->getListener()->NotifyOnPropertyChange() to notify about changes and parent to copy property value to another properties(if requird) and repaint visual editor
	class IPropertyHandler :public virtual IBuiltInControl
	{
	protected:
		IPropertyHandler() = default;
		~IPropertyHandler() = default;
		IPropertyHandler(const IPropertyHandler &other) = delete;
		IPropertyHandler(IPropertyHandler &&other) = delete;
		IPropertyHandler &operator=(const IPropertyHandler &other) = delete;
		IPropertyHandler &operator=(IPropertyHandler &&other) = delete;
	public:
		virtual IPackage *getPackage() = 0; // Return package
		virtual IProperty *getProperty() = 0; // Return assigned property
		virtual String getPropertyState() = 0; // Return state of assigned property
		virtual bool isEditable(IProperty *property) = 0; // Check whether specified property can be edited by this handler(when there are multiple handler with same name, first one accepted property will be used)

		virtual bool setProperty(IProperty *value) = 0; // Assign property before any other actions
		virtual bool setPropertyState(const String &value) = 0; // Set state with which handler should work
		virtual bool setControl(IControl *value) = 0; // Assign PropertyEditor control. Handler is derived from built-in control but it has abstract getControl() method and handler class can't be derived because it's created inside dll, so the parent control should be set
	};
}
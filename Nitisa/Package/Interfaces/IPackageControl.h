// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Core/Variant.h"
#include "IPackageEntity.h"
#include <iostream>

namespace nitisa
{
	class IComponent;
	class IControl;
	class IEventList;
	class IListItem;
	class IPackageControlListener;
	class IPropertyList;

	class Image;

	class IPackageControl :public virtual IPackageEntity
	{
	protected:
		IPackageControl() = default;
		~IPackageControl() = default;
		IPackageControl(const IPackageControl &other) = delete;
		IPackageControl(IPackageControl &&other) = delete;
		IPackageControl &operator=(const IPackageControl &other) = delete;
		IPackageControl &operator=(IPackageControl &&other) = delete;
	public:
		virtual const Image *getIcon() = 0; // Return icon. Could be nullptr but it is recommended to use unique one so that user could easily find the control amongs others in Form Builder
		virtual bool isVisible() = 0; // Whether it should be shown in component/control selection list
		virtual bool isDisplayIcon() = 0; // Whether control icon should be displayed as well
		virtual bool isInstance(IControl *control) = 0; // Return whether a specified control is instance of control corresponding to this package entity
		virtual bool isTransformable() = 0; // Whether control could be translated/scaled/rotated in Form Builder. If false, the control won't be transformable in form editor of the Form Builder
		virtual bool isDialogBox() = 0; // Whether control is derived from IDialogBox and can be used as base class used in exporting in Form Builder

		/**
		Create corresponding control, property and event lists
		@param [out] properties Created property list will be stored here. Pass nullptr to avoid property list creation
		@param [out] events Created event list will be stored here. Pass nullptr to avoid event list creation
		@return Created control
		@note IPackageService::NotifyOnCreateControl() will be called if either property or event list is created. If none of the lists is created, package will not be informed about control creation
		*/
		virtual IControl *Create(IPropertyList **properties, IEventList **events) = 0;
		virtual IPropertyList *CreatePropertyList(IControl *control) = 0; // Create property list for specified control
		virtual IEventList *CreateEventList(IControl *control) = 0; // Create event list for specified control
		virtual void Save(Variant &dest, IPropertyList *properties, IEventList *events) = 0; // Save properties and events into Variant
		virtual void Load(const Variant &src, IPropertyList *properties, IEventList *events) = 0; // Load properties and events from Variant
		/**
		Should output properties and events as c++ code
		@param f File stream
		@param shift Just a spaces for good code alignment. Add it to output
		@param owner Control name. Could be empty string if lists belong to form
		@param properties Property list
		@param events Event list
		@param form Form name
		@param dialog_box Dialog box class name if expoting as dialog box, otherwise should be empty
		*/
		virtual void Export(std::wofstream &f, const String &shift, const String &owner, IPropertyList *properties, IEventList *events, const String &form, const String &dialog_box) = 0;
		/**
		May output some extra code which is inserted into result file just before assigning a window to a form. May be used to set form properties before real window creation
		@param f File stream
		@param shift Just a spaces for good code alignment. Add it to output
		@param control Control
		*/
		virtual void ExportExtra(std::wofstream &f, const String &shift, IControl *control) = 0;
		/**
		Creates child control if specified control supports IControlCreateChild interface. Dialog can be added to specify which one of allowed child controls should be created if there are many of them
		By default cast control to IControlCreateChild and call it's CreateChild method
		@param parent Control which child should be created
		@param[out] child Created child control. Can be nullptr in case of listener is provided
		@param listener Listener which OnCreateChild will be called after successful child control creation. Can be nullptr
		@return True if succeeded
		*/
		virtual bool CreateChild(IControl *parent, IControl **child, IPackageControlListener *listener = nullptr) = 0;
		/**
		Create list item for the component. Should be implemented in package components and controls which supports items. Could show dialog to allow user to select which one of supported lit item types should be created and specify additional properties like caption.
		@param component Component which will own created item
		@param parent Parent item for the new one. Can be empty if item should be created in root
		@param[out] item Created item. Can be nullptr in case of listener is provided
		@param listener Listener which OnCreateListItem will be called after successful list item creation. Can be nullptr
		@return True on success
		*/
		virtual bool CreateListItem(IComponent *component, IListItem *parent, IListItem **item, IPackageControlListener *listener = nullptr) = 0;
	};
}
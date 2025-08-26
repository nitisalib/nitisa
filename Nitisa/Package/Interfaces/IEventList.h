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
#include <iostream>

namespace nitisa
{
	class IClass;
	class IEvent;
	class IPackage;
	class IPackageEntity;

	class IEventList
	{
	protected:
		IEventList() = default;
		~IEventList() = default;
		IEventList(const IEventList &other) = delete;
		IEventList(IEventList &&other) = delete;
		IEventList &operator=(const IEventList &other) = delete;
		IEventList &operator=(IEventList &&other) = delete;
	public:
		virtual IPackage *getPackage() = 0; // Return package
		virtual IClass *getParent() = 0; // Return parent object
		virtual int getCount() = 0; // Return event count
		virtual IEvent *getEvent(const int index) = 0; // Return event by index
		virtual IEvent *getEvent(const String &name) = 0; // Return event by name
		virtual IPackageEntity *getEntity() = 0; // Return package entity whose property list is it

		virtual void Release() = 0; // Destroy instance
		virtual void Save(Variant &dest) = 0; // Save list to Variant
		virtual void Load(const Variant &src) = 0; // Load list from Variant
		/**
		Export list as c++ code
		@param f File stream
		@param shift Just a spaces for good code alignment. Add it to output
		@param owner Control name. Could be empty string if event belongs to form
		@param form Form name
		@param dialog_box Dialog box class name if expoting as dialog box, otherwise should be empty
		*/
		virtual void Export(std::wofstream &f, const String &shift, const String &owner, const String &form, const String &dialog_box) = 0;
	};
}
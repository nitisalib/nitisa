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
	class IEventList;

	class IEvent
	{
	protected:
		IEvent() = default;
		~IEvent() = default;
		IEvent(const IEvent &other) = delete;
		IEvent(IEvent &&other) = delete;
		IEvent &operator=(const IEvent &other) = delete;
		IEvent &operator=(IEvent &&other) = delete;
	public:
		struct ForwardDeclaration
		{
			String Declaration;
			String HeaderFile;
			String Namespace;
		};
	public:
		virtual IEventList *getEventList() = 0; // Return event list
		virtual IClass *getParent() = 0; // Return parent object
		virtual String getName() = 0; // Return name
		virtual String getSignature() = 0; // Return event signature(for example, IControl::OnPaint event has signature "const MessagePaint &m, bool &draw_children"; all events have void return type)
		virtual String getArguments() = 0; // Return event arguments as they are in event callback call(for IControl::OnPaint it is "m , draw_children")
		virtual String getValue() = 0; // Return name of event callback function(like Button1_OnClick)
		virtual bool isChanged() = 0; // Return whether current value differs from one which was when event was created
		virtual int getHeaderFileCount() = 0; // Return header file count
		virtual String getHeaderFile(const int index) = 0; // Return header file by index. Relative to the package directory(for example, if entity will be in "/Packages/Vendor/Components/Name/Name.h", this should return "Vendor/Components/Name.h")
		virtual int getForwardDeclarationCount() = 0;
		virtual ForwardDeclaration getForwardDeclaration(const int index) = 0;

		virtual bool setValue(const String &value) = 0; // Set name for the event callback function

		virtual void Release() = 0; // Destroy the instance
		virtual void Save(Variant &dest) = 0; // Save properties to Variant
		virtual void Load(const Variant &src) = 0; // Load properties from Variant

		/**
		Should output event initialization as c++ code
		@param f File stream
		@param shift Just a spaces for good code alignment. Add it to output
		@param control Control name. Could be empty string if event belongs to form
		@param form Form name
		@param dialog_box Dialog box class name if expoting as dialog box, otherwise should be empty
		*/
		virtual void Export(std::wofstream &f, const String &shift, const String &control, const String &form, const String &dialog_box) = 0;
	};
}
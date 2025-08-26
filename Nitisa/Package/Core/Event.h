// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Core/Variant.h"
#include "../Interfaces/IEvent.h"
#include <iostream>
#include <vector>

namespace nitisa
{
	class IClass;
	class IEventList;

	class CEvent :public virtual IEvent
	{
	private:
		IEventList *m_pEventList;
		IClass *m_pParent;
		String m_sName;
		String m_sSignature;
		String m_sArguments;
		String m_sValue;
		StringArray m_aHeaderFiles;
		std::vector<ForwardDeclaration> m_aForwardDeclarations;
	public:
		IEventList *getEventList() override;
		IClass *getParent() override;
		String getName() override;
		String getSignature() override;
		String getArguments() override;
		String getValue() override;
		bool isChanged() override;
		int getHeaderFileCount() override;
		String getHeaderFile(const int index) override;
		int getForwardDeclarationCount() override;
		ForwardDeclaration getForwardDeclaration(const int index) override;

		bool setValue(const String &value) override;

		void Release() override;
		void Save(Variant &dest) override;
		void Load(const Variant &src) override;
		void Export(std::wofstream &f, const String &shift, const String &control, const String &form, const String &dialog_box) override;

		/**
		Constructor
		@param list Event list to which this event belong
		@param parent Parent object whose event this class instance describe
		@param name Name of the event(for example, OnClick)
		@param signature Event callback function arguments with types(for example, "IForm *sender, const CLOSE_ACTION &action")
		@param arguments Event callback function arguments(for example, "send, action")
		*/
		CEvent(IEventList *list, IClass *parent, const String &name, const String &signature, const String &arguments);
		virtual ~CEvent() = default;

		CEvent *AddHeaderFile(const String &value); // Add new header file to the list(use path relative to the Packages directory)
		CEvent *AddForwardDeclaration(const String &value, const String &header_file, const String &ns);
	};
}
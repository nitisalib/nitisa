// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../Interfaces/IProperty.h"
#include "ExportPrefixType.h"

namespace nitisa
{
	class IClass;
	class IProperyList;

	class CProperty :public virtual IProperty
	{
	public:
		using FSkip = bool(*)(IClass *parent);
	private:
		FSkip m_fSkip;
		bool m_bReadOnly;
		StringArray m_aHeaderFiles;
		std::vector<ForwardDeclaration> m_aForwardDeclarations;
	protected:
		String Prefix(const ExportPrefixType prefix_type, const String &prefix = L""); // Generate prefix depending on prefix type specified
	public:
		bool isSkip() override;
		int getHeaderFileCount() override;
		String getHeaderFile(const int index) override;
		int getForwardDeclarationCount() override;
		ForwardDeclaration getForwardDeclaration(const int index) override;

		void setParent(IClass *parent) override;
		IProperty *setAffectItems(const bool value) override;

		void Release() override;

		/**
		Constructor
		@param list List of properties to which this property belongs
		@param parent Parent object which property this one describes
		@param name Property name
		@param handler Property handler name
		@param skip Function checking if the property could be skipped when saving in Form Builder. Could be nullptr
		@param read_only Whether the property is read only
		*/
		CProperty(IPropertyList *list, IClass *parent, const String &name, const String &handler, FSkip skip, const bool read_only);
		virtual ~CProperty() = default;

		bool isReadOnly() const; // Return whether the property is read only

		CProperty *AddHeaderFile(const String &value); // Add new header file to the list(use path relative to the Packages directory)
		CProperty *AddForwardDeclaration(const String &value, const String &header_file, const String &ns);
	};
}
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
#include <fstream>

namespace nitisa
{
	class IClass;
	class IPropertyList;

	class IProperty
	{
	protected:
		IProperty() = default;
		~IProperty() = default;
		IProperty(const IProperty &other) = delete;
		IProperty(IProperty &&other) = delete;
		IProperty &operator=(const IProperty &other) = delete;
		IProperty &operator=(IProperty &&other) = delete;
	public:
		struct ForwardDeclaration
		{
			String Declaration;
			String HeaderFile;
			String Namespace;
		};
	protected:
		String m_sName;
		String m_sPropertyHandlerName;
		IClass *m_pParent;
		IPropertyList *m_pPropertyList;
		bool m_bAffectItems;
	public:
		String const &Name{ m_sName }; // Name
		String const &PropertyHandlerName{ m_sPropertyHandlerName }; // Name of property handler which can edit this property
		IClass* const &Parent{ m_pParent }; // Owner of the property
		IPropertyList* const &PropertyList{ m_pPropertyList }; // Property list containing the property
		bool const &AffectItems{ m_bAffectItems }; // Whether property change may affect control list items. By default false. If true, the Form Builder will perform list items(tree) update after property changes. Used only for components and controls(not for IListItem)
		
		virtual String getPreview() = 0; // Return preview of property value
		virtual String getPreview(const String &state) = 0; // Return preview by state
		virtual bool isChanged() = 0; // Return whether current value differs from one which was when property was created
		virtual bool isSkip() = 0; // Return whether property should be skipped when saving in Form Builder
		virtual int getHeaderFileCount() = 0; // Return header file count
		virtual String getHeaderFile(const int index) = 0; // Return header file by index. Relative to the package directory(for example, if entity will be in "/Packages/Vendor/Components/Name/Name.h", this should return "Vendor/Components/Name.h")
		virtual int getForwardDeclarationCount() = 0;
		virtual ForwardDeclaration getForwardDeclaration(const int index) = 0;

		virtual void setParent(IClass *parent) = 0; // Set owner. Do not set null or object which is incompatible with prev parent. No checks are performed. Currently used only in saving list items to check if list item was changed(differs from same list item just created)
		virtual IProperty *setAffectItems(const bool value) = 0; // Set whether changing the property affects on owner list items
		virtual IProperty *setChanged(const bool value) = 0; // Mark as changed/unchanged

		virtual void Release() = 0; // Destroy instance
		virtual bool Copy(IProperty *dest) = 0; // Copy to destination. Can copy only if dest has same type(could be casted to same type). Copy only value part
		virtual void Save(Variant &dest) = 0; // Save to Variant
		virtual void Load(const Variant &src) = 0; // Load from Variant
		/**
		Should output property as c++ code(like setColor({255, 0, 0, 55});)
		@param f File stream
		@param shift Just a spaces for good code alignment. Add it to output
		@param control Control/Component name
		*/
		virtual void Export(std::wofstream &f, const String &shift, const String &control) = 0;
	};
}
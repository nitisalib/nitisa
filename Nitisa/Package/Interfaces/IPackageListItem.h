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
	class IListItem;
	class IPropertyList;

	class IPackageListItem :public virtual IPackageEntity
	{
	protected:
		IPackageListItem() = default;
		~IPackageListItem() = default;
		IPackageListItem(const IPackageListItem &other) = delete;
		IPackageListItem(IPackageListItem &&other) = delete;
		IPackageListItem &operator=(const IPackageListItem &other) = delete;
		IPackageListItem &operator=(IPackageListItem &&other) = delete;
	public:
		virtual bool isInstance(IListItem *listitem) = 0; // Return whether a specified list item is instance of list item corresponding to this package entity

		/**
		Create corresponding list item and property list
		@param [out] properties Created property list will be stored here. Pass nullptr to avoid property list creation
		@return Created list item
		*/
		virtual IListItem *Create(IPropertyList **properties) = 0;
		virtual IPropertyList *CreatePropertyList(IListItem *listitem) = 0; // Create properties for specified list item
		virtual void Save(Variant &dest, IPropertyList *properties) = 0; // Save properties into Variant
		virtual void Load(const Variant &src, IPropertyList *properties) = 0; // Load properties from Variant
		virtual void Load(const String &src, IPropertyList *properties) = 0; // Load properties from JSON decoded string
		/**
		Should output properties as c++ code
		@param f File stream
		@param shift Just a spaces for good code alignment. Add it to output
		@param owner Component/Control name which owns the list items
		@param properties Property list
		*/
		virtual void Export(std::wofstream &f, const String &shift, const String &owner, IPropertyList *properties) = 0;
	};
}
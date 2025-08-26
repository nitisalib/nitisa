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
	class IProperty;
	class IPackage;
	class IPackageEntity;

	class IPropertyList
	{
	protected:
		IPropertyList() = default;
		~IPropertyList() = default;
		IPropertyList(const IPropertyList &other) = delete;
		IPropertyList(IPropertyList &&other) = delete;
		IPropertyList &operator=(const IPropertyList &other) = delete;
		IPropertyList &operator=(IPropertyList &&other) = delete;
	public:
		virtual IPackage *getPackage() = 0; // Return package
		virtual IClass *getParent() = 0; // Return owner
		virtual int getCount() = 0; // Return property count
		virtual IProperty *getProperty(const int index) = 0; // Return property by index
		virtual IProperty *getProperty(const String &name) = 0; // Return property by name
		virtual IPackageEntity *getEntity() = 0; // Return package entity whose property list is it

		virtual void setParent(IClass *parent, IPackageEntity *entity) = 0; // Set owner

		virtual void Release() = 0; // Destroy instance
		virtual void Save(Variant &dest) = 0; // Save properties to Variant
		virtual void Load(const Variant &src) = 0; // Load properties from Variant
		/**
		Should output properties initialization as c++ code(like setColor({255, 0, 0, 55});).
		@param f File stream
		@param shift Just a spaces for good code alignment. Add it to output
		@param owner Control/Component/Form name
		*/
		virtual void Export(std::wofstream &f, const String &shift, const String &owner) = 0;
	};
}
// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	class IClass;
	class IProperty;
	class IPropertyList;

	namespace ide
	{
		class IPropertyEditor :public virtual IControl
		{
		protected:
			IPropertyEditor() = default;
			~IPropertyEditor() = default;
			IPropertyEditor(const IPropertyEditor &other) = delete;
			IPropertyEditor(IPropertyEditor &&other) = delete;
			IPropertyEditor &operator=(const IPropertyEditor &other) = delete;
			IPropertyEditor &operator=(IPropertyEditor &&other) = delete;
		public:
			void(*OnPropertyChange)(IPropertyEditor *sender, IProperty *property, IPropertyList *property_list, IClass *parent); // Event called when property has been changed

			virtual int getPropertyListCount() = 0; // Return count of assigned property lists
			virtual IPropertyList *getPropertyList(const int index) = 0; // Return property list by index
			virtual int getPropertyCount() = 0; // Return count of common properties for all attached property lists
			virtual IProperty *getProperty(const int index) = 0; // Return property by index
			virtual int getActivePropertyIndex() = 0; // Return index of active property

			virtual bool AttachPropertyList(IPropertyList *list) = 0; // Attach property list
			virtual bool DetachPropertyList(const int index) = 0; // Detach property list by index
			virtual bool DetachPropertyList(IPropertyList *list) = 0; // Detach property list
			virtual bool DetachPropertyLists() = 0; // Detach all property lists
		};
	}
}
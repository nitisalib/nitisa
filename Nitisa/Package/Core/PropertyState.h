// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../Interfaces/IPropertyState.h"
#include "ExportPrefixType.h"
#include "Property.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class IClass;
	class IPropertyList;

	class CPropertyState :public virtual IPropertyState, public CProperty
	{
	private:
		StringArray m_aStates;
		ExportPrefixType m_eStatePrefixType;
		String m_sStatePrefix;
	public:
		int getStateCount() override;
		String getState(const int index) override;
		ExportPrefixType getStatePrefixType() override;
		String getStatePrefix() override;

		CPropertyState(
			IPropertyList *list, // List of properties to which this property belongs
			IClass *parent, // Parent object which property this one describes
			const String &name, // Property name
			const String &handler, // Property handler name
			FSkip skip, // Function checking if the property could be skipped when saving in Form Builder. Could be nullptr
			const bool read_only, // Whether the property is read only
			const StringArray &states, // List of state names
			const ExportPrefixType state_prefix_type, // Type of prefix which should be added to state name when exporting into form prototype header file
			const String &state_prefix); // Additional prefix which should be added to state name when exporting into form prototype header file
	};
}
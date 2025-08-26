// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/PropertyLists/ControlPropertyList.h"
#include "../../../Controls/EventEditor/EventEditor.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace ide
	{
		class CEventEditorPropertyList :public CControlPropertyList
		{
		private:
			static StringArray EventStates();
			static CEventEditor::EventState StringToEventState(const String &state);
		public:
			CEventEditorPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}
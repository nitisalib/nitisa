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
#include "../../../Controls/PropertyEditor/PropertyEditor.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace ide
	{
		class CPropertyEditorPropertyList :public CControlPropertyList
		{
		private:
			static StringArray FolderStates();
			static CPropertyEditor::FolderState StringToFolderState(const String &state);
			static StringArray PropertyStates();
			static CPropertyEditor::PropertyState StringToPropertyState(const String &state);
		public:
			CPropertyEditorPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}
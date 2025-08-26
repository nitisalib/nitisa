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
#include "../../../Controls/ImageListEditor/ImageListEditor.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CImageListEditorPropertyList :public CControlPropertyList
		{
		private:
			static StringArray StateItems();
			static CImageListEditor::State StringToState(const String &state);
			static StringArray ItemStateItems();
			static CImageListEditor::ItemState StringToItemState(const String &state);
		public:
			CImageListEditorPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}
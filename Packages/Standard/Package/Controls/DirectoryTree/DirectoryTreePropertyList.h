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
#include "../../../Controls/DirectoryTree/DirectoryTree.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CDirectoryTreePropertyList :public CControlPropertyList
		{
		private:
			static StringArray StateItems();
			static CDirectoryTree::State StringToState(const String &state);
			static StringArray FolderStateItems();
			static CDirectoryTree::FolderState StringToFolderState(const String &state);
		public:
			CDirectoryTreePropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}
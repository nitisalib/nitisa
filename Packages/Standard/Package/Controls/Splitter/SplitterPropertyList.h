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
#include "../../../Controls/Splitter/Splitter.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CSplitterPropertyList :public CControlPropertyList
		{
		private:
			static StringArray StateItems();
			static CSplitter::State StringToState(const String &state);
		public:
			CSplitterPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}
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
#include "../../../Controls/BitBtn/BitBtn.h"
#include "../../../Controls/IBitBtn.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CBitBtnPropertyList :public CControlPropertyList
		{
		private:
			static StringArray StateItems();
			static CBitBtn::State StringToState(const String &state);
			static StringArray KindItems();
			static String KindToString(const IBitBtn::Kind value);
			static IBitBtn::Kind StringToKind(const String &state);
		public:
			CBitBtnPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}
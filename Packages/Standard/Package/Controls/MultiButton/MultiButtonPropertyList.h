// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/PropertyLists/ControlPropertyList.h"
#include "../../../Controls/MultiButton/MultiButton.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CMultiButtonPropertyList :public CControlPropertyList
		{
		private:
			static StringArray StateItems();
			static CMultiButton::State StringToState(const String &state);

			static StringArray OpenDirectionItems();
			static String OpenDirectionToString(const CMultiButton::OpenDirection state);
			static CMultiButton::OpenDirection StringToOpenDirection(const String &state);

			static StringArray ImageSizeItems();
			static String ImageSizeToString(const CMultiButton::ImageSize state);
			static CMultiButton::ImageSize StringToImageSize(const String &state);
		public:
			CMultiButtonPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}
// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace standard
	{
		CListItemSelectCategory::CListItemSelectCategory() :
			CListItemLabel()
		{
			setEnabled(false);
			for (int i = 0; i <= (int)State::Disabled; i++)
				setColor((State)i, Color{ 0, 0, 0, 0 });
		}

		CListItemSelectCategory::CListItemSelectCategory(const String &caption) :
			CListItemLabel(caption)
		{
			setEnabled(false);
			for (int i = 0; i <= (int)State::Disabled; i++)
				setColor((State)i, Color{ 0, 0, 0, 0 });
		}

		IFont *CListItemSelectCategory::getFont()
		{
			if (QueryService()->getOwner() && cast<ISelect*>(QueryService()->getOwner()->getControl()))
				return cast<ISelect*>(QueryService()->getOwner()->getControl())->getCategoryFont();
			return nullptr;
		}

		bool CListItemSelectCategory::setVisible(const bool value)
		{
			return false;
		}
	}
}
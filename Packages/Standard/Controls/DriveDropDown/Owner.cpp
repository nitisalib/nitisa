// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
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
		CDriveDropDown::COwner::COwner(CDropDown *dropdown, CDriveDropDown *drivedropdown) :
			CBuiltInDropDownListItemOwner(dropdown),
			m_pDropDown{ drivedropdown }
		{

		}

		ITexture * CDriveDropDown::COwner::getIcon(IListItemIcon *item, RectF &part)
		{
			if (m_pDropDown->getForm() && m_pDropDown->getForm()->getRenderer())
			{
				if (m_pDropDown->getStyle())
				{
					IStyleSkin *skin{ m_pDropDown->getStyle()->getSkin(m_pDropDown->m_sClassName + L".Icon") };
					if (skin && skin->getImage())
					{
						part = skin->Rect;
						return m_pDropDown->getForm()->getRenderer()->CreateTextureFromImage(skin->getImage()->Image, 1, TextureFormat::RGBA, true);
					}
				}
				if (Application->Styles->getStyle(0))
				{
					IStyleSkin *skin{ Application->Styles->getStyle(0)->getSkin(m_pDropDown->m_sClassName + L".Icon") };
					if (skin && skin->getImage())
					{
						part = skin->Rect;
						return m_pDropDown->getForm()->getRenderer()->CreateTextureFromImage(skin->getImage()->Image, 1, TextureFormat::RGBA, true);
					}
				}
			}
			return nullptr;
		}
	}
}
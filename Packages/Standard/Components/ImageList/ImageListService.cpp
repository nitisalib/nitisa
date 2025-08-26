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
	#pragma region Constructor & destructor
		CImageListService::CImageListService(CImageList *image_list) :
			CComponentService(image_list),
			m_pImageList{ image_list }
		{

		}
	#pragma endregion

	#pragma region State change notifications
		void CImageListService::NotifyOnFreeResources()
		{
			for (auto pos = m_pImageList->m_aItems.begin(); pos != m_pImageList->m_aItems.end(); pos++)
				if (pos->Texture)
				{
					pos->Texture->Release();
					pos->Texture = nullptr;
				}
		}
	#pragma endregion
	}
}
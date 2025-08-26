// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ComponentService.h"

namespace nitisa
{
	namespace standard
	{
		class CImageList;

		class CImageListService :public CComponentService
		{
		private:
			CImageList *m_pImageList;
		public:
			CImageListService(CImageList *image_list);

			// State change notifications
			void NotifyOnFreeResources() override;
		};
	}
}
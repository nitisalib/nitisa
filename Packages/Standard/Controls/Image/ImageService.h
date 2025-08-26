// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ControlService.h"
#include "Nitisa/Core/Messages.h"

namespace nitisa
{
	namespace standard
	{
		class CImage;

		class CImageService :public CControlService
		{
		private:
			CImage *m_pImage;
		public:
			CImageService(CImage *image);

			// Notifications from parent control
			void NotifyOnParentStyleChange() override;

			// State change notifications
			void NotifyOnFreeResources() override;
			void NotifyOnStyleChange() override;
			void NotifyOnResize() override;

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;
		};
	}
}
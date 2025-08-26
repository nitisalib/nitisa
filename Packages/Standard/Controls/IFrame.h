// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	namespace standard
	{
		class IFrame :public virtual IControl
		{
		protected:
			IFrame() = default;
			~IFrame() = default;
			IFrame(const IFrame &other) = delete;
			IFrame(IFrame &&other) = delete;
			IFrame &operator=(const IFrame &other) = delete;
			IFrame &operator=(IFrame &&other) = delete;
		public:
			virtual String getCaption() = 0; // Return caption
			virtual bool isMinimizable() = 0; // Whether can be minimized
			virtual bool isMaximizable() = 0; // Whether can be maximized(align = client) and restored
			virtual bool isClosable() = 0; // Whether can be closed by user(has close button)
			virtual bool isResizable() = 0; // Whether can be resized by user
			virtual bool isMovable() = 0; // Whether can be moved by user
			virtual bool isMinimized() = 0; // Whether is minimized
			virtual bool isMaximized() = 0; // Whether is maximized

			virtual bool setCaption(const String &value) = 0; // Set caption
			virtual bool setMinimizable(const bool value) = 0; // Set whether can be minimized by user
			virtual bool setMaximizable(const bool value) = 0; // Set whether can be maximized by user
			virtual bool setClosable(const bool value) = 0; // Set whether can be closed by user
			virtual bool setResizable(const bool value) = 0; // Set whether can be resized by user
			virtual bool setMovable(const bool value) = 0; // Set whether can be moved by user

			virtual bool Show() = 0; // Show
			virtual bool ShowModal() = 0; // Show in modal state
			virtual bool Hide() = 0; // Hide
			virtual bool Minimize() = 0; // Minimize
			virtual bool Maximize() = 0; // Maximize
			virtual bool Restore() = 0; // Restore
		};
	}
}
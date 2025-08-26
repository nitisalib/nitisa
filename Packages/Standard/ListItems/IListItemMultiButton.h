// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IListItemCaption.h"

namespace nitisa
{
	namespace standard
	{
		class IListItemMultiButton :public virtual IListItemCaption
		{
		protected:
			IListItemMultiButton() = default;
			~IListItemMultiButton() = default;
			IListItemMultiButton(const IListItemMultiButton &other) = delete;
			IListItemMultiButton(IListItemMultiButton &&other) = delete;
			IListItemMultiButton &operator=(const IListItemMultiButton &other) = delete;
			IListItemMultiButton &operator=(IListItemMultiButton &&other) = delete;
		public:
			virtual int getImageIndex() const = 0; // Return image index

			virtual bool setImageIndex(const int value) = 0; // Set image index
		};
	}
}
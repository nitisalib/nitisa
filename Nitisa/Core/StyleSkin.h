// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IStyleSkin.h"
#include "../Math/RectF.h"
#include "Strings.h"

namespace nitisa
{
	class IStyleImage;

	class CStyleSkin :public virtual IStyleSkin
	{
	private:
		IStyleImage *m_pImage;
	public:
		IStyleImage *getImage() override;

		CStyleSkin(const String &name, IStyleImage *image, const RectF &rect);
		virtual ~CStyleSkin() = default;
	};
}
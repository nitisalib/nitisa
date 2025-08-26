// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

/*
	This styles are ready to be used as base classes. All deletes and modifiable properties are protected members
*/
#pragma once

#include "../Interfaces/IStyles.h"
#include "Strings.h"
#include <vector>

namespace nitisa
{
	class IStyle;

	class CStyles :public virtual IStyles
	{
	private:
		struct STYLE
		{
			String Package;
			IStyle *Style;
		};

		std::vector<STYLE> m_aStyles;
	public:
		int getStyleCount() override;
		IStyle *getStyle(const int index) override;
		IStyle *getStyle(const String &class_name) override;
		IStyle *getStyle(const String &package, const String &class_name) override;

		bool Add(IStyle *style) override;
		bool Add(const String &package, IStyle *style) override;

		~CStyles();
	};
}
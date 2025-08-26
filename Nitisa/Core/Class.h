// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IClass.h"
#include "Strings.h"

namespace nitisa
{
	class CClass :public virtual IClass
	{
	public:
		CClass(const String &class_name) // Create with specified class name
		{
			m_sClassName = class_name;
		}

		virtual ~CClass() = default;
	};
}
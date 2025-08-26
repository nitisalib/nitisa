// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"

namespace nitisa
{
	class IClass
	{
	protected:
		IClass() = default;
		~IClass() = default;
		IClass(const IClass &other) = delete;
		IClass(IClass &&other) = delete;
		IClass &operator=(const IClass &other) = delete;
		IClass &operator=(IClass &&other) = delete;
	protected:
		String m_sClassName;
		String m_sName;
	public:
		String const &ClassName{ m_sClassName }; // Class name
		String const &Name{ m_sName }; // Name

		virtual bool setName(const String &value) = 0; // Set name
	};
}
// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Version2.h"
#include "IReleasable.h"

namespace nitisa
{
	class INativeGraphics : public virtual IReleasable
	{
	protected:
		INativeGraphics() = default;
		~INativeGraphics() = default;
		INativeGraphics(const INativeGraphics &other) = delete;
		INativeGraphics(INativeGraphics &&other) = delete;
		INativeGraphics &operator=(const INativeGraphics &other) = delete;
		INativeGraphics &operator=(INativeGraphics &&other) = delete;
	protected:
		Version2 m_sVersion;
	public:
		const Version2 &Version{ m_sVersion }; // Version
	};
}
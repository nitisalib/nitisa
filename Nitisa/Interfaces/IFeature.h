// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "IReleasable.h"

namespace nitisa
{
	class IFeature :public virtual IReleasable
	{
	protected:
		IFeature() = default;
		~IFeature() = default;
		IFeature(const IFeature &other) = delete;
		IFeature(IFeature &&other) = delete;
		IFeature &operator=(const IFeature &other) = delete;
		IFeature &operator=(IFeature &&other) = delete;
	protected:
		String m_sName; // Name
	public:
		String const &Name{ m_sName }; // Name
	};
}
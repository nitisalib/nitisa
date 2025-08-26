// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "IModel.h"

namespace nitisa
{
	class IPrimitive :public virtual IModel
	{
	protected:
		IPrimitive() = default;
		~IPrimitive() = default;
		IPrimitive(const IPrimitive &other) = delete;
		IPrimitive(IPrimitive &&other) = delete;
		IPrimitive &operator=(const IPrimitive &other) = delete;
		IPrimitive &operator=(IPrimitive &&other) = delete;
	public:
		virtual bool Render() = 0; // Render primitive
	};
}
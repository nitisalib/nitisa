// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IFeature.h"
#include "Releasable.h"
#include "Strings.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class CFeature :public virtual IFeature, public CReleasable
	{
	protected:
		CFeature(const String &name);
	};
}
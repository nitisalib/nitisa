// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/BuiltInControl.h"
#include "../../Core/Strings.h"
#include "../Interfaces/IPropertyHandler.h"

namespace nitisa
{
	class IControl;
	class IPackage;

	class CPropertyHandler :public virtual IPropertyHandler, public CBuiltInControl
	{
	private:
		IControl *m_pControl;
		IPackage *m_pPackage;
	public:
		IControl *getControl() override;
		IPackage *getPackage() override;

		bool setControl(IControl *value) override;

		CPropertyHandler(IPackage *package, const String &name);
	};
}
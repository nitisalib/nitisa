// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IComponent.h"

namespace nitisa
{
	namespace standard
	{
		class IAdminRights :public virtual IComponent
		{
		protected:
			IAdminRights() = default;
			~IAdminRights() = default;
			IAdminRights(const IAdminRights &other) = delete;
			IAdminRights(IAdminRights &&other) = delete;
			IAdminRights &operator=(const IAdminRights &other) = delete;
			IAdminRights &operator=(IAdminRights &&other) = delete;
		public:
			virtual bool hasAdminRights() = 0; // Return true if application already has admin rights

			virtual bool Request(const String &params = L"") = 0; // Ask for admin rights. If application already has admin rights, return false. If user denies running with admin rights, return false. If user allows running with admin rights, run new instance of application and terminate this one
		};
	}
}
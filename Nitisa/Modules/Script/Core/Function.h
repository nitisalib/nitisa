// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Releasable.h"
#include "../Interfaces/IFunction.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class IErrorListener;

	namespace script
	{
		class CFunction :public virtual IFunction, public virtual CReleasable
		{
		protected:
			~CFunction() = default;
			CFunction(const CFunction &other) = delete;
			CFunction(CFunction &&other) = delete;
			CFunction &operator=(const CFunction &other) = delete;
			CFunction &operator=(CFunction &&other) = delete;
		protected:
			IErrorListener *m_pErrorListener; // Error listener

			CFunction(const String &name, IErrorListener *error_listener); // Constructor
		public:

		};
	}
}
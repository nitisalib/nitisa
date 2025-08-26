// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Strings.h"
#include "../../../Interfaces/IReleasable.h"
#include <vector>

namespace nitisa
{
	namespace script
	{
		class Variable;

		class IFunction :public virtual IReleasable
		{
		public:
			using Arguments = std::vector<IFunction*>;
		protected:
			IFunction() = default;
			~IFunction() = default;
			IFunction(const IFunction &other) = delete;
			IFunction(IFunction &&other) = delete;
			IFunction &operator=(const IFunction &other) = delete;
			IFunction &operator=(IFunction &&other) = delete;
		protected:
			String m_sName;
			Variable *m_pResult;
		public:
			String const &Name{ m_sName }; // Function name
			Variable* &Result{ m_pResult }; // Function execution result

			virtual bool Run() = 0; // Execute function
		};
	}
}
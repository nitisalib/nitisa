// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Function.h"
#include "../../Core/Variable.h"
#include <random>

namespace nitisa
{
	class IErrorListener;

	namespace script
	{
		class IFunction;

		class CFunctionRand :public CFunction
		{
		private:
			Variable m_sResult;
			IFunction *m_pOperand1;
			IFunction *m_pOperand2;
			std::default_random_engine m_cEngine;
		protected:
			void BeforeRelease() override;
		public:
			// IFunction methods
			bool Run() override;

			CFunctionRand(IErrorListener *error_listener, IFunction *operand1, IFunction *operand2);
		};
	}
}
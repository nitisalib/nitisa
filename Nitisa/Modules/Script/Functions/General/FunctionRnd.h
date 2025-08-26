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
		class CFunctionRnd :public virtual CFunction
		{
		private:
			Variable m_sResult;
			std::default_random_engine m_cEngine;
			std::uniform_real_distribution<double> m_cDistribution;
		public:
			// IFunction methods
			bool Run() override;

			CFunctionRnd(IErrorListener *error_listener);
		};
	}
}
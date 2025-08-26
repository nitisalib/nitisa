// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Utils.h"

namespace nitisa
{
	namespace ai
	{
		template<class FLOAT>
		class IRegularizeFunction
		{
		public:
			virtual FLOAT Output(const FLOAT value) = 0; // Calculate output
			virtual FLOAT Derivative(const FLOAT value) = 0; // Calculate derivative value
			virtual bool IsDead(const FLOAT weight, const FLOAT new_weight) = 0; // Whether weight is not used anymore
		};

		namespace regularizers
		{
			template<class FLOAT>
			class TL1 :public IRegularizeFunction<FLOAT>
			{
			public:
				FLOAT Output(const FLOAT value) override
				{
					return ntl::Abs<FLOAT>(value);
				}

				FLOAT Derivative(const FLOAT value) override
				{
					return ntl::Sign<FLOAT>(value);
				}

				bool IsDead(const FLOAT weight, const FLOAT new_weight) override
				{
					return weight * new_weight < 0;
				}
			};

			template<class FLOAT>
			class TL2 :public IRegularizeFunction<FLOAT>
			{
			public:
				FLOAT Output(const FLOAT value) override
				{
					return value * value / 2;
				}

				FLOAT Derivative(const FLOAT value) override
				{
					return value;
				}

				bool IsDead(const FLOAT weight, const FLOAT new_weight) override
				{
					return false;
				}
			};
		}
	}
}
// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Activators.h"

namespace nitisa
{
	namespace ai
	{
		template<class FLOAT>
		class IErrorFunction
		{
		public:
			virtual FLOAT Error(const FLOAT output, const FLOAT expected, const FLOAT amount, IActivator<FLOAT> *activator) = 0; // Calculate error function value
			virtual FLOAT Derivative(const FLOAT output, const FLOAT expected, const FLOAT amount, IActivator<FLOAT> *activator) = 0; // Calculate value of derivative of error function
		};

		namespace errors
		{
			template<class FLOAT>
			class TQuadratic :public IErrorFunction<FLOAT>
			{
			public:
				FLOAT Error(const FLOAT output, const FLOAT expected, const FLOAT amount, IActivator<FLOAT> *activator) override
				{
					return (output - expected) * (output - expected) / 2;
				}

				FLOAT Derivative(const FLOAT output, const FLOAT expected, const FLOAT amount, IActivator<FLOAT> *activator) override
				{
					return (output - expected) * activator->Derivative(amount);
				}
			};

			template<class FLOAT>
			class TCrossEntropy :public IErrorFunction<FLOAT>
			{
			public:
				FLOAT Error(const FLOAT output, const FLOAT expected, const FLOAT amount, IActivator<FLOAT> *activator) override
				{
					if (output <= 0 || output >= 1)
						return 0;
					return -expected * std::log(output) - (1 - expected) * std::log(1 - output);
				}

				FLOAT Derivative(const FLOAT output, const FLOAT expected, const FLOAT amount, IActivator<FLOAT> *activator) override
				{
					return output - expected;
				}
			};
		}
	}
}
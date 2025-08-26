// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Utils.h"
#include <cmath>

namespace nitisa
{
	namespace ai
	{
		template<class TYPE>
		class IActivator
		{
		public:
			virtual TYPE Calculate(const TYPE value) = 0; // Calculate activation function value in specified location
			virtual TYPE Derivative(const TYPE value) = 0; // Calculate derivative value of activation function in specified location
		};

		namespace activators
		{
			// Return scaled and shifted value(r = a * x + b)
			template<class TYPE>
			class TLinear : public IActivator<TYPE>
			{
			private:
				TYPE m_fBias;
				TYPE m_fScale;
			public:
				TLinear(const TYPE bias, const TYPE scale) :
					m_fBias{ bias },
					m_fScale{ scale }
				{

				}

				TYPE Calculate(const TYPE value) override
				{
					return m_fBias + m_fScale * value;
				}

				TYPE Derivative(const TYPE value) override
				{
					return m_fScale;
				}
			};

			// Return either "ifless_value" or "ifgreater_value" depending whether value if less then "threshold" or otherwise
			template<class TYPE>
			class TThreshold : public IActivator<TYPE>
			{
			private:
				TYPE m_fThreshold;
				TYPE m_fMin;
				TYPE m_fMax;
			public:
				TThreshold(const TYPE threshold, const TYPE ifless_value, const TYPE ifgreater_value) :
					m_fThreshold{ threshold },
					m_fMin{ ifless_value },
					m_fMax{ ifgreater_value }
				{

				}

				TYPE Calculate(const TYPE value) override
				{
					return (value < m_fThreshold) ? m_fMin : m_fMax;
				}

				TYPE Derivative(const TYPE value) override
				{
					return 0;
				}
			};

			// Sigmoid. Return in range [0..1]
			template<class FLOAT>
			class TLogistic : public IActivator<FLOAT>
			{
			private:
				FLOAT m_fGain;
			public:
				TLogistic(const FLOAT gain) :
					m_fGain{ gain }
				{

				}

				FLOAT Calculate(const FLOAT value) override
				{
					return 1 / (1 + std::exp(-m_fGain * value));
				}

				FLOAT Derivative(const FLOAT value) override
				{
					FLOAT v{ Calculate(value) };
					return m_fGain * v * (1 - v);
				}
			};

			// Transformed(shifted and scaled) sigmoid. Return in range [bias..scale + bias]
			template<class FLOAT>
			class TLogisticEx : public IActivator<FLOAT>
			{
			private:
				FLOAT m_fGain;
				FLOAT m_fScale;
				FLOAT m_fBias;
			public:
				TLogisticEx(const FLOAT gain, const FLOAT scale, const FLOAT bias) :
					m_fGain{ gain },
					m_fScale{ scale },
					m_fBias{ bias }
				{

				}

				FLOAT Calculate(const FLOAT value) override
				{
					return m_fScale / (1 + std::exp(-m_fGain * value)) + m_fBias;
				}

				FLOAT Derivative(const FLOAT value) override
				{
					FLOAT v{ 1 / (1 + std::exp(-m_fGain * value)) };
					return m_fGain * v * (1 - v) * m_fScale;
				}
			};

			// Tanh. Return in range [-1..+1]
			template<class FLOAT>
			class THyperTan : public IActivator<FLOAT>
			{
			private:
				FLOAT m_fGain;
			public:
				THyperTan(const FLOAT gain) :
					m_fGain{ gain }
				{

				}

				FLOAT Calculate(const FLOAT value) override
				{
					return std::tanh(m_fGain * value);
				}

				FLOAT Derivative(const FLOAT value) override
				{
					FLOAT v{ Calculate(value) };
					return m_fGain * (1 - v * v);
				}
			};

			// Transformed Tanh(shifted and scaled). Return in range [-scale + bias..scale + bias]
			template<class FLOAT>
			class THyperTanEx : public IActivator<FLOAT>
			{
			private:
				FLOAT m_fGain;
				FLOAT m_fScale;
				FLOAT m_fBias;
			public:
				THyperTanEx(const FLOAT gain, const FLOAT scale, const FLOAT bias) :
					m_fGain{ gain },
					m_fScale{ scale },
					m_fBias{ bias }
				{

				}

				FLOAT Calculate(const FLOAT value) override
				{
					return std::tanh(m_fGain * value) * m_fScale + m_fBias;
				}

				FLOAT Derivative(const FLOAT value) override
				{
					FLOAT v{ std::tanh(m_fGain * value) };
					return m_fGain * (1 - v * v) * m_fScale;
				}
			};

			template<class FLOAT>
			class TSoftSign : public IActivator<FLOAT>
			{
			public:
				FLOAT Calculate(const FLOAT value) override
				{
					return value / (1  + ntl::Abs<FLOAT>(value));
				}

				FLOAT Derivative(const FLOAT value) override
				{
					return 1 / std::pow(1 + ntl::Abs<FLOAT>(value), 2);
				}
			};

			template<class FLOAT>
			class TSoftPlus: public IActivator<FLOAT>
			{
			public:
				FLOAT Calculate(const FLOAT value) override
				{
					return std::log(1 + std::exp(value));
				}

				FLOAT Derivative(const FLOAT value) override
				{
					return 1 / (1 + std::exp(-value));
				}
			};

			template<class FLOAT>
			class TRelu : public IActivator<FLOAT>
			{
			public:
				FLOAT Calculate(const FLOAT value) override
				{
					return ntl::Max<FLOAT>(0, value);
				}

				FLOAT Derivative(const FLOAT value) override
				{
					return (value < 0) ? 0 : 1;
				}
			};

			template<class FLOAT>
			class TLeakyRelu : public IActivator<FLOAT>
			{
			private:
				FLOAT m_fA;
			public:
				TLeakyRelu(const FLOAT a) :
					m_fA{ a }
				{

				}

				FLOAT Calculate(const FLOAT value) override
				{
					return (value < 0) ? (m_fA * value) : value;
				}

				FLOAT Derivative(const FLOAT value) override
				{
					return (value < 0) ? m_fA : 1;
				}
			};

			template<class FLOAT>
			class TElu : public IActivator<FLOAT>
			{
			private:
				FLOAT m_fA;
			public:
				TElu(const FLOAT a) :
					m_fA{ a }
				{

				}

				FLOAT Calculate(const FLOAT value) override
				{
					return (value < 0) ? (m_fA * (std::exp(value) - 1)) : value;
				}

				FLOAT Derivative(const FLOAT value) override
				{
					return (value < 0) ? (Calculate(value) + m_fA) : 1;
				}
			};
		}
	}
}
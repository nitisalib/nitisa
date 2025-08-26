// This file is a part of Nitisa framework
// Copyright © 2018 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include <random>
#include <chrono>

namespace nitisa
{
	namespace ai
	{
		template<class TYPE>
		class IRandomizer
		{
		public:
			virtual TYPE Generate() = 0; // Return random value
		};

		namespace randomizers
		{
			template<class INTEGER>
			class TDefaultInteger : public IRandomizer<INTEGER>
			{
			private:
				INTEGER m_iMin;
				INTEGER m_iMax;
				std::default_random_engine m_cEngine;
				std::uniform_int_distribution<INTEGER> m_cDistribution;
			public:
				TDefaultInteger(const INTEGER min, const INTEGER max) :
					m_iMin{ min },
					m_iMax{ max },
					m_cDistribution{ m_iMin, m_iMax }
				{
					
				}

				TDefaultInteger(const INTEGER min, const INTEGER max, const unsigned int seed) :
					m_iMin{ min },
					m_iMax{ max },
					m_cEngine{ seed },
					m_cDistribution{ m_iMin, m_iMax }
				{
					
				}

				INTEGER Generate() override
				{
					return m_cDistribution(m_cEngine);
				}

				void setSeed(const unsigned int value)
				{
					m_cEngine.seed(value);
				}

				void setRandomSeed()
				{
					auto now{ std::chrono::system_clock::now() };
					std::chrono::milliseconds duration{ std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) };
					m_cEngine.seed((unsigned int)duration.count());
				}
			};

			template<class FLOAT>
			class TDefaultFloat : public IRandomizer<FLOAT>
			{
			private:
				FLOAT m_fMin;
				FLOAT m_fMax;
				std::default_random_engine m_cEngine;
				std::uniform_real_distribution<FLOAT> m_cDistribution;
			public:
				TDefaultFloat(const FLOAT min, const FLOAT max) :
					m_fMin{ min },
					m_fMax{ max },
					m_cDistribution{ m_fMin, m_fMax }
				{
					
				}

				TDefaultFloat(const FLOAT min, const FLOAT max, const unsigned int seed) :
					m_fMin{ min },
					m_fMax{ max },
					m_cEngine{ seed },
					m_cDistribution{ m_fMin, m_fMax }
				{
					
				}

				FLOAT Generate() override
				{
					return m_cDistribution(m_cEngine);
				}

				void setSeed(const unsigned int value)
				{
					m_cEngine.seed(value);
				}

				void setRandomSeed()
				{
					auto now{ std::chrono::system_clock::now() };
					std::chrono::milliseconds duration{ std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) };
					m_cEngine.seed((unsigned int)duration.count());
				}
			};

			template<class FLOAT>
			class TGauss : public IRandomizer<FLOAT>
			{
			private:
				FLOAT m_fMean;
				FLOAT m_fSigma;
				std::default_random_engine m_cEngine;
				std::normal_distribution<FLOAT> m_cDistribution;
			public:
				TGauss(const FLOAT mean = 0, const FLOAT sigma = 1) :
					m_cDistribution{ mean, sigma }
				{

				}

				TGauss(const FLOAT mean, const FLOAT sigma, const unsigned int seed) :
					m_cEngine{ seed },
					m_cDistribution{ mean, sigma }
				{

				}

				FLOAT Generate() override
				{
					return m_cDistribution(m_cEngine);
				}

				void setParams(const FLOAT mean, const FLOAT sigma)
				{
					m_cDistribution.param(std::normal_distribution<FLOAT>::param_type(mean, sigma));
					m_fMean = mean;
					m_fSigma = sigma;
				}

				void setSeed(const unsigned int value)
				{
					m_cEngine.seed(value);
				}

				void setRandomSeed()
				{
					auto now{ std::chrono::system_clock::now() };
					std::chrono::milliseconds duration{ std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) };
					m_cEngine.seed((unsigned int)duration.count());
				}
			};
		}
	}
}
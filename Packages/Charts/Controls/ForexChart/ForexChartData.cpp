// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace charts
	{
	#pragma region Constructor & destructor
		CForexChart::CForexChartData::CForexChartData()
		{

		}

		CForexChart::CForexChartData::CForexChartData(const std::vector<ChartData> &data) :
			m_aData{ data }
		{

		}

		void CForexChart::CForexChartData::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Getters
		int CForexChart::CForexChartData::getCount()
		{
			return (int)m_aData.size();
		}

		const CDateTime &CForexChart::CForexChartData::getDateTime(const int index) const
		{
			if (index >= 0 && index < (int)m_aData.size())
				return m_aData[index].DateTime;
			return m_sNow;
		}

		float CForexChart::CForexChartData::getOpen(const int index)
		{
			if (index >= 0 && index < (int)m_aData.size())
				return m_aData[index].Open;
			return 0;
		}

		float CForexChart::CForexChartData::getClose(const int index)
		{
			if (index >= 0 && index < (int)m_aData.size())
				return m_aData[index].Close;
			return 0;
		}

		float CForexChart::CForexChartData::getMin(const int index)
		{
			if (index >= 0 && index < (int)m_aData.size())
				return m_aData[index].Min;
			return 0;
		}

		float CForexChart::CForexChartData::getMax(const int index)
		{
			if (index >= 0 && index < (int)m_aData.size())
				return m_aData[index].Max;
			return 0;
		}

		String CForexChart::CForexChartData::getXLabel(const double x, const String &default_label)
		{
			return default_label;
		}

		String CForexChart::CForexChartData::getYLabel(const double y, const String &default_label)
		{
			return default_label;
		}
	#pragma endregion

	#pragma region Setters
		bool CForexChart::CForexChartData::setDateTime(const int index, const CDateTime &value)
		{
			if (index >= 0 && index < (int)m_aData.size())
			{
				m_aData[index].DateTime = value;
				return true;
			}
			return false;
		}

		bool CForexChart::CForexChartData::setOpen(const int index, const float value)
		{
			if (index >= 0 && index < (int)m_aData.size())
			{
				m_aData[index].Open = value;
				return true;
			}
			return false;
		}

		bool CForexChart::CForexChartData::setClose(const int index, const float value)
		{
			if (index >= 0 && index < (int)m_aData.size())
			{
				m_aData[index].Close = value;
				return true;
			}
			return false;
		}

		bool CForexChart::CForexChartData::setMin(const int index, const float value)
		{
			if (index >= 0 && index < (int)m_aData.size())
			{
				m_aData[index].Min = value;
				return true;
			}
			return false;
		}

		bool CForexChart::CForexChartData::setMax(const int index, const float value)
		{
			if (index >= 0 && index < (int)m_aData.size())
			{
				m_aData[index].Max = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		IForexChart::IForexChartData *CForexChart::CForexChartData::Clone()
		{
			return new CForexChartData(m_aData);
		}

		bool CForexChart::CForexChartData::Add(const CDateTime &datetime, const float open, const float close, const float min, const float max)
		{
			m_aData.push_back({ datetime, open, close, min, max });
			return true;
		}

		bool CForexChart::CForexChartData::Delete(const int index)
		{
			if (index >= 0 && index < (int)m_aData.size())
			{
				m_aData.erase(m_aData.begin() + index);
				return true;
			}
			return false;
		}

		bool CForexChart::CForexChartData::Clear()
		{
			if (m_aData.size() > 0)
			{
				m_aData.clear();
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}
// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
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
		CChartDataSet::CChartDataSet()
		{

		}

		CChartDataSet::CChartDataSet(const std::vector<IChartData*> &datas) :
			m_aDatas{ datas }
		{

		}

		CChartDataSet::~CChartDataSet()
		{
			DeleteDatas();
		}

		void CChartDataSet::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Interface getters
		String CChartDataSet::getXLabel(const float x, const String &default_label)
		{
			return default_label;
		}

		String CChartDataSet::getYLabel(const float y, const String &default_label)
		{
			return default_label;
		}

		int CChartDataSet::getDataCount()
		{
			return (int)m_aDatas.size();
		}

		IChartData *CChartDataSet::getData(const int index)
		{
			if (index >= 0 && index < (int)m_aDatas.size())
				return m_aDatas[index];
			return nullptr;
		}
	#pragma endregion

	#pragma region Interface methods
		IChartDataSet *CChartDataSet::Clone()
		{
			CChartDataSet *result{ new CChartDataSet() };
			for (auto data : m_aDatas)
				m_aDatas.push_back(data->Clone());
			return result;
		}

		bool CChartDataSet::AddData(IChartData *data)
		{
			if (!data)
				return false;
			for (auto d : m_aDatas)
				if (d == data)
					return false;
			m_aDatas.push_back(data);
			return true;
		}

		bool CChartDataSet::DetachData(const int index)
		{
			if (index >= 0 && index < (int)m_aDatas.size())
			{
				m_aDatas.erase(m_aDatas.begin() + index);
				return true;
			}
			return false;
		}

		bool CChartDataSet::DetachData(IChartData *data)
		{
			for (auto pos = m_aDatas.begin(); pos != m_aDatas.end(); pos++)
				if (*pos == data)
				{
					m_aDatas.erase(pos);
					return true;
				}
			return false;
		}

		bool CChartDataSet::DeleteData(const int index)
		{
			if (index >= 0 && index < (int)m_aDatas.size())
			{
				m_aDatas[index]->Release();
				m_aDatas.erase(m_aDatas.begin() + index);
				return true;
			}
			return false;
		}

		bool CChartDataSet::DeleteData(IChartData *data)
		{
			for (auto pos = m_aDatas.begin(); pos != m_aDatas.end(); pos++)
				if (*pos == data)
				{
					(*pos)->Release();
					m_aDatas.erase(pos);
					return true;
				}
			return false;
		}

		bool CChartDataSet::DetachDatas()
		{
			if (m_aDatas.size() > 0)
			{
				m_aDatas.clear();
				return true;
			}
			return false;
		}

		bool CChartDataSet::DeleteDatas()
		{
			if (m_aDatas.size() > 0)
			{
				for (auto data : m_aDatas)
					data->Release();
				m_aDatas.clear();
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}
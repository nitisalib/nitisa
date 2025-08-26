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
		CChartData::CChartData(const String name):
			m_sName{ name },
			m_pRenderer{ nullptr }
		{

		}

		CChartData::CChartData(const int size, const float def_x, const float def_y, const String &def_label, const String name) :
			m_sName{ name },
			m_pRenderer{ nullptr }
		{
			if (size > 0)
				m_aPoints.resize(size, POINT{ def_x, def_y, def_label });
		}

		CChartData::CChartData(const std::vector<POINT> &points, const String name):
			m_sName{ name },
			m_aPoints{ points },
			m_pRenderer{ nullptr }
		{

		}

		CChartData::~CChartData()
		{
			if (m_pRenderer)
				m_pRenderer->Release();
		}

		void CChartData::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region Interface getters
		String CChartData::getName()
		{
			return m_sName;
		}

		int CChartData::getCount()
		{
			return (int)m_aPoints.size();
		}

		float CChartData::getX(const int index)
		{
			if (index >= 0 && index < (int)m_aPoints.size())
				return m_aPoints[index].X;
			return 0;
		}

		float CChartData::getY(const int index)
		{
			if (index >= 0 && index < (int)m_aPoints.size())
				return m_aPoints[index].Y;
			return 0;
		}

		String CChartData::getLabel(const int index)
		{
			if (index >= 0 && index < (int)m_aPoints.size())
				return m_aPoints[index].Label;
			return L"";
		}

		IChartRenderer *CChartData::getRenderer()
		{
			return m_pRenderer;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CChartData::setName(const String &value)
		{
			if (value != m_sName)
			{
				m_sName = value;
				return true;
			}
			return false;
		}

		bool CChartData::setX(const int index, const float value)
		{
			if (index >= 0 && index < (int)m_aPoints.size())
			{
				m_aPoints[index].X = value;
				return true;
			}
			return false;
		}

		bool CChartData::setY(const int index, const float value)
		{
			if (index >= 0 && index < (int)m_aPoints.size())
			{
				m_aPoints[index].Y = value;
				return true;
			}
			return false;
		}

		bool CChartData::setLabel(const int index, const String &value)
		{
			if (index >= 0 && index < (int)m_aPoints.size())
			{
				m_aPoints[index].Label = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface methods
		IChartData *CChartData::Clone()
		{
			CChartData *result{ new CChartData(m_aPoints, m_sName) };
			result->m_pRenderer = m_pRenderer;
			return result;
		}

		void CChartData::AddPoint(const float x, const float y, const String &label)
		{
			m_aPoints.push_back(POINT{ x, y, label });
		}

		bool CChartData::DeletePoint(const int index)
		{
			if (index >= 0 && index < (int)m_aPoints.size())
			{
				m_aPoints.erase(m_aPoints.begin() + index);
				return true;
			}
			return false;
		}

		bool CChartData::DeletePoints()
		{
			if (m_aPoints.size() > 0)
			{
				m_aPoints.clear();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CChartData::setPoint(const int index, const POINT &value)
		{
			if (index >= 0 && index < (int)m_aPoints.size())
			{
				m_aPoints[index] = value;
				return true;
			}
			return false;
		}

		bool CChartData::setRenderer(IChartRenderer *value, const bool release_old)
		{
			if (value != m_pRenderer)
			{
				if (m_pRenderer && release_old)
					m_pRenderer->Release();
				m_pRenderer = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Methods
		bool CChartData::Resize(const int size, const float def_x, const float def_y, const String &def_label)
		{
			if (size >= 0 && size != (int)m_aPoints.size())
			{
				m_aPoints.resize(size, POINT{ def_x, def_y, def_label });
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}
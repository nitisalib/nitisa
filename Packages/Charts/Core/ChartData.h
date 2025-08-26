// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "../Interfaces/IChartData.h"
#include <vector>

namespace nitisa
{
	namespace charts
	{
		class IChartRenderer;

		class CChartData :public virtual IChartData
		{
		private:
			struct POINT
			{
				float X;
				float Y;
				String Label;
			};
		private:
			String m_sName;
			std::vector<POINT> m_aPoints;
			IChartRenderer *m_pRenderer;
		public:
			String getName() override;
			int getCount() override;
			float getX(const int index) override;
			float getY(const int index) override;
			String getLabel(const int index) override;
			IChartRenderer *getRenderer() override;

			bool setName(const String &value) override;
			bool setX(const int index, const float value) override;
			bool setY(const int index, const float value) override;
			bool setLabel(const int index, const String &value) override;

			void Release() override;
			IChartData *Clone() override;

			void AddPoint(const float x, const float y, const String &label = L"") override;
			bool DeletePoint(const int index) override;
			bool DeletePoints() override;

			CChartData(const String name = L""); // Create with no data and specified name
			CChartData(const int size, const float def_x = 0, const float def_y = 0, const String &def_label = L"", const String name = L""); // Create with specified name and size where each point has the same specified value
			CChartData(const std::vector<POINT> &points, const String name = L""); // Create with specified name and points
			virtual ~CChartData();

			bool setPoint(const int index, const POINT &value); // Set point data
			bool setRenderer(IChartRenderer *value, const bool release_old); // Assign renderer

			bool Resize(const int size, const float def_x = 0, const float def_y = 0, const String &def_label = L""); // Change size filling new points(if new size is greater than old one) with specified values
		};
	}
}
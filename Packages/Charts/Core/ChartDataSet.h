// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "../Interfaces/IChartDataSet.h"
#include <vector>

namespace nitisa
{
	namespace charts
	{
		class IChartData;

		class CChartDataSet :public virtual IChartDataSet
		{
		private:
			std::vector<IChartData*> m_aDatas;
		public:
			String getXLabel(const float x, const String &default_label) override; // Return default_label
			String getYLabel(const float y, const String &default_label) override; // Return default_label
			int getDataCount() override;
			IChartData *getData(const int index) override;

			void Release() override;
			IChartDataSet *Clone() override;

			bool AddData(IChartData *data) override;
			bool DetachData(const int index) override;
			bool DetachData(IChartData *data) override;
			bool DeleteData(const int index) override;
			bool DeleteData(IChartData *data) override;
			bool DetachDatas() override;
			bool DeleteDatas() override;

			CChartDataSet(); // Create empty
			CChartDataSet(const std::vector<IChartData*> &datas); // Create with specified datas
			virtual ~CChartDataSet();
		};
	}
}
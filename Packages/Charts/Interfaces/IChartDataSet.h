// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"

namespace nitisa
{
	namespace charts
	{
		class IChartData;

		class IChartDataSet
		{
		protected:
			IChartDataSet() = default;
			~IChartDataSet() = default;
			IChartDataSet(const IChartDataSet &other) = delete;
			IChartDataSet(IChartDataSet &&other) = delete;
			IChartDataSet &operator=(const IChartDataSet &other) = delete;
			IChartDataSet &operator=(IChartDataSet &&other) = delete;
		public:
			virtual String getXLabel(const float x, const String &default_label) = 0; // Return label for specified X-coordinate or specified default one
			virtual String getYLabel(const float y, const String &default_label) = 0; // Return label for specified Y-coordinate or specified default one
			virtual int getDataCount() = 0; // Return count of datas in set
			virtual IChartData *getData(const int index) = 0; // Return specified data

			virtual void Release() = 0; // Destroy
			virtual IChartDataSet *Clone() = 0; // Create a copy

			virtual bool AddData(IChartData *data) = 0; // Add new chart data to a set. Return false if data is nullptr of it is already in set
			virtual bool DetachData(const int index) = 0; // Remove data specified by index from list without destroying it
			virtual bool DetachData(IChartData *data) = 0; // Remove specified data from list without destroying it
			virtual bool DeleteData(const int index) = 0; // Remove data specified by index from list and destroy it
			virtual bool DeleteData(IChartData *data) = 0; // Remove specified data from list and destroy it
			virtual bool DetachDatas() = 0; // Remove all datas from list without destroying it
			virtual bool DeleteDatas() = 0; // Remove all datas from list and destroy it
		};
	}
}
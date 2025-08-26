// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/DateTime.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IControl.h"
#include "Nitisa/Math/PointB.h"
#include "Nitisa/Math/PointD.h"

namespace nitisa
{
	namespace charts
	{
		class IForexChart :public virtual IControl
		{
		protected:
			IForexChart() = default;
			~IForexChart() = default;
			IForexChart(const IForexChart &other) = delete;
			IForexChart(IForexChart &&other) = delete;
			IForexChart &operator=(const IForexChart &other) = delete;
			IForexChart &operator=(IForexChart &&other) = delete;
		public:
			class IForexChartData // Describes forex data
			{
			protected:
				IForexChartData() = default;
				~IForexChartData() = default;
				IForexChartData(const IForexChartData &other) = delete;
				IForexChartData(IForexChartData &&other) = delete;
				IForexChartData &operator=(const IForexChartData &other) = delete;
				IForexChartData &operator=(IForexChartData &&other) = delete;
			public:
				virtual int getCount() = 0; // Return count of points
				virtual const CDateTime &getDateTime(const int index) const = 0; // Return datetime of specified point
				virtual float getOpen(const int index) = 0; // Return open value of specified point
				virtual float getClose(const int index) = 0; // Return close value of specified point
				virtual float getMin(const int index) = 0; // Return minimum value of specified point
				virtual float getMax(const int index) = 0; // Return maximum value of specified point
				virtual String getXLabel(const double x, const String &default_label) = 0; // Return X-axis label for specified point or default one
				virtual String getYLabel(const double y, const String &default_label) = 0; // Return Y-axis label for specified point or default one

				virtual bool setDateTime(const int index, const CDateTime &value) = 0; // Set datetime of specified point
				virtual bool setOpen(const int index, const float value) = 0; // Set open value of specified point
				virtual bool setClose(const int index, const float value) = 0; // Set close value of specified point
				virtual bool setMin(const int index, const float value) = 0; // Set minimum value of specified point
				virtual bool setMax(const int index, const float value) = 0; // Set maximum value of specified point

				virtual void Release() = 0; // Destroy
				virtual IForexChartData *Clone() = 0; // Create a copy

				virtual bool Add(const CDateTime &datetime, const float open, const float close, const float min, const float max) = 0; // Add point
				virtual bool Delete(const int index) = 0; // Delete specified point
				virtual bool Clear() = 0; // Delete all points
			};
		public:
			void(*OnHoverPoint)(IForexChart *sender, const int index); // Event called when point appears under mouse pointer
			void(*OnLeavePoint)(IForexChart *sender); // Event called when there were point below mouse point and now no new point is below mouse pointer. Do not called when one point becomes unhovered and another becomes hovered. In the last case only OnHoverPoint will be called

			virtual PointD getXRange() = 0;  // Return range in X-direction in global coordinate space represented on client area of control
			virtual PointD getYRange() = 0; // Return range in Y-direction in global coordinate space represented on client area of control
			virtual PointB getAutoRange() = 0; // Return whether ranges in X and Y directions should be calculated automatically to represent entire data of the dataset assigned to a widget
			virtual IForexChartData *getData() = 0; // Return assigned data

			virtual bool setXRange(const PointD &value) = 0; // Set range in X-direction in global coordinate space represented on client area of control. It also cancels automatic range calculation in X direction
			virtual bool setYRange(const PointD &value) = 0; // Set range in Y-direction in global coordinate space represented on client area of control. It also cancels automatic range calculation in Y direction
			virtual bool setAutoRange(const PointB &value) = 0; // Set whether ranges in X and Y directions should be calculated automatically(to represent entire data of the dataset assigned to a widget)
			virtual bool setData(IForexChartData *value, const bool release_old) = 0; // Assign new data. If release_old is set to true then existing data will be destroyed first

			virtual void Update() = 0; // Update widget. Should be called after updating data to refresh a widget
		};
	}
}
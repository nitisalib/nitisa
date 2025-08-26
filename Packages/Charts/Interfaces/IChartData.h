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
		class IChartRenderer;

		class IChartData
		{
		protected:
			IChartData() = default;
			~IChartData() = default;
			IChartData(const IChartData &other) = delete;
			IChartData(IChartData &&other) = delete;
			IChartData &operator=(const IChartData &other) = delete;
			IChartData &operator=(IChartData &&other) = delete;
		public:
			virtual String getName() = 0; // Return name
			virtual int getCount() = 0; // Return count of points
			virtual float getX(const int index) = 0; // Return X-coordinate of specified point
			virtual float getY(const int index) = 0; // Return Y-coordinate of specified point
			virtual String getLabel(const int index) = 0; // Return label of specified point
			virtual IChartRenderer *getRenderer() = 0; // Return assigned renderer. Can be nullptr. May be used by some chart widgets for custom drawing

			virtual bool setName(const String &value) = 0; // Set name
			virtual bool setX(const int index, const float value) = 0; // Set X-coordinate of specified point
			virtual bool setY(const int index, const float value) = 0; // Set Y-coordinate of specified point
			virtual bool setLabel(const int index, const String &value) = 0; // Set label of specified point

			virtual void Release() = 0; // Destroy. It doesn't delete data from data set
			virtual IChartData *Clone() = 0; // Creates a copy

			virtual void AddPoint(const float x, const float y, const String &label = L"") = 0; // Add new point
			virtual bool DeletePoint(const int index) = 0; // Delete specified point
			virtual bool DeletePoints() = 0; // Delete all points
		};
	}
}
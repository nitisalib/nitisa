// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControl.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointB.h"

namespace nitisa
{
	namespace standard
	{
		class ITrackRange :public virtual IControl
		{
		protected:
			ITrackRange() = default;
			~ITrackRange() = default;
			ITrackRange(const ITrackRange &other) = delete;
			ITrackRange(ITrackRange &&other) = delete;
			ITrackRange &operator=(const ITrackRange &other) = delete;
			ITrackRange &operator=(ITrackRange &&other) = delete;
		public:
			void(*OnChange)(ITrackRange *sender); // Event called when control's value is changed

			virtual int getMin() = 0; // Return minimum
			virtual int getMax() = 0; // Return maximum
			virtual Point getValue() = 0; // Return current values(selected range)
			virtual PointB getTrackerEnabled() = 0; // Return whether trackers are enabled
			virtual PointB getTrackerVisible() = 0; // Return whether trackers are visible

			virtual bool setMin(const int value) = 0; // Set minimum
			virtual bool setMax(const int value) = 0; // Set maximum
			virtual bool setValue(const Point &value) = 0; // Set current values(selected range)
			virtual bool setTrackerEnabled(const PointB &value) = 0; // Set whether trackers are enabled
			virtual bool setTrackerVisible(const PointB &value) = 0; // Set whether trackers are visible
			virtual bool setValue1(const int value) = 0; // Set "from" value
			virtual bool setValue2(const int value) = 0; // Set "to" value
		};
	}
}
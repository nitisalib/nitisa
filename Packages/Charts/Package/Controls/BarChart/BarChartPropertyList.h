// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "../../../Core/BarChartRenderer.h"
#include "../../../Core/CustomCartesianChartPropertyList.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace charts
	{
		class CBarChartPropertyList :public CCustomCartesianChartPropertyList
		{
		private:
			static StringArray PointStateItems();
			static CBarChartRenderer::PointState StringToPointState(const String &state);
		public:
			CBarChartPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}
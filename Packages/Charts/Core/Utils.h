// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Variant.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/Vec3f.h"
#include "Enums.h"
#include <vector>

namespace nitisa
{
	namespace charts
	{
		// Convertion between data and view coordinate systems
		float DataXToView(const float x, const PointF &xrange, const float view_width);
		float DataYToView(const float y, const PointF &yrange, const float view_height);
		PointF DataToView(const PointF &p, const PointF &xrange, const PointF &yrange, const PointF &view_size);
		Vec3f DataToView3D(const PointF &p, const PointF &xrange, const PointF &yrange, const PointF &view_size);
		float ViewXToData(const float x, const PointF &xrange, const float view_width);
		float ViewYToData(const float y, const PointF &yrange, const float view_height);
		PointF ViewToData(const PointF &p, const PointF &xrange, const PointF &yrange, const PointF &view_size);

		LineInterpolationPosition StringToLineInterpolationPosition(const String &value);
		String LineInterpolationPositionToString(const LineInterpolationPosition value);
		StringArray LineInterpolationPositionItems();

		String LineInterpolationPositionArrayToString(const std::vector<LineInterpolationPosition> &value);
		Variant LineInterpolationPositionArrayToVariant(const std::vector<LineInterpolationPosition> &value);
		void LineInterpolationPositionArrayFromVariant(const Variant &value, std::vector<LineInterpolationPosition> &dest);
	}
}
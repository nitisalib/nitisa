// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		float DataXToView(const float x, const PointF &xrange, const float view_width)
		{
			return (x - xrange.X) * view_width / (xrange.Y - xrange.X);
		}

		float DataYToView(const float y, const PointF &yrange, const float view_height)
		{
			return view_height - (y - yrange.X) * view_height / (yrange.Y - yrange.X);
		}

		PointF DataToView(const PointF &p, const PointF &xrange, const PointF &yrange, const PointF &view_size)
		{
			return PointF{
				(p.X - xrange.X) * view_size.X / (xrange.Y - xrange.X),
				view_size.Y - (p.Y - yrange.X) * view_size.Y / (yrange.Y - yrange.X)
			};
		}

		Vec3f DataToView3D(const PointF &p, const PointF &xrange, const PointF &yrange, const PointF &view_size)
		{
			return Vec3f{
				(p.X - xrange.X) * view_size.X / (xrange.Y - xrange.X),
				view_size.Y - (p.Y - yrange.X) * view_size.Y / (yrange.Y - yrange.X),
				0
			};
		}

		float ViewXToData(const float x, const PointF &xrange, const float view_width)
		{
			return x * (xrange.Y - xrange.X) / view_width + xrange.X;
		}

		float ViewYToData(const float y, const PointF &yrange, const float view_height)
		{
			return view_height - y * (yrange.Y - yrange.X) / view_height + yrange.X;
		}

		PointF ViewToData(const PointF &p, const PointF &xrange, const PointF &yrange, const PointF &view_size)
		{
			return PointF{
				p.X * (xrange.Y - xrange.X) / view_size.X + xrange.X,
				view_size.Y - p.Y * (yrange.Y - yrange.X) / view_size.Y + yrange.X
			};
		}

		LineInterpolationPosition StringToLineInterpolationPosition(const String &value)
		{
			if (value == L"LineInterpolationPosition::Before")
				return LineInterpolationPosition::Before;
			if (value == L"LineInterpolationPosition::After")
				return LineInterpolationPosition::After;
			return LineInterpolationPosition::Middle;
		}

		String LineInterpolationPositionToString(const LineInterpolationPosition value)
		{
			switch (value)
			{
			case LineInterpolationPosition::Before: return L"LineInterpolationPosition::Before";
			case LineInterpolationPosition::After:	return L"LineInterpolationPosition::After";
			default:								return L"LineInterpolationPosition::Middle";
			}
		}

		StringArray LineInterpolationPositionItems()
		{
			return StringArray{
				L"LineInterpolationPosition::Before",
				L"LineInterpolationPosition::Middle",
				L"LineInterpolationPosition::After" };
		}

		String LineInterpolationPositionArrayToString(const std::vector<LineInterpolationPosition> &value)
		{
			if (value.size() == 0)
				return L"{}";
			if (value.size() == 1)
				return L"{ " + LineInterpolationPositionToString(value[0]) + L" }";
			return L"{ " + LineInterpolationPositionToString(value[0]) + L", ... }";
		}

		Variant LineInterpolationPositionArrayToVariant(const std::vector<LineInterpolationPosition> &value)
		{
			Variant result;
			for (auto v : value)
				result.push_back((Variant)LineInterpolationPositionToString(v));
			return result;
		}

		void LineInterpolationPositionArrayFromVariant(const Variant &value, std::vector<LineInterpolationPosition> &dest)
		{
			dest.clear();
			if (value.getType() == Variant::VariantType::Array)
				for (auto v : value)
					dest.push_back(StringToLineInterpolationPosition((String)v.second));
		}
	}
}
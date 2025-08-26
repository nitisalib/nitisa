// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	Variant ToVariant(const std::vector<std::pair<String, String>> &value)
	{
		Variant result;
		for (auto &row : value)
			if (!row.first.empty())
			{
				Variant t;
				t[L"Search"] = row.first;
				t[L"Replace"] = row.second;
				result.push_back(t);
			}
		return result;
	}

	void FromVariant(const Variant &src, std::vector<std::pair<String, String>> &dest)
	{
		dest.clear();
		if (src.getType() == Variant::VariantType::Array)
			for (size_t i = 0; i < src.size(); i++)
			{
				Variant row{ src.get((int)i) };
				if (row.getType() == Variant::VariantType::Map && row.size() == 2 && row.isSet(L"Search") && row.isSet(L"Replace") && row[L"Search"].getType() == Variant::VariantType::String &&
					row[L"Replace"].getType() == Variant::VariantType::String && !String(row[L"Search"]).empty())
					dest.push_back({ (String)row[L"Search"], (String)row[L"Replace"] });
			}
	}

	Variant ToVariant(const fb::SETTINGS &value)
	{
		Variant result;
		result[L"GridX"] = value.GridX;
		result[L"GridY"] = value.GridY;
		result[L"GridRotate"] = value.GridRotate;
		result[L"GridXStep"] = value.GridXStep;
		result[L"GridYStep"] = value.GridYStep;
		result[L"GridRotateStep"] = value.GridRotateStep;
		result[L"RotateShift"] = value.RotateShift;
		result[L"GridPointSize"] = value.GridPointSize;
		result[L"GridPointColor"] = ToVariant(value.GridPointColor);
		result[L"Namespace"] = value.Namespace;
		result[L"Prefix"] = value.Prefix;
		result[L"SelectionPointSize"] = value.SelectionPointSize;
		result[L"SelectionBorderWidth"] = value.SelectionBorderWidth;
		result[L"SelectionBorderColor"] = ToVariant(value.SelectionBorderColor);
		result[L"SelectionBackgroundColor"] = ToVariant(value.SelectionBackgroundColor);
		result[L"OverwriteIncludes"] = ToVariant(value.OverwriteIncludes);
		result[L"OverwriteNamespaces"] = ToVariant(value.OverwriteNamespaces);
		result[L"WidgetsSection"] = ToVariant(value.WidgetsSection);
		result[L"GenerateGetters"] = ToVariant(value.GenerateGetters);
		result[L"HighlightBorderWidth"] = ToVariant(value.HighlightBorderWidth);
		result[L"HighlightBorderColor"] = ToVariant(value.HighlightBorderColor);
		result[L"ExportAs"] = ToVariant((int)value.ExportAs);
		result[L"DialogBoxPackage"] = value.DialogBoxPackage;
		result[L"DialogBoxClass"] = value.DialogBoxClass;
		return result;
	}

	void FromVariant(const Variant &src, fb::SETTINGS &dest)
	{
		dest.OverwriteIncludes.clear();
		dest.OverwriteNamespaces.clear();
		if (src.isSet(L"GridX"))
			dest.GridX = (bool)src.get(L"GridX");
		if (src.isSet(L"GridY"))
			dest.GridY = (bool)src.get(L"GridY");
		if (src.isSet(L"GridRotate"))
			dest.GridRotate = (bool)src.get(L"GridRotate");
		if (src.isSet(L"GridXStep"))
			dest.GridXStep = ntl::Max<float>(1, (float)src.get(L"GridXStep"));
		if (src.isSet(L"GridYStep"))
			dest.GridYStep = ntl::Max<float>(1, (float)src.get(L"GridYStep"));
		if (src.isSet(L"GridRotateStep"))
			dest.GridRotateStep = ntl::Max<float>(0.000001f, (float)src.get(L"GridRotateStep"));
		if (src.isSet(L"RotateShift"))
			dest.RotateShift = ntl::Max<float>(1, (float)src.get(L"RotateShift"));
		if (src.isSet(L"GridPointSize"))
			dest.GridPointSize = ntl::Max<float>(1, (float)src.get(L"GridPointSize"));
		if (src.isSet(L"GridPointColor"))
			FromVariant(src.get(L"GridPointColor"), dest.GridPointColor);
		if (src.isSet(L"Namespace"))
			dest.Namespace = (String)src.get(L"Namespace");
		if (src.isSet(L"Prefix"))
			dest.Prefix = (String)src.get(L"Prefix");
		if (src.isSet(L"SelectionPointSize"))
			dest.SelectionPointSize = ntl::Max<float>(1, (float)src.get(L"SelectionPointSize"));
		if (src.isSet(L"SelectionBorderWidth"))
			dest.SelectionBorderWidth = ntl::Max<float>(0, (float)src.get(L"SelectionBorderWidth"));
		if (src.isSet(L"SelectionBorderColor"))
			FromVariant(src.get(L"SelectionBorderColor"), dest.SelectionBorderColor);
		if (src.isSet(L"SelectionBackgroundColor"))
			FromVariant(src.get(L"SelectionBackgroundColor"), dest.SelectionBackgroundColor);
		if (src.isSet(L"OverwriteIncludes"))
			FromVariant(src.get(L"OverwriteIncludes"), dest.OverwriteIncludes);
		if (src.isSet(L"OverwriteNamespaces"))
			FromVariant(src.get(L"OverwriteNamespaces"), dest.OverwriteNamespaces);
		if (src.isSet(L"WidgetsSection"))
		{
			dest.WidgetsSection = (String)src.get(L"WidgetsSection");
			if (dest.WidgetsSection != L"public" && dest.WidgetsSection != L"protected" && dest.WidgetsSection != L"private")
				dest.WidgetsSection = L"public";
		}
		if (src.isSet(L"GenerateGetters"))
			dest.GenerateGetters = (bool)src.get(L"GenerateGetters");
		if (src.isSet(L"HighlightBorderWidth"))
			FromVariant(src.get(L"HighlightBorderWidth"), dest.HighlightBorderWidth);
		if (src.isSet(L"HighlightBorderColor"))
			FromVariant(src.get(L"HighlightBorderColor"), dest.HighlightBorderColor);
		if (src.isSet(L"ExportAs"))
			dest.ExportAs = fb::ExportAs((int)src.get(L"ExportAs"));
		if (src.isSet(L"DialogBoxPackage"))
			dest.DialogBoxPackage = (String)src.get(L"DialogBoxPackage");
		if (src.isSet(L"DialogBoxClass"))
			dest.DialogBoxClass = (String)src.get(L"DialogBoxClass");
	}
}
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
		CBarChartPropertyList::CBarChartPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CCustomCartesianChartPropertyList(package, control, entity)
		{
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyBoolState(this, control, L"DrawBorder", false, PointStateItems(), ExportPrefixType::Namespace, L"CBarChartRenderer::", nullptr,
				[](IClass *parent, const String &state) {return cast<CBarChart*>(parent)->isDrawBorder(StringToPointState(state)); },
				[](IClass *parent, const String &state, const bool value) {return cast<CBarChart*>(parent)->setDrawBorder(StringToPointState(state), value); }))
				->AddHeaderFile(L"Charts/Core/BarChartRenderer.h");
			Add(new CPropertyBoolState(this, control, L"DrawBackground", false, PointStateItems(), ExportPrefixType::Namespace, L"CBarChartRenderer::", nullptr,
				[](IClass *parent, const String &state) {return cast<CBarChart*>(parent)->isDrawBackground(StringToPointState(state)); },
				[](IClass *parent, const String &state, const bool value) {return cast<CBarChart*>(parent)->setDrawBackground(StringToPointState(state), value); }))
				->AddHeaderFile(L"Charts/Core/BarChartRenderer.h");
			CPropertyFloatState *p{ Add(new CPropertyFloatState(this, control, L"BorderWidth", false, PointStateItems(), ExportPrefixType::Namespace, L"CBarChartRenderer::", nullptr,
				[](IClass *parent, const String &state) {return cast<CBarChart*>(parent)->getBorderWidth(StringToPointState(state)); },
				[](IClass *parent, const String &state, const float value) {return cast<CBarChart*>(parent)->setBorderWidth(StringToPointState(state), value); })) };
			p->setMin(0);
			p->AddHeaderFile(L"Charts/Core/BarChartRenderer.h");
			Add(new CPropertyColorState(this, control, L"BorderColor", false, PointStateItems(), ExportPrefixType::Namespace, L"CBarChartRenderer::", nullptr,
				[](IClass *parent, const String &state) {return cast<CBarChart*>(parent)->getBorderColor(StringToPointState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CBarChart*>(parent)->setBorderColor(StringToPointState(state), value); }))
				->AddHeaderFile(L"Charts/Core/BarChartRenderer.h");
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, PointStateItems(), ExportPrefixType::Namespace, L"CBarChartRenderer::", nullptr,
				[](IClass *parent, const String &state) {return cast<CBarChart*>(parent)->getBackgroundColor(StringToPointState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CBarChart*>(parent)->setBackgroundColor(StringToPointState(state), value); }))
				->AddHeaderFile(L"Charts/Core/BarChartRenderer.h");
			Add(new CPropertyBool(this, control, L"Vertical", false, nullptr,
				[](IClass *parent) {return cast<CBarChart*>(parent)->isVertical(); },
				[](IClass *parent, const bool value) {return cast<CBarChart*>(parent)->setVertical(value); }));
			Add(new CPropertyFloat(this, control, L"BarWidth", false, nullptr,
				[](IClass *parent) {return cast<CBarChart*>(parent)->getBarWidth(); },
				[](IClass *parent, const float value) {return cast<CBarChart*>(parent)->setBarWidth(value); }))
				->setMin(0);
		}

		StringArray CBarChartPropertyList::PointStateItems()
		{
			return StringArray{ L"PointState::Normal", L"PointState::Active" };

		}

		CBarChartRenderer::PointState CBarChartPropertyList::StringToPointState(const String &state)
		{
			if (state == L"PointState::Active")
				return CBarChartRenderer::PointState::Active;
			return CBarChartRenderer::PointState::Normal;
		}
	}
}
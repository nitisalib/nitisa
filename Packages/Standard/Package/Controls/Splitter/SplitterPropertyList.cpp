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
	namespace standard
	{
		CSplitterPropertyList::CSplitterPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Font");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"Font.Monospace");
			Delete(L"Font.Distance");
			Delete(L"Size");
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyFloat(this, control, L"DotWidth", false, nullptr,
				[](IClass *parent) {return cast<CSplitter*>(parent)->getDotWidth(); },
				[](IClass *parent, const float value) {return cast<CSplitter*>(parent)->setDotWidth(value); }))
				->setMin(0);
			Add(new CPropertyInteger(this, control, L"DotCount", false, nullptr,
				[](IClass *parent) {return cast<CSplitter*>(parent)->getDotCount(); },
				[](IClass *parent, const int value) {return cast<CSplitter*>(parent)->setDotCount(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CSplitter*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CSplitter*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CSplitter*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"DotColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CSplitter*>(parent)->getDotColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CSplitter*>(parent)->setDotColor(StringToState(state), value); }));
		}

		StringArray CSplitterPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Active",
				L"State::Disabled" };
		}

		CSplitter::State CSplitterPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CSplitter::State::Hovered;
			if (state == L"State::Active")
				return CSplitter::State::Active;
			if (state == L"State::Disabled")
				return CSplitter::State::Disabled;
			return CSplitter::State::Normal;
		}
	}
}
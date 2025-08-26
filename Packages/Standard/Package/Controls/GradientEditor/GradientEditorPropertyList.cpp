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
		CGradientEditorPropertyList::CGradientEditorPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"WantTabs");
			Delete(L"Font");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"Font.Monospace");
			Delete(L"Font.Distance");
			Delete(L"UseParentFont");

			Add(new CPropertyGradient(this, control, L"Gradient", nullptr,
				[](IClass *parent) {return cast<CGradientEditor*>(parent)->getGradient(); }));
			Add(new CPropertyInteger(this, control, L"ActivePoint", false, nullptr,
				[](IClass *parent) {return cast<CGradientEditor*>(parent)->getActivePoint(); },
				[](IClass *parent, const int value) {return cast<CGradientEditor*>(parent)->setActivePoint(value); }));
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CGradientEditor*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CGradientEditor*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyFloat(this, control, L"ArrowSize", false, nullptr,
				[](IClass *parent) {return cast<CGradientEditor*>(parent)->getArrowSize(); },
				[](IClass *parent, const float value) {return cast<CGradientEditor*>(parent)->setArrowSize(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"ArrowColor", false, ArrowStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGradientEditor*>(parent)->getArrowColor(StringToArrowState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CGradientEditor*>(parent)->setArrowColor(StringToArrowState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ArrowColorBorder", false, ArrowStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CGradientEditor*>(parent)->getArrowBorderColor(StringToArrowState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CGradientEditor*>(parent)->setArrowBorderColor(StringToArrowState(state), value); }));
		}

		StringArray CGradientEditorPropertyList::ArrowStateItems()
		{
			return StringArray{
				L"ArrowState::Normal",
				L"ArrowState::Hovered",
				L"ArrowState::Active",
				L"ArrowState::ActiveHovered" };
		}

		CGradientEditor::ArrowState CGradientEditorPropertyList::StringToArrowState(const String &state)
		{
			if (state == L"ArrowState::Hovered")
				return CGradientEditor::ArrowState::Hovered;
			if (state == L"ArrowState::Active")
				return CGradientEditor::ArrowState::Active;
			if (state == L"ArrowState::ActiveHovered")
				return CGradientEditor::ArrowState::ActiveHovered;
			return CGradientEditor::ArrowState::Normal;
		}
	}
}
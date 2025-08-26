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
	namespace ide
	{
		CFormViewPropertyList::CFormViewPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"Cursor");
			Delete(L"TransformControls");
			Delete(L"Enabled");

			Add(new CPropertyString(this, control, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CFormView*>(parent)->getCaption(); },
				[](IClass *parent, const String value) { return cast<CFormView*>(parent)->setCaption(value); }));
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CFormView*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) { return cast<CFormView*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, States(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFormView*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) { return cast<CFormView*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CFormViewPropertyList::States()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CFormView::State CFormViewPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CFormView::State::Active;
			return CFormView::State::Normal;
		}
	}
}
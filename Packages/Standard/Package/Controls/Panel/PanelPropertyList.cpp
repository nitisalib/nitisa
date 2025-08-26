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
		CPanelPropertyList::CPanelPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");

			Add(new CPropertyString(this, control, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CPanel*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CPanel*>(parent)->setCaption(value); }))
				->setChanged(true);
			Add(new CPropertyEnum(this, control, L"CaptionHorizontalAlign", false, TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return TextAlignToString(cast<CPanel*>(parent)->getCaptionHorizontalAlign()); },
				[](IClass *parent, const String value) {return cast<CPanel*>(parent)->setCaptionHorizontalAlign(StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyEnum(this, control, L"CaptionVerticalAlign", false, VerticalAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return VerticalAlignToString(cast<CPanel*>(parent)->getCaptionVerticalAlign()); },
				[](IClass *parent, const String value) {return cast<CPanel*>(parent)->setCaptionVerticalAlign(StringToVerticalAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/VerticalAlign.h");
			Add(new CPropertyEnum(this, control, L"OuterBevel", false, BevelItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) {return BevelToString(cast<CPanel*>(parent)->getOuterBevel()); },
				[](IClass *parent, const String value) {return cast<CPanel*>(parent)->setOuterBevel(StringToBevel(value)); }));
			Add(new CPropertyEnum(this, control, L"InnerBevel", false, BevelItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) {return BevelToString(cast<CPanel*>(parent)->getInnerBevel()); },
				[](IClass *parent, const String value) {return cast<CPanel*>(parent)->setInnerBevel(StringToBevel(value)); }));
			Add(new CPropertyColor(this, control, L"BevelRaisedColor", false, nullptr,
				[](IClass *parent) {return cast<CPanel*>(parent)->getBevelRaisedColor(); },
				[](IClass *parent, const Color value) {return cast<CPanel*>(parent)->setBevelRaisedColor(value); }));
			Add(new CPropertyColor(this, control, L"BevelLoweredColor", false, nullptr,
				[](IClass *parent) {return cast<CPanel*>(parent)->getBevelLoweredColor(); },
				[](IClass *parent, const Color value) {return cast<CPanel*>(parent)->setBevelLoweredColor(value); }));
			Add(new CPropertyRectF(this, control, L"OuterBevelWidth", false, nullptr,
				[](IClass *parent) {return cast<CPanel*>(parent)->getOuterBevelWidth(); },
				[](IClass *parent, const RectF value) {return cast<CPanel*>(parent)->setOuterBevelWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"InnerBevelWidth", false, nullptr,
				[](IClass *parent) {return cast<CPanel*>(parent)->getInnerBevelWidth(); },
				[](IClass *parent, const RectF value) {return cast<CPanel*>(parent)->setInnerBevelWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CPanel*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CPanel*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CPanel*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CPanel*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"BorderColor", false, nullptr,
				[](IClass *parent) {return cast<CPanel*>(parent)->getBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CPanel*>(parent)->setBorderColor(value); }));
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CPanel*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CPanel*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CPanel*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CPanel*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CPanel*>(parent)->getBackgroundGradient(); }));
			Add(new CPropertyColor(this, control, L"ShadowColor", false, nullptr,
				[](IClass *parent) {return cast<CPanel*>(parent)->getShadowColor(); },
				[](IClass *parent, const Color value) {return cast<CPanel*>(parent)->setShadowColor(value); }));
			Add(new CPropertyPointF(this, control, L"ShadowShift", false, nullptr,
				[](IClass *parent) {return cast<CPanel*>(parent)->getShadowShift(); },
				[](IClass *parent, const PointF value) {return cast<CPanel*>(parent)->setShadowShift(value); }));
			Add(new CPropertyInteger(this, control, L"ShadowRadius", false, nullptr,
				[](IClass *parent) {return cast<CPanel*>(parent)->getShadowRadius(); },
				[](IClass *parent, const int value) {return cast<CPanel*>(parent)->setShadowRadius(value); }))
				->setMin(1);
			Add(new CPropertyBool(this, control, L"UseMask", false, nullptr,
				[](IClass *parent) {return cast<CPanel*>(parent)->isUseMask(); },
				[](IClass *parent, const bool value) {return cast<CPanel*>(parent)->setUseMask(value); }));
		}

		StringArray CPanelPropertyList::BevelItems()
		{
			return StringArray{
				L"Bevel::Raised",
				L"Bevel::Lowered" };
		}

		String CPanelPropertyList::BevelToString(const CPanel::Bevel value)
		{
			switch (value)
			{
			case CPanel::Bevel::Lowered:	return L"Bevel::Lowered";
			default:						return L"Bevel::Raised";
			}
		}

		CPanel::Bevel CPanelPropertyList::StringToBevel(const String &value)
		{
			if (value == L"Bevel::Lowered")
				return CPanel::Bevel::Lowered;
			return CPanel::Bevel::Raised;
		}
	}
}
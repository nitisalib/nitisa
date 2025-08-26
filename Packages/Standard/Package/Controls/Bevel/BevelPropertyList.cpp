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
		CBevelPropertyList::CBevelPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Font");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"Font.Monospace");
			Delete(L"Font.Distance");
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");


			Add(new CPropertyEnum(this, control, L"BevelKind", false, BevelKindItems(), ExportPrefixType::Namespace, L"IBevel::", nullptr,
				[](IClass *parent) {return BevelKindToString(cast<CBevel*>(parent)->getBevelKind()); },
				[](IClass *parent, const String value) {return cast<CBevel*>(parent)->setBevelKind(StringToBevelKind(value)); }))
				->AddHeaderFile(L"Standard/Controls/IBevel.h");
			Add(new CPropertyEnum(this, control, L"BevelStyle", false, BevelStyleItems(), ExportPrefixType::Namespace, L"IBevel::", nullptr,
				[](IClass *parent) {return BevelStyleToString(cast<CBevel*>(parent)->getBevelStyle()); },
				[](IClass *parent, const String value) {return cast<CBevel*>(parent)->setBevelStyle(StringToBevelStyle(value)); }))
				->AddHeaderFile(L"Standard/Controls/IBevel.h");
			Add(new CPropertyColor(this, control, L"ColorLowered", false, nullptr,
				[](IClass *parent) {return cast<CBevel*>(parent)->getColorLowered(); },
				[](IClass *parent, const Color value) {return cast<CBevel*>(parent)->setColorLowered(value); }));
			Add(new CPropertyColor(this, control, L"ColorRaised", false, nullptr,
				[](IClass *parent) {return cast<CBevel*>(parent)->getColorRaised(); },
				[](IClass *parent, const Color value) {return cast<CBevel*>(parent)->setColorRaised(value); }));
			Add(new CPropertyFloat(this, control, L"BevelWidth", false, nullptr,
				[](IClass *parent) {return cast<CBevel*>(parent)->getBevelWidth(); },
				[](IClass *parent, const float value) {return cast<CBevel*>(parent)->setBevelWidth(value); }))
				->setMin(1);
		}

		StringArray CBevelPropertyList::BevelKindItems()
		{
			return StringArray{
				L"BevelKind::Box",
				L"BevelKind::Frame",
				L"BevelKind::LeftEdge",
				L"BevelKind::TopEdge",
				L"BevelKind::RightEdge",
				L"BevelKind::BottomEdge" };
		}

		IBevel::BevelKind CBevelPropertyList::StringToBevelKind(const String &value)
		{
			if (value == L"BevelKind::Frame")
				return IBevel::BevelKind::Frame;
			if (value == L"BevelKind::LeftEdge")
				return IBevel::BevelKind::LeftEdge;
			if (value == L"BevelKind::TopEdge")
				return IBevel::BevelKind::TopEdge;
			if (value == L"BevelKind::RightEdge")
				return IBevel::BevelKind::RightEdge;
			if (value == L"BevelKind::BottomEdge")
				return IBevel::BevelKind::BottomEdge;
			return IBevel::BevelKind::Box;
		}

		String CBevelPropertyList::BevelKindToString(const IBevel::BevelKind value)
		{
			switch (value)
			{
			case IBevel::BevelKind::Frame:		return L"BevelKind::Frame";
			case IBevel::BevelKind::LeftEdge:	return L"BevelKind::LeftEdge";
			case IBevel::BevelKind::TopEdge:	return L"BevelKind::TopEdge";
			case IBevel::BevelKind::RightEdge:	return L"BevelKind::RightEdge";
			case IBevel::BevelKind::BottomEdge: return L"BevelKind::BottomEdge";
			default:							return L"BevelKind::Box";
			}
		}

		StringArray CBevelPropertyList::BevelStyleItems()
		{
			return StringArray{
				L"BevelStyle::Lowered",
				L"BevelStyle::Raised" };
		}

		IBevel::BevelStyle CBevelPropertyList::StringToBevelStyle(const String &value)
		{
			if (value == L"BevelStyle::Raised")
				return IBevel::BevelStyle::Raised;
			return IBevel::BevelStyle::Lowered;
		}

		String CBevelPropertyList::BevelStyleToString(const IBevel::BevelStyle value)
		{
			switch (value)
			{
			case IBevel::BevelStyle::Raised:	return L"BevelStyle::Raised";
			default:							return L"BevelStyle::Lowered";
			}
		}
	}
}
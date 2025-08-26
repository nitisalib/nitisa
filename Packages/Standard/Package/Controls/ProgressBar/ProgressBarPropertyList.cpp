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
		CProgressBarPropertyList::CProgressBarPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"Enabled");

			Add(new CPropertyFloat(this, control, L"Min", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getMin(); },
				[](IClass *parent, const float value) {return cast<CProgressBar*>(parent)->setMin(value); }));
			Add(new CPropertyFloat(this, control, L"Max", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getMax(); },
				[](IClass *parent, const float value) {return cast<CProgressBar*>(parent)->setMax(value); }));
			Add(new CPropertyFloat(this, control, L"Progress", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getProgress(); },
				[](IClass *parent, const float value) {return cast<CProgressBar*>(parent)->setProgress(value); }));
			Add(new CPropertyString(this, control, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CProgressBar*>(parent)->setCaption(value); }));
			Add(new CPropertyEnum(this, control, L"CaptionHorizontalAlign", false, TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return TextAlignToString(cast<CProgressBar*>(parent)->getCaptionHorizontalAlign()); },
				[](IClass *parent, const String value) {return cast<CProgressBar*>(parent)->setCaptionHorizontalAlign(StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyEnum(this, control, L"CaptionVerticalAlign", false, VerticalAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return VerticalAlignToString(cast<CProgressBar*>(parent)->getCaptionVerticalAlign()); },
				[](IClass *parent, const String value) {return cast<CProgressBar*>(parent)->setCaptionVerticalAlign(StringToVerticalAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/VerticalAlign.h");
			Add(new CPropertyBool(this, control, L"Smooth", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->isSmooth(); },
				[](IClass *parent, const bool value) {return cast<CProgressBar*>(parent)->setSmooth(value); }));
			Add(new CPropertyFloat(this, control, L"BarSize", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getBarSize(); },
				[](IClass *parent, const float value) {return cast<CProgressBar*>(parent)->setBarSize(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"BarInterval", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getBarInterval(); },
				[](IClass *parent, const float value) {return cast<CProgressBar*>(parent)->setBarInterval(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"ShadowColor", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getShadowColor(); },
				[](IClass *parent, const Color value) {return cast<CProgressBar*>(parent)->setShadowColor(value); }));
			Add(new CPropertyPointF(this, control, L"ShadowShift", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getShadowShift(); },
				[](IClass *parent, const PointF value) {return cast<CProgressBar*>(parent)->setShadowShift(value); }));
			Add(new CPropertyInteger(this, control, L"ShadowRadius", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getShadowRadius(); },
				[](IClass *parent, const int value) {return cast<CProgressBar*>(parent)->setShadowRadius(value); }))
				->setMin(1);
			Add(new CPropertyRectF(this, control, L"OuterBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getOuterBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CProgressBar*>(parent)->setOuterBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"InnerBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getInnerBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CProgressBar*>(parent)->setInnerBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CProgressBar*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"OuterBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getOuterBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CProgressBar*>(parent)->setOuterBorderColor(value); }));
			Add(new CPropertyBorderColor(this, control, L"InnerBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getInnerBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CProgressBar*>(parent)->setInnerBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CProgressBar*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getBackgroundGradient(); }));
			Add(new CPropertyColor(this, control, L"ForegroundColor", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getForegroundColor(); },
				[](IClass *parent, const Color value) {return cast<CProgressBar*>(parent)->setForegroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"ForegroundGradient", nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getForegroundGradient(); }));
			Add(new CPropertyRectF(this, control, L"BarBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getBarBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CProgressBar*>(parent)->setBarBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BarBorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getBarBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CProgressBar*>(parent)->setBarBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"BarBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getBarBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CProgressBar*>(parent)->setBarBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"BarColor", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getBarColor(); },
				[](IClass *parent, const Color value) {return cast<CProgressBar*>(parent)->setBarColor(value); }));
			Add(new CPropertyGradient(this, control, L"BarGradient", nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getBarGradient(); }));
			Add(new CPropertyRectF(this, control, L"CaptionPadding", false, nullptr,
				[](IClass *parent) {return cast<CProgressBar*>(parent)->getCaptionPadding(); },
				[](IClass *parent, const RectF value) {return cast<CProgressBar*>(parent)->setCaptionPadding(value); }))
				->setMin(0);
			Add(new CPropertyEnum(this, control, L"FillDirection", false, FillDirectionItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) {return FillDirectionToString(cast<CProgressBar*>(parent)->getFillDirection()); },
				[](IClass *parent, const String value) {return cast<CProgressBar*>(parent)->setFillDirection(StringToFillDirection(value)); }));
		}

		StringArray CProgressBarPropertyList::FillDirectionItems()
		{
			return StringArray{
				L"FillDirection::LeftToRight",
				L"FillDirection::RightToLeft",
				L"FillDirection::TopToBottom",
				L"FillDirection::BottomToTop" };
		}

		String CProgressBarPropertyList::FillDirectionToString(const CProgressBar::FillDirection value)
		{
			switch (value)
			{
			case CProgressBar::FillDirection::RightToLeft:	return L"FillDirection::RightToLeft";
			case CProgressBar::FillDirection::TopToBottom:	return L"FillDirection::TopToBottom";
			case CProgressBar::FillDirection::BottomToTop:	return L"FillDirection::BottomToTop";
			default:										return L"FillDirection::LeftToRight";
			}
		}

		CProgressBar::FillDirection CProgressBarPropertyList::StringToFillDirection(const String &value)
		{
			if (value == L"FillDirection::RightToLeft")
				return CProgressBar::FillDirection::RightToLeft;
			if (value == L"FillDirection::TopToBottom")
				return CProgressBar::FillDirection::TopToBottom;
			if (value == L"FillDirection::BottomToTop")
				return CProgressBar::FillDirection::BottomToTop;
			return CProgressBar::FillDirection::LeftToRight;
		}
	}
}
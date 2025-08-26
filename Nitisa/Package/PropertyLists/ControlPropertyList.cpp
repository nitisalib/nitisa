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
	CControlPropertyList::CControlPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :CComponentPropertyList(package, control, entity)
	{
		Add(new CPropertyStyle(this, control, L"Style",
			[](IClass *parent) { return cast<IControl*>(parent)->isUseParentStyle(); },
			[](IClass *parent) { return cast<IControl*>(parent)->getStyle(); },
			[](IClass *parent, IStyle *value) {return cast<IControl*>(parent)->setStyle(value); }));
		Add(new CPropertyFont(this, control, L"Font", false,
			[](IClass *parent) { return cast<IControl*>(parent)->isUseParentFont(); },
			[](IClass *parent) { return cast<IControl*>(parent)->getControlFont(); },
			[](IClass *parent, IFont *value) {return cast<IControl*>(parent)->setFont(value); }));
		Add(new CPropertyFloat(this, control, L"Font.Distance", false,
			[](IClass *parent) { return true; },
			[](IClass *parent) {
				IFont *font{ cast<IControl*>(parent)->getControlFont() };
				if (font)
					return cast<IControl*>(parent)->getControlFont()->Distance;
				return 0.0f;
			},
			[](IClass *parent, const float value) {
				IFont *font{ cast<IControl*>(parent)->getControlFont() };
				if (font)
					return cast<IControl*>(parent)->getControlFont()->setDistance(value);
				return false;
			}));
		Add(new CPropertyBool(this, control, L"Font.Monospace", false,
			[](IClass *parent) { return true; },
			[](IClass *parent) {
				IFont *font{ cast<IControl*>(parent)->getControlFont() };
				if (font)
					return cast<IControl*>(parent)->getControlFont()->Monospace;
				return false;
			},
			[](IClass *parent, const bool value) {
				IFont *font{ cast<IControl*>(parent)->getControlFont() };
				if (font)
					return cast<IControl*>(parent)->getControlFont()->setMonospace(value);
				return false;
			}));
		Add(new CPropertyColor(this, control, L"Font.ShadowColor", false,
			[](IClass *parent) { return true; },
			[](IClass *parent) {
				IFont *font{ cast<IControl*>(parent)->getControlFont() };
				if (font)
					return cast<IControl*>(parent)->getControlFont()->ShadowColor;
				return Color{ 0, 0, 0, 0 };
			},
			[](IClass *parent, const Color value) {
				IFont *font{ cast<IControl*>(parent)->getControlFont() };
				if (font)
					return cast<IControl*>(parent)->getControlFont()->setShadowColor(value);
				return false;
			}));
		Add(new CPropertyPointF(this, control, L"Font.ShadowShift", false,
			[](IClass *parent) { return true; },
			[](IClass *parent) {
				IFont *font{ cast<IControl*>(parent)->getControlFont() };
				if (font)
					return cast<IControl*>(parent)->getControlFont()->ShadowShift;
				return PointF{ 0, 0 };
			},
			[](IClass *parent, const PointF value) {
				IFont *font{ cast<IControl*>(parent)->getControlFont() };
				if (font)
					return cast<IControl*>(parent)->getControlFont()->setShadowShift(value);
				return false;
			}));
		Add(new CPropertyInteger(this, control, L"Font.ShadowRadius", false,
			[](IClass *parent) { return true; },
			[](IClass *parent) {
				IFont *font{ cast<IControl*>(parent)->getControlFont() };
				if (font)
					return cast<IControl*>(parent)->getControlFont()->ShadowRadius;
				return 0;
			},
			[](IClass *parent, const int value) {
				IFont *font{ cast<IControl*>(parent)->getControlFont() };
				if (font)
					return cast<IControl*>(parent)->getControlFont()->setShadowRadius(value);
				return false;
			}))
			->setMin(1);
		Add(new CPropertyTransform(this, control, L"Transform", false,
			[](IClass *parent) { return cast<IControl*>(parent)->getAlign() != Align::None; },
			[](IClass *parent) { return cast<IControl*>(parent)->getTransform()->getTransform(); },
			[](IClass *parent, const Transform value) {return cast<IControl*>(parent)->getTransform()->setTransform(value); }));
		Add(new CPropertyTransform(this, control, L"TransformControls", false, nullptr,
			[](IClass *parent) { return cast<IControl*>(parent)->getTransformControls()->getTransform(); },
			[](IClass *parent, const Transform value) {return cast<IControl*>(parent)->getTransformControls()->setTransform(value); }));
		Add(new CPropertyRectF(this, control, L"Constraints", false, nullptr,
			[](IClass *parent) { return cast<IControl*>(parent)->getConstraints(); },
			[](IClass *parent, const RectF value) {return cast<IControl*>(parent)->setConstraints(value); }))
			->setMin(0);
		Add(new CPropertyPointF(this, control, L"Size", false, nullptr,
			[](IClass *parent) { return cast<IControl*>(parent)->getSize(); },
			[](IClass *parent, const PointF value) {return cast<IControl*>(parent)->setSize(value); }))
			->setMin(0);
		Add(new CPropertyInteger(this, control, L"ZIndex", false, nullptr,
			[](IClass *parent) { return cast<IControl*>(parent)->getZIndex(); },
			[](IClass *parent, const int value) {return cast<IControl*>(parent)->setZIndex(value); }));
		Add(new CPropertyEnum(this, control, L"Cursor", true, CursorTypeItems(), ExportPrefixType::None, L"", nullptr,
			[](IClass *parent) { return CursorTypeToString(cast<IControl*>(parent)->getCursor()); },
			[](IClass *parent, const String value) {return cast<IControl*>(parent)->setCursor(StringToCursorType(value)); }))
			->AddHeaderFile(L"Nitisa/Core/CursorType.h");
		Add(new CPropertyInteger(this, control, L"TabOrder", false, nullptr,
			[](IClass *parent) { return cast<IControl*>(parent)->getTabOrder(); },
			[](IClass *parent, const int value) {return cast<IControl*>(parent)->setTabOrder(value); }))
			->setMin(0);
		Add(new CPropertyString(this, control, L"HintText", false, nullptr,
			[](IClass *parent) { return cast<IControl*>(parent)->getHintText(); },
			[](IClass *parent, const String value) {return cast<IControl*>(parent)->setHintText(value); }));
		Add(new CPropertyFloat(this, control, L"HintDelay", false,
			[](IClass *parent) { return cast<IControl*>(parent)->isUseParentHintDelay(); },
			[](IClass *parent) { return cast<IControl*>(parent)->getHintDelay(); },
			[](IClass *parent, const float value) {return cast<IControl*>(parent)->setHintDelay(value); }))
			->setMin(0.001f);
		Add(new CPropertyPointF(this, control, L"HintShift", false,
			[](IClass *parent) { return cast<IControl*>(parent)->isUseParentHintShift(); },
			[](IClass *parent) { return cast<IControl*>(parent)->getHintShift(); },
			[](IClass *parent, const PointF value) {return cast<IControl*>(parent)->setHintShift(value); }));
		Add(new CPropertyBool(this, control, L"WantTabs", false, nullptr,
			[](IClass *parent) { return cast<IControl*>(parent)->isWantTabs(); },
			[](IClass *parent, const bool value) {return cast<IControl*>(parent)->setWantTabs(value); }));
		Add(new CPropertyBool(this, control, L"TabStop", false, nullptr,
			[](IClass *parent) { return cast<IControl*>(parent)->isTabStop(); },
			[](IClass *parent, const bool value) {return cast<IControl*>(parent)->setTabStop(value); }));
		Add(new CPropertyBool(this, control, L"DeactivateByTab", false, nullptr,
			[](IClass *parent) { return cast<IControl*>(parent)->isDeactivateByTab(); },
			[](IClass *parent, const bool value) {return cast<IControl*>(parent)->setDeactivateByTab(value); }));
		Add(new CPropertyBool(this, control, L"Visible", false, nullptr,
			[](IClass *parent) { return cast<IControl*>(parent)->isVisible(false); },
			[](IClass *parent, const bool value) {return cast<IControl*>(parent)->setVisible(value); }));
		Add(new CPropertyBool(this, control, L"Enabled", false, nullptr,
			[](IClass *parent) { return cast<IControl*>(parent)->isEnabled(false); },
			[](IClass *parent, const bool value) {return cast<IControl*>(parent)->setEnabled(value); }));
		Add(new CPropertyBool(this, control, L"ShowHint", false,
			[](IClass *parent) {return cast<IControl*>(parent)->isUseParentShowHint(); },
			[](IClass *parent) { return cast<IControl*>(parent)->isShowHint(); },
			[](IClass *parent, const bool value) {return cast<IControl*>(parent)->setShowHint(value); }));
		Add(new CPropertyBool(this, control, L"UseParentStyle", false, nullptr,
			[](IClass *parent) { return cast<IControl*>(parent)->isUseParentStyle(); },
			[](IClass *parent, const bool value) {return cast<IControl*>(parent)->setUseParentStyle(value); }));
		Add(new CPropertyBool(this, control, L"UseParentFont", false, nullptr,
			[](IClass *parent) { return cast<IControl*>(parent)->isUseParentFont(); },
			[](IClass *parent, const bool value) {return cast<IControl*>(parent)->setUseParentFont(value); }));
		Add(new CPropertyBool(this, control, L"UseParentShowHint", false, nullptr,
			[](IClass *parent) { return cast<IControl*>(parent)->isUseParentShowHint(); },
			[](IClass *parent, const bool value) {return cast<IControl*>(parent)->setUseParentShowHint(value); }));
		Add(new CPropertyBool(this, control, L"UseParentHintDelay", false, nullptr,
			[](IClass *parent) { return cast<IControl*>(parent)->isUseParentHintDelay(); },
			[](IClass *parent, const bool value) {return cast<IControl*>(parent)->setUseParentHintDelay(value); }));
		Add(new CPropertyBool(this, control, L"UseParentHintShift", false, nullptr,
			[](IClass *parent) { return cast<IControl*>(parent)->isUseParentHintShift(); },
			[](IClass *parent, const bool value) {return cast<IControl*>(parent)->setUseParentHintShift(value); }));
		Add(new CPropertyEnum(this, control, L"Align", false, AlignItems(), ExportPrefixType::None, L"", nullptr,
			[](IClass *parent) { return AlignToString(cast<IControl*>(parent)->getAlign()); },
			[](IClass *parent, const String value) {return cast<IControl*>(parent)->setAlign(StringToAlign(value)); }))
			->AddHeaderFile(L"Nitisa/Core/Align.h");
	}
}
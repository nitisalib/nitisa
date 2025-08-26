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
	CFormPropertyList::CFormPropertyList(IPackage *package, IForm *form, IPackageEntity *entity) :CPropertyList(package, form, entity)
	{
		Add(new CPropertyIdentifier(this, form, L"Name", false, nullptr,
			[](IClass *parent) {return cast<IForm*>(parent)->Name; },
			[](IClass *parent, const String value) {return cast<IForm*>(parent)->setName(value); }));
		Add(new CPropertyStyle(this, form, L"Style", nullptr,
			[](IClass *parent) {return cast<IForm*>(parent)->getStyle(); },
			[](IClass *parent, IStyle *value) {return cast<IForm*>(parent)->setStyle(value); }));
		Add(new CPropertyFont(this, form, L"Font", false, nullptr,
			[](IClass *parent) {return cast<IForm*>(parent)->getFont(); },
			[](IClass *parent, IFont *value) {return cast<IForm*>(parent)->setFont(value); }));
		Add(new CPropertyFloat(this, form, L"Font.Distance", false,
			[](IClass *parent) { return true; },
			[](IClass *parent) { return cast<IForm*>(parent)->getFont()->Distance; },
			[](IClass *parent, const float value) {return cast<IForm*>(parent)->getFont()->setDistance(value); }));
		Add(new CPropertyBool(this, form, L"Font.Monospace", false,
			[](IClass *parent) { return true; },
			[](IClass *parent) { return cast<IForm*>(parent)->getFont()->Monospace; },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->getFont()->setMonospace(value); }));
		Add(new CPropertyColor(this, form, L"Font.ShadowColor", false,
			[](IClass *parent) { return true; },
			[](IClass *parent) { return cast<IForm*>(parent)->getFont()->ShadowColor; },
			[](IClass *parent, const Color value) {return cast<IForm*>(parent)->getFont()->setShadowColor(value); }));
		Add(new CPropertyPointF(this, form, L"Font.ShadowShift", false,
			[](IClass *parent) { return true; },
			[](IClass *parent) { return cast<IForm*>(parent)->getFont()->ShadowShift; },
			[](IClass *parent, const PointF value) {return cast<IForm*>(parent)->getFont()->setShadowShift(value); }));
		Add(new CPropertyInteger(this, form, L"Font.ShadowRadius", false,
			[](IClass *parent) { return true; },
			[](IClass *parent) { return cast<IForm*>(parent)->getFont()->ShadowRadius; },
			[](IClass *parent, const int value) {return cast<IForm*>(parent)->getFont()->setShadowRadius(value); }))
			->setMin(1);
		Add(new CPropertyTransform(this, form, L"Transform", true, nullptr,
			[](IClass *parent) {return cast<IForm*>(parent)->getTransform()->getTransform(); },
			[](IClass *parent, const Transform value) {return cast<IForm*>(parent)->getTransform()->setTransform(value); }))
			->setAllowedTz(false)
			->setAllowedRx(false)
			->setAllowedRy(false)
			->setAllowedRz(false)
			->setAllowedSx(false)
			->setAllowedSy(false)
			->setAllowedSz(false)
			->setAllowedRotateOrder(false)
			->setAllowedTransformOrder(false);
		Add(new CPropertyTransform(this, form, L"TransformControls", false, nullptr,
			[](IClass *parent) {return cast<IForm*>(parent)->getTransformControls()->getTransform(); },
			[](IClass *parent, const Transform value) {return cast<IForm*>(parent)->getTransformControls()->setTransform(value); }));
		Add(new CPropertyEnum(this, form, L"Cursor", true, CursorTypeItems(), ExportPrefixType::None, L"", nullptr,
			[](IClass *parent) { return CursorTypeToString(cast<IForm*>(parent)->getCursor()); },
			[](IClass *parent, const String value) {return cast<IForm*>(parent)->setCursor(StringToCursorType(value)); }))
			->AddHeaderFile(L"Nitisa/Core/CursorType.h");
		Add(new CPropertyString(this, form, L"HintText", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->getHintText(); },
			[](IClass *parent, const String value) {return cast<IForm*>(parent)->setHintText(value); }));
		Add(new CPropertyFloat(this, form, L"HintDelay", false, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->getHintDelay(); },
			[](IClass *parent, const float value) {return cast<IForm*>(parent)->setHintDelay(value); }))
			->setMin(0.001f);
		Add(new CPropertyPointF(this, form, L"HintShift", false, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->getHintShift(); },
			[](IClass *parent, const PointF value) {return cast<IForm*>(parent)->setHintShift(value); }));
		Add(new CPropertyColor(this, form, L"BackgroundColor", false, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->getBackgroundColor(); },
			[](IClass *parent, const Color value) {return cast<IForm*>(parent)->setBackgroundColor(value); }));
		Add(new CPropertyBool(this, form, L"ShowHint", false, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->isShowHint(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setShowHint(value); }));
		Add(new CPropertyBool(this, form, L"FocusByLMB", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->isFocusByLMB(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setFocusByLMB(value); }));
		Add(new CPropertyBool(this, form, L"FocusByMMB", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->isFocusByMMB(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setFocusByMMB(value); }));
		Add(new CPropertyBool(this, form, L"FocusByRMB", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->isFocusByRMB(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setFocusByRMB(value); }));
		Add(new CPropertyBool(this, form, L"FocusByTab", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->isFocusByTab(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setFocusByTab(value); }));
		Add(new CPropertyString(this, form, L"Caption", false, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->getCaption(); },
			[](IClass *parent, const String value) {return cast<IForm*>(parent)->setCaption(value); }));
		Add(new CPropertyPoint(this, form, L"ClientSize", false, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->getSize(); },
			[](IClass *parent, const Point value) {return cast<IForm*>(parent)->setSize(value); }))
			->setChanged(true);
		Add(new CPropertyPoint(this, form, L"Position", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->getPosition(); },
			[](IClass *parent, const Point value) {return cast<IForm*>(parent)->setPosition(value); }));
		Add(new CPropertyEnum(this, form, L"State", true, WindowStateItems(), ExportPrefixType::None, L"", nullptr,
			[](IClass *parent) { return WindowStateToString(cast<IForm*>(parent)->getState()); },
			[](IClass *parent, const String value) {return cast<IForm*>(parent)->setState(StringToWindowState(value)); }))
			->AddHeaderFile(L"Nitisa/Core/WindowState.h");
		Add(new CPropertyBool(this, form, L"InterceptEnable", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->isInterceptEnable(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setInterceptEnable(value); }));
		Add(new CPropertyEnum(this, form, L"WindowPosition", true, WindowPositionItems(), ExportPrefixType::None, L"", nullptr,
			[](IClass *parent) { return WindowPositionToString(WindowPosition::Custom); },
			[](IClass *parent, const String value) {return cast<IForm*>(parent)->setWindowPosition(StringToWindowPosition(value)); }))
			->AddHeaderFile(L"Nitisa/Core/WindowPosition.h");
		Add(new CPropertyBool(this, form, L"HasBorder", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->hasBorder(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setHasBorder(value); }));
		Add(new CPropertyBool(this, form, L"HasCaption", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->hasCaption(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setHasCaption(value); }));
		Add(new CPropertyBool(this, form, L"HasDialogFrame", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->hasDialogFrame(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setHasDialogFrame(value); }));
		Add(new CPropertyBool(this, form, L"HasHorizontalScroll", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->hasHorizontalScroll(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setHasHorizontalScroll(value); }));
		Add(new CPropertyBool(this, form, L"HasVerticalScroll", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->hasVerticalScroll(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setHasVerticalScroll(value); }));
		Add(new CPropertyBool(this, form, L"HasMaximizeBox", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->hasMaximizeBox(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setHasMaximizeBox(value); }));
		Add(new CPropertyBool(this, form, L"HasMinimizeBox", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->hasMinimizeBox(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setHasMinimizeBox(value); }));
		Add(new CPropertyBool(this, form, L"HasSizeBox", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->hasSizeBox(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setHasSizeBox(value); }));
		Add(new CPropertyBool(this, form, L"HasSystemMenu", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->hasSystemMenu(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setHasSystemMenu(value); }));
		Add(new CPropertyBool(this, form, L"HasClientEdge", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->hasClientEdge(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setHasClientEdge(value); }));
		Add(new CPropertyBool(this, form, L"HasContextHelp", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->hasContextHelp(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setHasContextHelp(value); }));
		Add(new CPropertyBool(this, form, L"HasDialogModalFrame", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->hasDialogModalFrame(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setHasDialogModalFrame(value); }));
		Add(new CPropertyBool(this, form, L"HasStaticEdge", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->hasStaticEdge(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setHasStaticEdge(value); }));
		Add(new CPropertyBool(this, form, L"HasWindowEdge", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->hasWindowEdge(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setHasWindowEdge(value); }));
		Add(new CPropertyBool(this, form, L"IsPopup", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->isPopup(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setIsPopup(value); }));
		Add(new CPropertyBool(this, form, L"IsTabStop", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->isTabStop(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setIsTabStop(value); }));
		Add(new CPropertyBool(this, form, L"IsMDIChild", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->isMDIChild(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setIsMDIChild(value); }));
		Add(new CPropertyBool(this, form, L"IsToolWindow", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->isToolWindow(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setIsToolWindow(value); }));
		Add(new CPropertyBool(this, form, L"IsTopMost", true, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->isTopMost(); },
			[](IClass *parent, const bool value) {return cast<IForm*>(parent)->setIsTopMost(value); }));
		Add(new CPropertyRectF(this, form, L"BorderWidth", false, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->getBorderWidth(); },
			[](IClass *parent, const RectF value) {return cast<IForm*>(parent)->setBorderWidth(value); }))
			->setMin(0);
		Add(new CPropertyRectF(this, form, L"Padding", false, nullptr,
			[](IClass *parent) { return cast<IForm*>(parent)->getPadding(); },
			[](IClass *parent, const RectF value) {return cast<IForm*>(parent)->setPadding(value); }))
			->setMin(0);
	}
}
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
		CShapePropertyList::CShapePropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
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
			Delete(L"Enabled");
			Delete(L"UseParentFont");

			Add(new CPropertyEnum(this, control, L"ShapeType", false, ShapeTypeItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) {return ShapeTypeToString(cast<CShape*>(parent)->getShapeType()); },
				[](IClass *parent, const String value) {return cast<CShape*>(parent)->setShapeType(StringToShapeType(value)); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CShape*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) {return cast<CShape*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CShape*>(parent)->getBorderRadius(); },
				[](IClass *parent, const float value) {return cast<CShape*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"BorderColor", false, nullptr,
				[](IClass *parent) {return cast<CShape*>(parent)->getBorderColor(); },
				[](IClass *parent, const Color value) {return cast<CShape*>(parent)->setBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CShape*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CShape*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyMask(this, control, L"BorderMask", false, nullptr,
				[](IClass *parent) {return cast<CShape*>(parent)->getBorderMask(); },
				[](IClass *parent, const unsigned int value) {return cast<CShape*>(parent)->setBorderMask(value); }));
		}

		StringArray CShapePropertyList::ShapeTypeItems()
		{
			return StringArray{
				L"ShapeType::Circle",
				L"ShapeType::Ellipse",
				L"ShapeType::Rectangle",
				L"ShapeType::Square",
				L"ShapeType::RoundRectangle",
				L"ShapeType::RoundSquare",
				L"ShapeType::Triangle" };
		}

		CShape::ShapeType CShapePropertyList::StringToShapeType(const String &state)
		{
			if (state == L"ShapeType::Ellipse")
				return CShape::ShapeType::Ellipse;
			if (state == L"ShapeType::Rectangle")
				return CShape::ShapeType::Rectangle;
			if (state == L"ShapeType::Square")
				return CShape::ShapeType::Square;
			if (state == L"ShapeType::RoundRectangle")
				return CShape::ShapeType::RoundRectangle;
			if (state == L"ShapeType::RoundSquare")
				return CShape::ShapeType::RoundSquare;
			if (state == L"ShapeType::Triangle")
				return CShape::ShapeType::Triangle;
			return CShape::ShapeType::Circle;
		}

		String CShapePropertyList::ShapeTypeToString(const CShape::ShapeType state)
		{
			switch (state)
			{
			case CShape::ShapeType::Ellipse:		return L"ShapeType::Ellipse";
			case CShape::ShapeType::Rectangle:		return L"ShapeType::Rectangle";
			case CShape::ShapeType::Square:			return L"ShapeType::Square";
			case CShape::ShapeType::RoundRectangle: return L"ShapeType::RoundRectangle";
			case CShape::ShapeType::RoundSquare:	return L"ShapeType::RoundSquare";
			case CShape::ShapeType::Triangle:		return L"ShapeType::Triangle";
			default:								return L"ShapeType::Circle";
			}
		}
	}
}
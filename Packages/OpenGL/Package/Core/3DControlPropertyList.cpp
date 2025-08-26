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
	namespace opengl
	{
		C3DControlPropertyList::C3DControlPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Style");
			Delete(L"Font");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"Font.Monospace");
			Delete(L"Font.Distance");
			Delete(L"Transform");
			Delete(L"TransformControls");
			Delete(L"Constraints");
			Delete(L"Size");
			Delete(L"ZIndex");
			Delete(L"Cursor");
			Delete(L"TabOrder");
			Delete(L"HintText");
			Delete(L"HintDelay");
			Delete(L"HintShift");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"Visible");
			Delete(L"Enabled");
			Delete(L"ShowHint");
			Delete(L"UseParentStyle");
			Delete(L"UseParentFont");
			Delete(L"UseParentShowHint");
			Delete(L"UseParentHintDelay");
			Delete(L"UseParentHintShift");
			Delete(L"Align");

			Add(new CPropertyEnum(this, control, L"RenderMode", false, RenderModeItems(), ExportPrefixType::Namespace, L"I3DControl::", nullptr,
				[](IClass *parent) {return RenderModeToString(cast<C3DControl*>(parent)->getRenderMode()); },
				[](IClass *parent, const String value) {return cast<C3DControl*>(parent)->setRenderMode(StringToRenderMode(value)); }))
				->AddHeaderFile(L"OpenGL/Interfaces/I3DControl.h");
			Add(new CPropertyEnum(this, control, L"RotateOrder", false, RotateOrderItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return RotateOrderToString(cast<C3DControl*>(parent)->getRotateOrder()); },
				[](IClass *parent, const String value) {return cast<C3DControl*>(parent)->setRotateOrder(StringToRotateOrder(value)); }))
				->AddHeaderFile(L"Nitisa/Core/RotateOrder.h");
			Add(new CPropertyEnum(this, control, L"TransformOrder", false, TransformOrderItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return TransformOrderToString(cast<C3DControl*>(parent)->getTransformOrder()); },
				[](IClass *parent, const String value) {return cast<C3DControl*>(parent)->setTransformOrder(StringToTransformOrder(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TransformOrder.h");
			Add(new CPropertyFloat(this, control, L"X", false, nullptr,
				[](IClass *parent) {return cast<C3DControl*>(parent)->getX(); },
				[](IClass *parent, const float value) {return cast<C3DControl*>(parent)->setX(value); }));
			Add(new CPropertyFloat(this, control, L"Y", false, nullptr,
				[](IClass *parent) {return cast<C3DControl*>(parent)->getY(); },
				[](IClass *parent, const float value) {return cast<C3DControl*>(parent)->setY(value); }));
			Add(new CPropertyFloat(this, control, L"Z", false, nullptr,
				[](IClass *parent) {return cast<C3DControl*>(parent)->getZ(); },
				[](IClass *parent, const float value) {return cast<C3DControl*>(parent)->setZ(value); }));
			Add(new CPropertyFloat(this, control, L"Sx", false, nullptr,
				[](IClass *parent) {return cast<C3DControl*>(parent)->getSx(); },
				[](IClass *parent, const float value) {return cast<C3DControl*>(parent)->setSx(value); }));
			Add(new CPropertyFloat(this, control, L"Sy", false, nullptr,
				[](IClass *parent) {return cast<C3DControl*>(parent)->getSy(); },
				[](IClass *parent, const float value) {return cast<C3DControl*>(parent)->setSy(value); }));
			Add(new CPropertyFloat(this, control, L"Sz", false, nullptr,
				[](IClass *parent) {return cast<C3DControl*>(parent)->getSz(); },
				[](IClass *parent, const float value) {return cast<C3DControl*>(parent)->setSz(value); }));
			Add(new CPropertyFloat(this, control, L"Pitch", false, nullptr,
				[](IClass *parent) {return cast<C3DControl*>(parent)->getPitch(); },
				[](IClass *parent, const float value) {return cast<C3DControl*>(parent)->setPitch(value); }));
			Add(new CPropertyFloat(this, control, L"Yaw", false, nullptr,
				[](IClass *parent) {return cast<C3DControl*>(parent)->getYaw(); },
				[](IClass *parent, const float value) {return cast<C3DControl*>(parent)->setYaw(value); }));
			Add(new CPropertyFloat(this, control, L"Roll", false, nullptr,
				[](IClass *parent) {return cast<C3DControl*>(parent)->getRoll(); },
				[](IClass *parent, const float value) {return cast<C3DControl*>(parent)->setRoll(value); }));
			Add(new CPropertyControlMaterial(this, control, L"Material", nullptr,
				[](IClass *parent) {return cast<C3DControl*>(parent)->getMaterial(); },
				[](IClass *parent, IMaterialControl *value) {return cast<C3DControl*>(parent)->setMaterial(value); }));
		}

		StringArray C3DControlPropertyList::RenderModeItems()
		{
			return StringArray{
				L"RenderMode::Fill",
				L"RenderMode::Wireframe",
				L"RenderMode::Vertices" };
		}

		I3DControl::RenderMode C3DControlPropertyList::StringToRenderMode(const String &state)
		{
			if (state == L"RenderMode::Wireframe")
				return I3DControl::RenderMode::Wireframe;
			if (state == L"RenderMode::Vertices")
				return I3DControl::RenderMode::Vertices;
			return I3DControl::RenderMode::Fill;
		}

		String C3DControlPropertyList::RenderModeToString(const I3DControl::RenderMode state)
		{
			switch (state)
			{
			case I3DControl::RenderMode::Wireframe: return L"RenderMode::Wireframe";
			case I3DControl::RenderMode::Vertices:	return L"RenderMode::Vertices";
			default:								return L"RenderMode::Fill";
			}
		}
	}
}
// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
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
		CMaterialControlPropertyList::CMaterialControlPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
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
		}
	}
}
// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/3DControlPropertyList.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace opengl
	{
		class CJsonMeshPropertyList :public C3DControlPropertyList
		{
		public:
			CJsonMeshPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}
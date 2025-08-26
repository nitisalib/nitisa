// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "../Interfaces/I3DControl.h"

namespace nitisa
{
	namespace opengl
	{
		// Load 3D object from file in JSON format:
		//	{
		//		"Polygons": [
		//			{
		//				"Vertices": [
		//					{
		//						"Position": { "X": 0, "Y": 0, "Z": 0 },
		//						"Normal": { "Nx": 0, "Ny": 0, "Nz": 0 },
		//						"Texture": { "Tx": 0, "Ty": 0 }
		//					}
		//				]
		//			}
		//		]
		//	}
		class IJsonMesh :public virtual I3DControl
		{
		protected:
			IJsonMesh() = default;
			~IJsonMesh() = default;
			IJsonMesh(const IJsonMesh &other) = delete;
			IJsonMesh(IJsonMesh &&other) = delete;
			IJsonMesh &operator=(const IJsonMesh &other) = delete;
			IJsonMesh &operator=(IJsonMesh &&other) = delete;
		public:
			virtual String getFilename() = 0; // Return file name

			virtual bool setFilename(const String &value) = 0; // Set filename and try to load geometry
		};
	}
}
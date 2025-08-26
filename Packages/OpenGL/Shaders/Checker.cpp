// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
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
		namespace shaders
		{
			namespace checker
			{
				const AnsiString Vertex{
					"#version 140\n"

					"in vec2 in_Tex1;\n"
					"in vec3 in_Position;\n"

					"uniform mat4 app_Matrix;\n"

					"out vec2 var_Tex1;\n"

					"void main()\n"
					"{\n"
					"	var_Tex1 = in_Tex1;\n"
					"	gl_Position = app_Matrix * vec4(in_Position, 1);\n"
					"}\n"
				};

				const AnsiString Fragment{
					"#version 140\n"

					"in vec2 var_Tex1;\n"

					"uniform vec4 app_Color1;\n"
					"uniform vec4 app_Color2;\n"
					"uniform vec2 app_Scale;\n"

					"out vec4 FragColor;\n"

					"void main()\n"
					"{\n"
					"	int tx = int(var_Tex1.x * app_Scale.x * 2) % 2;\n"
					"	int ty = int(var_Tex1.y * app_Scale.y * 2) % 2;\n"
					"	if (tx == ty)\n"
					"		FragColor = app_Color1;\n"
					"	else\n"
					"		FragColor = app_Color2;\n"
					"}\n"
				};
			}
		}
	}
}
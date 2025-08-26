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
			namespace solid
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

					"uniform sampler2D app_Texture;\n"
					"uniform bool app_HasTexture;\n"
					"uniform vec4 app_Color;\n"

					"out vec4 FragColor;\n"

					"void main()\n"
					"{\n"
					"	if (app_HasTexture)\n"
					"		FragColor = texture(app_Texture, var_Tex1);\n"
					"	else\n"
					"		FragColor = app_Color;\n"
					"}\n"
				};
			}
		}
	}
}
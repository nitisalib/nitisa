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
			namespace gouraud
			{
				const AnsiString Vertex{
					"#version 140\n"

					"in vec2 in_Tex1;\n"
					"in vec3 in_Position;\n"
					"in vec3 in_Normal;\n"

					"uniform mat4 app_MatrixModel;\n"
					"uniform mat3 app_MatrixNormal;\n"
					"uniform mat4 app_MatrixCamera;\n"
					
					"uniform vec4 app_AmbientColor;\n"
					"uniform vec4 app_DiffuseAlbedo;\n"
					"uniform vec4 app_SpecularAlbedo;\n"
					"uniform vec3 app_LightPosition;\n"
					"uniform vec3 app_CameraPosition;\n"
					"uniform float app_Shininess;\n"

					"out vec2 var_Tex1;\n"
					"out vec4 var_Color;\n"

					"void main()\n"
					"{\n"
					"	var_Tex1 = in_Tex1;\n"
					"	vec4 P = app_MatrixModel * vec4(in_Position, 1);\n"
					"	vec3 N = normalize(app_MatrixNormal * in_Normal);\n"
					"	vec3 L = normalize(app_LightPosition - P.xyz);\n"
					"	vec3 V = normalize(app_CameraPosition - P.xyz);\n"
					"	vec3 R = reflect(-L, N);\n"
					"	vec4 diffuse = max(dot(N, L), 0.0) * app_DiffuseAlbedo;\n"
					"	vec4 specular = pow(max(dot(R, V), 0.0), app_Shininess) * app_SpecularAlbedo;\n"
					"	var_Color = app_AmbientColor + diffuse + specular;\n"
					"	gl_Position = app_MatrixCamera * P;\n"
					"}\n"
				};

				const AnsiString Fragment{
					"#version 140\n"

					"in vec2 var_Tex1;\n"
					"in vec4 var_Color;\n"

					"uniform sampler2D app_Texture;\n"
					"uniform bool app_HasTexture;\n"

					"out vec4 FragColor;\n"

					"void main()\n"
					"{\n"
					"	if (app_HasTexture)\n"
					"		FragColor = texture(app_Texture, var_Tex1) * var_Color;\n"
					"	else\n"
					"		FragColor = var_Color;\n"
					"}\n"
				};
			}
		}
	}
}
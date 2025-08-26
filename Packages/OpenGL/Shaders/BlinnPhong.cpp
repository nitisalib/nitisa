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
			namespace blinn_phong
			{
				const AnsiString Vertex{
					"#version 140\n"

					"in vec2 in_Tex1;\n"
					"in vec3 in_Position;\n"
					"in vec3 in_Normal;\n"

					"uniform mat4 app_MatrixModel;\n"
					"uniform mat3 app_MatrixNormal;\n"
					"uniform mat4 app_MatrixCamera;\n"
					"uniform vec3 app_LightPosition;\n"
					"uniform vec3 app_CameraPosition;\n"

					"out vec2 var_Tex1;\n"
					"out vec3 var_N;\n"
					"out vec3 var_L;\n"
					"out vec3 var_V;\n"

					"void main()\n"
					"{\n"
					"	var_Tex1 = in_Tex1;\n"
					"	vec4 P = app_MatrixModel * vec4(in_Position, 1);\n"
					"	var_N = app_MatrixNormal * in_Normal;\n"
					"	var_L = app_LightPosition - P.xyz;\n"
					"	var_V = app_CameraPosition - P.xyz;\n"
					"	gl_Position = app_MatrixCamera * P;\n"
					"}\n"
				};

				const AnsiString Fragment{
					"#version 140\n"

					"in vec2 var_Tex1;\n"
					"in vec3 var_N;\n"
					"in vec3 var_L;\n"
					"in vec3 var_V;\n"

					"uniform sampler2D app_Texture;\n"
					"uniform bool app_HasTexture;\n"
					"uniform vec4 app_AmbientColor;\n"
					"uniform vec4 app_DiffuseAlbedo;\n"
					"uniform vec4 app_SpecularAlbedo;\n"
					"uniform float app_Shininess;\n"

					"out vec4 FragColor;\n"

					"void main()\n"
					"{\n"
					"	vec3 n = normalize(var_N), l = normalize(var_L), v = normalize(var_V), h = normalize(l + v);\n"
					"	vec4 diffuse = max(dot(n, l), 0.0) * app_DiffuseAlbedo;\n"
					"	vec4 specular = pow(max(dot(n, h), 0.0), app_Shininess) * app_SpecularAlbedo;\n"
					"	FragColor = app_AmbientColor + diffuse + specular;\n"
					"	if (app_HasTexture)\n"
					"		FragColor = FragColor * texture(app_Texture, var_Tex1);\n"
					"}\n"
				};
			}
		}
	}
}
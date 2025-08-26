R"===(
layout (location = 0) in vec2 in_TCoord;
layout (location = 1) in vec2 in_BitMask;
layout (location = 2) in vec3 in_Position;
layout (location = 3) in vec4 in_Color;

struct MATRICES
{
	mat4 FormToGL;
	mat4 Primitive;
	mat4 MaskInv;
};

uniform MATRICES app_Matrices;

out vec2 var_TCoord;
out vec2 var_MCoord;
out vec4 var_Color;
out vec2 var_FormCoord;
out vec2 var_BitMask;
out vec2 var_PCoord;

void main()
{
	gl_Position = app_Matrices.FormToGL * app_Matrices.Primitive * vec4(in_Position.xy, 0, 1);
	var_TCoord = in_TCoord;
	var_Color = in_Color;
	var_FormCoord = (app_Matrices.Primitive * vec4(in_Position.xy, 0, 1)).xy;
	var_MCoord = (app_Matrices.MaskInv * app_Matrices.Primitive * vec4(in_Position.xy, 0, 1)).xy;
	var_BitMask = in_BitMask;
	var_PCoord = in_Position.xy;
}
)==="
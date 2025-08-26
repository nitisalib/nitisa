R"===(
struct MASK
{
	sampler2D Sampler;
	vec2 Size;
};

struct BITMASK
{
	uint X;
	uint Y;
};

uniform MASK app_Mask;
uniform BITMASK app_Bitmask;
uniform int app_BlockPointLocation;

uniform int app_SubroutineBlock;
uniform int app_SubroutineMask;
uniform int app_SubroutineBitmask;
uniform int app_SubroutineSpline;

// From vertex shader
in vec2 var_TCoord;
in vec2 var_MCoord;
in vec4 var_Color;
in vec2 var_FormCoord;
in vec2 var_BitMask;

// Output color
out vec4 FragColor;

// External functions
vec4 BlockPointColor(const vec2 p, const int index);
int BlockPointLocation(const vec2 p, const int index);
float CheckPointBetweenSplines(const vec2 point);
vec4 CalculateColor(const vec2 tex_coord, const vec2 form_coord, const vec4 color);
vec4 HSVToRGB(const vec4 hsva);

// Subroutine types
float SubTestBlock()
{
	switch (app_SubroutineBlock)
	{
		case 1:
			return BlockPointLocation(var_FormCoord, 0) == app_BlockPointLocation ? 1 : 0;
	}
	return 1;
}

float SubTestMask()
{
	switch (app_SubroutineMask)
	{
		case 1:
			return texture(app_Mask.Sampler, vec2(var_MCoord.x / app_Mask.Size.x, 1 - var_MCoord.y / app_Mask.Size.y)).a;
	}
	return 1;
}

float SubBitmask()
{
	switch (app_SubroutineBitmask)
	{
		case 1:
		{
			uint bit_x = uint(var_BitMask.x) % 32u;
			uint cmp_x = 1u << bit_x;
			return app_Bitmask.X & cmp_x;
		}
		case 2:
		{
			uint bit_x = uint(var_BitMask.x) % 32u;
			uint bit_y = uint(var_BitMask.y) % 32u;
			uint cmp_x = 1u << bit_x, cmp_y = 1u << bit_y;
			return ((app_Bitmask.X & cmp_x) > 0u && (app_Bitmask.Y & cmp_y) > 0u) ? 1 : 0;
		}
		case 3:
		{
			uint bit_x = uint(var_FormCoord.x) % 32u;
			uint bit_y = uint(var_FormCoord.y) % 32u;
			uint cmp_x = 1u << bit_x, cmp_y = 1u << bit_y;
			return ((app_Bitmask.X & cmp_x) > 0u && (app_Bitmask.Y & cmp_y) > 0u) ? 1 : 0;
		}
	}
	return 1;
}

float SubSplineLimit()
{
	switch (app_SubroutineSpline)
	{
		case 1:
			return CheckPointBetweenSplines(var_FormCoord);
		case 2:
			return CheckPointBetweenSplines(var_FormCoord.yx);
	}
	return 1;
}

// Entry point
void main()
{
	FragColor = CalculateColor(var_TCoord, var_FormCoord, var_Color);
	FragColor *= SubTestBlock();
	FragColor *= SubTestMask();
	FragColor *= SubBitmask();
	FragColor *= SubSplineLimit();
}
)==="
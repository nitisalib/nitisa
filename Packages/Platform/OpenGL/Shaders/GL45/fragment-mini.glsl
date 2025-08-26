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
subroutine float SubTestBlock();
subroutine float SubTestMask();
subroutine float SubBitMask();
subroutine float SubSplineLimit();

// Subroutine variables
subroutine uniform SubTestBlock TestBlock;
subroutine uniform SubTestMask TestMask;
subroutine uniform SubBitMask BitMask;
subroutine uniform SubSplineLimit SplineLimit;

// TestBlock subroutines
subroutine (SubTestBlock) float TestBlockNone()
{
	return 1;
}

subroutine (SubTestBlock) float TestBlockExists()
{
	return BlockPointLocation(var_FormCoord, 0) == app_BlockPointLocation ? 1 : 0;
}

// TestMask subroutines
subroutine (SubTestMask) float TestMaskNone()
{
	return 1;
}

subroutine (SubTestMask) float TestMaskExists()
{
	return texture(app_Mask.Sampler, vec2(var_MCoord.x / app_Mask.Size.x, 1 - var_MCoord.y / app_Mask.Size.y)).a;
}

// BitMask subroutine
subroutine (SubBitMask) float BitMaskNone()
{
	return 1;
}

subroutine (SubBitMask) float BitMask1D()
{
	uint bit_x = uint(var_BitMask.x) % 32;
	uint cmp_x = 1 << bit_x;
	return app_Bitmask.X & cmp_x;
}

subroutine (SubBitMask) float BitMask2D()
{
	uint bit_x = uint(var_BitMask.x) % 32;
	uint bit_y = uint(var_BitMask.y) % 32;
	uint cmp_x = 1 << bit_x, cmp_y = 1 << bit_y;
	return ((app_Bitmask.X & cmp_x) > 0 && (app_Bitmask.Y & cmp_y) > 0) ? 1 : 0;
}

subroutine (SubBitMask) float BitMaskForm()
{
	uint bit_x = uint(var_FormCoord.x) % 32;
	uint bit_y = uint(var_FormCoord.y) % 32;
	uint cmp_x = 1 << bit_x, cmp_y = 1 << bit_y;
	return ((app_Bitmask.X & cmp_x) > 0 && (app_Bitmask.Y & cmp_y) > 0) ? 1 : 0;
}

// SplineLimit subroutine
subroutine (SubSplineLimit) float SplineLimitNone()
{
	return 1;
}

subroutine (SubSplineLimit) float SplineLimitY()
{
	return CheckPointBetweenSplines(var_FormCoord);
}

subroutine (SubSplineLimit) float SplineLimitX()
{
	return CheckPointBetweenSplines(var_FormCoord.yx);
}

// Entry point
void main()
{
	FragColor = CalculateColor(var_TCoord, var_FormCoord, var_Color);
	FragColor *= TestBlock();
	FragColor *= TestMask();
	FragColor *= BitMask();
	FragColor *= SplineLimit();
}
)==="
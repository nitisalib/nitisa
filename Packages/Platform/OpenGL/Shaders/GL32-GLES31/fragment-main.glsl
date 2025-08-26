R"===(
struct TEXTURE
{
	sampler2D Sampler;
	sampler2DMS Multisampler;
	float Transparency;
	int SampleCount;
};

struct GRADIENT
{
	sampler2D PositionSampler;
	sampler2D ColorSampler;
	int Size;
	int Type;
};

struct BLUR
{
	int Radius;
	float K;
	float KExp;
	vec2 Disp;
};

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

struct CHECKER
{
	vec4 Color1;
	vec4 Color2;
};

struct HSV_PLANE
{
	float Hue;
};

uniform TEXTURE app_Texture;
uniform GRADIENT app_Gradient;
uniform BLUR app_Blur;
uniform MASK app_Mask;
uniform BITMASK app_Bitmask;
uniform CHECKER app_Checker;
uniform HSV_PLANE app_HSVPlane;
uniform int app_BlockPointLocation;

uniform int app_SubroutineBlock;
uniform int app_SubroutineMask;
uniform int app_SubroutineBitmask;
uniform int app_SubroutineSpline;
uniform int app_SubroutinePattern;

// From vertex shader
in vec2 var_TCoord;
in vec2 var_MCoord;
in vec4 var_Color;
in vec2 var_FormCoord;
in vec2 var_BitMask;
in vec2 var_PCoord;

// Output color
out vec4 FragColor;

// Contants
const int gtHorizontal = 0;
const int gtVertical = 1;
const int gtRadial = 2;
const int gtDiagonalDown = 3;
const int gtDiagonalUp = 4;
const int gtCircle = 5;

const int blockLimit = 0;
const int blockPrimitive = 1;

// External functions
vec4 BlockPointColor(const vec2 p, const int index);
int BlockPointLocation(const vec2 p, const int index);
float CheckPointBetweenSplines(const vec2 point);
vec4 HSVToRGB(const vec4 hsva);

// Subroutine types
float SubTestBlock()
{
	switch (app_SubroutineBlock)
	{
		case 1:
			return (BlockPointLocation(var_FormCoord, blockLimit) == app_BlockPointLocation) ? 1.0f : 0.0f;
	}
	return 1.0f;
}

float SubTestMask()
{
	switch (app_SubroutineMask)
	{
		case 1:
			return texture(app_Mask.Sampler, vec2(var_MCoord.x / app_Mask.Size.x, 1.0f - var_MCoord.y / app_Mask.Size.y)).a;
	}
	return 1.0f;
}

float SubBitmask()
{
	switch (app_SubroutineBitmask)
	{
		case 1:
		{
			uint bit_x = uint(var_BitMask.x) % 32u;
			uint cmp_x = 1u << bit_x;
			return ((app_Bitmask.X & cmp_x) > 0u) ? 1.0f : 0.0f;
		}
		case 2:
		{
			uint bit_x = uint(var_BitMask.x) % 32u;
			uint bit_y = uint(var_BitMask.y) % 32u;
			uint cmp_x = 1u << bit_x, cmp_y = 1u << bit_y;
			return ((app_Bitmask.X & cmp_x) > 0u && (app_Bitmask.Y & cmp_y) > 0u) ? 1.0f : 0.0f;
		}
		case 3:
		{
			uint bit_x = uint(var_FormCoord.x) % 32u;
			uint bit_y = uint(var_FormCoord.y) % 32u;
			uint cmp_x = 1u << bit_x, cmp_y = 1u << bit_y;
			return ((app_Bitmask.X & cmp_x) > 0u && (app_Bitmask.Y & cmp_y) > 0u) ? 1.0f : 0.0f;
		}
	}
	return 1.0f;
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
	return 1.0f;
}

// Pattern subroutines
vec4 PatternGradient()
{
	int i1 = 0, i2 = 1, i;
	float d = 0.0f, t;
	switch (app_Gradient.Type)
	{
	case gtVertical:
		d = 1.0f - var_TCoord.y;
		break;
	case gtRadial:
	{
		float x0 = var_TCoord.x - 0.5f;
		float y0 = 0.5f - var_TCoord.y;
		d = sqrt(2.0f * (x0 * x0 + y0 * y0));
		break;
	}
	case gtDiagonalUp:
	{
		d = (var_TCoord.x + var_TCoord.y) / 2.0f;
		break;
	}
	case gtDiagonalDown:
	{
		d = (var_TCoord.x + 1.0f - var_TCoord.y) / 2.0f;
		break;
	}
	case gtCircle:
	{
		d = sqrt(var_TCoord.x * var_TCoord.x + var_TCoord.y * var_TCoord.y);
		if (d > 1.0f)
			return vec4(0, 0, 0, 0);
		break;
	}
	default: //gtHorizontal
		d = var_TCoord.x;
		break;
	}
	for (i = 1; i < app_Gradient.Size; i++)
		if (texelFetch(app_Gradient.PositionSampler, ivec2(i, 0), 0).r >= d)
		{
			i1 = i - 1;
			i2 = i;
			break;
		}
	t = (d - texelFetch(app_Gradient.PositionSampler, ivec2(i1, 0), 0).r) / (texelFetch(app_Gradient.PositionSampler, ivec2(i2, 0), 0).r - texelFetch(app_Gradient.PositionSampler, ivec2(i1, 0), 0).r);
	return texelFetch(app_Gradient.ColorSampler, ivec2(i1, 0), 0) * (1.0f - t) + texelFetch(app_Gradient.ColorSampler, ivec2(i2, 0), 0) * t;
}

vec4 PatternTextureMultisample()
{
	ivec2 texSize = textureSize(app_Texture.Multisampler);
	ivec2 texCoord = ivec2(var_TCoord * texSize);
	vec4 color = vec4(0, 0, 0, 0);
    for (int i = 0; i < app_Texture.SampleCount; i++)
        color += texelFetch(app_Texture.Multisampler, texCoord, i);
    color /= float(app_Texture.SampleCount);
	return color * app_Texture.Transparency;
}

vec4 PatternText()
{
	float alpha = texture(app_Texture.Sampler, var_TCoord).r * var_Color.a;
	return vec4(var_Color.r * alpha, var_Color.g * alpha, var_Color.b * alpha, alpha);
}

vec4 PatternBlurHGaussian()
{
	float sum = 0.0f;
	vec4 result = vec4(0, 0, 0, 0);
	for (int i = -app_Blur.Radius; i <= app_Blur.Radius; i++)
	{
		float weight = app_Blur.K * exp(app_Blur.KExp * float(i * i));
		sum += weight;
		vec2 coord = vec2(var_TCoord.x + app_Blur.Disp.x * float(i), var_TCoord.y);
		result += texture(app_Texture.Sampler, coord) * weight;
	}
	return result / sum;
}

vec4 PatternBlurVGaussian()
{
	float sum = 0.0f;
	vec4 result = vec4(0, 0, 0, 0);
	for (int i = -app_Blur.Radius; i <= app_Blur.Radius; i++)
	{
		float weight = app_Blur.K * exp(app_Blur.KExp * float(i * i));
		sum += weight;
		vec2 coord = vec2(var_TCoord.x, var_TCoord.y + app_Blur.Disp.y * float(i));
		result += texture(app_Texture.Sampler, coord) * weight;
	}
	return result / sum;
}

vec4 PatternBlurHAverage()
{
	vec4 result = vec4(0, 0, 0, 0);
	for (int i = -app_Blur.Radius; i <= app_Blur.Radius; i++)
	{
		vec2 coord = vec2(var_TCoord.x + app_Blur.Disp.x * float(i), var_TCoord.y);
		result += texture(app_Texture.Sampler, coord);
	}
	return result / float(2 * app_Blur.Radius + 1);
}

vec4 PatternBlurVAverage()
{
	vec4 result = vec4(0, 0, 0, 0);
	for (int i = -app_Blur.Radius; i <= app_Blur.Radius; i++)
	{
		vec2 coord = vec2(var_TCoord.x, var_TCoord.y + app_Blur.Disp.y * float(i));
		result += texture(app_Texture.Sampler, coord);
	}
	return result / float(2 * app_Blur.Radius + 1);
}

vec4 PatternChecker()
{
	int x = int(var_TCoord.x), y = int(var_TCoord.y);
	return (((x + y) % 2) == 0) ? app_Checker.Color1 : app_Checker.Color2;
}

vec4 PatternHSVGradient()
{
	int i1 = 0, i2 = 1, i;
	float d = 0.0f, t;
	switch (app_Gradient.Type)
	{
	case gtVertical:
		d = 1.0f - var_TCoord.y;
		break;
	case gtRadial:
	{
		float x0 = var_TCoord.x - 0.5f;
		float y0 = 0.5f - var_TCoord.y;
		d = sqrt(2.0f * (x0 * x0 + y0 * y0));
		break;
	}
	case gtDiagonalUp:
	{
		d = (var_TCoord.x + var_TCoord.y) / 2.0f;
		break;
	}
	case gtDiagonalDown:
	{
		d = (var_TCoord.x + 1.0f - var_TCoord.y) / 2.0f;
		break;
	}
	case gtCircle:
	{
		d = sqrt(var_TCoord.x * var_TCoord.x + var_TCoord.y * var_TCoord.y);
		if (d > 1.0f)
			return vec4(0, 0, 0, 0);
		break;
	}
	default: //gtHorizontal
		d = var_TCoord.x;
		break;
	}
	for (i = 1; i < app_Gradient.Size; i++)
		if (texelFetch(app_Gradient.PositionSampler, ivec2(i, 0), 0).r >= d)
		{
			i1 = i - 1;
			i2 = i;
			break;
		}
	t = (d - texelFetch(app_Gradient.PositionSampler, ivec2(i1, 0), 0).r) / (texelFetch(app_Gradient.PositionSampler, ivec2(i2, 0), 0).r - texelFetch(app_Gradient.PositionSampler, ivec2(i1, 0), 0).r);
	vec4 result = HSVToRGB(texelFetch(app_Gradient.ColorSampler, ivec2(i1, 0), 0) * (1.0f - t) + texelFetch(app_Gradient.ColorSampler, ivec2(i2, 0), 0) * t);
	return vec4(result.r * result.a, result.g * result.a, result.b * result.a, result.a);
}

vec4 PatternHSVPlane()
{
	vec4 r = HSVToRGB(vec4(app_HSVPlane.Hue, var_TCoord.x, var_TCoord.y, 1));
	return vec4(r.r * r.a, r.g * r.a, r.b * r.a, r.a);
}

vec4 Pattern()
{
	switch (app_SubroutinePattern)
	{
		case 1: return PatternGradient();
		case 2: return texture(app_Texture.Sampler, var_TCoord) * app_Texture.Transparency;
		case 3: return PatternTextureMultisample();
		case 4: return BlockPointColor(var_PCoord, blockPrimitive);
		case 5: return PatternText();
		case 6: return PatternBlurHGaussian();
		case 7: return PatternBlurVGaussian();
		case 8: return PatternBlurHAverage();
		case 9: return PatternBlurVAverage();
		case 10: return vec4(0, 0, 0, texture(app_Texture.Sampler, var_TCoord).a * texture(app_Mask.Sampler, vec2(var_MCoord.x / app_Mask.Size.x, 1.0f - var_MCoord.y / app_Mask.Size.y)).a);
		case 11: return PatternChecker();
		case 12: return PatternHSVGradient();
		case 13: return PatternHSVPlane();
	}
	return var_Color;
}

// Entry point
void main()
{
	FragColor = Pattern();
	FragColor *= SubTestBlock();
	FragColor *= SubTestMask();
	FragColor *= SubBitmask();
	FragColor *= SubSplineLimit();
}
)==="
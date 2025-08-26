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
subroutine vec4 SubPattern();
subroutine float SubTestBlock();
subroutine float SubTestMask();
subroutine float SubBitMask();
subroutine float SubSplineLimit();

// Subroutine variables
subroutine uniform SubPattern Pattern;
subroutine uniform SubTestBlock TestBlock;
subroutine uniform SubTestMask TestMask;
subroutine uniform SubBitMask BitMask;
subroutine uniform SubSplineLimit SplineLimit;

// Pattern subroutines
subroutine (SubPattern) vec4 PatternColor()
{
	return var_Color;
}

subroutine (SubPattern) vec4 PatternGradient()
{
	int i1 = 0, i2 = 1, i;
	float d = 0, t;
	switch (app_Gradient.Type)
	{
	case gtVertical:
		d = 1 - var_TCoord.y;
		break;
	case gtRadial:
	{
		float x0 = var_TCoord.x - 0.5;
		float y0 = 0.5 - var_TCoord.y;
		d = sqrt(2 * (x0 * x0 + y0 * y0));
		break;
	}
	case gtDiagonalUp:
	{
		d = (var_TCoord.x + var_TCoord.y) / 2.0;
		break;
	}
	case gtDiagonalDown:
	{
		d = (var_TCoord.x + 1 - var_TCoord.y) / 2.0;
		break;
	}
	case gtCircle:
	{
		d = sqrt(var_TCoord.x * var_TCoord.x + var_TCoord.y * var_TCoord.y);
		if (d > 1)
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
	return texelFetch(app_Gradient.ColorSampler, ivec2(i1, 0), 0) * (1 - t) + texelFetch(app_Gradient.ColorSampler, ivec2(i2, 0), 0) * t;
}

subroutine (SubPattern) vec4 PatternTexture()
{
	return texture(app_Texture.Sampler, var_TCoord) * app_Texture.Transparency;
}

subroutine (SubPattern) vec4 PatternTextureMultisample()
{
	ivec2 texSize = textureSize(app_Texture.Multisampler);
	ivec2 texCoord = ivec2(var_TCoord * texSize);
	vec4 color = vec4(0, 0, 0, 0);
    for (int i = 0; i < app_Texture.SampleCount; i++)
        color += texelFetch(app_Texture.Multisampler, texCoord, i);
    color /= float(app_Texture.SampleCount);
	return color * app_Texture.Transparency;
}

subroutine (SubPattern) vec4 PatternBlock()
{
	return BlockPointColor(var_PCoord, blockPrimitive);
}

subroutine (SubPattern) vec4 PatternText()
{
	float alpha = texture(app_Texture.Sampler, var_TCoord).r * var_Color.a;
	return vec4(var_Color.r * alpha, var_Color.g * alpha, var_Color.b * alpha, alpha);
}

subroutine (SubPattern) vec4 PatternBlurHGaussian()
{
	float sum = 0;
	vec4 result = vec4(0, 0, 0, 0);
	for (int i = -app_Blur.Radius; i <= app_Blur.Radius; i++)
	{
		float weight = app_Blur.K * exp(app_Blur.KExp * i * i);
		sum += weight;
		vec2 coord = vec2(var_TCoord.x + app_Blur.Disp.x * i, var_TCoord.y);
		result += texture(app_Texture.Sampler, coord) * weight;
	}
	return result / sum;
}

subroutine (SubPattern) vec4 PatternBlurVGaussian()
{
	float sum = 0;
	vec4 result = vec4(0, 0, 0, 0);
	for (int i = -app_Blur.Radius; i <= app_Blur.Radius; i++)
	{
		float weight = app_Blur.K * exp(app_Blur.KExp * i * i);
		sum += weight;
		vec2 coord = vec2(var_TCoord.x, var_TCoord.y + app_Blur.Disp.y * i);
		result += texture(app_Texture.Sampler, coord) * weight;
	}
	return result / sum;
}

subroutine (SubPattern) vec4 PatternBlurHAverage()
{
	vec4 result = vec4(0, 0, 0, 0);
	for (int i = -app_Blur.Radius; i <= app_Blur.Radius; i++)
	{
		vec2 coord = vec2(var_TCoord.x + app_Blur.Disp.x * i, var_TCoord.y);
		result += texture(app_Texture.Sampler, coord);
	}
	return result / (2 * app_Blur.Radius + 1);
}

subroutine (SubPattern) vec4 PatternBlurVAverage()
{
	vec4 result = vec4(0, 0, 0, 0);
	for (int i = -app_Blur.Radius; i <= app_Blur.Radius; i++)
	{
		vec2 coord = vec2(var_TCoord.x, var_TCoord.y + app_Blur.Disp.y * i);
		result += texture(app_Texture.Sampler, coord);
	}
	return result / (2 * app_Blur.Radius + 1);
}

subroutine (SubPattern) vec4 PatternMask()
{
	return vec4(0, 0, 0, texture(app_Texture.Sampler, var_TCoord).a * texture(app_Mask.Sampler, vec2(var_MCoord.x / app_Mask.Size.x, 1 - var_MCoord.y / app_Mask.Size.y)).a);
}

subroutine (SubPattern) vec4 PatternChecker()
{
	int x = int(var_TCoord.x), y = int(var_TCoord.y);
	return (((x + y) % 2) == 0) ? app_Checker.Color1 : app_Checker.Color2;
}

subroutine (SubPattern) vec4 PatternHSVGradient()
{
	int i1 = 0, i2 = 1, i;
	float d = 0, t;
	switch (app_Gradient.Type)
	{
	case gtVertical:
		d = 1 - var_TCoord.y;
		break;
	case gtRadial:
	{
		float x0 = var_TCoord.x - 0.5;
		float y0 = 0.5 - var_TCoord.y;
		d = sqrt(2 * (x0 * x0 + y0 * y0));
		break;
	}
	case gtDiagonalUp:
	{
		d = (var_TCoord.x + var_TCoord.y) / 2.0;
		break;
	}
	case gtDiagonalDown:
	{
		d = (var_TCoord.x + 1 - var_TCoord.y) / 2.0;
		break;
	}
	case gtCircle:
	{
		d = sqrt(var_TCoord.x * var_TCoord.x + var_TCoord.y * var_TCoord.y);
		if (d > 1)
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
	vec4 result = HSVToRGB(texelFetch(app_Gradient.ColorSampler, ivec2(i1, 0), 0) * (1 - t) + texelFetch(app_Gradient.ColorSampler, ivec2(i2, 0), 0) * t);
	return vec4(result.r * result.a, result.g * result.a, result.b * result.a, result.a);
}

subroutine (SubPattern) vec4 PatternHSVPlane()
{
	vec4 r = HSVToRGB(vec4(app_HSVPlane.Hue, var_TCoord.x, var_TCoord.y, 1));
	return vec4(r.r * r.a, r.g * r.a, r.b * r.a, r.a);
}

// TestBlock subroutines
subroutine (SubTestBlock) float TestBlockNone()
{
	return 1.0f;
}

subroutine (SubTestBlock) float TestBlockExists()
{
	return (BlockPointLocation(var_FormCoord, blockLimit) == app_BlockPointLocation) ? 1.0f : 0.0f;
}

// TestMask subroutines
subroutine (SubTestMask) float TestMaskNone()
{
	return 1.0f;
}

subroutine (SubTestMask) float TestMaskExists()
{
	return texture(app_Mask.Sampler, vec2(var_MCoord.x / app_Mask.Size.x, 1 - var_MCoord.y / app_Mask.Size.y)).a;
}

// BitMask subroutine
subroutine (SubBitMask) float BitMaskNone()
{
	return 1.0f;
}

subroutine (SubBitMask) float BitMask1D()
{
	uint bit_x = uint(var_BitMask.x) % 32;
	uint cmp_x = 1 << bit_x;
	return ((app_Bitmask.X & cmp_x) > 0) ? 1.0f : 0.0f;
}

subroutine (SubBitMask) float BitMask2D()
{
	uint bit_x = uint(var_BitMask.x) % 32;
	uint bit_y = uint(var_BitMask.y) % 32;
	uint cmp_x = 1 << bit_x, cmp_y = 1 << bit_y;
	return ((app_Bitmask.X & cmp_x) > 0 && (app_Bitmask.Y & cmp_y) > 0) ? 1.0f : 0.0f;
}

subroutine (SubBitMask) float BitMaskForm()
{
	uint bit_x = uint(var_FormCoord.x) % 32;
	uint bit_y = uint(var_FormCoord.y) % 32;
	uint cmp_x = 1 << bit_x, cmp_y = 1 << bit_y;
	return ((app_Bitmask.X & cmp_x) > 0 && (app_Bitmask.Y & cmp_y) > 0) ? 1.0f : 0.0f;
}

// SplineLimit subroutine
subroutine (SubSplineLimit) float SplineLimitNone()
{
	return 1.0f;
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
	FragColor = Pattern();
	FragColor *= TestBlock();
	FragColor *= TestMask();
	FragColor *= BitMask();
	FragColor *= SplineLimit();
}
)==="
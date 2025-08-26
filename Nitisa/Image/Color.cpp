// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Operators
	std::wostream &operator<<(std::wostream &stream, const Color &a)
	{
		stream << L"{ " << a.R << L", " << a.G << L", " << a.B << L", " << a.A << L" }";
		return stream;
	}
#pragma endregion

#pragma region Conversion
	float LabHue(const float a, const float b)
	{
		return 1 / std::tan(b / a);
	}

	float LabSaturation(const float a, const float b)
	{
		return std::sqrt(a * a + b * b);
	}

	void RGBToLab(const float r, const float g, const float b, float &L, float &A, float &B)
	{
		L = (r + g + b) / 3;
		A = (2 * b - r - g) / 4 + 0.5f;
		B = (r - b) / 2 + 0.5f;
	}

	void LabToRGB(const float L, const float A, const float B, float &r, float &g, float &b)
	{
		r = 2 * B - 5 / 3.0f + 4 * A / 3 + L;
		g = L - 2 * B + 7 / 3.0f - 8 * A / 3.0f;
		b = 4 * A / 3 + L - 2 / 3.0f;
	}

	void RGBToYCbCr(const float r, const float g, const float b, const float gamma, const float Kr, const float Kg, const float Kb, float &y, float &cb, float &cr)
	{
		float r1{ std::pow(r, gamma) }, g1{ std::pow(g, gamma) }, b1{ std::pow(b, gamma) };
		y = Kr * r1 + Kg * g1 + Kb * b1;
		cb = (b1 - y) / (2 * (1 - Kb)) + 0.5f;
		cr = (r1 - y) / (2 * (1 - Kr)) + 0.5f;
	}

	void YCbCrToRGB(const float y, const float cb, const float cr, const float gamma, const float Kr, const float Kg, const float Kb, float &r, float &g, float &b)
	{
		float r1{ (cr - 0.5f) * 2 * (1 - Kr) + y }, b1{ (cb - 0.5f) * 2 * (1 - Kb) + y };
		r = std::pow(r1, 1 / gamma);
		b = std::pow(b1, 1 / gamma);
		g = std::pow((y - Kr * r1 - Kb * b1) / Kg, 1 / gamma);
	}

	void RGBToHSV(const float r, const float g, const float b, float &h, float &s, float &v)
	{
		float Cmax{ ntl::Max<float>(r, g, b) }, Cmin{ ntl::Min<float>(r, g, b) }, d{ Cmax - Cmin };
		if (d == 0)
			h = 0;
		else if (Cmax == r)
		{
			if (g >= b)
				h = (g - b) / (6 * d);
			else
				h = (g - b) / (6 * d) + 1;
		}
		else if (Cmax == g)
			h = ((b - r) / d + 2) / 6;
		else
			h = ((r - g) / d + 4) / 6;
		if (Cmax == 0)
			s = 0;
		else
			s = d / Cmax;
		v = Cmax;
	}

	void HSVToRGB(const float h, const float s, const float v, float &r, float &g, float &b)
	{
		float C{ v * s }, X{ C * (1 - ntl::Abs<float>(std::fmod(h * 6, 2.0f) - 1)) }, m{ v - C };
		if (h <= 1 / 6.0f)
		{
			r = C + m;
			g = X + m;
			b = m;
		}
		else if (h <= 2 / 6.0f)
		{
			r = X + m;
			g = C + m;
			b = m;
		}
		else if (h <= 3 / 6.0f)
		{
			r = m;
			g = C + m;
			b = X + m;
		}
		else if (h <= 4 / 6.0f)
		{
			r = m;
			g = X + m;
			b = C + m;
		}
		else if (h <= 5 / 6.0f)
		{
			r = X + m;
			g = m;
			b = C + m;
		}
		else
		{
			r = C + m;
			g = m;
			b = X + m;
		}
	}

	void RGBToHSI(const float r, const float g, const float b, float &h, float &s, float &i)
	{
		float MAX{ ntl::Max<float>(r, g, b) }, MIN{ ntl::Min<float>(r, g, b) }, d{ MAX - MIN };
		if (d == 0)
			h = 0;
		else if (MAX == r)
		{
			if (g >= b)
				h = (g - b) / (6 * d);
			else
				h = (g - b) / (6 * d) + 1;
		}
		else if (MAX == g)
			h = ((b - r) / d + 2) / 6;
		else
			h = ((r - g) / d + 4) / 6;
		i = (r + g + b) / 3;
		if (i == 0)
			s = 0;
		else
			s = 1 - MIN / i;
	}

	void HSIToRGB(const float h, const float s, const float i, float &r, float &g, float &b)
	{
		float H{ h * 360 };
		if (H <= 120)
		{
			b = i * (1 - s);
			r = i * (1 + s * std::cos(ntl::DegToRad<float>(H)) / std::cos(ntl::DegToRad<float>(60 - H)));
			g = 3 * i - b - r;
		}
		else if (H <= 240)
		{
			r = i * (1 - s);
			g = i * (1 + s * std::cos(ntl::DegToRad<float>(H - 120)) / std::cos(ntl::DegToRad<float>(180 - H)));
			b = 3 * i - r - g;
		}
		else
		{
			g = i * (1 - s);
			b = i * (1 + s * std::cos(ntl::DegToRad<float>(H - 240)) / std::cos(ntl::DegToRad<float>(300 - H)));
			r = 3 * i - r - g;
		}
	}

	void RGBToHSL(const float r, const float g, const float b, float &h, float &s, float &l)
	{
		float MAX{ ntl::Max<float>(r, g, b) }, MIN{ ntl::Min<float>(r, g, b) }, d{ MAX - MIN };
		if (d == 0)
			h = 0;
		else if (MAX == r)
		{
			if (g >= b)
				h = (g - b) / (6 * d);
			else
				h = (g - b) / (6 * d) + 1;
		}
		else if (MAX == g)
			h = ((b - r) / d + 2) / 6;
		else
			h = ((r - g) / d + 4) / 6;
		l = (MAX + MIN) / 2;
		if (d == 0)
			s = 0;
		else
			s = d / (1 - std::abs(2 * l - 1));
	}

	void HSLToRGB(const float h, const float s, const float l, float &r, float &g, float &b)
	{
		float H{ h * 360 };
		int Hi{ ntl::Round<int>(H / 60) % 6 };
		float C{ (1 - ntl::Abs<float>(2 * l - 1)) * s }, X{ C * float(1 - ntl::Abs<int>(ntl::Round<int>(H / 60) % 2 - 1)) }, m{ l - C / 2 };
		switch (Hi)
		{
		case 0:
			r = C + m;
			g = X + m;
			b = m;
			break;
		case 1:
			r = X + m;
			g = C + m;
			b = m;
			break;
		case 2:
			r = m;
			g = C + m;
			b = X + m;
			break;
		case 3:
			r = m;
			g = X + m;
			b = C + m;
			break;
		case 4:
			r = X + m;
			g = m;
			b = C + m;
			break;
		default:
			r = C + m;
			g = m;
			b = X + m;
		}
	}

	String AsSourceCode(const Color &a)
	{
		return L"Color{ " + ToString(a.R) + L", " + ToString(a.G) + L", " + ToString(a.B) + L", " + ToString(a.A) + L" }";
	}

	String ToString(const Color &value)
	{
		return ToString(value.R) + L", " + ToString(value.G) + L", " + ToString(value.B) + L", " + ToString(value.A);
	}

	Variant ToVariant(const Color &value)
	{
		Variant result;
		result.push_back((Variant)value.R);
		result.push_back((Variant)value.G);
		result.push_back((Variant)value.B);
		result.push_back((Variant)value.A);
		return result;
	}

	void FromVariant(const Variant &value, Color &dest)
	{
		dest = Color{ (unsigned char)(int)value.get(0), (unsigned char)(int)value.get(1), (unsigned char)(int)value.get(2), (unsigned char)(int)value.get(3) };
	}
#pragma endregion
}
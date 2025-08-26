// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Utils.h"
#include "../Core/Strings.h"
#include "../Core/Variant.h"
#include <iostream>

namespace nitisa
{
	constexpr float RGB_TO_YCBCR_KR_BROADCAST_TV{ 0.299f };
	constexpr float RGB_TO_YCBCR_KG_BROADCAST_TV{ 0.587f };
	constexpr float RGB_TO_YCBCR_KB_BROADCAST_TV{ 0.114f };
	constexpr float RGB_TO_YCBCR_KR_MONITOR{ 0.2126f };
	constexpr float RGB_TO_YCBCR_KG_MONITOR{ 0.7152f };
	constexpr float RGB_TO_YCBCR_KB_MONITOR{ 0.0722f };

	union Color
	{
		struct
		{
			unsigned char R; // Red channel
			unsigned char G; // Green channel
			unsigned char B; // Blue channel
			unsigned char A; // Alpha/transparency channel
		};
		struct
		{
			unsigned char Red;
			unsigned char Green;
			unsigned char Blue;
			unsigned char Alpha;
		};
		unsigned char Data[4]; // Channels

		unsigned char operator[](const int channel) const // Get channel value
		{
			return Data[channel];
		}

		unsigned char &operator[](const int channel) // Get channel value
		{
			return Data[channel];
		}

		bool operator==(const Color &other) const // Check if colors are equal
		{
			return R == other.R && G == other.G && B == other.B && A == other.A;
		}

		bool operator!=(const Color &other) const // Check if colors are not equal
		{
			return R != other.R || G != other.G || B != other.B || A != other.A;
		}

		Color operator*(const Color &other) const // Blend colors
		{
			int A{ (255 - other.A) };
			return Color{ (unsigned char)((R * A + other.R * other.A) >> 8), (unsigned char)((G * A + other.G * other.A) >> 8), (unsigned char)((B * A + other.B * other.A) >> 8), Alpha };
		}

		Color operator+(const Color &other) const // Add(blCanvas mode) colors
		{
			return {
				(unsigned char)(((other.R * 255) + R * (255 - other.A)) / 255),
				(unsigned char)(((other.G * 255) + G * (255 - other.A)) / 255),
				(unsigned char)(((other.B * 255) + B * (255 - other.A)) / 255),
				(unsigned char)((other.A * (255 - A) + (A * 255)) / 255) };
		}

		Color &operator*=(Color &other) // Blend colors in first one
		{
			int A{ (255 - other.A) };
			R = (unsigned char)((R * A + other.R * other.A) >> 8);
			G = (unsigned char)((G * A + other.G * other.A) >> 8);
			B = (unsigned char)((B * A + other.B * other.A) >> 8);
			return *this;
		}

		Color &operator+=(Color &other) // Add(blCanvas mode) colors and store result in first one
		{
			R = (unsigned char)(((other.R * 255) + R * (255 - other.A)) / 255);
			G = (unsigned char)(((other.G * 255) + G * (255 - other.A)) / 255);
			B = (unsigned char)(((other.B * 255) + B * (255 - other.A)) / 255);
			A = (unsigned char)((other.A * (255 - A) + (A * 255)) / 255);
			return *this;
		}

		unsigned char average() const // Return average value over all channels except the last one(grayscale)
		{
			return (unsigned char)(float(R + G + B) / 3.0f + 0.5f);
		}
	};

	std::wostream &operator<<(std::wostream &stream, const Color &a); // Output as source code

	float LabHue(const float a, const float b); // Return hue of LAB color space
	float LabSaturation(const float a, const float b); // Return saturation of LAB color space
	void LabToRGB(const float L, const float A, const float B, float &r, float &g, float &b); // Convert color from LAB to RGB color space
	void RGBToYCbCr(const float r, const float g, const float b, const float gamma, const float Kr, const float Kg, const float Kb, float &y, float &cb, float &cr); // Convert color from RGB to YCbCr color space
	void YCbCrToRGB(const float y, const float cb, const float cr, const float gamma, const float Kr, const float Kg, const float Kb, float &r, float &g, float &b); // Convert color from YCbCr to RGB color space
	void RGBToLab(const float r, const float g, const float b, float &L, float &A, float &B); // Convert color from RGB to LAB color space
	void RGBToHSV(const float r, const float g, const float b, float &h, float &s, float &v); // Convert color from RGB to HSV color space
	void HSVToRGB(const float h, const float s, const float v, float &r, float &g, float &b); // Convert color from HSV to RGB color space
	void RGBToHSI(const float r, const float g, const float b, float &h, float &s, float &i); // Convert color from RGB to HSI color space
	void HSIToRGB(const float h, const float s, const float i, float &r, float &g, float &b); // Convert color from HSI to RGB color space
	void RGBToHSL(const float r, const float g, const float b, float &h, float &s, float &l); // Convert color from RGB to HSL color space
	void HSLToRGB(const float h, const float s, const float l, float &r, float &g, float &b); // Convert color from HSL to RGB color space

	String AsSourceCode(const Color &a);
	String ToString(const Color &value);
	Variant ToVariant(const Color &value);
	void FromVariant(const Variant &value, Color &dest);

	inline Color LabToColor(const float L, const float A, const float B, const float a) // Convert color from LAB to RGBA
	{
		float r, g, b;
		LabToRGB(L, A, B, r, g, b);
		return Color{ ntl::Round<unsigned char>(r * 255), ntl::Round<unsigned char>(g * 255), ntl::Round<unsigned char>(b * 255), ntl::Round<unsigned char>(a * 255) };
	}

	inline Color YCbCrToColor(const float y, const float cb, const float cr, const float gamma, const float Kr, const float Kg, const float Kb, const float a) // Convert color from YCbCr to RGBA
	{
		float r, g, b;
		YCbCrToRGB(y, cb, cr, gamma, Kr, Kg, Kb, r, g, b);
		return Color{ ntl::Round<unsigned char>(r * 255), ntl::Round<unsigned char>(g * 255), ntl::Round<unsigned char>(b * 255), ntl::Round<unsigned char>(a * 255) };
	}

	inline Color HSVToColor(const float h, const float s, const float v, const float a) // Convert color from HSV to RGBA
	{
		float r, g, b;
		HSVToRGB(h, s, v, r, g, b);
		return Color{ ntl::Round<unsigned char>(r * 255), ntl::Round<unsigned char>(g * 255), ntl::Round<unsigned char>(b * 255), ntl::Round<unsigned char>(a * 255) };
	}

	inline Color HSIToColor(const float h, const float s, const float i, const float a) // Convert color from HSI to RGBA
	{
		float r, g, b;
		HSIToRGB(h, s, i, r, g, b);
		return Color{ ntl::Round<unsigned char>(r * 255), ntl::Round<unsigned char>(g * 255), ntl::Round<unsigned char>(b * 255), ntl::Round<unsigned char>(a * 255) };
	}

	inline Color HSLToColor(const float h, const float s, const float l, const float a) // Convert color from HSL to RGBA
	{
		float r, g, b;
		HSLToRGB(h, s, l, r, g, b);
		return Color{ ntl::Round<unsigned char>(r * 255), ntl::Round<unsigned char>(g * 255), ntl::Round<unsigned char>(b * 255), ntl::Round<unsigned char>(a * 255) };
	}

	inline void ColorToLab(const Color &color, float &L, float &A, float &B) // Convert color from RGBA to LAB
	{
		RGBToLab(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, L, A, B);
	}

	inline void ColorToYCbCr(const Color &color, const float gamma, const float Kr, const float Kg, const float Kb, float &y, float &cb, float &cr) // Convert color from RGBA to YCbCr
	{
		RGBToYCbCr(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, gamma, Kr, Kg, Kb, y, cb, cr);
	}

	inline void ColorToHSV(const Color &color, float &h, float &s, float &v) // Convert color from RGBA to HSV
	{
		RGBToHSV(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, h, s, v);
	}

	inline void ColorToHSI(const Color &color, float &h, float &s, float &i) // Convert color from RGBA to HSI
	{
		RGBToHSI(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, h, s, i);
	}

	inline void ColorToHSL(const Color &color, float &h, float &s, float &l) // Convert color from RGBA to HSL
	{
		RGBToHSL(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, h, s, l);
	}
}
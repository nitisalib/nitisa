// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "Color.h"

namespace nitisa
{
	class CColor
	{
	private:
		nitisa::Color m_sColor;
		String m_sName;
		bool m_bStandard;
		bool m_bNone;
	public:
		nitisa::Color const &Color{ m_sColor };
		String const &Name{ m_sName };
		bool const &isStandard{ m_bStandard };
		bool const &isNone{ m_bNone };

		CColor(const nitisa::Color &color, const String &name, const bool standard, const bool none) : // Construct with specified color, its name, whether it is a standard color, whether it is not a color
			m_sColor{ color },
			m_sName{ name },
			m_bStandard{ standard },
			m_bNone{ none }
		{

		}

		operator nitisa::Color() const // Convert to Color
		{
			return m_sColor;
		}

		operator String() const // Convert to String
		{
			return m_sName;
		}
	};

	class CColors
	{
	public:
		// Standard colors
		static const CColor Black;
		static const CColor Maroon;
		static const CColor Green;
		static const CColor Olive;
		static const CColor Navy;
		static const CColor Purple;
		static const CColor Teal;
		static const CColor Gray;
		static const CColor Silver;
		static const CColor Red;
		static const CColor Lime;
		static const CColor Yellow;
		static const CColor Blue;
		static const CColor Fuchsia;
		static const CColor Aqua;
		static const CColor White;
		// None color
		static const CColor None;
		// Extended colors
		static const CColor AliceBlue;
		static const CColor AntiqueWhite;
		static const CColor Aquamarine;
		static const CColor Azure;
		static const CColor Beige;
		static const CColor Bisque;
		static const CColor BlanchedAlmond;
		static const CColor BlueViolet;
		static const CColor Brown;
		static const CColor BurlyWood;
		static const CColor CadetBlue;
		static const CColor Chartreuse;
		static const CColor Chocolate;
		static const CColor Coral;
		static const CColor CornflowerBlue;
		static const CColor Cornsilk;
		static const CColor Crimson;
		static const CColor Cyan;
		static const CColor DarkBlue;
		static const CColor DarkCyan;
		static const CColor DarkGoldenRod;
		static const CColor DarkGray;
		static const CColor DarkGreen;
		static const CColor DarkKhaki;
		static const CColor DarkMagenta;
		static const CColor DarkOliveGreen;
		static const CColor DarkOrange;
		static const CColor DarkOrchid;
		static const CColor DarkRed;
		static const CColor DarkSalmon;
		static const CColor DarkSeaGreen;
		static const CColor DarkSlateBlue;
		static const CColor DarkSlateGray;
		static const CColor DarkTurquoise;
		static const CColor DarkViolet;
		static const CColor DeepPink;
		static const CColor DeepSkyBlue;
		static const CColor DimGray;
		static const CColor DodgerBlue;
		static const CColor FireBrick;
		static const CColor FloralWhite;
		static const CColor ForestGreen;
		static const CColor Gainsboro;
		static const CColor GhostWhite;
		static const CColor Gold;
		static const CColor GoldenRod;
		static const CColor GreenYellow;
		static const CColor HoneyDew;
		static const CColor HotPink;
		static const CColor IndianRed;
		static const CColor Indigo;
		static const CColor Ivory;
		static const CColor Khaki;
		static const CColor Lavender;
		static const CColor LavenderBlush;
		static const CColor LawnGreen;
		static const CColor LemonChiffon;
		static const CColor LightBlue;
		static const CColor LightCoral;
		static const CColor LightCyan;
		static const CColor LightGoldenRodYellow;
		static const CColor LightGray;
		static const CColor LightGreen;
		static const CColor LightPink;
		static const CColor LightSalmon;
		static const CColor LightSeaGreen;
		static const CColor LightSkyBlue;
		static const CColor LightSlateGray;
		static const CColor LightSteelBlue;
		static const CColor LightYellow;
		static const CColor LimeGreen;
		static const CColor Linen;
		static const CColor Magenta;
		static const CColor MediumAquaMarine;
		static const CColor MediumBlue;
		static const CColor MediumOrchid;
		static const CColor MediumPurple;
		static const CColor MediumSeaGreen;
		static const CColor MediumSlateBlue;
		static const CColor MediumSpringGreen;
		static const CColor MediumTurquoise;
		static const CColor MediumVioletRed;
		static const CColor MidnightBlue;
		static const CColor MintCream;
		static const CColor MistyRose;
		static const CColor Moccasin;
		static const CColor NavajoWhite;
		static const CColor OldLace;
		static const CColor OliveDrab;
		static const CColor Orange;
		static const CColor OrangeRed;
		static const CColor Orchid;
		static const CColor PaleGoldenRod;
		static const CColor PaleGreen;
		static const CColor PaleTurquoise;
		static const CColor PaleVioletRed;
		static const CColor PapayaWhip;
		static const CColor PeachPuff;
		static const CColor Peru;
		static const CColor Pink;
		static const CColor Plum;
		static const CColor PowderBlue;
		static const CColor RebeccaPurple;
		static const CColor RosyBrown;
		static const CColor RoyalBlue;
		static const CColor SaddleBrown;
		static const CColor Salmon;
		static const CColor SandyBrown;
		static const CColor SeaGreen;
		static const CColor SeaShell;
		static const CColor Sienna;
		static const CColor SkyBlue;
		static const CColor SlateBlue;
		static const CColor SlateGray;
		static const CColor Snow;
		static const CColor SpringGreen;
		static const CColor SteelBlue;
		static const CColor Tan;
		static const CColor Thistle;
		static const CColor Tomato;
		static const CColor Turquoise;
		static const CColor Violet;
		static const CColor Wheat;
		static const CColor WhiteSmoke;
		static const CColor YellowGreen;

		template<class F> static void EnumStandardColors(F callback); // Call callback for all colors marked as standard
		template<class F> static void EnumExtendedColors(F callback); // Call callback for all colors not marked as standard
	};

#pragma region Template methods
	template<class F> void CColors::EnumStandardColors(F callback)
	{
		callback(Black);
		callback(Maroon);
		callback(Green);
		callback(Olive);
		callback(Navy);
		callback(Purple);
		callback(Teal);
		callback(Gray);
		callback(Silver);
		callback(Red);
		callback(Lime);
		callback(Yellow);
		callback(Blue);
		callback(Fuchsia);
		callback(Aqua);
		callback(White);
	}

	template<class F> void CColors::EnumExtendedColors(F callback)
	{
		callback(AliceBlue);
		callback(AntiqueWhite);
		callback(Aquamarine);
		callback(Azure);
		callback(Beige);
		callback(Bisque);
		callback(BlanchedAlmond);
		callback(BlueViolet);
		callback(Brown);
		callback(BurlyWood);
		callback(CadetBlue);
		callback(Chartreuse);
		callback(Chocolate);
		callback(Coral);
		callback(CornflowerBlue);
		callback(Cornsilk);
		callback(Crimson);
		callback(Cyan);
		callback(DarkBlue);
		callback(DarkCyan);
		callback(DarkGoldenRod);
		callback(DarkGray);
		callback(DarkGreen);
		callback(DarkKhaki);
		callback(DarkMagenta);
		callback(DarkOliveGreen);
		callback(DarkOrange);
		callback(DarkOrchid);
		callback(DarkRed);
		callback(DarkSalmon);
		callback(DarkSeaGreen);
		callback(DarkSlateBlue);
		callback(DarkSlateGray);
		callback(DarkTurquoise);
		callback(DarkViolet);
		callback(DeepPink);
		callback(DeepSkyBlue);
		callback(DimGray);
		callback(DodgerBlue);
		callback(FireBrick);
		callback(FloralWhite);
		callback(ForestGreen);
		callback(Gainsboro);
		callback(GhostWhite);
		callback(Gold);
		callback(GoldenRod);
		callback(GreenYellow);
		callback(HoneyDew);
		callback(HotPink);
		callback(IndianRed);
		callback(Indigo);
		callback(Ivory);
		callback(Khaki);
		callback(Lavender);
		callback(LavenderBlush);
		callback(LawnGreen);
		callback(LemonChiffon);
		callback(LightBlue);
		callback(LightCoral);
		callback(LightCyan);
		callback(LightGoldenRodYellow);
		callback(LightGray);
		callback(LightGreen);
		callback(LightPink);
		callback(LightSalmon);
		callback(LightSeaGreen);
		callback(LightSkyBlue);
		callback(LightSlateGray);
		callback(LightSteelBlue);
		callback(LightYellow);
		callback(LimeGreen);
		callback(Linen);
		callback(Magenta);
		callback(MediumAquaMarine);
		callback(MediumBlue);
		callback(MediumOrchid);
		callback(MediumPurple);
		callback(MediumSeaGreen);
		callback(MediumSlateBlue);
		callback(MediumSpringGreen);
		callback(MediumTurquoise);
		callback(MediumVioletRed);
		callback(MidnightBlue);
		callback(MintCream);
		callback(MistyRose);
		callback(Moccasin);
		callback(NavajoWhite);
		callback(OldLace);
		callback(OliveDrab);
		callback(Orange);
		callback(OrangeRed);
		callback(Orchid);
		callback(PaleGoldenRod);
		callback(PaleGreen);
		callback(PaleTurquoise);
		callback(PaleVioletRed);
		callback(PapayaWhip);
		callback(PeachPuff);
		callback(Peru);
		callback(Pink);
		callback(Plum);
		callback(PowderBlue);
		callback(RebeccaPurple);
		callback(RosyBrown);
		callback(RoyalBlue);
		callback(SaddleBrown);
		callback(Salmon);
		callback(SandyBrown);
		callback(SeaGreen);
		callback(SeaShell);
		callback(Sienna);
		callback(SkyBlue);
		callback(SlateBlue);
		callback(SlateGray);
		callback(Snow);
		callback(SpringGreen);
		callback(SteelBlue);
		callback(Tan);
		callback(Thistle);
		callback(Tomato);
		callback(Turquoise);
		callback(Violet);
		callback(Wheat);
		callback(WhiteSmoke);
		callback(YellowGreen);
	}
#pragma endregion
}
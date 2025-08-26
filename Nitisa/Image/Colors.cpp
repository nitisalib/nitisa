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
	// Standard colors
	const CColor CColors::Black{ Color{ 0x00, 0x00, 0x00, 0xFF }, L"Black", true, false };
	const CColor CColors::Maroon{ Color{ 0x80, 0x00, 0x00, 0xFF }, L"Maroon", true, false };
	const CColor CColors::Green{ Color{ 0x00, 0x80, 0x00, 0xFF }, L"Green", true, false };
	const CColor CColors::Olive{ Color{ 0x80, 0x80, 0x00, 0xFF }, L"Olive", true, false };
	const CColor CColors::Navy{ Color{ 0x00, 0x00, 0x80, 0xFF }, L"Navy", true, false };
	const CColor CColors::Purple{ Color{ 0x80, 0x00, 0x80, 0xFF }, L"Purple", true, false };
	const CColor CColors::Teal{ Color{ 0x00, 0x80, 0x80, 0xFF }, L"Teal", true, false };
	const CColor CColors::Gray{ Color{ 0x80, 0x80, 0x80, 0xFF }, L"Gray", true, false };
	const CColor CColors::Silver{ Color{ 0xC0, 0xC0, 0xC0, 0xFF }, L"Silver", true, false };
	const CColor CColors::Red{ Color{ 0xFF, 0x00, 0x00, 0xFF }, L"Red", true, false };
	const CColor CColors::Lime{ Color{ 0x00, 0xFF, 0x00, 0xFF }, L"Lime", true, false };
	const CColor CColors::Yellow{ Color{ 0xFF, 0xFF, 0x00, 0xFF }, L"Yellow", true, false };
	const CColor CColors::Blue{ Color{ 0x00, 0x00, 0xFF, 0xFF }, L"Blue", true, false };
	const CColor CColors::Fuchsia{ Color{ 0xFF, 0x00, 0xFF, 0xFF }, L"Fuchsia", true, false };
	const CColor CColors::Aqua{ Color{ 0x00, 0xFF, 0xFF, 0xFF }, L"Aqua", true, false };
	const CColor CColors::White{ Color{ 0xFF, 0xFF, 0xFF, 0xFF }, L"White", true, false };
	// None color
	const CColor CColors::None{ Color{ 0x00, 0x00, 0x00, 0x00 }, L"None", true, true };
	// Extended colors
	const CColor CColors::AliceBlue{ Color{ 0xF0, 0xF8, 0xFF, 0xFF }, L"AliceBlue", false, false };
	const CColor CColors::AntiqueWhite{ Color{ 0xFA, 0xEB, 0xD7, 0xFF }, L"AntiqueWhite", false, false };
	const CColor CColors::Aquamarine{ Color{ 0x7F, 0xFF, 0xD4, 0xFF }, L"Aquamarine", false, false };
	const CColor CColors::Azure{ Color{ 0xF0, 0xFF, 0xFF, 0xFF }, L"Azure", false, false };
	const CColor CColors::Beige{ Color{ 0xF5, 0xF5, 0xDC, 0xFF }, L"Beige", false, false };
	const CColor CColors::Bisque{ Color{ 0xFF, 0xE4, 0xC4, 0xFF }, L"Bisque", false, false };
	const CColor CColors::BlanchedAlmond{ Color{ 0xFF, 0xEB, 0xCD, 0xFF }, L"BlanchedAlmond", false, false };
	const CColor CColors::BlueViolet{ Color{ 0x8A, 0x2B, 0xE2, 0xFF }, L"BlueViolet", false, false };
	const CColor CColors::Brown{ Color{ 0xA5, 0x2A, 0x2A, 0xFF }, L"Brown", false, false };
	const CColor CColors::BurlyWood{ Color{ 0xDE, 0xB8, 0x87, 0xFF }, L"BurlyWood", false, false };
	const CColor CColors::CadetBlue{ Color{ 0x5F, 0x9E, 0xA0, 0xFF }, L"CadetBlue", false, false };
	const CColor CColors::Chartreuse{ Color{ 0x7F, 0xFF, 0x00, 0xFF }, L"Chartreuse", false, false };
	const CColor CColors::Chocolate{ Color{ 0xD2, 0x69, 0x1E, 0xFF }, L"Chocolate", false, false };
	const CColor CColors::Coral{ Color{ 0xFF, 0x7F, 0x50, 0xFF }, L"Coral", false, false };
	const CColor CColors::CornflowerBlue{ Color{ 0x64, 0x95, 0xED, 0xFF }, L"CornflowerBlue", false, false };
	const CColor CColors::Cornsilk{ Color{ 0xFF, 0xF8, 0xDC, 0xFF }, L"Cornsilk", false, false };
	const CColor CColors::Crimson{ Color{ 0xDC, 0x14, 0x3C, 0xFF }, L"Crimson", false, false };
	const CColor CColors::Cyan{ Color{ 0x00, 0xFF, 0xFF, 0xFF }, L"Cyan", false, false };
	const CColor CColors::DarkBlue{ Color{ 0x00, 0x00, 0x8B, 0xFF }, L"DarkBlue", false, false };
	const CColor CColors::DarkCyan{ Color{ 0x00, 0x8B, 0x8B, 0xFF }, L"DarkCyan", false, false };
	const CColor CColors::DarkGoldenRod{ Color{ 0xB8, 0x86, 0x0B, 0xFF }, L"DarkGoldenRod", false, false };
	const CColor CColors::DarkGray{ Color{ 0xA9, 0xA9, 0xA9, 0xFF }, L"DarkGray", false, false };
	const CColor CColors::DarkGreen{ Color{ 0x00, 0x64, 0x00, 0xFF }, L"DarkGreen", false, false };
	const CColor CColors::DarkKhaki{ Color{ 0xBD, 0xB7, 0x6B, 0xFF }, L"DarkKhaki", false, false };
	const CColor CColors::DarkMagenta{ Color{ 0x8B, 0x00, 0x8B, 0xFF }, L"DarkMagenta", false, false };
	const CColor CColors::DarkOliveGreen{ Color{ 0x55, 0x6B, 0x2F, 0xFF }, L"DarkOliveGreen", false, false };
	const CColor CColors::DarkOrange{ Color{ 0xFF, 0x8C, 0x00, 0xFF }, L"DarkOrange", false, false };
	const CColor CColors::DarkOrchid{ Color{ 0x99, 0x32, 0xCC, 0xFF }, L"DarkOrchid", false, false };
	const CColor CColors::DarkRed{ Color{ 0x8B, 0x00, 0x00, 0xFF }, L"DarkRed", false, false };
	const CColor CColors::DarkSalmon{ Color{ 0xE9, 0x96, 0x7A, 0xFF }, L"DarkSalmon", false, false };
	const CColor CColors::DarkSeaGreen{ Color{ 0x8F, 0xBC, 0x8F, 0xFF }, L"DarkSeaGreen", false, false };
	const CColor CColors::DarkSlateBlue{ Color{ 0x48, 0x3D, 0x8B, 0xFF }, L"DarkSlateBlue", false, false };
	const CColor CColors::DarkSlateGray{ Color{ 0x2F, 0x4F, 0x4F, 0xFF }, L"DarkSlateGray", false, false };
	const CColor CColors::DarkTurquoise{ Color{ 0x00, 0xCE, 0xD1, 0xFF }, L"DarkTurquoise", false, false };
	const CColor CColors::DarkViolet{ Color{ 0x94, 0x00, 0xD3, 0xFF }, L"DarkViolet", false, false };
	const CColor CColors::DeepPink{ Color{ 0xFF, 0x14, 0x93, 0xFF }, L"DeepPink", false, false };
	const CColor CColors::DeepSkyBlue{ Color{ 0x00, 0xBF, 0xFF, 0xFF }, L"DeepSkyBlue", false, false };
	const CColor CColors::DimGray{ Color{ 0x69, 0x69, 0x69, 0xFF }, L"DimGray", false, false };
	const CColor CColors::DodgerBlue{ Color{ 0x1E, 0x90, 0xFF, 0xFF }, L"DodgerBlue", false, false };
	const CColor CColors::FireBrick{ Color{ 0xB2, 0x22, 0x22, 0xFF }, L"FireBrick", false, false };
	const CColor CColors::FloralWhite{ Color{ 0xFF, 0xFA, 0xF0, 0xFF }, L"FloralWhite", false, false };
	const CColor CColors::ForestGreen{ Color{ 0x22, 0x8B, 0x22, 0xFF }, L"ForestGreen", false, false };
	const CColor CColors::Gainsboro{ Color{ 0xDC, 0xDC, 0xDC, 0xFF }, L"Gainsboro", false, false };
	const CColor CColors::GhostWhite{ Color{ 0xF8, 0xF8, 0xFF, 0xFF }, L"GhostWhite", false, false };
	const CColor CColors::Gold{ Color{ 0xFF, 0xD7, 0x00, 0xFF }, L"Gold", false, false };
	const CColor CColors::GoldenRod{ Color{ 0xDA, 0xA5, 0x20, 0xFF }, L"GoldenRod", false, false };
	const CColor CColors::GreenYellow{ Color{ 0xAD, 0xFF, 0x2F, 0xFF }, L"GreenYellow", false, false };
	const CColor CColors::HoneyDew{ Color{ 0xF0, 0xFF, 0xF0, 0xFF }, L"HoneyDew", false, false };
	const CColor CColors::HotPink{ Color{ 0xFF, 0x69, 0xB4, 0xFF }, L"HotPink", false, false };
	const CColor CColors::IndianRed{ Color{ 0xCD, 0x5C, 0x5C, 0xFF }, L"IndianRed", false, false };
	const CColor CColors::Indigo{ Color{ 0x4B, 0x00, 0x82, 0xFF }, L"Indigo", false, false };
	const CColor CColors::Ivory{ Color{ 0xFF, 0xFF, 0xF0, 0xFF }, L"Ivory", false, false };
	const CColor CColors::Khaki{ Color{ 0xF0, 0xE6, 0x8C, 0xFF }, L"Khaki", false, false };
	const CColor CColors::Lavender{ Color{ 0xE6, 0xE6, 0xFA, 0xFF }, L"Lavender", false, false };
	const CColor CColors::LavenderBlush{ Color{ 0xFF, 0xF0, 0xF5, 0xFF }, L"LavenderBlush", false, false };
	const CColor CColors::LawnGreen{ Color{ 0x7C, 0xFC, 0x00, 0xFF }, L"LawnGreen", false, false };
	const CColor CColors::LemonChiffon{ Color{ 0xFF, 0xFA, 0xCD, 0xFF }, L"LemonChiffon", false, false };
	const CColor CColors::LightBlue{ Color{ 0xAD, 0xD8, 0xE6, 0xFF }, L"LightBlue", false, false };
	const CColor CColors::LightCoral{ Color{ 0xF0, 0x80, 0x80, 0xFF }, L"LightCoral", false, false };
	const CColor CColors::LightCyan{ Color{ 0xE0, 0xFF, 0xFF, 0xFF }, L"LightCyan", false, false };
	const CColor CColors::LightGoldenRodYellow{ Color{ 0xFA, 0xFA, 0xD2, 0xFF }, L"LightGoldenRodYellow", false, false };
	const CColor CColors::LightGray{ Color{ 0xD3, 0xD3, 0xD3, 0xFF }, L"LightGray", false, false };
	const CColor CColors::LightGreen{ Color{ 0x90, 0xEE, 0x90, 0xFF }, L"LightGreen", false, false };
	const CColor CColors::LightPink{ Color{ 0xFF, 0xB6, 0xC1, 0xFF }, L"LightPink", false, false };
	const CColor CColors::LightSalmon{ Color{ 0xFF, 0xA0, 0x7A, 0xFF }, L"LightSalmon", false, false };
	const CColor CColors::LightSeaGreen{ Color{ 0x20, 0xB2, 0xAA, 0xFF }, L"LightSeaGreen", false, false };
	const CColor CColors::LightSkyBlue{ Color{ 0x87, 0xCE, 0xFA, 0xFF }, L"LightSkyBlue", false, false };
	const CColor CColors::LightSlateGray{ Color{ 0x77, 0x88, 0x99, 0xFF }, L"LightSlateGray", false, false };
	const CColor CColors::LightSteelBlue{ Color{ 0xB0, 0xC4, 0xDE, 0xFF }, L"LightSteelBlue", false, false };
	const CColor CColors::LightYellow{ Color{ 0xFF, 0xFF, 0xE0, 0xFF }, L"LightYellow", false, false };
	const CColor CColors::LimeGreen{ Color{ 0x32, 0xCD, 0x32, 0xFF }, L"LimeGreen", false, false };
	const CColor CColors::Linen{ Color{ 0xFA, 0xF0, 0xE6, 0xFF }, L"Linen", false, false };
	const CColor CColors::Magenta{ Color{ 0xFF, 0x00, 0xFF, 0xFF }, L"Magenta", false, false };
	const CColor CColors::MediumAquaMarine{ Color{ 0x66, 0xCD, 0xAA, 0xFF }, L"MediumAquaMarine", false, false };
	const CColor CColors::MediumBlue{ Color{ 0x00, 0x00, 0xCD, 0xFF }, L"MediumBlue", false, false };
	const CColor CColors::MediumOrchid{ Color{ 0xBA, 0x55, 0xD3, 0xFF }, L"MediumOrchid", false, false };
	const CColor CColors::MediumPurple{ Color{ 0x93, 0x70, 0xDB, 0xFF }, L"MediumPurple", false, false };
	const CColor CColors::MediumSeaGreen{ Color{ 0x3C, 0xB3, 0x71, 0xFF }, L"MediumSeaGreen", false, false };
	const CColor CColors::MediumSlateBlue{ Color{ 0x7B, 0x68, 0xEE, 0xFF }, L"MediumSlateBlue", false, false };
	const CColor CColors::MediumSpringGreen{ Color{ 0x00, 0xFA, 0x9A, 0xFF }, L"MediumSpringGreen", false, false };
	const CColor CColors::MediumTurquoise{ Color{ 0x48, 0xD1, 0xCC, 0xFF }, L"MediumTurquoise", false, false };
	const CColor CColors::MediumVioletRed{ Color{ 0xC7, 0x15, 0x85, 0xFF }, L"MediumVioletRed", false, false };
	const CColor CColors::MidnightBlue{ Color{ 0x19, 0x19, 0x70, 0xFF }, L"MidnightBlue", false, false };
	const CColor CColors::MintCream{ Color{ 0xF5, 0xFF, 0xFA, 0xFF }, L"MintCream", false, false };
	const CColor CColors::MistyRose{ Color{ 0xFF, 0xE4, 0xE1, 0xFF }, L"MistyRose", false, false };
	const CColor CColors::Moccasin{ Color{ 0xFF, 0xE4, 0xB5, 0xFF }, L"Moccasin", false, false };
	const CColor CColors::NavajoWhite{ Color{ 0xFF, 0xDE, 0xAD, 0xFF }, L"NavajoWhite", false, false };
	const CColor CColors::OldLace{ Color{ 0xFD, 0xF5, 0xE6, 0xFF }, L"OldLace", false, false };
	const CColor CColors::OliveDrab{ Color{ 0x6B, 0x8E, 0x23, 0xFF }, L"OliveDrab", false, false };
	const CColor CColors::Orange{ Color{ 0xFF, 0xA5, 0x00, 0xFF }, L"Orange", false, false };
	const CColor CColors::OrangeRed{ Color{ 0xFF, 0x45, 0x00, 0xFF }, L"OrangeRed", false, false };
	const CColor CColors::Orchid{ Color{ 0xDA, 0x70, 0xD6, 0xFF }, L"Orchid", false, false };
	const CColor CColors::PaleGoldenRod{ Color{ 0xEE, 0xE8, 0xAA, 0xFF }, L"PaleGoldenRod", false, false };
	const CColor CColors::PaleGreen{ Color{ 0x98, 0xFB, 0x98, 0xFF }, L"PaleGreen", false, false };
	const CColor CColors::PaleTurquoise{ Color{ 0xAF, 0xEE, 0xEE, 0xFF }, L"PaleTurquoise", false, false };
	const CColor CColors::PaleVioletRed{ Color{ 0xDB, 0x70, 0x93, 0xFF }, L"PaleVioletRed", false, false };
	const CColor CColors::PapayaWhip{ Color{ 0xFF, 0xEF, 0xD5, 0xFF }, L"PapayaWhip", false, false };
	const CColor CColors::PeachPuff{ Color{ 0xFF, 0xDA, 0xB9, 0xFF }, L"PeachPuff", false, false };
	const CColor CColors::Peru{ Color{ 0xCD, 0x85, 0x3F, 0xFF }, L"Peru", false, false };
	const CColor CColors::Pink{ Color{ 0xFF, 0xC0, 0xCB, 0xFF }, L"Pink", false, false };
	const CColor CColors::Plum{ Color{ 0xDD, 0xA0, 0xDD, 0xFF }, L"Plum", false, false };
	const CColor CColors::PowderBlue{ Color{ 0xB0, 0xE0, 0xE6, 0xFF }, L"PowderBlue", false, false };
	const CColor CColors::RebeccaPurple{ Color{ 0x66, 0x33, 0x99, 0xFF }, L"RebeccaPurple", false, false };
	const CColor CColors::RosyBrown{ Color{ 0xBC, 0x8F, 0x8F, 0xFF }, L"RosyBrown", false, false };
	const CColor CColors::RoyalBlue{ Color{ 0x41, 0x69, 0xE1, 0xFF }, L"RoyalBlue", false, false };
	const CColor CColors::SaddleBrown{ Color{ 0x8B, 0x45, 0x13, 0xFF }, L"SaddleBrown", false, false };
	const CColor CColors::Salmon{ Color{ 0xFA, 0x80, 0x72, 0xFF }, L"Salmon", false, false };
	const CColor CColors::SandyBrown{ Color{ 0xF4, 0xA4, 0x60, 0xFF }, L"SandyBrown", false, false };
	const CColor CColors::SeaGreen{ Color{ 0x2E, 0x8B, 0x57, 0xFF }, L"SeaGreen", false, false };
	const CColor CColors::SeaShell{ Color{ 0xFF, 0xF5, 0xEE, 0xFF }, L"SeaShell", false, false };
	const CColor CColors::Sienna{ Color{ 0xA0, 0x52, 0x2D, 0xFF }, L"Sienna", false, false };
	const CColor CColors::SkyBlue{ Color{ 0x87, 0xCE, 0xEB, 0xFF }, L"SkyBlue", false, false };
	const CColor CColors::SlateBlue{ Color{ 0x6A, 0x5A, 0xCD, 0xFF }, L"SlateBlue", false, false };
	const CColor CColors::SlateGray{ Color{ 0x70, 0x80, 0x90, 0xFF }, L"SlateGray", false, false };
	const CColor CColors::Snow{ Color{ 0xFF, 0xFA, 0xFA, 0xFF }, L"Snow", false, false };
	const CColor CColors::SpringGreen{ Color{ 0x00, 0xFF, 0x7F, 0xFF }, L"SpringGreen", false, false };
	const CColor CColors::SteelBlue{ Color{ 0x46, 0x82, 0xB4, 0xFF }, L"SteelBlue", false, false };
	const CColor CColors::Tan{ Color{ 0xD2, 0xB4, 0x8C, 0xFF }, L"Tan", false, false };
	const CColor CColors::Thistle{ Color{ 0xD8, 0xBF, 0xD8, 0xFF }, L"Thistle", false, false };
	const CColor CColors::Tomato{ Color{ 0xFF, 0x63, 0x47, 0xFF }, L"Tomato", false, false };
	const CColor CColors::Turquoise{ Color{ 0x40, 0xE0, 0xD0, 0xFF }, L"Turquoise", false, false };
	const CColor CColors::Violet{ Color{ 0xEE, 0x82, 0xEE, 0xFF }, L"Violet", false, false };
	const CColor CColors::Wheat{ Color{ 0xF5, 0xDE, 0xB3, 0xFF }, L"Wheat", false, false };
	const CColor CColors::WhiteSmoke{ Color{ 0xF5, 0xF5, 0xF5, 0xFF }, L"WhiteSmoke", false, false };
	const CColor CColors::YellowGreen{ Color{ 0x9A, 0xCD, 0x32, 0xFF }, L"YellowGreen", false, false };
}
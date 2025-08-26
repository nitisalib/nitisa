// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace standard
	{
		const int IconWidth{ 26 }, IconHeight{ 26 };
		const Color IconData[26 * 26]{
			{ 47, 46, 46, 60 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 63 },{ 47, 46, 46, 60 },
			{ 38, 33, 34, 216 },{ 38, 33, 34, 228 },{ 38, 33, 34, 230 },{ 38, 33, 34, 230 },{ 38, 33, 34, 230 },{ 38, 33, 34, 230 },{ 38, 33, 34, 230 },{ 38, 33, 34, 229 },{ 38, 33, 34, 228 },{ 38, 33, 34, 229 },{ 38, 33, 34, 230 },{ 38, 33, 34, 230 },{ 38, 33, 34, 230 },{ 38, 33, 34, 230 },{ 38, 33, 34, 230 },{ 38, 33, 34, 230 },{ 38, 33, 34, 230 },{ 38, 33, 34, 230 },{ 38, 33, 34, 230 },{ 38, 33, 34, 230 },{ 38, 33, 34, 230 },{ 38, 33, 34, 230 },{ 38, 33, 34, 230 },{ 38, 33, 34, 230 },{ 38, 33, 34, 228 },{ 38, 33, 34, 216 },
			{ 35, 29, 30, 255 },{ 35, 29, 30, 255 },{ 34, 29, 30, 255 },{ 34, 29, 30, 255 },{ 34, 29, 30, 255 },{ 34, 29, 30, 255 },{ 34, 29, 30, 255 },{ 34, 29, 30, 255 },{ 35, 29, 30, 255 },{ 35, 29, 30, 255 },{ 35, 29, 30, 255 },{ 33, 28, 29, 255 },{ 32, 26, 27, 255 },{ 32, 26, 27, 255 },{ 33, 28, 29, 255 },{ 33, 27, 29, 255 },{ 32, 26, 28, 255 },{ 32, 26, 28, 255 },{ 34, 28, 29, 255 },{ 33, 27, 28, 255 },{ 32, 26, 28, 255 },{ 32, 26, 28, 255 },{ 34, 28, 30, 255 },{ 35, 29, 30, 255 },{ 35, 29, 30, 255 },{ 35, 29, 30, 255 },
			{ 36, 31, 32, 245 },{ 36, 31, 32, 255 },{ 36, 31, 32, 98 },{ 35, 30, 31, 64 },{ 35, 30, 31, 65 },{ 35, 30, 31, 65 },{ 35, 30, 31, 64 },{ 36, 31, 32, 146 },{ 36, 31, 32, 255 },{ 36, 31, 32, 206 },{ 34, 29, 30, 65 },{ 38, 33, 34, 62 },{ 40, 37, 38, 40 },{ 40, 37, 38, 40 },{ 37, 33, 34, 65 },{ 38, 34, 35, 59 },{ 40, 37, 38, 40 },{ 40, 37, 38, 43 },{ 37, 33, 33, 65 },{ 39, 35, 36, 53 },{ 40, 37, 37, 40 },{ 40, 37, 37, 48 },{ 36, 31, 32, 64 },{ 35, 30, 31, 98 },{ 36, 31, 32, 255 },{ 36, 31, 32, 245 },
			{ 36, 31, 32, 247 },{ 36, 31, 32, 255 },{ 36, 31, 32, 20 },{ 36, 31, 32, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 91 },{ 36, 31, 32, 255 },{ 35, 30, 31, 181 },{ 36, 32, 32, 0 },{ 48, 47, 47, 0 },{ 51, 51, 51, 7 },{ 51, 51, 51, 7 },{ 47, 46, 46, 0 },{ 48, 47, 47, 0 },{ 51, 50, 50, 8 },{ 50, 50, 50, 2 },{ 47, 45, 45, 0 },{ 49, 48, 48, 0 },{ 50, 50, 50, 8 },{ 51, 51, 51, 0 },{ 43, 40, 41, 0 },{ 35, 29, 30, 20 },{ 36, 31, 32, 255 },{ 36, 31, 32, 247 },
			{ 36, 31, 32, 246 },{ 36, 31, 32, 255 },{ 36, 31, 32, 45 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 109 },{ 36, 31, 32, 255 },{ 36, 31, 32, 189 },{ 37, 32, 33, 0 },{ 37, 32, 33, 27 },{ 36, 30, 31, 255 },{ 36, 30, 31, 255 },{ 37, 32, 33, 0 },{ 37, 32, 33, 58 },{ 36, 31, 32, 255 },{ 36, 31, 32, 224 },{ 37, 32, 33, 0 },{ 36, 31, 32, 123 },{ 36, 31, 32, 255 },{ 36, 31, 32, 169 },{ 37, 32, 33, 0 },{ 36, 31, 32, 45 },{ 36, 31, 32, 255 },{ 36, 31, 32, 246 },
			{ 36, 31, 32, 246 },{ 36, 31, 32, 255 },{ 36, 31, 32, 45 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 109 },{ 36, 31, 32, 255 },{ 36, 31, 32, 189 },{ 36, 31, 32, 0 },{ 36, 30, 31, 28 },{ 36, 30, 31, 255 },{ 36, 30, 31, 255 },{ 36, 30, 31, 0 },{ 36, 30, 31, 59 },{ 36, 30, 31, 255 },{ 36, 30, 31, 226 },{ 36, 30, 31, 0 },{ 36, 30, 31, 124 },{ 36, 30, 31, 255 },{ 36, 30, 31, 170 },{ 36, 31, 32, 0 },{ 36, 31, 32, 45 },{ 36, 31, 32, 255 },{ 36, 31, 32, 246 },
			{ 36, 31, 32, 246 },{ 36, 31, 32, 255 },{ 36, 31, 32, 45 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 109 },{ 36, 31, 32, 255 },{ 36, 31, 32, 189 },{ 36, 31, 32, 0 },{ 36, 31, 32, 27 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 0 },{ 36, 31, 32, 57 },{ 36, 31, 32, 255 },{ 36, 31, 32, 220 },{ 36, 31, 32, 0 },{ 36, 31, 32, 121 },{ 36, 31, 32, 255 },{ 36, 31, 32, 166 },{ 36, 31, 32, 0 },{ 36, 31, 32, 45 },{ 36, 31, 32, 255 },{ 36, 31, 32, 246 },
			{ 36, 31, 32, 246 },{ 36, 31, 32, 255 },{ 36, 31, 32, 45 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 109 },{ 36, 31, 32, 255 },{ 36, 31, 32, 189 },{ 36, 31, 32, 0 },{ 36, 31, 32, 27 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 0 },{ 36, 31, 32, 57 },{ 36, 31, 32, 255 },{ 36, 31, 32, 220 },{ 36, 31, 32, 0 },{ 36, 31, 32, 121 },{ 36, 31, 32, 255 },{ 36, 31, 32, 166 },{ 36, 31, 32, 0 },{ 36, 31, 32, 45 },{ 36, 31, 32, 255 },{ 36, 31, 32, 246 },
			{ 36, 31, 32, 246 },{ 36, 31, 32, 255 },{ 36, 31, 32, 45 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 109 },{ 36, 31, 32, 255 },{ 36, 31, 32, 189 },{ 36, 31, 32, 0 },{ 36, 31, 32, 27 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 0 },{ 36, 31, 32, 57 },{ 36, 31, 32, 255 },{ 36, 31, 32, 220 },{ 36, 31, 32, 0 },{ 36, 31, 32, 121 },{ 36, 31, 32, 255 },{ 36, 31, 32, 166 },{ 36, 31, 32, 0 },{ 36, 31, 32, 45 },{ 36, 31, 32, 255 },{ 36, 31, 32, 246 },
			{ 36, 31, 32, 246 },{ 36, 31, 32, 255 },{ 36, 31, 32, 45 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 109 },{ 36, 31, 32, 255 },{ 36, 31, 32, 189 },{ 36, 31, 32, 0 },{ 36, 31, 32, 27 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 0 },{ 36, 31, 32, 57 },{ 36, 31, 32, 255 },{ 36, 31, 32, 220 },{ 36, 31, 32, 0 },{ 36, 31, 32, 121 },{ 36, 31, 32, 255 },{ 36, 31, 32, 166 },{ 36, 31, 32, 0 },{ 36, 31, 32, 45 },{ 36, 31, 32, 255 },{ 36, 31, 32, 246 },
			{ 36, 31, 32, 246 },{ 36, 31, 32, 255 },{ 36, 31, 32, 45 },{ 36, 31, 32, 0 },{ 34, 28, 29, 0 },{ 34, 29, 30, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 109 },{ 36, 31, 32, 255 },{ 36, 31, 32, 189 },{ 36, 31, 32, 0 },{ 36, 31, 32, 27 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 0 },{ 36, 31, 32, 57 },{ 36, 31, 32, 255 },{ 36, 31, 32, 220 },{ 36, 31, 32, 0 },{ 36, 31, 32, 121 },{ 36, 31, 32, 255 },{ 36, 31, 32, 166 },{ 36, 31, 32, 0 },{ 36, 31, 32, 45 },{ 36, 31, 32, 255 },{ 36, 31, 32, 246 },
			{ 36, 31, 32, 246 },{ 36, 31, 32, 255 },{ 36, 31, 32, 45 },{ 34, 28, 29, 0 },{ 43, 40, 41, 0 },{ 41, 37, 38, 0 },{ 33, 28, 29, 0 },{ 36, 31, 32, 109 },{ 36, 31, 32, 255 },{ 36, 31, 32, 189 },{ 35, 30, 31, 0 },{ 34, 29, 30, 31 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 34, 29, 30, 0 },{ 35, 29, 30, 66 },{ 36, 31, 31, 255 },{ 35, 31, 31, 255 },{ 34, 29, 30, 0 },{ 35, 30, 31, 140 },{ 35, 30, 31, 255 },{ 35, 30, 31, 192 },{ 34, 29, 30, 0 },{ 36, 31, 32, 45 },{ 36, 31, 32, 255 },{ 36, 31, 32, 246 },
			{ 36, 31, 32, 246 },{ 36, 31, 32, 255 },{ 34, 28, 29, 41 },{ 42, 40, 40, 0 },{ 55, 56, 56, 0 },{ 53, 54, 54, 0 },{ 39, 35, 36, 0 },{ 34, 28, 29, 106 },{ 36, 32, 33, 255 },{ 34, 29, 30, 188 },{ 38, 33, 34, 0 },{ 39, 36, 36, 9 },{ 35, 30, 30, 132 },{ 35, 30, 30, 132 },{ 39, 36, 36, 0 },{ 38, 35, 35, 25 },{ 35, 31, 31, 132 },{ 35, 31, 31, 111 },{ 39, 36, 36, 0 },{ 37, 33, 33, 59 },{ 35, 31, 31, 132 },{ 36, 32, 32, 82 },{ 40, 36, 37, 0 },{ 36, 30, 31, 41 },{ 36, 31, 32, 255 },{ 36, 31, 32, 246 },
			{ 36, 31, 32, 246 },{ 35, 29, 31, 255 },{ 44, 41, 42, 38 },{ 55, 55, 55, 0 },{ 52, 52, 52, 0 },{ 53, 54, 54, 0 },{ 53, 53, 53, 0 },{ 40, 36, 37, 104 },{ 34, 28, 29, 255 },{ 36, 32, 33, 187 },{ 49, 49, 49, 0 },{ 53, 54, 53, 0 },{ 49, 49, 49, 0 },{ 49, 49, 49, 0 },{ 52, 52, 52, 0 },{ 51, 52, 51, 0 },{ 49, 49, 49, 0 },{ 50, 49, 49, 0 },{ 52, 52, 52, 0 },{ 51, 51, 51, 0 },{ 50, 49, 49, 0 },{ 50, 50, 50, 0 },{ 54, 54, 54, 0 },{ 44, 41, 42, 38 },{ 35, 29, 31, 255 },{ 36, 31, 32, 246 },
			{ 36, 31, 32, 242 },{ 36, 31, 32, 255 },{ 40, 36, 37, 220 },{ 39, 35, 36, 210 },{ 38, 34, 35, 212 },{ 38, 34, 35, 212 },{ 40, 36, 37, 210 },{ 39, 35, 36, 230 },{ 35, 29, 30, 255 },{ 38, 33, 34, 244 },{ 40, 37, 38, 211 },{ 39, 35, 36, 212 },{ 40, 37, 37, 213 },{ 40, 37, 37, 213 },{ 40, 36, 36, 213 },{ 40, 36, 37, 213 },{ 40, 36, 37, 213 },{ 40, 36, 37, 213 },{ 39, 35, 36, 213 },{ 40, 36, 37, 213 },{ 40, 36, 37, 213 },{ 40, 36, 37, 213 },{ 40, 36, 37, 211 },{ 40, 36, 37, 220 },{ 36, 31, 32, 255 },{ 36, 31, 32, 242 },
			{ 36, 31, 32, 241 },{ 36, 31, 32, 255 },{ 35, 29, 30, 255 },{ 34, 29, 30, 255 },{ 34, 29, 30, 255 },{ 34, 29, 30, 255 },{ 34, 29, 30, 255 },{ 35, 30, 31, 255 },{ 36, 32, 33, 255 },{ 36, 30, 31, 255 },{ 34, 28, 29, 255 },{ 34, 29, 30, 255 },{ 34, 29, 30, 255 },{ 34, 29, 30, 255 },{ 34, 29, 30, 255 },{ 34, 29, 30, 255 },{ 34, 29, 30, 255 },{ 34, 29, 30, 255 },{ 34, 29, 30, 255 },{ 34, 29, 30, 255 },{ 34, 29, 30, 255 },{ 34, 29, 30, 255 },{ 34, 28, 30, 255 },{ 35, 29, 30, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },
			{ 36, 31, 32, 241 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 212 },{ 35, 30, 31, 87 },{ 35, 30, 31, 87 },{ 35, 30, 31, 87 },{ 35, 30, 31, 87 },{ 35, 30, 31, 87 },{ 35, 30, 31, 87 },{ 35, 30, 31, 87 },{ 35, 30, 31, 87 },{ 35, 30, 31, 87 },{ 35, 30, 31, 87 },{ 35, 30, 31, 87 },{ 35, 30, 31, 87 },{ 35, 30, 31, 87 },{ 35, 30, 31, 87 },{ 35, 30, 31, 89 },{ 35, 30, 31, 82 },
			{ 36, 31, 32, 241 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 32, 32, 149 },{ 36, 32, 33, 145 },{ 36, 30, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 180 },{ 36, 31, 32, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },
			{ 36, 31, 32, 241 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 31, 130 },{ 35, 30, 31, 0 },{ 35, 30, 31, 99 },{ 35, 31, 32, 253 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 189 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },
			{ 36, 31, 32, 241 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 37, 32, 32, 134 },{ 36, 32, 31, 0 },{ 34, 30, 30, 82 },{ 35, 31, 32, 252 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 189 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },
			{ 36, 31, 32, 241 },{ 36, 31, 32, 255 },{ 35, 30, 31, 255 },{ 39, 35, 35, 141 },{ 39, 35, 36, 125 },{ 35, 30, 30, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 189 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },
			{ 36, 31, 32, 241 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 31, 250 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 255 },{ 36, 31, 32, 189 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 36, 31, 32, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },
			{ 35, 30, 31, 255 },{ 35, 30, 31, 255 },{ 35, 30, 31, 255 },{ 35, 30, 31, 255 },{ 35, 30, 31, 255 },{ 35, 30, 31, 255 },{ 35, 30, 31, 255 },{ 35, 30, 31, 255 },{ 35, 30, 31, 255 },{ 35, 30, 31, 205 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 36, 30, 31, 0 },{ 35, 29, 30, 0 },{ 34, 29, 30, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },
			{ 37, 32, 33, 216 },{ 37, 32, 33, 229 },{ 37, 32, 33, 229 },{ 37, 32, 33, 229 },{ 37, 32, 33, 229 },{ 37, 32, 33, 229 },{ 37, 32, 33, 229 },{ 37, 32, 33, 229 },{ 37, 32, 33, 229 },{ 37, 32, 33, 169 },{ 37, 32, 33, 0 },{ 37, 32, 33, 0 },{ 37, 32, 33, 0 },{ 37, 32, 33, 0 },{ 37, 32, 33, 0 },{ 37, 32, 33, 0 },{ 37, 32, 33, 0 },{ 36, 31, 32, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },
			{ 41, 39, 40, 60 },{ 41, 39, 40, 64 },{ 41, 39, 40, 64 },{ 41, 39, 40, 64 },{ 41, 39, 40, 64 },{ 41, 39, 40, 64 },{ 41, 39, 40, 64 },{ 41, 39, 40, 64 },{ 41, 39, 40, 64 },{ 41, 39, 40, 47 },{ 41, 39, 40, 0 },{ 41, 39, 40, 0 },{ 41, 39, 40, 0 },{ 41, 39, 40, 0 },{ 41, 39, 40, 0 },{ 41, 39, 40, 0 },{ 41, 40, 40, 0 },{ 40, 38, 38, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },{ 35, 30, 31, 0 },
		};

		CPackageSelect::CPackageSelect(IPackage *package) :
			CPackageControl(package, L"standard"),
			m_cIcon{ IconWidth, IconHeight, IconData },
			m_bDialogBoxResized{ false }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Controls/Select/Select.h");
		}

		IControl *CPackageSelect::Create(IPropertyList **properties, IEventList **events)
		{
			IControl *result{ new CSelect() };
			if (properties)
				*properties = new CSelectPropertyList(getPackage(), result, this);
			if (events)
				*events = new CSelectEventList(getPackage(), result, this);
			if (properties || events)
				getPackage()->QueryService()->NotifyOnCreateControl(result, this, *properties, *events);
			return result;
		}

		IPropertyList *CPackageSelect::CreatePropertyList(IControl *control)
		{
			if (isInstance(control))
				return new CSelectPropertyList(getPackage(), control, this);
			return nullptr;
		}

		IEventList *CPackageSelect::CreateEventList(IControl *control)
		{
			if (isInstance(control))
				return new CSelectEventList(getPackage(), control, this);
			return nullptr;
		}

		bool CPackageSelect::CreateListItem(IComponent *component, IListItem *parent, IListItem **item, IPackageControlListener *listener)
		{
			if (component && (item || listener))
			{
				CSelect *control{ cast<CSelect*>(component) };
				if (control)
				{
					if (Application->DialogBoxes)
					{
						CDialogBoxSelectListItem *dlg{ getDialogBox(component) };
						m_sCreateListItemParams.Component = component;
						m_sCreateListItemParams.Control = control;
						m_sCreateListItemParams.Item = item;
						m_sCreateListItemParams.Listener = listener;
						dlg->setDialogBoxListener(this);
						dlg->ShowModal();
						if (!m_bDialogBoxResized)
						{
							dlg->setBackgroundColor(Color{ 240, 240, 240, 255 });
							dlg->AutoResize(true);
							m_bDialogBoxResized = true;
						}
						return true;
					}
					IPackageForm *pform{ getPackage()->getForm(CFormSelectListItem::ClassName) };
					IFormSelectListItem *form{ cast<IFormSelectListItem*>(pform->getInstance()) };
					if (!form && control->getForm() && control->getForm()->QueryService()->getWindow() && control->getForm()->getRenderer())
						form = cast<IFormSelectListItem*>(pform->Create(control->getForm()->QueryService()->getWindow()->CreateInstance(), control->getForm()->getRenderer()->CreateInstance()));
					if (form && cast<IForm*>(form)->ShowModal() == ModalResult::Ok)
					{
						if (control->Add(form->getItemCaption(), form->getItemTypeIndex() == 1))
						{
							if (listener)
								listener->OnCreateListItem(this, parent, control->getItem(control->getItemCount() - 1));
							return true;
						}
					}
				}
			}
			return false;
		}

		CDialogBoxSelectListItem *CPackageSelect::getDialogBox(IComponent *component)
		{
			CDialogBoxSelectListItem *dlg;
			for (int i = component->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((dlg = cast<CDialogBoxSelectListItem*>(component->getForm()->getControl(i))))
					return dlg;
			dlg = new CDialogBoxSelectListItem(component->getForm());
			return dlg;
		}

		String CPackageSelect::getCategory()
		{
			return L"Additional";
		}

		String CPackageSelect::getClassName()
		{
			return L"Select";
		}

		String CPackageSelect::getTitle()
		{
			return L"Select";
		}

		String CPackageSelect::getDescription()
		{
			return L"Select";
		}

		String CPackageSelect::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageSelect::getIcon()
		{
			return &m_cIcon;
		}

		bool CPackageSelect::isVisible()
		{
			return true;
		}

		bool CPackageSelect::isDisplayIcon()
		{
			return false;
		}

		bool CPackageSelect::isInstance(IControl *control)
		{
			return cast<CSelect*>(control) != nullptr;
		}

		bool CPackageSelect::isTransformable()
		{
			return true;
		}

		void CPackageSelect::Save(Variant &dest, IPropertyList *properties, IEventList *events)
		{
			CPackageControl::Save(dest, properties, events);
			CSelect *control{ cast<CSelect*>(properties->getParent()) };
			if (Application->Editor && control)
				for (int i = 0; i < control->getItemCount(); i++)
				{
					IListItem *item{ control->getItem(i) };
					IPackageListItem *package_item{ Application->Editor->getListItem(item) };
					Variant data;
					if (package_item)
					{
						data[L"Package"] = package_item->getPackage()->getName();
						data[L"ClassName"] = package_item->getClassName();
						IPropertyList *properties;
						IListItem *test{ package_item->Create(&properties) };
						properties->setParent(item, this);
						test->Release();
						properties->Save(data);
						properties->Release();
					}
					dest[L"Items"].push_back(data);
				}
		}

		void CPackageSelect::Load(const Variant &src, IPropertyList *properties, IEventList *events)
		{
			CSelect *control{ cast<CSelect*>(properties->getParent()) };
			if (Application->Editor && control && src.isSet(L"Items") && src.get(L"Items").getType() == Variant::VariantType::Array)
			{
				control->DeleteItems();
				for (auto pos : src.get(L"Items"))
					if (pos.second.isSet(L"Package") && pos.second.isSet(L"ClassName"))
					{
						IPackageListItem *package_item{ Application->Editor->getListItem((String)pos.second.get(L"Package"), (String)pos.second.get(L"ClassName")) };
						if (package_item)
						{
							IPropertyList *properties;
							IListItem *item{ package_item->Create(&properties) };
							properties->Load(pos.second);
							properties->Release();
							if (!control->AddItem(item))
								item->Release();
						}
					}
			}
			CPackageControl::Load(src, properties, events);
		}

		void CPackageSelect::Export(std::wofstream &f, const String &shift, const String &owner, IPropertyList *properties, IEventList *events, const String &form, const String &dialog_box)
		{
			CSelect *control{ cast<CSelect*>(properties->getParent()) };
			if (Application->Editor && control)
				for (int i = 0; i < control->getItemCount(); i++)
				{
					IListItem *item{ control->getItem(i) };
					IPackageListItem *package_item{ Application->Editor->getListItem(item) };
					if (package_item)
					{
						IPropertyList *properties;
						IListItem *tmp{ package_item->Create(&properties) };
						properties->setParent(item, this);
						tmp->Release();
						String ns{ package_item->getNamespace() };
						if (!ns.empty())
							ns += L"::";
						f << shift << L"{" << std::endl;
						f << shift << L"\t" << ns << L"C" << item->ClassName << L" *item{ new " << ns << L"C" << item->ClassName << L"() };" << std::endl;
						properties->Export(f, shift + L"\t", L"item");
						f << shift << L"\t" << owner << L"->AddItem(item);" << std::endl;
						f << shift << L"}" << std::endl;
						properties->Release();
					}
				}
			CPackageControl::Export(f, shift, owner, properties, events, form, dialog_box);
		}

		void CPackageSelect::OnClose(IDialogBox *sender)
		{
			if (sender->getModalResult() == ModalResult::Ok)
			{
				CDialogBoxSelectListItem *dlg{ cast<CDialogBoxSelectListItem*>(sender) };
				IListItem *i;
				if (dlg->getItemTypeIndex() == 1)
					i = new CListItemSelectCategory(dlg->getItemCaption());
				else
					i = new CListItemSelectLabel(dlg->getItemCaption());
				if (m_sCreateListItemParams.Item)
					*m_sCreateListItemParams.Item = i;
				if (m_sCreateListItemParams.Control)
					m_sCreateListItemParams.Control->AddItem(i);
				if (m_sCreateListItemParams.Listener)
					m_sCreateListItemParams.Listener->OnCreateListItem(this, nullptr, i);
			}
		}

		void CPackageSelect::OnRestore(IDialogBox *sender)
		{

		}

		void CPackageSelect::OnMinimize(IDialogBox *sender)
		{

		}

		void CPackageSelect::OnMaximize(IDialogBox *sender)
		{

		}
	}
}
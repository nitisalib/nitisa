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
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 239, 235, 222,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 239, 235, 222,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 198, 211, 239, 255 }, { 198, 211, 239, 255 }, { 198, 211, 239, 255 }, { 198, 211, 239, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 198, 211, 239, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 198, 211, 239, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 198, 211, 239, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 198, 211, 239, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 198, 211, 239, 255 }, { 198, 211, 239, 255 }, { 198, 211, 239, 255 }, { 198, 211, 239, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 198, 211, 239, 255 }, { 198, 211, 239, 255 }, { 198, 211, 239, 255 }, { 198, 211, 239, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 198, 211, 239, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 198, 211, 239, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 198, 211, 239, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 198, 211, 239, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 239, 235, 222, 255 }, { 102, 102, 102, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 198, 211, 239, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 198, 211, 239, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 239, 235, 222, 255 }, { 102, 102, 102, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 198, 211, 239, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 198, 211, 239, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 102, 102, 102, 255 }, { 102, 102, 102, 255 }, { 255, 255, 255, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 239, 235, 222, 255 }, { 102, 102, 102, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 198, 211, 239, 255 }, { 198, 211, 239, 255 }, { 198, 211, 239, 255 }, { 198, 211, 239, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 239, 235, 222, 255 }, { 102, 102, 102, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 198, 211, 239, 255 }, { 198, 211, 239, 255 }, { 198, 211, 239, 255 }, { 198, 211, 239, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 198, 211, 239, 255 }, { 198, 211, 239, 255 }, { 198, 211, 239, 255 }, { 198, 211, 239, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 239, 235, 222, 255 }, { 102, 102, 102, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 239, 235, 222,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 239, 235, 222, 255 }, { 102, 102, 102, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 239, 235, 222,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 239, 235, 222, 255 }, { 102, 102, 102, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 239, 235, 222,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 239, 235, 222, 255 }, { 102, 102, 102, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 239, 235, 222,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 239, 235, 222,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 239, 235, 222, 255 }, { 153, 153, 153, 255 }, { 239, 235, 222,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 153, 153, 153, 255 }, { 239, 235, 222,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
		};

		CPackageMainMenu::CPackageMainMenu(IPackage *package) :
			CPackageControl(package, L"standard"),
			m_cIcon{ IconWidth, IconHeight, IconData },
			m_bDialogBoxResized{ false }
		{
			// Supported platforms

			// Header files
			AddHeaderFile(L"Standard/Controls/MainMenu/MainMenu.h");
			AddHeaderFile(L"Standard/ListItems/MenuCheckBox/ListItemMenuCheckBox.h");
			AddHeaderFile(L"Standard/ListItems/MenuLabel/ListItemMenuLabel.h");
			AddHeaderFile(L"Standard/ListItems/MenuRadioButton/ListItemMenuRadioButton.h");
			AddHeaderFile(L"Standard/ListItems/MenuSeparator/ListItemMenuSeparator.h");
		}

		IControl *CPackageMainMenu::Create(IPropertyList **properties, IEventList **events)
		{
			IControl *result{ new CMainMenu() };
			if (properties)
				*properties = new CMainMenuPropertyList(getPackage(), result, this);
			if (events)
				*events = new CMainMenuEventList(getPackage(), result, this);
			if (properties || events)
				getPackage()->QueryService()->NotifyOnCreateControl(result, this, *properties, *events);
			return result;
		}

		IPropertyList *CPackageMainMenu::CreatePropertyList(IControl *control)
		{
			if (isInstance(control))
				return new CMainMenuPropertyList(getPackage(), control, this);
			return nullptr;
		}

		IEventList *CPackageMainMenu::CreateEventList(IControl *control)
		{
			if (isInstance(control))
				return new CMainMenuEventList(getPackage(), control, this);
			return nullptr;
		}

		String CPackageMainMenu::getNamespace()
		{
			return L"standard";
		}

		String CPackageMainMenu::getCategory()
		{
			return L"Standard";
		}

		String CPackageMainMenu::getClassName()
		{
			return L"MainMenu";
		}

		String CPackageMainMenu::getTitle()
		{
			return L"MainMenu";
		}

		String CPackageMainMenu::getDescription()
		{
			return L"MainMenu";
		}

		String CPackageMainMenu::getReferenceUrl()
		{
			return L"";
		}

		const Image *CPackageMainMenu::getIcon()
		{
			return &m_cIcon;
		}

		bool CPackageMainMenu::isVisible()
		{
			return true;
		}

		bool CPackageMainMenu::isDisplayIcon()
		{
			return false;
		}

		bool CPackageMainMenu::isInstance(IControl *control)
		{
			return cast<CMainMenu*>(control) != nullptr;
		}

		CDialogBoxMenuListItem *CPackageMainMenu::getDialogBox(IComponent *component)
		{
			CDialogBoxMenuListItem *dlg;
			for (int i = component->getForm()->getControlCount() - 1; i >= 0; i--)
				if ((dlg = cast<CDialogBoxMenuListItem*>(component->getForm()->getControl(i))))
					return dlg;
			dlg = new CDialogBoxMenuListItem(component->getForm());
			return dlg;
		}

		bool CPackageMainMenu::CreateListItem(IComponent *component, IListItem *parent, IListItem **item, IPackageControlListener *listener)
		{
			if (component && (item || listener))
			{
				IMainMenu *control{ cast<IMainMenu*>(component) };
				if (control)
				{
					if (Application->DialogBoxes)
					{
						CDialogBoxMenuListItem *dlg{ getDialogBox(component) };
						m_sCreateListItemParams.Component = component;
						m_sCreateListItemParams.Control = control;
						m_sCreateListItemParams.Parent = parent;
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
					IPackageForm *pform{ getPackage()->getForm(CFormMenuListItem::ClassName) };
					IFormMenuListItem *form{ cast<IFormMenuListItem*>(pform->getInstance()) };
					if (!form && control->getForm() && control->getForm()->QueryService()->getWindow() && control->getForm()->getRenderer())
						form = cast<IFormMenuListItem*>(pform->Create(control->getForm()->QueryService()->getWindow()->CreateInstance(), control->getForm()->getRenderer()->CreateInstance()));
					if (form && cast<IForm*>(form)->ShowModal() == ModalResult::Ok)
					{
						if (!parent)
							parent = control->getRootItem();
						IListItem *i{ nullptr };
						switch (form->getItemTypeIndex())
						{
						case 0:
							i = new CListItemMenuLabel(form->getItemCaption());
							break;
						case 1:
							i = new CListItemMenuCheckBox(form->getItemCaption());
							break;
						case 2:
							i = new CListItemMenuRadioButton(form->getItemCaption());
							break;
						case 3:
							i = new CListItemMenuSeparator();
							break;
						}
						if (item)
							*item = i;
						if (i)
						{
							parent->AddItem(i);
							if (listener)
								listener->OnCreateListItem(this, parent, i);
							return true;
						}
					}
				}
			}
			return false;
		}

		void CPackageMainMenu::SaveListItem(Variant &dest, IListItem *item)
		{
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
			for (int i = 0; i < item->getItemCount(); i++)
				SaveListItem(data[L"Items"], item->getItem(i));
			dest.push_back(data);
		}

		void CPackageMainMenu::Save(Variant &dest, IPropertyList *properties, IEventList *events)
		{
			CPackageControl::Save(dest, properties, events);
			CMainMenu *menu{ cast<CMainMenu*>(properties->getParent()) };
			if (Application->Editor && menu && menu->getRootItem()->getItemCount() > 0)
				for (int i = 0; i < menu->getRootItem()->getItemCount(); i++)
					SaveListItem(dest[L"Items"], menu->getRootItem()->getItem(i));
		}

		void CPackageMainMenu::LoadListItem(const Variant &src, IListItem *parent)
		{
			if (src.isSet(L"Package") && src.isSet(L"ClassName"))
			{
				IPackageListItem *package_item{ Application->Editor->getListItem((String)src.get(L"Package"), (String)src.get(L"ClassName")) };
				if (package_item)
				{
					IPropertyList *properties;
					IListItem *item{ package_item->Create(&properties) };
					properties->Load(src);
					properties->Release();
					if (parent->AddItem(item))
					{
						if (src.isSet(L"Items") && src.get(L"Items").getType() == Variant::VariantType::Array)
							for (auto pos : src.get(L"Items"))
								LoadListItem(pos.second, item);
					}
					else
						item->Release();
				}
			}
		}

		void CPackageMainMenu::Load(const Variant &src, IPropertyList *properties, IEventList *events)
		{
			CMainMenu *menu{ cast<CMainMenu*>(properties->getParent()) };
			if (Application->Editor && menu && src.isSet(L"Items") && src.get(L"Items").getType() == Variant::VariantType::Array)
				for (auto pos : src.get(L"Items"))
					LoadListItem(pos.second, menu->getRootItem());
			CPackageControl::Load(src, properties, events);
		}

		void CPackageMainMenu::ExportListItem(std::wofstream &f, const String &shift, const String &parent, IListItem *item, const int level)
		{
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
				f << shift << L"\t" << ns << L"C" << item->ClassName << L" *item" << level << L"{ new " << ns << L"C" << item->ClassName << L"() };" << std::endl;
				properties->Export(f, shift + L"\t", L"item" + ToString(level));
				f << shift << L"\t" << parent << L"->AddItem(item" << level << L");" << std::endl;
				for (int i = 0; i < item->getItemCount(); i++)
					ExportListItem(f, shift + L"\t", L"item" + ToString(level), item->getItem(i), level + 1);
				f << shift << L"}" << std::endl;
				properties->Release();
			}
		}

		void CPackageMainMenu::Export(std::wofstream &f, const String &shift, const String &owner, IPropertyList *properties, IEventList *events, const String &form, const String &dialog_box)
		{
			CMainMenu *menu{ cast<CMainMenu*>(properties->getParent()) };
			if (Application->Editor && menu && menu->getRootItem()->getItemCount() > 0)
				for (int i = 0; i < menu->getRootItem()->getItemCount(); i++)
					ExportListItem(f, shift, owner + L"->getRootItem()", menu->getRootItem()->getItem(i), 0);
			CPackageControl::Export(f, shift, owner, properties, events, form, dialog_box);
		}

		bool CPackageMainMenu::isTransformable()
		{
			return true;
		}

		void CPackageMainMenu::OnClose(IDialogBox *sender)
		{
			if (sender->getModalResult() == ModalResult::Ok)
			{
				if (!m_sCreateListItemParams.Parent)
					m_sCreateListItemParams.Parent = m_sCreateListItemParams.Control->getRootItem();
				IListItem *i{ nullptr };
				CDialogBoxMenuListItem *dlg{ cast<CDialogBoxMenuListItem*>(sender) };
				switch (dlg->getItemTypeIndex())
				{
				case 0:
					i = new CListItemMenuLabel(dlg->getItemCaption());
					break;
				case 1:
					i = new CListItemMenuCheckBox(dlg->getItemCaption());
					break;
				case 2:
					i = new CListItemMenuRadioButton(dlg->getItemCaption());
					break;
				case 3:
					i = new CListItemMenuSeparator();
					break;
				}
				if (m_sCreateListItemParams.Item)
					*m_sCreateListItemParams.Item = i;
				if (i)
				{
					m_sCreateListItemParams.Parent->AddItem(i);
					if (m_sCreateListItemParams.Listener)
						m_sCreateListItemParams.Listener->OnCreateListItem(this, m_sCreateListItemParams.Parent, i);
				}
			}
		}

		void CPackageMainMenu::OnRestore(IDialogBox *sender)
		{

		}

		void CPackageMainMenu::OnMinimize(IDialogBox *sender)
		{

		}

		void CPackageMainMenu::OnMaximize(IDialogBox *sender)
		{

		}
	}
}
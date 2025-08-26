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
	namespace ide
	{
		const int DataIconWidth{ 30 };
		const int DataIconHeight{ 30 };
		const Color DataIcon[30 * 30]{
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 152, 152, 152, 255 }, {  41,  41,  41, 255 }, {   0,   0,   0, 255 }, {  41,  41,  40, 255 }, { 148, 148, 148, 255 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 150, 150, 150, 255 }, {  73,  66,  39, 255 }, { 239, 227, 188, 255 }, { 245, 233, 191, 255 }, { 236, 222, 175, 255 }, {  73,  66,  39, 255 }, { 136, 136, 135, 255 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, {  40,  40,  40, 255 }, { 239, 227, 188, 255 }, { 242, 225, 165, 255 }, { 238, 214, 128, 255 }, { 238, 214, 128, 255 }, { 224, 201, 120, 255 }, {  39,  39,  39, 255 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, {   0,   0,   0, 255 }, {   0,   0,   0, 255 }, {   0,   0,   0, 255 }, {   0,   0,   0, 255 }, {   0,   0,   0, 255 }, {   0,   0,   0, 255 }, { 238, 214, 128, 255 }, { 238, 214, 128, 255 }, { 238, 214, 128, 255 }, { 238, 214, 128, 255 }, {   0,   0,   0, 255 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, {   0,   0,   0, 255 }, { 232, 123,  97, 255 }, { 228,  97,  67, 255 }, { 228,  97,  67, 255 }, { 228,  97,  67, 255 }, {   0,   0,   0, 255 }, {   0,   0,   0, 255 }, { 165, 148,  88, 255 }, { 238, 214, 128, 255 }, { 224, 201, 120, 255 }, {  39,  39,  38, 255 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, {   0,   0,   0, 255 }, { 228,  97,  67, 255 }, { 223,  66,  30, 255 }, { 223,  66,  30, 255 }, { 223,  66,  30, 255 }, {   0,   0,   0, 255 }, { 194, 200, 208, 255 }, {   0,   0,   0, 255 }, { 187, 167, 100, 255 }, {  73,  66,  39, 255 }, { 140, 139, 137, 255 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, {   0,   0,   0, 255 }, { 228,  97,  67, 255 }, { 223,  66,  30, 255 }, { 223,  66,  30, 255 }, { 223,  66,  30, 255 }, { 130, 130, 130, 255 }, { 139, 162, 187, 255 }, {   0,   0,   0, 255 }, {  38,  38,  38, 255 }, { 141, 140, 139, 255 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, {   0,   0,   0, 255 }, { 228,  97,  67, 255 }, { 223,  66,  30, 255 }, { 223,  66,  30, 255 }, { 126,  36,  15, 255 }, { 199, 208, 216, 255 }, { 117, 144, 174, 255 }, {  97, 120, 145, 255 }, {  67,  67,  66, 255 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, {   0,   0,   0, 255 }, { 228,  97,  67, 255 }, { 223,  66,  30, 255 }, { 223,  66,  30, 255 }, { 106, 106, 106, 255 }, { 158, 177, 198, 255 }, { 117, 144, 174, 255 }, { 117, 144, 174, 255 }, {   0,   0,   0, 255 }, { 161, 160, 158, 255 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, {   0,   0,   0, 255 }, {   0,   0,   0, 255 }, {   0,   0,   0, 255 }, {   0,   0,   0, 255 }, { 199, 208, 216, 255 }, { 117, 144, 174, 255 }, { 117, 144, 174, 255 }, { 117, 144, 174, 255 }, {  97, 120, 145, 255 }, {   0,   0,   0, 255 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, {   0,   0,   0, 255 }, {   0,   0,   0, 255 }, {   0,   0,   0, 255 }, {   0,   0,   0, 255 }, {   0,   0,   0, 255 }, {   0,   0,   0, 255 }, {   0,   0,   0, 255 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
			{ 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 }, { 255, 255, 255,   0 },
		};
		const Image ComponentIcon{ DataIconWidth, DataIconHeight, DataIcon };

		const PointF CFormEditor::ComponentIconSize{ 28, 28 };

	#pragma region CGradientListener
		CFormEditor::CGradientListener::CGradientListener(CFormEditor *control) :
			m_pControl{ control }
		{

		}

		void CFormEditor::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CFormEditor::CFormEditor() :
			CControl(L"FormEditor", true, true, true, true, false, false),
			m_cGradientListener{ this },
			m_sBackgroundColor{ 191, 205, 219, 255 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_fSelectionSize{ 4 },
			m_aSelectionColor{ Color{ 127, 127, 255, 255 }, Color{ 127, 255, 127, 255 }, Color{ 255, 127, 127, 255 }, Color{ 127, 127, 127, 255 } },
			m_sGridEnabled{ true, true },
			m_sGridSize{ 10, 10 },
			m_fGridPointSize{ 1 },
			m_sGridPointColor{ 113, 21, 36, 255 },
			m_bRotateGridEnabled{ true },
			m_fRotateGridSize{ ntl::DegToRad<float>(10.0f) },
			m_bUseMask{ true },
			m_fRotateShift{ 2 },
			m_fSelectionBorderWidth{ 1 },
			m_sSelectionBorderColor{ 0, 0, 255, 150 },
			m_sSelectionBackgroundColor{ 0, 0, 255, 50 },
			m_sPadding{ 0, 0, 0, 0 },
			m_pCanvas{ nullptr },
			m_pCanvasControl{ nullptr },
			m_pCanvasControlBackground{ nullptr },
			m_pMask{ nullptr },
			m_bIgnoreGradient{ false },
			m_eHoveredPart{ Part::None },
			m_eOperation{ Part::None },
			m_bMouseDown{ false },
			m_pPropertySource{ nullptr }
		{
			OnSelectControl = nullptr;
			OnDeselectControl = nullptr;
			OnSelectComponent = nullptr;
			OnDeselectComponent = nullptr;
			OnCheckComponentAllowed = nullptr;
			OnComponentTransform = nullptr;
			OnControlTransform = nullptr;
			OnControlResize = nullptr;
			OnMouseDown = nullptr;

			setService(new CFormEditorService(this), true);
			setSize(PointF{ 185, 105 });
		}

		CFormEditor::CFormEditor(IForm *parent) :CFormEditor()
		{
			setForm(parent);
		}

		CFormEditor::CFormEditor(IControl *parent) : CFormEditor()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IControl getters
		CursorType CFormEditor::getCursor()
		{
			if (getForm() && !isMultipleSelect())
			{
				int index{ getFirstSelectedControl() };
				if (index >= 0 && m_aControls[index].Control->isVisible(false))
				{
					switch (getControlPart(index, (PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())))
					{
					case Part::ResizeLeft:
					case Part::ResizeRight:
						return CursorType::SizeWestEast;
					case Part::ResizeTop:
					case Part::ResizeBottom:
						return CursorType::SizeNorthSouth;
					case Part::ResizeLeftTop:
					case Part::ResizeRightBottom:
						return CursorType::SizeNorthwestSoutheast;
					case Part::ResizeRightTop:
					case Part::ResizeLeftBottom:
						return CursorType::SizeNortheastSouthwest;
					case Part::Rotate:
						return CursorType::SizeAll;
					default:
						break;
					}
				}
			}
			return CControl::getCursor();
		}

		IFont *CFormEditor::getFont()
		{
			if (m_pPropertySource && !CControl::getControlFont()->isEqual(m_pPropertySource->getFont()))
				CControl::setFont(m_pPropertySource->getFont(), true);
			return CControl::getControlFont();
		}

		IStyle *CFormEditor::getStyle()
		{
			if (m_pPropertySource)
				return m_pPropertySource->getStyle();
			return CControl::getStyle();
		}

		ITransform *CFormEditor::getTransformControls()
		{
			if (m_pPropertySource)
				return m_pPropertySource->getTransformControls();
			return CControl::getTransformControls();
		}

		bool CFormEditor::isShowHint()
		{
			if (m_pPropertySource)
				return m_pPropertySource->isShowHint();
			return CControl::isShowHint();
		}

		float CFormEditor::getHintDelay()
		{
			if (m_pPropertySource)
				return m_pPropertySource->getHintDelay();
			return CControl::getHintDelay();
		}

		PointF CFormEditor::getHintShift()
		{
			if (m_pPropertySource)
				return m_pPropertySource->getHintShift();
			return CControl::getHintShift();
		}

		RectF CFormEditor::getClientRect()
		{
			RectF result{ CControl::getClientRect() };
			result.Left += m_sPadding.Left;
			result.Top += m_sPadding.Top;
			result.Right -= m_sPadding.Right;
			result.Bottom -= m_sPadding.Bottom;
			result.validate();
			return result;
		}
	#pragma endregion

	#pragma region IFormEditor getters
		bool CFormEditor::isControlSelected(IControl *control)
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if (pos->Control == control)
					return pos->Selected;
			return false;
		}

		bool CFormEditor::isComponentSelected(IComponent *component)
		{
			if (component)
				for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++)
					if (pos->Component == component)
						return pos->Selected;
			return false;
		}

		PointF CFormEditor::getComponentPosition(IComponent *component)
		{
			for (auto pos : m_aComponents)
				if (pos.Component == component)
					return pos.Position;
			return PointF{ 0, 0 };
		}

		PointF CFormEditor::getControlPosition(IControl *control)
		{
			for (auto pos : m_aComponents)
				if (pos.Control == control)
					return pos.Position;
			return PointF{ 0, 0 };
		}
	#pragma endregion

	#pragma region Getters
		IForm *CFormEditor::getPropertySource()
		{
			return m_pPropertySource;
		}

		Color CFormEditor::getBackgroundColor()
		{
			if (m_pPropertySource)
				return m_pPropertySource->getBackgroundColor();
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CFormEditor::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}

		float CFormEditor::getSelectionSize() const
		{
			return m_fSelectionSize;
		}

		Color CFormEditor::getSelectionColor(const SelectionState state) const
		{
			return m_aSelectionColor[(int)state];
		}

		PointB CFormEditor::getGridEnabled() const
		{
			return m_sGridEnabled;
		}

		PointF CFormEditor::getGridSize() const
		{
			return m_sGridSize;
		}

		float CFormEditor::getGridPointSize() const
		{
			return m_fGridPointSize;
		}

		Color CFormEditor::getGridPointColor() const
		{
			return m_sGridPointColor;
		}

		bool CFormEditor::isRotateGridEnabled() const
		{
			return m_bRotateGridEnabled;
		}

		float CFormEditor::getRotateGridSize() const
		{
			return m_fRotateGridSize;
		}

		bool CFormEditor::isUseMask() const
		{
			return m_bUseMask;
		}

		float CFormEditor::getRotateShift() const
		{
			return m_fRotateShift;
		}

		float CFormEditor::getSelectionBorderWidth() const
		{
			return m_fSelectionBorderWidth;
		}

		Color CFormEditor::getSelectionBorderColor() const
		{
			return m_sSelectionBorderColor;
		}

		Color CFormEditor::getSelectionBackgroundColor() const
		{
			return m_sSelectionBackgroundColor;
		}

		RectF CFormEditor::getPadding() const
		{
			return m_sPadding;
		}
	#pragma endregion

	#pragma region IControl setters
		bool CFormEditor::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_fSelectionSize *= avg;
				m_sGridSize *= s;
				m_fGridPointSize *= avg;
				m_fRotateShift *= avg;
				m_fSelectionBorderWidth *= avg;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IFormEditor setters
		bool CFormEditor::setComponentPosition(IComponent *component, const PointF &value)
		{
			for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++)
				if (pos->Component == component)
				{
					if (IsNotEqual(pos->Position, value))
					{
						pos->Position = value;
						Repaint(false);
						return true;
					}
					break;
				}
			return false;
		}

		bool CFormEditor::setControlPosition(IControl *control, const PointF &value)
		{
			if (control)
				for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++)
					if (pos->Control == control)
					{
						if (IsNotEqual(pos->Position, value))
						{
							pos->Position = value;
							Repaint(false);
							return true;
						}
						break;
					}
			return false;
		}
	#pragma endregion

	#pragma region IFormEditor methods
		void CFormEditor::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}

		bool CFormEditor::SelectControl(IControl *control)
		{
			if (control)
			{
				bool changed{ false };
				for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
					if (pos->Control == control)
					{
						if (!pos->Selected)
						{
							pos->Selected = true;
							if (OnSelectControl)
								OnSelectControl(this, pos->Control);
							changed = true;
						}
						break;
					}
				for (auto &pos : m_aComponents)
					if (pos.Control == control)
					{
						if (!pos.Selected)
						{
							pos.Selected = true;
							changed = true;
						}
						break;
					}
				if (changed)
				{
					Repaint(false);
					return true;
				}
			}
			return false;
		}

		bool CFormEditor::SelectComponent(IComponent *component)
		{
			if (component)
				for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++)
					if (pos->Component == component)
					{
						if (!pos->Selected)
						{
							pos->Selected = true;
							if (OnSelectComponent)
								OnSelectComponent(this, pos->Component);
							Repaint(false);
							return true;
						}
						return false;
					}
			return false;
		}

		bool CFormEditor::SelectAllControls()
		{
			CLockRepaint lock{ this };
			bool result{ false };
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if (!pos->Selected)
				{
					pos->Selected = true;
					if (OnSelectControl)
						OnSelectControl(this, pos->Control);
					result = true;
				}
			for (auto &pos : m_aComponents)
				if (!pos.Component && !pos.Selected)
				{
					pos.Selected = true;
					result = true;
				}
			if (result)
				Repaint(false);
			return result;
		}

		bool CFormEditor::SelectAllComponents()
		{
			CLockRepaint lock{ this };
			bool result{ false };
			for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++)
				if (!pos->Selected && pos->Component)
				{
					pos->Selected = true;
					if (OnSelectComponent)
						OnSelectComponent(this, pos->Component);
					result = true;
				}
			if (result)
				Repaint(false);
			return result;
		}

		bool CFormEditor::SelectAll()
		{
			CLockRepaint lock{ this };
			bool r1{ SelectAllControls() }, r2{ SelectAllComponents() };
			return r1 || r2;
		}

		bool CFormEditor::DeselectControl(IControl *control)
		{
			if (control)
			{
				bool changed{ false };
				for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
					if (pos->Control == control)
					{
						if (pos->Selected)
						{
							pos->Selected = false;
							if (OnDeselectControl)
								OnDeselectControl(this, pos->Control);
							changed = true;
						}
						break;
					}
				for (auto &pos : m_aComponents)
					if (pos.Control == control)
					{
						if (pos.Selected)
						{
							pos.Selected = false;
							changed = true;
						}
						break;
					}
				if (changed)
				{
					Repaint(false);
					return true;
				}
			}
			return false;
		}

		bool CFormEditor::DeselectComponent(IComponent *component)
		{
			if (component)
				for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++)
					if (pos->Component == component)
					{
						if (pos->Selected)
						{
							pos->Selected = false;
							if (OnDeselectComponent)
								OnDeselectComponent(this, pos->Component);
							Repaint(false);
							return true;
						}
						return false;
					}
			return false;
		}

		bool CFormEditor::DeselectAllControls()
		{
			CLockRepaint lock{ this };
			bool result{ false };
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if (pos->Selected)
				{
					pos->Selected = false;
					if (OnDeselectControl)
						OnDeselectControl(this, pos->Control);
					result = true;
				}
			for (auto &pos : m_aComponents)
				if (!pos.Component && pos.Selected)
				{
					pos.Selected = false;
					result = true;
				}
			if (result)
				Repaint(false);
			return result;
		}

		bool CFormEditor::DeselectAllComponents()
		{
			CLockRepaint lock{ this };
			bool result{ false };
			for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++)
				if (pos->Selected && pos->Component)
				{
					pos->Selected = false;
					if (OnDeselectComponent)
						OnDeselectComponent(this, pos->Component);
					result = true;
				}
			if (result)
				Repaint(false);
			return result;
		}

		bool CFormEditor::DeselectAll()
		{
			CLockRepaint lock{ this };
			bool r1{ DeselectAllControls() }, r2{ DeselectAllComponents() };
			return r1 || r2;
		}

		bool CFormEditor::DeleteSelected()
		{
			CLockRepaint lock{ this };
			bool result{ false };
			while (true)
			{
				bool passed{ true };
				for (auto pos : m_aComponents)
					if (pos.Selected)
					{
						result = true;
						if (pos.Component)
							pos.Component->Release();
						else
							pos.Control->Release();
						passed = false;
						break;
					}
				if (passed)
					break;
			}
			while (true)
			{
				bool passed{ true };
				for (auto pos : m_aControls)
					if (pos.Selected)
					{
						result = true;
						pos.Control->Release();
						passed = false;
						break;
					}
				if (passed)
					break;
			}
			return result;
		}
	#pragma endregion

	#pragma region Setters
		bool CFormEditor::setPropertySource(IForm *value)
		{
			if (value != m_pPropertySource)
			{
				m_pPropertySource = value;
				return true;
			}
			return false;
		}

		bool CFormEditor::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				if (m_cBackgroundGradient.getPointCount() < 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormEditor::setSelectionSize(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fSelectionSize))
			{
				m_fSelectionSize = value;
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CFormEditor::setSelectionColor(const SelectionState state, const Color &value)
		{
			if (value != m_aSelectionColor[(int)state])
			{
				m_aSelectionColor[(int)state] = value;
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CFormEditor::setGridEnabled(const PointB &value)
		{
			if (value != m_sGridEnabled)
			{
				m_sGridEnabled = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CFormEditor::setGridSize(const PointF &value)
		{
			if (ntl::IsGreater<float>(value.X, 0) && ntl::IsGreater<float>(value.Y, 0) && IsNotEqual(value, m_sGridSize))
			{
				m_sGridSize = value;
				if (m_sGridEnabled.X || m_sGridEnabled.Y)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormEditor::setGridPointSize(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fGridPointSize))
			{
				m_fGridPointSize = value;
				if (m_sGridEnabled.X || m_sGridEnabled.Y)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormEditor::setGridPointColor(const Color &value)
		{
			if (value != m_sGridPointColor)
			{
				m_sGridPointColor = value;
				if (m_sGridEnabled.X || m_sGridEnabled.Y)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFormEditor::setRotateGridEnabled(const bool value)
		{
			if (value != m_bRotateGridEnabled)
			{
				m_bRotateGridEnabled = value;
				return true;
			}
			return false;
		}

		bool CFormEditor::setRotateGridSize(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fRotateGridSize))
			{
				m_fRotateGridSize = value;
				return true;
			}
			return false;
		}

		bool CFormEditor::setUseMask(const bool value)
		{
			if (value != m_bUseMask)
			{
				m_bUseMask = value;
				Repaint(true);
				return true;
			}
			return false;
		}

		bool CFormEditor::setRotateShift(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fRotateShift))
			{
				m_fRotateShift = value;
				if (!isMultipleSelect() && getFirstSelectedControl() >= 0)
					Repaint(false);
				return true;
			}
			return false;
		}

		bool CFormEditor::setSelectionBorderWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fSelectionBorderWidth))
			{
				m_fSelectionBorderWidth = value;
				if (m_bMouseDown && m_eOperation == Part::Select)
					Repaint(false);
				return true;
			}
			return false;
		}

		bool CFormEditor::setSelectionBorderColor(const Color &value)
		{
			if (value != m_sSelectionBorderColor)
			{
				m_sSelectionBorderColor = value;
				if (ntl::IsGreater<float>(m_fSelectionBorderWidth, 0) && m_bMouseDown && m_eOperation == Part::Select)
					Repaint(false);
				return true;
			}
			return false;
		}

		bool CFormEditor::setSelectionBackgroundColor(const Color &value)
		{
			if (value != m_sSelectionBackgroundColor)
			{
				m_sSelectionBackgroundColor = value;
				if (m_bMouseDown && m_eOperation == Part::Select)
					Repaint(false);
				return true;
			}
			return false;
		}

		bool CFormEditor::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				CLockRepaint lock{ this };
				m_sPadding = value;
				QueryService()->AlignControls();
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		bool CFormEditor::isMultipleSelect()
		{
			int count{ 0 };
			for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++)
				if (pos->Selected && pos->Component)
					if (++count > 1)
						return true;
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if (pos->Selected)
					if (++count > 1)
						return true;
			return false;
		}

		int CFormEditor::getFirstSelectedComponent()
		{
			for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++)
				if (pos->Selected && pos->Component)
					return int(pos - m_aComponents.begin());
			return -1;
		}

		int CFormEditor::getFirstSelectedControl()
		{
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if (pos->Selected)
					return int(pos - m_aControls.begin());
			return -1;
		}

		CFormEditor::Part CFormEditor::getControlPart(const int index, const PointF &position)
		{
			PointF p{ m_aControls[index].Control->FormToLocal(position) };
			IEditor *editor{ Application->Editor };
			if (editor && !editor->getControl(m_aControls[index].Control)->isTransformable())
				return Part::None;
			RectF r{ -m_fSelectionSize, -m_fSelectionSize, 0, 0 };
			if (p.X >= r.Left && p.X < r.Right && p.Y >= r.Top && p.Y < r.Bottom)
				return Part::ResizeLeftTop;
			r = RectF{ (m_aControls[index].Control->getWidth() - m_fSelectionSize) * 0.5f, -m_fSelectionSize, (m_aControls[index].Control->getWidth() + m_fSelectionSize) * 0.5f, 0 };
			if (p.X >= r.Left && p.X < r.Right && p.Y >= r.Top && p.Y < r.Bottom)
				return Part::ResizeTop;
			r = RectF{ m_aControls[index].Control->getWidth(), -m_fSelectionSize, m_aControls[index].Control->getWidth() + m_fSelectionSize, 0 };
			if (p.X >= r.Left && p.X < r.Right && p.Y >= r.Top && p.Y < r.Bottom)
				return Part::ResizeRightTop;
			r = RectF{ m_aControls[index].Control->getWidth(), (m_aControls[index].Control->getHeight() - m_fSelectionSize) * 0.5f, m_aControls[index].Control->getWidth() + m_fSelectionSize,
				(m_aControls[index].Control->getHeight() + m_fSelectionSize) * 0.5f };
			if (p.X >= r.Left && p.X < r.Right && p.Y >= r.Top && p.Y < r.Bottom)
				return Part::ResizeRight;
			r = RectF{ m_aControls[index].Control->getWidth(), m_aControls[index].Control->getHeight(), m_aControls[index].Control->getWidth() + m_fSelectionSize,
				m_aControls[index].Control->getHeight() + m_fSelectionSize };
			if (p.X >= r.Left && p.X < r.Right && p.Y >= r.Top && p.Y < r.Bottom)
				return Part::ResizeRightBottom;
			r = RectF{ (m_aControls[index].Control->getWidth() - m_fSelectionSize) * 0.5f, m_aControls[index].Control->getHeight(),
				(m_aControls[index].Control->getWidth() + m_fSelectionSize) * 0.5f, m_aControls[index].Control->getHeight() + m_fSelectionSize };
			if (p.X >= r.Left && p.X < r.Right && p.Y >= r.Top && p.Y < r.Bottom)
				return Part::ResizeBottom;
			r = RectF{ -m_fSelectionSize, m_aControls[index].Control->getHeight(), 0, m_aControls[index].Control->getHeight() + m_fSelectionSize };
			if (p.X >= r.Left && p.X < r.Right && p.Y >= r.Top && p.Y < r.Bottom)
				return Part::ResizeLeftBottom;
			r = RectF{ -m_fSelectionSize, (m_aControls[index].Control->getHeight() - m_fSelectionSize) * 0.5f, 0, (m_aControls[index].Control->getHeight() + m_fSelectionSize) * 0.5f };
			if (p.X >= r.Left && p.X < r.Right && p.Y >= r.Top && p.Y < r.Bottom)
				return Part::ResizeLeft;
			r = RectF{ m_aControls[index].Control->getWidth() + m_fSelectionSize + m_fRotateShift, -m_fSelectionSize, m_aControls[index].Control->getWidth() + 2 * m_fSelectionSize + m_fRotateShift, 0 };
			if (p.X >= r.Left && p.X < r.Right && p.Y >= r.Top && p.Y < r.Bottom)
				return Part::Rotate;
			return Part::None;
		}

		bool CFormEditor::DeselectChildren(IControl *parent)
		{
			bool result{ false };
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if (pos->Control != parent && parent->hasChild(pos->Control) && pos->Selected)
				{
					pos->Selected = false;
					result = true;
				}
			for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++)
				if (!pos->Component && pos->Control != parent && parent->hasChild(pos->Control) && pos->Selected)
				{
					pos->Selected = false;
					result = true;
				}
			return result;
		}

		bool CFormEditor::UpdateHoveredPart(const PointF &position)
		{
			Part part{ Part::None };
			if (!isMultipleSelect())
			{
				int index{ getFirstSelectedControl() };
				if (index >= 0 && m_aControls[index].Control->isVisible(false))
					part = getControlPart(index, position);
			}
			if (part != m_eHoveredPart)
			{
				m_eHoveredPart = part;
				return true;
			}
			return false;
		}

		int CFormEditor::getComponent(const PointF &position)
		{
			for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++)
			{
				Vec4f v{ ntl::Inversed<float>(getComponentMatrix(pos->Position)) * Vec4f{ position.X,  position.Y, 0, 1 } };
				if (v.X >= 0 && v.X < ComponentIconSize.X && v.Y >= 0 && v.Y < ComponentIconSize.Y)
					return int(pos - m_aComponents.begin());
			}
			return -1;
		}

		CFormEditor::SelectionState CFormEditor::getSelectionState(const bool is_multiple_select, const int first_selected_control, const int control_index, const Part part)
		{
			if (is_multiple_select)
				return SelectionState::Disabled;
			if (first_selected_control != control_index)
				return SelectionState::Normal;
			if (m_bMouseDown)
			{
				if (part == m_eOperation)
					return SelectionState::Active;
				return SelectionState::Normal;
			}
			if (part == m_eHoveredPart)
				return SelectionState::Hovered;
			return SelectionState::Normal;
		}

		Mat4f CFormEditor::getComponentMatrix(const PointF &position)
		{
			return getTransformMatrix() * getTransformControls()->getMatrix() * ntl::Mat4Translate<float>(position.X, position.Y, 0);
		}

		void CFormEditor::SetFormRecursively(IControl *control, IForm *form)
		{
			control->QueryService()->setForm(form);
			if (form)
				control->QueryService()->setTabOrder(form->QueryService()->GenerateTabOrder(control));
			for (int i = 0; i < control->getControlCount(); i++)
				SetFormRecursively(control->getControl(i), form);
		}

		void CFormEditor::GenerateNameRecursively(IControl *control)
		{
			if (getForm())
			{
				control->QueryService()->setName(getForm()->QueryService()->GenerateControlName(control));
				for (int i = 0; i < control->getControlCount(); i++)
					GenerateNameRecursively(control->getControl(i));
			}
		}

		void CFormEditor::NotifyAttach(IControl *control)
		{
			// Notify attached control about parent style & font change and attaching
			if (control->isUseParentStyle())
				CNotifier::ParentStyleChange(control);
			if (control->isUseParentFont())
				CNotifier::ParentFontChange(control);
			control->QueryService()->NotifyOnAttach();
			if (control->OnAttach)
				control->OnAttach(control);
			// Notificy this control about attaching
			QueryService()->NotifyOnChildAttach(control);
			if (OnChildAttach)
				OnChildAttach(this, control);
			// Notify all controls about attach event
			if (getForm())
				CNotifier::ControlAttach(getForm(), control);
			else
				CNotifier::ControlAttach(this, control);
		}

		void CFormEditor::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".BackgroundGradient", m_cBackgroundGradient);
			style->getOption(m_sClassName + L".SelectionSize", m_fSelectionSize);
			for (int i = 0; i <= (int)SelectionState::Disabled; i++)
			{
				String name;
				switch ((SelectionState)i)
				{
				case SelectionState::Normal:
					name = L"Normal";
					break;
				case SelectionState::Hovered:
					name = L"Hovered";
					break;
				case SelectionState::Active:
					name = L"Active";
					break;
				default:
					name = L"Disabled";
				}
				style->getOption(m_sClassName + L".SelectionColor[" + name + L"]", m_aSelectionColor[i]);
			}
			style->getOption(m_sClassName + L".GridSize", m_sGridSize);
			style->getOption(m_sClassName + L".GridPointSize", m_fGridPointSize);
			style->getOption(m_sClassName + L".GridPointColor", m_sGridPointColor);
			style->getOption(m_sClassName + L".RotateGridSize", m_fRotateGridSize);
			style->getOption(m_sClassName + L".RotateShift", m_fRotateShift);
			style->getOption(m_sClassName + L".SelectionBorderWidth", m_fSelectionBorderWidth);
			style->getOption(m_sClassName + L".SelectionBorderColor", m_sSelectionBorderColor);
			style->getOption(m_sClassName + L".SelectionBackgroundColor", m_sSelectionBackgroundColor);
			m_bIgnoreGradient = false;
		}
	#pragma endregion

	#pragma region Controls
		bool CFormEditor::InsertControl(IControl *control, const int before)
		{
			if (!control || control == this || control->hasChild(this))
				return false;
			CLockRepaint lock{ this }, lock2{ control };
			Repaint(true);
			// Detach control from parent
			if (control->getParent())
				control->getParent()->DetachControl(control);
			else if (control->getForm())
				control->getForm()->DetachControl(control);
			// Add control to list
			QueryService()->InsertControl(control, before);
			// Set parent, form, names, tab indices
			control->QueryService()->setParent(this);
			SetFormRecursively(control, getForm());
			GenerateNameRecursively(control);
			// Align controls if attached control is aligned
			if (control->getAlign() != Align::None)
				QueryService()->AlignControls();
			NotifyAttach(control);
			Repaint(true);
			return true;
		}
	#pragma endregion

	#pragma region Paint
		void CFormEditor::Render(IRenderer *renderer, const Mat4f &matrix)
		{
			RectF all_rect{ 0, 0, getWidth(), getHeight() };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				// Background
				if (m_cBackgroundGradient.getPointCount() > 1)
					renderer->DrawGradient(all_rect, m_cBackgroundGradient);
				else if (getBackgroundColor().A > 0)
					renderer->DrawRectangle(all_rect, getBackgroundColor());
				// Grid
				if ((m_sGridEnabled.X || m_sGridEnabled.Y) && m_sGridPointColor.A > 0 && getTransformControls()->isIdentity())
				{
					ITexture::IData *data{ m_pCanvas->Lock(TextureFormat::RGBA, 0, false) };
					if (data)
					{
						int x, y{ 0 }, px, py;
						float s{ m_fGridPointSize / 2 };
						Rect r{ ntl::Round<int>(-s), ntl::Round<int>(-s), ntl::Round<int>(-s) + ntl::Round<int>(m_fGridPointSize), ntl::Round<int>(-s) + ntl::Round<int>(m_fGridPointSize) };
						while ((float)y < getHeight())
						{
							x = 0;
							while ((float)x < getWidth())
							{
								for (py = y + r.Top; py < y + r.Bottom; py++)
									if (py >= 0 && py < data->Height)
										for (px = x + r.Left; px < x + r.Right; px++)
											if (px >= 0 && px < data->Width)
												data->setColor(px, py, m_sGridPointColor);
								x += ntl::Round<int>(m_sGridSize.X);
							}
							y += ntl::Round<int>(m_sGridSize.Y);
						}
						data->Release();
					}
				}

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, matrix, m_pCanvas, PointF{ 0, 0 });
		}

		void CFormEditor::RenderComponents(IRenderer *renderer)
		{
			IEditor *editor{ Application->Editor };
			// Render components
			RenderComponentCanvas(renderer);
			Mat4f m;
			CStorePrimitiveMatrix s_matrix{ renderer };
			for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++)
			{
				m = getComponentMatrix(pos->Position);
				ITexture *icon;
				if (pos->Component)
				{
					IPackageComponent *pc{ editor ? editor->getComponent(pos->Component) : nullptr };
					icon = (pc && pc->getIcon()) ? renderer->CreateTextureFromImage(*pc->getIcon(), 1, TextureFormat::RGBA, true) : nullptr;
				}
				else
				{
					IPackageControl *pc{ editor ? editor->getControl(pos->Control) : nullptr };
					icon = (pc && pc->getIcon()) ? renderer->CreateTextureFromImage(*pc->getIcon(), 1, TextureFormat::RGBA, true) : nullptr;
				}
				if (icon)
				{
					DrawCanvas(renderer, m, m_pCanvasControlBackground, PointF{ 0, 0 });
					renderer
						->ActivatePrimitiveMatrix(m * ntl::Mat4Translate<float>(1, 1, 0) * ntl::Mat4Scale<float>((ComponentIconSize.X - 2) / icon->Widthf, (ComponentIconSize.Y - 2) / icon->Heightf, 1))
						->DrawImage(icon, 1);
				}
				else
					DrawCanvas(renderer, m, m_pCanvasControl, PointF{ 0, 0 });
			}
		}

		void CFormEditor::RenderComponentCanvas(IRenderer *renderer)
		{
			if (!m_pCanvasControlBackground || !m_pCanvasControlBackground->isValid())
			{
				if (!m_pCanvasControlBackground)
					m_pCanvasControlBackground = renderer->CreateTexture(ntl::Round<int>(ComponentIconSize.X), ntl::Round<int>(ComponentIconSize.Y), 1, TextureFormat::RGBA, true);
				else
					m_pCanvasControlBackground->setSize(ntl::Round<int>(ComponentIconSize.X), ntl::Round<int>(ComponentIconSize.Y));
				if (m_pCanvasControlBackground)
				{
					CStoreTarget s_target{ renderer };
					BlockColors colors{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 }, Color{ 240, 240, 240, 255 }, Color{ 0, 0, 0, 0 } };
					renderer
						->ActivateTarget(m_pCanvasControlBackground)
						->Clear(Color{ 0, 0, 0, 0 })
						->DrawBlock(RectF{ 0, 0, ComponentIconSize.X, ComponentIconSize.Y }, RectF{ 1, 1, 1, 1 }, RectF{ 0, 0, 0, 0 }, colors);
					m_pCanvasControlBackground->setValid(true);
				}
			}
			if (!m_pCanvasControl || !m_pCanvasControl->isValid())
			{
				if (!m_pCanvasControl)
					m_pCanvasControl = renderer->CreateTexture(ntl::Round<int>(ComponentIconSize.X), ntl::Round<int>(ComponentIconSize.Y), 1, TextureFormat::RGBA, true);
				else
					m_pCanvasControl->setSize(ntl::Round<int>(ComponentIconSize.X), ntl::Round<int>(ComponentIconSize.Y));
				if (m_pCanvasControl)
				{
					CStoreTarget s_target{ renderer };
					BlockColors colors{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 }, Color{ 240, 240, 240, 255 }, Color{ 0, 0, 0, 0 } };
					renderer
						->ActivateTarget(m_pCanvasControl)
						->Clear(Color{ 0, 0, 0, 0 })
						->DrawBlock(RectF{ 0, 0, ComponentIconSize.X, ComponentIconSize.Y }, RectF{ 1, 1, 1, 1 }, RectF{ 0, 0, 0, 0 }, colors);
					ITexture *icon{ renderer->CreateTextureFromImage(ComponentIcon, 1, TextureFormat::RGBA, true) };
					if (icon)
					{
						CStorePrimitiveMatrix s_matrix{ renderer };
						renderer
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(1, 1, 0) * ntl::Mat4Scale<float>((ComponentIconSize.X - 2.0f) / DataIconWidth, (ComponentIconSize.Y - 2.0f) / DataIconHeight, 1))
							->DrawImage(icon, 1);
						icon->Release();
					}
					m_pCanvasControl->setValid(true);
				}
			}
		}

		void CFormEditor::RenderSelection(IRenderer *renderer)
		{
			bool multi{ isMultipleSelect() };
			int selected_control{ multi ? -1 : getFirstSelectedControl() };
			IEditor *editor{ Application->Editor };
			CStorePrimitiveMatrix s_matrix{ renderer };
			// Controls
			for (auto pos = m_aControls.begin(); pos != m_aControls.end(); pos++)
				if (pos->Selected && pos->Control->isVisible(true) && editor && editor->getControl(pos->Control)->isTransformable())
				{
					Mat4f m{ pos->Control->getTransformMatrix() };
					// LeftTop
					SelectionState state{ getSelectionState(multi, selected_control, int(pos - m_aControls.begin()), Part::ResizeLeftTop) };
					renderer
						->ActivatePrimitiveMatrix(&m)
						->DrawRectangle(RectF{ -m_fSelectionSize, -m_fSelectionSize, 0, 0 }, m_aSelectionColor[(int)state]);
					// Top
					state = getSelectionState(multi, selected_control, int(pos - m_aControls.begin()), Part::ResizeTop);
					renderer->DrawRectangle(RectF{ (pos->Control->getWidth() - m_fSelectionSize) * 0.5f, -m_fSelectionSize, (pos->Control->getWidth() + m_fSelectionSize) * 0.5f, 0 }, m_aSelectionColor[(int)state]);
					// RightTop
					state = getSelectionState(multi, selected_control, int(pos - m_aControls.begin()), Part::ResizeRightTop);
					renderer->DrawRectangle(RectF{ pos->Control->getWidth(), -m_fSelectionSize, pos->Control->getWidth() + m_fSelectionSize, 0 }, m_aSelectionColor[(int)state]);
					// Right
					state = getSelectionState(multi, selected_control, int(pos - m_aControls.begin()), Part::ResizeRight);
					renderer->DrawRectangle(RectF{ pos->Control->getWidth(), (pos->Control->getHeight() - m_fSelectionSize) * 0.5f, pos->Control->getWidth() + m_fSelectionSize,
						(pos->Control->getHeight() + m_fSelectionSize) * 0.5f }, m_aSelectionColor[(int)state]);
					// RightBottom
					state = getSelectionState(multi, selected_control, int(pos - m_aControls.begin()), Part::ResizeRightBottom);
					renderer->DrawRectangle(RectF{ pos->Control->getWidth(), pos->Control->getHeight(), pos->Control->getWidth() + m_fSelectionSize, pos->Control->getHeight() + m_fSelectionSize },
						m_aSelectionColor[(int)state]);
					// Bottom
					state = getSelectionState(multi, selected_control, int(pos - m_aControls.begin()), Part::ResizeBottom);
					renderer->DrawRectangle(RectF{ (pos->Control->getWidth() - m_fSelectionSize) * 0.5f, pos->Control->getHeight(), (pos->Control->getWidth() + m_fSelectionSize) * 0.5f,
						pos->Control->getHeight() + m_fSelectionSize }, m_aSelectionColor[(int)state]);
					// LeftBottom
					state = getSelectionState(multi, selected_control, int(pos - m_aControls.begin()), Part::ResizeLeftBottom);
					renderer->DrawRectangle(RectF{ -m_fSelectionSize, pos->Control->getHeight(), 0, pos->Control->getHeight() + m_fSelectionSize }, m_aSelectionColor[(int)state]);
					// Left
					state = getSelectionState(multi, selected_control, int(pos - m_aControls.begin()), Part::ResizeLeft);
					renderer->DrawRectangle(RectF{ -m_fSelectionSize, (pos->Control->getHeight() - m_fSelectionSize) * 0.5f, 0, (pos->Control->getHeight() + m_fSelectionSize) * 0.5f },
						m_aSelectionColor[(int)state]);
					// Rotate
					if (!multi)
					{
						state = getSelectionState(multi, selected_control, int(pos - m_aControls.begin()), Part::Rotate);
						renderer->DrawRectangle(RectF{ pos->Control->getWidth() + m_fSelectionSize + m_fRotateShift, -m_fSelectionSize, pos->Control->getWidth() + 2 * m_fSelectionSize + m_fRotateShift, 0 },
							m_aSelectionColor[(int)state]);
					}
				}
			// Components
			for (auto pos = m_aComponents.begin(); pos != m_aComponents.end(); pos++)
				if (pos->Selected)
				{
					Mat4f m{ getComponentMatrix(pos->Position) };
					renderer
						->ActivatePrimitiveMatrix(&m)
						// LeftTop
						->DrawRectangle(RectF{ -m_fSelectionSize, -m_fSelectionSize, 0, 0 }, m_aSelectionColor[(int)SelectionState::Disabled])
						// RightTop
						->DrawRectangle(RectF{ ComponentIconSize.X, -m_fSelectionSize, ComponentIconSize.X + m_fSelectionSize, 0 }, m_aSelectionColor[(int)SelectionState::Disabled])
						// RightBottom
						->DrawRectangle(RectF{ ComponentIconSize.X, ComponentIconSize.Y, ComponentIconSize.X + m_fSelectionSize, ComponentIconSize.Y + m_fSelectionSize }, m_aSelectionColor[(int)SelectionState::Disabled])
						// LeftBottom
						->DrawRectangle(RectF{ -m_fSelectionSize, ComponentIconSize.Y, 0, ComponentIconSize.Y + m_fSelectionSize }, m_aSelectionColor[(int)SelectionState::Disabled]);
				}
		}

		void CFormEditor::RenderSelectionRectangle(IRenderer *renderer, const RectF &rect)
		{
			if (ntl::IsGreater<float>(m_fSelectionBorderWidth, 0))
			{
				BlockColors colors{ m_sSelectionBorderColor, m_sSelectionBorderColor, m_sSelectionBorderColor, m_sSelectionBorderColor, m_sSelectionBackgroundColor, Color{ 0, 0, 0, 0 } };
				renderer->DrawBlock(rect, RectF{ m_fSelectionBorderWidth, m_fSelectionBorderWidth, m_fSelectionBorderWidth, m_fSelectionBorderWidth }, RectF{ 0, 0, 0, 0 }, colors);
			}
			else
				renderer->DrawRectangle(rect, m_sSelectionBackgroundColor);
		}

		void CFormEditor::RenderMask(IRenderer *renderer)
		{
			if (PrepareCanvas(renderer, &m_pMask, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pMask)
					->Clear(Color{ 0, 0, 0, 255 });
				m_pMask->setValid(true);
			}
		}
	#pragma endregion
	}
}
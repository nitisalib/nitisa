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
	namespace script
	{
		String ExpressionTypeToString(const ExpressionType type)
		{
			switch (type)
			{
			case ExpressionType::Bool: return L"Bool";
			case ExpressionType::Brace: return L"Brace";
			case ExpressionType::Call: return L"Call";
			case ExpressionType::Cast: return L"Cast";
			case ExpressionType::Float: return L"Float";
			case ExpressionType::Identifier: return L"Identifier";
			case ExpressionType::Integer: return L"Integer";
			case ExpressionType::Null: return L"Null";
			case ExpressionType::Operator: return L"Operator";
			case ExpressionType::Sequence: return L"Sequence";
			case ExpressionType::String: return L"String";
			case ExpressionType::Subscript: return L"Subscript";
			default: return L"";
			}
		}
	}
}
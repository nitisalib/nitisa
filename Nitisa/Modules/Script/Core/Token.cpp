// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
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
		bool Token::operator==(const Token &other) const
		{
			if (Type != other.Type)
				return false;
			switch (Type)
			{
			case TokenType::String:
				if (Op != other.Op || Value != other.Value || Prefix != other.Prefix || Postfix != other.Postfix)
					return false;
				break;
			case TokenType::Integer:
				if (Value != other.Value || Prefix != other.Prefix || Postfix != other.Postfix || Base != other.Base)
					return false;
				break;
			case TokenType::Float:
				if (Value != other.Value || Postfix != other.Postfix || Base != other.Base)
					return false;
				break;
			case TokenType::Operator:
				if (Op != other.Op)
					return false;
				break;
			case TokenType::Group:
				if (Op != other.Op || Count != other.Count)
					return false;
				break;
			default:
				if (Value != other.Value)
					return false;
				break;
			}
			return true;
		}

		bool Token::operator!=(const Token &other) const
		{
			if (Type != other.Type)
				return true;
			switch (Type)
			{
			case TokenType::String:
				if (Op != other.Op || Value != other.Value || Prefix != other.Prefix || Postfix != other.Postfix)
					return true;
				break;
			case TokenType::Integer:
				if (Value != other.Value || Prefix != other.Prefix || Postfix != other.Postfix || Base != other.Base)
					return true;
				break;
			case TokenType::Float:
				if (Value != other.Value || Postfix != other.Postfix || Base != other.Base)
					return true;
				break;
			case TokenType::Operator:
				if (Op != other.Op)
					return true;
				break;
			case TokenType::Group:
				if (Op != other.Op || Count != other.Count)
					return true;
				break;
			default:
				if (Value != other.Value)
					return true;
				break;
			}
			return false;
		}

		String TokenToString(const Token &token)
		{
			String result{ token.Prefix };
			if (token.Type == TokenType::String)
			{
				result += token.Op->Name + token.Value;
				if (token.Op->Name != L"//")
					result += token.Op->Close.empty() ? token.Op->Name : token.Op->Close;
			}
			else
				result += token.Value;
			result += token.Postfix;
			return result;
		}
	}
}
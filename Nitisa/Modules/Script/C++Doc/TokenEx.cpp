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
		namespace cppdoc
		{
			TokenEx::TokenEx(script::Token *token, const size_t &index) :
				m_pToken{ token },
				m_iIndex{ index }
			{

			}

			script::Token *TokenEx::operator->()
			{
				return m_pToken;
			}

			bool TokenEx::operator==(const TokenEx &other) const
			{
				return *other.m_pToken == *m_pToken;
			}

			bool TokenEx::operator!=(const TokenEx &other) const
			{
				return *other.m_pToken != *m_pToken;
			}

			TokenEx::operator script::Token *()
			{
				return m_pToken;
			}

			TokenEx &TokenEx::operator=(const TokenEx &other)
			{
				m_pToken = other.m_pToken;
				m_iIndex = other.m_iIndex;
				return *this;
			}

			TokenEx &TokenEx::operator=(TokenEx &&other)
			{
				m_pToken = other.m_pToken;
				m_iIndex = other.m_iIndex;
				return *this;
			}
		}
	}
}
// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef _WIN32
#include <Windows.h>
#include <shellapi.h>
#endif

namespace nitisa
{
	namespace standard
	{
	#pragma region Constructor & destructor
		CAdminRights::CAdminRights() :
			CComponent(L"AdminRights"),
			m_bHasAdminRights{ false }
		{
		#ifdef _WIN32
			BOOL is_admin{ FALSE };
			PSID group{ nullptr };
			SID_IDENTIFIER_AUTHORITY authority{ SECURITY_NT_AUTHORITY };
			if (AllocateAndInitializeSid(&authority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &group))
			{
				if (CheckTokenMembership(nullptr, group, &is_admin))
					m_bHasAdminRights = is_admin ? true : false;
				FreeSid(group);
			}
		#endif
		}

		CAdminRights::CAdminRights(IForm *parent) :CAdminRights()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Getters
		bool CAdminRights::hasAdminRights()
		{
			return m_bHasAdminRights;
		}
	#pragma endregion

	#pragma region Methods
		bool CAdminRights::Request(const String &params)
		{
		#ifdef _WIN32
			if (!m_bHasAdminRights)
			{
				SHELLEXECUTEINFO sei{ sizeof(sei) };
				sei.lpVerb = L"runas";
				const String s{ Application->ApplicationDirectory + Application->ApplicationFileName + ((params.length() > 0) ? (L" " + params) : L"") };
				sei.lpFile = s.c_str();
				sei.hwnd = NULL;
				sei.nShow = SW_NORMAL;
				if (!ShellExecuteEx(&sei))
					return false;
				exit(0);
				return true;
			}
		#endif
			return false;
		}
	#pragma endregion
	}
}
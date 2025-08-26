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
#pragma region Constructor & destructor
	CPackageEntity::CPackageEntity(IPackage *package, const String &ns) :
		m_pPackage{ package },
		m_sNamespace{ ns }
	{

	}

	void CPackageEntity::Release()
	{
		delete this;
	}
#pragma endregion

#pragma region Getters
	IPackage *CPackageEntity::getPackage()
	{
		return m_pPackage;
	}

	String CPackageEntity::getNamespace()
	{
		return m_sNamespace;
	}

	int CPackageEntity::getPlatformCount()
	{
		return (int)m_aPlatforms.size();
	}

	PlatformVersion CPackageEntity::getPlatform(const int index)
	{
		if (index >= 0 && index < (int)m_aPlatforms.size())
			return m_aPlatforms[index];
		return PlatformVersion{ PlatformType::None };
	}

	int CPackageEntity::getHeaderFileCount()
	{
		return (int)m_aHeaderFiles.size();
	}

	String CPackageEntity::getHeaderFile(const int index)
	{
		if (index >= 0 && index < (int)m_aHeaderFiles.size())
			return m_aHeaderFiles[index];
		return L"";
	}

	int CPackageEntity::getForwardDeclarationCount()
	{
		return (int)m_aForwardDeclarations.size();
	}

	IPackageEntity::ForwardDeclaration CPackageEntity::getForwardDeclaration(const int index)
	{
		if (index >= 0 && index < (int)m_aForwardDeclarations.size())
			return m_aForwardDeclarations[index];
		return ForwardDeclaration{ L"", L"" };
	}
#pragma endregion

#pragma region Setters
	bool CPackageEntity::setNamespace(const String &value)
	{
		if (value != m_sNamespace)
		{
			m_sNamespace = value;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Helpers
	CPackageEntity *CPackageEntity::AddPlatform(const PlatformVersion &platform)
	{
		m_aPlatforms.push_back(platform);
		return this;
	}

	CPackageEntity *CPackageEntity::AddHeaderFile(const String &value)
	{
		m_aHeaderFiles.push_back(value);
		return this;
	}

	CPackageEntity *CPackageEntity::AddForwardDeclaration(const String &value, const String &header_file, const String &ns)
	{
		m_aForwardDeclarations.push_back(ForwardDeclaration{ value, header_file, ns });
		return this;
	}
#pragma endregion
}
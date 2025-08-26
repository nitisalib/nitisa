// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/PlatformVersion.h"
#include "../../Core/Strings.h"
#include "../Interfaces/IPackageEntity.h"
#include <vector>

namespace nitisa
{
	class IPackage;

	class CPackageEntity :public virtual IPackageEntity
	{
	private:
		IPackage *m_pPackage;
		String m_sNamespace;
		std::vector<PlatformVersion> m_aPlatforms;
		StringArray m_aHeaderFiles;
		std::vector<ForwardDeclaration> m_aForwardDeclarations;
	public:
		// Properties
		IPackage *getPackage() override;
		String getNamespace() override;
		int getPlatformCount() override;
		PlatformVersion getPlatform(const int index) override;
		int getHeaderFileCount() override;
		String getHeaderFile(const int index) override;
		int getForwardDeclarationCount() override;
		ForwardDeclaration getForwardDeclaration(const int index) override;

		bool setNamespace(const String &value) override;

		void Release() override;

		CPackageEntity(
			IPackage *package, // Package to which the entity belongs
			const String &ns); // Namespace to which the entity belongs
		virtual ~CPackageEntity() = default;

		CPackageEntity *AddPlatform(const PlatformVersion &platform); // Add new platform to the list
		CPackageEntity *AddHeaderFile(const String &value); // Add new header file to the list(use path relative to the Packages directory)
		CPackageEntity *AddForwardDeclaration(const String &value, const String &header_file, const String &ns);
	};
}
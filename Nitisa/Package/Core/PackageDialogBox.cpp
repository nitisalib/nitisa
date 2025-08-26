// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	CPackageDialogBox::CPackageDialogBox(IPackage *package, const String &ns) :CPackageControl(package, ns)
	{

	}

	bool CPackageDialogBox::isDialogBox()
	{
		return true;
	}

	int CPackageDialogBox::getDialogBoxHeaderFileCount()
	{
		return (int)m_aDialogBoxHeaderFiles.size();
	}

	String CPackageDialogBox::getDialogBoxHeaderFile(const int index)
	{
		if (index >= 0 && index < (int)m_aDialogBoxHeaderFiles.size())
			return m_aDialogBoxHeaderFiles[index];
		return L"";
	}

	void CPackageDialogBox::AddDialogBoxHeaderFile(const String &value)
	{
		m_aDialogBoxHeaderFiles.push_back(value);
	}
}
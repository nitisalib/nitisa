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
	namespace standard
	{
	#pragma region Constructor & destructor
		CSysBrowseFolderDialog::CSysBrowseFolderDialog() :
			CComponent(L"SysBrowseFolderDialog"),
			m_bOnlyFileSystem{ false },
			m_bNoNetwork{ false },
			m_bNoAncestors{ false },
			m_bShowEditBox{ false },
			m_bNewStyle{ false },
			m_bShowHint{ false },
			m_bHideNewFolder{ false },
			m_bDontTranslateTargets{ false },
			m_bOnlyComputers{ false },
			m_bOnlyPrinters{ false },
			m_bShowFiles{ false },
			m_bShowShareable{ false }
		{

		}

		CSysBrowseFolderDialog::CSysBrowseFolderDialog(IForm *parent) :CSysBrowseFolderDialog()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		String CSysBrowseFolderDialog::getFolder()
		{
			return m_sFolder;
		}

		String CSysBrowseFolderDialog::getTitle()
		{
			return m_sTitle;
		}

		bool CSysBrowseFolderDialog::isOnlyFileSystem()
		{
			return m_bOnlyFileSystem;
		}

		bool CSysBrowseFolderDialog::isNoNetwork()
		{
			return m_bNoNetwork;
		}

		bool CSysBrowseFolderDialog::isNoAncestors()
		{
			return m_bNoAncestors;
		}

		bool CSysBrowseFolderDialog::isShowEditBox()
		{
			return m_bShowEditBox;
		}

		bool CSysBrowseFolderDialog::isNewStyle()
		{
			return m_bNewStyle;
		}

		bool CSysBrowseFolderDialog::isShowHint()
		{
			return m_bShowHint;
		}

		bool CSysBrowseFolderDialog::isHideNewFolder()
		{
			return m_bHideNewFolder;
		}

		bool CSysBrowseFolderDialog::isDontTranslateTargets()
		{
			return m_bDontTranslateTargets;
		}

		bool CSysBrowseFolderDialog::isOnlyComputers()
		{
			return m_bOnlyComputers;
		}

		bool CSysBrowseFolderDialog::isOnlyPrinters()
		{
			return m_bOnlyPrinters;
		}

		bool CSysBrowseFolderDialog::isShowFiles()
		{
			return m_bShowFiles;
		}

		bool CSysBrowseFolderDialog::isShowShareable()
		{
			return m_bShowShareable;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CSysBrowseFolderDialog::setTitle(const String &value)
		{
			if (value != m_sTitle)
			{
				m_sTitle = value;
				return true;
			}
			return false;
		}

		bool CSysBrowseFolderDialog::setOnlyFileSystem(const bool value)
		{
			if (value != m_bOnlyFileSystem)
			{
				m_bOnlyFileSystem = value;
				return true;
			}
			return false;
		}

		bool CSysBrowseFolderDialog::setNoNetwork(const bool value)
		{
			if (value != m_bNoNetwork)
			{
				m_bNoNetwork = value;
				return true;
			}
			return false;
		}

		bool CSysBrowseFolderDialog::setNoAncestors(const bool value)
		{
			if (value != m_bNoAncestors)
			{
				m_bNoAncestors = value;
				return true;
			}
			return false;
		}

		bool CSysBrowseFolderDialog::setShowEditBox(const bool value)
		{
			if (value != m_bShowEditBox)
			{
				m_bShowEditBox = value;
				return true;
			}
			return false;
		}

		bool CSysBrowseFolderDialog::setNewStyle(const bool value)
		{
			if (value != m_bNewStyle)
			{
				m_bNewStyle = value;
				return true;
			}
			return false;
		}

		bool CSysBrowseFolderDialog::setShowHint(const bool value)
		{
			if (value != m_bShowHint)
			{
				m_bShowHint = value;
				return true;
			}
			return false;
		}

		bool CSysBrowseFolderDialog::setHideNewFolder(const bool value)
		{
			if (value != m_bHideNewFolder)
			{
				m_bHideNewFolder = value;
				return true;
			}
			return false;
		}

		bool CSysBrowseFolderDialog::setDontTranslateTargets(const bool value)
		{
			if (value != m_bDontTranslateTargets)
			{
				m_bDontTranslateTargets = value;
				return true;
			}
			return false;
		}

		bool CSysBrowseFolderDialog::setOnlyComputers(const bool value)
		{
			if (value != m_bOnlyComputers)
			{
				m_bOnlyComputers = value;
				return true;
			}
			return false;
		}

		bool CSysBrowseFolderDialog::setOnlyPrinters(const bool value)
		{
			if (value != m_bOnlyPrinters)
			{
				m_bOnlyPrinters = value;
				return true;
			}
			return false;
		}

		bool CSysBrowseFolderDialog::setShowFiles(const bool value)
		{
			if (value != m_bShowFiles)
			{
				m_bShowFiles = value;
				return true;
			}
			return false;
		}

		bool CSysBrowseFolderDialog::setShowShareable(const bool value)
		{
			if (value != m_bShowShareable)
			{
				m_bShowShareable = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface helpers
		bool CSysBrowseFolderDialog::Execute()
		{
			return Application->Dialogs->BrowseFolder(m_sFolder, m_sTitle, m_bOnlyFileSystem, m_bNoNetwork, m_bNoAncestors, m_bShowEditBox, m_bNewStyle, m_bShowHint, m_bHideNewFolder,
				m_bDontTranslateTargets, m_bOnlyComputers, m_bOnlyPrinters, m_bShowFiles, m_bShowShareable);
		}
	#pragma endregion
	}
}
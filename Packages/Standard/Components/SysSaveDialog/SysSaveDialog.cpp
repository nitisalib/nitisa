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
		CSysSaveDialog::CSysSaveDialog() :
			CComponent(L"SysSaveDialog"),
			m_iFilterIndex{ 1 },
			m_bCreatePrompt{ true },
			m_bMustExists{ true },
			m_bShowHidden{ true },
			m_bHideReadOnly{ false },
			m_bNoNetwork{ true },
			m_bOverwritePrompt{ true }
		{

		}

		CSysSaveDialog::CSysSaveDialog(IForm *parent) :CSysSaveDialog()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		String CSysSaveDialog::getFilter()
		{
			return m_sFilter;
		}

		int CSysSaveDialog::getFilterIndex()
		{
			return m_iFilterIndex;
		}

		String CSysSaveDialog::getFileName()
		{
			return m_sFileName;
		}

		String CSysSaveDialog::getDefaultExtension()
		{
			return m_sDefaultExtension;
		}

		bool CSysSaveDialog::isCreatePrompt()
		{
			return m_bCreatePrompt;
		}

		bool CSysSaveDialog::isMustExists()
		{
			return m_bMustExists;
		}

		bool CSysSaveDialog::isShowHidden()
		{
			return m_bShowHidden;
		}

		bool CSysSaveDialog::isHideReadOnly()
		{
			return m_bHideReadOnly;
		}

		bool CSysSaveDialog::isNoNetwork()
		{
			return m_bNoNetwork;
		}

		bool CSysSaveDialog::isOverwritePrompt()
		{
			return m_bOverwritePrompt;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CSysSaveDialog::setFilter(const String &value)
		{
			if (value != m_sFilter)
			{
				m_sFilter = value;
				return true;
			}
			return false;
		}

		bool CSysSaveDialog::setFilterIndex(const int value)
		{
			if (value != m_iFilterIndex)
			{
				m_iFilterIndex = value;
				return true;
			}
			return false;
		}

		bool CSysSaveDialog::setFileName(const String &value)
		{
			if (value != m_sFileName)
			{
				m_sFileName = value;
				return true;
			}
			return false;
		}

		bool CSysSaveDialog::setDefaultExtension(const String &value)
		{
			if (value != m_sDefaultExtension)
			{
				m_sDefaultExtension = value;
				return true;
			}
			return false;
		}

		bool CSysSaveDialog::setCreatePrompt(const bool value)
		{
			if (value != m_bCreatePrompt)
			{
				m_bCreatePrompt = value;
				return true;
			}
			return false;
		}

		bool CSysSaveDialog::setMustExists(const bool value)
		{
			if (value != m_bMustExists)
			{
				m_bMustExists = value;
				return true;
			}
			return false;
		}

		bool CSysSaveDialog::setShowHidden(const bool value)
		{
			if (value != m_bShowHidden)
			{
				m_bShowHidden = value;
				return true;
			}
			return false;
		}

		bool CSysSaveDialog::setHideReadOnly(const bool value)
		{
			if (value != m_bHideReadOnly)
			{
				m_bHideReadOnly = value;
				return true;
			}
			return false;
		}

		bool CSysSaveDialog::setNoNetwork(const bool value)
		{
			if (value != m_bNoNetwork)
			{
				m_bNoNetwork = value;
				return true;
			}
			return false;
		}

		bool CSysSaveDialog::setOverwritePrompt(const bool value)
		{
			if (value != m_bOverwritePrompt)
			{
				m_bOverwritePrompt = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface helpers
		bool CSysSaveDialog::Execute()
		{
			return Application->Dialogs->Save(m_sFilter, m_iFilterIndex, m_sFileName, m_sDefaultExtension, m_bCreatePrompt, m_bMustExists, m_bShowHidden, m_bHideReadOnly, m_bNoNetwork, m_bOverwritePrompt);
		}
	#pragma endregion
	}
}
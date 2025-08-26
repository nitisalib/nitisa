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
		CSysOpenDialog::CSysOpenDialog() :
			CComponent(L"SysOpenDialog"),
			m_sFilter{ L"All files(*.*)|*.*" },
			m_iFilterIndex{ 1 },
			m_bMultiselect{ false },
			m_bCreatePrompt{ true },
			m_bMustExists{ true },
			m_bShowHidden{ true },
			m_bHideReadOnly{ false },
			m_bNoNetwork{ true }
		{

		}

		CSysOpenDialog::CSysOpenDialog(IForm *parent) :CSysOpenDialog()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		String CSysOpenDialog::getFilter()
		{
			return m_sFilter;
		}

		int CSysOpenDialog::getFilterIndex()
		{
			return m_iFilterIndex;
		}

		String CSysOpenDialog::getFileName()
		{
			return m_sFileName;
		}

		int CSysOpenDialog::getFileCount()
		{
			return (int)m_aFiles.size();
		}

		String CSysOpenDialog::getFile(const int index)
		{
			if (index >= 0 && index < (int)m_aFiles.size())
				return m_aFiles[index];
			return L"";
		}

		bool CSysOpenDialog::isMultiselect()
		{
			return m_bMultiselect;
		}

		bool CSysOpenDialog::isCreatePrompt()
		{
			return m_bCreatePrompt;
		}

		bool CSysOpenDialog::isMustExists()
		{
			return m_bMustExists;
		}

		bool CSysOpenDialog::isShowHidden()
		{
			return m_bShowHidden;
		}

		bool CSysOpenDialog::isHideReadOnly()
		{
			return m_bHideReadOnly;
		}

		bool CSysOpenDialog::isNoNetwork()
		{
			return m_bNoNetwork;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CSysOpenDialog::setFilter(const String &value)
		{
			if (value != m_sFilter)
			{
				m_sFilter = value;
				return true;
			}
			return false;
		}

		bool CSysOpenDialog::setFilterIndex(const int value)
		{
			if (value != m_iFilterIndex)
			{
				m_iFilterIndex = value;
				return true;
			}
			return false;
		}

		bool CSysOpenDialog::setFileName(const String &value)
		{
			if (value != m_sFileName)
			{
				m_sFileName = value;
				return true;
			}
			return false;
		}

		bool CSysOpenDialog::setMultiselect(const bool value)
		{
			if (value != m_bMultiselect)
			{
				m_bMultiselect = value;
				return true;
			}
			return false;
		}

		bool CSysOpenDialog::setCreatePrompt(const bool value)
		{
			if (value != m_bCreatePrompt)
			{
				m_bCreatePrompt = value;
				return true;
			}
			return false;
		}

		bool CSysOpenDialog::setMustExists(const bool value)
		{
			if (value != m_bMustExists)
			{
				m_bMustExists = value;
				return true;
			}
			return false;
		}

		bool CSysOpenDialog::setShowHidden(const bool value)
		{
			if (value != m_bShowHidden)
			{
				m_bShowHidden = value;
				return true;
			}
			return false;
		}

		bool CSysOpenDialog::setHideReadOnly(const bool value)
		{
			if (value != m_bHideReadOnly)
			{
				m_bHideReadOnly = value;
				return true;
			}
			return false;
		}

		bool CSysOpenDialog::setNoNetwork(const bool value)
		{
			if (value != m_bNoNetwork)
			{
				m_bNoNetwork = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface helpers
		bool CSysOpenDialog::Execute()
		{
			m_aFiles.clear();
			bool result{ Application->Dialogs->Open(m_sFilter, m_iFilterIndex, m_sFileName, m_bMultiselect, m_bCreatePrompt, m_bMustExists, m_bShowHidden, m_bHideReadOnly, m_bNoNetwork) };
			if (result)
			{
				if (m_bMultiselect)
				{
					StringArray parts{ Explode(m_sFileName, L"\n") };
					for (int i = 1; i < (int)parts.size(); i++)
						m_aFiles.push_back(parts[0] + Application->System->DirectorySeparator + parts[i]);
					if (m_aFiles.size() > 0)
						m_sFileName = m_aFiles[0];
				}
				else
					m_aFiles.push_back(m_sFileName);
			}
			return result;
		}
	#pragma endregion
	}
}
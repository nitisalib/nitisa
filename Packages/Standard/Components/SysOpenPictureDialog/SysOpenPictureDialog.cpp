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
		CSysOpenPictureDialog::CSysOpenPictureDialog() :
			CComponent(L"SysOpenPictureDialog"),
			m_iFilterIndex{ 1 },
			m_bMultiselect{ false },
			m_bCreatePrompt{ true },
			m_bMustExists{ true },
			m_bShowHidden{ true },
			m_bHideReadOnly{ false },
			m_bNoNetwork{ true }
		{
			m_sFilter = Application->Picture->Filter;
		}

		CSysOpenPictureDialog::CSysOpenPictureDialog(IForm *parent) :CSysOpenPictureDialog()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		String CSysOpenPictureDialog::getFilter()
		{
			return m_sFilter;
		}

		int CSysOpenPictureDialog::getFilterIndex()
		{
			return m_iFilterIndex;
		}

		String CSysOpenPictureDialog::getFileName()
		{
			return m_sFileName;
		}

		int CSysOpenPictureDialog::getFileCount()
		{
			return (int)m_aFiles.size();
		}

		String CSysOpenPictureDialog::getFile(const int index)
		{
			if (index >= 0 && index < (int)m_aFiles.size())
				return m_aFiles[index];
			return L"";
		}

		bool CSysOpenPictureDialog::isMultiselect()
		{
			return m_bMultiselect;
		}

		bool CSysOpenPictureDialog::isCreatePrompt()
		{
			return m_bCreatePrompt;
		}

		bool CSysOpenPictureDialog::isMustExists()
		{
			return m_bMustExists;
		}

		bool CSysOpenPictureDialog::isShowHidden()
		{
			return m_bShowHidden;
		}

		bool CSysOpenPictureDialog::isHideReadOnly()
		{
			return m_bHideReadOnly;
		}

		bool CSysOpenPictureDialog::isNoNetwork()
		{
			return m_bNoNetwork;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CSysOpenPictureDialog::setFilter(const String &value)
		{
			if (value != m_sFilter)
			{
				m_sFilter = value;
				return true;
			}
			return false;
		}

		bool CSysOpenPictureDialog::setFilterIndex(const int value)
		{
			if (value != m_iFilterIndex)
			{
				m_iFilterIndex = value;
				return true;
			}
			return false;
		}

		bool CSysOpenPictureDialog::setFileName(const String &value)
		{
			if (value != m_sFileName)
			{
				m_sFileName = value;
				return true;
			}
			return false;
		}

		bool CSysOpenPictureDialog::setMultiselect(const bool value)
		{
			if (value != m_bMultiselect)
			{
				m_bMultiselect = value;
				return true;
			}
			return false;
		}

		bool CSysOpenPictureDialog::setCreatePrompt(const bool value)
		{
			if (value != m_bCreatePrompt)
			{
				m_bCreatePrompt = value;
				return true;
			}
			return false;
		}

		bool CSysOpenPictureDialog::setMustExists(const bool value)
		{
			if (value != m_bMustExists)
			{
				m_bMustExists = value;
				return true;
			}
			return false;
		}

		bool CSysOpenPictureDialog::setShowHidden(const bool value)
		{
			if (value != m_bShowHidden)
			{
				m_bShowHidden = value;
				return true;
			}
			return false;
		}

		bool CSysOpenPictureDialog::setHideReadOnly(const bool value)
		{
			if (value != m_bHideReadOnly)
			{
				m_bHideReadOnly = value;
				return true;
			}
			return false;
		}

		bool CSysOpenPictureDialog::setNoNetwork(const bool value)
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
		bool CSysOpenPictureDialog::Execute()
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
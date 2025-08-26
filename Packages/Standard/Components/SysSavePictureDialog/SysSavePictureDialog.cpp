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
		CSysSavePictureDialog::CSysSavePictureDialog() :
			CComponent(L"SysSavePictureDialog"),
			m_iFilterIndex{ 1 },
			m_bCreatePrompt{ true },
			m_bMustExists{ true },
			m_bShowHidden{ true },
			m_bHideReadOnly{ false },
			m_bNoNetwork{ true },
			m_bOverwritePrompt{ true }
		{
			m_sFilter =
				L"Bitmap(*.bmp)|*.bmp\n"
				L"Graphics Interchange Format(*.gif)|*.gif\n"
				L"Joint Photographic Experts Group(*.jpg;*.jpeg)|*.jpg;*.jpeg\n"
				L"Portable Network Graphics(*.png)|*.png\n"
				L"Tag Image File Format(*.tiff)|*.tiff";
		}

		CSysSavePictureDialog::CSysSavePictureDialog(IForm *parent) :CSysSavePictureDialog()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		String CSysSavePictureDialog::getFilter()
		{
			return m_sFilter;
		}

		int CSysSavePictureDialog::getFilterIndex()
		{
			return m_iFilterIndex;
		}

		String CSysSavePictureDialog::getFileName()
		{
			return m_sFileName;
		}

		String CSysSavePictureDialog::getDefaultExtension()
		{
			return m_sDefaultExtension;
		}

		bool CSysSavePictureDialog::isCreatePrompt()
		{
			return m_bCreatePrompt;
		}

		bool CSysSavePictureDialog::isMustExists()
		{
			return m_bMustExists;
		}

		bool CSysSavePictureDialog::isShowHidden()
		{
			return m_bShowHidden;
		}

		bool CSysSavePictureDialog::isHideReadOnly()
		{
			return m_bHideReadOnly;
		}

		bool CSysSavePictureDialog::isNoNetwork()
		{
			return m_bNoNetwork;
		}

		bool CSysSavePictureDialog::isOverwritePrompt()
		{
			return m_bOverwritePrompt;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CSysSavePictureDialog::setFilter(const String &value)
		{
			if (value != m_sFilter)
			{
				m_sFilter = value;
				return true;
			}
			return false;
		}

		bool CSysSavePictureDialog::setFilterIndex(const int value)
		{
			if (value != m_iFilterIndex)
			{
				m_iFilterIndex = value;
				return true;
			}
			return false;
		}

		bool CSysSavePictureDialog::setFileName(const String &value)
		{
			if (value != m_sFileName)
			{
				m_sFileName = value;
				return true;
			}
			return false;
		}

		bool CSysSavePictureDialog::setDefaultExtension(const String &value)
		{
			if (value != m_sDefaultExtension)
			{
				m_sDefaultExtension = value;
				return true;
			}
			return false;
		}

		bool CSysSavePictureDialog::setCreatePrompt(const bool value)
		{
			if (value != m_bCreatePrompt)
			{
				m_bCreatePrompt = value;
				return true;
			}
			return false;
		}

		bool CSysSavePictureDialog::setMustExists(const bool value)
		{
			if (value != m_bMustExists)
			{
				m_bMustExists = value;
				return true;
			}
			return false;
		}

		bool CSysSavePictureDialog::setShowHidden(const bool value)
		{
			if (value != m_bShowHidden)
			{
				m_bShowHidden = value;
				return true;
			}
			return false;
		}

		bool CSysSavePictureDialog::setHideReadOnly(const bool value)
		{
			if (value != m_bHideReadOnly)
			{
				m_bHideReadOnly = value;
				return true;
			}
			return false;
		}

		bool CSysSavePictureDialog::setNoNetwork(const bool value)
		{
			if (value != m_bNoNetwork)
			{
				m_bNoNetwork = value;
				return true;
			}
			return false;
		}

		bool CSysSavePictureDialog::setOverwritePrompt(const bool value)
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
		bool CSysSavePictureDialog::Execute()
		{
			return Application->Dialogs->Save(m_sFilter, m_iFilterIndex, m_sFileName, m_sDefaultExtension, m_bCreatePrompt, m_bMustExists, m_bShowHidden, m_bHideReadOnly, m_bNoNetwork, m_bOverwritePrompt);
		}
	#pragma endregion
	}
}
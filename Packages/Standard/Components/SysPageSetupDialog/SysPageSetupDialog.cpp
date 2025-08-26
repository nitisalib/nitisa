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
		CSysPageSetupDialog::CSysPageSetupDialog() :
			CComponent(L"SysPageSetupDialog"),
			m_bDisableMargins{ false },
			m_bDisableOrientation{ false },
			m_bDisablePagePainting{ false },
			m_bDisablePaper{ false },
			m_bNoNetworkButton{ false },
			m_sMinMargins{ 0, 0, 0, 0 },
			m_sMargins{ 0, 0, 0, 0 },
			m_bLandscape{ false },
			m_ePaperSize{ IDialogs::PrintPaperSize::Unknown },
			m_fPaperLength{ 0 },
			m_fPaperWidth{ 0 },
			m_fScale{ 1 },
			m_iCopies{ 1 },
			m_ePaperSource{ IDialogs::PrintPaperSource::Unknown },
			m_ePrintQuality{ IDialogs::PrintQuality::Unknown },
			m_bMonochrome{ true },
			m_eDuplex{ IDialogs::PrintDuplex::Unknown },
			m_eTTOption{ IDialogs::PrintTTOption::Unknown },
			m_bCollate{ false },
			m_eMediaType{ IDialogs::PrintMediaType::Unknown },
			m_eDitherType{ IDialogs::PrintDitherType::Unknown },
			m_sSize{ 0, 0 }
		{

		}

		CSysPageSetupDialog::CSysPageSetupDialog(IForm *parent) :CSysPageSetupDialog()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Interface getters
		bool CSysPageSetupDialog::isDisableMargins()
		{
			return m_bDisableMargins;
		}

		bool CSysPageSetupDialog::isDisableOrientation()
		{
			return m_bDisableOrientation;
		}

		bool CSysPageSetupDialog::isDisablePagePainting()
		{
			return m_bDisablePagePainting;
		}

		bool CSysPageSetupDialog::isDisablePaper()
		{
			return m_bDisablePaper;
		}

		bool CSysPageSetupDialog::isNoNetworkButton()
		{
			return m_bNoNetworkButton;
		}

		RectF CSysPageSetupDialog::getMinMargins()
		{
			return m_sMinMargins;
		}

		String CSysPageSetupDialog::getDeviceName()
		{
			return m_sDeviceName;
		}

		RectF CSysPageSetupDialog::getMargins()
		{
			return m_sMargins;
		}

		bool CSysPageSetupDialog::isLandscape()
		{
			return m_bLandscape;
		}

		IDialogs::PrintPaperSize CSysPageSetupDialog::getPaperSize()
		{
			return m_ePaperSize;
		}

		float CSysPageSetupDialog::getPaperLength()
		{
			return m_fPaperLength;
		}

		float CSysPageSetupDialog::getPaperWidth()
		{
			return m_fPaperWidth;
		}

		float CSysPageSetupDialog::getScale()
		{
			return m_fScale;
		}

		int CSysPageSetupDialog::getCopies()
		{
			return m_iCopies;
		}

		IDialogs::PrintPaperSource CSysPageSetupDialog::getPaperSource()
		{
			return m_ePaperSource;
		}

		IDialogs::PrintQuality CSysPageSetupDialog::getPrintQuality()
		{
			return m_ePrintQuality;
		}

		bool CSysPageSetupDialog::isMonochrome()
		{
			return m_bMonochrome;
		}

		IDialogs::PrintDuplex CSysPageSetupDialog::getDuplex()
		{
			return m_eDuplex;
		}

		IDialogs::PrintTTOption CSysPageSetupDialog::getTTOption()
		{
			return m_eTTOption;
		}

		bool CSysPageSetupDialog::isCollate()
		{
			return m_bCollate;
		}

		IDialogs::PrintMediaType CSysPageSetupDialog::getMediaType()
		{
			return m_eMediaType;
		}

		IDialogs::PrintDitherType CSysPageSetupDialog::getDitherType()
		{
			return m_eDitherType;
		}

		PointF CSysPageSetupDialog::getSize()
		{
			return m_sSize;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CSysPageSetupDialog::setDisableMargins(const bool value)
		{
			if (value != m_bDisableMargins)
			{
				m_bDisableMargins = value;
				return true;
			}
			return false;
		}

		bool CSysPageSetupDialog::setDisableOrientation(const bool value)
		{
			if (value != m_bDisableOrientation)
			{
				m_bDisableOrientation = value;
				return true;
			}
			return false;
		}

		bool CSysPageSetupDialog::setDisablePagePainting(const bool value)
		{
			if (value != m_bDisablePagePainting)
			{
				m_bDisablePagePainting = value;
				return true;
			}
			return false;
		}

		bool CSysPageSetupDialog::setDisablePaper(const bool value)
		{
			if (value != m_bDisablePaper)
			{
				m_bDisablePaper = value;
				return true;
			}
			return false;
		}

		bool CSysPageSetupDialog::setNoNetworkButton(const bool value)
		{
			if (value != m_bNoNetworkButton)
			{
				m_bNoNetworkButton = value;
				return true;
			}
			return false;
		}

		bool CSysPageSetupDialog::setMinMargins(const RectF &value)
		{
			if (IsNotEqual(value, m_sMinMargins))
			{
				m_sMinMargins = value;
				return true;
			}
			return false;
		}

		bool CSysPageSetupDialog::setMargins(const RectF &value)
		{
			if (IsNotEqual(value, m_sMargins))
			{
				m_sMargins = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface helpers
		bool CSysPageSetupDialog::Execute()
		{
			return Application->Dialogs->PageSetup(m_bDisableMargins, m_bDisableOrientation, m_bDisablePagePainting, m_bDisablePaper, m_bNoNetworkButton, m_sMinMargins, m_sDeviceName, m_sMargins,
				m_bLandscape, m_ePaperSize, m_fPaperLength, m_fPaperWidth, m_fScale, m_iCopies, m_ePaperSource, m_ePrintQuality, m_bMonochrome, m_eDuplex, m_eTTOption, m_bCollate, m_eMediaType,
				m_eDitherType, m_sSize);
		}
	#pragma endregion
	}
}
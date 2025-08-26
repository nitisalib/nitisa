// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		CSysPrintDialog::CSysPrintDialog() :
			CComponent(L"SysPrintDialog"),
			m_bSelectCollate{ false },
			m_bSelectCurrentPage{ false },
			m_bDisablePrintToFile{ false },
			m_bHidePrintToFile{ false },
			m_bDisableCurrentPage{ false },
			m_bNoPageNums{ false },
			m_bNoSelection{ false },
			m_bSelectPageNums{ false },
			m_bSelectPrintToFile{ false },
			m_bSelectSelection{ false },
			m_iMinPage{ 1 },
			m_iMaxPage{ 1 },
			m_iMaxPageRangeCount{ 1 },
			m_iPageRangeCount{ 0 },
			m_aPageRanges{ nullptr },
			m_iCopies{ 1 },
			m_bLandscape{ false },
			m_ePaperSize{ IDialogs::PrintPaperSize::Unknown },
			m_fPaperLength{ 0 },
			m_fPaperWidth{ 0 },
			m_fScale{ 1 },
			m_ePaperSource{ IDialogs::PrintPaperSource::Unknown },
			m_ePrintQuality{ IDialogs::PrintQuality::Unknown },
			m_bMonochrome{ false },
			m_eDuplex{ IDialogs::PrintDuplex::Unknown },
			m_eTTOption{ IDialogs::PrintTTOption::Unknown },
			m_bCollate{ false },
			m_eMediaType{ IDialogs::PrintMediaType::Unknown },
			m_eDitherType{ IDialogs::PrintDitherType::Unknown }
		{

		}

		CSysPrintDialog::CSysPrintDialog(IForm *parent) :CSysPrintDialog()
		{
			setForm(parent);
		}

		void CSysPrintDialog::BeforeRelease()
		{
			if (m_aPageRanges)
			{
				delete[] m_aPageRanges;
				m_aPageRanges = nullptr;
			}
			CComponent::BeforeRelease();
		}
	#pragma endregion

	#pragma region Interface getters
		bool CSysPrintDialog::isSelectCollate()
		{
			return m_bSelectCollate;
		}

		bool CSysPrintDialog::isSelectCurrentPage()
		{
			return m_bSelectCurrentPage;
		}

		bool CSysPrintDialog::isDisablePrintToFile()
		{
			return m_bDisablePrintToFile;
		}

		bool CSysPrintDialog::isHidePrintToFile()
		{
			return m_bHidePrintToFile;
		}

		bool CSysPrintDialog::isDisableCurrentPage()
		{
			return m_bDisableCurrentPage;
		}

		bool CSysPrintDialog::isNoPageNums()
		{
			return m_bNoPageNums;
		}

		bool CSysPrintDialog::isNoSelection()
		{
			return m_bNoSelection;
		}

		bool CSysPrintDialog::isSelectPageNums()
		{
			return m_bSelectPageNums;
		}

		bool CSysPrintDialog::isSelectPrintToFile()
		{
			return m_bSelectPrintToFile;
		}

		bool CSysPrintDialog::isSelectSelection()
		{
			return m_bSelectSelection;
		}

		int CSysPrintDialog::getMinPage()
		{
			return m_iMinPage;
		}

		int CSysPrintDialog::getMaxPage()
		{
			return m_iMaxPage;
		}

		int CSysPrintDialog::getMaxPageRangeCount()
		{
			return m_iMaxPageRangeCount;
		}

		int CSysPrintDialog::getPageRangeCount()
		{
			return m_iPageRangeCount;
		}

		Point CSysPrintDialog::getPageRange(const int index)
		{
			if (index >= 0 && index < m_iPageRangeCount)
				return m_aPageRanges[index];
			return Point{ 0, 0 };
		}

		int CSysPrintDialog::getCopies()
		{
			return m_iCopies;
		}

		String CSysPrintDialog::getDeviceName()
		{
			return m_sDeviceName;
		}

		bool CSysPrintDialog::isLandscape()
		{
			return m_bLandscape;
		}

		IDialogs::PrintPaperSize CSysPrintDialog::getPaperSize()
		{
			return m_ePaperSize;
		}

		float CSysPrintDialog::getPaperLength()
		{
			return m_fPaperLength;
		}

		float CSysPrintDialog::getPaperWidth()
		{
			return m_fPaperWidth;
		}

		float CSysPrintDialog::getScale()
		{
			return m_fScale;
		}

		IDialogs::PrintPaperSource CSysPrintDialog::getPaperSource()
		{
			return m_ePaperSource;
		}

		IDialogs::PrintQuality CSysPrintDialog::getPrintQuality()
		{
			return m_ePrintQuality;
		}

		bool CSysPrintDialog::isMonochrome()
		{
			return m_bMonochrome;
		}

		IDialogs::PrintDuplex CSysPrintDialog::getDuplex()
		{
			return m_eDuplex;
		}

		IDialogs::PrintTTOption CSysPrintDialog::getTTOption()
		{
			return m_eTTOption;
		}

		bool CSysPrintDialog::isCollate()
		{
			return m_bCollate;
		}

		IDialogs::PrintMediaType CSysPrintDialog::getMediaType()
		{
			return m_eMediaType;
		}

		IDialogs::PrintDitherType CSysPrintDialog::getDitherType()
		{
			return m_eDitherType;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CSysPrintDialog::setSelectCollate(const bool value)
		{
			if (value != m_bSelectCollate)
			{
				m_bSelectCollate = value;
				return true;
			}
			return false;
		}

		bool CSysPrintDialog::setSelectCurrentPage(const bool value)
		{
			if (value != m_bSelectCurrentPage)
			{
				m_bSelectCurrentPage = value;
				return true;
			}
			return false;
		}

		bool CSysPrintDialog::setDisablePrintToFile(const bool value)
		{
			if (value != m_bDisablePrintToFile)
			{
				m_bDisablePrintToFile = value;
				return true;
			}
			return false;
		}

		bool CSysPrintDialog::setHidePrintToFile(const bool value)
		{
			if (value != m_bHidePrintToFile)
			{
				m_bHidePrintToFile = value;
				return true;
			}
			return false;
		}

		bool CSysPrintDialog::setDisableCurrentPage(const bool value)
		{
			if (value != m_bDisableCurrentPage)
			{
				m_bDisableCurrentPage = value;
				return true;
			}
			return false;
		}

		bool CSysPrintDialog::setNoPageNums(const bool value)
		{
			if (value != m_bNoPageNums)
			{
				m_bNoPageNums = value;
				return true;
			}
			return false;
		}

		bool CSysPrintDialog::setNoSelection(const bool value)
		{
			if (value != m_bNoSelection)
			{
				m_bNoSelection = value;
				return true;
			}
			return false;
		}

		bool CSysPrintDialog::setSelectPageNums(const bool value)
		{
			if (value != m_bSelectPageNums)
			{
				m_bSelectPageNums = value;
				return true;
			}
			return false;
		}

		bool CSysPrintDialog::setSelectPrintToFile(const bool value)
		{
			if (value != m_bSelectPrintToFile)
			{
				m_bSelectPrintToFile = value;
				return true;
			}
			return false;
		}

		bool CSysPrintDialog::setSelectSelection(const bool value)
		{
			if (value != m_bSelectSelection)
			{
				m_bSelectSelection = value;
				return true;
			}
			return false;
		}

		bool CSysPrintDialog::setMinPage(const int value)
		{
			if (value > 0 && value != m_iMinPage)
			{
				m_iMinPage = value;
				if (m_iMaxPage < m_iMinPage)
					m_iMaxPage = m_iMinPage;
				return true;
			}
			return false;
		}

		bool CSysPrintDialog::setMaxPage(const int value)
		{
			if (value > 0 && value != m_iMaxPage)
			{
				m_iMaxPage = value;
				if (m_iMinPage > m_iMaxPage)
					m_iMinPage = m_iMaxPage;
				return true;
			}
			return false;
		}

		bool CSysPrintDialog::setMaxPageRangeCount(const int value)
		{
			if (value >= 0 && value != m_iMaxPageRangeCount)
			{
				m_iMaxPageRangeCount = value;
				return true;
			}
			return false;
		}

		bool CSysPrintDialog::setPageRangeCount(const int value)
		{
			if (value >= 0 && value != m_iPageRangeCount)
			{
				m_iPageRangeCount = value;
				if (m_aPageRanges)
				{
					delete[] m_aPageRanges;
					m_aPageRanges = nullptr;
				}
				if (m_iPageRangeCount > 0)
					m_aPageRanges = new Point[m_iPageRangeCount];
				return true;
			}
			return false;
		}

		bool CSysPrintDialog::setPageRange(const int index, const Point &value)
		{
			if (index >= 0 && index < m_iPageRangeCount && value.X > 0 && value.Y > 0 && value.Y >= value.X && value != m_aPageRanges[index])
			{
				m_aPageRanges[index] = value;
				return true;
			}
			return false;
		}

		bool CSysPrintDialog::setCopies(const int value)
		{
			if (value > 0 && value != m_iCopies)
			{
				m_iCopies = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface helpers
		IDialogs::PrintDialogResult CSysPrintDialog::Execute(void **handle)
		{
			Point *ranges{ nullptr };
			if (m_iMaxPageRangeCount > 0)
			{
				ranges = new Point[m_iMaxPageRangeCount];
				for (int i = 0; i < m_iPageRangeCount; i++)
					ranges[i] = m_aPageRanges[i];
			}
			IDialogs::PrintDialogResult result{ Application->Dialogs->Print(m_bSelectCollate, m_bSelectCurrentPage, m_bDisablePrintToFile, m_bHidePrintToFile, m_bDisableCurrentPage, m_bNoPageNums, m_bNoSelection,
				m_bSelectPageNums, m_bSelectPrintToFile, m_bSelectSelection, m_iMinPage, m_iMaxPage, m_iMaxPageRangeCount, m_iPageRangeCount, ranges, m_iCopies, m_sDeviceName, m_bLandscape,
				m_ePaperSize, m_fPaperLength, m_fPaperWidth, m_fScale, m_ePaperSource, m_ePrintQuality, m_bMonochrome, m_eDuplex, m_eTTOption, m_bCollate, m_eMediaType, m_eDitherType, handle) };
			if (result != IDialogs::PrintDialogResult::Error)
			{
				if (m_aPageRanges)
				{
					delete[] m_aPageRanges;
					m_aPageRanges = nullptr;
				}
				if (m_iPageRangeCount > 0)
				{
					m_aPageRanges = new Point[m_iPageRangeCount];
					for (int i = 0; i < m_iPageRangeCount; i++)
						m_aPageRanges[i] = ranges[i];
				}
			}
			if (ranges)
				delete[] ranges;
			return result;
		}
	#pragma endregion
	}
}
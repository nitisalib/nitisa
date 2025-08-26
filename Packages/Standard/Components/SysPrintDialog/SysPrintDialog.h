// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Component.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IDialogs.h"
#include "Nitisa/Math/Point.h"
#include "../ISysPrintDialog.h"

namespace nitisa
{
	class IForm;

	namespace standard
	{
		class CSysPrintDialog :public virtual ISysPrintDialog, public CComponent
		{
		private:
			bool m_bSelectCollate;
			bool m_bSelectCurrentPage;
			bool m_bDisablePrintToFile;
			bool m_bHidePrintToFile;
			bool m_bDisableCurrentPage;
			bool m_bNoPageNums;
			bool m_bNoSelection;
			bool m_bSelectPageNums;
			bool m_bSelectPrintToFile;
			bool m_bSelectSelection;
			int m_iMinPage;
			int m_iMaxPage;
			int m_iMaxPageRangeCount;
			int m_iPageRangeCount;
			Point *m_aPageRanges;
			int m_iCopies;
			String m_sDeviceName;
			bool m_bLandscape;
			IDialogs::PrintPaperSize m_ePaperSize;
			float m_fPaperLength;
			float m_fPaperWidth;
			float m_fScale;
			IDialogs::PrintPaperSource m_ePaperSource;
			IDialogs::PrintQuality m_ePrintQuality;
			bool m_bMonochrome;
			IDialogs::PrintDuplex m_eDuplex;
			IDialogs::PrintTTOption m_eTTOption;
			bool m_bCollate;
			IDialogs::PrintMediaType m_eMediaType;
			IDialogs::PrintDitherType m_eDitherType;
		protected:
			void BeforeRelease() override;
		public:
			bool isSelectCollate() override;
			bool isSelectCurrentPage() override;
			bool isDisablePrintToFile() override;
			bool isHidePrintToFile() override;
			bool isDisableCurrentPage() override;
			bool isNoPageNums() override;
			bool isNoSelection() override;
			bool isSelectPageNums() override;
			bool isSelectPrintToFile() override;
			bool isSelectSelection() override;
			int getMinPage() override;
			int getMaxPage() override;
			int getMaxPageRangeCount() override;
			int getPageRangeCount() override;
			Point getPageRange(const int index) override;
			int getCopies() override;
			String getDeviceName() override;
			bool isLandscape() override;
			IDialogs::PrintPaperSize getPaperSize() override;
			float getPaperLength() override;
			float getPaperWidth() override;
			float getScale() override;
			IDialogs::PrintPaperSource getPaperSource() override;
			IDialogs::PrintQuality getPrintQuality() override;
			bool isMonochrome() override;
			IDialogs::PrintDuplex getDuplex() override;
			IDialogs::PrintTTOption getTTOption() override;
			bool isCollate() override;
			IDialogs::PrintMediaType getMediaType() override;
			IDialogs::PrintDitherType getDitherType() override;

			bool setSelectCollate(const bool value) override;
			bool setSelectCurrentPage(const bool value) override;
			bool setDisablePrintToFile(const bool value) override;
			bool setHidePrintToFile(const bool value) override;
			bool setDisableCurrentPage(const bool value) override;
			bool setNoPageNums(const bool value) override;
			bool setNoSelection(const bool value) override;
			bool setSelectPageNums(const bool value) override;
			bool setSelectPrintToFile(const bool value) override;
			bool setSelectSelection(const bool value) override;
			bool setMinPage(const int value) override;
			bool setMaxPage(const int value) override;
			bool setMaxPageRangeCount(const int value) override;
			bool setPageRangeCount(const int value) override;
			bool setPageRange(const int index, const Point &value) override;
			bool setCopies(const int value) override;

			IDialogs::PrintDialogResult Execute(void **handle) override;

			CSysPrintDialog();
			CSysPrintDialog(IForm *parent);
		};
	}
}
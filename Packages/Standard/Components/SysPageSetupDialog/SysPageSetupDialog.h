// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Component.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IDialogs.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../ISysPageSetupDialog.h"

namespace nitisa
{
	class IForm;

	namespace standard
	{
		class CSysPageSetupDialog :public virtual ISysPageSetupDialog, public CComponent
		{
		private:
			bool m_bDisableMargins;
			bool m_bDisableOrientation;
			bool m_bDisablePagePainting;
			bool m_bDisablePaper;
			bool m_bNoNetworkButton;
			RectF m_sMinMargins;
			String m_sDeviceName;
			RectF m_sMargins;
			bool m_bLandscape;
			IDialogs::PrintPaperSize m_ePaperSize;
			float m_fPaperLength;
			float m_fPaperWidth;
			float m_fScale;
			int m_iCopies;
			IDialogs::PrintPaperSource m_ePaperSource;
			IDialogs::PrintQuality m_ePrintQuality;
			bool m_bMonochrome;
			IDialogs::PrintDuplex m_eDuplex;
			IDialogs::PrintTTOption m_eTTOption;
			bool m_bCollate;
			IDialogs::PrintMediaType m_eMediaType;
			IDialogs::PrintDitherType m_eDitherType;
			PointF m_sSize;
		public:
			bool isDisableMargins() override;
			bool isDisableOrientation() override;
			bool isDisablePagePainting() override;
			bool isDisablePaper() override;
			bool isNoNetworkButton() override;
			RectF getMinMargins() override;
			String getDeviceName() override;
			RectF getMargins() override;
			bool isLandscape() override;
			IDialogs::PrintPaperSize getPaperSize() override;
			float getPaperLength() override;
			float getPaperWidth() override;
			float getScale() override;
			int getCopies() override;
			IDialogs::PrintPaperSource getPaperSource() override;
			IDialogs::PrintQuality getPrintQuality() override;
			bool isMonochrome() override;
			IDialogs::PrintDuplex getDuplex() override;
			IDialogs::PrintTTOption getTTOption() override;
			bool isCollate() override;
			IDialogs::PrintMediaType getMediaType() override;
			IDialogs::PrintDitherType getDitherType() override;
			PointF getSize() override;

			bool setDisableMargins(const bool value) override;
			bool setDisableOrientation(const bool value) override;
			bool setDisablePagePainting(const bool value) override;
			bool setDisablePaper(const bool value) override;
			bool setNoNetworkButton(const bool value) override;
			bool setMinMargins(const RectF &value) override;
			bool setMargins(const RectF &value) override;

			bool Execute() override;

			CSysPageSetupDialog();
			CSysPageSetupDialog(IForm *parent);
		};
	}
}
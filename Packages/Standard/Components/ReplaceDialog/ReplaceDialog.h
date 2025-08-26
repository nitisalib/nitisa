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
#include "Nitisa/Interfaces/IDialogBoxListener.h"
#include "../IReplaceDialog.h"
#include "../IColorDialog.h"

namespace nitisa
{
	class IDialogBox;
	class IForm;

	namespace standard
	{
		class CFormReplace;
		class CReplaceDialogService;
		class CDialogBoxReplace;

		class CReplaceDialog :public virtual IReplaceDialog, public CComponent
		{
			friend CReplaceDialogService;
		private:
			class CDialogBoxListener :public virtual IDialogBoxListener
			{
			private:
				CReplaceDialog *m_pComponent;
			public:
				void OnClose(IDialogBox *sender) override;
				void OnRestore(IDialogBox *sender) override;
				void OnMinimize(IDialogBox *sender) override;
				void OnMaximize(IDialogBox *sender) override;

				CDialogBoxListener(CReplaceDialog *component);
			};
		private:
			String m_sText;
			String m_sReplace;
			bool m_bMatchWholeWords;
			bool m_bMatchCase;
			IFormReplace::SearchDirection m_eSearchDirection;
			bool m_bUseDialogBox;
			CDialogBoxReplace *m_pDialogBoxReplace;
			CDialogBoxListener m_cDialogBoxListener;

			CFormReplace *m_pFormReplace;
			bool m_bShown;

			CFormReplace * getFormReplace();
		public:
			String getText() override;
			String getReplace() override;
			bool isMatchWholeWords() override;
			bool isMatchCase() override;
			IFormReplace::SearchDirection getSearchDirection() override;
			bool isUseDialogBox() override;

			bool setText(const String &value) override;
			bool setReplace(const String &value) override;
			bool setMatchWholeWords(const bool value) override;
			bool setMatchCase(const bool value) override;
			bool setSearchDirection(const IFormReplace::SearchDirection value) override;
			bool setUseDialogBox(const bool value) override;

			bool Execute() override;

			CReplaceDialog();
			CReplaceDialog(IForm *parent);
		};
	}
}
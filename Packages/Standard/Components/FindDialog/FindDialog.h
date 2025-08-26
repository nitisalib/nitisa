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
#include "Nitisa/Interfaces/IDialogBoxListener.h"
#include "../IFindDialog.h"
#include "../IColorDialog.h"

namespace nitisa
{
	class IDialogBox;

	namespace standard
	{
		class CFormFind;
		class CFindDialogService;
		class CDialogBoxFind;

		class CFindDialog :public virtual IFindDialog, public CComponent
		{
			friend CFindDialogService;
		private:
			class CDialogBoxListener :public virtual IDialogBoxListener
			{
			private:
				CFindDialog *m_pComponent;
			public:
				void OnClose(IDialogBox *sender) override;
				void OnRestore(IDialogBox *sender) override;
				void OnMinimize(IDialogBox *sender) override;
				void OnMaximize(IDialogBox *sender) override;

				CDialogBoxListener(CFindDialog *component);
			};
		private:
			String m_sText;
			bool m_bMatchWholeWords;
			bool m_bMatchCase;
			IFormFind::SearchDirection m_eSearchDirection;
			bool m_bUseDialogBox;
			CDialogBoxFind *m_pDialogBoxFind;
			CDialogBoxListener m_cDialogBoxListener;

			CFormFind *m_pFormFind;
			bool m_bShown;

			CFormFind *getFormFind();
		public:
			String getText() override;
			bool isMatchWholeWords() override;
			bool isMatchCase() override;
			IFormFind::SearchDirection getSearchDirection() override;
			bool isUseDialogBox() override;

			bool setText(const String &value) override;
			bool setMatchWholeWords(const bool value) override;
			bool setMatchCase(const bool value) override;
			bool setSearchDirection(const IFormFind::SearchDirection value) override;
			bool setUseDialogBox(const bool value) override;

			bool Execute() override;

			CFindDialog();
			CFindDialog(IForm *parent);
		};
	}
}
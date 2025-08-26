// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Messages.h"
#include "Nitisa/Core/Strings.h"
#include "../IFormReplace.h"
#include "IDialogBoxReplaceProto.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CDialogBoxReplace :public virtual IFormReplace, public IDialogBoxReplaceProto
		{
		private:
			class CDialogBoxReplaceService :public IDialogBoxReplaceProtoService
			{
			private:
				CDialogBoxReplace * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxReplaceService(CDialogBoxReplace *control);
			};
		private:
			void LoadTranslatableTexts();
		protected:
			void FormReplaceProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void EditText_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void EditText_OnChange(IControl *sender) override;
			void EditReplace_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void ButtonReplace_OnClick(IControl *sender) override;
			void ButtonReplaceAll_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			String getText() override;
			String getReplace() override;
			bool isMatchWholeWords() override;
			bool isMatchCase() override;
			SearchDirection getSearchDirection() override;

			bool setText(const String &value) override;
			bool setReplace(const String &value) override;
			bool setMatchWholeWords(const bool value) override;
			bool setMatchCase(const bool value) override;
			bool setSearchDirection(const SearchDirection value) override;

			void ActivateFirstEnabledInput() override;

			CDialogBoxReplace();
			CDialogBoxReplace(IForm *parent);
			CDialogBoxReplace(IControl *parent);
		};
	}
}
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
#include "../IFormMemo.h"
#include "IDialogBoxMemoProto.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CDialogBoxMemo :public virtual IFormMemo, public IDialogBoxMemoProto
		{
		private:
			class CDialogBoxMemoService :public IDialogBoxMemoProtoService
			{
			private:
				CDialogBoxMemo * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxMemoService(CDialogBoxMemo *control);
			};
		private:
			void LoadTranslatableTexts();
		protected:
			void FormMemoProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			String getValue() override;

			bool setValue(const String &value) override;

			void ActivateFirstEnabledInput() override;

			CDialogBoxMemo();
			CDialogBoxMemo(IForm *parent);
			CDialogBoxMemo(IControl *parent);
		};
	}
}
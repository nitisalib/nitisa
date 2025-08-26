// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/FormService.h"
#include "Nitisa/Core/Messages.h"
#include "Nitisa/Core/Strings.h"
#include "../IFormMemo.h"
#include "IFormMemoProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormMemo :public virtual IFormMemo, public IFormMemoProto
		{
		private:
			class CFormMemoService :public CFormService
			{
			private:
				CFormMemo * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormMemoService(CFormMemo *form);
			};
		private:
			void LoadTranslatableTexts();
		protected:
			void FormMemoProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			String getValue() override;

			bool setValue(const String &value) override;

			void ActivateFirstEnabledInput() override;

			CFormMemo(IWindow *window, IRenderer *renderer);
		};
	}
}
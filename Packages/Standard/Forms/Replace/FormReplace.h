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
#include "../IFormReplace.h"
#include "IFormReplaceProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormReplace :public virtual IFormReplace, public IFormReplaceProto
		{
		private:
			class CFormReplaceService :public CFormService
			{
			private:
				CFormReplace * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormReplaceService(CFormReplace *form);
			};
		private:
			static CFormReplace *m_pInstance;

			void LoadTranslatableTexts();
		protected:
			void FormReplaceProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
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

			CFormReplace(IWindow *window, IRenderer *renderer);
			~CFormReplace() override;

			static CFormReplace *getInstance(); // Return form instance if any was created
		};
	}
}
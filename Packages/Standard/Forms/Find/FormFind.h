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
#include "../IFormFind.h"
#include "IFormFindProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormFind :public virtual IFormFind, public IFormFindProto
		{
		private:
			class CFormFindService :public CFormService
			{
			private:
				CFormFind * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormFindService(CFormFind *form);
			};
		private:
			static CFormFind *m_pInstance;

			void LoadTranslatableTexts();
		protected:
			void FormFindProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
			void EditText_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void EditText_OnChange(IControl *sender) override;
			void ButtonSearch_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			String getText() override;
			bool isMatchWholeWords() override;
			bool isMatchCase() override;
			SearchDirection getSearchDirection() override;

			bool setText(const String &value) override;
			bool setMatchWholeWords(const bool value) override;
			bool setMatchCase(const bool value) override;
			bool setSearchDirection(const SearchDirection value) override;

			void ActivateFirstEnabledInput() override;

			CFormFind(IWindow *window, IRenderer *renderer);
			~CFormFind() override;

			static CFormFind *getInstance(); // Return form instance if any was created
		};
	}
}
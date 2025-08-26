// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Hotkey.h"
#include "Nitisa/Core/FormService.h"
#include "Nitisa/Core/Strings.h"
#include "../IFormHotkeyList.h"
#include "IFormHotkeyListProto.h"

namespace nitisa
{
	class IControl;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormHotkeyList :public virtual IFormHotkeyList, public IFormHotkeyListProto
		{
		private:
			class CFormHotkeyListService :public CFormService
			{
			private:
				CFormHotkeyList * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormHotkeyListService(CFormHotkeyList *form);
			};
		private:
			std::vector<Hotkey> m_aHotkeys;

			void LoadTranslatableTexts();
		protected:
			void ButtonAdd_OnClick(IControl *sender) override;
			void ButtonDelete_OnClick(IControl *sender) override;
			void ButtonClear_OnClick(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			int getHotkeyCount() override;
			Hotkey getHotkey(const int index) override;

			bool AddHotkey(const Hotkey &value) override;
			bool DeleteHotkey(const int index) override;
			bool DeleteHotkeys() override;

			void ActivateFirstEnabledInput() override;

			CFormHotkeyList(IWindow *window, IRenderer *renderer);
		};
	}
}
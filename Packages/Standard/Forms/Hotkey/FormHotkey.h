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
#include "../IFormHotkey.h"
#include "IFormHotkeyProto.h"

namespace nitisa
{
	class IControl;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormHotkey :public virtual IFormHotkey, public IFormHotkeyProto
		{
		private:
			class CFormHotkeyService :public CFormService
			{
			private:
				CFormHotkey * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormHotkeyService(CFormHotkey *form);
			};
		private:
			void LoadTranslatableTexts();
		protected:
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
			void ButtonEmpty_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			Hotkey getValue() override;

			bool setValue(const Hotkey &value) override;

			void ActivateFirstEnabledInput() override;

			CFormHotkey(IWindow *window, IRenderer *renderer);
		};
	}
}
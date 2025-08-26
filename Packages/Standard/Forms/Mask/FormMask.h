// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/FormService.h"
#include "Nitisa/Core/Messages.h"
#include "Nitisa/Core/Strings.h"
#include "../IFormMask.h"
#include "IFormMaskProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CCheckBox;
		
		class CFormMask :public virtual IFormMask, public IFormMaskProto
		{
		private:
			class CFormMaskService :public CFormService
			{
			private:
				CFormMask * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormMaskService(CFormMask *form);
			};
		private:
			CCheckBox *m_aBits[32];
			unsigned int m_iValue;

			static void CheckBox_OnChange(IControl *sender);

			void InitControls();
			void InitEvents();
			void LoadTranslatableTexts();
			void ValueToControls();
			void ControlsToValue();
		protected:
			void FormMaskProto_OnPaint(IForm *sender, const MessagePaint &m, bool &draw_children) override;
			void FormMaskProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			unsigned int getValue() override;

			bool setValue(const unsigned int value) override;

			CFormMask(IWindow *window, IRenderer *renderer);
		};
	}
}
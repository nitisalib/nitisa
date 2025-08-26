// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Messages.h"
#include "Nitisa/Core/Strings.h"
#include "../IFormMask.h"
#include "IDialogBoxMaskProto.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CCheckBox;

		class CDialogBoxMask :public virtual IFormMask, public IDialogBoxMaskProto
		{
		private:
			class CDialogBoxMaskService :public IDialogBoxMaskProtoService
			{
			private:
				CDialogBoxMask * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxMaskService(CDialogBoxMask *control);
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
			void FormMaskProto_OnPaint(IControl *sender, const MessagePaint &m, bool &draw_children) override;
			void FormMaskProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			unsigned int getValue() override;

			bool setValue(const unsigned int value) override;

			CDialogBoxMask();
			CDialogBoxMask(IForm *parent);
			CDialogBoxMask(IControl *parent);
		};
	}
}
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
#include "Nitisa/Image/Color.h"
#include "../IFormColor.h"
#include "IDialogBoxColorProto.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CDialogBoxColor :public virtual IFormColor, public IDialogBoxColorProto
		{
		private:
			class CDialogBoxColorService :public IDialogBoxColorProtoService
			{
			private:
				CDialogBoxColor * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxColorService(CDialogBoxColor *control);
			};
		private:
			Color m_sColor;

			void LoadTranslatableTexts();
			void UpdateEdits();
		protected:
			void FormColorProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void HSVPlane_OnChange(IControl *sender) override;
			void HSVBar_OnChange(IControl *sender) override;
			void AlphaBar_OnChange(IControl *sender) override;
			void EditHue_OnKillFocus(IControl *sender) override;
			void EditHue_OnChange(IControl *sender) override;
			void EditSaturation_OnKillFocus(IControl *sender) override;
			void EditSaturation_OnChange(IControl *sender) override;
			void EditValue_OnKillFocus(IControl *sender) override;
			void EditValue_OnChange(IControl *sender) override;
			void EditR_OnKillFocus(IControl *sender) override;
			void EditR_OnChange(IControl *sender) override;
			void EditG_OnKillFocus(IControl *sender) override;
			void EditG_OnChange(IControl *sender) override;
			void EditB_OnKillFocus(IControl *sender) override;
			void EditB_OnChange(IControl *sender) override;
			void EditA_OnKillFocus(IControl *sender) override;
			void EditA_OnChange(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			Color getValue() override;

			bool setValue(const Color &value) override;

			void ActivateFirstEnabledInput() override;

			CDialogBoxColor();
			CDialogBoxColor(IForm *parent);
			CDialogBoxColor(IControl *parent);
		};
	}
}
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
#include "Nitisa/Image/Color.h"
#include "../IFormColor.h"
#include "IFormColorProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormColor :public virtual IFormColor, public IFormColorProto
		{
		private:
			class CFormColorService :public CFormService
			{
			private:
				CFormColor * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormColorService(CFormColor *form);
			};
		private:
			Color m_sColor;
			static CFormColor *m_pInstance;

			void LoadTranslatableTexts();
			void UpdateEdits();
		protected:
			void FormColorProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
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

			CFormColor(IWindow *window, IRenderer *renderer);
			~CFormColor() override;

			static CFormColor *getInstance(); // Return form instance if any was created
		};
	}
}
// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Messages.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "../IFormBorderColor.h"
#include "IDialogBoxBorderColorProto.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CDialogBoxBorderColor :public virtual IFormBorderColor, public IDialogBoxBorderColorProto
		{
		private:
			class CDialogBoxBorderColorService :public IDialogBoxBorderColorProtoService
			{
			private:
				CDialogBoxBorderColor * m_pControl;
			public:
				// Notifications
				void NotifyOnFreeResources() override;
				void NotifyOnTranslateChange() override;

				CDialogBoxBorderColorService(CDialogBoxBorderColor *control);
			};
		private:
			BorderColor m_sValue;
			Color *m_pColor;
			bool m_bColorDialogAdjusted;

			ITexture *m_pCanvas;

			void LoadTranslatableTexts();
			void SelectColor(Color *color);
		protected:
			void DialogBoxBorderColorProto_OnPaint(IControl *sender, const MessagePaint &m, bool &draw_children) override;
			void DialogBoxBorderColorProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void ColorDialog1_OnApply(IComponent *sender) override;
			void ButtonLeft_OnClick(IControl *sender) override;
			void ButtonTop_OnClick(IControl *sender) override;
			void ButtonRight_OnClick(IControl *sender) override;
			void ButtonBottom_OnClick(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			bool hasComponent(IComponent *component) override;
			BorderColor getValue() override;

			bool setBackgroundColor(const Color &value) override;
			bool setValue(const BorderColor &value) override;

			void ActivateFirstEnabledInput() override;

			CDialogBoxBorderColor();
			CDialogBoxBorderColor(IForm *parent);
			CDialogBoxBorderColor(IControl *parent);
		};
	}
}
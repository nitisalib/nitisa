// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/FormService.h"
#include "Nitisa/Core/Messages.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BorderColor.h"
#include "../IFormBorderColor.h"
#include "IFormBorderColorProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormBorderColor :public virtual IFormBorderColor, public IFormBorderColorProto
		{
		private:
			class CFormBorderColorService :public CFormService
			{
			private:
				CFormBorderColor * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormBorderColorService(CFormBorderColor *form);
			};
		private:
			BorderColor m_sValue;

			void LoadTranslatableTexts();
			void SelectColor(Color &color);
		protected:
			void FormBorderColorProto_OnPaint(IForm *sender, const MessagePaint &m, bool &draw_children) override;
			void FormBorderColorProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
			void ButtonLeft_OnClick(IControl *sender) override;
			void ButtonTop_OnClick(IControl *sender) override;
			void ButtonRight_OnClick(IControl *sender) override;
			void ButtonBottom_OnClick(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			BorderColor getValue() override;

			bool setValue(const BorderColor &value) override;

			void ActivateFirstEnabledInput() override;

			CFormBorderColor(IWindow *window, IRenderer *renderer);
		};
	}
}
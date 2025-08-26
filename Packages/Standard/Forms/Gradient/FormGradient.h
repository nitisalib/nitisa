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
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Image/Image.h"
#include "../IFormGradient.h"
#include "IFormGradientProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormGradient :public virtual IFormGradient, public IFormGradientProto
		{
		private:
			class CFormGradientService :public CFormService
			{
			private:
				CFormGradient * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormGradientService(CFormGradient *form);
			};
		private:
			Image m_cImgMouse;

			void LoadTranslatableTexts();
		protected:
			void FormGradientProto_OnPaint(IForm *sender, const MessagePaint &m, bool &draw_children) override;
			void FormGradientProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
			void GradientEditor_OnChange(IControl *sender) override;
			void Panel_OnLeftMouseButtonUp(IControl *sender, const MessageMouse &m, bool &processed) override;
			void EditPosition_OnKillFocus(IControl *sender) override;
			void EditPosition_OnChange(IControl *sender) override;
			void ButtonPrev_OnClick(IControl *sender) override;
			void ButtonNext_OnClick(IControl *sender) override;
			void DropDownType_OnSelect(IControl *sender, const int index) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			Gradient *getValue() override;

			bool setValue(Gradient &value) override;

			CFormGradient(IWindow *window, IRenderer *renderer);
		};
	}
}
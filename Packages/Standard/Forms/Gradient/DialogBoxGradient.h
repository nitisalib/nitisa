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
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Image/Image.h"
#include "../IFormGradient.h"
#include "IDialogBoxGradientProto.h"

namespace nitisa
{
	class IComponent;
	class IControl;
	class IForm;

	namespace standard
	{
		class CDialogBoxGradient :public virtual IFormGradient, public IDialogBoxGradientProto
		{
		private:
			class CDialogBoxGradientService :public IDialogBoxGradientProtoService
			{
			private:
				CDialogBoxGradient * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxGradientService(CDialogBoxGradient *control);
			};
		private:
			Image m_cImgMouse;
			bool m_bColorDialogAdjusted;
			Mat4f m_sTranslate;

			void LoadTranslatableTexts();
		protected:
			void FormGradientProto_OnPaint(IControl *sender, const MessagePaint &m, bool &draw_children) override;
			void FormGradientProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void ColorDialog1_OnApply(IComponent *sender) override;
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

			bool hasComponent(IComponent *component) override;
			Gradient *getValue() override;

			bool setBackgroundColor(const Color &value) override;
			bool setValue(Gradient &value) override;

			CDialogBoxGradient();
			CDialogBoxGradient(IForm *parent);
			CDialogBoxGradient(IControl *parent);
		};
	}
}
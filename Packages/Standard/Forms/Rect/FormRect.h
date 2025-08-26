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
#include "Nitisa/Math/Rect.h"
#include "../IFormRect.h"
#include "IFormRectProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormRect :public virtual IFormRect, public IFormRectProto
		{
		private:
			class CFormRectService :public CFormService
			{
			private:
				CFormRect * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormRectService(CFormRect *form);
			};
		private:
			Rect m_sValue;
			bool m_bHasMin;
			bool m_bHasMax;
			int m_iMin;
			int m_iMax;

			void LoadTranslatableTexts();
		protected:
			void FormRectProto_OnPaint(IForm *sender, const MessagePaint &m, bool &draw_children) override;
			void FormRectProto_OnKeyDown(IForm *sender, const MessageKey &m) override;
			void EditLeft_OnKillFocus(IControl *sender) override;
			void EditTop_OnKillFocus(IControl *sender) override;
			void EditRight_OnKillFocus(IControl *sender) override;
			void EditBottom_OnKillFocus(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			Rect getValue() override;
			bool hasMin() override;
			bool hasMax() override;
			int getMin() override;
			int getMax() override;

			bool setValue(const Rect &value) override;
			bool setHasMin(const bool value) override;
			bool setHasMax(const bool value) override;
			bool setMin(const int value) override;
			bool setMax(const int value) override;

			void ActivateFirstEnabledInput() override;

			CFormRect(IWindow *window, IRenderer *renderer);
		};
	}
}
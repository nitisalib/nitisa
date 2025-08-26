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
#include "Nitisa/Math/RectL.h"
#include "../IFormRectL.h"
#include "IFormRectLProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormRectL :public virtual IFormRectL, public IFormRectLProto
		{
		private:
			class CFormRectLService :public CFormService
			{
			private:
				CFormRectL * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormRectLService(CFormRectL *form);
			};
		private:
			RectL m_sValue;
			bool m_bHasMin;
			bool m_bHasMax;
			long long m_iMin;
			long long m_iMax;

			void LoadTranslatableTexts();
		protected:
			void FormRectLProto_OnPaint(IForm *sender, const MessagePaint &m, bool &draw_children) override;
			void FormRectLProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
			void EditLeft_OnKillFocus(IControl *sender) override;
			void EditTop_OnKillFocus(IControl *sender) override;
			void EditRight_OnKillFocus(IControl *sender) override;
			void EditBottom_OnKillFocus(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			RectL getValue() override;
			bool hasMin() override;
			bool hasMax() override;
			long long getMin() override;
			long long getMax() override;

			bool setValue(const RectL &value) override;
			bool setHasMin(const bool value) override;
			bool setHasMax(const bool value) override;
			bool setMin(const long long value) override;
			bool setMax(const long long value) override;

			void ActivateFirstEnabledInput() override;

			CFormRectL(IWindow *window, IRenderer *renderer);
		};
	}
}
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
#include "Nitisa/Math/RectF.h"
#include "../IFormRectF.h"
#include "IFormRectFProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormRectF :public virtual IFormRectF, public IFormRectFProto
		{
		private:
			class CFormRectFService :public CFormService
			{
			private:
				CFormRectF * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormRectFService(CFormRectF *form);
			};
		private:
			RectF m_sValue;
			bool m_bHasMin;
			bool m_bHasMax;
			float m_fMin;
			float m_fMax;

			void LoadTranslatableTexts();
		protected:
			void FormRectFProto_OnPaint(IForm *sender, const MessagePaint &m, bool &draw_children) override;
			void FormRectFProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
			void EditLeft_OnKillFocus(IControl *sender) override;
			void EditTop_OnKillFocus(IControl *sender) override;
			void EditRight_OnKillFocus(IControl *sender) override;
			void EditBottom_OnKillFocus(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			RectF getValue() override;
			bool hasMin() override;
			bool hasMax() override;
			float getMin() override;
			float getMax() override;

			bool setValue(const RectF &value) override;
			bool setHasMin(const bool value) override;
			bool setHasMax(const bool value) override;
			bool setMin(const float value) override;
			bool setMax(const float value) override;
			
			void ActivateFirstEnabledInput() override;

			CFormRectF(IWindow *window, IRenderer *renderer);
		};
	}
}
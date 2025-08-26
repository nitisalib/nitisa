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
#include "Nitisa/Math/RectF.h"
#include "../IFormRectF.h"
#include "IDialogBoxRectFProto.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CDialogBoxRectF :public virtual IFormRectF, public IDialogBoxRectFProto
		{
		private:
			class CDialogBoxRectFService :public IDialogBoxRectFProtoService
			{
			private:
				CDialogBoxRectF * m_pControl;
			public:
				// Notifications
				void NotifyOnFreeResources() override;
				void NotifyOnTranslateChange() override;

				CDialogBoxRectFService(CDialogBoxRectF *control);
			};
		private:
			RectF m_sValue;
			bool m_bHasMin;
			bool m_bHasMax;
			float m_fMin;
			float m_fMax;

			ITexture *m_pCanvas;

			void LoadTranslatableTexts();
		protected:
			void FormRectFProto_OnPaint(IControl *sender, const MessagePaint &m, bool &draw_children) override;
			void FormRectFProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
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

			CDialogBoxRectF();
			CDialogBoxRectF(IForm *parent);
			CDialogBoxRectF(IControl *parent);
		};
	}
}
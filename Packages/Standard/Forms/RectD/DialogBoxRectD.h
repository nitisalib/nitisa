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
#include "Nitisa/Math/RectD.h"
#include "../IFormRectD.h"
#include "IDialogBoxRectDProto.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CDialogBoxRectD :public virtual IFormRectD, public IDialogBoxRectDProto
		{
		private:
			class CDialogBoxRectDService :public IDialogBoxRectDProtoService
			{
			private:
				CDialogBoxRectD * m_pControl;
			public:
				// Notifications
				void NotifyOnFreeResources() override;
				void NotifyOnTranslateChange() override;

				CDialogBoxRectDService(CDialogBoxRectD *control);
			};
		private:
			RectD m_sValue;
			bool m_bHasMin;
			bool m_bHasMax;
			double m_fMin;
			double m_fMax;

			ITexture *m_pCanvas;

			void LoadTranslatableTexts();
		protected:
			void FormRectDProto_OnPaint(IControl *sender, const MessagePaint &m, bool &draw_children) override;
			void FormRectDProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void EditLeft_OnKillFocus(IControl *sender) override;
			void EditTop_OnKillFocus(IControl *sender) override;
			void EditRight_OnKillFocus(IControl *sender) override;
			void EditBottom_OnKillFocus(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			RectD getValue() override;
			bool hasMin() override;
			bool hasMax() override;
			double getMin() override;
			double getMax() override;

			bool setValue(const RectD &value) override;
			bool setHasMin(const bool value) override;
			bool setHasMax(const bool value) override;
			bool setMin(const double value) override;
			bool setMax(const double value) override;

			void ActivateFirstEnabledInput() override;

			CDialogBoxRectD();
			CDialogBoxRectD(IForm *parent);
			CDialogBoxRectD(IControl *parent);
		};
	}
}
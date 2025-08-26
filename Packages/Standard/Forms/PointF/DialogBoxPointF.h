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
#include "Nitisa/Math/PointF.h"
#include "../IFormPointF.h"
#include "IDialogBoxPointFProto.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CDialogBoxPointF :public virtual IFormPointF, public IDialogBoxPointFProto
		{
		private:
			class CDialogBoxPointFService :public IDialogBoxPointFProtoService
			{
			private:
				CDialogBoxPointF * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxPointFService(CDialogBoxPointF *control);
			};
		private:
			PointF m_sValue;
			bool m_bHasMin;
			bool m_bHasMax;
			float m_fMin;
			float m_fMax;

			void LoadTranslatableTexts();
		protected:
			void FormPointFProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void EditX_OnKillFocus(IControl *sender) override;
			void EditY_OnKillFocus(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			PointF getValue() override;
			bool hasMin() override;
			bool hasMax() override;
			float getMin() override;
			float getMax() override;

			bool setValue(const PointF &value) override;
			bool setHasMin(const bool value) override;
			bool setHasMax(const bool value) override;
			bool setMin(const float value) override;
			bool setMax(const float value) override;

			void ActivateFirstEnabledInput() override;

			CDialogBoxPointF();
			CDialogBoxPointF(IForm *parent);
			CDialogBoxPointF(IControl *parent);
		};
	}
}
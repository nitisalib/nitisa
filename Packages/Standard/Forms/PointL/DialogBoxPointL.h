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
#include "Nitisa/Math/PointL.h"
#include "../IFormPointL.h"
#include "IDialogBoxPointLProto.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CDialogBoxPointL :public virtual IFormPointL, public IDialogBoxPointLProto
		{
		private:
			class CDialogBoxPointLService :public IDialogBoxPointLProtoService
			{
			private:
				CDialogBoxPointL * m_pControl;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CDialogBoxPointLService(CDialogBoxPointL *control);
			};
		private:
			PointL m_sValue;
			bool m_bHasMin;
			bool m_bHasMax;
			long long m_iMin;
			long long m_iMax;

			void LoadTranslatableTexts();
		protected:
			void FormPointLProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void EditX_OnKillFocus(IControl *sender) override;
			void EditY_OnKillFocus(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			PointL getValue() override;
			bool hasMin() override;
			bool hasMax() override;
			long long getMin() override;
			long long getMax() override;

			bool setValue(const PointL &value) override;
			bool setHasMin(const bool value) override;
			bool setHasMax(const bool value) override;
			bool setMin(const long long value) override;
			bool setMax(const long long value) override;

			void ActivateFirstEnabledInput() override;

			CDialogBoxPointL();
			CDialogBoxPointL(IForm *parent);
			CDialogBoxPointL(IControl *parent);
		};
	}
}
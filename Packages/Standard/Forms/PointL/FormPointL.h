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
#include "Nitisa/Math/PointL.h"
#include "../IFormPointL.h"
#include "IFormPointLProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormPointL :public virtual IFormPointL, public IFormPointLProto
		{
		private:
			class CFormPointLService :public CFormService
			{
			private:
				CFormPointL * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormPointLService(CFormPointL *form);
			};
		private:
			PointL m_sValue;
			bool m_bHasMin;
			bool m_bHasMax;
			long long m_iMin;
			long long m_iMax;

			void LoadTranslatableTexts();
		protected:
			void FormPointLProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
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

			CFormPointL(IWindow *window, IRenderer *renderer);
		};
	}
}
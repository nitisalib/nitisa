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
#include "Nitisa/Math/PointF.h"
#include "../IFormPointF.h"
#include "IFormPointFProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormPointF :public virtual IFormPointF, public IFormPointFProto
		{
		private:
			class CFormPointFService :public CFormService
			{
			private:
				CFormPointF * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormPointFService(CFormPointF *form);
			};
		private:
			PointF m_sValue;
			bool m_bHasMin;
			bool m_bHasMax;
			float m_fMin;
			float m_fMax;

			void LoadTranslatableTexts();
		protected:
			void FormPointFProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
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

			CFormPointF(IWindow *window, IRenderer *renderer);
		};
	}
}
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
#include "Nitisa/Math/PointD.h"
#include "../IFormPointD.h"
#include "IFormPointDProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormPointD :public virtual IFormPointD, public IFormPointDProto
		{
		private:
			class CFormPointDService :public CFormService
			{
			private:
				CFormPointD * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormPointDService(CFormPointD *form);
			};
		private:
			PointD m_sValue;
			bool m_bHasMin;
			bool m_bHasMax;
			double m_fMin;
			double m_fMax;

			void LoadTranslatableTexts();
		protected:
			void FormPointDProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
			void EditX_OnKillFocus(IControl *sender) override;
			void EditY_OnKillFocus(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			PointD getValue() override;
			bool hasMin() override;
			bool hasMax() override;
			double getMin() override;
			double getMax() override;

			bool setValue(const PointD &value) override;
			bool setHasMin(const bool value) override;
			bool setHasMax(const bool value) override;
			bool setMin(const double value) override;
			bool setMax(const double value) override;

			void ActivateFirstEnabledInput() override;

			CFormPointD(IWindow *window, IRenderer *renderer);
		};
	}
}
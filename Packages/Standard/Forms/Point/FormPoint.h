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
#include "Nitisa/Math/Point.h"
#include "../IFormPoint.h"
#include "IFormPointProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormPoint :public virtual IFormPoint, public IFormPointProto
		{
		private:
			class CFormPointService :public CFormService
			{
			private:
				CFormPoint * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormPointService(CFormPoint *form);
			};
		private:
			Point m_sValue;
			bool m_bHasMin;
			bool m_bHasMax;
			int m_iMin;
			int m_iMax;

			void LoadTranslatableTexts();
		protected:
			void FormPointProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
			void EditX_OnKillFocus(IControl *sender) override;
			void EditY_OnKillFocus(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			Point getValue() override;
			bool hasMin() override;
			bool hasMax() override;
			int getMin() override;
			int getMax() override;

			bool setValue(const Point &value) override;
			bool setHasMin(const bool value) override;
			bool setHasMax(const bool value) override;
			bool setMin(const int value) override;
			bool setMax(const int value) override;

			void ActivateFirstEnabledInput() override;

			CFormPoint(IWindow *window, IRenderer *renderer);
		};
	}
}
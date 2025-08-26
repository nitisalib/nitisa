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
#include "Nitisa/Math/RectB.h"
#include "../IFormRectB.h"
#include "IFormRectBProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormRectB :public virtual IFormRectB, public IFormRectBProto
		{
		private:
			class CFormRectBService :public CFormService
			{
			private:
				CFormRectB * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormRectBService(CFormRectB *form);
			};
		private:
			void LoadTranslatableTexts();
		protected:
			void FormRectBProto_OnPaint(IForm *sender, const MessagePaint &m, bool &draw_children) override;
			void FormRectBProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			RectB getValue() override;

			bool setValue(const RectB &value) override;

			void ActivateFirstEnabledInput() override;

			CFormRectB(IWindow *window, IRenderer *renderer);
		};
	}
}
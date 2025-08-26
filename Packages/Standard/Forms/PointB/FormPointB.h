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
#include "Nitisa/Math/PointB.h"
#include "../IFormPointB.h"
#include "IFormPointBProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormPointB :public virtual IFormPointB, public IFormPointBProto
		{
		private:
			class CFormPointBService :public CFormService
			{
			private:
				CFormPointB * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormPointBService(CFormPointB *form);
			};
		private:
			void LoadTranslatableTexts();
		protected:
			void FormPointBProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			PointB getValue() override;

			bool setValue(const PointB &value) override;

			void ActivateFirstEnabledInput() override;

			CFormPointB(IWindow *window, IRenderer *renderer);
		};
	}
}
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
#include "Nitisa/Math/RectB.h"
#include "../IFormRectB.h"
#include "IDialogBoxRectBProto.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CDialogBoxRectB :public virtual IFormRectB, public IDialogBoxRectBProto
		{
		private:
			class CDialogBoxRectBService :public IDialogBoxRectBProtoService
			{
			private:
				CDialogBoxRectB * m_pControl;
			public:
				// Notifications
				void NotifyOnFreeResources() override;
				void NotifyOnTranslateChange() override;

				CDialogBoxRectBService(CDialogBoxRectB *control);
			};
		private:
			ITexture *m_pCanvas;

			void LoadTranslatableTexts();
		protected:
			void FormRectBProto_OnPaint(IControl *sender, const MessagePaint &m, bool &draw_children) override;
			void FormRectBProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			RectB getValue() override;

			bool setValue(const RectB &value) override;

			void ActivateFirstEnabledInput() override;

			CDialogBoxRectB();
			CDialogBoxRectB(IForm *parent);
			CDialogBoxRectB(IControl *parent);
		};
	}
}
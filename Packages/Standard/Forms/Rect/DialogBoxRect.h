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
#include "Nitisa/Math/Rect.h"
#include "../IFormRect.h"
#include "IDialogBoxRectProto.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CDialogBoxRect :public virtual IFormRect, public IDialogBoxRectProto
		{
		private:
			class CDialogBoxRectService :public IDialogBoxRectProtoService
			{
			private:
				CDialogBoxRect * m_pControl;
			public:
				// Notifications
				void NotifyOnFreeResources() override;
				void NotifyOnTranslateChange() override;

				CDialogBoxRectService(CDialogBoxRect *control);
			};
		private:
			Rect m_sValue;
			bool m_bHasMin;
			bool m_bHasMax;
			int m_iMin;
			int m_iMax;
			
			ITexture *m_pCanvas;

			void LoadTranslatableTexts();
		protected:
			void FormRectProto_OnPaint(IControl *sender, const MessagePaint &m, bool &draw_children) override;
			void FormRectProto_OnKeyDown(IControl *sender, const MessageKey &m, bool &processed) override;
			void EditLeft_OnKillFocus(IControl *sender) override;
			void EditTop_OnKillFocus(IControl *sender) override;
			void EditRight_OnKillFocus(IControl *sender) override;
			void EditBottom_OnKillFocus(IControl *sender) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			Rect getValue() override;
			bool hasMin() override;
			bool hasMax() override;
			int getMin() override;
			int getMax() override;

			bool setValue(const Rect &value) override;
			bool setHasMin(const bool value) override;
			bool setHasMax(const bool value) override;
			bool setMin(const int value) override;
			bool setMax(const int value) override;

			void ActivateFirstEnabledInput() override;

			CDialogBoxRect();
			CDialogBoxRect(IForm *parent);
			CDialogBoxRect(IControl *parent);
		};
	}
}
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
#include "IFormConfiguration.h"
#include "../../Core/Types.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace fb
	{
		class CFormConfiguration :public IFormConfiguration
		{
		private:
			bool m_bGlobal;

			bool Validate();
		protected:
			void FormSettings_OnKeyDown(IForm *sender, const MessageKey &m) override;
			void PanelGridColor_OnLeftMouseButtonDown(IControl *sender, const MessageMouse &m, bool &processed) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonOkForm_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
			void PanelSelectionBorderColor_OnLeftMouseButtonDown(IControl *sender, const MessageMouse &m, bool &processed) override;
			void PanelSelectionBackgroundColor_OnLeftMouseButtonDown(IControl *sender, const MessageMouse &m, bool &processed) override;
			void PanelHighlightBorderColorLeft_OnLeftMouseButtonUp(IControl *sender, const MessageMouse &m, bool &processed) override;
			void PanelHighlightBorderColorTop_OnLeftMouseButtonUp(IControl *sender, const MessageMouse &m, bool &processed) override;
			void PanelHighlightBorderColorRight_OnLeftMouseButtonUp(IControl *sender, const MessageMouse &m, bool &processed) override;
			void PanelHighlightBorderColorBottom_OnLeftMouseButtonUp(IControl *sender, const MessageMouse &m, bool &processed) override;
			void RadioButtonForm_OnChange(IControl *sender) override;
			void RadioButtonDialogBox_OnChange(IControl *sender) override;
		public:
			CFormConfiguration();

			bool isGlobal() const;

			void ToSettings(SETTINGS &dst);
			void FromSettings(const SETTINGS &src);

			void AddDialogBox(const String &name, const String &caption);
		};

		extern CFormConfiguration *FormConfiguration;
	}
}
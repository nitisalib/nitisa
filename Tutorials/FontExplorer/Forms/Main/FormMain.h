#pragma once

#include "IFormMain.h" // Include form prototype header file

namespace nitisa
{
	namespace app
	{
		class CFormMain :public IFormMain // Declare form class derived from form prototype class
		{
		protected:
			// Event processing methods taken from the corresponding (protected) section of the form prototype class
			void FormMain_OnPaint(IForm *sender, const MessagePaint &m, bool &draw_children) override;
			void DropDownName_OnSelect(IControl *sender, const int index) override;
			void UpDownHeight_OnChange(standard::IUpDown *sender) override;
			void DropDownWeight_OnSelect(IControl *sender, const int index) override;
			void UpDownDistance_OnChange(standard::IUpDown *sender) override;
			void PanelColor_OnLeftMouseButtonUp(IControl *sender, const MessageMouse &m, bool &processed) override;
			void PanelShadowColor_OnLeftMouseButtonUp(IControl *sender, const MessageMouse &m, bool &processed) override;
			void UpDownShadowShiftX_OnChange(standard::IUpDown *sender) override;
			void UpDownShadowShiftY_OnChange(standard::IUpDown *sender) override;
			void UpDownShadowRadius_OnChange(standard::IUpDown *sender) override;
			void CheckBoxItalic_OnChange(IControl *sender) override;
			void CheckBoxUnderline_OnChange(IControl *sender) override;
			void CheckBoxStrikeOut_OnChange(IControl *sender) override;
			void CheckBoxMonospace_OnChange(IControl *sender) override;
		public:
			CFormMain(); // Constructor
		};

		extern CFormMain *FormMain; // Variable to store form instance pointer
	}
}
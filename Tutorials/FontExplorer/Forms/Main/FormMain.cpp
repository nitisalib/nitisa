#include "Nitisa/Interfaces/IFont.h" // IFont interface is declared here. It stores font properties
#include "Nitisa/Interfaces/IPlatformFont.h" // IPlatformFont interface is declared here. It stores platform interface properties and is used by renderer to draw texts
#include "Nitisa/Interfaces/IRenderer.h" // IRenderer interface is declared here. We use renderer for drawing

#include "Nitisa/Render/StorePrimitiveMatrix.h" // CStorePrimitiveMatrix helper class is declared here. We use it for more convenient storing and restoring active primitive matrix in renderer
#include "Nitisa/Render/Utils.h"

#include "Platform/Core/Renderer.h" // Helper class CRenderer is declared here. It's being used to create renderer
#include "Platform/Core/Window.h" // Helper class CWindow is declared here. It's being used to create window

#include "FormMain.h" // Header file of the form

namespace nitisa
{
	namespace app
	{
		CFormMain *FormMain{ nullptr };

		// Constructor just calls parent class constructor giving him window and renderer
		CFormMain::CFormMain() :
			IFormMain(CWindow::Create(), CRenderer::Create())
		{

		}

		// Event called when we change font name
		void CFormMain::DropDownName_OnSelect(IControl *sender, const int index)
		{
			getFont()->setFontName(m_pDropDownName->getText());
		}

		// Event called when we change font height
		void CFormMain::UpDownHeight_OnChange(standard::IUpDown *sender)
		{
			getFont()->setHeight(m_pUpDownHeight->getValue());
		}

		// Event called when we change font weight
		void CFormMain::DropDownWeight_OnSelect(IControl *sender, const int index)
		{
			getFont()->setWeight((FontWeight)m_pDropDownWeight->getActiveIndex());
		}

		// Event called when we change font additional distance between characters
		void CFormMain::UpDownDistance_OnChange(standard::IUpDown *sender)
		{
			getFont()->setDistance((float)m_pUpDownDistance->getValue());
		}

		// Event called when we release left mouse button on panel widget storing font color
		void CFormMain::PanelColor_OnLeftMouseButtonUp(IControl *sender, const MessageMouse &m, bool &processed)
		{
			m_pColorDialog->setColor(m_pPanelColor->getBackgroundColor()); // Assign panel background color to color dialog
			if (m_pColorDialog->Execute()) // Show color dialog and if it was closed by OK button do
			{
				m_pPanelColor->setBackgroundColor(m_pColorDialog->getColor()); // Change panel color to selected one
				getFont()->setColor(m_pColorDialog->getColor()); // Change form font color to selected one
			}
		}

		// Event called when we release left mouse button on panel widget storing font shadow color
		void CFormMain::PanelShadowColor_OnLeftMouseButtonUp(IControl *sender, const MessageMouse &m, bool &processed)
		{
			m_pColorDialog->setColor(m_pPanelShadowColor->getBackgroundColor()); // Assign panel background color to color dialog
			if (m_pColorDialog->Execute()) // Show color dialog and if it was closed by OK button do
			{
				m_pPanelShadowColor->setBackgroundColor(m_pColorDialog->getColor()); // Change panel color to selected one
				getFont()->setShadowColor(m_pColorDialog->getColor()); // Change form font shadow color to selected one
			}
		}

		// Event called when we change X coordinate of the shadow shift
		void CFormMain::UpDownShadowShiftX_OnChange(standard::IUpDown *sender)
		{
			getFont()->setShadowShift(PointF{ (float)m_pUpDownShadowShiftX->getValue(), getFont()->ShadowShift.Y });
		}

		// Event called when we change Y coordinate of the shadow shift
		void CFormMain::UpDownShadowShiftY_OnChange(standard::IUpDown *sender)
		{
			getFont()->setShadowShift(PointF{ getFont()->ShadowShift.X, (float)m_pUpDownShadowShiftY->getValue() });
		}

		// Event called when we change shadow radius
		void CFormMain::UpDownShadowRadius_OnChange(standard::IUpDown *sender)
		{
			getFont()->setShadowRadius(m_pUpDownShadowRadius->getValue());
		}

		// Event called when we Italic checkbox state
		void CFormMain::CheckBoxItalic_OnChange(IControl *sender)
		{
			getFont()->setItalic(m_pCheckBoxItalic->getChecked() == standard::ICheckBox::CheckedState::Checked);
		}

		// Event called when we Underline checkbox state
		void CFormMain::CheckBoxUnderline_OnChange(IControl *sender)
		{
			getFont()->setUnderline(m_pCheckBoxUnderline->getChecked() == standard::ICheckBox::CheckedState::Checked);
		}

		// Event called when we StrikeOut checkbox state
		void CFormMain::CheckBoxStrikeOut_OnChange(IControl *sender)
		{
			getFont()->setStrikeOut(m_pCheckBoxStrikeOut->getChecked() == standard::ICheckBox::CheckedState::Checked);
		}

		// Event called when we Monospace checkbox state
		void CFormMain::CheckBoxMonospace_OnChange(IControl *sender)
		{
			getFont()->setMonospace(m_pCheckBoxMonospace->getChecked() == standard::ICheckBox::CheckedState::Checked);
		}

		// Event called when form is being re-painted
		void CFormMain::FormMain_OnPaint(IForm *sender, const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass) // We only want to draw if it's the first step
			{
				// Text to be drawn
				static const String text{ L"Hello World!" };
				// Store renderer, font and platform font to avoid called getter methods multiple times
				IRenderer *renderer{ getRenderer() };
				IFont *font{ getFont() };
				IPlatformFont *pf{ getFont()->getPlatformFont(renderer) };
				// Calculate size of the form part where we are going to draw text
				PointF area_size{ m_pGroupBox1->getTransform()->getTx(), (float)getClientHeight() };
				// Calculate text size
				PointF text_size{ pf->getStringSize(text, font->Distance) };
				// Calculate text position so it is in the middle of the form free area
				PointF text_position{ (area_size - text_size) / 2 };
				// Calculate text rectangle
				RectF client{ text_position.X, text_position.Y, text_position.X + text_size.X, text_position.Y + text_size.Y };
				// Draw shadow with helper function
				DrawTextShadow(renderer, pf, font->Distance, Identity, client + font->ShadowShift, text_position, text, font->ShadowColor, font->ShadowShift, font->ShadowRadius);
				// Calculate text transformation matrix to be used in drawing. We need to round position to avoid artifacts
				Mat4f matrix{ ntl::Mat4Translate<float>(std::round(text_position.X), std::round(text_position.Y), 0) };
				// Store current renderer's active primitive matrix
				CStorePrimitiveMatrix s_matrix{ renderer };
				// Draw
				renderer
					->ActivatePrimitiveMatrix(&matrix) // Activate our primitive matrix
					->DrawText(text, pf, font->Distance, font->Color); // Draw text
			} // Here s_matrix variable will be destroyed and restore renderer's active primitive matrix it stored at the creation moment
		}
	}
}
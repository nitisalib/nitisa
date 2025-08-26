#include "Nitisa/Interfaces/IApplication.h" // Application variable is declared here. We use it to get access to its Dialogs property
#include "Nitisa/Interfaces/IDialogs.h" // IDialogs interface is declared here. We use its Error method to show information about an error

#include "Platform/Core/Renderer.h" // Helper class CRenderer is declared here. It's being used to create renderer
#include "Platform/Core/Window.h" // Helper class CWindow is declared here. It's being used to create window

#include "FormMain.h" // Header file of the form

namespace nitisa
{
	namespace app
	{
		CFormMain *FormMain{ nullptr };

		// Constructor calls parent class constructor giving him window and renderer
		CFormMain::CFormMain() :
			IFormMain(CWindow::Create(), CRenderer::Create())
		{
			// Fill cells of StringGrid widgets with Identity matrix
			MatrixToWidget(Identity, m_pStringGridA);
			MatrixToWidget(Identity, m_pStringGridB);
		}

		// Put matrix elements into corresponding cells of a StringGrid widget
		void CFormMain::MatrixToWidget(const Mat4f &m, standard::CStringGrid *widget)
		{
			for (int row = 0; row < 4; row++)
				for (int col = 0; col < 4; col++)
					widget->setCell(col, row, ToFixed(m[row][col], 2));
		}

		// Get numbers from StringGrid widget cells and try to put them into corresponding matrix elements
		bool CFormMain::WidgetToMatrix(standard::CStringGrid *widget, Mat4f &m)
		{
			for (int row = 0; row < 4; row++)
				for (int col = 0; col < 4; col++)
					if (!TryStringToFloat(widget->getCell(col, row), m[row][col])) // If cell doesn't contain correct number
					{
						Application->Dialogs->Error(L"You have incorrect number in row " + ToString(row) + L" and column " + ToString(col)); // Show error
						widget->setCellActive(col, row, true); // Activate cell with error value
						widget->setCellFocused(col, row, true); // Make cell with error value focused
						widget->setCellSelected(col, row, true); // Make cell with error value selected
						return false;
					}
			return true;
		}

		void CFormMain::ButtonCalculate_OnClick(IControl *sender)
		{
			Mat4f a, b; // Variables to store matrices
			if (!WidgetToMatrix(m_pStringGridA, a)) // Try to fill first matrix elements from StringGrid widget cells
				return;
			if (!WidgetToMatrix(m_pStringGridB, b)) // Try to fill second matrix elements from StringGrid widget cells
				return;
			MatrixToWidget(a * b, m_pStringGridResult); // Multiply matrices and put result into the third StringGrid
		}
	}
}
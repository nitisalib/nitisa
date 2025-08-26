#pragma once

#include "IFormMain.h" // Include form prototype header file

namespace nitisa
{
	namespace app
	{
		class CFormMain :public IFormMain // Declare form class derived from form prototype class
		{
		private:
			// Helper methods
			void MatrixToWidget(const Mat4f &m, standard::CStringGrid *widget);
			bool WidgetToMatrix(standard::CStringGrid *widget, Mat4f &m);
		protected:
			// Event processing methods taken from the corresponding (protected) section of the form prototype class
			void ButtonCalculate_OnClick(IControl *sender) override;
		public:
			CFormMain(); // Constructor
		};

		extern CFormMain *FormMain; // Variable to store form instance pointer
	}
}
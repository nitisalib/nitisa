#pragma once

// Include form prototype. It is generated when you save form in the Form Builder.
// TODO: Rename if you saved form with another name
#include "IFormMain.h"

namespace nitisa
{
	namespace app
	{
		// Main form class.
		// TODO: Rename class and/or prototype class if your form name is not FormMain
		class CFormMain :public IFormMain
		{
		protected:
			// TODO: Here should be methods called at different events.
			// Just copy declarations from protected section of IFormMain and implement them.
		public:
			CFormMain();
		};

		// Global variable for main form
		extern CFormMain *FormMain;
	}
}
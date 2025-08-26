#pragma once

#include "Nitisa/Core/Form.h"

namespace nitisa
{
	namespace coolwidgets
	{
		class CRegistration;
	}

	class CFormMain :public CForm
	{
	private:
		coolwidgets::CRegistration *m_pRegistration;
	public:
		CFormMain();
	};

	extern CFormMain *FormMain;
}
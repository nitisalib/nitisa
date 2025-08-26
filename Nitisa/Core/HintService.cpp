// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	CHintService::CHintService(CHint *hint) :
		m_pHint{ hint }
	{

	}

	void CHintService::setForm(IForm *value)
	{
		m_pHint->Hide(true);
		m_pHint->m_cFont.NotifyOnFreeResources();
		if (m_pHint->m_pRenderTarget)
		{
			m_pHint->m_pRenderTarget->Release();
			m_pHint->m_pRenderTarget = nullptr;
		}
		if (m_pHint->m_hTimer)
		{
			m_pHint->m_pForm->DeleteTimer(m_pHint->m_hTimer);
			m_pHint->m_hTimer = nullptr;
		}
		m_pHint->m_pForm = value;
	}

	void CHintService::Release()
	{
		delete this;
	}
}
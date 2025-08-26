// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	CModelService::CModelService(CModel *model) :
		m_pModel{ model }
	{

	}

	void CModelService::setParent(IModel *value)
	{
		m_pModel->m_pParent = value;
	}

	void CModelService::NotifyOnParentTransformChanged()
	{
		m_pModel->m_bMatricesValid = false;
		for (auto model : m_pModel->m_aModels)
			model->QueryService()->NotifyOnParentTransformChanged();
	}
}
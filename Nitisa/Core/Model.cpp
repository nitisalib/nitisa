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
#pragma region Constructor & destructor
	CModel::CModel(const bool accept_parent, const bool accept_models) :
		CReleasable(),
		CTransformable(),
		m_cService{ this },
		m_sModelMatrix{ 1, 0 },
		m_sNormalMatrix{ 1, 0 },
		m_bMatricesValid{ false }
	{
		m_pParent = nullptr;
		m_bAcceptParent = accept_parent;
		m_bAcceptModels = accept_models;
	}

	void CModel::BeforeRelease()
	{
		if (m_pParent)
			m_pParent->DetachModel(this);
		DeleteModels();
	}
#pragma endregion

#pragma region IModel getters
	int CModel::getModelCount() const
	{
		return (int)m_aModels.size();
	}

	IModel *CModel::getModel(const int index)
	{
		if (index >= 0 && index < (int)m_aModels.size())
			return m_aModels[index];
		return nullptr;
	}

	const Mat4f &CModel::getModelMatrix()
	{
		UpdateMatrices();
		return m_sModelMatrix;
	}

	const Mat3f &CModel::getNormalMatrix()
	{
		UpdateMatrices();
		return m_sNormalMatrix;
	}

	bool CModel::hasModel(IModel *value) const
	{
		if (value)
		{
			for (auto m : m_aModels)
				if (m == value)
					return true;
			for (auto m : m_aModels)
				if (m->hasModel(value))
					return true;
		}
		return false;
	}

	bool CModel::isAcceptParent(IModel *parent)
	{
		return true;
	}

	bool CModel::isAcceptModel(IModel *model)
	{
		return true;
	}
#pragma endregion

#pragma region IModel setters
	bool CModel::setParent(IModel *value)
	{
		if (value && (value == m_pParent || !m_bAcceptParent || !isAcceptParent(value) || !value->AcceptModels || !value->isAcceptModel(this) || hasModel(value)))
			return false;
		if (value != m_pParent)
		{
			if (m_pParent)
				m_pParent->DetachModel(this);
			m_pParent = value;
			if (m_pParent)
				m_pParent->AddModel(this);
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region IModel methods
	IModelService *CModel::QueryService()
	{
		return &m_cService;
	}
#pragma endregion

#pragma region IModel models
	size_t CModel::AddModel(IModel *model)
	{
		if (!model || model == this || !m_bAcceptModels || !isAcceptModel(model) || !model->AcceptParent || !model->isAcceptParent(this) || hasModel(model))
		{
			return false;
		}
		if (model->Parent)
			model->Parent->DetachModel(model);
		model->QueryService()->setParent(this);
		m_aModels.push_back(model);
		model->QueryService()->NotifyOnParentTransformChanged();
		return true;
	}

	bool CModel::DetachModel(const int index)
	{
		if (index >= 0 && index < (int)m_aModels.size())
		{
			IModel *model{ m_aModels[index] };
			m_aModels.erase(m_aModels.begin() + index);
			model->QueryService()->setParent(nullptr);
			model->QueryService()->NotifyOnParentTransformChanged();
			return true;
		}
		return false;
	}

	bool CModel::DetachModel(IModel *model)
	{
		if (model && model->Parent == this)
			for (auto pos = m_aModels.begin(); pos != m_aModels.end(); pos++)
				if (*pos == model)
					return DetachModel(int(pos - m_aModels.begin()));
		return false;
	}

	bool CModel::DeleteModel(const int index)
	{
		if (index >= 0 && index < (int)m_aModels.size())
		{
			m_aModels[index]->Release();
			return true;
		}
		return false;
	}

	bool CModel::DeleteModel(IModel *value)
	{
		if (value && value->Parent == this)
			for (auto pos = m_aModels.begin(); pos != m_aModels.end(); pos++)
				if (*pos == value)
					return DeleteModel(int(pos - m_aModels.begin()));
		return false;
	}

	bool CModel::DeleteModels()
	{
		if (m_aModels.size() > 0)
		{
			while (m_aModels.size() > 0)
				DeleteModel(0);
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Helpers
	void CModel::UpdateMatrices()
	{
		if (!m_bMatricesValid)
		{
			if (m_pParent)
				m_sModelMatrix = m_pParent->getMatrix() * getMatrix();
			else
				m_sModelMatrix = getMatrix();
			m_sNormalMatrix = Mat3f{
				m_sModelMatrix._11, m_sModelMatrix._12, m_sModelMatrix._13,
				m_sModelMatrix._21, m_sModelMatrix._22, m_sModelMatrix._23,
				m_sModelMatrix._31, m_sModelMatrix._32, m_sModelMatrix._33
			};
			ntl::Inverse<float>(m_sNormalMatrix);
			ntl::Transpose<float>(m_sNormalMatrix);
			m_bMatricesValid = true;
		}
	}
#pragma endregion
}
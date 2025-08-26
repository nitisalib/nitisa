// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IModel.h"
#include "../Math/Mat3f.h"
#include "../Math/Mat4f.h"
#include "ModelService.h"
#include "Releasable.h"
#include "Transformable.h"
#include <vector>

namespace nitisa
{
	class IModelService;

	class CModel :public virtual IModel, public CReleasable, public CTransformable
	{
		friend CModelService;
	private:
		CModelService m_cService;
		IModel *m_pParent;
		std::vector<IModel*> m_aModels;
		Mat4f m_sModelMatrix;
		Mat3f m_sNormalMatrix;
		bool m_bMatricesValid;

		void UpdateMatrices();
	protected:
		void BeforeRelease() override;
	public:
		// IModel getters
		int getModelCount() const override;
		IModel *getModel(const int index) override;
		bool hasModel(IModel *value) const override;
		const Mat4f &getModelMatrix() override;
		const Mat3f &getNormalMatrix() override;
		bool isAcceptParent(IModel *parent) override;
		bool isAcceptModel(IModel *model) override;

		// IModel setters
		bool setParent(IModel *value) override;

		// IModel methods
		IModelService *QueryService() override;

		// IModel models
		size_t AddModel(IModel *model) override;
		bool DetachModel(const int index) override;
		bool DetachModel(IModel *model) override;
		bool DeleteModel(const int index) override;
		bool DeleteModel(IModel *model) override;
		bool DeleteModels() override;

		CModel(const bool accept_parent, const bool accept_models);
	};
}
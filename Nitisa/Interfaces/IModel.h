// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Math/Mat3f.h"
#include "../Math/Mat4f.h"
#include "IReleasable.h"
#include "ITransformable.h"

namespace nitisa
{
	class IModelService;

	class IModel : public virtual IReleasable, public virtual ITransformable
	{
	protected:
		IModel() = default;
		~IModel() = default;
		IModel(const IModel &other) = delete;
		IModel(IModel &&other) = delete;
		IModel &operator=(const IModel &other) = delete;
		IModel &operator=(IModel &&other) = delete;
	protected:
		IModel *m_pParent;
		bool m_bAcceptParent;
		bool m_bAcceptModels;
	public:
		IModel* const &Parent{ m_pParent }; // Parent model
		bool const &AcceptParent{ m_bAcceptParent }; // Whether it can be attached to another model
		bool const &AcceptModels{ m_bAcceptModels }; // Whether another models can be attached to this one

		virtual int getModelCount() const = 0; // Return count of attached model
		virtual IModel *getModel(const int index) = 0; // Return attached model by index
		virtual bool hasModel(IModel *value) const = 0; // Check whether specified model exists in hierarchy
		virtual const Mat4f &getModelMatrix() = 0; // Return model matrix
		virtual const Mat3f &getNormalMatrix() = 0; // Return normal matrix
		virtual bool isAcceptParent(IModel *parent) = 0; // Check whether it cane be attached to specified parent 
		virtual bool isAcceptModel(IModel *model) = 0; // Check whether specified model can be attached to this one

		virtual bool setParent(IModel *value) = 0; // Attach this model to specified parent

		virtual IModelService *QueryService() = 0; // Return model service

		virtual size_t AddModel(IModel *model) = 0; // Add model to list
		virtual bool DetachModel(const int index) = 0; // Detach model from list by index
		virtual bool DetachModel(IModel *model) = 0; // Detach model from list
		virtual bool DeleteModel(const int index) = 0; // Delete model from list by index
		virtual bool DeleteModel(IModel *model) = 0; // Delete model from list
		virtual bool DeleteModels() = 0; // Delete all child models
	};
}
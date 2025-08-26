// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	class IModel;

	class IModelService
	{
	protected:
		IModelService() = default;
		~IModelService() = default;
		IModelService(const IModelService &other) = delete;
		IModelService(IModelService &&other) = delete;
		IModelService &operator=(const IModelService &other) = delete;
		IModelService &operator=(IModelService &&other) = delete;
	public:
		virtual void setParent(IModel *value) = 0; // Set parent

		virtual void NotifyOnParentTransformChanged() = 0; // Called when there were a change in parent(of any level) model transformation
	};
}
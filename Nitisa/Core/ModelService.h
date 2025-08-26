// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IModelService.h"

namespace nitisa
{
	class IModel;

	class CModel;

	class CModelService :public virtual IModelService
	{
	private:
		CModel *m_pModel;
	public:
		void setParent(IModel *value) override;

		void NotifyOnParentTransformChanged() override;

		CModelService(CModel *model);
	};
}
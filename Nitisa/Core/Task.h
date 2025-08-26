// This file is a part of Nitisa framework
// Copyright © 2018 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/ITask.h"

namespace nitisa
{
	template<class Type>
	class CTask :public virtual ITask
	{
	private:
		Type m_fRun;
	public:
		void Run() override
		{
			m_fRun();
		}

		void Release() override
		{
			delete this;
		}

		CTask(Type run) : m_fRun{ run }
		{

		}

		virtual ~CTask() = default;
	};

	template<class Type>
	ITask *CreateTask(Type run)
	{
		return new CTask<Type>(run);
	}
}
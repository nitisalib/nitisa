// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Releasable.h"
#include "../../../Core/Strings.h"
#include "../Interfaces/IExpressionRunner.h"
#include "Variable.h"
#include <utility>
#include <vector>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IErrorListener;

	namespace script
	{
		class IFunction;

		class CExpressionRunner :public virtual IExpressionRunner, public virtual CReleasable
		{
		protected:
			~CExpressionRunner() = default;
			CExpressionRunner(const CExpressionRunner &other) = delete;
			CExpressionRunner(CExpressionRunner &&other) = delete;
			CExpressionRunner &operator=(const CExpressionRunner &other) = delete;
			CExpressionRunner &operator=(CExpressionRunner &&other) = delete;
		protected:
			IErrorListener *m_pErrorListener; // Error listener
			std::vector<std::pair<String, Variable*>> m_aVariables; // Variable list
			IFunction *m_pFunction; // Prepared function

			void BeforeRelease() override;

			CExpressionRunner(); // Constructor
		public:
			IErrorListener* &ErrorListener{ m_pErrorListener }; // Error listener. Can be nullptr if no additional error information is required

			// IExpressionRunner getters
			size_t getVariableCount() const override;
			Variable *getVariable(const size_t index) override;
			Variable *getVariable(const String &name) override;

			// IExpressionRunner variables
			bool AddVariable(const String &name, const Variable &variable) override;
			bool DeleteVariable(const size_t index) override;
			bool DeleteVariable(const String &name) override;
			bool DeleteVariables() override;
		};
	}
}
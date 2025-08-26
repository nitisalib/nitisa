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
#include "../Interfaces/IExpression.h"
#include "ExpressionType.h"
#include <vector>

#pragma warning(disable: 4250)

namespace nitisa
{
	namespace script
	{
		class IExpression;

		struct Operator;

		namespace generic
		{
			class CExpressionBuilder;
		}

		class CExpression :public virtual IExpression, public CReleasable
		{
			friend generic::CExpressionBuilder;
		protected:
			CExpression(const size_t index, const ExpressionType type, const bool allow_children);
			~CExpression() = default;
			CExpression(const CExpression &other) = delete;
			CExpression(CExpression &&other) = delete;
			CExpression &operator=(const CExpression &other) = delete;
			CExpression &operator=(CExpression &&other) = delete;
		protected:
			std::vector<const Operator*> m_aPriorOperators; // List of prior operators
			std::vector<const Operator*> m_aPosteriorOperators; // List of posterior operators
			std::vector<IExpression*> m_aExpressions; // List of expressions
			bool m_bAllowChildren; // Whether child expressions are allowed

			String PriorOperatorsToString() const; // Convert prior operator list to string representation
			String PosteriorOperatorsToString() const; // Convert posterior operator list to string representation
		protected:
			void BeforeRelease() override;
		public:
			// IExpression operators
			IExpression *operator[](const size_t index) override;

			// IExpression getters
			size_t getPriorOperatorCount() const override;
			const Operator *getPriorOperator(const size_t index) const override;
			size_t getPosteriorOperatorCount() const override;
			const Operator *getPosteriorOperator(const size_t index) const override;
			size_t getExpressionCount() const override;
			size_t getExpressionIndex(IExpression *expression) const override;
			IExpression *getExpression(const size_t index) override;

			// IExpression prior operators
			bool AddPriorOperator(const Operator *value) override;
			bool DeletePriorOperator(const size_t index) override;
			bool DeletePriorOperators() override;

			// IExpression posterior operators
			bool AddPosteriorOperator(const Operator *value) override;
			bool DeletePosteriorOperator(const size_t index) override;
			bool DeletePosteriorOperators() override;

			// IExpression expression methods
			bool AddExpression(IExpression *expression) override;
			bool InsertExpression(IExpression *expression, const size_t before) override;
			bool DetachExpression(const size_t index) override;
			bool DetachExpression(IExpression *expression) override;
			bool DetachExpressions(const size_t index, const size_t count) override;
			bool DetachExpressions() override;
			bool DeleteExpression(const size_t index) override;
			bool DeleteExpression(IExpression *expression) override;
			bool DeleteExpressions(const size_t index, const size_t count) override;
			bool DeleteExpressions() override;
		};
	}
}
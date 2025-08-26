// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Strings.h"
#include "../../../Interfaces/IReleasable.h"
#include "../Core/ExpressionType.h"

namespace nitisa
{
	namespace script
	{
		struct Operator;

		// Prior and Posterior operators should be added in order they are to be applied (starting from 0)
		class IExpression :public virtual IReleasable
		{
		protected:
			IExpression() = default;
			~IExpression() = default;
			IExpression(const IExpression &other) = delete;
			IExpression(IExpression &&other) = delete;
			IExpression &operator=(const IExpression &other) = delete;
			IExpression &operator=(IExpression &&other) = delete;
		protected:
			size_t m_iIndex;
			ExpressionType m_eType;
		public:
			size_t const &Index{ m_iIndex }; // Index of token start from which the expression was created
			ExpressionType const &Type{ m_eType }; // Expression type

			virtual IExpression *operator[](const size_t index) = 0; // Return expression at specified index

			virtual size_t getPriorOperatorCount() const = 0; // Return prior operator count
			virtual const Operator *getPriorOperator(const size_t index) const = 0; // Return prior operator by index
			virtual size_t getPosteriorOperatorCount() const = 0; // Return posterior operator count
			virtual const Operator *getPosteriorOperator(const size_t index) const = 0; // Return posterior operator by index
			virtual size_t getExpressionCount() const = 0; // Return expression count
			virtual size_t getExpressionIndex(IExpression *expression) const = 0; // Return specified expression index or npos
			virtual IExpression *getExpression(const size_t index) = 0; // Return expression by index

			virtual bool AddPriorOperator(const Operator *value) = 0; // Add prior operator
			virtual bool DeletePriorOperator(const size_t index) = 0; // Delete prior operator by index
			virtual bool DeletePriorOperators() = 0; // Delete all prior operators

			virtual bool AddPosteriorOperator(const Operator *value) = 0; // Add posterior operator
			virtual bool DeletePosteriorOperator(const size_t index) = 0; // Delete posterior operator by index
			virtual bool DeletePosteriorOperators() = 0; // Delete all posterior operators

			virtual bool AddExpression(IExpression *expression) = 0; // Add expression
			virtual bool InsertExpression(IExpression *expression, const size_t before) = 0; // Insert expression before specified one
			virtual bool DetachExpression(const size_t index) = 0; // Delete expression by index not destroying it
			virtual bool DetachExpression(IExpression *expression) = 0; // Delete specified expression not destroying it
			virtual bool DetachExpressions(const size_t index, const size_t count) = 0; // Delete expressions from specified range not destroying them
			virtual bool DetachExpressions() = 0; // Delete all expressions not destroying them
			virtual bool DeleteExpression(const size_t index) = 0; // Delete expression by index
			virtual bool DeleteExpression(IExpression *expression) = 0; // Delete specified expression
			virtual bool DeleteExpressions(const size_t index, const size_t count) = 0; // Delete expression from specified range
			virtual bool DeleteExpressions() = 0; // Delete all expressions

			virtual String toString() = 0; // Convert to string representation
		};
	}
}
// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace db
	{
	#pragma region Expression
		DbCondition Expression(const String &expression)
		{
			DbCondition result{ new CDbCondition() };
			result->setOperand1(expression);
			return result;
		}
	#pragma endregion

	#pragma region Equals
		DbCondition Equals(const String &operand1, const String &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Equals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Equals(const String &operand1, const DbValue &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Equals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Equals(const DbValue &operand1, const String &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Equals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Equals(const DbValue &operand1, const DbValue &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Equals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Equals(const String &operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Equals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Equals(DbCondition operand1, const String &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Equals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Equals(DbCondition operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Equals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Equals(const DbValue &operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Equals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Equals(DbCondition operand1, const DbValue &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Equals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}
	#pragma endregion

	#pragma region NotEquals
		DbCondition NotEquals(const String &operand1, const String &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition NotEquals(const String &operand1, const DbValue &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition NotEquals(const DbValue &operand1, const String &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition NotEquals(const DbValue &operand1, const DbValue &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition NotEquals(const String &operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition NotEquals(DbCondition operand1, const String &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition NotEquals(DbCondition operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition NotEquals(const DbValue &operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition NotEquals(DbCondition operand1, const DbValue &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}
	#pragma endregion

	#pragma region Greater
		DbCondition Greater(const String &operand1, const String &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Greater;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Greater(const String &operand1, const DbValue &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Greater;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Greater(const DbValue &operand1, const String &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Greater;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Greater(const DbValue &operand1, const DbValue &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Greater;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Greater(const String &operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Greater;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Greater(DbCondition operand1, const String &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Greater;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Greater(DbCondition operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Greater;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Greater(const DbValue &operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Greater;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Greater(DbCondition operand1, const DbValue &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Greater;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}
	#pragma endregion

	#pragma region GreaterEquals
		DbCondition GreaterEquals(const String &operand1, const String &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::GreaterEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition GreaterEquals(const String &operand1, const DbValue &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::GreaterEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition GreaterEquals(const DbValue &operand1, const String &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::GreaterEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition GreaterEquals(const DbValue &operand1, const DbValue &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::GreaterEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition GreaterEquals(const String &operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::GreaterEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition GreaterEquals(DbCondition operand1, const String &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::GreaterEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition GreaterEquals(DbCondition operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::GreaterEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition GreaterEquals(const DbValue &operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::GreaterEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition GreaterEquals(DbCondition operand1, const DbValue &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::GreaterEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}
	#pragma endregion

	#pragma region Less
		DbCondition Less(const String &operand1, const String &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Less;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Less(const String &operand1, const DbValue &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Less;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Less(const DbValue &operand1, const String &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Less;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Less(const DbValue &operand1, const DbValue &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Less;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Less(const String &operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Less;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Less(DbCondition operand1, const String &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Less;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Less(DbCondition operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Less;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Less(const DbValue &operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Less;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition Less(DbCondition operand1, const DbValue &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Less;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}
	#pragma endregion

	#pragma region LessEquals
		DbCondition LessEquals(const String &operand1, const String &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::LessEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition LessEquals(const String &operand1, const DbValue &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::LessEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition LessEquals(const DbValue &operand1, const String &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::LessEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition LessEquals(const DbValue &operand1, const DbValue &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::LessEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition LessEquals(const String &operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::LessEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition LessEquals(DbCondition operand1, const String &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::LessEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition LessEquals(DbCondition operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::LessEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition LessEquals(const DbValue &operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::LessEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}

		DbCondition LessEquals(DbCondition operand1, const DbValue &operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::LessEquals;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}
	#pragma endregion

	#pragma region And
		DbCondition And(DbCondition operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::And;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}
	#pragma endregion

	#pragma region Or
		DbCondition Or(DbCondition operand1, DbCondition operand2)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Or;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			return result;
		}
	#pragma endregion

	#pragma region Not
		DbCondition Not(DbCondition operand)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Not;
			result->setOperand1(operand);
			return result;
		}
	#pragma endregion

	#pragma region Between
		DbCondition Between(const String &operand1, const String &operand2, const String &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(const String &operand1, const String &operand2, const DbValue &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(const String &operand1, const String &operand2, DbCondition operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(const String &operand1, const DbValue &operand2, const String &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(const String &operand1, const DbValue &operand2, const DbValue &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(const String &operand1, const DbValue &operand2, DbCondition operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(const String &operand1, DbCondition operand2, const String &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(const String &operand1, DbCondition operand2, const DbValue &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(const String &operand1, DbCondition operand2, DbCondition operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(const DbValue &operand1, const String &operand2, const String &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(const DbValue &operand1, const String &operand2, const DbValue &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(const DbValue &operand1, const String &operand2, DbCondition operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(const DbValue &operand1, const DbValue &operand2, const String &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(const DbValue &operand1, const DbValue &operand2, const DbValue &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(const DbValue &operand1, const DbValue &operand2, DbCondition operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(const DbValue &operand1, DbCondition operand2, const String &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(const DbValue &operand1, DbCondition operand2, const DbValue &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(const DbValue &operand1, DbCondition operand2, DbCondition operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(DbCondition operand1, const String &operand2, const String &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(DbCondition operand1, const String &operand2, const DbValue &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(DbCondition operand1, const String &operand2, DbCondition operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(DbCondition operand1, const DbValue &operand2, const String &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(DbCondition operand1, const DbValue &operand2, const DbValue &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(DbCondition operand1, const DbValue &operand2, DbCondition operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(DbCondition operand1, DbCondition operand2, const String &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(DbCondition operand1, DbCondition operand2, const DbValue &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition Between(DbCondition operand1, DbCondition operand2, DbCondition operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Between;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}
	#pragma endregion

	#pragma region NotBetween
		DbCondition NotBetween(const String &operand1, const String &operand2, const String &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(const String &operand1, const String &operand2, const DbValue &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(const String &operand1, const String &operand2, DbCondition operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(const String &operand1, const DbValue &operand2, const String &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(const String &operand1, const DbValue &operand2, const DbValue &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(const String &operand1, const DbValue &operand2, DbCondition operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(const String &operand1, DbCondition operand2, const String &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(const String &operand1, DbCondition operand2, const DbValue &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(const String &operand1, DbCondition operand2, DbCondition operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(const DbValue &operand1, const String &operand2, const String &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(const DbValue &operand1, const String &operand2, const DbValue &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(const DbValue &operand1, const String &operand2, DbCondition operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(const DbValue &operand1, const DbValue &operand2, const String &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(const DbValue &operand1, const DbValue &operand2, const DbValue &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(const DbValue &operand1, const DbValue &operand2, DbCondition operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(const DbValue &operand1, DbCondition operand2, const String &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(const DbValue &operand1, DbCondition operand2, const DbValue &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(const DbValue &operand1, DbCondition operand2, DbCondition operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(DbCondition operand1, const String &operand2, const String &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(DbCondition operand1, const String &operand2, const DbValue &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(DbCondition operand1, const String &operand2, DbCondition operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(DbCondition operand1, const DbValue &operand2, const String &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(DbCondition operand1, const DbValue &operand2, const DbValue &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(DbCondition operand1, const DbValue &operand2, DbCondition operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(DbCondition operand1, DbCondition operand2, const String &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(DbCondition operand1, DbCondition operand2, const DbValue &operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}

		DbCondition NotBetween(DbCondition operand1, DbCondition operand2, DbCondition operand3)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotBetween;
			result->setOperand1(operand1);
			result->setOperand2(operand2);
			result->setOperand3(operand3);
			return result;
		}
	#pragma endregion

	#pragma region In
		DbCondition In(const String &column, const std::vector<DbValue> &values)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::In;
			result->setOperand1(column);
			result->m_aValues = values;
			return result;
		}

		DbCondition In(const DbValue &value, const std::vector<DbValue> &values)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::In;
			result->setOperand1(value);
			result->m_aValues = values;
			return result;
		}

		DbCondition In(DbCondition expression, const std::vector<DbValue> &values)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::In;
			result->setOperand1(expression);
			result->m_aValues = values;
			return result;
		}
	#pragma endregion

	#pragma region NotIn
		DbCondition NotIn(const String &column, const std::vector<DbValue> &values)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotIn;
			result->setOperand1(column);
			result->m_aValues = values;
			return result;
		}

		DbCondition NotIn(const DbValue &value, const std::vector<DbValue> &values)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotIn;
			result->setOperand1(value);
			result->m_aValues = values;
			return result;
		}

		DbCondition NotIn(DbCondition expression, const std::vector<DbValue> &values)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotIn;
			result->setOperand1(expression);
			result->m_aValues = values;
			return result;
		}
	#pragma endregion

	#pragma region Like
		DbCondition Like(const String &column, const String &pattern)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Like;
			result->setOperand1(column);
			result->setOperand2(pattern);
			return result;
		}

		DbCondition Like(const DbValue &value, const String &pattern)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Like;
			result->setOperand1(value);
			result->setOperand2(pattern);
			return result;
		}

		DbCondition Like(DbCondition expression, const String &pattern)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Like;
			result->setOperand1(expression);
			result->setOperand2(pattern);
			return result;
		}
	#pragma endregion

	#pragma region NotLike
		DbCondition NotLike(const String &column, const String &pattern)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotLike;
			result->setOperand1(column);
			result->setOperand2(pattern);
			return result;
		}

		DbCondition NotLike(const DbValue &value, const String &pattern)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotLike;
			result->setOperand1(value);
			result->setOperand2(pattern);
			return result;
		}

		DbCondition NotLike(DbCondition expression, const String &pattern)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotLike;
			result->setOperand1(expression);
			result->setOperand2(pattern);
			return result;
		}
	#pragma endregion

	#pragma region Exists
		DbCondition Exists(const String &query)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::Exists;
			result->setOperand1(query);
			return result;
		}
	#pragma endregion

	#pragma region NotExists
		DbCondition NotExists(const String &query)
		{
			DbCondition result{ new CDbCondition() };
			result->m_eType = CDbCondition::ConditionType::NotExists;
			result->setOperand1(query);
			return result;
		}
	#pragma endregion

	#pragma region Shorts
		DbCondition expr(const String &expression)
		{
			return Expression(expression);
		}

		DbCondition eqcc(const String &operand1, const String &operand2)
		{
			return Equals(operand1, operand2);
		}

		DbCondition eqcv(const String &operand1, const DbValue &operand2)
		{
			return Equals(operand1, operand2);
		}

		DbCondition eqvc(const DbValue &operand1, const String &operand2)
		{
			return Equals(operand1, operand2);
		}

		DbCondition eqvv(const DbValue &operand1, const DbValue &operand2)
		{
			return Equals(operand1, operand2);
		}

		DbCondition eqce(const String &operand1, const String &operand2)
		{
			return Equals(operand1, expr(operand2));
		}

		DbCondition eqec(const String &operand1, const String &operand2)
		{
			return Equals(expr(operand1), operand2);
		}

		DbCondition eqee(const String &operand1, const String &operand2)
		{
			return Equals(expr(operand1), expr(operand2));
		}

		DbCondition eqve(const DbValue &operand1, const String &operand2)
		{
			return Equals(operand1, expr(operand2));
		}

		DbCondition eqev(const String &operand1, const DbValue &operand2)
		{
			return Equals(expr(operand1), operand2);
		}
		
		DbCondition necc(const String &operand1, const String &operand2)
		{
			return NotEquals(operand1, operand2);
		}
		
		DbCondition necv(const String &operand1, const DbValue &operand2)
		{
			return NotEquals(operand1, operand2);
		}
		
		DbCondition nevc(const DbValue &operand1, const String &operand2)
		{
			return NotEquals(operand1, operand2);
		}
		
		DbCondition nevv(const DbValue &operand1, const DbValue &operand2)
		{
			return NotEquals(operand1, operand2);
		}
		
		DbCondition nece(const String &operand1, const String &operand2)
		{
			return NotEquals(operand1, expr(operand2));
		}
		
		DbCondition neec(const String &operand1, const String &operand2)
		{
			return NotEquals(expr(operand1), operand2);
		}
		
		DbCondition neee(const String &operand1, const String &operand2)
		{
			return NotEquals(expr(operand1), expr(operand2));
		}
		
		DbCondition neve(const DbValue &operand1, const String &operand2)
		{
			return NotEquals(operand1, expr(operand2));
		}
		
		DbCondition neev(const String &operand1, const DbValue &operand2)
		{
			return NotEquals(expr(operand1), operand2);
		}
		
		DbCondition gtcc(const String &operand1, const String &operand2)
		{
			return Greater(operand1, operand2);
		}
		
		DbCondition gtcv(const String &operand1, const DbValue &operand2)
		{
			return Greater(operand1, operand2);
		}
		
		DbCondition gtvc(const DbValue &operand1, const String &operand2)
		{
			return Greater(operand1, operand2);
		}
		
		DbCondition gtvv(const DbValue &operand1, const DbValue &operand2)
		{
			return Greater(operand1, operand2);
		}
		
		DbCondition gtce(const String &operand1, const String &operand2)
		{
			return Greater(operand1, expr(operand2));
		}
		
		DbCondition gtec(const String &operand1, const String &operand2)
		{
			return Greater(expr(operand1), operand2);
		}
		
		DbCondition gtee(const String &operand1, const String &operand2)
		{
			return Greater(expr(operand1), expr(operand2));
		}
		
		DbCondition gtve(const DbValue &operand1, const String &operand2)
		{
			return Greater(operand1, expr(operand2));
		}
		
		DbCondition gtev(const String &operand1, const DbValue &operand2)
		{
			return Greater(expr(operand1), operand2);
		}
		
		DbCondition gecc(const String &operand1, const String &operand2)
		{
			return GreaterEquals(operand1, operand2);
		}
		
		DbCondition gecv(const String &operand1, const DbValue &operand2)
		{
			return GreaterEquals(operand1, operand2);
		}
		
		DbCondition gevc(const DbValue &operand1, const String &operand2)
		{
			return GreaterEquals(operand1, operand2);
		}
		
		DbCondition gevv(const DbValue &operand1, const DbValue &operand2)
		{
			return GreaterEquals(operand1, operand2);
		}
		
		DbCondition gece(const String &operand1, const String &operand2)
		{
			return GreaterEquals(operand1, expr(operand2));
		}
		
		DbCondition geec(const String &operand1, const String &operand2)
		{
			return GreaterEquals(expr(operand1), operand2);
		}
		
		DbCondition geee(const String &operand1, const String &operand2)
		{
			return GreaterEquals(expr(operand1), expr(operand2));
		}
		
		DbCondition geve(const DbValue &operand1, const String &operand2)
		{
			return GreaterEquals(operand1, expr(operand2));
		}
		
		DbCondition geev(const String &operand1, const DbValue &operand2)
		{
			return GreaterEquals(expr(operand1), operand2);
		}
		
		DbCondition lscc(const String &operand1, const String &operand2)
		{
			return Less(operand1, operand2);
		}
		
		DbCondition lscv(const String &operand1, const DbValue &operand2)
		{
			return Less(operand1, operand2);
		}
		
		DbCondition lsvc(const DbValue &operand1, const String &operand2)
		{
			return Less(operand1, operand2);
		}
		
		DbCondition lsvv(const DbValue &operand1, const DbValue &operand2)
		{
			return Less(operand1, operand2);
		}
		
		DbCondition lsce(const String &operand1, const String &operand2)
		{
			return Less(operand1, expr(operand2));
		}
		
		DbCondition lsec(const String &operand1, const String &operand2)
		{
			return Less(expr(operand1), operand2);
		}
		
		DbCondition lsee(const String &operand1, const String &operand2)
		{
			return Less(expr(operand1), expr(operand2));
		}
		
		DbCondition lsve(const DbValue &operand1, const String &operand2)
		{
			return Less(operand1, expr(operand2));
		}
		
		DbCondition lsev(const String &operand1, const DbValue &operand2)
		{
			return Less(expr(operand1), operand2);
		}
		
		DbCondition lecc(const String &operand1, const String &operand2)
		{
			return LessEquals(operand1, operand2);
		}
		
		DbCondition lecv(const String &operand1, const DbValue &operand2)
		{
			return LessEquals(operand1, operand2);
		}
		
		DbCondition levc(const DbValue &operand1, const String &operand2)
		{
			return LessEquals(operand1, operand2);
		}
		
		DbCondition levv(const DbValue &operand1, const DbValue &operand2)
		{
			return LessEquals(operand1, operand2);
		}
		
		DbCondition lece(const String &operand1, const String &operand2)
		{
			return LessEquals(operand1, expr(operand2));
		}
		
		DbCondition leec(const String &operand1, const String &operand2)
		{
			return LessEquals(expr(operand1), operand2);
		}
		
		DbCondition leee(const String &operand1, const String &operand2)
		{
			return LessEquals(expr(operand1), expr(operand2));
		}
		
		DbCondition leve(const DbValue &operand1, const String &operand2)
		{
			return LessEquals(operand1, expr(operand2));
		}
		
		DbCondition leev(const String &operand1, const DbValue &operand2)
		{
			return LessEquals(expr(operand1), operand2);
		}
		
		DbCondition a(DbCondition operand1, DbCondition operand2)
		{
			return And(operand1, operand2);
		}
		
		DbCondition o(DbCondition operand1, DbCondition operand2)
		{
			return Or(operand1, operand2);
		}
		
		DbCondition n(DbCondition operand)
		{
			return Not(operand);
		}
		
		DbCondition btccc(const String &operand1, const String &operand2, const String &operand3)
		{
			return Between(operand1, operand2, operand3);
		}
		
		DbCondition btccv(const String &operand1, const String &operand2, const DbValue &operand3)
		{
			return Between(operand1, operand2, operand3);
		}
		
		DbCondition btcce(const String &operand1, const String &operand2, const String &operand3)
		{
			return Between(operand1, operand2, expr(operand3));
		}
		
		DbCondition btcvc(const String &operand1, const DbValue &operand2, const String &operand3)
		{
			return Between(operand1, operand2, operand3);
		}
		
		DbCondition btcvv(const String &operand1, const DbValue &operand2, const DbValue &operand3)
		{
			return Between(operand1, operand2, operand3);
		}
		
		DbCondition btcve(const String &operand1, const DbValue &operand2, const String &operand3)
		{
			return Between(operand1, operand2, expr(operand3));
		}
		
		DbCondition btcec(const String &operand1, const String &operand2, const String &operand3)
		{
			return Between(operand1, expr(operand2), operand3);
		}
		
		DbCondition btcev(const String &operand1, const String &operand2, const DbValue &operand3)
		{
			return Between(operand1, expr(operand2), operand3);
		}
		
		DbCondition btcee(const String &operand1, const String &operand2, const String &operand3)
		{
			return Between(operand1, expr(operand2), expr(operand3));
		}
		
		DbCondition btvcc(const DbValue &operand1, const String &operand2, const String &operand3)
		{
			return Between(operand1, operand2, operand3);
		}
		
		DbCondition btvcv(const DbValue &operand1, const String &operand2, const DbValue &operand3)
		{
			return Between(operand1, operand2, operand3);
		}
		
		DbCondition btvce(const DbValue &operand1, const String &operand2, const String &operand3)
		{
			return Between(operand1, operand2, expr(operand3));
		}
		
		DbCondition btvvc(const DbValue &operand1, const DbValue &operand2, const String &operand3)
		{
			return Between(operand1, operand2, operand3);
		}
		
		DbCondition btvvv(const DbValue &operand1, const DbValue &operand2, const DbValue &operand3)
		{
			return Between(operand1, operand2, operand3);
		}
		
		DbCondition btvve(const DbValue &operand1, const DbValue &operand2, const String &operand3)
		{
			return Between(operand1, operand2, expr(operand3));
		}
		
		DbCondition btvec(const DbValue &operand1, const String &operand2, const String &operand3)
		{
			return Between(operand1, expr(operand2), operand3);
		}
		
		DbCondition btvev(const DbValue &operand1, const String &operand2, const DbValue &operand3)
		{
			return Between(operand1, expr(operand2), operand3);
		}
		
		DbCondition btvee(const DbValue &operand1, const String &operand2, const String &operand3)
		{
			return Between(operand1, expr(operand2), expr(operand3));
		}
		
		DbCondition btecc(const String &operand1, const String &operand2, const String &operand3)
		{
			return Between(expr(operand1), operand2, operand3);
		}
		
		DbCondition btecv(const String &operand1, const String &operand2, const DbValue &operand3)
		{
			return Between(expr(operand1), operand2, operand3);
		}
		
		DbCondition btece(const String &operand1, const String &operand2, const String &operand3)
		{
			return Between(expr(operand1), operand2, expr(operand3));
		}
		
		DbCondition btevc(const String &operand1, const DbValue &operand2, const String &operand3)
		{
			return Between(expr(operand1), operand2, operand3);
		}
		
		DbCondition btevv(const String &operand1, const DbValue &operand2, const DbValue &operand3)
		{
			return Between(expr(operand1), operand2, operand3);
		}
		
		DbCondition bteve(const String &operand1, const DbValue &operand2, const String &operand3)
		{
			return Between(expr(operand1), operand2, expr(operand3));
		}
		
		DbCondition bteec(const String &operand1, const String &operand2, const String &operand3)
		{
			return Between(expr(operand1), expr(operand2), operand3);
		}
		
		DbCondition bteev(const String &operand1, const String &operand2, const DbValue &operand3)
		{
			return Between(expr(operand1), expr(operand2), operand3);
		}
		
		DbCondition bteee(const String &operand1, const String &operand2, const String &operand3)
		{
			return Between(expr(operand1), expr(operand2), expr(operand3));
		}
		
		DbCondition nbccc(const String &operand1, const String &operand2, const String &operand3)
		{
			return NotBetween(operand1, operand2, operand3);
		}
		
		DbCondition nbccv(const String &operand1, const String &operand2, const DbValue &operand3)
		{
			return NotBetween(operand1, operand2, operand3);
		}
		
		DbCondition nbcce(const String &operand1, const String &operand2, const String &operand3)
		{
			return NotBetween(operand1, operand2, expr(operand3));
		}
		
		DbCondition nbcvc(const String &operand1, const DbValue &operand2, const String &operand3)
		{
			return NotBetween(operand1, operand2, operand3);
		}
		
		DbCondition nbcvv(const String &operand1, const DbValue &operand2, const DbValue &operand3)
		{
			return NotBetween(operand1, operand2, operand3);
		}
		
		DbCondition nbcve(const String &operand1, const DbValue &operand2, const String &operand3)
		{
			return NotBetween(operand1, operand2, expr(operand3));
		}
		
		DbCondition nbcec(const String &operand1, const String &operand2, const String &operand3)
		{
			return NotBetween(operand1, expr(operand2), operand3);
		}
		
		DbCondition nbcev(const String &operand1, const String &operand2, const DbValue &operand3)
		{
			return NotBetween(operand1, expr(operand2), operand3);
		}
		
		DbCondition nbcee(const String &operand1, const String &operand2, const String &operand3)
		{
			return NotBetween(operand1, expr(operand2), expr(operand3));
		}
		
		DbCondition nbvcc(const DbValue &operand1, const String &operand2, const String &operand3)
		{
			return NotBetween(operand1, operand2, operand3);
		}
		
		DbCondition nbvcv(const DbValue &operand1, const String &operand2, const DbValue &operand3)
		{
			return NotBetween(operand1, operand2, operand3);
		}
		
		DbCondition nbvce(const DbValue &operand1, const String &operand2, const String &operand3)
		{
			return NotBetween(operand1, operand2, expr(operand3));
		}
		
		DbCondition nbvvc(const DbValue &operand1, const DbValue &operand2, const String &operand3)
		{
			return NotBetween(operand1, operand2, operand3);
		}
		
		DbCondition nbvvv(const DbValue &operand1, const DbValue &operand2, const DbValue &operand3)
		{
			return NotBetween(operand1, operand2, operand3);
		}
		
		DbCondition nbvve(const DbValue &operand1, const DbValue &operand2, const String &operand3)
		{
			return NotBetween(operand1, operand2, expr(operand3));
		}
		
		DbCondition nbvec(const DbValue &operand1, const String &operand2, const String &operand3)
		{
			return NotBetween(operand1, expr(operand2), operand3);
		}
		
		DbCondition nbvev(const DbValue &operand1, const String &operand2, const DbValue &operand3)
		{
			return NotBetween(operand1, expr(operand2), operand3);
		}
		
		DbCondition nbvee(const DbValue &operand1, const String &operand2, const String &operand3)
		{
			return NotBetween(operand1, expr(operand2), expr(operand3));
		}
		
		DbCondition nbecc(const String &operand1, const String &operand2, const String &operand3)
		{
			return NotBetween(expr(operand1), operand2, operand3);
		}
		
		DbCondition nbecv(const String &operand1, const String &operand2, const DbValue &operand3)
		{
			return NotBetween(expr(operand1), operand2, operand3);
		}
		
		DbCondition nbece(const String &operand1, const String &operand2, const String &operand3)
		{
			return NotBetween(expr(operand1), operand2, expr(operand3));
		}
		
		DbCondition nbevc(const String &operand1, const DbValue &operand2, const String &operand3)
		{
			return NotBetween(expr(operand1), operand2, operand3);
		}
		
		DbCondition nbevv(const String &operand1, const DbValue &operand2, const DbValue &operand3)
		{
			return NotBetween(expr(operand1), operand2, operand3);
		}
		
		DbCondition nbeve(const String &operand1, const DbValue &operand2, const String &operand3)
		{
			return NotBetween(expr(operand1), operand2, expr(operand3));
		}
		
		DbCondition nbeec(const String &operand1, const String &operand2, const String &operand3)
		{
			return NotBetween(expr(operand1), expr(operand2), operand3);
		}
		
		DbCondition nbeev(const String &operand1, const String &operand2, const DbValue &operand3)
		{
			return NotBetween(expr(operand1), expr(operand2), operand3);
		}
		
		DbCondition nbeee(const String &operand1, const String &operand2, const String &operand3)
		{
			return NotBetween(expr(operand1), expr(operand2), expr(operand3));
		}
		
		DbCondition inc(const String &column, const std::vector<DbValue> &values)
		{
			return In(column, values);
		}
		
		DbCondition inv(const DbValue &value, const std::vector<DbValue> &values)
		{
			return In(value, values);
		}
		
		DbCondition ine(const String &expression, const std::vector<DbValue> &values)
		{
			return In(expr(expression), values);
		}
		
		DbCondition nic(const String &column, const std::vector<DbValue> &values)
		{
			return NotIn(column, values);
		}
		
		DbCondition niv(const DbValue &value, const std::vector<DbValue> &values)
		{
			return NotIn(value, values);
		}
		
		DbCondition nie(const String &expression, const std::vector<DbValue> &values)
		{
			return NotIn(expr(expression), values);
		}
		
		DbCondition lkc(const String &column, const String &pattern)
		{
			return Like(column, pattern);
		}
		
		DbCondition lkv(const DbValue &value, const String &pattern)
		{
			return Like(value, pattern);
		}
		
		DbCondition lke(const String &expression, const String &pattern)
		{
			return Like(expr(expression), pattern);
		}
		
		DbCondition nlc(const String &column, const String &pattern)
		{
			return NotLike(column, pattern);
		}
		
		DbCondition nlv(const DbValue &value, const String &pattern)
		{
			return NotLike(value, pattern);
		}
		
		DbCondition nle(const String &expression, const String &pattern)
		{
			return NotLike(expr(expression), pattern);
		}
		
		DbCondition ex(const String &query)
		{
			return Exists(query);
		}
		
		DbCondition ne(const String &query)
		{
			return NotExists(query);
		}
	#pragma endregion
	}

#pragma region Setters
	void CDbCondition::setOperand1(const String &column)
	{
		m_eOperand1Type = OperandType::Column;
		m_sColumn1 = column;
	}

	void CDbCondition::setOperand1(const DbValue &value)
	{
		m_eOperand1Type = OperandType::Value;
		m_sValue1 = value;
	}

	void CDbCondition::setOperand1(DbCondition expression)
	{
		m_eOperand1Type = OperandType::Expression;
		m_pOperand1 = expression;
	}

	void CDbCondition::setOperand2(const String &column)
	{
		m_eOperand2Type = OperandType::Column;
		m_sColumn2 = column;
	}

	void CDbCondition::setOperand2(const DbValue &value)
	{
		m_eOperand2Type = OperandType::Value;
		m_sValue2 = value;
	}

	void CDbCondition::setOperand2(DbCondition expression)
	{
		m_eOperand2Type = OperandType::Expression;
		m_pOperand2 = expression;
	}

	void CDbCondition::setOperand3(const String &column)
	{
		m_eOperand3Type = OperandType::Column;
		m_sColumn3 = column;
	}

	void CDbCondition::setOperand3(const DbValue &value)
	{
		m_eOperand3Type = OperandType::Value;
		m_sValue3 = value;
	}

	void CDbCondition::setOperand3(DbCondition expression)
	{
		m_eOperand3Type = OperandType::Expression;
		m_pOperand3 = expression;
	}
#pragma endregion
}
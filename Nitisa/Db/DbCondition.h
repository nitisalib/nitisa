// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Releasable.h"
#include "../Core/ReleasablePtr.h"
#include "../Core/Strings.h"
#include "DbValue.h"
#include <vector>

namespace nitisa
{
	class CDbCondition;

	using DbCondition = ReleasablePtr<CDbCondition>;
	using DbConditions = std::vector<DbCondition>;

	namespace db
	{
		DbCondition Expression(const String &expression);
		DbCondition Equals(const String &operand1, const String &operand2); // column1 = column2
		DbCondition Equals(const String &operand1, const DbValue &operand2); // column = value
		DbCondition Equals(const DbValue &operand1, const String &operand2); // value = column
		DbCondition Equals(const DbValue &operand1, const DbValue &operand2); // value1 = value2
		DbCondition Equals(const String &operand1, DbCondition operand2); // column = expression
		DbCondition Equals(DbCondition operand1, const String &operand2); // expression = column
		DbCondition Equals(DbCondition operand1, DbCondition operand2); // expression1 = expression2
		DbCondition Equals(const DbValue &operand1, DbCondition operand2); // value = expression
		DbCondition Equals(DbCondition operand1, const DbValue &operand2); // expression = value
		DbCondition NotEquals(const String &operand1, const String &operand2); // column1 != column2
		DbCondition NotEquals(const String &operand1, const DbValue &operand2); // column != value
		DbCondition NotEquals(const DbValue &operand1, const String &operand2); // value != column
		DbCondition NotEquals(const DbValue &operand1, const DbValue &operand2); // value1 != value2
		DbCondition NotEquals(const String &operand1, DbCondition operand2); // column != expression
		DbCondition NotEquals(DbCondition operand1, const String &operand2); // expression != column
		DbCondition NotEquals(DbCondition operand1, DbCondition operand2); // expression1 != expression2
		DbCondition NotEquals(const DbValue &operand1, DbCondition operand2); // value != expression
		DbCondition NotEquals(DbCondition operand1, const DbValue &operand2); // expression != value
		DbCondition Greater(const String &operand1, const String &operand2); // column1 > column2
		DbCondition Greater(const String &operand1, const DbValue &operand2); // column > value
		DbCondition Greater(const DbValue &operand1, const String &operand2); // value > column
		DbCondition Greater(const DbValue &operand1, const DbValue &operand2); // value1 > value2
		DbCondition Greater(const String &operand1, DbCondition operand2); // column > expression
		DbCondition Greater(DbCondition operand1, const String &operand2); // expression > column
		DbCondition Greater(DbCondition operand1, DbCondition operand2); // expression1 > expression2
		DbCondition Greater(const DbValue &operand1, DbCondition operand2); // value > expression
		DbCondition Greater(DbCondition operand1, const DbValue &operand2); // expression > value
		DbCondition GreaterEquals(const String &operand1, const String &operand2); // column1 >= column2
		DbCondition GreaterEquals(const String &operand1, const DbValue &operand2); // column >= value
		DbCondition GreaterEquals(const DbValue &operand1, const String &operand2); // value >= column
		DbCondition GreaterEquals(const DbValue &operand1, const DbValue &operand2); // value1 >= value2
		DbCondition GreaterEquals(const String &operand1, DbCondition operand2); // column >= expression
		DbCondition GreaterEquals(DbCondition operand1, const String &operand2); // expression >= column
		DbCondition GreaterEquals(DbCondition operand1, DbCondition operand2); // expression1 >= expression2
		DbCondition GreaterEquals(const DbValue &operand1, DbCondition operand2); // value >= expression
		DbCondition GreaterEquals(DbCondition operand1, const DbValue &operand2); // expression >= value
		DbCondition Less(const String &operand1, const String &operand2); // column1 < column2
		DbCondition Less(const String &operand1, const DbValue &operand2); // column < value
		DbCondition Less(const DbValue &operand1, const String &operand2); // value < column
		DbCondition Less(const DbValue &operand1, const DbValue &operand2); // value1 < value2
		DbCondition Less(const String &operand1, DbCondition operand2); // column < expression
		DbCondition Less(DbCondition operand1, const String &operand2); // expression < column
		DbCondition Less(DbCondition operand1, DbCondition operand2); // expression1 < expression2
		DbCondition Less(const DbValue &operand1, DbCondition operand2); // value < expression
		DbCondition Less(DbCondition operand1, const DbValue &operand2); // expression < value
		DbCondition LessEquals(const String &operand1, const String &operand2); // column1 <= column2
		DbCondition LessEquals(const String &operand1, const DbValue &operand2); // column <= value
		DbCondition LessEquals(const DbValue &operand1, const String &operand2); // value <= column
		DbCondition LessEquals(const DbValue &operand1, const DbValue &operand2); // value1 <= value2
		DbCondition LessEquals(const String &operand1, DbCondition operand2); // column <= expression
		DbCondition LessEquals(DbCondition operand1, const String &operand2); // expression <= column
		DbCondition LessEquals(DbCondition operand1, DbCondition operand2); // expression1 <= expression2
		DbCondition LessEquals(const DbValue &operand1, DbCondition operand2); // value <= expression
		DbCondition LessEquals(DbCondition operand1, const DbValue &operand2); // expression <= value
		DbCondition And(DbCondition operand1, DbCondition operand2);
		DbCondition Or(DbCondition operand1, DbCondition operand2);
		DbCondition Not(DbCondition operand);
		DbCondition Between(const String &operand1, const String &operand2, const String &operand3); // column1 BETWEEN column2 AND column3
		DbCondition Between(const String &operand1, const String &operand2, const DbValue &operand3); // column1 BETWEEN column2 AND value3
		DbCondition Between(const String &operand1, const String &operand2, DbCondition operand3); // column1 BETWEEN column2 AND expression3
		DbCondition Between(const String &operand1, const DbValue &operand2, const String &operand3); // column1 BETWEEN value2 AND column3
		DbCondition Between(const String &operand1, const DbValue &operand2, const DbValue &operand3); // column1 BETWEEN value2 AND value3
		DbCondition Between(const String &operand1, const DbValue &operand2, DbCondition operand3); // column1 BETWEEN value2 AND expression3
		DbCondition Between(const String &operand1, DbCondition operand2, const String &operand3); // column1 BETWEEN expression2 AND column3
		DbCondition Between(const String &operand1, DbCondition operand2, const DbValue &operand3); // column1 BETWEEN expression2 AND value3
		DbCondition Between(const String &operand1, DbCondition operand2, DbCondition operand3); // column1 BETWEEN expression2 AND expression3
		DbCondition Between(const DbValue &operand1, const String &operand2, const String &operand3); // value1 BETWEEN column2 AND column3
		DbCondition Between(const DbValue &operand1, const String &operand2, const DbValue &operand3); // value1 BETWEEN column2 AND value3
		DbCondition Between(const DbValue &operand1, const String &operand2, DbCondition operand3); // value1 BETWEEN column2 AND expression3
		DbCondition Between(const DbValue &operand1, const DbValue &operand2, const String &operand3); // value1 BETWEEN value2 AND column3
		DbCondition Between(const DbValue &operand1, const DbValue &operand2, const DbValue &operand3); // value1 BETWEEN value2 AND value3
		DbCondition Between(const DbValue &operand1, const DbValue &operand2, DbCondition operand3); // value1 BETWEEN value2 AND expression3
		DbCondition Between(const DbValue &operand1, DbCondition operand2, const String &operand3); // value1 BETWEEN expression2 AND column3
		DbCondition Between(const DbValue &operand1, DbCondition operand2, const DbValue &operand3); // value1 BETWEEN expression2 AND value3
		DbCondition Between(const DbValue &operand1, DbCondition operand2, DbCondition operand3); // value1 BETWEEN expression2 AND expression3
		DbCondition Between(DbCondition operand1, const String &operand2, const String &operand3); // expression1 BETWEEN column2 AND column3
		DbCondition Between(DbCondition operand1, const String &operand2, const DbValue &operand3); // expression1 BETWEEN column2 AND value3
		DbCondition Between(DbCondition operand1, const String &operand2, DbCondition operand3); // expression1 BETWEEN column2 AND expression3
		DbCondition Between(DbCondition operand1, const DbValue &operand2, const String &operand3); // expression1 BETWEEN value2 AND column3
		DbCondition Between(DbCondition operand1, const DbValue &operand2, const DbValue &operand3); // expression1 BETWEEN value2 AND value3
		DbCondition Between(DbCondition operand1, const DbValue &operand2, DbCondition operand3); // expression1 BETWEEN value2 AND expression3
		DbCondition Between(DbCondition operand1, DbCondition operand2, const String &operand3); // expression1 BETWEEN expression2 AND column3
		DbCondition Between(DbCondition operand1, DbCondition operand2, const DbValue &operand3); // expression1 BETWEEN expression2 AND value3
		DbCondition Between(DbCondition operand1, DbCondition operand2, DbCondition operand3); // expression1 BETWEEN expression2 AND expression3
		DbCondition NotBetween(const String &operand1, const String &operand2, const String &operand3); // column1 NOT BETWEEN column2 AND column3
		DbCondition NotBetween(const String &operand1, const String &operand2, const DbValue &operand3); // column1 NOT BETWEEN column2 AND value3
		DbCondition NotBetween(const String &operand1, const String &operand2, DbCondition operand3); // column1 NOT BETWEEN column2 AND expression3
		DbCondition NotBetween(const String &operand1, const DbValue &operand2, const String &operand3); // column1 NOT BETWEEN value2 AND column3
		DbCondition NotBetween(const String &operand1, const DbValue &operand2, const DbValue &operand3); // column1 NOT BETWEEN value2 AND value3
		DbCondition NotBetween(const String &operand1, const DbValue &operand2, DbCondition operand3); // column1 NOT BETWEEN value2 AND expression3
		DbCondition NotBetween(const String &operand1, DbCondition operand2, const String &operand3); // column1 NOT BETWEEN expression2 AND column3
		DbCondition NotBetween(const String &operand1, DbCondition operand2, const DbValue &operand3); // column1 NOT BETWEEN expression2 AND value3
		DbCondition NotBetween(const String &operand1, DbCondition operand2, DbCondition operand3); // column1 NOT BETWEEN expression2 AND expression3
		DbCondition NotBetween(const DbValue &operand1, const String &operand2, const String &operand3); // value1 NOT BETWEEN column2 AND column3
		DbCondition NotBetween(const DbValue &operand1, const String &operand2, const DbValue &operand3); // value1 NOT BETWEEN column2 AND value3
		DbCondition NotBetween(const DbValue &operand1, const String &operand2, DbCondition operand3); // value1 NOT BETWEEN column2 AND expression3
		DbCondition NotBetween(const DbValue &operand1, const DbValue &operand2, const String &operand3); // value1 NOT BETWEEN value2 AND column3
		DbCondition NotBetween(const DbValue &operand1, const DbValue &operand2, const DbValue &operand3); // value1 NOT BETWEEN value2 AND value3
		DbCondition NotBetween(const DbValue &operand1, const DbValue &operand2, DbCondition operand3); // value1 NOT BETWEEN value2 AND expression3
		DbCondition NotBetween(const DbValue &operand1, DbCondition operand2, const String &operand3); // value1 NOT BETWEEN expression2 AND column3
		DbCondition NotBetween(const DbValue &operand1, DbCondition operand2, const DbValue &operand3); // value1 NOT BETWEEN expression2 AND value3
		DbCondition NotBetween(const DbValue &operand1, DbCondition operand2, DbCondition operand3); // value1 NOT BETWEEN expression2 AND expression3
		DbCondition NotBetween(DbCondition operand1, const String &operand2, const String &operand3); // expression1 NOT BETWEEN column2 AND column3
		DbCondition NotBetween(DbCondition operand1, const String &operand2, const DbValue &operand3); // expression1 NOT BETWEEN column2 AND value3
		DbCondition NotBetween(DbCondition operand1, const String &operand2, DbCondition operand3); // expression1 NOT BETWEEN column2 AND expression3
		DbCondition NotBetween(DbCondition operand1, const DbValue &operand2, const String &operand3); // expression1 NOT BETWEEN value2 AND column3
		DbCondition NotBetween(DbCondition operand1, const DbValue &operand2, const DbValue &operand3); // expression1 NOT BETWEEN value2 AND value3
		DbCondition NotBetween(DbCondition operand1, const DbValue &operand2, DbCondition operand3); // expression1 NOT BETWEEN value2 AND expression3
		DbCondition NotBetween(DbCondition operand1, DbCondition operand2, const String &operand3); // expression1 NOT BETWEEN expression2 AND column3
		DbCondition NotBetween(DbCondition operand1, DbCondition operand2, const DbValue &operand3); // expression1 NOT BETWEEN expression2 AND value3
		DbCondition NotBetween(DbCondition operand1, DbCondition operand2, DbCondition operand3); // expression1 NOT BETWEEN expression2 AND expression3
		DbCondition In(const String &column, const std::vector<DbValue> &values); // column IN (...)
		DbCondition In(const DbValue &value, const std::vector<DbValue> &values); // value IN (...)
		DbCondition In(DbCondition expression, const std::vector<DbValue> &values); // expression IN (...)
		DbCondition NotIn(const String &column, const std::vector<DbValue> &values); // column NOT IN (...)
		DbCondition NotIn(const DbValue &value, const std::vector<DbValue> &values); // value NOT IN (...)
		DbCondition NotIn(DbCondition expression, const std::vector<DbValue> &values); // expression NOT IN (...)
		DbCondition Like(const String &column, const String &pattern); // column LIKE pattern
		DbCondition Like(const DbValue &value, const String &pattern); // value LIKE pattern
		DbCondition Like(DbCondition expression, const String &pattern); // expression LIKE pattern
		DbCondition NotLike(const String &column, const String &pattern); // column NOT LIKE pattern
		DbCondition NotLike(const DbValue &value, const String &pattern); // value NOT LIKE pattern
		DbCondition NotLike(DbCondition expression, const String &pattern); // expression NOT LIKE pattern
		DbCondition Exists(const String &query);
		DbCondition NotExists(const String &query);

		// Shorts
		DbCondition expr(const String &expression);
		DbCondition eqcc(const String &operand1, const String &operand2);
		DbCondition eqcv(const String &operand1, const DbValue &operand2);
		DbCondition eqvc(const DbValue &operand1, const String &operand2);
		DbCondition eqvv(const DbValue &operand1, const DbValue &operand2);
		DbCondition eqce(const String &operand1, const String &operand2);
		DbCondition eqec(const String &operand1, const String &operand2);
		DbCondition eqee(const String &operand1, const String &operand2);
		DbCondition eqve(const DbValue &operand1, const String &operand2);
		DbCondition eqev(const String &operand1, const DbValue &operand2);
		DbCondition necc(const String &operand1, const String &operand2);
		DbCondition necv(const String &operand1, const DbValue &operand2);
		DbCondition nevc(const DbValue &operand1, const String &operand2);
		DbCondition nevv(const DbValue &operand1, const DbValue &operand2);
		DbCondition nece(const String &operand1, const String &operand2);
		DbCondition neec(const String &operand1, const String &operand2);
		DbCondition neee(const String &operand1, const String &operand2);
		DbCondition neve(const DbValue &operand1, const String &operand2);
		DbCondition neev(const String &operand1, const DbValue &operand2);
		DbCondition gtcc(const String &operand1, const String &operand2);
		DbCondition gtcv(const String &operand1, const DbValue &operand2);
		DbCondition gtvc(const DbValue &operand1, const String &operand2);
		DbCondition gtvv(const DbValue &operand1, const DbValue &operand2);
		DbCondition gtce(const String &operand1, const String &operand2);
		DbCondition gtec(const String &operand1, const String &operand2);
		DbCondition gtee(const String &operand1, const String &operand2);
		DbCondition gtve(const DbValue &operand1, const String &operand2);
		DbCondition gtev(const String &operand1, const DbValue &operand2);
		DbCondition gecc(const String &operand1, const String &operand2);
		DbCondition gecv(const String &operand1, const DbValue &operand2);
		DbCondition gevc(const DbValue &operand1, const String &operand2);
		DbCondition gevv(const DbValue &operand1, const DbValue &operand2);
		DbCondition gece(const String &operand1, const String &operand2);
		DbCondition geec(const String &operand1, const String &operand2);
		DbCondition geee(const String &operand1, const String &operand2);
		DbCondition geve(const DbValue &operand1, const String &operand2);
		DbCondition geev(const String &operand1, const DbValue &operand2);
		DbCondition lscc(const String &operand1, const String &operand2);
		DbCondition lscv(const String &operand1, const DbValue &operand2);
		DbCondition lsvc(const DbValue &operand1, const String &operand2);
		DbCondition lsvv(const DbValue &operand1, const DbValue &operand2);
		DbCondition lsce(const String &operand1, const String &operand2);
		DbCondition lsec(const String &operand1, const String &operand2);
		DbCondition lsee(const String &operand1, const String &operand2);
		DbCondition lsve(const DbValue &operand1, const String &operand2);
		DbCondition lsev(const String &operand1, const DbValue &operand2);
		DbCondition lecc(const String &operand1, const String &operand2);
		DbCondition lecv(const String &operand1, const DbValue &operand2);
		DbCondition levc(const DbValue &operand1, const String &operand2);
		DbCondition levv(const DbValue &operand1, const DbValue &operand2);
		DbCondition lece(const String &operand1, const String &operand2);
		DbCondition leec(const String &operand1, const String &operand2);
		DbCondition leee(const String &operand1, const String &operand2);
		DbCondition leve(const DbValue &operand1, const String &operand2);
		DbCondition leev(const String &operand1, const DbValue &operand2);
		DbCondition a(DbCondition operand1, DbCondition operand2);
		DbCondition o(DbCondition operand1, DbCondition operand2);
		DbCondition n(DbCondition operand);
		DbCondition btccc(const String &operand1, const String &operand2, const String &operand3);
		DbCondition btccv(const String &operand1, const String &operand2, const DbValue &operand3);
		DbCondition btcce(const String &operand1, const String &operand2, const String &operand3);
		DbCondition btcvc(const String &operand1, const DbValue &operand2, const String &operand3);
		DbCondition btcvv(const String &operand1, const DbValue &operand2, const DbValue &operand3);
		DbCondition btcve(const String &operand1, const DbValue &operand2, const String &operand3);
		DbCondition btcec(const String &operand1, const String &operand2, const String &operand3);
		DbCondition btcev(const String &operand1, const String &operand2, const DbValue &operand3);
		DbCondition btcee(const String &operand1, const String &operand2, const String &operand3);
		DbCondition btvcc(const DbValue &operand1, const String &operand2, const String &operand3);
		DbCondition btvcv(const DbValue &operand1, const String &operand2, const DbValue &operand3);
		DbCondition btvce(const DbValue &operand1, const String &operand2, const String &operand3);
		DbCondition btvvc(const DbValue &operand1, const DbValue &operand2, const String &operand3);
		DbCondition btvvv(const DbValue &operand1, const DbValue &operand2, const DbValue &operand3);
		DbCondition btvve(const DbValue &operand1, const DbValue &operand2, const String &operand3);
		DbCondition btvec(const DbValue &operand1, const String &operand2, const String &operand3);
		DbCondition btvev(const DbValue &operand1, const String &operand2, const DbValue &operand3);
		DbCondition btvee(const DbValue &operand1, const String &operand2, const String &operand3);
		DbCondition btecc(const String &operand1, const String &operand2, const String &operand3);
		DbCondition btecv(const String &operand1, const String &operand2, const DbValue &operand3);
		DbCondition btece(const String &operand1, const String &operand2, const String &operand3);
		DbCondition btevc(const String &operand1, const DbValue &operand2, const String &operand3);
		DbCondition btevv(const String &operand1, const DbValue &operand2, const DbValue &operand3);
		DbCondition bteve(const String &operand1, const DbValue &operand2, const String &operand3);
		DbCondition bteec(const String &operand1, const String &operand2, const String &operand3);
		DbCondition bteev(const String &operand1, const String &operand2, const DbValue &operand3);
		DbCondition bteee(const String &operand1, const String &operand2, const String &operand3);
		DbCondition nbccc(const String &operand1, const String &operand2, const String &operand3);
		DbCondition nbccv(const String &operand1, const String &operand2, const DbValue &operand3);
		DbCondition nbcce(const String &operand1, const String &operand2, const String &operand3);
		DbCondition nbcvc(const String &operand1, const DbValue &operand2, const String &operand3);
		DbCondition nbcvv(const String &operand1, const DbValue &operand2, const DbValue &operand3);
		DbCondition nbcve(const String &operand1, const DbValue &operand2, const String &operand3);
		DbCondition nbcec(const String &operand1, const String &operand2, const String &operand3);
		DbCondition nbcev(const String &operand1, const String &operand2, const DbValue &operand3);
		DbCondition nbcee(const String &operand1, const String &operand2, const String &operand3);
		DbCondition nbvcc(const DbValue &operand1, const String &operand2, const String &operand3);
		DbCondition nbvcv(const DbValue &operand1, const String &operand2, const DbValue &operand3);
		DbCondition nbvce(const DbValue &operand1, const String &operand2, const String &operand3);
		DbCondition nbvvc(const DbValue &operand1, const DbValue &operand2, const String &operand3);
		DbCondition nbvvv(const DbValue &operand1, const DbValue &operand2, const DbValue &operand3);
		DbCondition nbvve(const DbValue &operand1, const DbValue &operand2, const String &operand3);
		DbCondition nbvec(const DbValue &operand1, const String &operand2, const String &operand3);
		DbCondition nbvev(const DbValue &operand1, const String &operand2, const DbValue &operand3);
		DbCondition nbvee(const DbValue &operand1, const String &operand2, const String &operand3);
		DbCondition nbecc(const String &operand1, const String &operand2, const String &operand3);
		DbCondition nbecv(const String &operand1, const String &operand2, const DbValue &operand3);
		DbCondition nbece(const String &operand1, const String &operand2, const String &operand3);
		DbCondition nbevc(const String &operand1, const DbValue &operand2, const String &operand3);
		DbCondition nbevv(const String &operand1, const DbValue &operand2, const DbValue &operand3);
		DbCondition nbeve(const String &operand1, const DbValue &operand2, const String &operand3);
		DbCondition nbeec(const String &operand1, const String &operand2, const String &operand3);
		DbCondition nbeev(const String &operand1, const String &operand2, const DbValue &operand3);
		DbCondition nbeee(const String &operand1, const String &operand2, const String &operand3);
		DbCondition inc(const String &column, const std::vector<DbValue> &values);
		DbCondition inv(const DbValue &value, const std::vector<DbValue> &values);
		DbCondition ine(const String &expression, const std::vector<DbValue> &values);
		DbCondition nic(const String &column, const std::vector<DbValue> &values);
		DbCondition niv(const DbValue &value, const std::vector<DbValue> &values);
		DbCondition nie(const String &expression, const std::vector<DbValue> &values);
		DbCondition lkc(const String &column, const String &pattern);
		DbCondition lkv(const DbValue &value, const String &pattern);
		DbCondition lke(const String &expression, const String &pattern);
		DbCondition nlc(const String &column, const String &pattern);
		DbCondition nlv(const DbValue &value, const String &pattern);
		DbCondition nle(const String &expression, const String &pattern);
		DbCondition ex(const String &query);
		DbCondition ne(const String &query);
	}

	class CDbCondition final :public CReleasable
	{
		friend DbCondition db::Expression(const String &expression);
		friend DbCondition db::Equals(const String &operand1, const String &operand2);
		friend DbCondition db::Equals(const String &operand1, const DbValue &operand2);
		friend DbCondition db::Equals(const DbValue &operand1, const String &operand2);
		friend DbCondition db::Equals(const DbValue &operand1, const DbValue &operand2);
		friend DbCondition db::Equals(const String &operand1, DbCondition operand2);
		friend DbCondition db::Equals(DbCondition operand1, const String &operand2);
		friend DbCondition db::Equals(DbCondition operand1, DbCondition operand2);
		friend DbCondition db::Equals(const DbValue &operand1, DbCondition operand2);
		friend DbCondition db::Equals(DbCondition operand1, const DbValue &operand2);
		friend DbCondition db::NotEquals(const String &operand1, const String &operand2);
		friend DbCondition db::NotEquals(const String &operand1, const DbValue &operand2);
		friend DbCondition db::NotEquals(const DbValue &operand1, const String &operand2);
		friend DbCondition db::NotEquals(const DbValue &operand1, const DbValue &operand2);
		friend DbCondition db::NotEquals(const String &operand1, DbCondition operand2);
		friend DbCondition db::NotEquals(DbCondition operand1, const String &operand2);
		friend DbCondition db::NotEquals(DbCondition operand1, DbCondition operand2);
		friend DbCondition db::NotEquals(const DbValue &operand1, DbCondition operand2);
		friend DbCondition db::NotEquals(DbCondition operand1, const DbValue &operand2);
		friend DbCondition db::Greater(const String &operand1, const String &operand2);
		friend DbCondition db::Greater(const String &operand1, const DbValue &operand2);
		friend DbCondition db::Greater(const DbValue &operand1, const String &operand2);
		friend DbCondition db::Greater(const DbValue &operand1, const DbValue &operand2);
		friend DbCondition db::Greater(const String &operand1, DbCondition operand2);
		friend DbCondition db::Greater(DbCondition operand1, const String &operand2);
		friend DbCondition db::Greater(DbCondition operand1, DbCondition operand2);
		friend DbCondition db::Greater(const DbValue &operand1, DbCondition operand2);
		friend DbCondition db::Greater(DbCondition operand1, const DbValue &operand2);
		friend DbCondition db::GreaterEquals(const String &operand1, const String &operand2);
		friend DbCondition db::GreaterEquals(const String &operand1, const DbValue &operand2);
		friend DbCondition db::GreaterEquals(const DbValue &operand1, const String &operand2);
		friend DbCondition db::GreaterEquals(const DbValue &operand1, const DbValue &operand2);
		friend DbCondition db::GreaterEquals(const String &operand1, DbCondition operand2);
		friend DbCondition db::GreaterEquals(DbCondition operand1, const String &operand2);
		friend DbCondition db::GreaterEquals(DbCondition operand1, DbCondition operand2);
		friend DbCondition db::GreaterEquals(const DbValue &operand1, DbCondition operand2);
		friend DbCondition db::GreaterEquals(DbCondition operand1, const DbValue &operand2);
		friend DbCondition db::Less(const String &operand1, const String &operand2);
		friend DbCondition db::Less(const String &operand1, const DbValue &operand2);
		friend DbCondition db::Less(const DbValue &operand1, const String &operand2);
		friend DbCondition db::Less(const DbValue &operand1, const DbValue &operand2);
		friend DbCondition db::Less(const String &operand1, DbCondition operand2);
		friend DbCondition db::Less(DbCondition operand1, const String &operand2);
		friend DbCondition db::Less(DbCondition operand1, DbCondition operand2);
		friend DbCondition db::Less(const DbValue &operand1, DbCondition operand2);
		friend DbCondition db::Less(DbCondition operand1, const DbValue &operand2);
		friend DbCondition db::LessEquals(const String &operand1, const String &operand2);
		friend DbCondition db::LessEquals(const String &operand1, const DbValue &operand2);
		friend DbCondition db::LessEquals(const DbValue &operand1, const String &operand2);
		friend DbCondition db::LessEquals(const DbValue &operand1, const DbValue &operand2);
		friend DbCondition db::LessEquals(const String &operand1, DbCondition operand2);
		friend DbCondition db::LessEquals(DbCondition operand1, const String &operand2);
		friend DbCondition db::LessEquals(DbCondition operand1, DbCondition operand2);
		friend DbCondition db::LessEquals(const DbValue &operand1, DbCondition operand2);
		friend DbCondition db::LessEquals(DbCondition operand1, const DbValue &operand2);
		friend DbCondition db::And(DbCondition operand1, DbCondition operand2);
		friend DbCondition db::Or(DbCondition operand1, DbCondition operand2);
		friend DbCondition db::Not(DbCondition operand);
		friend DbCondition db::Between(const String &operand1, const String &operand2, const String &operand3);
		friend DbCondition db::Between(const String &operand1, const String &operand2, const DbValue &operand3);
		friend DbCondition db::Between(const String &operand1, const String &operand2, DbCondition operand3);
		friend DbCondition db::Between(const String &operand1, const DbValue &operand2, const String &operand3);
		friend DbCondition db::Between(const String &operand1, const DbValue &operand2, const DbValue &operand3);
		friend DbCondition db::Between(const String &operand1, const DbValue &operand2, DbCondition operand3);
		friend DbCondition db::Between(const String &operand1, DbCondition operand2, const String &operand3);
		friend DbCondition db::Between(const String &operand1, DbCondition operand2, const DbValue &operand3);
		friend DbCondition db::Between(const String &operand1, DbCondition operand2, DbCondition operand3);
		friend DbCondition db::Between(const DbValue &operand1, const String &operand2, const String &operand3);
		friend DbCondition db::Between(const DbValue &operand1, const String &operand2, const DbValue &operand3);
		friend DbCondition db::Between(const DbValue &operand1, const String &operand2, DbCondition operand3);
		friend DbCondition db::Between(const DbValue &operand1, const DbValue &operand2, const String &operand3);
		friend DbCondition db::Between(const DbValue &operand1, const DbValue &operand2, const DbValue &operand3);
		friend DbCondition db::Between(const DbValue &operand1, const DbValue &operand2, DbCondition operand3);
		friend DbCondition db::Between(const DbValue &operand1, DbCondition operand2, const String &operand3);
		friend DbCondition db::Between(const DbValue &operand1, DbCondition operand2, const DbValue &operand3);
		friend DbCondition db::Between(const DbValue &operand1, DbCondition operand2, DbCondition operand3);
		friend DbCondition db::Between(DbCondition operand1, const String &operand2, const String &operand3);
		friend DbCondition db::Between(DbCondition operand1, const String &operand2, const DbValue &operand3);
		friend DbCondition db::Between(DbCondition operand1, const String &operand2, DbCondition operand3);
		friend DbCondition db::Between(DbCondition operand1, const DbValue &operand2, const String &operand3);
		friend DbCondition db::Between(DbCondition operand1, const DbValue &operand2, const DbValue &operand3);
		friend DbCondition db::Between(DbCondition operand1, const DbValue &operand2, DbCondition operand3);
		friend DbCondition db::Between(DbCondition operand1, DbCondition operand2, const String &operand3);
		friend DbCondition db::Between(DbCondition operand1, DbCondition operand2, const DbValue &operand3);
		friend DbCondition db::Between(DbCondition operand1, DbCondition operand2, DbCondition operand3);
		friend DbCondition db::NotBetween(const String &operand1, const String &operand2, const String &operand3);
		friend DbCondition db::NotBetween(const String &operand1, const String &operand2, const DbValue &operand3);
		friend DbCondition db::NotBetween(const String &operand1, const String &operand2, DbCondition operand3);
		friend DbCondition db::NotBetween(const String &operand1, const DbValue &operand2, const String &operand3);
		friend DbCondition db::NotBetween(const String &operand1, const DbValue &operand2, const DbValue &operand3);
		friend DbCondition db::NotBetween(const String &operand1, const DbValue &operand2, DbCondition operand3);
		friend DbCondition db::NotBetween(const String &operand1, DbCondition operand2, const String &operand3);
		friend DbCondition db::NotBetween(const String &operand1, DbCondition operand2, const DbValue &operand3);
		friend DbCondition db::NotBetween(const String &operand1, DbCondition operand2, DbCondition operand3);
		friend DbCondition db::NotBetween(const DbValue &operand1, const String &operand2, const String &operand3);
		friend DbCondition db::NotBetween(const DbValue &operand1, const String &operand2, const DbValue &operand3);
		friend DbCondition db::NotBetween(const DbValue &operand1, const String &operand2, DbCondition operand3);
		friend DbCondition db::NotBetween(const DbValue &operand1, const DbValue &operand2, const String &operand3);
		friend DbCondition db::NotBetween(const DbValue &operand1, const DbValue &operand2, const DbValue &operand3);
		friend DbCondition db::NotBetween(const DbValue &operand1, const DbValue &operand2, DbCondition operand3);
		friend DbCondition db::NotBetween(const DbValue &operand1, DbCondition operand2, const String &operand3);
		friend DbCondition db::NotBetween(const DbValue &operand1, DbCondition operand2, const DbValue &operand3);
		friend DbCondition db::NotBetween(const DbValue &operand1, DbCondition operand2, DbCondition operand3);
		friend DbCondition db::NotBetween(DbCondition operand1, const String &operand2, const String &operand3);
		friend DbCondition db::NotBetween(DbCondition operand1, const String &operand2, const DbValue &operand3);
		friend DbCondition db::NotBetween(DbCondition operand1, const String &operand2, DbCondition operand3);
		friend DbCondition db::NotBetween(DbCondition operand1, const DbValue &operand2, const String &operand3);
		friend DbCondition db::NotBetween(DbCondition operand1, const DbValue &operand2, const DbValue &operand3);
		friend DbCondition db::NotBetween(DbCondition operand1, const DbValue &operand2, DbCondition operand3);
		friend DbCondition db::NotBetween(DbCondition operand1, DbCondition operand2, const String &operand3);
		friend DbCondition db::NotBetween(DbCondition operand1, DbCondition operand2, const DbValue &operand3);
		friend DbCondition db::NotBetween(DbCondition operand1, DbCondition operand2, DbCondition operand3);
		friend DbCondition db::In(const String &column, const std::vector<DbValue> &values);
		friend DbCondition db::In(const DbValue &value, const std::vector<DbValue> &values);
		friend DbCondition db::In(DbCondition expression, const std::vector<DbValue> &values);
		friend DbCondition db::NotIn(const String &column, const std::vector<DbValue> &values);
		friend DbCondition db::NotIn(const DbValue &value, const std::vector<DbValue> &values);
		friend DbCondition db::NotIn(DbCondition expression, const std::vector<DbValue> &values);
		friend DbCondition db::Like(const String &column, const String &pattern);
		friend DbCondition db::Like(const DbValue &value, const String &pattern);
		friend DbCondition db::Like(DbCondition expression, const String &pattern);
		friend DbCondition db::NotLike(const String &column, const String &pattern);
		friend DbCondition db::NotLike(const DbValue &value, const String &pattern);
		friend DbCondition db::NotLike(DbCondition expression, const String &pattern);
		friend DbCondition db::Exists(const String &query);
		friend DbCondition db::NotExists(const String &query);
	public:
		enum class ConditionType
		{
			Expression, // Condition is a custom expression (for example, "LENGTH(name)" or "IFNULL(age, 0)")
			Equals, // Condition is a comparison for equality
			NotEquals, // Condition is a comparison for not equality
			Greater, // Condition is a checking whether first operand is greater than second one
			GreaterEquals, // Condition is a checking whether first operand is greater or equals to second one
			Less, // Condition is a checking whether first operand is less than second one
			LessEquals, // Condition is a checking whether first operand is less or equals to second one
			And, // Condition is a concatenation of two other conditions with AND operator
			Or, // Condition is a concatenation of two other conditions with OR operator
			Not, // Condition is a negation of other condition
			Between, // Condition is checking whether first operand is between second and third ones
			NotBetween, // Condition is checking whether first operand is not between second and third ones
			In, // Condition is checking whether operand is in array of allowed values
			NotIn, // Condition is checking whether operand is not in array of allowed values
			Like, // Condition is checking whether operand corresponds to specified pattern
			NotLike, // Condition is checking whether operand does not correspond to specified pattern
			Exists, // Condition is checking whether expression has data in a result
			NotExists // Condition is checking whether expression has no data in a result 
		};

		enum class OperandType
		{
			Column, // Operand is a column name
			Value, // Operand is a value
			Expression // Operand is another expression
		};
	private:
		ConditionType m_eType;
		OperandType m_eOperand1Type;
		OperandType m_eOperand2Type;
		OperandType m_eOperand3Type;
		String m_sColumn1;
		String m_sColumn2;
		String m_sColumn3;
		DbValue m_sValue1;
		DbValue m_sValue2;
		DbValue m_sValue3;
		std::vector<DbValue> m_aValues;
		DbCondition m_pOperand1;
		DbCondition m_pOperand2;
		DbCondition m_pOperand3;

		void setOperand1(const String &column);
		void setOperand1(const DbValue &value);
		void setOperand1(DbCondition expression);
		void setOperand2(const String &column);
		void setOperand2(const DbValue &value);
		void setOperand2(DbCondition expression);
		void setOperand3(const String &column);
		void setOperand3(const DbValue &value);
		void setOperand3(DbCondition expression);

		CDbCondition() = default;
	public:
		ConditionType const &Type{ m_eType }; // Condition type
		OperandType const &Operand1Type{ m_eOperand1Type }; // Operand1 type
		OperandType const &Operand2Type{ m_eOperand2Type }; // Operand2 type
		OperandType const &Operand3Type{ m_eOperand3Type }; // Operand3 type
		String const &Column1{ m_sColumn1 }; // Column1 name. Only relevant if Operand1Type = Column
		String const &Column2{ m_sColumn2 }; // Column2 name. Only relevant if Operand2Type = Column
		String const &Column3{ m_sColumn3 }; // Column3 name. Only relevant if Operand3Type = Column
		DbValue const &Value1{ m_sValue1 }; // Value1. Only relevant if Operand1Type = Value
		DbValue const &Value2{ m_sValue2 }; // Value2. Only relevant if Operand2Type = Value
		DbValue const &Value3{ m_sValue3 }; // Value3. Only relevant if Operand3Type = Value
		std::vector<DbValue> const &Values{ m_aValues }; // Array of values. Only relevant if Type = In or NotIn
		DbCondition const &Operand1{ m_pOperand1 }; // Expression1. Only relevant if Operand1Type = Expression
		DbCondition const &Operand2{ m_pOperand2 }; // Expression2. Only relevant if Operand2Type = Expression
		DbCondition const &Operand3{ m_pOperand3 }; // Expression3. Only relevant if Operand3Type = Expression
	};
}
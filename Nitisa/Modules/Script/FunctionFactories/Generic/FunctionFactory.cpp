// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace script
	{
		namespace generic
		{
		#pragma region Constructor & destructor
			CFunctionFactory::CFunctionFactory() :
				CReleasable()
			{

			}
		#pragma endregion

		#pragma region IFunctionFactory methods
			IFunction *CFunctionFactory::Create(const String &name, IErrorListener *error_listener, const IFunction::Arguments &arguments, IFunction *modify)
			{
				// Arithmetic
				if (name == L"&")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionBitwiseAnd(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"|")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionBitwiseOr(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"^")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionBitwiseXor(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"/")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionDivide(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"-")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionMinus(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"%")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionModulo(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"*")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionMultiply(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"+")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionPlus(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"<<")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionShiftLeft(error_listener, arguments[0], arguments[1]);
				}
				if (name == L">>")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionShiftRight(error_listener, arguments[0], arguments[1]);
				}
				// Assignment
				if (name == L"=")
				{
					if (!modify)
						return nullptr;
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionAssign(error_listener, arguments[0], arguments[1], modify);
				}
				if (name == L"&=")
				{
					if (!modify)
						return nullptr;
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionBitwiseAndAssign(error_listener, arguments[0], arguments[1], modify);
				}
				if (name == L"|=")
				{
					if (!modify)
						return nullptr;
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionBitwiseOrAssign(error_listener, arguments[0], arguments[1], modify);
				}
				if (name == L"^=")
				{
					if (!modify)
						return nullptr;
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionBitwiseXorAssign(error_listener, arguments[0], arguments[1], modify);
				}
				if (name == L"/=")
				{
					if (!modify)
						return nullptr;
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionDivideAssign(error_listener, arguments[0], arguments[1], modify);
				}
				if (name == L"-=")
				{
					if (!modify)
						return nullptr;
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionMinusAssign(error_listener, arguments[0], arguments[1], modify);
				}
				if (name == L"%=")
				{
					if (!modify)
						return nullptr;
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionModuloAssign(error_listener, arguments[0], arguments[1], modify);
				}
				if (name == L"*=")
				{
					if (!modify)
						return nullptr;
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionMultiplyAssign(error_listener, arguments[0], arguments[1], modify);
				}
				if (name == L"+=")
				{
					if (!modify)
						return nullptr;
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionPlusAssign(error_listener, arguments[0], arguments[1], modify);
				}
				if (name == L"<<=")
				{

					if (!modify)
						return nullptr;
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionShiftLeftAssign(error_listener, arguments[0], arguments[1], modify);
				}
				if (name == L">>=")
				{
					if (!modify)
						return nullptr;
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionShiftRightAssign(error_listener, arguments[0], arguments[1], modify);
				}
				// Cast
				if (name == L"__cast(bool)")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionBool(error_listener, arguments[0]);
				}
				if (name == L"__cast(double)")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionDouble(error_listener, arguments[0]);
				}
				if (name == L"__cast(float)")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionDouble(error_listener, arguments[0]);
				}
				if (name == L"__cast(int)")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionInt64(error_listener, arguments[0]);
				}
				if (name == L"__cast(int64)")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionInt64(error_listener, arguments[0]);
				}
				if (name == L"__cast(Integer)")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionInt64(error_listener, arguments[0]);
				}
				if (name == L"__cast(String)")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionString(error_listener, arguments[0]);
				}
				if (name == L"bool")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionBool(error_listener, arguments[0]);
				}
				if (name == L"double")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionDouble(error_listener, arguments[0]);
				}
				if (name == L"float")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionDouble(error_listener, arguments[0]);
				}
				if (name == L"int")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionInt64(error_listener, arguments[0]);
				}
				if (name == L"int64")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionInt64(error_listener, arguments[0]);
				}
				if (name == L"Integer")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionInt64(error_listener, arguments[0]);
				}
				if (name == L"String")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionString(error_listener, arguments[0]);
				}
				// Comparison
				if (name == L"&&")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionAnd(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"==")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionEqual(error_listener, arguments[0], arguments[1]);
				}
				if (name == L">")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionGreater(error_listener, arguments[0], arguments[1]);
				}
				if (name == L">=")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionGreaterEqual(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"<")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionLess(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"<=")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionLessEqual(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"!=")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionNotEqual(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"||")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionOr(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"<=>")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionSpaceship(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"?:")
				{
					if (arguments.size() != 3)
						return nullptr;
					return new CFunctionTernary(error_listener, arguments[0], arguments[1], arguments[2]);
				}
				// General
				if (name == L"->")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionArrow(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"{}")
					return new CFunctionBrace(error_listener, arguments);
				if (name == L".")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionArrow(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"::")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionArrow(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"[]")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionSubscript(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"rnd")
				{
					if (arguments.empty())
						return new CFunctionRnd(error_listener);
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionRndRange(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"rand")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionRand(error_listener, arguments[0], arguments[1]);
				}
				// Mathematics
				if (name == L"abs")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionAbs(error_listener, arguments[0]);
				}
				if (name == L"acos")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionACos(error_listener, arguments[0]);
				}
				if (name == L"acosh")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionACosH(error_listener, arguments[0]);
				}
				if (name == L"asin")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionASin(error_listener, arguments[0]);
				}
				if (name == L"asinh")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionASinH(error_listener, arguments[0]);
				}
				if (name == L"atan")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionATan(error_listener, arguments[0]);
				}
				if (name == L"atan2")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionATan2(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"cbrt")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionCbrt(error_listener, arguments[0]);
				}
				if (name == L"ceil")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionCeil(error_listener, arguments[0]);
				}
				if (name == L"cos")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionCos(error_listener, arguments[0]);
				}
				if (name == L"cosh")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionCosH(error_listener, arguments[0]);
				}
				if (name == L"dim")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionDim(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"erf")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionErf(error_listener, arguments[0]);
				}
				if (name == L"erfc")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionErfC(error_listener, arguments[0]);
				}
				if (name == L"exp")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionExp(error_listener, arguments[0]);
				}
				if (name == L"exp2")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionExp2(error_listener, arguments[0]);
				}
				if (name == L"expm1")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionExpM1(error_listener, arguments[0]);
				}
				if (name == L"floor")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionFloor(error_listener, arguments[0]);
				}
				if (name == L"fma")
				{
					if (arguments.size() != 3)
						return nullptr;
					return new CFunctionFMA(error_listener, arguments[0], arguments[1], arguments[2]);
				}
				if (name == L"gamma")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionGamma(error_listener, arguments[0]);
				}
				if (name == L"hypot")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionHypot(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"ldexp")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionLdExp(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"lgamma")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionLGamma(error_listener, arguments[0]);
				}
				if (name == L"log")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionLog(error_listener, arguments[0]);
				}
				if (name == L"log10")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionLog10(error_listener, arguments[0]);
				}
				if (name == L"log1p")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionLog1P(error_listener, arguments[0]);
				}
				if (name == L"log2")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionLog2(error_listener, arguments[0]);
				}
				if (name == L"max")
				{
					if (arguments.size() < 1)
						return nullptr;
					return new CFunctionMax(error_listener, arguments);
				}
				if (name == L"min")
				{
					if (arguments.size() < 1)
						return nullptr;
					return new CFunctionMin(error_listener, arguments);
				}
				if (name == L"mod")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionMod(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"pow")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionPow(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"remainder")
				{
					if (arguments.size() != 2)
						return nullptr;
					return new CFunctionRemainder(error_listener, arguments[0], arguments[1]);
				}
				if (name == L"round")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionRound(error_listener, arguments[0]);
				}
				if (name == L"roundf")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionRoundF(error_listener, arguments[0]);
				}
				if (name == L"sin")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionSin(error_listener, arguments[0]);
				}
				if (name == L"sinh")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionSinH(error_listener, arguments[0]);
				}
				if (name == L"sqrt")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionSqrt(error_listener, arguments[0]);
				}
				if (name == L"tan")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionTan(error_listener, arguments[0]);
				}
				if (name == L"tanh")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionTanH(error_listener, arguments[0]);
				}
				if (name == L"trunc")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionTrunc(error_listener, arguments[0]);
				}
				// Unary
				if (name == L"~x")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionBitwiseNot(error_listener, arguments[0]);
				}
				if (name == L"!x")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionLogicalNot(error_listener, arguments[0]);
				}
				if (name == L"x--")
				{
					if (!modify)
						return nullptr;
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionPostfixDecrement(error_listener, arguments[0], modify);
				}
				if (name == L"x++")
				{
					if (!modify)
						return nullptr;
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionPostfixIncrement(error_listener, arguments[0], modify);
				}
				if (name == L"--x")
				{
					if (!modify)
						return nullptr;
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionPrefixDecrement(error_listener, arguments[0], modify);
				}
				if (name == L"++x")
				{
					if (!modify)
						return nullptr;
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionPrefixIncrement(error_listener, arguments[0], modify);
				}
				if (name == L"-x")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionUnaryMinus(error_listener, arguments[0]);
				}
				if (name == L"+x")
				{
					if (arguments.size() != 1)
						return nullptr;
					return new CFunctionUnaryPlus(error_listener, arguments[0]);
				}
				return nullptr;
			}
		#pragma endregion
		}
	}
}
// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
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
		// General
		const ErrorInfo ERROR_GENERAL_EXPECTED_CLOSE_BRACKET					{    1, L"Expected close bracket (')') at position {index} but '{token}' found" };
		const ErrorInfo ERROR_GENERAL_EXPECTED_COLON							{    2, L"Expected colon (':') at position {index} but '{token}' found" };
		const ErrorInfo ERROR_GENERAL_EXPECTED_COMMA							{    3, L"Expected comma (',') at position {index} but '{token}' found" };
		const ErrorInfo ERROR_GENERAL_EXPECTED_ELLIPSIS							{    4, L"Expected ellipsis ('...') at position {index} but '{token}' found" };
		const ErrorInfo ERROR_GENERAL_EXPECTED_END								{    5, L"Expected end of data at position {index} but '{token}' found" };
		const ErrorInfo ERROR_GENERAL_EXPECTED_EQUAL							{    6, L"Expected equal ('=') at position {index} but '{token}' found" };
		const ErrorInfo ERROR_GENERAL_EXPECTED_IDENTIFIER						{    7, L"Expected identifier at position {index} but '{token}' found" };
		const ErrorInfo ERROR_GENERAL_EXPECTED_LESS								{    8, L"Expected less ('<') at position {index} but '{token}' found" };
		const ErrorInfo ERROR_GENERAL_EXPECTED_NAME								{    9, L"Expected '{name}' at position {index} but '{token}' found" };
		const ErrorInfo ERROR_GENERAL_EXPECTED_NEW_LINE							{   10, L"Expected new line ('\\n') at position {index} but '{token}' found" };
		const ErrorInfo ERROR_GENERAL_EXPECTED_NUMBER							{   11, L"Expected number at position {index} but '{token}' found" };
		const ErrorInfo ERROR_GENERAL_EXPECTED_OPEN_BRACE						{   12, L"Expected open brace ('{') at position {index} but '{token}' found" };
		const ErrorInfo ERROR_GENERAL_EXPECTED_OPEN_BRACKET						{   13, L"Expected open bracket ('(') at position {index} but '{token}' found" };
		const ErrorInfo ERROR_GENERAL_EXPECTED_OPERATOR							{   14, L"Expected operator at position {index} but '{token}' found" };
		const ErrorInfo ERROR_GENERAL_EXPECTED_OPERATOR_NAME					{   15, L"Expected operator '{name}' at position {index} but '{token}' found" };
		const ErrorInfo ERROR_GENERAL_EXPECTED_SEMICOLON						{   16, L"Expected semicolon (';') at position {index} but '{token}' found" };
		const ErrorInfo ERROR_GENERAL_EXPECTED_STRING							{   17, L"Expected string at position {index} but '{token}' found" };
		const ErrorInfo ERROR_GENERAL_OPERATOR_NOT_POSTERIOR					{   18, L"Operator '{name}' at position {index} expected to have 'Posterior' mark but it doesn't" };
		const ErrorInfo ERROR_GENERAL_OPERATOR_NOT_PRIOR						{   19, L"Operator '{name}' at position {index} expected to have 'Prior' mark but it doesn't" };
		const ErrorInfo ERROR_GENERAL_POSTERIOR_OPERATOR_NOT_ALLOWED			{   20, L"Operator '{name}' at position {index} doesn't allow another posterior operator" };
		const ErrorInfo ERROR_GENERAL_PRIOR_OPERATOR_NOT_ALLOWED				{   21, L"Operator '{name}' at position {index} doesn't allow another prior operator" };
		const ErrorInfo ERROR_GENERAL_UNEXPECTED_END							{   22, L"Unexpected end of data" };
		const ErrorInfo ERROR_GENERAL_UNEXPECTED_OPERATOR						{   23, L"Unexpected operator '{token}' at position {index}" };
		const ErrorInfo ERROR_GENERAL_UNEXPECTED_TOKEN							{   24, L"Unexpected token '{token}' at position {index}" };
		const ErrorInfo ERROR_GENERAL_UNKNOWN_IDENTIFIER						{   25, L"Unknown identifier '{token}' at position {index}" };
		const ErrorInfo ERROR_GENERAL_UNKNOWN_TOKEN								{   26, L"Unknown token '{token}' at position {index}" };
		// Json
		const ErrorInfo ERROR_JSON_EXPECTED_ARRAY_END							{  100, L"Expected array end (']') at position {index} but '{token}' found" };
		const ErrorInfo ERROR_JSON_EXPECTED_OBJECT_END							{  101, L"Expected object end ('}') at position {index} but '{token}' found" };
		// Xml
		const ErrorInfo ERROR_XML_DOCTYPE_NOT_ALLOWED							{  200, L"DOCTYPE not allowed at position {index}" };
		const ErrorInfo ERROR_XML_ELEMENT_NOT_ALLOWED							{  201, L"Element not allowed at position {index}" };
		const ErrorInfo ERROR_XML_EXPECTED_DOCTYPE								{  202, L"Expected 'DOCTYPE' at position {index} but '{token}' found" };
		const ErrorInfo ERROR_XML_EXPECTED_ELEMENT_CLOSE_OPERATOR				{  203, L"Expected '</' at position {index} but '{token}' found" };
		const ErrorInfo ERROR_XML_PROLOG_NOT_ALLOWED							{  204, L"Prolog not allowed at position {index}" };
		// Expression Builder
		const ErrorInfo ERROR_EB_EXPECTED_EXPRESSION_NAME						{  300, L"Expected expression name at position {index}" };
		const ErrorInfo ERROR_EB_EXPECTED_NORMAL_OPERATOR						{  301, L"Expected normal operator at position {index} but '{token}' found" };
		const ErrorInfo ERROR_EB_EXPECTED_OPERAND								{  302, L"Expected operand at position {index}" };
		const ErrorInfo ERROR_EB_EXPECTED_OPERATOR_BETWEEN_OPERANDS				{  303, L"Expected operator between operands at position {index}" };
		const ErrorInfo ERROR_EB_EXPECTED_TOKENIZER								{  304, L"Tokenizer is required" };
		const ErrorInfo ERROR_EB_EXPECTED_TOKENS								{  305, L"Tokens are required" };
		const ErrorInfo ERROR_EB_INVALID_TOKENS_RANGE							{  306, L"Tokens range {first}..{last} is invalid" };
		const ErrorInfo ERROR_EB_INVALID_TOKENS_RANGE_END						{  307, L"Tokens range end value {last} should be less then token number {size}" };
		const ErrorInfo ERROR_EB_INVALID_TOKENS_RANGE_START						{  308, L"Tokens range start value {first} should be less then token number {size}" };
		const ErrorInfo ERROR_EB_POSTERIOR_OPERATOR_BEFORE_MEMBER_ACCESS		{  309, L"Posterior operator before member access operator is not allowed near position {index}" };
		const ErrorInfo ERROR_EB_PRIOR_OPERATOR_AFTER_MEMBER_ACCESS				{  310, L"Prior operator after member access operator is not allowed near position {index}" };
		const ErrorInfo ERROR_EB_STRING_PREFIX_MISMATCH							{  311, L"String prefix mismatch ('{1}' vs '{2}') at position {index}" };
		const ErrorInfo ERROR_EB_UNEXPECTED_EXPRESSION_TYPE						{  312, L"Unexpected expression type '{type}' at position {index}" };
		const ErrorInfo ERROR_EB_UNEXPECTED_NAME_EXPRESSION_TYPE				{  313, L"Unexpected name expression type '{type}' at position {index}" };
		const ErrorInfo ERROR_EB_USER_DEFINED_LITERALS_NOT_ALLOWED				{  314, L"User-defined literals are not allowed but found at position {index}" };
		// Expression Runner
		const ErrorInfo ERROR_ER_BRACE_ARGUMENTS_WITH_POSTERIOR_OPERATORS		{  400, L"Brace arguments has posterior operator(s) at position {index} but it should not" };
		const ErrorInfo ERROR_ER_BRACE_ARGUMENTS_WITH_PRIOR_OPERATORS			{  401, L"Brace arguments has prior operator(s) at position {index} but it should not" };
		const ErrorInfo ERROR_ER_BRACE_NAME_EXPRESSION_TYPE						{  402, L"Brace name expression type is '{type}' but only 'Cast' is allowed at position {index}" };
		const ErrorInfo ERROR_ER_BRACE_NAME_WITH_POSTERIOR_OPERATORS			{  403, L"Brace name has posterior operator(s) at position {index} but it should not" };
		const ErrorInfo ERROR_ER_BRACE_NAME_WITH_PRIOR_OPERATORS				{  404, L"Brace name has prior operator(s) at position {index} but it should not" };
		const ErrorInfo ERROR_ER_CALL_ARGUMENTS_WITH_POSTERIOR_OPERATORS		{  405, L"Call arguments has posterior operator(s) at position {index} but it should not" };
		const ErrorInfo ERROR_ER_CALL_ARGUMENTS_WITH_PRIOR_OPERATORS			{  406, L"Call arguments has prior operator(s) at position {index} but it should not" };
		const ErrorInfo ERROR_ER_CALL_NAME_EXPRESSION_TYPE						{  407, L"Call name expression type is '{type}' but only 'Identifier' is allowed at position {index}" };
		const ErrorInfo ERROR_ER_CALL_NAME_WITH_POSTERIOR_OPERATORS				{  408, L"Call name has posterior operator(s) at position {index} but it should not" };
		const ErrorInfo ERROR_ER_CALL_NAME_WITH_PRIOR_OPERATORS					{  409, L"Call name has prior operator(s) at position {index} but it should not" };
		const ErrorInfo ERROR_ER_CAST_DATA_TYPE_EMPTY							{  410, L"Empty cast data type is not allowed at position {index}" };
		const ErrorInfo ERROR_ER_CAST_NAME_WITH_POSTERIOR_OPERATORS				{  411, L"Cast name has posterior operator(s) at position {index} but it should not" };
		const ErrorInfo ERROR_ER_CAST_NAME_WITH_PRIOR_OPERATORS					{  412, L"Cast name has prior operator(s) at position {index} but it should not" };
		const ErrorInfo ERROR_ER_FUNCTION_NOT_FOUND								{  413, L"Function/Operator '{name}' with {count} arguments is not found" };
		const ErrorInfo ERROR_ER_EMPTY_SEQUENCE									{  414, L"Empty sequence at position {index}" };
		const ErrorInfo ERROR_ER_EXPECTED_BRACE_ARGUMENTS						{  415, L"Expected brace arguments at position {index} but none found" };
		const ErrorInfo ERROR_ER_EXPECTED_CAST_OPERAND							{  416, L"Expected operand after cast at position {index}" };
		const ErrorInfo ERROR_ER_EXPECTED_EXPRESSION							{  417, L"Expression is required" };
		const ErrorInfo ERROR_ER_EXPECTED_FIVE_EXPRESSIONS_FOR_TERNARY			{  418, L"Expected five expressions for ternary operator at position {index}" };
		const ErrorInfo ERROR_ER_EXPECTED_ODD_ARGUMENT_COUNT					{  419, L"Expected odd argument count at position {index}" };
		const ErrorInfo ERROR_ER_EXPECTED_ODD_EXPRESSION_COUNT					{  420, L"Expected odd expression count at position {index}" };
		const ErrorInfo ERROR_ER_EXPECTED_ONE_ARGUMENT							{  421, L"Expected only one argument at position {index}" };
		const ErrorInfo ERROR_ER_EXPECTED_OPERAND								{  422, L"Expected operand at position {index} but operator found" };
		const ErrorInfo ERROR_ER_EXPECTED_OPERATOR								{  423, L"Expected operator at position {index} but operand found" };
		const ErrorInfo ERROR_ER_EXPECTED_SUBSCRIPT_ARGUMENTS					{  424, L"Expected subscript arguments at position {index}" };
		const ErrorInfo ERROR_ER_EXPECTED_SUBSCRIPT_NAME						{  425, L"Expected subscript name at position {index}" };
		const ErrorInfo ERROR_ER_IDENTIFIER_WITH_POSTERIOR_OPERATORS			{  426, L"Identifier '{name}' has posterior operator(s) at position {index} but it should not" };
		const ErrorInfo ERROR_ER_IDENTIFIER_WITH_PRIOR_OPERATORS				{  427, L"Identifier '{name}' has prior operator(s) at position {index} but it should not" };
		const ErrorInfo ERROR_ER_NOT_PREPARED									{  428, L"Expression is not prepared" };
		const ErrorInfo ERROR_ER_SUBSCRIPT_ARGUMENTS_WITH_POSTERIOR_OPERATORS	{  429, L"Subscript arguments has posterior operator(s) at position {index} but it should not" };
		const ErrorInfo ERROR_ER_SUBSCRIPT_ARGUMENTS_WITH_PRIOR_OPERATORS		{  430, L"Subscript arguments has prior operator(s) at position {index} but it should not" };
		const ErrorInfo ERROR_ER_SUBSCRIPT_NAME_WITH_POSTERIOR_OPERATORS		{  431, L"Subscript name has posterior operator(s) at position {index} but it should not" };
		const ErrorInfo ERROR_ER_SUBSCRIPT_NAME_WITH_PRIOR_OPERATORS			{  432, L"Subscript name has prior operator(s) at position {index} but it should not" };
		const ErrorInfo ERROR_ER_UNSUPPORTED_CAST_NAME_EXPRESSION_TYPE			{  433, L"Cast name expression type is '{type}' bu only 'Cast' is allowed at position {index}" };
		const ErrorInfo ERROR_ER_UNSUPPORTED_EXPRESSION_TYPE					{  434, L"Expression of type '{type}' is not supported but found at position {index}" };
		const ErrorInfo ERROR_ER_UNSUPPORTED_SUBSCRIPT_NAME_EXPRESSION_TYPE		{  435, L"Subscript name expression of type '{type}' is not supported but found at position {index}" };
		// Functions
		const ErrorInfo ERROR_FUNCTION_EXPECTED_ARGUMENTS						{  500, L"Expected arguments in function '{name}'" };
		const ErrorInfo ERROR_FUNCTION_INDEX_OUT_OF_BOUNDS						{  501, L"Index {index} out of bounds [0..{size}) in function '{name}'" };
		const ErrorInfo ERROR_FUNCTION_MISSING_OPERAND_1						{  502, L"Expression is not prepared properly. Missing first operand in function '{name}'" };
		const ErrorInfo ERROR_FUNCTION_MISSING_OPERAND_2						{  503, L"Expression is not prepared properly. Missing second operand in function '{name}'" };
		const ErrorInfo ERROR_FUNCTION_MISSING_OPERAND_3						{  504, L"Expression is not prepared properly. Missing third operand in function '{name}'" };
		const ErrorInfo ERROR_FUNCTION_OPERAND_1_NOT_ARRAY						{  505, L"First operand is expected to be an array in function '{name}'" };
		const ErrorInfo ERROR_FUNCTION_OPERAND_1_NOT_OBJECT						{  506, L"First operand is expected to be an object in function '{name}'" };
		const ErrorInfo ERROR_FUNCTION_OPERAND_2_NOT_IDENTIFIER					{  507, L"Second operand is expected to be an identifier in function '{name}'" };
		// C++Doc pre-processor
		const ErrorInfo ERROR_CPPDOC_PP_DEFINITION_EXISTS						{  600, L"{index}: Definition '{name}' already exists" };
		const ErrorInfo ERROR_CPPDOC_PP_DUPLICATE_VARIADIC						{  601, L"{index}: Duplicate '...'" };
		const ErrorInfo ERROR_CPPDOC_PP_EXPECTED_ANSI_STRING					{  602, L"{index}: String enclosed by \"\" with no prefix is expected but '{name}' is found" };
		const ErrorInfo ERROR_CPPDOC_PP_EXPECTED_DEFINE_AFTER_HASH				{  603, L"{index}: 'define' is expected after '#'/'%:'" };
		const ErrorInfo ERROR_CPPDOC_PP_EXPECTED_EXPRESSION						{  604, L"{index}: Expression is expected" };
		const ErrorInfo ERROR_CPPDOC_PP_EXPECTED_HASH							{  605, L"{index}: Expected '#' or '%:' operator but none is found" };
		const ErrorInfo ERROR_CPPDOC_PP_EXPECTED_IDENTIFIER						{  606, L"{index}: Identifier is expected but '{name}' is found" };
		const ErrorInfo ERROR_CPPDOC_PP_EXPECTED_IDENTIFIER_AFTER_DEFINE		{  607, L"{index}: Identifier is expected after 'define'" };
		const ErrorInfo ERROR_CPPDOC_PP_EXPECTED_NEW_LINE						{  608, L"{index}: New line is expected" };
		const ErrorInfo ERROR_CPPDOC_PP_EXPECTED_ONE_ARGUMENT					{  609, L"{index}: Only 1 argument is expected. {count} is found" };
		const ErrorInfo ERROR_CPPDOC_PP_EXPECTED_OPERAND						{  610, L"{index}: Operand is expected but '{name}' is found" };
		const ErrorInfo ERROR_CPPDOC_PP_EXPECTED_OPERATOR						{  611, L"{index}: Operator is expected but '{name}' is found" };
		const ErrorInfo ERROR_CPPDOC_PP_EXPECTED_PARAMETER						{  612, L"{index}: Parameter is expected" };
		const ErrorInfo ERROR_CPPDOC_PP_EXPECTED_TOKEN							{  613, L"{index}: '{token}' is expected but '{name}' is found" };
		const ErrorInfo ERROR_CPPDOC_PP_INVALID_ARGUMENT_COUNT					{  614, L"{index}: Got {count} arguments but {expected} is expected" };
		const ErrorInfo ERROR_CPPDOC_PP_INVALID_EXPRESSION						{  615, L"{index}: Invalid expression" };
		const ErrorInfo ERROR_CPPDOC_PP_INVALID_OPERAND							{  616, L"{index}: Invalid operand '{name}'" };
		const ErrorInfo ERROR_CPPDOC_PP_INVALID_NEXT_CONCATINATE_ARGUMENT		{  617, L"{index}: Right concatinate argument '{name}' is invalid" };
		const ErrorInfo ERROR_CPPDOC_PP_INVALID_PREV_CONCATINATE_ARGUMENT		{  618, L"{index}: Left concatinate argument '{name}' is invalid" };
		const ErrorInfo ERROR_CPPDOC_PP_MISSING_NEXT_CONCATINATE_ARGUMENT		{  619, L"{index}: Right concatinate argument is missing" };
		const ErrorInfo ERROR_CPPDOC_PP_MISSING_PREV_CONCATINATE_ARGUMENT		{  620, L"{index}: Left concatinate argument is missing" };
		const ErrorInfo ERROR_CPPDOC_PP_TOO_FEW_ARGUMENTS						{  621, L"{index}: Too few arguments ({count}). At least {expected} is expected" };
		const ErrorInfo ERROR_CPPDOC_PP_UNEXPECTED_END							{  622, L"{index}: Unexpected end, the '{name}' is expected" };
		const ErrorInfo ERROR_CPPDOC_PP_UNEXPECTED_END_EXPECTED_EXPRESSION		{  623, L"{index}: Unexpected end. Expression is expected" };
		const ErrorInfo ERROR_CPPDOC_PP_UNEXPECTED_END_EXPECTED_IDENTIFIER		{  624, L"{index}: Unexpected end. Identifier is expected" };
		const ErrorInfo ERROR_CPPDOC_PP_UNEXPECTED_END_EXPECTED_OPERAND			{  625, L"{index}: Unexpected end. Operand is expected" };
		const ErrorInfo ERROR_CPPDOC_PP_UNEXPECTED_PRIOR_OPERATORS				{  626, L"{index}: Unexpected prior operators" };
		const ErrorInfo ERROR_CPPDOC_PP_UNEXPECTED_TOKEN						{  627, L"{index}: Unexpected token '{name}' is found" };
		const ErrorInfo ERROR_CPPDOC_PP_UNFINISHED_BRANCH						{  628, L"{index}: Unfinished conditional branch" };
		const ErrorInfo ERROR_CPPDOC_PP_UNKNOWN_DIRECTIVE						{  629, L"{index}: Unknown directive '{name}'" };
		const ErrorInfo ERROR_CPPDOC_PP_UNKNOWN_FUNCTION						{  630, L"{index}: Unknown function '{name}'" };
		const ErrorInfo ERROR_CPPDOC_PP_UNSUPPORTED_OPERATOR					{  631, L"{index}: Operator '{name}' is not supported in pre-processor expression" };
		// C++Doc
		const ErrorInfo ERROR_CPPDOC_BITFIELD_REQUIRE_ID_DECLARATOR				{  700, L"{index}: Bitfield is allowed only after simple id-declarator" };
		const ErrorInfo ERROR_CPPDOC_DUPLICATE_AUTO								{  701, L"{index}: Second 'auto' is not allowed" };
		const ErrorInfo ERROR_CPPDOC_DUPLICATE_FINAL							{  702, L"{index}: Second 'final' is not allowed" };
		const ErrorInfo ERROR_CPPDOC_DUPLICATE_PRIVATE							{  703, L"{index}: Second 'private' is not allowed" };
		const ErrorInfo ERROR_CPPDOC_DUPLICATE_PROTECTED						{  704, L"{index}: Second 'protected' is not allowed" };
		const ErrorInfo ERROR_CPPDOC_DUPLICATE_PUBLIC							{  705, L"{index}: Second 'public' is not allowed" };
		const ErrorInfo ERROR_CPPDOC_DUPLICATE_REPLACEABLE						{  706, L"{index}: Second 'replaceable_if_eligible' is not allowed" };
		const ErrorInfo ERROR_CPPDOC_DUPLICATE_TRIVIALLY_RELOCATABLE			{  707, L"{index}: Second 'trivially_relocatable_if_eligible' is not allowed" };
		const ErrorInfo ERROR_CPPDOC_DUPLICATE_VIRTUAL							{  708, L"{index}: Second 'virtual' is not allowed" };
		const ErrorInfo ERROR_CPPDOC_EXPECTED_ANSI								{  709, L"{index}: Expected ANSI string but '{name}' is found" };
		const ErrorInfo ERROR_CPPDOC_EXPECTED_ARGUMENT							{  710, L"{index}: Expected argument but '{name}' is found" };
		const ErrorInfo ERROR_CPPDOC_EXPECTED_AUTO								{  711, L"{index}: Expected 'auto'" };
		const ErrorInfo ERROR_CPPDOC_EXPECTED_DECLARATOR						{  712, L"{index}: Expected declarator but '{name}' is found" };
		const ErrorInfo ERROR_CPPDOC_EXPECTED_EXPRESSION						{  713, L"{index}: Expected expression but '{name}' is found" };
		const ErrorInfo ERROR_CPPDOC_EXPECTED_IDENTIFIER						{  714, L"{index}: Expected identifier but '{name}' is found" };
		const ErrorInfo ERROR_CPPDOC_EXPECTED_INITIALIZATION					{  715, L"{index}: Expected initialization but '{name}' is found" };
		const ErrorInfo ERROR_CPPDOC_EXPECTED_SPECIFIER							{  716, L"{index}: Expected specifier but '{name}' is found" };
		const ErrorInfo ERROR_CPPDOC_EXPECTED_STRING							{  717, L"{index}: Expected string but '{name}' is found" };
		const ErrorInfo ERROR_CPPDOC_EXPECTED_TOKEN								{  718, L"{index}: Expected '{token}' but '{name}' is found" };
		const ErrorInfo ERROR_CPPDOC_EXPECTED_TRAILING							{  719, L"{index}: Expected trailing but '{name}' is found" };
		const ErrorInfo ERROR_CPPDOC_EXPECTED_TYPE_ID							{  720, L"{index}: Expected type-id but '{name}' is found" };
		const ErrorInfo ERROR_CPPDOC_EXPORT_MODULE_WITHOUT_NAME					{  721, L"{index}: Module withot name cannot be exported" };
		const ErrorInfo ERROR_CPPDOC_EXPORT_PRIVATE_MODULE						{  722, L"{index}: Private module cannot be exported" };
		const ErrorInfo ERROR_CPPDOC_INLINE_NOT_ALLOWED_HERE					{  723, L"{index}: Inline is not allowed here" };
		const ErrorInfo ERROR_CPPDOC_INVALID_DECLARATOR							{  724, L"{index}: Invalid declarator" };
		const ErrorInfo ERROR_CPPDOC_INVALID_IDENTIFIER							{  725, L"{index}: Invalid identifier" };
		const ErrorInfo ERROR_CPPDOC_INVALID_IDENTIFIER_DOUBLE_DESTRUCTOR		{  726, L"{index}: Invalid identifier. Double destructor is not allowed" };
		const ErrorInfo ERROR_CPPDOC_INVALID_PARTITION_NAME						{  727, L"{index}: Invalid partition name" };
		const ErrorInfo ERROR_CPPDOC_UNEXPECTED_END								{  728, L"{index}: Unexpected end, the '{name}' is expected" };
		const ErrorInfo ERROR_CPPDOC_UNEXPECTED_END_AFTER_ARRAY					{  729, L"{index}: Unexpected end after array list" };
		const ErrorInfo ERROR_CPPDOC_UNEXPECTED_END_AFTER_ATTRIBUTE_LIST		{  730, L"{index}: Unexpected end after attribute list" };
		const ErrorInfo ERROR_CPPDOC_UNEXPECTED_END_AFTER_DECLARATOR			{  731, L"{index}: Unexpected end after declarator list" };
		const ErrorInfo ERROR_CPPDOC_UNEXPECTED_END_AFTER_MEMBER_INITIALIZATION	{  732, L"{index}: Unexpected end after member initialization" };
		const ErrorInfo ERROR_CPPDOC_UNEXPECTED_END_AFTER_MODULE_NAME			{  733, L"{index}: Unexpected end after module name" };
		const ErrorInfo ERROR_CPPDOC_UNEXPECTED_END_AFTER_PARAMETERS			{  734, L"{index}: Unexpected end after parameters list" };
		const ErrorInfo ERROR_CPPDOC_UNEXPECTED_END_AFTER_PARTITION_NAME		{  735, L"{index}: Unexpected end after partition name" };
		const ErrorInfo ERROR_CPPDOC_UNEXPECTED_END_AFTER_STRING				{  736, L"{index}: Unexpected end after string" };
		const ErrorInfo ERROR_CPPDOC_UNEXPECTED_END_AFTER_TOKEN					{  737, L"{index}: Unexpected end after '{name}'" };
		const ErrorInfo ERROR_CPPDOC_UNEXPECTED_END_EXPECTED_ARGUMENT			{  738, L"{index}: Unexpected end, argument is expected" };
		const ErrorInfo ERROR_CPPDOC_UNEXPECTED_END_EXPECTED_ATTRIBUTE_LIST 	{  739, L"{index}: Unexpected end, attribute list is expected" };
		const ErrorInfo ERROR_CPPDOC_UNEXPECTED_END_EXPECTED_BASE_CLASS			{  740, L"{index}: Unexpected end, base class is expected" };
		const ErrorInfo ERROR_CPPDOC_UNEXPECTED_END_EXPECTED_DECLARATOR			{  741, L"{index}: Unexpected end, declarator is expected" };
		const ErrorInfo ERROR_CPPDOC_UNEXPECTED_END_EXPECTED_IDENTIFIER			{  742, L"{index}: Unexpected end, identifier is expected" };
		const ErrorInfo ERROR_CPPDOC_UNEXPECTED_FUNCTION_DEFINITION				{  743, L"{index}: Unexpected function definition" };
		const ErrorInfo ERROR_CPPDOC_UNION_WITH_BASE_CLASS						{  744, L"{index}: Union cannot have base class" };
	}
}
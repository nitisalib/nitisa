// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			enum class EntityType
			{
				Root,
				Comment,
				Module,
				Import,
				Export,
				LanguageLinkage,
				Empty,
				Block,
				Asm,
				NamespaceAlias,
				Namespace,
				UsingNamespace,
				TypeAlias,
				Using,
				UsingEnum,
				Template,
				Concept,
				Enum, // Declaration specifier
				Enumerator,
				Class, // Declaration specifier
				ClassBase,
				Public,
				Protected,
				Private,
				Friend,
				SimpleDeclaration,
				Typedef, // Declaration specifier
				Inline, // Declaration specifier
				Virtual, // Declaration specifier
				Explicit, // Declaration specifier
				Constexpr, // Declaration specifier
				Consteval, // Declaration specifier
				Constinit, // Declaration specifier
				Register, // Declaration specifier
				Static, // Declaration specifier
				ThreadLocal, // Declaration specifier
				Extern, // Declaration specifier
				Mutable, // Declaration specifier
				Char, // Declaration specifier
				Char8T, // Declaration specifier
				Char16T, // Declaration specifier
				Char32T, // Declaration specifier
				WCharT, // Declaration specifier
				Bool, // Declaration specifier
				Short, // Declaration specifier
				Int, // Declaration specifier
				Long, // Declaration specifier
				Signed, // Declaration specifier
				Unsigned, // Declaration specifier
				Float, // Declaration specifier
				Double, // Declaration specifier
				Void, // Declaration specifier
				Auto, // Declaration specifier
				Decltype, // Declaration specifier
				PackIndexing, // Declaration specifier
				Typename, // Declaration specifier
				Const, // Declaration specifier
				Volatile, // Declaration specifier
				Override, // Declaration specifier
				Final, // Declaration specifier
				LRef, // Declaration specifier
				RRef, // Declaration specifier
				TemplateSpecifier, // Declaration specifier
				Name,
				ParameterPack,
				PtrDeclarator,
				LValueDeclarator,
				RValueDeclarator,
				NoPtrDeclarator,
				IdDeclarator,
				Array,
				Function,
				FunctionParameter,
				FunctionPreContract,
				FunctionPostContract,
				StructuredBinding,
				StaticAssert,
				StdCall,
				CDecl,
				ThisCall,
				FastCall,
				Naked,
			};
		}
	}
}
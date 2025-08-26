// This file is a part of Nitisa framework
// Copyright © 2024 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"

namespace nitisa
{
	class CDbMigrationGenerator
	{
	private:
		using FGenerator = String(*)(const String &tabs, const String &name);

		// Helpers
		static String GenerateTimestamp();
		static String GenerateHeaderFileContent(const String &ts, const String &migration_name, const StringArray &namespaces, const bool revert);
		static String GenerateSourceFileContent(const String &ts, const String &migration_name, const String &name, const StringArray &namespaces, const bool revert, FGenerator generator, FGenerator revert_generator);

		// Generators
		static String EmptyGenerator(const String &tabs, const String &name);
		static String CreateTableGenerator(const String &tabs, const String &name);
		static String DropTableGenerator(const String &tabs, const String &name);
		
		// Generate
		static bool GenerateEmpty(const String &migration_name, const String &path, const StringArray &namespaces, const bool revert);
		static bool GenerateCreateTable(const String &migration_name, const String &table, const String &path, const StringArray &namespaces, const bool revert);
		static bool GenerateDropTable(const String &migration_name, const String &table, const String &path, const StringArray &namespaces);
	public:
		// Generate migration header and source files
		static bool Generate(const String &name, const String &path, const StringArray &namespaces, const bool revert, const bool force_empty); // path should have directory separator at the end
	};
}
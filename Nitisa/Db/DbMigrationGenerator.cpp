// This file is a part of Nitisa framework
// Copyright © 2024 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region Helpers
	String CDbMigrationGenerator::GenerateTimestamp()
	{
		CDateTime dt;
		return
			PadLeft(ToString(dt.getYear()), L'0', 4) +
			PadLeft(ToString(dt.getMonth()), L'0', 2) +
			PadLeft(ToString(dt.getDay()), L'0', 2) +
			PadLeft(ToString(dt.getHour()), L'0', 2) +
			PadLeft(ToString(dt.getMinute()), L'0', 2) +
			PadLeft(ToString(dt.getSecond()), L'0', 2);
	}

	String CDbMigrationGenerator::GenerateHeaderFileContent(const String &ts, const String &migration_name, const StringArray &namespaces, const bool revert)
	{
		String result, tabs;
		result += L"#pragma once\n";
		result += L"\n";
		result += L"#include \"Nitisa/Db/DbMigration.h\"\n";
		result += L"\n";
		for (auto const &ns : namespaces)
		{
			result += tabs + L"namespace " + ns + L"\n";
			result += tabs + L"{\n";
			tabs += L"\t";
		}

		result += tabs + L"class C" + ts + L"_" + migration_name + L" :public CDbMigration\n";
		result += tabs + L"{\n";
		result += tabs + L"public:\n";
		result += tabs + L"\tvoid Run() override;\n";
		if (revert)
			result += tabs + L"\tvoid Revert() override;\n";
		result += L"\n";
		result += tabs + L"\tC" + ts + L"_" + migration_name + L"();\n";
		result += tabs + L"};\n";

		for (size_t i = 0; i < namespaces.size(); i++)
		{
			tabs.pop_back();
			result += tabs + L"}\n";
		}

		if (result[result.length() - 1] == L'\n')
			result.pop_back();

		return result;
	}

	String CDbMigrationGenerator::GenerateSourceFileContent(const String &ts, const String &migration_name, const String &name, const StringArray &namespaces, const bool revert, FGenerator generator, FGenerator revert_generator)
	{
		String result, tabs;
		result += L"#include \"stdafx.h\"\n";
		result += L"\n";
		for (auto const &ns : namespaces)
		{
			result += tabs + L"namespace " + ns + L"\n";
			result += tabs + L"{\n";
			tabs += L"\t";
		}

		result += tabs + L"C" + ts + L"_" + migration_name + L"::C" + ts + L"_" + migration_name + L"() :\n";
		result += tabs + L"\tCDbMigration(L\"C" + ts + L"_" + migration_name + L"\")\n";
		result += tabs + L"{\n";
		result += L"\n";
		result += tabs + L"}\n";
		result += L"\n";
		result += tabs + L"void C" + ts + L"_" + migration_name + L"::Run()\n";
		result += tabs + L"{\n";
		result += generator(tabs, name);
		result += tabs + L"}\n";
		if (revert)
		{
			result += L"\n";
			result += tabs + L"void C" + ts + L"_" + migration_name + L"::Revert()\n";
			result += tabs + L"{\n";
			result += revert_generator(tabs, name);
			result += tabs + L"}\n";
		}

		for (size_t i = 0; i < namespaces.size(); i++)
		{
			tabs.pop_back();
			result += tabs + L"}\n";
		}

		if (result[result.length() - 1] == L'\n')
			result.pop_back();

		return result;
	}
#pragma endregion

#pragma region Generators
	String CDbMigrationGenerator::EmptyGenerator(const String &tabs, const String &name)
	{
		return L"\n";
	}

	String CDbMigrationGenerator::CreateTableGenerator(const String &tabs, const String &name)
	{
		String result;
		
		result += tabs + L"\tCreateTable(\n";
		result += tabs + L"\t\tL\"" + name + L"\"\n";
		result += tabs + L"\t\tIDbMigration::MigrationColumns{\n";
		result += tabs + L"\t\t\tColumn(L\"id\")->Integer()->Unsigned()->NotNull()->PrimaryKey()->AutoIncrement()\n";
		result += tabs + L"\t\t}\n";
		result += tabs + L"\t);\n";

		return result;
	}

	String CDbMigrationGenerator::DropTableGenerator(const String &tabs, const String &name)
	{
		return tabs + L"\tDropTable(L\"" + name + L"\", true);\n";
	}
#pragma endregion

#pragma region Generate
	bool CDbMigrationGenerator::Generate(const String &name, const String &path, const StringArray &namespaces, const bool revert, const bool force_empty)
	{
		String migration_name{ Trim(name) };
		if (migration_name.empty())
			return false;
		String filepath{ Trim(path) };

		if (!force_empty)
		{
			StringArray parts{ Explode(name, L"_") };
			if (parts.size() > 2)
			{
				String action{ ToLower(parts[0]) }, entity{ ToLower(parts[1]) };
				if (action == L"create")
				{
					if (entity == L"table")
					{
						String entity_name{ Implode(L"_", StringArray{ parts.begin() + 2, parts.end()}) };
						return GenerateCreateTable(migration_name, entity_name, filepath, namespaces, revert);
					}
				}
				else if (action == L"drop")
				{
					if (entity == L"table")
					{
						String entity_name{ Implode(L"_", StringArray{ parts.begin() + 2, parts.end()}) };
						return GenerateDropTable(migration_name, entity_name, filepath, namespaces);
					}
				}
			}
		}

		return GenerateEmpty(migration_name, filepath, namespaces, revert);
	}

	bool CDbMigrationGenerator::GenerateEmpty(const String &migration_name, const String &path, const StringArray &namespaces, const bool revert)
	{
		String ts{ GenerateTimestamp() };
		return
			PutUTF8FileContent(path + ts + L"_" + migration_name + L".h", GenerateHeaderFileContent(ts, migration_name, namespaces, revert)) &&
			PutUTF8FileContent(path + ts + L"_" + migration_name + L".cpp", GenerateSourceFileContent(ts, migration_name, L"", namespaces, revert, &EmptyGenerator, &EmptyGenerator));
	}

	bool CDbMigrationGenerator::GenerateCreateTable(const String &migration_name, const String &table, const String &path, const StringArray &namespaces, const bool revert)
	{
		String ts{ GenerateTimestamp() };
		return
			PutUTF8FileContent(path + ts + L"_" + migration_name + L".h", GenerateHeaderFileContent(ts, migration_name, namespaces, revert)) &&
			PutUTF8FileContent(path + ts + L"_" + migration_name + L".cpp", GenerateSourceFileContent(ts, migration_name, table, namespaces, revert, &CreateTableGenerator, &DropTableGenerator));
	}

	bool CDbMigrationGenerator::GenerateDropTable(const String &migration_name, const String &table, const String &path, const StringArray &namespaces)
	{
		String ts{ GenerateTimestamp() };
		return
			PutUTF8FileContent(path + ts + L"_" + migration_name + L".h", GenerateHeaderFileContent(ts, migration_name, namespaces, false)) &&
			PutUTF8FileContent(path + ts + L"_" + migration_name + L".cpp", GenerateSourceFileContent(ts, migration_name, table, namespaces, false, &DropTableGenerator, nullptr));
	}
#pragma endregion
}
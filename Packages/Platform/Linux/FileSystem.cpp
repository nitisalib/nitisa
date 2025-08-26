// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#if defined(__linux__) && !defined(__ANDROID__)
#include <regex>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

namespace nitisa
{
	namespace platform
	{
		namespace linux
		{
			CFileSystem::CFileSystem()
			{
				m_bCaseSensitive = true;
			}

		#pragma region Search
			bool CFileSystem::SearchFiles(const String &filter, SearchFilesResult &result)
			{
				// Divide filter into parts
				StringArray folders{ Explode(filter, L"/") };
				if (folders.size() == 0)
					return false;
				// Prepare path
				AnsiString path;
				for (size_t i = 0; i < folders.size() - 1; i++)
					path += StringToAnsi(folders[i]) + "/";
				if (filter[0] == L'/')
					path = "/" + path;
				// Prepare filter part
				AnsiString t{ StringToAnsi(folders[folders.size() - 1]) }, f;
				for (auto c : t)
					if (c == '*')
						f += ".*";
					else if (c == '?')
						f += ".";
					else if (c == '.')
						f += "\\.";
					else
						f += c;
				std::regex r{ f };
				// Open directory
				DIR *dir{ opendir(path.c_str()) };
				if (!dir)
					return false;
				// Enumerate files
				result.clear();
				while (true)
				{
					dirent *d{ readdir(dir) };
					if (!d)
						break;
					AnsiString filename{ d->d_name };
					if (filename.empty())
						break;
					std::smatch m;
					if (std::regex_search(filename, m, r))
					{
						if (d->d_type == DT_DIR)
							result.push_back({ AnsiToString(filename), 0, false, false, true, false, false, true, false, false, false, false });
						else
						{
							FILE *file{ fopen((path + filename).c_str(), "r") };
							if (file)
							{
								fseek(file, 0, SEEK_END);
								result.push_back({ AnsiToString(filename), (long long)ftell(file), false, false, false, false, false, true, false, false, false, false });
								fclose(file);
							}
						}
					}
				}
				closedir(dir);
				return true;
			}

			StringArray CFileSystem::SearchDrives()
			{
				StringArray result;
				result.push_back(L"/");
				return result;
			}
		#pragma endregion

		#pragma region File methods
			bool CFileSystem::FileExists(const String &filename)
			{
				// Try to open the file
				FILE *file{ fopen(StringToAnsi(filename).c_str(), "r") };
				if (file)
				{
					fclose(file);
					return true;
				}
				return false;
			}

			IFile *CFileSystem::FileOpen(const String &filename, const OpenMode open_mode, const bool read, const bool write, const bool share_delete, const bool share_read,
				const bool share_write, const bool archieved, const bool encrypted, const bool hidden, const bool offline, const bool readonly, const bool system, const bool temporary,
				const bool delete_on_close, const bool no_buffering, const bool random_access)
			{
				AnsiString mode;
				switch (open_mode)
				{
				case OpenMode::CreateAlways:
					mode = "w";
					break;
				case OpenMode::CreateNew:
					mode = "w";
					break;
				case OpenMode::OpenAlways:
					mode = "w";
					break;
				case OpenMode::OpenExisting:
					mode = write ? "w" : "r";
					break;
				case OpenMode::TrancateExisting:
					mode = write ? "w" : "r";
					break;
				}
				FILE *file{ fopen(StringToAnsi(filename).c_str(), mode.c_str()) };
				if (file)
					return new CFile(*reinterpret_cast<PlatformHandle*>(&file), filename);
				return nullptr;
			}

			bool CFileSystem::FileCopy(const String &filename, const String &new_filename, const bool overwrite_existing)
			{
				if (filename == new_filename)
					return false;
				std::ifstream src(StringToAnsi(filename).c_str(), std::ios::binary);
				if (src.bad())
					return false;
				std::ofstream dst(StringToAnsi(new_filename).c_str(), std::ios::binary);
				if (dst.bad())
					return false;
				dst << src.rdbuf();
				return true;
			}

			bool CFileSystem::FileMove(const String &filename, const String &new_filename, const bool overwrite_existing)
			{
				return rename(StringToAnsi(filename).c_str(), StringToAnsi(new_filename).c_str()) == 0;
			}

			bool CFileSystem::FileDelete(const String &filename)
			{
				return remove(StringToAnsi(filename).c_str()) == 0;
			}
		#pragma endregion

		#pragma region Directory methods
			bool CFileSystem::DirectoryExists(const String &path)
			{
				DIR *d{ opendir(StringToAnsi(path).c_str()) };
				if (d)
				{
					closedir(d);
					return true;
				}
				return false;
			}

			bool CFileSystem::DirectoryCreate(const String &path)
			{
				return mkdir(StringToAnsi(path).c_str(), 0777) == 0;
			}

			bool CFileSystem::DirectoryMove(const String &path, const String &new_path, const bool overwrite_existing)
			{
				return rename(StringToAnsi(path).c_str(), StringToAnsi(new_path).c_str()) == 0;
			}

			bool CFileSystem::DirectoryDelete(const String &path)
			{
				return rmdir(StringToAnsi(path).c_str()) == 0;
			}
		#pragma endregion
		}
	}
}
#endif
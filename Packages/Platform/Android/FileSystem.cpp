// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef __ANDROID__
#include <android/asset_manager.h>
#include <regex>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

namespace nitisa
{
	namespace platform
	{
		namespace android
		{
		#pragma region Constructor & destructor
			CFileSystem::CFileSystem(CApplication *application) :
				m_pApplication{ application }
			{
				m_bCaseSensitive = true;
			}
		#pragma endregion

		#pragma region Helpers
			String CFileSystem::ExtractPath(const String &path, bool &assets)
			{
				if (path.find(L"assets:", 0) == 0)
				{
					assets = true;
					return path.substr(7);
				}
				assets = false;
				return path;
			}
		#pragma endregion

		#pragma region Search
			bool CFileSystem::AssetsSearchFiles(const String &filter, SearchFilesResult &result)
			{
				// AssetManager is required
				if (!m_pApplication->getAssetManager())
					return false;
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
				AAssetDir *dir{ AAssetManager_openDir(m_pApplication->getAssetManager(), path.c_str()) };
				if (!dir)
					return false;
				// Enumerate files
				result.clear();
				while (true)
				{
					const char *s{ AAssetDir_getNextFileName(dir) };
					if (!s)
						break;
					AnsiString filename{ s };
					if (filename.empty())
						break;
					std::smatch m;
					if (std::regex_search(filename, m, r))
					{
						AAsset *file{ AAssetManager_open(m_pApplication->getAssetManager(), (path + filename).c_str(), AASSET_MODE_STREAMING) };
						if (file)
						{
							result.push_back({ AnsiToString(filename), (long long)AAsset_getLength64(file), false, false, false, false, false, true, false, false, false, false });
							AAsset_close(file);
						}
					}
				}
				AAssetDir_close(dir);
				return true;
			}

			bool CFileSystem::SearchFiles(const String &filter, SearchFilesResult &result)
			{
				bool is_assets;
				String fltr{ ExtractPath(filter, is_assets) };
				if (is_assets)
					return AssetsSearchFiles(fltr, result);
				
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

				return result;
			}
		#pragma endregion

		#pragma region File methods
			bool CFileSystem::AssetsFileExists(const String &filename)
			{
				// AssetManager is required
				if (!m_pApplication->getAssetManager())
					return false;
				// Try to open the file
				AAsset *file{ AAssetManager_open(m_pApplication->getAssetManager(), StringToAnsi(filename).c_str(), AASSET_MODE_STREAMING) };
				if (file)
				{
					AAsset_close(file);
					return true;
				}
				return false;
			}

			bool CFileSystem::FileExists(const String &filename)
			{
				bool is_assets;
				String flnm{ ExtractPath(filename, is_assets) };
				if (is_assets)
					return AssetsFileExists(flnm);

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
				bool is_assets;
				String flnm{ ExtractPath(filename, is_assets) };
				if (is_assets)
				{
					if (read && !write)
					{
						AAsset *file{ AAssetManager_open(m_pApplication->getAssetManager(), StringToAnsi(filename).c_str(), AASSET_MODE_STREAMING) };
						if (file)
							return new CFile(file, filename);
					}
					return nullptr;
				}

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
					return new CFile(file, filename);
				return nullptr;
			}

			bool CFileSystem::FileCopy(const String &filename, const String &new_filename, const bool overwrite_existing)
			{
				bool is_assets;
				ExtractPath(filename, is_assets);
				if (is_assets)
					return false;
				ExtractPath(new_filename, is_assets);
				if (is_assets)
					return false;

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
				bool is_assets;
				ExtractPath(filename, is_assets);
				if (is_assets)
					return false;
				ExtractPath(new_filename, is_assets);
				if (is_assets)
					return false;

				return rename(StringToAnsi(filename).c_str(), StringToAnsi(new_filename).c_str()) == 0;
			}

			bool CFileSystem::FileDelete(const String &filename)
			{
				bool is_assets;
				ExtractPath(filename, is_assets);
				if (is_assets)
					return false;

				return remove(StringToAnsi(filename).c_str()) == 0;
			}
		#pragma endregion

		#pragma region Directory methods
			bool CFileSystem::AssetsDirectoryExists(const String &path)
			{
				// AssetManager is required
				if (!m_pApplication->getAssetManager())
					return false;
				// Open directory
				AAssetDir *dir{ AAssetManager_openDir(m_pApplication->getAssetManager(), StringToAnsi(path).c_str()) };
				if (!dir)
					return false;
				AAssetDir_close(dir);
				return true;
			}

			bool CFileSystem::DirectoryExists(const String &path)
			{
				bool is_assets;
				String p{ ExtractPath(path, is_assets) };
				if (is_assets)
					return AssetsDirectoryExists(p);
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
				bool is_assets;
				ExtractPath(path, is_assets);
				if (is_assets)
					return false;

				return mkdir(StringToAnsi(path).c_str(), 0777) == 0;
			}

			bool CFileSystem::DirectoryMove(const String &path, const String &new_path, const bool overwrite_existing)
			{
				bool is_assets;
				ExtractPath(path, is_assets);
				if (is_assets)
					return false;
				ExtractPath(new_path, is_assets);
				if (is_assets)
					return false;

				return rename(StringToAnsi(path).c_str(), StringToAnsi(new_path).c_str()) == 0;
			}

			bool CFileSystem::DirectoryDelete(const String &path)
			{
				bool is_assets;
				ExtractPath(path, is_assets);
				if (is_assets)
					return false;

				return rmdir(StringToAnsi(path).c_str()) == 0;
			}
		#pragma endregion
		}
	}
}
#endif
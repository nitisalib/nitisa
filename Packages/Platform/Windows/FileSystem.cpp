// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>

namespace nitisa
{
	namespace platform
	{
		namespace windows
		{
			CFileSystem::CFileSystem()
			{
				m_bCaseSensitive = false;
			}

			bool CFileSystem::SearchFiles(const String &filter, SearchFilesResult &result)
			{
				WIN32_FIND_DATA data;
				HANDLE handle{ FindFirstFileW(filter.c_str(), &data) };
				if (handle != INVALID_HANDLE_VALUE)
				{
					result.clear();
					do
					{
						SearchFileInfo info;
						info.Name = data.cFileName;
						info.Size = ((unsigned __int64)data.nFileSizeHigh << 32) + data.nFileSizeLow;
						info.Archieved = data.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE;
						info.Compressed = data.dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED;
						info.Directory = data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
						info.Encrypted = data.dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED;
						info.Hidden = data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN;
						info.Normal = data.dwFileAttributes & FILE_ATTRIBUTE_NORMAL;
						info.Offline = data.dwFileAttributes & FILE_ATTRIBUTE_OFFLINE;
						info.Readonly = data.dwFileAttributes & FILE_ATTRIBUTE_READONLY;
						info.System = data.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM;
						info.Temporary = data.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY;
						result.push_back(info);

					} while (FindNextFileW(handle, &data) != 0);
					FindClose(handle);
					return true;
				}
				return false;
			}

			bool CFileSystem::FileExists(const String &filename)
			{
				DWORD attributes{ GetFileAttributesW(filename.c_str()) };
				return attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY);
			}

			bool CFileSystem::DirectoryExists(const String &path)
			{
				DWORD attributes{ GetFileAttributesW(path.c_str()) };
				return attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY);
			}

			StringArray CFileSystem::SearchDrives()
			{
				StringArray result;
				wchar_t volume_name[MAX_PATH] = L"";
				HANDLE handle{ FindFirstVolume(volume_name, MAX_PATH) };
				if (handle != INVALID_HANDLE_VALUE)
				{
					do
					{
						DWORD char_count{ MAX_PATH + 1 };
						wchar_t *names{ nullptr }, *name_idx{ nullptr };
						bool success{ false };

						for (;;)
						{
							names = new wchar_t[char_count];
							success = GetVolumePathNamesForVolumeNameW(volume_name, names, char_count, &char_count);
							if (success)
								break;
							if (GetLastError() != ERROR_MORE_DATA)
								break;
							delete[] names;
							names = nullptr;
						}
						if (success)
							for (name_idx = names; name_idx[0] != L'\0'; name_idx += wcslen(name_idx) + 1)
								if (name_idx[1] == L':')
								{
									result.push_back(name_idx);
									break;
								}
						if (names)
							delete[] names;
					} while (FindNextVolume(handle, volume_name, MAX_PATH));
					FindVolumeClose(handle);
				}
				return result;
			}

			IFile *CFileSystem::FileOpen(const String &filename, const OpenMode open_mode, const bool read, const bool write, const bool share_delete, const bool share_read,
				const bool share_write, const bool archieved, const bool encrypted, const bool hidden, const bool offline, const bool readonly, const bool system, const bool temporary,
				const bool delete_on_close, const bool no_buffering, const bool random_access)
			{
				DWORD access{ 0 }, share{ 0 }, mode{ 0 }, flags{ 0 };
				if (read)
					access |= GENERIC_READ;
				if (write)
					access |= GENERIC_WRITE;
				if (share_delete)
					share |= FILE_SHARE_DELETE;
				if (share_read)
					share |= FILE_SHARE_READ;
				if (share_write)
					share |= FILE_SHARE_WRITE;
				switch (open_mode)
				{
				case OpenMode::CreateAlways:
					mode = CREATE_ALWAYS;
					break;
				case OpenMode::CreateNew:
					mode = CREATE_NEW;
					break;
				case OpenMode::OpenAlways:
					mode = OPEN_ALWAYS;
					break;
				case OpenMode::OpenExisting:
					mode = OPEN_EXISTING;
					break;
				case OpenMode::TrancateExisting:
					mode = TRUNCATE_EXISTING;
					break;
				}
				if (archieved)
					flags |= FILE_ATTRIBUTE_ARCHIVE;
				if (encrypted)
					flags |= FILE_ATTRIBUTE_ENCRYPTED;
				if (hidden)
					flags |= FILE_ATTRIBUTE_HIDDEN;
				if (offline)
					flags |= FILE_ATTRIBUTE_OFFLINE;
				if (readonly)
					flags |= FILE_ATTRIBUTE_READONLY;
				if (system)
					flags |= FILE_ATTRIBUTE_SYSTEM;
				if (temporary)
					flags |= FILE_ATTRIBUTE_TEMPORARY;
				if (delete_on_close)
					flags |= FILE_FLAG_DELETE_ON_CLOSE;
				if (no_buffering)
					flags |= FILE_FLAG_NO_BUFFERING;
				if (random_access)
					flags |= FILE_FLAG_RANDOM_ACCESS;
				if (flags == 0)
					flags = FILE_ATTRIBUTE_NORMAL;
				HANDLE handle{ CreateFile(filename.c_str(), access, share, nullptr, mode, flags, nullptr) };
				if (handle != INVALID_HANDLE_VALUE)
					return new CFile((void*)handle, filename);
				return nullptr;
			}

			bool CFileSystem::FileCopy(const String &filename, const String &new_filename, const bool overwrite_existing)
			{
				return CopyFile(filename.c_str(), new_filename.c_str(), !overwrite_existing);
			}

			bool CFileSystem::FileMove(const String &filename, const String &new_filename, const bool overwrite_existing)
			{
				return MoveFileEx(filename.c_str(), new_filename.c_str(), overwrite_existing ? MOVEFILE_REPLACE_EXISTING : 0);
			}

			bool CFileSystem::FileDelete(const String &filename)
			{
				return DeleteFile(filename.c_str());
			}

			bool CFileSystem::DirectoryCreate(const String &path)
			{
				return CreateDirectory(path.c_str(), nullptr);
			}

			bool CFileSystem::DirectoryMove(const String &path, const String &new_path, const bool overwrite_existing)
			{
				return MoveFileEx(path.c_str(), new_path.c_str(), overwrite_existing ? MOVEFILE_REPLACE_EXISTING : 0);
			}

			bool CFileSystem::DirectoryDelete(const String &path)
			{
				return RemoveDirectory(path.c_str());
			}
		}
	}
}
#endif
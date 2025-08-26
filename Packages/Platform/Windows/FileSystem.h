// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef _WIN32
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IFileSystem.h"

namespace nitisa
{
	class IFile;

	namespace platform
	{
		namespace windows
		{
			class CFileSystem :public virtual IFileSystem
			{
			public:
				bool SearchFiles(const String &filter, SearchFilesResult &result) override;
				bool FileExists(const String &filename) override;
				bool DirectoryExists(const String &path) override;
				StringArray SearchDrives() override;
				IFile *FileOpen(const String &filename, const OpenMode open_mode, const bool read, const bool write, const bool share_delete = false, const bool share_read = false,
					const bool share_write = false, const bool archieved = false, const bool encrypted = false, const bool hidden = false, const bool offline = false, const bool readonly = false,
					const bool system = false, const bool temporary = false, const bool delete_on_close = false, const bool no_buffering = false, const bool random_access = false) override;
				bool FileCopy(const String &filename, const String &new_filename, const bool overwrite_existing) override;
				bool FileMove(const String &filename, const String &new_filename, const bool overwrite_existing) override;
				bool FileDelete(const String &filename) override;
				bool DirectoryCreate(const String &path) override;
				bool DirectoryMove(const String &path, const String &new_path, const bool overwrite_existing) override;
				bool DirectoryDelete(const String &path) override;

				CFileSystem();
			};
		}
	}
}
#endif
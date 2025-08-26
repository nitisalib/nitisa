// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IFileSystem.h"

namespace nitisa
{
	class IFile;

	namespace platform
	{
		namespace android
		{
			class CApplication;

			// To work with application assets instead of file system use assets: prefix in filters, names, pathes. Please note, assets are readonly, any changes will fail
			class CFileSystem :public virtual IFileSystem
			{
			private:
				CApplication * m_pApplication;

				String ExtractPath(const String &path, bool &assets);
				bool AssetsSearchFiles(const String &filter, SearchFilesResult &result);
				bool AssetsFileExists(const String &filename);
				bool AssetsDirectoryExists(const String &path);
			public:
				bool SearchFiles(const String &filter, SearchFilesResult &result) override; // In case of searching in assets only files could be searched. There is no way to search directories in the assets using Android NDK
				bool FileExists(const String &filename) override;
				bool DirectoryExists(const String &path) override;
				StringArray SearchDrives() override; // Not supported. Return empty result
				IFile *FileOpen(const String &filename, const OpenMode open_mode, const bool read, const bool write,
					// Following remaining parameters are not supported
					const bool share_delete = false, const bool share_read = false, const bool share_write = false, const bool archieved = false, const bool encrypted = false,
					const bool hidden = false, const bool offline = false, const bool readonly = false, const bool system = false, const bool temporary = false, const bool delete_on_close = false,
					const bool no_buffering = false, const bool random_access = false) override;
				bool FileCopy(const String &filename, const String &new_filename,
					const bool overwrite_existing) override; // This parameter is not supported
				bool FileMove(const String &filename, const String &new_filename,
					const bool overwrite_existing) override; // This parameter is not supported
				bool FileDelete(const String &filename) override;
				bool DirectoryCreate(const String &path) override;
				bool DirectoryMove(const String &path, const String &new_path, const bool overwrite_existing) override;
				bool DirectoryDelete(const String &path) override;

				CFileSystem(CApplication *application);
			};
		}
	}
}
#endif
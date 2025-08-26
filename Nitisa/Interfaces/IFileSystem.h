// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include <vector>

namespace nitisa
{
	class IFile;

	class IFileSystem
	{
	protected:
		IFileSystem() = default;
		~IFileSystem() = default;
		IFileSystem(const IFileSystem &other) = delete;
		IFileSystem(IFileSystem &&other) = delete;
		IFileSystem &operator=(const IFileSystem &other) = delete;
		IFileSystem &operator=(IFileSystem &&other) = delete;
	public:
		enum class OpenMode // File open modes
		{
			CreateAlways, // Creates a new file, always
			CreateNew, // Creates a new file, only if it does not already exist
			OpenAlways, // Opens a file, always
			OpenExisting, // Opens a file or device, only if it exists
			TrancateExisting // Opens a file and truncates it so that its size is zero bytes, only if it exists
		};

		struct SearchFileInfo // Describes file/directory
		{
			String Name; // Name without path
			long long Size; // Size
			bool Archieved; // Whether it is archieved
			bool Compressed; // Whether it is compressed
			bool Directory; // Whether it is directory
			bool Encrypted; // Whether it is encrypted
			bool Hidden; // Whether it is hidden
			bool Normal; // Whether it is normal file
			bool Offline; // Whether it is offline
			bool Readonly; // Whether it is readonly
			bool System; // Whether it is system file
			bool Temporary; // Whether it is temporary file
		};

		using SearchFilesResult = std::vector<SearchFileInfo>; // Array of file descriptions
	protected:
		bool m_bCaseSensitive;
	public:
		bool const &CaseSensitive{ m_bCaseSensitive };

		virtual bool SearchFiles(const String &filter, SearchFilesResult &result) = 0; // Search files. Filter is like C:\*.* or D:\docs\?ooking*.pdf
		virtual bool FileExists(const String &filename) = 0; // Check whether specified file exists
		virtual bool DirectoryExists(const String &path) = 0; // Check whether specified directory exists
		virtual StringArray SearchDrives() = 0; // Return all found drives(volumes) which are mounted as drives
		virtual IFile *FileOpen( // Create or open a file. Return nullptr if failed
			const String &filename, // The name of the file or device to be created or opened
			const OpenMode open_mode,
			const bool read, // Whether read access is required
			const bool write, // Whether write access is required
			const bool share_delete = false, // Enables subsequent open operations on a file or device to request delete access
			const bool share_read = false, // Enables subsequent open operations on a file or device to request read access
			const bool share_write = false, // Enables subsequent open operations on a file or device to request write access
			const bool archieved = false, // The file should be archived
			const bool encrypted = false, // The file or directory is encrypted
			const bool hidden = false, // The file is hidden
			const bool offline = false, // The data of a file is not immediately available
			const bool readonly = false, // The file is read only
			const bool system = false, // The file is part of or used exclusively by an operating system
			const bool temporary = false, // The file is being used for temporary storage
			const bool delete_on_close = false, // The file is to be deleted immediately after all of its handles are closed
			const bool no_buffering = false, // The file or device is being opened with no system caching for data reads and writes
			const bool random_access = false) = 0; // Access is intended to be random. The system can use this as a hint to optimize file caching
		virtual bool FileCopy(const String &filename, const String &new_filename, const bool overwrite_existing) = 0; // Copy file
		virtual bool FileMove(const String &filename, const String &new_filename, const bool overwrite_existing) = 0; // Rename file
		virtual bool FileDelete(const String &filename) = 0; // Delete file
		virtual bool DirectoryCreate(const String &path) = 0; // Create new directory
		virtual bool DirectoryMove(const String &path, const String &new_path, const bool overwrite_existing) = 0; // Rename directory
		virtual bool DirectoryDelete(const String &path) = 0; // Delete directory. Usually should be empty
	};
}
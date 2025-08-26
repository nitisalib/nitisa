// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"

namespace nitisa
{
	class IFile
	{
	protected:
		IFile() = default;
		~IFile() = default;
		IFile(const IFile &other) = delete;
		IFile(IFile &&other) = delete;
		IFile &operator=(const IFile &other) = delete;
		IFile &operator=(IFile &&other) = delete;
	public:
		enum class SeekFrom // How to set file pointer
		{
			Begin, // Starting from the beginning of the file
			Current, // Starting from current pointer value
			End // Starting from the end of the file
		};
	protected:
		String m_sFilename;
	public:
		String const &Filename{ m_sFilename }; // File name

		virtual long long getSize() = 0; // Return file size
		virtual long long getPointer() = 0; // Return pointer position

		virtual bool setPointer(const long long value, const SeekFrom seek_from) = 0; // Set pointer in file to new position

		virtual bool Read( // Read data from file to specified buffer. Check not only the result value but also if "read" value is correct!
			const unsigned int size, // Count of bytes to read(should be <= size of buffer)
			unsigned char *buffer, // Destination of read data
			unsigned long &read) = 0; // Store actual number of read bytes
		virtual bool Write( // Write data from specified buffer to file. Check not only the return value but also if "written" value is correct!
			const unsigned int size, // Number of bytes to write from the buffer
			unsigned char *buffer, // Buffer which data should be put into file
			unsigned long &written) = 0; // Store actual number of written bytes

		virtual void Release() = 0; // Close file and release the object
	};
}
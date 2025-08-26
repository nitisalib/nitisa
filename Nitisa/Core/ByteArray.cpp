// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	ByteArray Merge(const std::vector<ByteArray> &arrays)
	{
		ByteArray result;
		size_t size{ 0 };
		for (auto &arr : arrays)
			size += arr.size();
		if (size > 0)
		{
			result.resize(size);
			size_t index{ 0 };
			for (auto &arr : arrays)
				for (size_t i = 0; i < arr.size(); i++)
					result[index++] = arr[i];
		}
		return result;
	}
}
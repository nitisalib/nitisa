// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Progress.h"
#include "../Core/ProgressStage.h"

namespace nitisa
{
	namespace script
	{
		class IProgressListener
		{
		protected:
			IProgressListener() = default;
			~IProgressListener() = default;
			IProgressListener(const IProgressListener &other) = delete;
			IProgressListener(IProgressListener &&other) = delete;
			IProgressListener &operator=(const IProgressListener &other) = delete;
			IProgressListener &operator=(IProgressListener &&other) = delete;
		public:
			virtual void NotifyOnProgress(const ProgressStage stage, const Progress &progress, bool &abort) = 0; // Method called during execution progress. To stop the "abort" may be changed to false
		};
	}
}
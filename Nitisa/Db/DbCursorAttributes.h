// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"

namespace nitisa
{
	struct DbCursorAttributes
	{
		bool Valid; // Indicates whether this structure contains valid data (it was successfully retrieved from data source)
		bool Next;
		bool Absolute;
		bool Relative;
		bool Bookmark;
		bool LockExclusive;
		bool LockNoChange;
		bool LockUnlock;
		bool PosPosition;
		bool PosUpdate;
		bool PosDelete;
		bool PosRefresh;
		bool PositionedUpdate;
		bool PositionedDelete;
		bool SelectForUpdate;
		bool BulkAdd;
		bool BulkUpdateByBookmark;
		bool BulkDeleteByBookmark;
		bool BulkFetchByBookmark;
		bool ReadOnlyConcurrency;
		bool LockConcurrency;
		bool OptimisticRowConcurrency;
		bool OptimisticValueConcurrency;
		bool SensitivityAdditions;
		bool SensitivityDeletions;
		bool SensitivityUpdates;
		bool MaximumRowsSelect;
		bool MaximumRowsInsert;
		bool MaximumRowsDelete;
		bool MaximumRowsUpdate;
		bool MaximumRowsCatalog;
		bool MaximumRowsAffectsAll;
		bool ExactRowCount;
		bool ApproximateRowCount;
		bool SimulateNonUnique;
		bool SimulateTryUnique;
		bool SimulateUnique;

		explicit operator String() const;
	};
}
// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	DbCursorAttributes::operator String() const
	{
		StringArray list;
		if (Next) list.push_back(L"Next");
		if (Absolute) list.push_back(L"Absolute");
		if (Relative) list.push_back(L"Relative");
		if (Bookmark) list.push_back(L"Bookmark");
		if (LockExclusive) list.push_back(L"LockExclusive");
		if (LockNoChange) list.push_back(L"LockNoChange");
		if (LockUnlock) list.push_back(L"LockUnlock");
		if (PosPosition) list.push_back(L"PosPosition");
		if (PosUpdate) list.push_back(L"PosUpdate");
		if (PosDelete) list.push_back(L"PosDelete");
		if (PosRefresh) list.push_back(L"PosRefresh");
		if (PositionedUpdate) list.push_back(L"PositionedUpdate");
		if (PositionedDelete) list.push_back(L"PositionedDelete");
		if (SelectForUpdate) list.push_back(L"SelectForUpdate");
		if (BulkAdd) list.push_back(L"BulkAdd");
		if (BulkUpdateByBookmark) list.push_back(L"BulkUpdateByBookmark");
		if (BulkDeleteByBookmark) list.push_back(L"BulkDeleteByBookmark");
		if (BulkFetchByBookmark) list.push_back(L"BulkFetchByBookmark");
		if (ReadOnlyConcurrency) list.push_back(L"ReadOnlyConcurrency");
		if (LockConcurrency) list.push_back(L"LockConcurrency");
		if (OptimisticRowConcurrency) list.push_back(L"OptimisticRowConcurrency");
		if (OptimisticValueConcurrency) list.push_back(L"OptimisticValueConcurrency");
		if (SensitivityAdditions) list.push_back(L"SensitivityAdditions");
		if (SensitivityDeletions) list.push_back(L"SensitivityDeletions");
		if (SensitivityUpdates) list.push_back(L"SensitivityUpdates");
		if (MaximumRowsSelect) list.push_back(L"MaximumRowsSelect");
		if (MaximumRowsInsert) list.push_back(L"MaximumRowsInsert");
		if (MaximumRowsDelete) list.push_back(L"MaximumRowsDelete");
		if (MaximumRowsUpdate) list.push_back(L"MaximumRowsUpdate");
		if (MaximumRowsCatalog) list.push_back(L"MaximumRowsCatalog");
		if (MaximumRowsAffectsAll) list.push_back(L"MaximumRowsAffectsAll");
		if (ExactRowCount) list.push_back(L"ExactRowCount");
		if (ApproximateRowCount) list.push_back(L"ApproximateRowCount");
		if (SimulateNonUnique) list.push_back(L"SimulateNonUnique");
		if (SimulateTryUnique) list.push_back(L"SimulateTryUnique");
		if (SimulateUnique) list.push_back(L"SimulateUnique");
		return Implode(L", ", list);
	}
}
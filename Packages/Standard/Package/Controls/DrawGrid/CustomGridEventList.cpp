// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace standard
	{
		CCustomGridEventList::CCustomGridEventList(IPackage *package, IControl *control, IPackageEntity *entity) :CControlEventList(package, control, entity)
		{
			// Other input events
			Delete(L"OnHotkey");

			// Events from child controls
			Delete(L"OnChildStyleChange");
			Delete(L"OnChildFontChange");
			Delete(L"OnChildTransform");
			Delete(L"OnChildResize");
			Delete(L"OnChildShow");
			Delete(L"OnChildHide");
			Delete(L"OnChildAttach");
			Delete(L"OnChildDetach");
			Delete(L"OnChildEnable");
			Delete(L"OnChildDisable");

			// State change events
			Delete(L"OnTransformControls");
			Delete(L"OnSetModal");
			Delete(L"OnKillModal");
			Delete(L"OnSetCaptureKeyboard");
			Delete(L"OnKillCaptureKeyboard");
			Delete(L"OnActivate");
			Delete(L"OnDeactivate");

			Add(new CEvent(this, control, L"OnRenderCell", L"{namespace}ICustomGrid *sender, const int column, const int row, IListItem *item, const Matrix &matrix, const Block *block", L"sender, column, row, item, matrix, block"))
				->AddForwardDeclaration(L"class ICustomGrid;", L"Standard/Controls/IDrawGrid.h", L"standard")
				->AddForwardDeclaration(L"class IListItem;", L"Nitisa/Interfaces/IListItem.h", L"")
				->AddForwardDeclaration(L"struct Block;", L"Nitisa/Math/Block.h", L"")
				->AddHeaderFile(L"Nitisa/Math/Mat4f.h");
			Add(new CEvent(this, control, L"OnHoverCell", L"{namespace}ICustomGrid *sender, const int column, const int row, IListItem *item", L"sender, column, row, item"))
				->AddForwardDeclaration(L"class ICustomGrid;", L"Standard/Controls/IDrawGrid.h", L"standard")
				->AddForwardDeclaration(L"class IListItem;", L"Nitisa/Interfaces/IListItem.h", L"");
			Add(new CEvent(this, control, L"OnLeaveCell", L"{namespace}ICustomGrid *sender, const int column, const int row, IListItem *item", L"sender, column, row, item"))
				->AddForwardDeclaration(L"class ICustomGrid;", L"Standard/Controls/IDrawGrid.h", L"standard")
				->AddForwardDeclaration(L"class IListItem;", L"Nitisa/Interfaces/IListItem.h", L"");
			Add(new CEvent(this, control, L"OnSelectCell", L"{namespace}ICustomGrid *sender, const int column, const int row, IListItem *item", L"sender, column, row, item"))
				->AddForwardDeclaration(L"class ICustomGrid;", L"Standard/Controls/IDrawGrid.h", L"standard")
				->AddForwardDeclaration(L"class IListItem;", L"Nitisa/Interfaces/IListItem.h", L"");
			Add(new CEvent(this, control, L"OnDeselectCell", L"{namespace}ICustomGrid *sender, const int column, const int row, IListItem *item", L"sender, column, row, item"))
				->AddForwardDeclaration(L"class ICustomGrid;", L"Standard/Controls/IDrawGrid.h", L"standard")
				->AddForwardDeclaration(L"class IListItem;", L"Nitisa/Interfaces/IListItem.h", L"");
			Add(new CEvent(this, control, L"OnActivateCell", L"{namespace}ICustomGrid *sender, const int column, const int row, IListItem *item", L"sender, column, row, item"))
				->AddForwardDeclaration(L"class ICustomGrid;", L"Standard/Controls/IDrawGrid.h", L"standard")
				->AddForwardDeclaration(L"class IListItem;", L"Nitisa/Interfaces/IListItem.h", L"");
			Add(new CEvent(this, control, L"OnDeactivateCell", L"{namespace}ICustomGrid *sender, const int column, const int row, IListItem *item", L"sender, column, row, item"))
				->AddForwardDeclaration(L"class ICustomGrid;", L"Standard/Controls/IDrawGrid.h", L"standard")
				->AddForwardDeclaration(L"class IListItem;", L"Nitisa/Interfaces/IListItem.h", L"");
			Add(new CEvent(this, control, L"OnEnableCell", L"{namespace}ICustomGrid *sender, const int column, const int row, IListItem *item", L"sender, column, row, item"))
				->AddForwardDeclaration(L"class ICustomGrid;", L"Standard/Controls/IDrawGrid.h", L"standard")
				->AddForwardDeclaration(L"class IListItem;", L"Nitisa/Interfaces/IListItem.h", L"");
			Add(new CEvent(this, control, L"OnDisableCell", L"{namespace}ICustomGrid *sender, const int column, const int row, IListItem *item", L"sender, column, row, item"))
				->AddForwardDeclaration(L"class ICustomGrid;", L"Standard/Controls/IDrawGrid.h", L"standard")
				->AddForwardDeclaration(L"class IListItem;", L"Nitisa/Interfaces/IListItem.h", L"");
			Add(new CEvent(this, control, L"OnMouseDownCell", L"{namespace}ICustomGrid *sender, const int column, const int row, IListItem *item, const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift", L"sender, column, row, item, position, left, middle, right, ctrl, alt, shift"))
				->AddForwardDeclaration(L"class ICustomGrid;", L"Standard/Controls/IDrawGrid.h", L"standard")
				->AddForwardDeclaration(L"class IListItem;", L"Nitisa/Interfaces/IListItem.h", L"")
				->AddHeaderFile(L"Nitisa/Math/PointF.h");
			Add(new CEvent(this, control, L"OnMouseUpCell", L"{namespace}ICustomGrid *sender, const int column, const int row, IListItem *item, const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift", L"sender, column, row, item, position, left, middle, right, ctrl, alt, shift"))
				->AddForwardDeclaration(L"class ICustomGrid;", L"Standard/Controls/IDrawGrid.h", L"standard")
				->AddForwardDeclaration(L"class IListItem;", L"Nitisa/Interfaces/IListItem.h", L"")
				->AddHeaderFile(L"Nitisa/Math/PointF.h");
			Add(new CEvent(this, control, L"OnMouseMoveCell", L"{namespace}ICustomGrid *sender, const int column, const int row, IListItem *item, const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, bool &repaint_required", L"sender, column, row, item, position, left, middle, right, ctrl, alt, shift, repaint_required"))
				->AddForwardDeclaration(L"class ICustomGrid;", L"Standard/Controls/IDrawGrid.h", L"standard")
				->AddForwardDeclaration(L"class IListItem;", L"Nitisa/Interfaces/IListItem.h", L"")
				->AddHeaderFile(L"Nitisa/Math/PointF.h");
		}
	}
}
// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ControlService.h"
#include "Nitisa/Core/FocusedBy.h"
#include "Nitisa/Core/Messages.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/PointB.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"

namespace nitisa
{
	class IComponent;
	class IControl;

	namespace ide
	{
		class CFormEditor;

		class CFormEditorService :public CControlService
		{
		private:
			CFormEditor *m_pEditor;
			Mat4f m_sFormToEditor;
			PointF m_sDownPoint;
			PointF m_sDownPointEditor;
			RectF m_sSelectionRect;
			bool m_bMaskActive;

			void AttachControl(IControl *control);
			bool RemoveInvalidControls();
			void MouseDownCancel(const bool check_capture, const PointF &position);
			void MouseDown(const MessageMouse &m);
			void MouseUp(const MessageMouse &m);
			void MouseMove(const MessageMouse &m);
			void StoreTransform(const PointF &position); // Position is mouse position in form coordinate system
			void ResizeLeft(const PointF &position, const PointB &grid_enabled);
			void ResizeTop(const PointF &position, const PointB &grid_enabled);
			void ResizeRight(const PointF &position, const PointB &grid_enabled);
			void ResizeBottom(const PointF &position, const PointB &grid_enabled);
			void ResizeLeftTop(const PointF &position, const PointB &grid_enabled);
			void ResizeRightTop(const PointF &position, const PointB &grid_enabled);
			void ResizeRightBottom(const PointF &position, const PointB &grid_enabled);
			void ResizeLeftBottom(const PointF &position, const PointB &grid_enabled);
			void Rotate(const PointF &position);
			void Translate(const PointF &position, const PointB &grid_enabled);
			void Select(const PointF &position);
			void DeselectAllExceptComponent(const int index);
			void DeselectAllExceptControl(const int index);
			bool DeselectChildControls();
			void ProcessKeyUp();
			void ProcessKeyDown();
			void ProcessKeyLeft();
			void ProcessKeyRight();
			void ProcessSelectAll();
		public:
			CFormEditorService(CFormEditor *editor);

			// State change notifications
			void NotifyOnAttach() override;
			void NotifyOnDetach() override;
			void NotifyOnFreeResources() override;

			// Other components/controls/objects change notifications
			void NotifyOnComponentAttach(IComponent *component) override;
			void NotifyOnComponentDetach(IComponent *component) override;
			void NotifyOnControlAttach(IControl *control) override;
			void NotifyOnControlDetach(IControl *control) override;

			// Notifications from parent control
			void NotifyOnParentStyleChange() override;

			// State change notifications
			void NotifyOnStyleChange() override;
			void NotifyOnResize() override;
			void NotifyOnEnable() override;
			void NotifyOnDisable() override;
			void NotifyOnMouseHover(const MessagePosition &m) override;
			void NotifyOnMouseLeave() override;
			void NotifyOnKillCaptureMouse() override;
			void NotifyOnTransformControls() override; // Repaint due to grid may be disabled

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;
			void NotifyOnPaintEnd(const MessagePaint &m) override;

			// Input notifications
			void NotifyOnKeyDown(const MessageKey &m, bool &processed) override;
			void NotifyOnMouseMove(const MessageMouse &m, bool &processed) override;
			void NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed) override;
			void NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed) override;
			void NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed) override;
			void NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed) override;
			void NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed) override;
			void NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed) override;
			void NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed) override;
			void NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed) override;
			void NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed) override;

			// Interceptors
			bool InterceptSetCursor(IControl *control) override;
			bool InterceptMouseHover(IControl *control) override;
			bool InterceptShowHint(IControl *control, String &hint) override;
			bool InterceptTabOrder() override;
			bool InterceptHotkeys(IControl *control, const MessageHotkey &m) override;
			bool InterceptKeyDown(IControl *control, const MessageKey &m) override;
			bool InterceptKeyUp(IControl *control, const MessageKey &m) override;
			bool InterceptChar(IControl *control, const MessageChar &m) override;
			bool InterceptDeadChar(IControl *control, const MessageChar &m) override;
			bool InterceptMouseMove(IControl *control, const MessageMouse &m) override;
			bool InterceptLeftMouseButtonDown(IControl *control, const MessageMouse &m) override;
			bool InterceptLeftMouseButtonUp(IControl *control, const MessageMouse &m) override;
			bool InterceptLeftMouseButtonDoubleClick(IControl *control, const MessageMouse &m) override;
			bool InterceptMiddleMouseButtonDown(IControl *control, const MessageMouse &m) override;
			bool InterceptMiddleMouseButtonUp(IControl *control, const MessageMouse &m) override;
			bool InterceptMiddleMouseButtonDoubleClick(IControl *control, const MessageMouse &m) override;
			bool InterceptRightMouseButtonDown(IControl *control, const MessageMouse &m) override;
			bool InterceptRightMouseButtonUp(IControl *control, const MessageMouse &m) override;
			bool InterceptRightMouseButtonDoubleClick(IControl *control, const MessageMouse &m) override;
			bool InterceptMouseVerticalWheel(IControl *control, const MessageMouseWheel &m) override;
			bool InterceptMouseHorizontalWheel(IControl *control, const MessageMouseWheel &m) override;
			bool InterceptDropFiles(IControl *control, const MessageDropFiles &m) override;
			bool InterceptFocus(IControl *control, const FocusedBy focused_by) override;
		};
	}
}
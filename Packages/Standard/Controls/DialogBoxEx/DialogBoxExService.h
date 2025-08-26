// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/DialogBoxService.h"
#include "Nitisa/Core/Messages.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/PointF.h"

namespace nitisa
{
	class IComponent;
	class IControl;

	namespace standard
	{
		class CDialogBoxEx;

		class CDialogBoxExService :public CDialogBoxService
		{
		private:
			CDialogBoxEx *m_pControl;
			bool m_bMaskActive;
			PointF m_sDownLocal;
			PointF m_sDownTransform;
			PointF m_sDownSize;
			Mat4f m_sDownMatrixInversed;

			void CancelDown(const bool check_capture);
			void ProcessMoveLeftTopCorner(const PointF &position);
			void ProcessMoveRightTopCorner(const PointF &position);
			void ProcessMoveRightBottomCorner(const PointF &position);
			void ProcessMoveLeftBottomCorner(const PointF &position);
			void ProcessMoveLeftBorder(const PointF &position);
			void ProcessMoveTopBorder(const PointF &position);
			void ProcessMoveRightBorder(const PointF &position);
			void ProcessMoveBottomBorder(const PointF &position);
			void ProcessMoveCaption(const PointF &position);
		public:
			CDialogBoxExService(CDialogBoxEx *control);

			// State change notifications
			void NotifyOnAttach() override;
			void NotifyOnFreeResources() override;

			// Component notifications
			void NotifyOnComponentDetach(IComponent *component) override;
			void NotifyOnComponentChange(IComponent *component) override;

			// Control notifications
			void NotifyOnControlDetach(IControl *control) override;
			void NotifyOnControlChange(IControl *control) override;

			// Notifications from parent control
			void NotifyOnParentStyleChange() override;
			void NotifyOnParentFontChange() override;
			void NotifyOnParentResize() override;

			// State change notifications
			void NotifyOnShow() override;
			void NotifyOnHide() override;
			void NotifyOnEnable() override;
			void NotifyOnDisable() override;
			void NotifyOnResize() override;
			void NotifyOnTransform() override;
			void NotifyOnStyleChange() override;
			void NotifyOnFontChange() override;
			void NotifyOnSetModal() override;
			void NotifyOnKillModal() override;
			void NotifyOnKillCaptureMouse() override;

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;
			void NotifyOnPaintEnd(const MessagePaint &m) override;

			// Mouse input notifications
			void NotifyOnMouseHover(const MessagePosition &m) override;
			void NotifyOnMouseLeave() override;
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

			// Dialog box notifications
			void NotifyOnSetActive() override;
			void NotifyOnKillActive() override;
		};
	}
}
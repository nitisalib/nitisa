// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Align.h"
#include "Nitisa/Core/DialogBoxService.h"
#include "Nitisa/Core/Messages.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "Nitisa/Math/Transform.h"
#include "../ICoolBar.h"

namespace nitisa
{
	class IControl;

	namespace standard
	{
		class CCoolBar;

		class CCoolBarService :public CDialogBoxService
		{
		private:
			struct Config
			{
				IControl *Parent;
				ICoolBar *ParentBar;
				PointF DownShiftControl;
				PointF PrevPosParent;
				ICoolBar *PrevBar;
				PointF PrevBarSize;
				Align OriginalAlign;
				PointF OriginalSize;
				Transform OriginalTransform;
				int OriginalIndex;
				ICoolBar::Orientation OriginalOrientation;
			};
		private:
			CCoolBar *m_pControl;
			bool m_bIgnoreTransformControls;
			Config m_sDownConfig;

			ICoolBar *FindPrevBar();
			IControl *FindPrevControl();
			IControl *FindNextControl();
			IControl *FindPrevAlignedControl(const Align align);
			IControl *FindNextAlignedControl(const Align align);
			IControl *FindLastAlignedControl(const Align align);
			PointF CalculateControlPosition(const PointF &pos_on_parent);
			void ProcessMoveOnBarLeftToRight(const PointF &pos_on_parent);
			void ProcessMoveOnBarTopToBottom(const PointF &pos_on_parent);
			void ProcessMoveOnBarRightToLeft(const PointF &pos_on_parent);
			void ProcessMoveOnBarBottomToTop(const PointF &pos_on_parent);
			void ProcessMoveOnBar(const PointF &pos);
			void ProcessMoveOnParentAlignLeft(const PointF &pos_on_parent);
			void ProcessMoveOnParentAlignTop(const PointF &pos_on_parent);
			void ProcessMoveOnParentAlignRight(const PointF &pos_on_parent);
			void ProcessMoveOnParentAlignBottom(const PointF &pos_on_parent);
			void ProcessMoveOnParentAlignNone(const PointF &pos_on_parent);
			void ProcessMoveOnParent(const PointF &pos);
			void CancelDown(const bool cancel_capture, const bool cancel_changes);
		public:
			// Helpers
			void AlignControls() override;

			// State change notifications
			void NotifyOnFreeResources() override;

			// Application notifications
			void NotifyOnTranslateChange() override;

			// Notifications from parent control
			void NotifyOnParentStyleChange() override;
			void NotifyOnParentFontChange() override;

			// Notifications from child controls
			void NotifyOnChildTransform(IControl *control) override;
			void NotifyOnChildResize(IControl *control) override;
			void NotifyOnChildShow(IControl *control) override;
			void NotifyOnChildHide(IControl *control) override;
			void NotifyOnChildAttach(IControl *control) override;
			void NotifyOnChildDetach(IControl *control) override;
			void NotifyOnChildBeforeTransform(IControl *control, bool &allowed) override;
			void NotifyOnChildBeforeShow(IControl *control, bool &allowed) override;
			void NotifyOnChildBeforeHide(IControl *control, bool &allowed) override;

			// State change notifications
			void NotifyOnEnable() override;
			void NotifyOnDisable() override;
			void NotifyOnResize() override;
			void NotifyOnTransformControls() override;
			void NotifyOnStyleChange() override;
			void NotifyOnFontChange() override;
			void NotifyOnKillCaptureMouse() override;

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;

			// Keyboard input notifications
			void NotifyOnKeyDown(const MessageKey &m, bool &processed) override;

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
			void NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed) override;

			// DialogBox notifications
			void NotifyOnKillActive() override;

			CCoolBarService(CCoolBar *control);
		};
	}
}
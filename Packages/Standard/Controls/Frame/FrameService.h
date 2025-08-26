// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ControlService.h"
#include "Nitisa/Core/Messages.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"

namespace nitisa
{
	class IControl;

	namespace standard
	{
		class CFrame;

		class CFrameService :public CControlService
		{
			friend CFrame;
		private:
			enum class DownPart
			{
				None,
				Caption,
				LeftBorder,
				TopBorder,
				RightBorder,
				BottomBorder,
				LeftTopCorner,
				RightTopCorner,
				RightBottomCorner,
				LeftBottomCorner,
				MinimizeRestoreButton,
				MaximizeRestoreButton,
				CloseButton
			};

			CFrame *m_pFrame;
			PointF m_sDownPosLocal;
			PointF m_sDownTransform;
			Mat4f m_sDownMatrixInversed;
			PointF m_sDownSize;
			DownPart m_eDownPart;
			RectF m_sDownRect;
			RectF m_sLastRect; // Frame position and size before minimization or maximization

			void UpdateHoveredButton(const PointF &position);
			void MouseUp(const bool check_capture);
		public:
			CFrameService(CFrame *frame);

			// State change notifications
			void NotifyOnAttach() override;
			void NotifyOnFreeResources() override;

			// Other components/controls/objects change notifications
			void NotifyOnControlSetFocus(IControl *control, const MessageFocus &m) override;
			void NotifyOnControlKillFocus(IControl *control) override;

			// Notifications from parent control
			void NotifyOnParentStyleChange() override;
			void NotifyOnParentFontChange() override;

			// State change notifications
			void NotifyOnStyleChange() override;
			void NotifyOnFontChange() override;
			void NotifyOnMouseHover(const MessagePosition &m) override;
			void NotifyOnMouseLeave() override;
			void NotifyOnKillCaptureMouse() override; // set down_part to none
			void NotifyOnSetFocus(const MessageFocus &m) override;
			void NotifyOnKillFocus() override;
			void NotifyOnResize() override;

			// Paint notifications
			void NotifyOnPaint(const MessagePaint &m, bool &draw_children) override;
			void NotifyOnPaintEnd(const MessagePaint &m) override;

			// Input notifications
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
		};
	}
}
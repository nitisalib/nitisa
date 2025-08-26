// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Image/Color.h"
#include "../Interfaces/ICaret.h"
#include "../Interfaces/ITimerListener.h"
#include "../Math/Mat4f.h"
#include "../Math/PointF.h"
#include "Aliases.h"
#include "Feedback.h"
#include <chrono>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IFeedbackListener;
	class IRenderer;

	// A control which shows the caret should assign feedback callback and call form repaint of corresponding area
	// Inversed mode could work slow for huge carets(it is recommended to disable this mode for such caret sizes). It also works only when caret is being rendered on render target. When there is
	// no render target active(drawing directly onto a form) nothing will be drawn. Standard text input and text area always draw onto internal buffer and handle this properly
	class CCaret :public virtual ICaret, public CFeedback
	{
	private:
		class CTimerListener :public virtual ITimerListener
		{
		private:
			CCaret *m_pCaret;
		public:
			void NotifyOnTimer(const PlatformHandle id) override;

			CTimerListener(CCaret *caret);
		};
	private:
		IRenderer *m_pRenderer;
		bool m_bVisible;
		PointF m_sSize;
		float m_fIntervalVisible;
		float m_fIntervalHidden;
		bool m_bIsVisible;
		PlatformHandle m_hTimer;
		std::chrono::steady_clock::time_point m_sStart;
		Color m_sColor;
		bool m_bInversed;
		CTimerListener m_cTimerListener;
	public:
		IRenderer *getRenderer() override;
		bool isVisible() override;
		PointF getSize() override;
		float getIntervalVisible() override;
		float getIntervalHidden() override;
		bool isInversed() override; // True by default. See note above

		bool setRenderer(IRenderer *value) override;
		bool setVisible(const bool value) override;
		bool setSize(const PointF &value) override;
		bool setIntervalVisible(const float value) override;
		bool setIntervalHidden(const float value) override;
		bool setInversed(const bool value) override;

		void Render(const Mat4f &matrix) override;
		void Release() override;

		CCaret(IFeedbackListener *listener); // Listener notification is called when repaint is required
		virtual ~CCaret();
	};
}
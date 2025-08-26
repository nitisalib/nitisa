// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Aliases.h"
#include "../Image/Color.h"
#include "../Interfaces/IHint.h"
#include "../Interfaces/ITimerListener.h"
#include "../Math/Point.h"
#include "../Math/Rect.h"
#include "../Math/RectF.h"
#include "Font.h"
#include "Strings.h"
#include <chrono>

namespace nitisa
{
	class IForm;
	class IHintService;
	class ITexture;

	class CHintService;

	class CHint :public virtual IHint
	{
		friend CHintService;
	private:
		enum class StateType
		{
			Hidden,
			Showing,
			Visible,
			Hiding
		};

		class CTimerListener :public virtual ITimerListener
		{
		private:
			CHint *m_pHint;
		public:
			void NotifyOnTimer(const PlatformHandle id) override;

			CTimerListener(CHint *hint);
		};
	private:
		StateType m_eState, m_eLastState;
		IForm *m_pForm;
		String m_sHint;
		float m_fBorderWidth;
		float m_fPadding;
		Color m_sBorderColor;
		Color m_sBackgroundColor;
		CFont m_cFont;
		float m_fIntervalShowing;
		float m_fIntervalVisible;
		float m_fIntervalHiding;

		PlatformHandle m_hTimer;
		std::chrono::steady_clock::time_point m_sStartTime;
		ITexture *m_pRenderTarget;
		StringArray m_aLines;
		RectF m_sRect;
		float m_fLineHeight;
		IHintService *m_pService;
		CTimerListener m_cTimerListener;
	public:
		void Release() override;
		void Render() override;
		void Show(const String &hint, const Point &pos, const Rect &client) override;
		void Hide(const bool immediately) override;
		IHintService *QueryService() override;

		CHint();
		virtual ~CHint();
	};
}
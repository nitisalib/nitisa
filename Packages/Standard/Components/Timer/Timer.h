// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/Component.h"
#include "Nitisa/Interfaces/ITimerListener.h"
#include "../ITimer.h"

namespace nitisa
{
	class IComponent;
	class IForm;

	namespace standard
	{
		class CTimerService;

		class CTimer :public virtual ITimer, public CComponent
		{
			friend CTimerService;
		private:
			class CTimerListener :public virtual ITimerListener
			{
			private:
				CTimer *m_pControl;
			public:
				void NotifyOnTimer(const PlatformHandle id) override;

				CTimerListener(CTimer *control);
			};
		private:
			PlatformHandle m_iTimer;
			float m_fInterval;
			bool m_bEnabled;
			CTimerListener m_cTimerListener;

			void FreeTimer();
		public:
			void(*OnTimer)(IComponent *sender);

			CTimer();
			CTimer(IForm *parent);

			float getInterval() override;
			bool isEnabled() override;

			bool setInterval(const float value) override;
			bool setEnabled(const bool value) override;
		};
	}
}
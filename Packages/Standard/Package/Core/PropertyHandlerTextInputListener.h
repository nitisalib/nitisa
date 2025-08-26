// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/IBuiltInTextInput.h"
#include "Nitisa/Math/RectF.h"

namespace nitisa
{
	class IBuiltInControl;

	namespace standard
	{
		class CPropertyHandlerTextInput;

		class CPropertyHandlerTextInputListener :public virtual IBuiltInTextInputListener
		{
		private:
			CPropertyHandlerTextInput *m_pHandler;
		public:
			CPropertyHandlerTextInputListener(CPropertyHandlerTextInput *handler);
			virtual ~CPropertyHandlerTextInputListener() = default;

			void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
			void NotifyOnTextChanged(IBuiltInControl *sender) override;
		};
	}
}
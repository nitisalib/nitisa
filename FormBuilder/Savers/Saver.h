// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/Variant.h"
#include "../Core/Types.h"
#include "../Interfaces/ISaver.h"

namespace nitisa
{
	class IControl;

	namespace ide
	{
		class IFormEditor;
	}

	namespace fb
	{
		class CComponentList;
		class CControlList;

		class CSaver :public virtual ISaver
		{
		private:
			ErrorType m_eLastError;

			void SaveComponent(COMPONENT_INFO *info, ide::IFormEditor *form_editor, Variant &dest);
			bool SaveControl(IControl *control, CControlList *controls, ide::IFormEditor *form_editor, Variant &dest);
		public:
			String getName() const override;
			String getDescription() const override;
			String getVersion() const override;
			ErrorType getLastError() const override;

			void Release() override;

			String Save(
				CComponentList *components,
				CControlList *controls,
				Form &form,
				ide::IFormEditor *form_editor,
				const String &layout = L"",
				const SETTINGS *settings = nullptr) override;

			CSaver();
			virtual ~CSaver() = default;
		};
	}
}
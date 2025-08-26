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
	namespace fb
	{
	#pragma region Constructor & destructor
		CSaver::CSaver() :
			m_eLastError{ ErrorType::None }
		{

		}

		void CSaver::Release()
		{
			delete this;
		}
	#pragma endregion

	#pragma region ISaver getters
		String CSaver::getName() const
		{
			return L"Save as *.nfr";
		}

		String CSaver::getDescription() const
		{
			return L"Save form into Nitisa Form Resource file";
		}

		String CSaver::getVersion() const
		{
			return L"1.0.0";
		}

		ISaver::ErrorType CSaver::getLastError() const
		{
			return m_eLastError;
		}
	#pragma endregion

	#pragma region Helpers
	#pragma endregion

	#pragma region Saving
		String CSaver::Save(
			CComponentList *components,
			CControlList *controls,
			Form &form,
			ide::IFormEditor *form_editor,
			const String &layout,
			const SETTINGS *settings)
		{
			Variant data;
			if (!layout.empty())
				data[L"Layout"] = layout;
			data[L"Version"] = NFR_VERSION;
			if (settings)
				data[L"Settings"] = ToVariant(*settings);
			form.Properties->Save(data[L"Form"]);
			form.Events->Save(data[L"Form"]);
			for (int i = 0; i < components->getCount(); i++)
			{
				Variant ctrl;
				SaveComponent(components->getInfo(i), form_editor, ctrl);
				data[L"Components"].push_back(ctrl);
			}
			for (int i = 0; i < form_editor->getControlCount(); i++)
			{
				Variant ctrl;
				if (SaveControl(form_editor->getControl(i), controls, form_editor, ctrl))
					data[L"Controls"].push_back(ctrl);
			}
			return json_encode(data);
		}

		void CSaver::SaveComponent(COMPONENT_INFO *info, ide::IFormEditor *form_editor, Variant &dest)
		{
			info->PackageComponent->Save(dest, info->Properties, info->Events);
			PointF position{ form_editor->getComponentPosition(info->Component) };
			dest[L"Position"].push_back((Variant)position.X);
			dest[L"Position"].push_back((Variant)position.Y);
		}

		bool CSaver::SaveControl(IControl *control, CControlList *controls, ide::IFormEditor *form_editor, Variant &dest)
		{
			CONTROL_INFO *info{ controls->getInfo(control) };
			if (info)
			{
				info->PackageControl->Save(dest, info->Properties, info->Events);
				if (info->PackageControl->isDisplayIcon())
				{
					PointF position{ form_editor->getControlPosition(control) };
					dest[L"Position"].push_back((Variant)position.X);
					dest[L"Position"].push_back((Variant)position.Y);
				}
				for (int i = 0; i < control->getControlCount(); i++)
				{
					Variant ctrl;
					if (SaveControl(control->getControl(i), controls, form_editor, ctrl))
						dest[L"Controls"].push_back(ctrl);
				}
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}
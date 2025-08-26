// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

#ifdef DialogBox
#undef DialogBox
#endif

namespace nitisa
{
	namespace fb
	{
	#pragma region Constructor & destructor
		CDialogBoxConfiguration::CDialogBoxConfiguration() :
			IDialogBoxConfiguration(L"DialogBoxConfiguration", true, true, false, false),
			m_bGlobal{ true },
			m_bColorDialogAdjusted{ false }
		{
			setStaticTabOrder(true);
			setUseMask(false);
		}

		CDialogBoxConfiguration::CDialogBoxConfiguration(IForm *parent) : CDialogBoxConfiguration()
		{
			setForm(parent);
		}
	#pragma endregion

	#pragma region Events
		void CDialogBoxConfiguration::ColorDialog_OnApply(IComponent *sender)
		{
			m_pColorDialogPanel->setBackgroundColor(m_pColorDialog->getColor());
		}

		void CDialogBoxConfiguration::FormSettings_OnKeyDown(IControl *sender, const MessageKey &m, bool &processed)
		{
			switch (m.Key)
			{
			case Key::Escape:
				setModalResult(ModalResult::Cancel);
				break;
			case Key::Return:
				if (Application->Keyboard->isDown(Key::Control) && Validate())
					setModalResult(ModalResult::Ok);
				break;
			}
		}

		void CDialogBoxConfiguration::PanelGridColor_OnLeftMouseButtonDown(IControl *sender, const MessageMouse &m, bool &processed)
		{
			ExecuteColorDialog(m_pPanelGridColor);
		}

		void CDialogBoxConfiguration::ButtonOk_OnClick(IControl *sender)
		{
			if (Validate())
			{
				m_bGlobal = true;
				setModalResult(ModalResult::Ok);
			}
		}

		void CDialogBoxConfiguration::ButtonOkForm_OnClick(IControl *sender)
		{
			if (Validate())
			{
				m_bGlobal = false;
				setModalResult(ModalResult::Ok);
			}
		}

		void CDialogBoxConfiguration::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}

		void CDialogBoxConfiguration::PanelSelectionBorderColor_OnLeftMouseButtonDown(IControl *sender, const MessageMouse &m, bool &processed)
		{
			ExecuteColorDialog(m_pPanelSelectionBorderColor);
		}

		void CDialogBoxConfiguration::PanelSelectionBackgroundColor_OnLeftMouseButtonDown(IControl *sender, const MessageMouse &m, bool &processed)
		{
			ExecuteColorDialog(m_pPanelSelectionBackgroundColor);
		}

		void CDialogBoxConfiguration::PanelHighlightBorderColorLeft_OnLeftMouseButtonUp(IControl *sender, const MessageMouse &m, bool &processed)
		{
			ExecuteColorDialog(m_pPanelHighlightBorderColorLeft);
		}

		void CDialogBoxConfiguration::PanelHighlightBorderColorTop_OnLeftMouseButtonUp(IControl *sender, const MessageMouse &m, bool &processed)
		{
			ExecuteColorDialog(m_pPanelHighlightBorderColorTop);
		}

		void CDialogBoxConfiguration::PanelHighlightBorderColorRight_OnLeftMouseButtonUp(IControl *sender, const MessageMouse &m, bool &processed)
		{
			ExecuteColorDialog(m_pPanelHighlightBorderColorRight);
		}

		void CDialogBoxConfiguration::PanelHighlightBorderColorBottom_OnLeftMouseButtonUp(IControl *sender, const MessageMouse &m, bool &processed)
		{
			ExecuteColorDialog(m_pPanelHighlightBorderColorBottom);
		}

		void CDialogBoxConfiguration::RadioButtonForm_OnChange(IControl *sender)
		{
			m_pDropDownDialogBox->setEnabled(m_pRadioButtonDialogBox->isChecked());
		}

		void CDialogBoxConfiguration::RadioButtonDialogBox_OnChange(IControl *sender)
		{
			m_pDropDownDialogBox->setEnabled(m_pRadioButtonDialogBox->isChecked());
		}
	#pragma endregion

	#pragma region Getters
		bool CDialogBoxConfiguration::isGlobal() const
		{
			return m_bGlobal;
		}
	#pragma endregion

	#pragma region Helpers
		bool CDialogBoxConfiguration::Validate()
		{
			if (m_pRadioButtonDialogBox->isChecked() && m_pDropDownDialogBox->getActiveIndex() < 0)
			{
				Application->Dialogs->Error(L"Please select widget to be used as DialogBox!");
				m_pDropDownDialogBox->setFocus();
				return false;
			}
			return true;
		}

		void CDialogBoxConfiguration::ExecuteColorDialog(standard::CPanel *panel)
		{
			m_pColorDialogPanel = panel;
			m_pColorDialog->setColor(panel->getBackgroundColor());
			m_pColorDialog->Execute();
			if (!m_bColorDialogAdjusted)
			{
				m_pColorDialog->getDialogBox()->setBackgroundColor(getBackgroundColor());
				m_pColorDialog->getDialogBox()->AutoResize(true);
				m_bColorDialogAdjusted = true;
			}
		}

		void CDialogBoxConfiguration::ToSettings(SETTINGS &dst)
		{
			dst.GridX = m_pCheckBoxXAxis->getChecked() == standard::ICheckBox::CheckedState::Checked;
			dst.GridY = m_pCheckBoxYAxis->getChecked() == standard::ICheckBox::CheckedState::Checked;
			dst.GridRotate = m_pCheckBoxRotate->getChecked() == standard::ICheckBox::CheckedState::Checked;
			float f;
			if (TryStringToFloat(m_pEditXAxis->getText(), f) && ntl::IsGreater<float>(f, 0))
				dst.GridXStep = f;
			if (TryStringToFloat(m_pEditYAxis->getText(), f) && ntl::IsGreater<float>(f, 0))
				dst.GridYStep = f;
			if (TryStringToFloat(m_pEditRotate->getText(), f) && ntl::IsGreater<float>(f, 0))
				dst.GridRotateStep = ntl::DegToRad<float>(f);
			if (TryStringToFloat(m_pEditRotateShift->getText(), f) && ntl::IsGreater<float>(f, 0))
				dst.RotateShift = f;
			if (TryStringToFloat(m_pEditPointSize->getText(), f) && ntl::IsGreater<float>(f, 0))
				dst.GridPointSize = f;
			dst.GridPointColor = m_pPanelGridColor->getBackgroundColor();
			dst.Namespace = m_pEditNamespace->getText();
			dst.Prefix = m_pEditPrefix->getText();
			if (TryStringToFloat(m_pEditSelectionPointSize->getText(), f) && ntl::IsGreater<float>(f, 0))
				dst.SelectionPointSize = f;
			if (TryStringToFloat(m_pEditSelectionBorderWidth->getText(), f) && ntl::IsGreaterOrEqual<float>(f, 0))
				dst.SelectionBorderWidth = f;
			dst.SelectionBorderColor = m_pPanelSelectionBorderColor->getBackgroundColor();
			dst.SelectionBackgroundColor = m_pPanelSelectionBackgroundColor->getBackgroundColor();
			dst.OverwriteIncludes.clear();
			for (int i = 1; i < m_pValueListEditorOverwriteIncludes->getRows(); i++)
				if (!m_pValueListEditorOverwriteIncludes->getCell(0, i).empty())
					dst.OverwriteIncludes.push_back({ m_pValueListEditorOverwriteIncludes->getCell(0, i), m_pValueListEditorOverwriteIncludes->getCell(1, i) });
			dst.OverwriteNamespaces.clear();
			for (int i = 1; i < m_pValueListEditorOverwriteNamespaces->getRows(); i++)
				if (!m_pValueListEditorOverwriteNamespaces->getCell(0, i).empty())
					dst.OverwriteNamespaces.push_back({ m_pValueListEditorOverwriteNamespaces->getCell(0, i), m_pValueListEditorOverwriteNamespaces->getCell(1, i) });
			dst.WidgetsSection = m_pDropDownWidgetsSection->getText();
			dst.GenerateGetters = m_pCheckBoxGenerateGetters->getChecked() == standard::ICheckBox::CheckedState::Checked;
			dst.HighlightBorderWidth.Left = (float)m_pUpDownHighlightBorderWidthLeft->getValue();
			dst.HighlightBorderWidth.Top = (float)m_pUpDownHighlightBorderWidthTop->getValue();
			dst.HighlightBorderWidth.Right = (float)m_pUpDownHighlightBorderWidthRight->getValue();
			dst.HighlightBorderWidth.Bottom = (float)m_pUpDownHighlightBorderWidthBottom->getValue();
			dst.HighlightBorderColor.Left = m_pPanelHighlightBorderColorLeft->getBackgroundColor();
			dst.HighlightBorderColor.Top = m_pPanelHighlightBorderColorTop->getBackgroundColor();
			dst.HighlightBorderColor.Right = m_pPanelHighlightBorderColorRight->getBackgroundColor();
			dst.HighlightBorderColor.Bottom = m_pPanelHighlightBorderColorBottom->getBackgroundColor();
			dst.ExportAs = m_pRadioButtonDialogBox->isChecked() ? ExportAs::DialogBox : ExportAs::Form;
			if (dst.ExportAs == ExportAs::Form)
			{
				dst.DialogBoxPackage = L"";
				dst.DialogBoxClass = L"";
			}
			else
			{
				IPackageControl *ctrl{ Application->Editor->getControl(StringToInt(m_pDropDownDialogBox->getItem(m_pDropDownDialogBox->getActiveIndex())->Name)) };
				dst.DialogBoxPackage = ctrl->getPackage()->getName();
				dst.DialogBoxClass = ctrl->getClassName();
			}
		}

		void CDialogBoxConfiguration::FromSettings(const SETTINGS &src)
		{
			m_pCheckBoxXAxis->setChecked(src.GridX ? standard::ICheckBox::CheckedState::Checked : standard::ICheckBox::CheckedState::Unchecked);
			m_pCheckBoxYAxis->setChecked(src.GridY ? standard::ICheckBox::CheckedState::Checked : standard::ICheckBox::CheckedState::Unchecked);
			m_pCheckBoxRotate->setChecked(src.GridRotate ? standard::ICheckBox::CheckedState::Checked : standard::ICheckBox::CheckedState::Unchecked);
			m_pEditXAxis->setText(ToStringCompact(src.GridXStep));
			m_pEditYAxis->setText(ToStringCompact(src.GridYStep));
			m_pEditRotate->setText(ToStringCompact(ntl::RadToDeg<float>(src.GridRotateStep)));
			m_pEditRotateShift->setText(ToStringCompact(src.RotateShift));
			m_pEditPointSize->setText(ToStringCompact(src.GridPointSize));
			m_pPanelGridColor->setBackgroundColor(src.GridPointColor);
			m_pEditNamespace->setText(src.Namespace);
			m_pEditPrefix->setText(src.Prefix);
			m_pEditSelectionPointSize->setText(ToStringCompact(src.SelectionPointSize));
			m_pEditSelectionBorderWidth->setText(ToStringCompact(src.SelectionBorderWidth));
			m_pPanelSelectionBorderColor->setBackgroundColor(src.SelectionBorderColor);
			m_pPanelSelectionBackgroundColor->setBackgroundColor(src.SelectionBackgroundColor);
			m_pValueListEditorOverwriteIncludes->Clear();
			for (auto &item : src.OverwriteIncludes)
				m_pValueListEditorOverwriteIncludes->Add(item.first, item.second);
			m_pValueListEditorOverwriteNamespaces->Clear();
			for (auto &item : src.OverwriteNamespaces)
				m_pValueListEditorOverwriteNamespaces->Add(item.first, item.second);
			if (src.WidgetsSection == L"public")
				m_pDropDownWidgetsSection->setActiveIndex(0);
			else if (src.WidgetsSection == L"protected")
				m_pDropDownWidgetsSection->setActiveIndex(1);
			else
				m_pDropDownWidgetsSection->setActiveIndex(2);
			m_pCheckBoxGenerateGetters->setChecked(src.GenerateGetters ? standard::ICheckBox::CheckedState::Checked : standard::ICheckBox::CheckedState::Unchecked);
			m_pUpDownHighlightBorderWidthLeft->setValue(ntl::Round<int>(src.HighlightBorderWidth.Left));
			m_pUpDownHighlightBorderWidthTop->setValue(ntl::Round<int>(src.HighlightBorderWidth.Top));
			m_pUpDownHighlightBorderWidthRight->setValue(ntl::Round<int>(src.HighlightBorderWidth.Right));
			m_pUpDownHighlightBorderWidthBottom->setValue(ntl::Round<int>(src.HighlightBorderWidth.Bottom));
			m_pPanelHighlightBorderColorLeft->setBackgroundColor(src.HighlightBorderColor.Left);
			m_pPanelHighlightBorderColorTop->setBackgroundColor(src.HighlightBorderColor.Top);
			m_pPanelHighlightBorderColorRight->setBackgroundColor(src.HighlightBorderColor.Right);
			m_pPanelHighlightBorderColorBottom->setBackgroundColor(src.HighlightBorderColor.Bottom);
			(src.ExportAs == ExportAs::Form) ? m_pRadioButtonForm->setChecked(true) : m_pRadioButtonDialogBox->setChecked(true);
			if (src.ExportAs == ExportAs::DialogBox)
			{
				IEditor *editor{ Application->Editor };
				String index;
				for (int i = 0; i < editor->getControlCount(); i++)
					if (editor->getControl(i)->getPackage()->getName() == src.DialogBoxPackage && editor->getControl(i)->getClassName() == src.DialogBoxClass)
					{
						index = ToString(i);
						break;
					}
				for (int i = 0; i < m_pDropDownDialogBox->getItemCount(); i++)
					if (m_pDropDownDialogBox->getItem(i)->Name == index)
					{
						m_pDropDownDialogBox->setActiveIndex(i);
						break;
					}
				m_pDropDownDialogBox->setEnabled(true);
			}
			else
				m_pDropDownDialogBox->setEnabled(false);
		}

		void CDialogBoxConfiguration::AddDialogBox(const String &name, const String &caption)
		{
			standard::CListItemLabel *item{ new standard::CListItemLabel(caption) };
			item->setName(name);
			m_pDropDownDialogBox->Add(item);
		}
	#pragma endregion
	}
}
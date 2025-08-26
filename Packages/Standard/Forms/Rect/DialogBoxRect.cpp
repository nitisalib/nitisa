// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace standard
	{
		const String CDialogBoxRect::ClassName{ L"DialogBoxRect" };

	#pragma region Service
		CDialogBoxRect::CDialogBoxRectService::CDialogBoxRectService(CDialogBoxRect *control) :
			IDialogBoxRectProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxRect::CDialogBoxRectService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
			IDialogBoxRectProtoService::NotifyOnFreeResources();
		}

		void CDialogBoxRect::CDialogBoxRectService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxRect::CDialogBoxRect() :
			IDialogBoxRectProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxRectService(this)),
			m_sValue{ 0, 0, 0, 0 },
			m_bHasMin{ false },
			m_bHasMax{ false },
			m_iMin{ 0 },
			m_iMax{ 0 },
			m_pCanvas{ nullptr }
		{
			setStaticTabOrder(true);
			setUseMask(false);
			LoadTranslatableTexts();
		}

		CDialogBoxRect::CDialogBoxRect(IForm *parent) :CDialogBoxRect()
		{
			setForm(parent);
		}

		CDialogBoxRect::CDialogBoxRect(IControl *parent) : CDialogBoxRect()
		{
			setParent(parent);
		}

		void CDialogBoxRect::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Borders(integer)"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CDialogBoxRect::FormRectProto_OnPaint(IControl *sender, const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass)
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				if (!m_pCanvas)
				{
					if ((m_pCanvas = renderer->CreateTexture(258, 88, 1, TextureFormat::RGBA, true)))
					{
						CStoreTarget s_target{ renderer };
						renderer
							->ActivateTarget(m_pCanvas)
							->Clear(Color{ 0, 0, 0, 0 })
							->DrawBlock(
								RectF{ 8, 8, 258, 88 },
								RectF{ 50, 20, 50, 20 },
								RectF{ 0, 0, 0, 0 },
								BlockColors{ Color{ 200, 200, 200, 255 }, Color{ 160, 160, 160, 255 }, Color{ 200, 200, 200, 255 }, Color{ 160, 160, 160, 255 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } })
							->DrawBlock(
								RectF{ 8, 8, 258, 88 },
								RectF{ 1, 1, 1, 1 },
								RectF{ 0, 0, 0, 0 },
								BlockColors{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } })
							->DrawBlock(
								RectF{ 58, 28, 208, 68 },
								RectF{ 1, 1, 1, 1 },
								RectF{ 0, 0, 0, 0 },
								BlockColors{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } });
					}
				}
				if (m_pCanvas)
				{
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivatePrimitiveMatrix(getTransformControls()->getMatrix() * getTransformMatrix())
						->DrawImage(m_pCanvas, 1);
				}
			}
		}

		void CDialogBoxRect::FormRectProto_OnKeyDown(IControl *sender, const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if (m.Key == Key::Return || m.Key == Key::Separator)
			{
				CEdit *edit{ cast<CEdit*>(getForm()->getFocusedControl()) };
				if (edit)
					edit->OnKillFocus(edit);
				setModalResult(ModalResult::Ok);
			}
		}

		void CDialogBoxRect::EditLeft_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			int v;
			if (!TryStringToInt(edit->getText(), v))
				v = m_sValue.Left;
			if (m_bHasMin && v < m_iMin)
				v = m_iMin;
			else if (m_bHasMax && v > m_iMax)
				v = m_iMax;
			m_sValue.Left = v;
			edit->setText(ToString(v));
		}

		void CDialogBoxRect::EditTop_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			int v;
			if (!TryStringToInt(edit->getText(), v))
				v = m_sValue.Top;
			if (m_bHasMin && v < m_iMin)
				v = m_iMin;
			else if (m_bHasMax && v > m_iMax)
				v = m_iMax;
			m_sValue.Top = v;
			edit->setText(ToString(v));
		}

		void CDialogBoxRect::EditRight_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			int v;
			if (!TryStringToInt(edit->getText(), v))
				v = m_sValue.Right;
			if (m_bHasMin && v < m_iMin)
				v = m_iMin;
			else if (m_bHasMax && v > m_iMax)
				v = m_iMax;
			m_sValue.Right = v;
			edit->setText(ToString(v));
		}

		void CDialogBoxRect::EditBottom_OnKillFocus(IControl *sender)
		{
			CEdit *edit{ cast<CEdit*>(sender) };
			int v;
			if (!TryStringToInt(edit->getText(), v))
				v = m_sValue.Bottom;
			if (m_bHasMin && v < m_iMin)
				v = m_iMin;
			else if (m_bHasMax && v > m_iMax)
				v = m_iMax;
			m_sValue.Bottom = v;
			edit->setText(ToString(v));
		}

		void CDialogBoxRect::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CDialogBoxRect::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		Rect CDialogBoxRect::getValue()
		{
			return m_sValue;
		}

		bool CDialogBoxRect::hasMin()
		{
			return m_bHasMin;
		}

		bool CDialogBoxRect::hasMax()
		{
			return m_bHasMax;
		}

		int CDialogBoxRect::getMin()
		{
			return m_iMin;
		}

		int CDialogBoxRect::getMax()
		{
			return m_iMax;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDialogBoxRect::setValue(const Rect &value)
		{
			if (value != m_sValue)
			{
				CLockRepaint lock{ this };
				m_sValue = value;
				m_pEditLeft->setText(ToString(m_sValue.Left));
				m_pEditTop->setText(ToString(m_sValue.Top));
				m_pEditRight->setText(ToString(m_sValue.Right));
				m_pEditBottom->setText(ToString(m_sValue.Bottom));
				return true;
			}
			return false;
		}

		bool CDialogBoxRect::setHasMin(const bool value)
		{
			if (value != m_bHasMin)
			{
				m_bHasMin = value;
				return true;
			}
			return false;
		}

		bool CDialogBoxRect::setHasMax(const bool value)
		{
			if (value != m_bHasMax)
			{
				m_bHasMax = value;
				return true;
			}
			return false;
		}

		bool CDialogBoxRect::setMin(const int value)
		{
			if (value != m_iMin || !m_bHasMin)
			{
				m_iMin = value;
				m_bHasMin = true;
				return true;
			}
			return false;
		}

		bool CDialogBoxRect::setMax(const int value)
		{
			if (value != m_iMax || !m_bHasMax)
			{
				m_iMax = value;
				m_bHasMax = true;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface methods
		void CDialogBoxRect::ActivateFirstEnabledInput()
		{
			m_pEditLeft->SelectAll();
			m_pEditLeft->setFocus();
		}
	#pragma endregion
	}
}
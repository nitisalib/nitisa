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
		const String CFormBorderColor::ClassName{ L"FormBorderColor" };

	#pragma region Service
		CFormBorderColor::CFormBorderColorService::CFormBorderColorService(CFormBorderColor *form) :
			CFormService(form),
			m_pForm{ form }
		{

		}

		void CFormBorderColor::CFormBorderColorService::NotifyOnTranslateChange()
		{
			m_pForm->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CFormBorderColor::CFormBorderColor(IWindow *window, IRenderer *renderer) :
			IFormBorderColorProto(window, renderer, ClassName),
			m_sValue{ Color{ 200, 200, 200, 255 }, Color{ 160, 160, 160, 255 }, Color{ 200, 200, 200, 255 }, Color{ 160, 160, 160, 255 } }
		{
			setService(new CFormBorderColorService(this), true);
			LoadTranslatableTexts();
		}

		void CFormBorderColor::LoadTranslatableTexts()
		{
			CLockRepaint lock{ this };
			setCaption(Application->Translate->t(ClassName, L"Border colors"));
			m_pButtonLeft->setCaption(Application->Translate->t(ClassName, L"Left"));
			m_pButtonTop->setCaption(Application->Translate->t(ClassName, L"Top"));
			m_pButtonRight->setCaption(Application->Translate->t(ClassName, L"Right"));
			m_pButtonBottom->setCaption(Application->Translate->t(ClassName, L"Bottom"));
			m_pButtonOk->setCaption(Application->Translate->t(ClassName, L"OK"));
			m_pButtonCancel->setCaption(Application->Translate->t(ClassName, L"Cancel"));
		}
	#pragma endregion

	#pragma region Events
		void CFormBorderColor::FormBorderColorProto_OnPaint(IForm *sender, const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass)
			{
				IRenderer *renderer{ sender->getRenderer() };
				renderer
					->DrawBlock(
						RectF{ 8, 8, 258, 88 },
						RectF{ 50, 20, 50, 20 },
						RectF{ 0, 0, 0, 0 },
						BlockColors{ m_sValue.Left, m_sValue.Top, m_sValue.Right, m_sValue.Bottom, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } })
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

		void CFormBorderColor::FormBorderColorProto_OnKeyUp(IForm *sender, const MessageKey &m)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if ((m.Key == Key::Return || m.Key == Key::Separator) && Application->Keyboard->isDown(Key::Control))
				setModalResult(ModalResult::Ok);
		}

		void CFormBorderColor::ButtonLeft_OnClick(IControl *sender)
		{
			SelectColor(m_sValue.Left);
		}

		void CFormBorderColor::ButtonTop_OnClick(IControl *sender)
		{
			SelectColor(m_sValue.Top);
		}

		void CFormBorderColor::ButtonRight_OnClick(IControl *sender)
		{
			SelectColor(m_sValue.Right);
		}

		void CFormBorderColor::ButtonBottom_OnClick(IControl *sender)
		{
			SelectColor(m_sValue.Bottom);
		}

		void CFormBorderColor::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CFormBorderColor::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		BorderColor CFormBorderColor::getValue()
		{
			return m_sValue;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFormBorderColor::setValue(const BorderColor &value)
		{
			if (value != m_sValue)
			{
				m_sValue = value;
				Repaint();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface methods
		void CFormBorderColor::ActivateFirstEnabledInput()
		{
			m_pButtonLeft->setFocus();
		}
	#pragma endregion

	#pragma region Helpers
		void CFormBorderColor::SelectColor(Color &color)
		{
			m_pColorDialog1->setColor(color);
			if (m_pColorDialog1->Execute())
			{
				color = m_pColorDialog1->getColor();
				Repaint();
			}
		}
	#pragma endregion
	}
}
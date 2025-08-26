// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		const String CDialogBoxBorderColor::ClassName{ L"DialogBoxBorderColor" };

	#pragma region Service
		CDialogBoxBorderColor::CDialogBoxBorderColorService::CDialogBoxBorderColorService(CDialogBoxBorderColor *control) :
			IDialogBoxBorderColorProtoService(control),
			m_pControl{ control }
		{

		}

		void CDialogBoxBorderColor::CDialogBoxBorderColorService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
			IDialogBoxBorderColorProtoService::NotifyOnFreeResources();
		}

		void CDialogBoxBorderColor::CDialogBoxBorderColorService::NotifyOnTranslateChange()
		{
			m_pControl->LoadTranslatableTexts();
		}
	#pragma endregion

	#pragma region Constructor & destrictor
		CDialogBoxBorderColor::CDialogBoxBorderColor() :
			IDialogBoxBorderColorProto(ClassName, true, true, false, false, DesignDPI, new CDialogBoxBorderColorService(this)),
			m_sValue{ Color{ 200, 200, 200, 255 }, Color{ 160, 160, 160, 255 }, Color{ 200, 200, 200, 255 }, Color{ 160, 160, 160, 255 } },
			m_bColorDialogAdjusted{ false },
			m_pCanvas{ nullptr }
		{
			setStaticTabOrder(true);
			setUseMask(false);
			LoadTranslatableTexts();
		}

		CDialogBoxBorderColor::CDialogBoxBorderColor(IForm *parent) :CDialogBoxBorderColor()
		{
			setForm(parent);
		}

		CDialogBoxBorderColor::CDialogBoxBorderColor(IControl *parent) : CDialogBoxBorderColor()
		{
			setParent(parent);
		}

		void CDialogBoxBorderColor::LoadTranslatableTexts()
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
		void CDialogBoxBorderColor::DialogBoxBorderColorProto_OnPaint(IControl *sender, const MessagePaint &m, bool &draw_children)
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
				if (m_pCanvas)
				{
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivatePrimitiveMatrix(getTransformControls()->getMatrix() * getTransformMatrix())
						->DrawImage(m_pCanvas, 1);
				}
			}
		}

		void CDialogBoxBorderColor::DialogBoxBorderColorProto_OnKeyUp(IControl *sender, const MessageKey &m, bool &processed)
		{
			if (m.Key == Key::Escape)
				setModalResult(ModalResult::Cancel);
			else if ((m.Key == Key::Return || m.Key == Key::Separator) && Application->Keyboard->isDown(Key::Control))
				setModalResult(ModalResult::Ok);
		}

		void CDialogBoxBorderColor::ColorDialog1_OnApply(IComponent *sender)
		{
			*m_pColor = m_pColorDialog1->getColor();
			if (m_pCanvas)
			{
				m_pCanvas->Release();
				m_pCanvas = nullptr;
			}
			Repaint(false);
		}

		void CDialogBoxBorderColor::ButtonLeft_OnClick(IControl *sender)
		{
			SelectColor(&m_sValue.Left);
		}

		void CDialogBoxBorderColor::ButtonTop_OnClick(IControl *sender)
		{
			SelectColor(&m_sValue.Top);
		}

		void CDialogBoxBorderColor::ButtonRight_OnClick(IControl *sender)
		{
			SelectColor(&m_sValue.Right);
		}

		void CDialogBoxBorderColor::ButtonBottom_OnClick(IControl *sender)
		{
			SelectColor(&m_sValue.Bottom);
		}

		void CDialogBoxBorderColor::ButtonOk_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Ok);
		}

		void CDialogBoxBorderColor::ButtonCancel_OnClick(IControl *sender)
		{
			setModalResult(ModalResult::Cancel);
		}
	#pragma endregion

	#pragma region Interface getters
		bool CDialogBoxBorderColor::hasComponent(IComponent *component)
		{
			if (IDialogBoxBorderColorProto::hasComponent(component))
				return true;
			if (m_pColorDialog1->getDialogBox() && m_pColorDialog1->getDialogBox()->hasComponent(component))
				return true;
			return false;
		}

		BorderColor CDialogBoxBorderColor::getValue()
		{
			return m_sValue;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDialogBoxBorderColor::setBackgroundColor(const Color &value)
		{
			if (m_pColorDialog1->getDialogBox())
				m_pColorDialog1->getDialogBox()->setBackgroundColor(value);
			return IDialogBoxBorderColorProto::setBackgroundColor(value);
		}

		bool CDialogBoxBorderColor::setValue(const BorderColor &value)
		{
			if (value != m_sValue)
			{
				m_sValue = value;
				if (m_pCanvas)
				{
					m_pCanvas->Release();
					m_pCanvas = nullptr;
				}
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface methods
		void CDialogBoxBorderColor::ActivateFirstEnabledInput()
		{
			m_pButtonLeft->setFocus();
		}
	#pragma endregion

	#pragma region Helpers
		void CDialogBoxBorderColor::SelectColor(Color *color)
		{
			m_pColor = color;
			m_pColorDialog1->setColor(*color);
			m_pColorDialog1->Execute();
			if (!m_bColorDialogAdjusted)
			{
				m_pColorDialog1->getDialogBox()->setBackgroundColor(getBackgroundColor());
				m_pColorDialog1->getDialogBox()->AutoResize(true);
				m_bColorDialogAdjusted = true;
			}
		}
	#pragma endregion
	}
}
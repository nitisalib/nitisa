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
	namespace ide
	{
	#pragma region CGradientListener
		CPropertyEditor::CGradientListener::CGradientListener(CPropertyEditor *control) :
			m_pControl{ control }
		{

		}

		void CPropertyEditor::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CPropertyEditor::CPropertyEditor() :
			CControl(L"PropertyEditor", true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_sBorderWidth{ 0, 0, 0, 0 },
			m_sBorderColor{ Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 } },
			m_sBackgroundColor{ 255, 255, 255, 255 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_fFolderWidth{ 13 },
			m_sFolderBackgroundColor{ 255, 251, 240, 255 },
			m_cFolderBackgroundGradient{ &m_cGradientListener },
			m_fFolderIconPadding{ 2 },
			m_fFolderIconBorderWidth{ 1 },
			m_fFolderIconBorderRadius{ 2 },
			m_sFolderIconBorderColor{ 145, 145, 145, 255 },
			m_sFolderIconBackgroundColor{ 250, 250, 250, 255 },
			m_cFolderIconBackgroundGradient{ &m_cGradientListener },
			m_fFolderIconInnerPadding{ 1 },
			m_aFolderIconLineColor{ Color{ 41, 66, 144, 255 }, Color{ 41, 66, 144, 255 } },
			m_fFolderSeparatorWidth{ 1 },
			m_sFolderSeparatorColor{ 128, 128, 128, 255 },
			m_cFolderSeparatorGradient{ &m_cGradientListener },
			m_fCaptionWidth{ 0.5f },
			m_fCaptionPadding{ 1 },
			m_fCaptionStatePadding{ 6 },
			m_aCaptionColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			m_aCaptionBorderWidth{ 0, 0, 0 },
			m_aCaptionBorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			m_aCaptionBackgroundColor{ Color{ 0, 0, 0, 0 }, Color{ 240, 240, 240, 255 }, Color{ 224, 224, 224, 255 } },
			m_aCaptionBackgroundGradient{ Gradient{ &m_cGradientListener }, Gradient{ &m_cGradientListener }, Gradient{ &m_cGradientListener } },
			m_fCaptionSeparatorWidth{ 1 },
			m_sCaptionSeparatorColor{ 160, 160, 160, 255 },
			m_cCaptionSeparatorGradient{ &m_cGradientListener },
			m_pCanvas{ nullptr },
			m_pScroll{ nullptr },
			m_bIgnoreGradient{ true },
			m_cListener{ this },
			m_eHoveredElement{ Element::None },
			m_eDownElement{ Element::None },
			m_iHoveredPropertyIndex{ -1 },
			m_iHoveredPropertyStateIndex{ -1 },
			m_iFocusedPropertyIndex{ -1 },
			m_iFocusedPropertyStateIndex{ -1 },
			m_fRowHeight{ 0 },
			m_pHandler{ nullptr },
			m_fHandlerY{ 0 },
			m_cScrollListener{ this },
			m_bUpdateRequired{ true },
			m_pDefaultPropertyHandler{ nullptr }
		{
			OnPropertyChange = nullptr;
			setService(new CPropertyEditorService(this), true);
			m_cFolderIconBackgroundGradient.setPointCount(3);
			m_cFolderIconBackgroundGradient.setPointColor(0, Color{ 252, 252, 252, 255 });
			m_cFolderIconBackgroundGradient.setPointColor(1, Color{ 250, 250, 250, 255 });
			m_cFolderIconBackgroundGradient.setPointColor(2, Color{ 227, 227, 227, 255 });
			m_bIgnoreGradient = false;
			setSize(PointF{ 234, 328 });
		}

		CPropertyEditor::CPropertyEditor(IForm *parent) :CPropertyEditor()
		{
			setForm(parent);
		}

		CPropertyEditor::CPropertyEditor(IControl *parent) : CPropertyEditor()
		{
			setParent(parent);
		}

		CPropertyEditor::~CPropertyEditor()
		{
			if (m_pScroll)
				m_pScroll->Release();
			if (m_pDefaultPropertyHandler)
				m_pDefaultPropertyHandler->Release();
		}
	#pragma endregion

	#pragma region Interface getters
		CursorType CPropertyEditor::getCursor()
		{
			Update();
			if (ntl::IsGreater<float>(m_fCaptionSeparatorWidth, 0) && getForm() && isPointOverCaptionSeparator(FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition()))))
				return CursorType::SizeWestEast;
			if (m_pHandler && getForm())
			{
				PointF p{ FormToHandler((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())) };
				return m_pHandler->getCursor(p, CControl::getCursor());
			}
			return CControl::getCursor();
		}

		int CPropertyEditor::getPropertyListCount()
		{
			return (int)m_aPropertyLists.size();
		}

		IPropertyList *CPropertyEditor::getPropertyList(const int index)
		{
			if (index >= 0 && index < (int)m_aPropertyLists.size())
				return m_aPropertyLists[index];
			return nullptr;
		}

		int CPropertyEditor::getPropertyCount()
		{
			return (int)m_aProperties.size();
		}

		IProperty *CPropertyEditor::getProperty(const int index)
		{
			if (index >= 0 && index < (int)m_aProperties.size())
				return m_aProperties[index].Property;
			return nullptr;
		}

		int CPropertyEditor::getActivePropertyIndex()
		{
			Update();
			return m_iFocusedPropertyIndex;
		}
	#pragma endregion

	#pragma region Getters
		IBuiltInScroll *CPropertyEditor::getScroll()
		{
			if (!m_pScroll)
			{
				m_pScroll = new CScroll(this);
				m_pScroll->setListener(&m_cScrollListener);
				cast<CScroll*>(m_pScroll)->SwitchDirection(true);
			}
			return m_pScroll;
		}

		RectF CPropertyEditor::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		BorderColor CPropertyEditor::getBorderColor() const
		{
			return m_sBorderColor;
		}

		Color CPropertyEditor::getLeftBorderColor() const
		{
			return m_sBorderColor.Left;
		}

		Color CPropertyEditor::getTopBorderColor() const
		{
			return m_sBorderColor.Top;
		}

		Color CPropertyEditor::getRightBorderColor() const
		{
			return m_sBorderColor.Right;
		}

		Color CPropertyEditor::getBottomBorderColor() const
		{
			return m_sBorderColor.Bottom;
		}

		Color CPropertyEditor::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Gradient *CPropertyEditor::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}

		float CPropertyEditor::getFolderWidth() const
		{
			return m_fFolderWidth;
		}

		Color CPropertyEditor::getFolderBackgroundColor() const
		{
			return m_sFolderBackgroundColor;
		}

		Gradient *CPropertyEditor::getFolderBackgroundGradient()
		{
			return &m_cFolderBackgroundGradient;
		}

		float CPropertyEditor::getFolderIconPadding() const
		{
			return m_fFolderIconPadding;
		}

		float CPropertyEditor::getFolderIconBorderWidth() const
		{
			return m_fFolderIconBorderWidth;
		}

		float CPropertyEditor::getFolderIconBorderRadius() const
		{
			return m_fFolderIconBorderRadius;
		}

		Color CPropertyEditor::getFolderIconBorderColor() const
		{
			return m_sFolderIconBorderColor;
		}

		Color CPropertyEditor::getFolderIconBackgroundColor() const
		{
			return m_sFolderIconBackgroundColor;
		}

		Gradient *CPropertyEditor::getFolderIconBackgroundGradient()
		{
			return &m_cFolderIconBackgroundGradient;
		}

		float CPropertyEditor::getFolderIconInnerPadding() const
		{
			return m_fFolderIconInnerPadding;
		}

		Color CPropertyEditor::getFolderIconLineColor(const FolderState state)
		{
			return m_aFolderIconLineColor[(int)state];
		}

		float CPropertyEditor::getFolderSeparatorWidth() const
		{
			return m_fFolderSeparatorWidth;
		}

		Color CPropertyEditor::getFolderSeparatorColor() const
		{
			return m_sFolderSeparatorColor;
		}

		Gradient *CPropertyEditor::getFolderSeparatorGradient()
		{
			return &m_cFolderSeparatorGradient;
		}

		float CPropertyEditor::getCaptionWidth() const
		{
			return m_fCaptionWidth;
		}

		float CPropertyEditor::getCaptionPadding() const
		{
			return m_fCaptionPadding;
		}

		float CPropertyEditor::getCaptionStatePadding() const
		{
			return m_fCaptionStatePadding;
		}

		Color CPropertyEditor::getCaptionColor(const PropertyState state) const
		{
			return m_aCaptionColor[(int)state];
		}

		float CPropertyEditor::getCaptionBorderWidth(const PropertyState state) const
		{
			return m_aCaptionBorderWidth[(int)state];
		}

		Color CPropertyEditor::getCaptionBorderColor(const PropertyState state) const
		{
			return m_aCaptionBorderColor[(int)state];
		}

		Color CPropertyEditor::getCaptionBackgroundColor(const PropertyState state) const
		{
			return m_aCaptionBackgroundColor[(int)state];
		}

		Gradient *CPropertyEditor::getCaptionBackgroundGradient(const PropertyState state)
		{
			return &m_aCaptionBackgroundGradient[(int)state];
		}

		float CPropertyEditor::getCaptionSeparatorWidth() const
		{
			return m_fCaptionSeparatorWidth;
		}

		Color CPropertyEditor::getCaptionSeparatorColor() const
		{
			return m_sCaptionSeparatorColor;
		}

		Gradient *CPropertyEditor::getCaptionSeparatorGradient()
		{
			return &m_cCaptionSeparatorGradient;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CPropertyEditor::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			if (CControl::setDPI(value))
			{
				getScroll()->setDPI(value);
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sBorderWidth *= s;
				m_fFolderWidth *= s.X;
				m_fFolderIconPadding *= s.X;
				m_fFolderIconBorderWidth *= s.X;
				m_fFolderIconBorderRadius *= avg;
				m_fFolderIconInnerPadding *= s.X;
				m_fFolderSeparatorWidth *= s.X;
				m_fCaptionPadding *= s.X;
				m_fCaptionStatePadding *= s.X;
				for (int i = 0; i <= (int)PropertyState::Focused; i++)
					m_aCaptionBorderWidth[i] *= s.X;
				m_fCaptionSeparatorWidth *= s.X;
				m_bUpdateRequired = true;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(true);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Interface methods
		void CPropertyEditor::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}

		bool CPropertyEditor::AttachPropertyList(IPropertyList *list)
		{
			if (list && std::find(m_aPropertyLists.begin(), m_aPropertyLists.end(), list) == m_aPropertyLists.end())
			{
				FreeHandler();
				m_aPropertyLists.push_back(list);
				m_bUpdateRequired = true;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPropertyEditor::DetachPropertyList(const int index)
		{
			if (index >= 0 && index < (int)m_aPropertyLists.size())
			{
				FreeHandler();
				m_aPropertyLists.erase(m_aPropertyLists.begin() + index);
				m_bUpdateRequired = true;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPropertyEditor::DetachPropertyList(IPropertyList *list)
		{
			if (list)
			{
				auto pos{ std::find(m_aPropertyLists.begin(), m_aPropertyLists.end(), list) };
				if (pos != m_aPropertyLists.end())
				{
					FreeHandler();
					m_aPropertyLists.erase(pos);
					m_bUpdateRequired = true;
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			}
			return false;
		}

		bool CPropertyEditor::DetachPropertyLists()
		{
			if (m_aPropertyLists.size() > 0)
			{
				FreeHandler();
				m_aPropertyLists.clear();
				m_bUpdateRequired = true;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CPropertyEditor::setScroll(IBuiltInScroll *value)
		{
			if (value && value != m_pScroll)
			{
				value->setListener(&m_cScrollListener);
				value->NotifyOnFreeResources();
				value->setVertical(true);
				if (m_pScroll)
					m_pScroll->Release();
				m_pScroll = value;
				m_bUpdateRequired = true;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(true);
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				m_sBorderWidth = value;
				m_bUpdateRequired = true;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(true);
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setBorderColor(const BorderColor &value)
		{
			if (value != m_sBorderColor)
			{
				m_sBorderColor = value;
				if (m_sBorderWidth.has_positive())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setLeftBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ value, m_sBorderColor.Top, m_sBorderColor.Right, m_sBorderColor.Bottom });
		}

		bool CPropertyEditor::setTopBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, value, m_sBorderColor.Right, m_sBorderColor.Bottom });
		}

		bool CPropertyEditor::setRightBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, m_sBorderColor.Top, value, m_sBorderColor.Bottom });
		}

		bool CPropertyEditor::setBottomBorderColor(const Color &value)
		{
			return setBorderColor(BorderColor{ m_sBorderColor.Left, m_sBorderColor.Top, m_sBorderColor.Right, value });
		}

		bool CPropertyEditor::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				if (m_cBackgroundGradient.getPointCount() < 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setFolderWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fFolderWidth))
			{
				m_fFolderWidth = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setFolderBackgroundColor(const Color &value)
		{
			if (value != m_sFolderBackgroundColor)
			{
				m_sFolderBackgroundColor = value;
				if (ntl::IsGreater<float>(m_fFolderWidth, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setFolderIconPadding(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fFolderIconPadding))
			{
				m_fFolderIconInnerPadding = value;
				if (ntl::IsGreater<float>(m_fFolderWidth, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setFolderIconBorderWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fFolderIconBorderWidth))
			{
				m_fFolderIconBorderWidth = value;
				if (ntl::IsGreater<float>(m_fFolderWidth, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setFolderIconBorderRadius(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fFolderIconBorderRadius))
			{
				m_fFolderIconBorderRadius = value;
				if (ntl::IsGreater<float>(m_fFolderWidth, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setFolderIconBorderColor(const Color &value)
		{
			if (value != m_sFolderIconBorderColor)
			{
				m_sFolderIconBorderColor = value;
				if (ntl::IsGreater<float>(m_fFolderWidth, 0) && ntl::IsGreater<float>(m_fFolderIconBorderWidth, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setFolderIconBackgroundColor(const Color &value)
		{
			if (value != m_sFolderIconBackgroundColor)
			{
				m_sFolderIconBackgroundColor = value;
				if (ntl::IsGreater<float>(m_fFolderWidth, 0) && m_cFolderIconBackgroundGradient.getPointCount() < 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setFolderIconInnerPadding(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fFolderIconInnerPadding))
			{
				m_fFolderIconInnerPadding = value;
				if (ntl::IsGreater<float>(m_fFolderWidth, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setFolderIconLineColor(const FolderState state, const Color &value)
		{
			if (value != m_aFolderIconLineColor[(int)state])
			{
				m_aFolderIconLineColor[(int)state] = value;
				if (ntl::IsGreater<float>(m_fFolderWidth, 0))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setFolderSeparatorWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fFolderSeparatorWidth))
			{
				m_fFolderSeparatorWidth = value;
				if (m_sFolderSeparatorColor.A > 0 || m_cFolderSeparatorGradient.getPointCount() >= 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setFolderSeparatorColor(const Color &value)
		{
			if (value != m_sFolderSeparatorColor)
			{
				m_sFolderSeparatorColor = value;
				if (ntl::IsGreater<float>(m_fFolderSeparatorWidth, 0) && m_cFolderSeparatorGradient.getPointCount() < 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setCaptionWidth(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsLess<float>(value, 1) && ntl::IsNotEqual<float>(value, m_fCaptionWidth))
			{
				m_fCaptionWidth = value;
				if (m_pHandler)
					m_pHandler->setSize(PointF{ CalculateHandlerWidth(), m_fRowHeight });
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setCaptionPadding(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fCaptionPadding))
			{
				m_fCaptionPadding = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setCaptionStatePadding(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fCaptionStatePadding))
			{
				m_fCaptionStatePadding = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setCaptionColor(const PropertyState state, const Color &value)
		{
			if (value != m_aCaptionColor[(int)state])
			{
				m_aCaptionColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setCaptionBorderWidth(const PropertyState state, const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_aCaptionBorderWidth[(int)state]))
			{
				m_aCaptionBorderWidth[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setCaptionBorderColor(const PropertyState state, const Color &value)
		{
			if (value != m_aCaptionBorderColor[(int)state])
			{
				m_aCaptionBorderColor[(int)state] = value;
				if (m_aCaptionBorderWidth[(int)state] > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setCaptionBackgroundColor(const PropertyState state, const Color &value)
		{
			if (value != m_aCaptionBackgroundColor[(int)state])
			{
				m_aCaptionBackgroundColor[(int)state] = value;
				if (m_aCaptionBackgroundGradient[(int)state].getPointCount() < 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setCaptionSeparatorWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fCaptionSeparatorWidth))
			{
				m_fCaptionSeparatorWidth = value;
				if (m_sCaptionSeparatorColor.A > 0 || m_cCaptionSeparatorGradient.getPointCount() >= 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CPropertyEditor::setCaptionSeparatorColor(const Color &value)
		{
			if (value != m_sCaptionSeparatorColor)
			{
				m_sCaptionSeparatorColor = value;
				if (ntl::IsGreater<float>(m_fCaptionSeparatorWidth, 0) && m_cCaptionSeparatorGradient.getPointCount() < 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		bool CPropertyEditor::isPointOverCaptionSeparator(const PointF &position)
		{
			RectF r;
			float caption_width{ CalculateCaptionWidth() };
			r.Left = m_sBorderWidth.Left + m_fFolderWidth + m_fFolderSeparatorWidth + caption_width;
			r.Top = m_sBorderWidth.Top;
			r.Right = r.Left + m_fCaptionSeparatorWidth;
			r.Bottom = getHeight() - m_sBorderWidth.Bottom;
			return r.is_valid() && !r.is_zero() && position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom;
		}

		void CPropertyEditor::Update()
		{
			if (m_bUpdateRequired)
			{
				UpdatePropertyList();
				UpdateScroll();
				m_bUpdateRequired = false;
			}
		}

		void CPropertyEditor::UpdatePropertyList()
		{
			// Build list of package properties required to be in visible properties
			std::vector<IProperty*> properties;
			if (m_aPropertyLists.size() > 0)
			{
				for (int i = 0; i < m_aPropertyLists[0]->getCount(); i++)
					properties.push_back(m_aPropertyLists[0]->getProperty(i));
				if (m_aPropertyLists.size() > 1)
				{
					auto pos{ properties.begin() };
					while (pos != properties.end())
					{
						bool allowed{ true };
						for (int i = 1; i < (int)m_aPropertyLists.size(); i++)
						{
							bool found{ false };
							for (int j = 0; j < m_aPropertyLists[i]->getCount(); j++)
							{
								IProperty *p{ m_aPropertyLists[i]->getProperty(j) };
								if (CompareProperties(p, *pos))
								{
									found = true;
									break;
								}
							}
							if (!found)
							{
								allowed = false;
								break;
							}
						}
						if (!allowed)
							pos = properties.erase(pos);
						else
							pos++;
					}
				}
			}
			// Update list of visible properties
			IProperty *focused_property{ m_iFocusedPropertyIndex >= 0 ? m_aProperties[m_iFocusedPropertyIndex].Property : nullptr };
			auto pos{ m_aProperties.begin() };
			while (pos != m_aProperties.end())
			{
				auto p{ std::find(properties.begin(), properties.end(), pos->Property) };
				if (p == properties.end())
					pos = m_aProperties.erase(pos);
				else
				{
					properties.erase(p);
					pos++;
				}
			}
			for (auto pos = properties.begin(); pos != properties.end(); pos++)
				m_aProperties.push_back({ *pos, cast<IPropertyState*>(*pos), true });
			std::sort(m_aProperties.begin(), m_aProperties.end(), [](const PROPERTY &a, const PROPERTY &b) { return a.Property->Name < b.Property->Name; });
			if (focused_property)
			{
				for (auto pos = m_aProperties.begin(); pos != m_aProperties.end(); pos++)
					if (pos->Property == focused_property)
					{
						m_iFocusedPropertyIndex = int(pos - m_aProperties.begin());
						focused_property = nullptr;
						break;
					}
				if (focused_property)
					FreeHandler();
			}
		}

		void CPropertyEditor::UpdateScroll()
		{
			// Calculate required height
			float required_height{ 0 };
			m_fRowHeight = 2 * m_fCaptionPadding;
			if (getForm() && getForm()->getRenderer())
			{
				IPlatformFont *pf{ getFont()->getPlatformFont(getForm()->getRenderer()) };
				if (pf)
					m_fRowHeight += pf->getStringSize(L"Wy", 0).Y;
			}
			getScroll()->setSize(PointF{ getScroll()->getSize().X, getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom });
			getScroll()->setPosition(PointF{ getWidth() - m_sBorderWidth.Right - getScroll()->getWidth(), m_sBorderWidth.Top });
			getScroll()->setDeltaMedium(m_fRowHeight * 3);
			for (auto pos : m_aProperties)
			{
				required_height += m_fRowHeight;
				if (!pos.Folded)
					required_height += m_fRowHeight * (float)pos.PropertyState->getStateCount();
			}
			if (ntl::IsGreater<float>(required_height, getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom))
			{
				getScroll()->setEnabled(true);
				getScroll()->setMax(required_height - getHeight() + m_sBorderWidth.Top + m_sBorderWidth.Bottom);
				float area{ getScroll()->getSize().Y - 2 * (getScroll()->getSize().X - 1) };
				if (ntl::IsGreater<float>(area, 0))
				{
					getScroll()->setScrollerSize(getScroll()->getSize().Y / required_height * area);
					getScroll()->setDeltaLarge(getScroll()->getSize().Y / required_height * getScroll()->getMax());
				}
				else
				{
					getScroll()->setScrollerSize(1);
					getScroll()->setDeltaLarge(1);
				}
			}
			else
			{
				getScroll()->setEnabled(false);
				getScroll()->setScroll(0);
			}
		}

		float CPropertyEditor::CalculateCaptionWidth()
		{
			return m_fCaptionWidth * ntl::Max<float>(0, getWidth() - m_sBorderWidth.Left - m_sBorderWidth.Right - m_fFolderWidth - m_fFolderSeparatorWidth - getScroll()->getSize().X);
		}

		float CPropertyEditor::CalculateHandlerWidth()
		{
			return ntl::Max<float>(0, (1 - m_fCaptionWidth) * ntl::Max<float>(0, getWidth() - m_sBorderWidth.Left - m_sBorderWidth.Right - m_fFolderWidth - m_fFolderSeparatorWidth - getScroll()->getSize().X - m_fCaptionSeparatorWidth));
		}

		float CPropertyEditor::CalculateHandlerX()
		{
			return m_sBorderWidth.Left + m_fFolderWidth + m_fFolderSeparatorWidth + CalculateCaptionWidth() + m_fCaptionSeparatorWidth;
		}

		float CPropertyEditor::CalculateHandlerY()
		{
			float result{ m_sBorderWidth.Top };
			if (getScroll()->isEnabled())
				result -= getScroll()->getScroll();
			for (auto pos = m_aProperties.begin(); pos != m_aProperties.end(); pos++)
				if (int(pos - m_aProperties.begin()) == m_iFocusedPropertyIndex)
				{
					result += float(m_iFocusedPropertyStateIndex + 1) * m_fRowHeight;
					break;
				}
				else
				{
					result += m_fRowHeight;
					if (!pos->Folded)
						result += m_fRowHeight * (float)pos->PropertyState->getStateCount();
				}
			return result;
		}

		CPropertyEditor::PropertyState CPropertyEditor::getPropertyState(const int index)
		{
			if (index == m_iFocusedPropertyIndex && m_aProperties[index].Folded)
				return PropertyState::Focused;
			if (m_eHoveredElement == Element::Property && index == m_iHoveredPropertyIndex && m_iHoveredPropertyStateIndex < 0)
				return PropertyState::Hovered;
			return PropertyState::Normal;
		}

		CPropertyEditor::PropertyState CPropertyEditor::getPropertyState(const int index, const int state)
		{
			if (index == m_iFocusedPropertyIndex && !m_aProperties[index].Folded && state == m_iFocusedPropertyStateIndex)
				return PropertyState::Focused;
			if (m_eHoveredElement == Element::Property && index == m_iHoveredPropertyIndex && state == m_iHoveredPropertyStateIndex)
				return PropertyState::Hovered;
			return PropertyState::Normal;
		}

		CPropertyEditor::Element CPropertyEditor::getElement(const PointF &position, int &property_index, int &property_state_index, PointF &property_position)
		{
			// Caption separator
			if (ntl::IsGreater<float>(m_fCaptionSeparatorWidth, 0))
			{
				RectF r;
				float caption_width{ CalculateCaptionWidth() };
				r.Left = m_sBorderWidth.Left + m_fFolderWidth + m_fFolderSeparatorWidth + caption_width;
				r.Top = m_sBorderWidth.Top;
				r.Right = r.Left + m_fCaptionSeparatorWidth;
				r.Bottom = getHeight() - m_sBorderWidth.Bottom;
				if (r.is_valid() && !r.is_zero() && position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
					return Element::CaptionSeparator;
			}
			// Scroll
			if (position.X >= getWidth() - m_sBorderWidth.Right - getScroll()->getSize().X && position.X < getWidth() - m_sBorderWidth.Right && position.Y >= m_sBorderWidth.Top && position.Y < getHeight() - m_sBorderWidth.Bottom)
				return Element::Scroll;
			// Property
			if (position.X >= m_sBorderWidth.Left && position.X < getWidth() - m_sBorderWidth.Right - getScroll()->getSize().X && position.Y >= m_sBorderWidth.Top && position.Y < getHeight() - m_sBorderWidth.Bottom)
			{
				float x{ m_sBorderWidth.Left + m_fFolderWidth + m_fFolderSeparatorWidth + CalculateCaptionWidth() + m_fCaptionSeparatorWidth }, y{ m_sBorderWidth.Top };
				if (getScroll()->isEnabled())
					y -= getScroll()->getScroll();
				for (auto pos = m_aProperties.begin(); pos != m_aProperties.end(); pos++)
				{
					if (position.Y >= y && position.Y < y + m_fRowHeight * float(1 + (pos->Folded ? 0 : pos->PropertyState->getStateCount())))
					{
						// Folder
						if (ntl::IsGreater<float>(m_fFolderWidth, 0) && pos->PropertyState)
						{
							RectF r{ m_sBorderWidth.Left + m_fFolderIconPadding, y + (m_fRowHeight - m_fFolderWidth + 2 * m_fFolderIconPadding) * 0.5f, 0, 0 };
							r.Right = r.Left + m_fFolderWidth - 2 * m_fFolderIconPadding;
							r.Bottom = r.Top + m_fFolderWidth - 2 * m_fFolderIconPadding;
							if (r.is_valid() && position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
							{
								property_state_index = -1;
								property_index = int(pos - m_aProperties.begin());
								return Element::Folder;
							}
						}
						// Property
						property_position.X = x;
						property_position.Y = y;
						property_state_index = -1;
						if (!pos->Folded)
						{
							property_state_index = int((position.Y - y) / m_fRowHeight) - 1;
							property_position.Y += float(property_state_index + 1) * m_fRowHeight;
						}
						property_index = int(pos - m_aProperties.begin());
						return Element::Property;
					}
					y += m_fRowHeight;
					if (!pos->Folded)
						y += m_fRowHeight * (float)pos->PropertyState->getStateCount();
				}
			}
			return Element::None;
		}

		bool CPropertyEditor::UpdateHoveredElement(const PointF &position)
		{
			int property_index, property_state_index;
			PointF property_position;
			Element new_element{ getElement(position, property_index, property_state_index, property_position) };
			if (new_element != m_eHoveredElement || ((new_element == Element::Folder || new_element == Element::Property) && (property_index != m_iHoveredPropertyIndex || property_state_index != m_iHoveredPropertyStateIndex)))
			{
				switch (m_eHoveredElement)
				{
				case Element::Scroll:
					getScroll()->NotifyOnMouseLeave();
					break;
				case Element::Property:
					if (m_pHandler && (m_iHoveredPropertyIndex != m_iFocusedPropertyIndex || m_iHoveredPropertyStateIndex != m_iFocusedPropertyStateIndex))
						m_pHandler->NotifyOnMouseLeave();
					break;
				default:
					break;
				}
				m_eHoveredElement = new_element;
				m_iHoveredPropertyIndex = property_index;
				m_iHoveredPropertyStateIndex = property_state_index;
				switch (m_eHoveredElement)
				{
				case Element::Scroll:
					getScroll()->NotifyOnMouseHover(PointF{ position.X - getWidth() - m_sBorderWidth.Left - getScroll()->getSize().X, position.Y - m_sBorderWidth.Top });
					break;
				case Element::Property:
					if (m_pHandler && m_iHoveredPropertyIndex == m_iFocusedPropertyIndex && m_iHoveredPropertyStateIndex == m_iFocusedPropertyStateIndex)
						m_pHandler->NotifyOnMouseHover(PointF{ position.X - property_position.X, position.Y - property_position.Y });
					break;
				default:
					break;
				}
				return true;
			}
			return false;
		}

		void CPropertyEditor::FreeHandler()
		{
			if (m_pHandler)
			{
				if (isActive())
					getForm()->setActiveControl(nullptr);
				m_pHandler->NotifyOnFreeResources();
				m_pHandler->setFocused(false);
				m_pHandler->setListener(nullptr);
				m_pHandler->setProperty(nullptr);
				m_pHandler->setControl(nullptr);
				if (m_pHandler != m_pDefaultPropertyHandler)
					m_pHandler->Release();
				m_pHandler = nullptr;
				m_iFocusedPropertyIndex = m_iFocusedPropertyStateIndex = -1;
			}
		}

		PointF CPropertyEditor::FormToHandler(const PointF &position)
		{
			PointF p{ FormToLocal(position) };
			float x{ CalculateHandlerX() };
			float y{ m_sBorderWidth.Top - (getScroll()->isEnabled() ? getScroll()->getScroll() : 0) };
			for (auto pos = m_aProperties.begin(); pos != m_aProperties.end(); pos++)
			{
				if (pos - m_aProperties.begin() == m_iFocusedPropertyIndex)
					return PointF{ p.X - x, p.Y - y - float(m_iFocusedPropertyStateIndex + 1) * m_fRowHeight };
				y += m_fRowHeight;
				if (!pos->Folded)
					y += m_fRowHeight * (float)pos->PropertyState->getStateCount();
			}
			return PointF{ 0, 0 };
		}

		bool CPropertyEditor::CompareProperties(IProperty *a, IProperty *b)
		{
			IPropertyState *as{ cast<IPropertyState*>(a) }, *bs{ cast<IPropertyState*>(b) };
			if (as && bs)
			{
				// Both are state properties
				if (as->Name == bs->Name && as->PropertyHandlerName == bs->PropertyHandlerName && as->getStateCount() == bs->getStateCount())
				{
					for (int i = 0; i < as->getStateCount(); i++)
						if (as->getState(i) != bs->getState(i))
							return false;
					return true;
				}
			}
			else if (!as && !bs)
				// Both are common(not state) properties
				return a->Name == b->Name && a->PropertyHandlerName == b->PropertyHandlerName;
			return false;
		}

		IPropertyHandler *CPropertyEditor::getPropertyHandler(const String &name)
		{
			IPackagePropertyHandler *pph{ Application->Editor->getPropertyHandler(name) };
			if (pph)
				return pph->Create();
			if (!m_pDefaultPropertyHandler)
				m_pDefaultPropertyHandler = new CPropertyHandlerDefault(nullptr);
			return m_pDefaultPropertyHandler;
		}

		void CPropertyEditor::UpdateFormStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L"BorderWidth", m_sBorderWidth);
			style->getOption(m_sClassName + L"BorderColor", m_sBorderColor);
			style->getOption(m_sClassName + L"BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L"BackgroundGradient", m_cBackgroundGradient);
			style->getOption(m_sClassName + L"FolderWidth", m_fFolderWidth);
			style->getOption(m_sClassName + L"FolderBackgroundColor", m_sFolderBackgroundColor);
			style->getOption(m_sClassName + L"FolderBackgroundGradient", m_cFolderBackgroundGradient);
			style->getOption(m_sClassName + L"FolderIconPadding", m_fFolderIconPadding);
			style->getOption(m_sClassName + L"FolderIconBorderWidth", m_fFolderIconBorderWidth);
			style->getOption(m_sClassName + L"FolderIconBorderRadius", m_fFolderIconBorderRadius);
			style->getOption(m_sClassName + L"FolderIconBorderColor", m_sFolderIconBorderColor);
			style->getOption(m_sClassName + L"FolderIconBackgroundColor", m_sFolderIconBackgroundColor);
			style->getOption(m_sClassName + L"FolderIconBackgroundGradient", m_cFolderIconBackgroundGradient);
			style->getOption(m_sClassName + L"FolderIconInnerPadding", m_fFolderIconInnerPadding);
			style->getOption(m_sClassName + L"FolderIconLineColor[Folded]", m_aFolderIconLineColor[(int)FolderState::Folded]);
			style->getOption(m_sClassName + L"FolderIconLineColor[Unfolded]", m_aFolderIconLineColor[(int)FolderState::Unfolded]);
			style->getOption(m_sClassName + L"FolderSeparatorWidth", m_fFolderSeparatorWidth);
			style->getOption(m_sClassName + L"FolderSeparatorColor", m_sFolderSeparatorColor);
			style->getOption(m_sClassName + L"FolderSeparatorGradient", m_cFolderSeparatorGradient);
			style->getOption(m_sClassName + L"CaptionWidth", m_fCaptionWidth);
			for (int i = 0; i <= (int)PropertyState::Focused; i++)
			{
				String name;
				switch ((PropertyState)i)
				{
				case PropertyState::Normal:
					name = L"Normal";
					break;
				case PropertyState::Hovered:
					name = L"Hovered";
					break;
				default:
					name = L"Focused";
				}
				style->getOption(m_sClassName + L"CaptionColor[" + name + L"]", m_aCaptionColor[i]);
				style->getOption(m_sClassName + L"CaptionBorderWidth[" + name + L"]", m_aCaptionBorderWidth[i]);
				style->getOption(m_sClassName + L"CaptionBorderColor[" + name + L"]", m_aCaptionBorderColor[i]);
				style->getOption(m_sClassName + L"CaptionBackgroundColor[" + name + L"]", m_aCaptionBackgroundColor[i]);
				style->getOption(m_sClassName + L"CaptionBackgroundGradient[" + name + L"]", m_aCaptionBackgroundGradient[i]);
			}
			style->getOption(m_sClassName + L"CaptionSeparatorWidth", m_fCaptionSeparatorWidth);
			style->getOption(m_sClassName + L"CaptionSeparatorColor", m_sCaptionSeparatorColor);
			style->getOption(m_sClassName + L"CaptionSeparatorGradient", m_cCaptionSeparatorGradient);

			if (m_pHandler)
				m_pHandler->UpdateFromStyle(style, m_pHandler->ClassName);
			getScroll()->UpdateFromStyle(style, m_pHandler->ClassName);
			m_bIgnoreGradient = false;
			m_bUpdateRequired = true;
		}
	#pragma endregion

	#pragma region Property change notification
		void CPropertyEditor::NotifyOnPropertyChange(IProperty *property)
		{
			// Update other list properties if multiple property lists added
			if (OnPropertyChange)
				OnPropertyChange(this, property, m_aPropertyLists[0], m_aPropertyLists[0]->getParent());
			if (m_aPropertyLists.size() > 1)
				for (int i = 0; i < (int)m_aPropertyLists.size(); i++)
					for (int j = 0; j < m_aPropertyLists[i]->getCount(); j++)
						if (m_aPropertyLists[i]->getProperty(j) != property && CompareProperties(m_aPropertyLists[i]->getProperty(j), property))
						{
							if (property->Copy(m_aPropertyLists[i]->getProperty(j)))
								if (OnPropertyChange)
									OnPropertyChange(this, m_aPropertyLists[i]->getProperty(j), m_aPropertyLists[i], m_aPropertyLists[i]->getParent());
							break;
						}
			// Repaint
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
		}
	#pragma endregion

	#pragma region Paint
		void CPropertyEditor::Render()
		{
			IRenderer * renderer{ getForm()->getRenderer() };
			RectF all_rect{ 0, 0, getWidth(), getHeight() };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				Update();
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				DrawSimpleBackground(renderer, all_rect, m_sBorderWidth, RectF{ 0, 0, 0, 0 }, m_sBorderColor, m_sBackgroundColor, m_cBackgroundGradient);
				RenderControl(renderer);

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 });
		}

		void CPropertyEditor::RenderControl(IRenderer *renderer)
		{
			float x{ m_sBorderWidth.Left };

			// Render folder area
			if (ntl::IsGreater<float>(m_fFolderWidth, 0))
			{
				if (m_cFolderBackgroundGradient.getPointCount() > 1)
					renderer->DrawGradient(RectF{ x, m_sBorderWidth.Top, x + m_fFolderWidth, getHeight() - m_sBorderWidth.Bottom }, m_cFolderBackgroundGradient);
				else if (m_sFolderBackgroundColor.A > 0)
					renderer->DrawRectangle(RectF{ x, m_sBorderWidth.Top, x + m_fFolderWidth, getHeight() - m_sBorderWidth.Bottom }, m_sFolderBackgroundColor);
				x += m_fFolderWidth;
			}

			// Render folder separator
			if (ntl::IsGreater<float>(m_fFolderSeparatorWidth, 0))
			{
				if (m_cFolderSeparatorGradient.getPointCount() > 1)
					renderer->DrawGradient(RectF{ x, m_sBorderWidth.Top, x + m_fFolderSeparatorWidth, getHeight() - m_sBorderWidth.Bottom }, m_cFolderSeparatorGradient);
				else if (m_sFolderSeparatorColor.A > 0)
					renderer->DrawRectangle(RectF{ x, m_sBorderWidth.Top, x + m_fFolderSeparatorWidth, getHeight() - m_sBorderWidth.Bottom }, m_sFolderSeparatorColor);
				x += m_fFolderSeparatorWidth;
			}

			// Render caption separator
			float width_caption{ CalculateCaptionWidth() }, width_value{ CalculateHandlerWidth() }, x_caption{ x }, x_value{ x + width_caption + m_fCaptionSeparatorWidth };
			x += width_caption;
			if (ntl::IsGreater<float>(m_fCaptionSeparatorWidth, 0))
			{
				if (m_cCaptionSeparatorGradient.getPointCount() > 1)
					renderer->DrawGradient(RectF{ x, m_sBorderWidth.Top, x + m_fCaptionSeparatorWidth, getHeight() - m_sBorderWidth.Bottom }, m_cCaptionSeparatorGradient);
				else if (m_sCaptionSeparatorColor.A > 0)
					renderer->DrawRectangle(RectF{ x, m_sBorderWidth.Top, x + m_fCaptionSeparatorWidth, getHeight() - m_sBorderWidth.Bottom }, m_sCaptionSeparatorColor);
				x += m_fCaptionSeparatorWidth;
			}

			// Items
			IPlatformFont *pf{ getFont()->getPlatformFont(renderer) };
			float line_height{ pf->getStringSize(L"Wy", 0).Y };
			Block b{ RectF{ 0, 0, getWidth(), getHeight() }, m_sBorderWidth, RectF{ 0, 0, 0, 0 }, PointLocation::Inside };
			float border_folder_icon{ m_fFolderIconBorderWidth + m_fFolderIconInnerPadding };
			float width_folder_icon{ ntl::IsGreater<float>(m_fFolderWidth, 0) ? ntl::Max<float>(0, m_fFolderWidth - 2 * m_fFolderIconPadding) : 0 };
			RectF folder_icon_border{ m_fFolderIconBorderWidth, m_fFolderIconBorderWidth, m_fFolderIconBorderWidth, m_fFolderIconBorderWidth };
			RectF folder_icon_radius{ m_fFolderIconBorderRadius, m_fFolderIconBorderRadius, m_fFolderIconBorderRadius, m_fFolderIconBorderRadius };
			BorderColor folder_icon_border_color{ m_sFolderIconBorderColor, m_sFolderIconBorderColor, m_sFolderIconBorderColor, m_sFolderIconBorderColor };
			IBaseTexture *old{ renderer->ActiveTarget };
			ITexture *folder_icon_folded{ ntl::IsGreater<float>(width_folder_icon, 0) ? renderer->CreateTexture(ntl::Round<int>(width_folder_icon), ntl::Round<int>(width_folder_icon), 1, TextureFormat::RGBA, true) : nullptr };
			ITexture *folder_icon_unfolded{ ntl::IsGreater<float>(width_folder_icon, 0) ? renderer->CreateTexture(ntl::Round<int>(width_folder_icon), ntl::Round<int>(width_folder_icon), 1, TextureFormat::RGBA, true) : nullptr };
			PointB folder_icon_drawn{ false, false };
			ITexture *clip_caption{ ntl::IsGreater<float>(width_caption, 0) ? renderer->CreateTexture(ntl::Round<int>(width_caption), ntl::Round<int>(m_fRowHeight), 1, TextureFormat::RGBA, true) : nullptr };
			RectF clip_caption_rect{ 0, 0, clip_caption ? clip_caption->Widthf : 0, clip_caption ? clip_caption->Heightf : 0 };
			ITexture *clip_value{ ntl::IsGreater<float>(width_value, 0) ? renderer->CreateTexture(ntl::Round<int>(width_value), ntl::Round<int>(m_fRowHeight), 1, TextureFormat::RGBA, true) : nullptr };
			RectF clip_value_rect{ 0, 0, clip_value ? clip_value->Widthf : 0, clip_value ? clip_value->Heightf : 0 };
			float y{ m_sBorderWidth.Top };
			if (getScroll()->isEnabled())
				y -= getScroll()->getScroll();
			for (auto pos = m_aProperties.begin(); pos != m_aProperties.end(); pos++)
			{
				// Folder
				if (folder_icon_folded && folder_icon_unfolded && pos->PropertyState && y + m_fRowHeight >= m_sBorderWidth.Top && y < getHeight() - m_sBorderWidth.Bottom)
				{
					if (pos->Folded)
					{
						if (!folder_icon_drawn.X)
						{
							renderer
								->ActivateTarget(folder_icon_folded)
								->Clear(Color{ 0, 0, 0, 0 });
							DrawSimpleBackground(renderer, RectF{ 0, 0, width_folder_icon, width_folder_icon }, folder_icon_border, folder_icon_radius, folder_icon_border_color,
								m_sFolderIconBackgroundColor, m_cFolderIconBackgroundGradient);
							float icon_width{ width_folder_icon - 2 * border_folder_icon - 2 };
							float center{ width_folder_icon * 0.5f };
							if (ntl::IsGreater<float>(icon_width, 0) && m_aFolderIconLineColor[(int)FolderState::Folded].A > 0)
							{
								renderer->DrawRectangle(RectF{ border_folder_icon, center - 0.5f, width_folder_icon - border_folder_icon, center + 0.5f }, m_aFolderIconLineColor[(int)FolderState::Folded]);
								renderer->DrawRectangle(RectF{ center - 0.5f, border_folder_icon, center + 0.5f, width_folder_icon - border_folder_icon }, m_aFolderIconLineColor[(int)FolderState::Folded]);
							}
							renderer->ActivateTarget(old);
							folder_icon_drawn.X = true;
						}
					}
					else
					{
						if (!folder_icon_drawn.Y)
						{
							renderer
								->ActivateTarget(folder_icon_unfolded)
								->Clear(Color{ 0, 0, 0, 0 });
							DrawSimpleBackground(renderer, RectF{ 0, 0, width_folder_icon, width_folder_icon }, folder_icon_border, folder_icon_radius, folder_icon_border_color,
								m_sFolderIconBackgroundColor, m_cFolderIconBackgroundGradient);
							float icon_width{ width_folder_icon - 2 * border_folder_icon - 2 };
							float center{ width_folder_icon * 0.5f };
							if (ntl::IsGreater<float>(icon_width, 0) && m_aFolderIconLineColor[(int)FolderState::Unfolded].A > 0)
								renderer->DrawRectangle(RectF{ border_folder_icon, center - 0.5f, width_folder_icon - border_folder_icon, center + 0.5f }, m_aFolderIconLineColor[(int)FolderState::Folded]);
							renderer->ActivateTarget(old);
							folder_icon_drawn.Y = true;
						}
					}
					CStoreBlock s_block{ renderer };
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivateBlock(getScroll()->isEnabled() ? &b : nullptr)
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(m_sBorderWidth.Left + m_fFolderIconPadding, y + (m_fRowHeight - width_folder_icon) * 0.5f, 0))
						->DrawImage(pos->Folded ? folder_icon_folded : folder_icon_unfolded, 1);
				}

				// Caption
				if (clip_caption)
				{
					PropertyState state{ getPropertyState(int(pos - m_aProperties.begin())) };
					Color color{ m_aCaptionColor[(int)state].A > 0 ? m_aCaptionColor[(int)state] : getFont()->Color };
					if (color.A > 0 && y + m_fRowHeight >= m_sBorderWidth.Top && y < getHeight() - m_sBorderWidth.Bottom)
					{
						renderer
							->ActivateTarget(clip_caption)
							->Clear(Color{ 0, 0, 0, 0 });

						DrawSimpleBackground(renderer, clip_caption_rect, RectF{ m_aCaptionBorderWidth[(int)state], m_aCaptionBorderWidth[(int)state], m_aCaptionBorderWidth[(int)state],
							m_aCaptionBorderWidth[(int)state] }, RectF{ 0, 0, 0, 0 }, BorderColor{ m_aCaptionBorderColor[(int)state], m_aCaptionBorderColor[(int)state], m_aCaptionBorderColor[(int)state],
							m_aCaptionBorderColor[(int)state] }, m_aCaptionBackgroundColor[(int)state], m_aCaptionBackgroundGradient[(int)state]);

						CStoreBlock s_block{ renderer };
						CStorePrimitiveMatrix s_matrix{ renderer };
						renderer
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(m_fCaptionPadding, (m_fRowHeight - line_height) * 0.5f, 0))
							->DrawText(pos->Property->Name, pf, getFont()->Distance, color)
							->ActivateTarget(old)
							->ActivateBlock(getScroll()->isEnabled() ? &b : nullptr)
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(x_caption + clip_caption_rect.Left, y + clip_caption_rect.Top, 0))
							->DrawImage(clip_caption, 1);
					}
					// Caption states
					if (!pos->Folded)
					{
						for (int i = 0; i < pos->PropertyState->getStateCount(); i++)
						{
							state = getPropertyState(int(pos - m_aProperties.begin()), i);
							color = m_aCaptionColor[(int)state].A > 0 ? m_aCaptionColor[(int)state] : getFont()->Color;
							if (color.A > 0 && y + float(2 + i) * m_fRowHeight >= m_sBorderWidth.Top && y + float(1 + i) * m_fRowHeight < getHeight() - m_sBorderWidth.Bottom)
							{
								renderer
									->ActivateTarget(clip_caption)
									->Clear(Color{ 0, 0, 0, 0 });

								DrawSimpleBackground(renderer, clip_caption_rect, RectF{ m_aCaptionBorderWidth[(int)state], m_aCaptionBorderWidth[(int)state], m_aCaptionBorderWidth[(int)state],
									m_aCaptionBorderWidth[(int)state] }, RectF{ 0, 0, 0, 0 }, BorderColor{ m_aCaptionBorderColor[(int)state], m_aCaptionBorderColor[(int)state], m_aCaptionBorderColor[(int)state],
									m_aCaptionBorderColor[(int)state] }, m_aCaptionBackgroundColor[(int)state], m_aCaptionBackgroundGradient[(int)state]);

								CStoreBlock s_block{ renderer };
								CStorePrimitiveMatrix s_matrix{ renderer };
								renderer
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(m_fCaptionPadding + m_fCaptionStatePadding, (m_fRowHeight - line_height) * 0.5f, 0))
									->DrawText(pos->PropertyState->getState(i), pf, getFont()->Distance, color)
									->ActivateTarget(old)
									->ActivateBlock(getScroll()->isEnabled() ? &b : nullptr)
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(x_caption + clip_caption_rect.Left, y + float(i + 1) * m_fRowHeight + clip_caption_rect.Top, 0))
									->DrawImage(clip_caption, 1);
							}
						}
					}
				}

				// Value
				if (clip_value)
				{
					if (!isFocused() || int(pos - m_aProperties.begin()) != m_iFocusedPropertyIndex || m_iFocusedPropertyStateIndex >= 0)
					{
						if (getFont()->Color.A > 0 && y + m_fRowHeight >= m_sBorderWidth.Top && y < getHeight() - m_sBorderWidth.Bottom)
						{
							String property_string{ pos->Property->getPreview() };
							if (!property_string.empty())
							{
								CStoreBlock s_block{ renderer };
								CStorePrimitiveMatrix s_matrix{ renderer };
								renderer
									->ActivateTarget(clip_value)
									->Clear(Color{ 0, 0, 0, 0 })
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(m_fCaptionPadding, (m_fRowHeight - line_height) * 0.5f, 0))
									->DrawText(property_string, pf, getFont()->Distance, getFont()->Color)
									->ActivateTarget(old)
									->ActivateBlock(getScroll()->isEnabled() ? &b : nullptr)
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(x_value + clip_value_rect.Left, y + clip_value_rect.Top, 0))
									->DrawImage(clip_value, 1);
							}
						}
					}
					else if (int(pos - m_aProperties.begin()) == m_iFocusedPropertyIndex && m_iFocusedPropertyStateIndex < 0 && y + m_fRowHeight >= m_sBorderWidth.Top && y < getHeight() - m_sBorderWidth.Bottom)
					{
						CStoreBlock s_block{ renderer };
						CStorePrimitiveMatrix s_matrix{ renderer };
						renderer
							->ActivateTarget(clip_value)
							->Clear(Color{ 0, 0, 0, 0 })
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(-x_value - clip_value_rect.Left, -y - clip_value_rect.Top, 0))
							->DrawImage(old, 1)
							->ActivatePrimitiveMatrix(nullptr);
						m_pHandler->Render(false, Identity, nullptr);
						renderer
							->ActivateTarget(old)
							->ActivateBlock(getScroll()->isEnabled() ? &b : nullptr)
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(x_value + clip_value_rect.Left, y + clip_value_rect.Top, 0))
							->DrawImage(clip_value, 1);
					}
					// States
					if (!pos->Folded)
					{
						for (int i = 0; i < pos->PropertyState->getStateCount(); i++)
						{
							if (!isFocused() || int(pos - m_aProperties.begin()) != m_iFocusedPropertyIndex || m_iFocusedPropertyStateIndex != i)
							{
								if (getFont()->Color.A > 0 && y + float(2 + i) * m_fRowHeight >= m_sBorderWidth.Top && y + float(1 + i) * m_fRowHeight < getHeight() - m_sBorderWidth.Bottom)
								{
									String property_string{ pos->PropertyState->getPreview(pos->PropertyState->getState(i)) };
									if (!property_string.empty())
									{
										CStoreBlock s_block{ renderer };
										CStorePrimitiveMatrix s_matrix{ renderer };
										renderer
											->ActivateTarget(clip_value)
											->Clear(Color{ 0, 0, 0, 0 })
											->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(m_fCaptionPadding, (m_fRowHeight - line_height) * 0.5f, 0))
											->DrawText(property_string, pf, getFont()->Distance, getFont()->Color)
											->ActivateTarget(old)
											->ActivateBlock(getScroll()->isEnabled() ? &b : nullptr)
											->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(x_value + clip_value_rect.Left, y + float(i + 1) * m_fRowHeight + clip_value_rect.Top, 0))
											->DrawImage(clip_value, 1);
									}
								}
							}
							else if (int(pos - m_aProperties.begin()) == m_iFocusedPropertyIndex && m_iFocusedPropertyStateIndex == i &&
								y + float(2 + i) * m_fRowHeight >= m_sBorderWidth.Top && y + float(1 * i) * m_fRowHeight < getHeight() - m_sBorderWidth.Bottom)
							{
								CStoreBlock s_block{ renderer };
								CStorePrimitiveMatrix s_matrix{ renderer };
								renderer
									->ActivateTarget(clip_value)
									->Clear(Color{ 0, 0, 0, 0 })
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(-x_value - clip_value_rect.Left, -y - float(i + 1) * m_fRowHeight - clip_value_rect.Top, 0))
									->DrawImage(old, 1)
									->ActivatePrimitiveMatrix(nullptr);
								m_pHandler->Render(false, Identity, nullptr);
								renderer
									->ActivateTarget(old)
									->ActivateBlock(getScroll()->isEnabled() ? &b : nullptr)
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(x_value + clip_value_rect.Left, y + float(i + 1) * m_fRowHeight + clip_value_rect.Top, 0))
									->DrawImage(clip_value, 1);
							}
						}
					}
				}
				y += m_fRowHeight;
				if (!pos->Folded)
					y += m_fRowHeight * (float)pos->PropertyState->getStateCount();
			}
			if (clip_caption)
				clip_caption->Release();
			if (clip_value)
				clip_value->Release();
			if (folder_icon_folded)
				folder_icon_folded->Release();
			if (folder_icon_unfolded)
				folder_icon_unfolded->Release();

			// Scroll
			getScroll()->setSize(PointF{ getScroll()->getSize().X, getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom });
			getScroll()->Render(false, ntl::Mat4Translate<float>(getWidth() - m_sBorderWidth.Left - getScroll()->getSize().X, m_sBorderWidth.Top, 0), nullptr);
		}

		void CPropertyEditor::RenderHandler() // Called at second render pass
		{
			Update();
			if (isFocused() && m_pHandler && m_fHandlerY + m_fRowHeight >= m_sBorderWidth.Top && m_fHandlerY < getHeight() - m_sBorderWidth.Bottom)
				m_pHandler->Render(true, getTransformMatrix() * ntl::Mat4Translate<float>(CalculateHandlerX(), m_fHandlerY, 0), nullptr);
		}
	#pragma endregion
	}
}
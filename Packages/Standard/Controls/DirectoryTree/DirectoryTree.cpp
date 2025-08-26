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
		const float CDirectoryTree::ItemHeightAuto{ -1 };
		const float CDirectoryTree::ItemHeightText{ 0 };

	#pragma region CGradientListener
		CDirectoryTree::CGradientListener::CGradientListener(CDirectoryTree *control) :
			m_pControl{ control }
		{

		}

		void CDirectoryTree::CGradientListener::NotifyOnChange()
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
		CDirectoryTree::CDirectoryTree() :
			CControl(L"DirectoryTree", true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_pFileList{ nullptr },
			m_bShowArchieved{ true },
			m_bShowCompressed{ true },
			m_bShowEncrypted{ true },
			m_bShowHidden{ false },
			m_bShowNormal{ true },
			m_bShowOffline{ false },
			m_bShowReadOnly{ true },
			m_bShowSystem{ true },
			m_bShowTemporary{ false },
			m_sBorderWidth{ 1, 1, 1, 1 },
			m_sBorderRadius{ 0, 0, 0, 0 },
			m_sPadding{ 1, 1, 1, 1 },
			m_aBorderColor{
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } },
				BorderColor{ Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 } },
				BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } },
				BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } },
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } } },
			m_aBackgroundColor{
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 244, 244, 244, 255 } },
			m_aBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aShadowColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aShadowRadius{ 1, 1, 1, 1, 1 },
			m_aCornerColor{
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 } },
			m_fItemHeight{ -1 },
			m_sFolderSize{ 9, 9 },
			m_sFolderLinesColor{ 200, 200, 200, 255 },
			m_aFolderBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aFolderBorderRadius{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aFolderBorderColor{
				BorderColor{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 } },
				BorderColor{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 } } },
			m_aFolderBackgroundColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aFolderBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aFolderSignSize{
				PointF{ 5, 1 },
				PointF{ 5, 1 } },
			m_aFolderSignColor{
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 } },
			m_bMultiselect{ true },
			m_eHScrollVisibility{ ScrollVisibility::Auto },
			m_eVScrollVisibility{ ScrollVisibility::Auto },
			m_fScrollInterval{ 0.3f },
			m_fScrollDelta{ 10 },
			m_pCanvas{ nullptr },
			m_pVScroll{ nullptr },
			m_pHScroll{ nullptr },
			m_cScrollListener{ this },
			m_bHScrollVisible{ false },
			m_bVScrollVisible{ false },
			m_iLockUpdate{ 0 },
			m_eHoveredElement{ Element::None },
			m_eDownElement{ Element::None },
			m_pHoveredItem{ nullptr },
			m_bIgnoreGradient{ false },
			m_bItemsSorted{ true },
			m_cOwner{ this },
			OnSelectDirectory{ nullptr },
			OnDeselectDirectory{ nullptr },
			OnActivateDirectory{ nullptr },
			OnDeactivateDirectory{ nullptr }
		{
			if (Application->System->Platform == PlatformType::Windows)
				m_sRootDirectory = L"C:\\";
			setService(new CDirectoryTreeService(this), true);
			m_cRootItem.QueryService()->setOwner(&m_cOwner);
			setSize(PointF{ 121, 97 });
			Rescan();
		}

		CDirectoryTree::CDirectoryTree(IForm *parent) :CDirectoryTree()
		{
			setForm(parent);
		}

		CDirectoryTree::CDirectoryTree(IControl *parent) : CDirectoryTree()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IControl methods
		void CDirectoryTree::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region Interface getters
		RectF CDirectoryTree::getClientRect()
		{
			RectF result{
				m_sBorderWidth.Left + m_sPadding.Left,
				m_sBorderWidth.Top + m_sPadding.Top,
				getWidth() - m_sBorderWidth.Right - m_sPadding.Right - (m_bVScrollVisible ? getVScroll()->getWidth() : 0),
				getHeight() - m_sBorderWidth.Bottom - m_sPadding.Bottom - (m_bHScrollVisible ? getHScroll()->getHeight() : 0)
			};
			result.validate();
			return result;
		}

		RectF CDirectoryTree::getRenderRect()
		{
			State state{ getState() };
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
		}

		String CDirectoryTree::getRootDirectory()
		{
			return m_sRootDirectory;
		}

		String CDirectoryTree::getDirectory()
		{
			return getItemPath(FindActiveItem(&m_cRootItem));
		}

		String CDirectoryTree::getFilter()
		{
			return m_sFilter;
		}

		IFileList *CDirectoryTree::getFileList()
		{
			return m_pFileList;
		}

		bool CDirectoryTree::isShowArchieved()
		{
			return m_bShowArchieved;
		}

		bool CDirectoryTree::isShowCompressed()
		{
			return m_bShowCompressed;
		}

		bool CDirectoryTree::isShowEncrypted()
		{
			return m_bShowEncrypted;
		}

		bool CDirectoryTree::isShowHidden()
		{
			return m_bShowHidden;
		}

		bool CDirectoryTree::isShowNormal()
		{
			return m_bShowNormal;
		}

		bool CDirectoryTree::isShowOffline()
		{
			return m_bShowOffline;
		}

		bool CDirectoryTree::isShowReadOnly()
		{
			return m_bShowReadOnly;
		}

		bool CDirectoryTree::isShowSystem()
		{
			return m_bShowSystem;
		}

		bool CDirectoryTree::isShowTemporary()
		{
			return m_bShowTemporary;
		}
	#pragma endregion

	#pragma region Getters
		CDirectoryTree::State CDirectoryTree::getState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (isFocused())
			{
				if (isHovered())
					return State::FocusedHovered;
				return State::Focused;
			}
			if (isHovered())
				return State::Hovered;
			return State::Normal;
		}

		RectF CDirectoryTree::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		RectF CDirectoryTree::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		RectF CDirectoryTree::getPadding() const
		{
			return m_sPadding;
		}

		BorderColor CDirectoryTree::getBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CDirectoryTree::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CDirectoryTree::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		Color CDirectoryTree::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		PointF CDirectoryTree::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		int CDirectoryTree::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		Color CDirectoryTree::getCornerColor(const State state) const
		{
			return m_aCornerColor[(int)state];
		}

		float CDirectoryTree::getItemHeight() const
		{
			return m_fItemHeight;
		}

		PointF CDirectoryTree::getFolderSize() const
		{
			return m_sFolderSize;
		}

		Color CDirectoryTree::getFolderLinesColor() const
		{
			return m_sFolderLinesColor;
		}

		RectF CDirectoryTree::getFolderBorderWidth(const FolderState state) const
		{
			return m_aFolderBorderWidth[(int)state];
		}

		RectF CDirectoryTree::getFolderBorderRadius(const FolderState state) const
		{
			return m_aFolderBorderRadius[(int)state];
		}

		BorderColor CDirectoryTree::getFolderBorderColor(const FolderState state) const
		{
			return m_aFolderBorderColor[(int)state];
		}

		Color CDirectoryTree::getFolderBackgroundColor(const FolderState state) const
		{
			return m_aFolderBackgroundColor[(int)state];
		}

		Gradient *CDirectoryTree::getFolderBackgroundGradient(const FolderState state)
		{
			return &m_aFolderBackgroundGradient[(int)state];
		}

		PointF CDirectoryTree::getFolderSignSize(const FolderState state) const
		{
			return m_aFolderSignSize[(int)state];
		}

		Color CDirectoryTree::getFolderSignColor(const FolderState state) const
		{
			return m_aFolderSignColor[(int)state];
		}

		bool CDirectoryTree::isMultiselect() const
		{
			return m_bMultiselect;
		}

		ScrollVisibility CDirectoryTree::getHScrollVisibility() const
		{
			return m_eHScrollVisibility;
		}

		ScrollVisibility CDirectoryTree::getVScrollVisibility() const
		{
			return m_eVScrollVisibility;
		}

		float CDirectoryTree::getScrollInterval() const
		{
			return m_fScrollInterval;
		}

		float CDirectoryTree::getScrollDelta() const
		{
			return m_fScrollDelta;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CDirectoryTree::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				getHScroll()->setDPI(value);
				getVScroll()->setDPI(value);
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sBorderWidth *= s;
				m_sBorderRadius *= avg;
				m_sPadding *= s;
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aShadowShift[i] *= s;
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
				}
				if (ntl::IsGreater<float>(m_fItemHeight, 0))
					m_fItemHeight *= s.Y;
				m_sFolderSize *= s;
				for (int i = 0; i <= (int)FolderState::Hovered; i++)
				{
					m_aFolderBorderWidth[i] *= s;
					m_aFolderBorderRadius[i] *= avg;
					m_aFolderSignSize[i] *= s;
				}
				m_fScrollDelta *= avg;
				SetListItemDPI(&m_cRootItem);
				Update();
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setRootDirectory(const String &value)
		{
			String v{ value };
			if (v.length() > 0 && v[v.length() - 1] != Application->System->DirectorySeparator)
				v += Application->System->DirectorySeparator;
			if (v.length() > 0 && v != m_sRootDirectory)
			{
				m_sRootDirectory = v;
				Rescan();
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setFilter(const String &value)
		{
			if (value != m_sFilter)
			{
				m_sFilter = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setFileList(IFileList *value)
		{
			if (value != m_pFileList && (!value || (value && value->getForm() && value->getForm() == getForm())))
			{
				m_pFileList = value;
				if (m_pFileList)
					m_pFileList->setDirectory(getDirectory());
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setShowArchieved(const bool value)
		{
			if (value != m_bShowArchieved)
			{
				m_bShowArchieved = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setShowCompressed(const bool value)
		{
			if (value != m_bShowCompressed)
			{
				m_bShowCompressed = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setShowEncrypted(const bool value)
		{
			if (value != m_bShowEncrypted)
			{
				m_bShowEncrypted = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setShowHidden(const bool value)
		{
			if (value != m_bShowHidden)
			{
				m_bShowHidden = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setShowNormal(const bool value)
		{
			if (value != m_bShowNormal)
			{
				m_bShowNormal = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setShowOffline(const bool value)
		{
			if (value != m_bShowOffline)
			{
				m_bShowOffline = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setShowReadOnly(const bool value)
		{
			if (value != m_bShowReadOnly)
			{
				m_bShowReadOnly = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setShowSystem(const bool value)
		{
			if (value != m_bShowSystem)
			{
				m_bShowSystem = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setShowTemporary(const bool value)
		{
			if (value != m_bShowTemporary)
			{
				m_bShowTemporary = value;
				Rescan();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CDirectoryTree::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				LockUpdate();
				m_sBorderWidth = value;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setBorderRadius(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderRadius))
			{
				m_sBorderRadius = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				LockUpdate();
				m_sPadding = value;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aBorderColor[(int)state])
			{
				m_aBorderColor[(int)state] = value;
				if (getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setLeftBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ value, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CDirectoryTree::setTopBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, value, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CDirectoryTree::setRightBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, value, m_aBorderColor[(int)state].Bottom });
		}

		bool CDirectoryTree::setBottomBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, value });
		}

		bool CDirectoryTree::setBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aBackgroundColor[(int)state])
			{
				m_aBackgroundColor[(int)state] = value;
				if (getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setShadowColor(const State state, const Color &value)
		{
			if (value != m_aShadowColor[(int)state])
			{
				CLockRepaint lock{ this };
				State s{ getState() };
				if (s == state && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				m_aShadowColor[(int)state] = value;
				if (s == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				State s{ getState() };
				if (s == state && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				m_aShadowShift[(int)state] = value;
				if (s == state && m_aShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setShadowRadius(const State state, const int value)
		{
			if (value > 0 && value != m_aShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				State s{ getState() };
				if (s == state && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				m_aShadowRadius[(int)state] = value;
				if (s == state && m_aShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setCornerColor(const State state, const Color &value)
		{
			if (value != m_aCornerColor[(int)state])
			{
				m_aCornerColor[(int)state] = value;
				if (getState() == state && m_bHScrollVisible && m_bVScrollVisible)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setItemHeight(const float value)
		{
			if (ntl::IsLess<float>(value, 0) && ntl::IsLess<float>(m_fItemHeight, 0))
				return false;
			if (ntl::IsNotEqual<float>(value, m_fItemHeight))
			{
				LockUpdate();
				if (ntl::IsLess<float>(value, 0))
					m_fItemHeight = -1;
				else
					m_fItemHeight = value;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setFolderSize(const PointF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, m_sFolderSize))
			{
				m_sFolderSize = value;
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setFolderLinesColor(const Color &value)
		{
			if (value != m_sFolderLinesColor)
			{
				m_sFolderLinesColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setFolderBorderWidth(const FolderState state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aFolderBorderWidth[(int)state]))
			{
				m_aFolderBorderWidth[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setFolderBorderRadius(const FolderState state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aFolderBorderRadius[(int)state]))
			{
				m_aFolderBorderRadius[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setFolderBorderColor(const FolderState state, const BorderColor &value)
		{
			if (value != m_aFolderBorderColor[(int)state])
			{
				m_aFolderBorderColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setFolderBackgroundColor(const FolderState state, const Color &value)
		{
			if (value != m_aFolderBackgroundColor[(int)state])
			{
				m_aFolderBackgroundColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setFolderSignSize(const FolderState state, const PointF &value)
		{
			if (ntl::IsGreaterOrEqual<float>(value.X, 0) && ntl::IsGreaterOrEqual<float>(value.Y, 0) && IsNotEqual(value, m_aFolderSignSize[(int)state]))
			{
				m_aFolderSignSize[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setFolderSignColor(const FolderState state, const Color &value)
		{
			if (value != m_aFolderSignColor[(int)state])
			{
				m_aFolderSignColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setMultiselect(const bool value)
		{
			if (value != m_bMultiselect)
			{
				CLockRepaint lock{ this };
				m_bMultiselect = value;
				if (!m_bMultiselect)
					DeselectAllExceptFirst();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setHScrollVisibility(const ScrollVisibility value)
		{
			if (value != m_eHScrollVisibility)
			{
				LockUpdate();
				m_eHScrollVisibility = value;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setVScrollVisibility(const ScrollVisibility value)
		{
			if (value != m_eVScrollVisibility)
			{
				LockUpdate();
				m_eVScrollVisibility = value;
				UnlockUpdate();
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setScrollInterval(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollInterval))
			{
				m_fScrollInterval = value;
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setScrollDelta(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollDelta))
			{
				m_fScrollDelta = value;
				return true;
			}
			return false;
		}

		bool CDirectoryTree::setBorderColor(const BorderColor &value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setBorderColor((State)i, value) || result;
			return result;
		}

		bool CDirectoryTree::setLeftBorderColor(const Color &value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setLeftBorderColor((State)i, value) || result;
			return result;
		}

		bool CDirectoryTree::setTopBorderColor(const Color &value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setTopBorderColor((State)i, value) || result;
			return result;
		}

		bool CDirectoryTree::setRightBorderColor(const Color &value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setRightBorderColor((State)i, value) || result;
			return result;
		}

		bool CDirectoryTree::setBottomBorderColor(const Color &value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setBottomBorderColor((State)i, value) || result;
			return result;
		}

		bool CDirectoryTree::setBackgroundColor(const Color &value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setBackgroundColor((State)i, value) || result;
			return result;
		}

		bool CDirectoryTree::setShadowColor(const Color &value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setShadowColor((State)i, value) || result;
			return result;
		}

		bool CDirectoryTree::setShadowShift(const PointF &value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setShadowShift((State)i, value) || result;
			return result;
		}

		bool CDirectoryTree::setShadowRadius(const int value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setShadowRadius((State)i, value) || result;
			return result;
		}

		bool CDirectoryTree::setCornerColor(const Color &value)
		{
			bool result{ false };
			CLockRepaint lock{ this };
			for (int i = 0; i <= (int)State::Disabled; i++)
				result = setCornerColor((State)i, value) || result;
			return result;
		}
	#pragma endregion

	#pragma region Helpers
		void CDirectoryTree::UpdateFromStyle(IStyle *style)
		{
			style->getOption(m_sClassName + L".BorderWidth", m_sBorderWidth);
			style->getOption(m_sClassName + L".BorderRadius", m_sBorderRadius);
			style->getOption(m_sClassName + L".Padding", m_sPadding);
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				String name;
				switch ((State)i)
				{
				case State::Hovered:
					name = L"Hovered";
					break;
				case State::Focused:
					name = L"Focused";
					break;
				case State::FocusedHovered:
					name = L"FocusedHovered";
					break;
				case State::Disabled:
					name = L"Disabled";
					break;
				default:
					name = L"Normal";
				}
				style->getOption(m_sClassName + L".BorderColor[" + name + L"]", m_aBorderColor[i]);
				style->getOption(m_sClassName + L".BackgroundColor[" + name + L"]", m_aBackgroundColor[i]);
				style->getOption(m_sClassName + L".BackgroundGradient[" + name + L"]", m_aBackgroundGradient[i]);
				style->getOption(m_sClassName + L".ShadowColor[" + name + L"]", m_aShadowColor[i]);
				style->getOption(m_sClassName + L".ShadowShift[" + name + L"]", m_aShadowShift[i]);
				style->getOption(m_sClassName + L".ShadowRadius[" + name + L"]", m_aShadowRadius[i]);
				style->getOption(m_sClassName + L".CornerColor[" + name + L"]", m_aCornerColor[i]);
			}
			style->getOption(m_sClassName + L".ItemHeight", m_fItemHeight);
			style->getOption(m_sClassName + L".FolderSize", m_sFolderSize);
			style->getOption(m_sClassName + L".FolderLinesColor", m_sFolderLinesColor);
			for (int i = 0; i <= (int)FolderState::Hovered; i++)
			{
				String name;
				switch ((FolderState)i)
				{
				case FolderState::Hovered:
					name = L"Hovered";
					break;
				default:
					name = L"Normal";
				}
				style->getOption(m_sClassName + L".FolderBorderWidth[" + name + L"]", m_aFolderBorderWidth[i]);
				style->getOption(m_sClassName + L".FolderBorderRadius[" + name + L"]", m_aFolderBorderRadius[i]);
				style->getOption(m_sClassName + L".FolderBorderColor[" + name + L"]", m_aFolderBorderColor[i]);
				style->getOption(m_sClassName + L".FolderBackgroundColor[" + name + L"]", m_aFolderBackgroundColor[i]);
				style->getOption(m_sClassName + L".FolderBackgroundGradient[" + name + L"]", m_aFolderBackgroundGradient[i]);
				style->getOption(m_sClassName + L".FolderSignSize[" + name + L"]", m_aFolderSignSize[i]);
				style->getOption(m_sClassName + L".FolderSignColor[" + name + L"]", m_aFolderSignColor[i]);
			}
			style->getOption(m_sClassName + L".ScrollInterval", m_fScrollInterval);
			style->getOption(m_sClassName + L".ScrollDelta", m_fScrollDelta);
			m_cOwner.setIgnoreSizeChange(true);
			m_cOwner.setIgnoreRepaintRequired(true);
			UpdateItemFromStyle(&m_cRootItem);
			m_cOwner.setIgnoreSizeChange(false);
			m_cOwner.setIgnoreRepaintRequired(false);
			Update();
			UpdateHoveredElement();
		}

		IBuiltInScroll *CDirectoryTree::getVScroll()
		{
			if (!m_pVScroll)
			{
				CScroll *scroll{ new CScroll(this) };
				scroll->setListener(&m_cScrollListener);
				m_pVScroll = scroll;
				if (!scroll->isVertical())
					scroll->SwitchDirection(true);
			}
			return m_pVScroll;
		}

		IBuiltInScroll *CDirectoryTree::getHScroll()
		{
			if (!m_pHScroll)
			{
				CScroll *scroll{ new CScroll(this) };
				scroll->setListener(&m_cScrollListener);
				m_pHScroll = scroll;
				if (scroll->isVertical())
					scroll->SwitchDirection(true);
			}
			return m_pHScroll;
		}

		void CDirectoryTree::LockUpdate()
		{
			m_iLockUpdate++;
		}

		void CDirectoryTree::UnlockUpdate()
		{
			if (--m_iLockUpdate <= 0)
			{
				Update();
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
		}

		void CDirectoryTree::EnumSelectedDirectories(void *param, FDirectoryCallback callback)
		{
			if (callback)
			{
				EnumItems(&m_cRootItem, param, callback, [](CDirectoryTree *tree, void *param, IListItem *item, FDirectoryCallback callback) {
					if (item->isVisible() && item->isSelected())
						callback(param, tree->getItemPath(item));
				});
			}
		}

		void CDirectoryTree::EnumItems(IListItem *item, void *param, FDirectoryCallback callback, void(*enumerator)(CDirectoryTree *tree, void *param, IListItem *item, FDirectoryCallback callback))
		{
			for (int i = 0; i < item->getItemCount(); i++)
			{
				enumerator(this, param, item->getItem(i), callback);
				EnumItems(item->getItem(i), param, callback, enumerator);
			}
		}

		void CDirectoryTree::SortItems()
		{
			if (!m_bItemsSorted)
			{
				std::sort(m_aItems.begin(), m_aItems.end(), [](const ITEM &a, const ITEM &b) {return a.Item < b.Item; });
				m_bItemsSorted = true;
			}
		}

		int CDirectoryTree::FindItemIndex(IListItem *item) // Assume m_aItems is sorted
		{
			ITEM s{ item };
			auto pos{ std::lower_bound(m_aItems.begin(), m_aItems.end(), s, [](const ITEM &a, const ITEM &b) {return a.Item < b.Item; }) };
			if (pos == m_aItems.end() || pos->Item != item)
				return -1;
			return int(pos - m_aItems.begin());
		}

		void CDirectoryTree::CalculateRequiredSize(IListItem *parent, PointF &required_size, const float line_height, const int level)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible())
				{
					PointF size{ parent->getItem(i)->QueryService()->getRequiredSize() };
					float height{ ntl::IsGreater<float>(m_fItemHeight, 0) ? m_fItemHeight : (ntl::IsEqual<float>(m_fItemHeight, 0) ? line_height : size.Y) };
					required_size.Y += height;
					required_size.X = ntl::Max<float>(required_size.X, size.X + height * (float)level);
					parent->getItem(i)->QueryService()->setSize(PointF{ size.X, height });
					if (parent->getItem(i)->getItemCount() > 0)
					{
						int index{ FindItemIndex(parent->getItem(i)) };
						if (index >= 0 && !m_aItems[index].Folded)
							CalculateRequiredSize(parent->getItem(i), required_size, line_height, level + 1);
					}
				}
		}

		void CDirectoryTree::Update()
		{
			if (getForm() && getForm()->getRenderer() && getFont() && getFont()->getPlatformFont(getForm()->getRenderer()))
			{
				// Client area
				RectF client{
					m_sBorderWidth.Left + m_sPadding.Left,
					m_sBorderWidth.Top + m_sPadding.Top,
					getWidth() - m_sBorderWidth.Right - m_sPadding.Right,
					getHeight() - m_sBorderWidth.Bottom - m_sPadding.Bottom };
				if (m_eVScrollVisibility == ScrollVisibility::Visible)
					client.Right -= getVScroll()->getWidth();
				if (m_eHScrollVisibility == ScrollVisibility::Visible)
					client.Bottom -= getHScroll()->getHeight();
				if (client.is_valid() && !client.is_zero())
				{
					SortItems();
					// Calculate required size
					float line_height{ getFont()->getPlatformFont(getForm()->getRenderer())->getStringSize(L"Wy", getFont()->Distance).Y };
					PointF required_size{ 0, 0 };
					CalculateRequiredSize(&m_cRootItem, required_size, line_height, 1);
					// Update scrolls
					if (ntl::IsGreater<float>(required_size.X, client.width()))
					{
						getHScroll()->setEnabled(isEnabled(false));
						switch (m_eHScrollVisibility)
						{
						case ScrollVisibility::None:
							m_bHScrollVisible = false;
							getHScroll()->setMax(required_size.X - client.width());
							break;
						default:
							m_bHScrollVisible = true;
							getHScroll()->setMax(required_size.X - client.width());
						}
					}
					else
					{
						getHScroll()->setScroll(0);
						getHScroll()->setEnabled(false);
						m_bHScrollVisible = m_eHScrollVisibility == ScrollVisibility::Visible;
					}
					if (ntl::IsGreater<float>(required_size.Y, client.height()))
					{
						getVScroll()->setEnabled(isEnabled(false));
						switch (m_eVScrollVisibility)
						{
						case ScrollVisibility::None:
							m_bVScrollVisible = false;
							getVScroll()->setMax(required_size.Y - client.height());
							break;
						default:
							m_bVScrollVisible = true;
							getVScroll()->setMax(required_size.Y - client.height());
						}
					}
					else
					{
						getVScroll()->setScroll(0);
						getVScroll()->setEnabled(false);
						m_bVScrollVisible = m_eVScrollVisibility == ScrollVisibility::Visible;
					}
					if (m_bHScrollVisible)
					{
						getHScroll()->setPosition(PointF{ m_sBorderWidth.Left, getHeight() - m_sBorderWidth.Bottom - getHScroll()->getHeight() });
						getHScroll()->setSize(PointF{ getWidth() - m_sBorderWidth.Left - m_sBorderWidth.Right - (m_bVScrollVisible ? getVScroll()->getWidth() : 0), getHScroll()->getHeight() });
					}
					if (m_bVScrollVisible)
					{
						getVScroll()->setPosition(PointF{ getWidth() - m_sBorderWidth.Right - getVScroll()->getWidth(), m_sBorderWidth.Top });
						getVScroll()->setSize(PointF{ getVScroll()->getWidth(), getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom - (m_bHScrollVisible ? getHScroll()->getHeight() : 0) });
					}
				}
			}
		}

		bool CDirectoryTree::UpdateHoveredElement()
		{
			if (getForm())
				return UpdateHoveredElement(FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())));
			return false;
		}

		void CDirectoryTree::UpdateHoveredItem(IListItem *parent, const PointF &position, PointF &current, Element &element, IListItem **hovered, const float line_height)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				if (element != Element::None)
					return;
				if (parent->getItem(i)->isVisible())
				{
					PointF size{ parent->getItem(i)->getSize() };
					if (position.X >= current.X && position.X < current.X + size.Y + size.X && position.Y >= current.Y && position.Y < current.Y + size.Y)
					{
						if (m_sFolderSize.X > 0 && m_sFolderSize.Y > 0)
						{
							RectF folder{ current.X + (size.Y - m_sFolderSize.X) / 2, current.Y + (size.Y - m_sFolderSize.Y) / 2 };
							folder.Right = folder.Left + m_sFolderSize.X;
							folder.Bottom = folder.Top + m_sFolderSize.Y;
							if (position.X >= folder.Left && position.X < folder.Right && position.Y >= folder.Top && position.Y < folder.Bottom)
							{
								element = Element::Folder;
								*hovered = parent->getItem(i);
								return;
							}
						}
						if (position.X >= current.X + size.Y)
						{
							element = Element::Item;
							*hovered = parent->getItem(i);
							return;
						}
					}
					current.Y += size.Y;
					if (parent->getItem(i)->getItemCount() > 0 && !m_aItems[FindItemIndex(parent->getItem(i))].Folded)
					{
						current.X += size.Y;
						UpdateHoveredItem(parent->getItem(i), position, current, element, hovered, line_height);
						current.X -= size.Y;
					}
				}
				if (current.Y >= getHeight() - m_sBorderWidth.Bottom - m_sPadding.Bottom)
					break;
			}
		}

		bool CDirectoryTree::UpdateHoveredElement(const PointF &position)
		{
			if (m_eDownElement == Element::None)
			{
				Element new_element{ Element::None };
				IListItem *hovered{ nullptr };
				if (isEnabled(false))
				{
					RectF client{ m_sBorderWidth.Left, m_sBorderWidth.Top, getWidth() - m_sBorderWidth.Right, getHeight() - m_sBorderWidth.Bottom };
					if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
					{
						// VScroll
						if (m_bVScrollVisible)
						{
							if (position.X >= getVScroll()->getLeft() && position.X < getVScroll()->getLeft() + getVScroll()->getWidth() && position.Y >= getVScroll()->getTop() && position.Y < getVScroll()->getTop() + getVScroll()->getHeight())
								new_element = Element::VScroll;
							else
								client.Right -= getVScroll()->getWidth();
						}
						// HScroll
						if (new_element == Element::None && m_bHScrollVisible)
						{
							if (position.X >= getHScroll()->getLeft() && position.X < getHScroll()->getLeft() + getHScroll()->getWidth() && position.Y >= getHScroll()->getTop() && position.Y < getHScroll()->getTop() + getHScroll()->getHeight())
								new_element = Element::HScroll;
							else
								client.Bottom -= getHScroll()->getHeight();
						}
						// Items and folders
						if (new_element == Element::None)
						{
							PointF current{
								m_sBorderWidth.Left + m_sPadding.Left - (getHScroll()->isEnabled() ? getHScroll()->getScroll() : 0),
								m_sBorderWidth.Top + m_sPadding.Top - (getVScroll()->isEnabled() ? getVScroll()->getScroll() : 0)
							};
							client.Left += m_sPadding.Left;
							client.Top += m_sPadding.Top;
							client.Right -= m_sPadding.Right;
							client.Bottom -= m_sPadding.Bottom;
							if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
								UpdateHoveredItem(&m_cRootItem, position, current, new_element, &hovered, getFont()->getPlatformFont(getForm()->getRenderer())->getStringSize(L"Wy", getFont()->Distance).Y);
						}
					}
				}
				if (new_element != m_eHoveredElement || hovered != m_pHoveredItem)
				{
					switch (m_eHoveredElement)
					{
					case Element::VScroll:
						getVScroll()->NotifyOnMouseLeave();
						break;
					case Element::HScroll:
						getHScroll()->NotifyOnMouseLeave();
						break;
					case Element::Item:
						m_pHoveredItem->QueryService()->setHovered(false);
						break;
					default:
						break;
					}
					m_eHoveredElement = new_element;
					m_pHoveredItem = hovered;
					switch (m_eHoveredElement)
					{
					case Element::VScroll:
						getVScroll()->NotifyOnMouseHover(PointF{ position.X - getVScroll()->getPosition().X, position.Y - getVScroll()->getPosition().Y });
						break;
					case Element::HScroll:
						getHScroll()->NotifyOnMouseHover(PointF{ position.X - getHScroll()->getPosition().X, position.Y - getHScroll()->getPosition().Y });
						break;
					case Element::Item:
						m_pHoveredItem->QueryService()->setHovered(true);
						break;
					default:
						break;
					}
					return true;
				}
			}
			return false;
		}

		void CDirectoryTree::DeselectAllExceptFirst(IListItem *parent, bool &first)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				if (parent->getItem(i)->isSelected())
				{
					if (first)
						first = false;
					else
						parent->getItem(i)->setSelected(false);
				}
				DeselectAllExceptFirst(parent->getItem(i), first);
			}
		}

		void CDirectoryTree::DeselectAllExceptFirst()
		{
			m_cOwner.setIgnoreDeselect(true);
			bool first{ true };
			DeselectAllExceptFirst(&m_cRootItem, first);
			m_cOwner.setIgnoreDeselect(true);
		}

		bool CDirectoryTree::DeselectAllExceptItem(IListItem *parent, IListItem *exclude)
		{
			bool result{ false };
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				if (parent->getItem(i) != exclude && parent->getItem(i)->isSelected())
				{
					parent->getItem(i)->setSelected(false);
					result = true;
				}
				result = DeselectAllExceptItem(parent->getItem(i), exclude) || result;
			}
			return result;
		}

		void CDirectoryTree::DeactivateAllExceptItem(IListItem *parent, IListItem *exclude)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				if (parent->getItem(i) != exclude && parent->getItem(i)->isActive())
					parent->getItem(i)->setActive(false);
				DeactivateAllExceptItem(parent->getItem(i), exclude);
			}
		}

		bool CDirectoryTree::DeselectAllExceptParent(IListItem *parent, IListItem *exclude)
		{
			bool result{ false };
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				if (parent != exclude && parent->getItem(i)->isSelected())
					result = parent->getItem(i)->setSelected(false) || result;
				result = DeselectAllExceptParent(parent->getItem(i), exclude) || result;
			}
			return result;
		}

		bool CDirectoryTree::DeselectAllExceptParent(IListItem *exclude)
		{
			return DeselectAllExceptParent(&m_cRootItem, exclude);
		}

		void CDirectoryTree::UpdateItemFromStyle(IListItem *parent)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				parent->getItem(i)->QueryService()->UpdateFromStyle();
				UpdateItemFromStyle(parent->getItem(i));
			}
		}

		bool CDirectoryTree::ScrollToActiveItem(IListItem *parent, PointF &current, bool &changed)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
				if (parent->getItem(i)->isVisible())
				{
					PointF size{ parent->getItem(i)->getSize() };
					if (parent->getItem(i)->isActive())
					{
						RectF client{ getClientRect() };
						if (getHScroll()->isEnabled())
						{
							if (current.X + size.Y + size.X >= client.Right)
							{
								if (getHScroll()->setScroll(getHScroll()->getScroll() + current.X + size.Y + size.X - client.Right))
									changed = true;
							}
							else if (current.X < client.Left)
							{
								if (getHScroll()->setScroll(getHScroll()->getScroll() - client.Left + current.X))
									changed = true;
							}
						}
						if (getVScroll()->isEnabled())
						{
							if (current.Y + size.Y >= client.Bottom)
							{
								if (getVScroll()->setScroll(getVScroll()->getScroll() + current.Y + size.Y - client.Bottom))
									changed = true;
							}
							else if (current.Y < client.Top)
							{
								if (getVScroll()->setScroll(getVScroll()->getScroll() - client.Top + current.Y))
									changed = true;
							}
						}
						return true;
					}
					current.Y += size.Y;
					if (!m_aItems[FindItemIndex(parent->getItem(i))].Folded)
					{
						current.X += size.X;
						if (ScrollToActiveItem(parent->getItem(i), current, changed))
							return true;
						current.X -= size.X;
					}
				}
			return false;
		}

		IListItem *CDirectoryTree::FindActiveItem(IListItem *parent)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				if (parent->getItem(i)->isActive())
					return parent->getItem(i);
				IListItem *a{ FindActiveItem(parent->getItem(i)) };
				if (a)
					return a;
			}
			return nullptr;
		}

		String CDirectoryTree::getItemPath(IListItem *item)
		{
			String result;
			while (item && item != &m_cRootItem)
			{
				result = cast<IListItemIcon*>(item)->getCaption() + Application->System->DirectorySeparator + result;
				item = item->getParent();
			}
			return m_sRootDirectory + result;
		}

		StringArray CDirectoryTree::FindDirectories(const String &filter)
		{
			IFileSystem::SearchFilesResult list;
			StringArray result;
			if (Application->FileSystem->SearchFiles(filter, list))
				for (auto pos : list)
					if (pos.Directory && pos.Name != L"." && pos.Name != L"..")
					{
						if (!m_bShowArchieved && pos.Archieved)
							continue;
						if (!m_bShowCompressed && pos.Compressed)
							continue;
						if (!m_bShowEncrypted && pos.Encrypted)
							continue;
						if (!m_bShowHidden && pos.Hidden)
							continue;
						if (!m_bShowNormal && pos.Normal)
							continue;
						if (!m_bShowOffline && pos.Offline)
							continue;
						if (!m_bShowReadOnly && pos.Readonly)
							continue;
						if (!m_bShowSystem && pos.System)
							continue;
						if (!m_bShowTemporary && pos.Temporary)
							continue;
						result.push_back(pos.Name);
					}
			return result;
		}

		bool CDirectoryTree::Rescan()
		{
			if (m_sRootDirectory.length() > 0 && Application->FileSystem->DirectoryExists(m_sRootDirectory))
			{
				m_cRootItem.DeleteItems();
				StringArray list{ FindDirectories(m_sRootDirectory + (m_sFilter.length() > 0 ? m_sFilter : L"*")) };
				for (auto name : list)
				{
					CListItemIcon *item{ new CListItemIcon(name) };
					m_cRootItem.AddItem(item);
					StringArray subfolders{ FindDirectories(m_sRootDirectory + name + Application->System->DirectorySeparator + (m_sFilter.length() > 0 ? m_sFilter : L"*")) };
					for (auto subname : subfolders)
						item->AddItem(new CListItemIcon(subname));
				}
				Update();
				if (m_pFileList)
					m_pFileList->setDirectory(getDirectory());
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		void CDirectoryTree::Rescan(const int index)
		{
			String path{ getItemPath(m_aItems[index].Item) };
			for (int i = 0; i < m_aItems[index].Item->getItemCount(); i++)
			{
				IListItemIcon *item{ cast<IListItemIcon*>(m_aItems[index].Item->getItem(i)) };
				item->DeleteItems();
				StringArray subfolders{ FindDirectories(path + item->getCaption() + Application->System->DirectorySeparator + (m_sFilter.length() > 0 ? m_sFilter : L"*")) };
				for (auto subname : subfolders)
					item->AddItem(new CListItemIcon(subname));
			}
		}

		void CDirectoryTree::DoOnActivateItem(IListItem *item)
		{
			if (OnActivateDirectory)
				OnActivateDirectory(this, getItemPath(item));
			if (m_pFileList)
				m_pFileList->setDirectory(getDirectory());
		}

		void CDirectoryTree::DoOnDeactivateItem(IListItem *item)
		{
			if (OnDeactivateDirectory)
				OnDeactivateDirectory(this, getItemPath(item));
			if (m_pFileList)
				m_pFileList->setDirectory(getDirectory());
		}

		void CDirectoryTree::SetListItemDPI(IListItem *parent)
		{
			parent->QueryService()->setDPI(getDPI());
			for (int i = 0; i < parent->getItemCount(); i++)
				SetListItemDPI(parent->getItem(i));
		}
	#pragma endregion

	#pragma region Paint
		void CDirectoryTree::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			State state{ getState() };
			PointF disp{ DispOnCanvas(m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				SortItems();
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });
				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };
				DrawBlockShadow(renderer, rect, m_sBorderRadius, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
				DrawSimpleBackground(renderer, rect, m_sBorderWidth, m_sBorderRadius, m_aBorderColor[(int)state], m_aBackgroundColor[(int)state], m_aBackgroundGradient[(int)state]);
				RenderItems(renderer, disp, state);
				RenderScrolls(renderer, disp);
				RenderCorner(renderer, disp, state);
				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}

		void CDirectoryTree::RenderItems(IRenderer *renderer, const PointF &disp, const State state)
		{
			RectF client{ getClientRect() };
			if (!client.is_zero() && m_cRootItem.getItemCount() > 0)
			{
				PointF current{ -getHScroll()->getScroll(), -getVScroll()->getScroll() };
				ITexture *clip{ renderer->CreateTexture(ntl::Round<int>(client.width()), ntl::Round<int>(client.height()), 1, TextureFormat::RGBA, true) };
				if (clip)
				{
					renderer
						->ActivateTarget(clip)
						->Clear(Color{ 0, 0, 0, 0 });
					ITexture *folder_normal_folded{ nullptr }, *folder_hovered_folded{ nullptr }, *folder_normal{ nullptr }, *folder_hovered{ nullptr }, *clip_items{ nullptr };
					RenderItems(
						&m_cRootItem,
						renderer,
						current,
						getFont()->getPlatformFont(renderer)->getStringSize(L"Wy", getFont()->Distance).Y,
						client.height(),
						&folder_normal_folded,
						&folder_hovered_folded,
						&folder_normal,
						&folder_hovered,
						&clip_items);
					if (folder_normal_folded)
						folder_normal_folded->Release();
					if (folder_hovered_folded)
						folder_hovered_folded->Release();
					if (folder_normal)
						folder_normal->Release();
					if (folder_hovered)
						folder_hovered->Release();
					if (clip_items)
						clip_items->Release();
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivateTarget(m_pCanvas)
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(disp.X + client.Left, disp.Y + client.Top, 0));
					if (ntl::IsGreater<float>(m_sBorderRadius.Left, ntl::Min<float>(m_sBorderWidth.Left + m_sPadding.Left, m_sBorderWidth.Top + m_sPadding.Top)) ||
						ntl::IsGreater<float>(m_sBorderRadius.Top, ntl::Min<float>(m_sBorderWidth.Top + m_sPadding.Top, m_sBorderWidth.Right + m_sPadding.Right)) ||
						ntl::IsGreater<float>(m_sBorderRadius.Right, ntl::Min<float>(m_sBorderWidth.Right + m_sPadding.Right, m_sBorderWidth.Bottom + m_sPadding.Bottom)) ||
						ntl::IsGreater<float>(m_sBorderRadius.Bottom, ntl::Min<float>(m_sBorderWidth.Bottom + m_sPadding.Bottom, m_sBorderWidth.Left + m_sPadding.Left)))
					{
						Block b{
							RectF{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() },
							RectF{
								m_sBorderWidth.Left + m_sPadding.Left,
								m_sBorderWidth.Top + m_sPadding.Top,
								m_sBorderWidth.Right + m_sPadding.Right + (m_bVScrollVisible ? getVScroll()->getWidth() : 0),
								m_sBorderWidth.Bottom + m_sPadding.Bottom + (m_bHScrollVisible ? getHScroll()->getHeight() : 0),
							},
							m_sBorderRadius,
							PointLocation::Inside
						};
						CStoreBlock s_block{ renderer };
						renderer
							->ActivateBlock(&b)
							->DrawImage(clip, 1);
					}
					else
						renderer->DrawImage(clip, 1);
					clip->Release();
				}
			}
		}

		void CDirectoryTree::RenderItems(IListItem *parent, IRenderer *renderer, PointF &current, const float line_height, const float client_height, ITexture **folder_normal_folded,
			ITexture **folder_hovered_folded, ITexture **folder_normal, ITexture **folder_hovered, ITexture **clip_items)
		{
			for (int i = 0; i < parent->getItemCount(); i++)
			{
				if (parent->getItem(i)->isVisible())
				{
					PointF size{ parent->getItem(i)->getSize() };
					bool folded{ m_aItems[FindItemIndex(parent->getItem(i))].Folded };
					if (current.Y >= -size.Y)
					{
						// Folder
						if (parent->getItem(i)->getItemCount() > 0)
						{
							ITexture *folder{ RenderFolder(renderer, parent->getItem(i), folder_normal_folded, folder_hovered_folded, folder_normal, folder_hovered, folded) };
							if (folder)
							{
								PointF p{ current.X + (size.Y - folder->Widthf) / 2, current.Y + (size.Y - folder->Heightf) / 2 };
								{
									CStorePrimitiveMatrix s_matrix{ renderer };
									renderer
										->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(p.X, p.Y, 0))
										->DrawImage(folder, 1);
								}
								if (!folded && m_sFolderLinesColor.A > 0)
								{
									renderer->DrawLines({
										PointF{ current.X + size.Y / 2, current.Y + size.Y },
										PointF{ current.X + size.Y / 2, current.Y + size.Y + size.Y / 2 },
										PointF{ current.X + size.Y, current.Y + size.Y + size.Y / 2 } },
										m_sFolderLinesColor,
										false);
								}
							}
						}
						// Item
						parent->getItem(i)->QueryService()->Render(ntl::Mat4Translate<float>(std::round(current.X + size.Y), std::round(current.Y), 0), nullptr, false, clip_items);
					}
					current.Y += size.Y;
					if (parent->getItem(i)->getItemCount() > 0 && !folded)
					{
						current.X += size.Y;
						RenderItems(parent->getItem(i), renderer, current, line_height, client_height, folder_normal_folded, folder_hovered_folded, folder_normal, folder_hovered, clip_items);
						current.X -= size.Y;
					}
				}
				if (current.Y >= client_height)
					break;
			}
		}

		ITexture *CDirectoryTree::RenderFolder(IRenderer *renderer, IListItem *item, ITexture **folder_normal_folded, ITexture **folder_hovered_folded, ITexture **folder_normal,
			ITexture **folder_hovered, const bool folded)
		{
			if (ntl::IsGreater<float>(m_sFolderSize.X, 0) && ntl::IsGreater<float>(m_sFolderSize.Y, 0))
			{
				FolderState state{ (m_eHoveredElement == Element::Folder && item == m_pHoveredItem) ? FolderState::Hovered : FolderState::Normal };
				ITexture **folder{ (m_eHoveredElement == Element::Folder && item == m_pHoveredItem) ? (folded ? folder_hovered_folded : folder_hovered) : (folded ? folder_normal_folded : folder_normal) };
				if (!*folder)
				{
					*folder = renderer->CreateTexture(ntl::Round<int>(m_sFolderSize.X), ntl::Round<int>(m_sFolderSize.Y), 1, TextureFormat::RGBA, true);
					if (*folder)
					{
						CStoreTarget s_target{ renderer };
						renderer
							->ActivateTarget(*folder)
							->Clear(Color{ 0, 0, 0, 0 });
						DrawSimpleBackground(
							renderer,
							RectF{ 0, 0, m_sFolderSize.X, m_sFolderSize.Y },
							m_aFolderBorderWidth[(int)state],
							m_aFolderBorderRadius[(int)state],
							m_aFolderBorderColor[(int)state],
							m_aFolderBackgroundColor[(int)state],
							m_aFolderBackgroundGradient[(int)state]);
						if (ntl::IsGreater<float>(m_aFolderSignSize[(int)state].X, 0) && ntl::IsGreater<float>(m_aFolderSignSize[(int)state].Y, 0))
						{
							// Horizontal line
							PointF p{ (m_sFolderSize.X - m_aFolderSignSize[(int)state].X) / 2, (m_sFolderSize.Y - m_aFolderSignSize[(int)state].Y) / 2 };
							renderer->DrawRectangle(RectF{ p.X, p.Y, p.X + m_aFolderSignSize[(int)state].X, p.Y + m_aFolderSignSize[(int)state].Y }, m_aFolderSignColor[(int)state]);
							if (folded)
							{
								// Vertical line
								p = PointF{ (m_sFolderSize.X - m_aFolderSignSize[(int)state].Y) / 2, (m_sFolderSize.Y - m_aFolderSignSize[(int)state].X) / 2 };
								renderer->DrawRectangle(RectF{ p.X, p.Y, p.X + m_aFolderSignSize[(int)state].Y, p.Y + m_aFolderSignSize[(int)state].X }, m_aFolderSignColor[(int)state]);
							}
						}
					}
				}
				return *folder;
			}
			return nullptr;
		}

		void CDirectoryTree::RenderScrolls(IRenderer *renderer, const PointF &disp)
		{
			Block b{ RectF{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() }, m_sBorderWidth, m_sBorderRadius, PointLocation::Inside };
			if (m_bHScrollVisible)
				getHScroll()->Render(false, ntl::Mat4Translate<float>(m_sBorderWidth.Left + disp.X, getHeight() - m_sBorderWidth.Bottom - getHScroll()->getSize().Y + disp.Y, 0), &b);
			if (m_bVScrollVisible)
				getVScroll()->Render(false, ntl::Mat4Translate<float>(getWidth() - m_sBorderWidth.Right - getVScroll()->getSize().X + disp.X, m_sBorderWidth.Top + disp.Y, 0), &b);
		}

		void CDirectoryTree::RenderCorner(IRenderer *renderer, const PointF &disp, const State state)
		{
			if (m_bVScrollVisible && m_bHScrollVisible && m_aCornerColor[(int)state].A > 0)
			{
				Block b{ RectF{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() }, m_sBorderWidth, m_sBorderRadius, PointLocation::Inside };
				RectF r{
					getWidth() - m_sBorderWidth.Right - getVScroll()->getSize().X + disp.X,
					getHeight() - m_sBorderWidth.Bottom - getHScroll()->getSize().Y + disp.Y,
					getWidth() - m_sBorderWidth.Right + disp.X,
					getHeight() - m_sBorderWidth.Bottom + disp.Y };
				CStoreBlock s_block{ renderer };
				renderer
					->ActivateBlock(&b)
					->DrawRectangle(r, m_aCornerColor[(int)state]);
			}
		}
	#pragma endregion
	}
}
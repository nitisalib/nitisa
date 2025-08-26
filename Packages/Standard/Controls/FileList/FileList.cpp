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
	#pragma region CGradientListener
		CFileList::CGradientListener::CGradientListener(CFileList *control) :
			m_pControl{ control }
		{

		}

		void CFileList::CGradientListener::NotifyOnChange()
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
		CFileList::CFileList() :
			CControl(L"FileList", true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_bShowArchieved{ true },
			m_bShowCompressed{ true },
			m_bShowEncrypted{ true },
			m_bShowHidden{ false },
			m_bShowNormal{ true },
			m_bShowOffline{ false },
			m_bShowReadOnly{ true },
			m_bShowSystem{ true },
			m_bShowTemporary{ false },
			m_iActiveIndex{ -1 },
			m_sBorderWidth{ 1, 1, 1, 1 },
			m_sBorderRadius{ 0, 0, 0, 0 },
			m_sPadding{ 1, 1, 1, 1 },
			m_fSearchResetInterval{ 2 },
			m_eHorizontalScrollBar{ ScrollVisibility::Auto },
			m_eVerticalScrollBar{ ScrollVisibility::Auto },
			m_iColumns{ 1 },
			m_bMultiselect{ true },
			m_fScrollInterval{ 0.3f },
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
			m_aCornerColor{
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 } },
			m_pHScroll{ nullptr },
			m_pVScroll{ nullptr },
			m_bIgnoreGradient{ false },
			m_cOwner{ this },
			m_eHoveredElement{ Element::None },
			m_eDownElement{ Element::None },
			m_sLastSearch{ std::chrono::steady_clock::now() },
			m_sGrid{ 0, 0 },
			m_sItemSize{ 0, 0 },
			m_bHScroll{ false },
			m_bVScroll{ false },
			m_iDownIndex{ -1 },
			m_pDownItem{ nullptr },
			m_iLockUpdate{ 0 },
			m_bUpdateRequired{ false },
			m_pCanvas{ nullptr },
			m_cScrollListener{ this },
			OnActivate{ nullptr },
			OnDeactivate{ nullptr },
			OnSelect{ nullptr },
			OnDeselect{ nullptr }
		{
			if (Application->System->Platform == PlatformType::Windows)
				m_sDirectory = L"C:\\";
			setService(new CFileListService(this), true);
			setSize(PointF{ 121, 97 });
			Rescan();
		}

		CFileList::CFileList(IForm *parent) :CFileList()
		{
			setForm(parent);
		}

		CFileList::CFileList(IControl *parent) : CFileList()
		{
			setParent(parent);
		}

		CFileList::~CFileList()
		{
			if (m_pHScroll)
				m_pHScroll->Release();
			if (m_pVScroll)
				m_pVScroll->Release();
		}

		void CFileList::BeforeRelease()
		{
			DeleteItems();
			CControl::BeforeRelease();
		}
	#pragma endregion

	#pragma region Interface getters
		RectF CFileList::getClientRect()
		{
			RectF result{
				m_sBorderWidth.Left + m_sPadding.Left,
				m_sBorderWidth.Top + m_sPadding.Top,
				getWidth() - m_sBorderWidth.Right - m_sPadding.Right,
				getHeight() - m_sBorderWidth.Bottom - m_sPadding.Bottom
			};
			result.validate();
			return result;
		}

		RectF CFileList::getRenderRect()
		{
			RectF result{ getRenderRect(State::Normal) };
			for (int i = 1; i <= (int)State::Disabled; i++)
				result += getRenderRect((State)i);
			return result;
		}

		String CFileList::getDirectory()
		{
			return m_sDirectory;
		}

		String CFileList::getFilter()
		{
			return m_sFilter;
		}

		bool CFileList::isShowArchieved()
		{
			return m_bShowArchieved;
		}

		bool CFileList::isShowCompressed()
		{
			return m_bShowCompressed;
		}

		bool CFileList::isShowEncrypted()
		{
			return m_bShowEncrypted;
		}

		bool CFileList::isShowHidden()
		{
			return m_bShowHidden;
		}

		bool CFileList::isShowNormal()
		{
			return m_bShowNormal;
		}

		bool CFileList::isShowOffline()
		{
			return m_bShowOffline;
		}

		bool CFileList::isShowReadOnly()
		{
			return m_bShowReadOnly;
		}

		bool CFileList::isShowSystem()
		{
			return m_bShowSystem;
		}

		bool CFileList::isShowTemporary()
		{
			return m_bShowTemporary;
		}

		String CFileList::getActiveFile()
		{
			if (m_iActiveIndex >= 0)
				return cast<IListItemLabel*>(m_aItems[m_iActiveIndex])->getCaption();
			return L"";
		}

		int CFileList::getFileCount()
		{
			return (int)m_aItems.size();
		}

		String CFileList::getFile(const int index)
		{
			if (index >= 0 && index < (int)m_aItems.size())
				return m_aItems[index]->getCaption();
			return L"";
		}

		bool CFileList::isFileSelected(const int index)
		{
			if (index >= 0 && index < (int)m_aItems.size())
				return m_aItems[index]->isSelected();
			return false;
		}
	#pragma endregion

	#pragma region Interface setters
		bool CFileList::setDPI(const Point &value)
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
				Update();
				return true;
			}
			return false;
		}

		bool CFileList::setDirectory(const String &value)
		{
			String v{ value };
			if (v.length() > 0 && v[v.length() - 1] != Application->System->DirectorySeparator)
				v += Application->System->DirectorySeparator;
			if (v.length() > 0 && v != m_sDirectory)
			{
				m_sDirectory = v;
				Rescan();
				return true;
			}
			return false;
		}

		bool CFileList::setFilter(const String &value)
		{
			if (value != m_sFilter)
			{
				m_sFilter = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CFileList::setShowArchieved(const bool value)
		{
			if (value != m_bShowArchieved)
			{
				m_bShowArchieved = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CFileList::setShowCompressed(const bool value)
		{
			if (value != m_bShowCompressed)
			{
				m_bShowCompressed = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CFileList::setShowEncrypted(const bool value)
		{
			if (value != m_bShowEncrypted)
			{
				m_bShowEncrypted = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CFileList::setShowHidden(const bool value)
		{
			if (value != m_bShowHidden)
			{
				m_bShowHidden = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CFileList::setShowNormal(const bool value)
		{
			if (value != m_bShowNormal)
			{
				m_bShowNormal = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CFileList::setShowOffline(const bool value)
		{
			if (value != m_bShowOffline)
			{
				m_bShowOffline = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CFileList::setShowReadOnly(const bool value)
		{
			if (value != m_bShowReadOnly)
			{
				m_bShowReadOnly = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CFileList::setShowSystem(const bool value)
		{
			if (value != m_bShowSystem)
			{
				m_bShowSystem = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CFileList::setShowTemporary(const bool value)
		{
			if (value != m_bShowTemporary)
			{
				m_bShowTemporary = value;
				Rescan();
				return true;
			}
			return false;
		}

		bool CFileList::setFileSelected(const int index, const bool value)
		{
			if (index >= 0 && index < (int)m_aItems.size() && m_aItems[index]->isSelected() != value)
				return m_aItems[index]->setSelected(value);
			return false;
		}
	#pragma endregion

	#pragma region Getters
		CFileList::State CFileList::getState()
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

		int CFileList::getActiveIndex()
		{
			return m_iActiveIndex;
		}

		RectF CFileList::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		RectF CFileList::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		RectF CFileList::getPadding() const
		{
			return m_sPadding;
		}

		float CFileList::getSearchResetInterval() const
		{
			return m_fSearchResetInterval;
		}

		ScrollVisibility CFileList::getHorizontalScrollBar() const
		{
			return m_eHorizontalScrollBar;
		}

		ScrollVisibility CFileList::getVerticalScrollBar() const
		{
			return m_eVerticalScrollBar;
		}

		int CFileList::getColumns() const
		{
			return m_iColumns;
		}

		bool CFileList::isMultiselect() const
		{
			return m_bMultiselect;
		}

		float CFileList::getScrollInterval() const
		{
			return m_fScrollInterval;
		}

		Color CFileList::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		PointF CFileList::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		int CFileList::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		BorderColor CFileList::getBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CFileList::getLeftBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Left;
		}

		Color CFileList::getTopBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Top;
		}

		Color CFileList::getRightBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Right;
		}

		Color CFileList::getBottomBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state].Bottom;
		}

		Color CFileList::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CFileList::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		Color CFileList::getCornerColor(const State state) const
		{
			return m_aCornerColor[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CFileList::setHScroll(IBuiltInScroll *value)
		{
			if (value && value != m_pHScroll)
			{
				value->setListener(&m_cScrollListener);
				value->NotifyOnFreeResources();
				if (value->isVertical())
				{
					CScroll *scroll{ cast<CScroll*>(value) };
					if (scroll)
						scroll->SwitchDirection(true);
					else
						value->setVertical(false);
				}
				value->setMin(0);
				if (m_pHScroll)
					m_pHScroll->Release();
				m_pHScroll = value;
				Update();
				return true;
			}
			return false;
		}

		bool CFileList::setVScroll(IBuiltInScroll *value)
		{
			if (value && value != m_pVScroll)
			{
				value->setListener(&m_cScrollListener);
				value->NotifyOnFreeResources();
				if (!value->isVertical())
				{
					CScroll *scroll{ cast<CScroll*>(value) };
					if (scroll)
						scroll->SwitchDirection(true);
					else
						value->setVertical(true);
				}
				value->setMin(0);
				if (m_pVScroll)
					m_pVScroll->Release();
				m_pVScroll = value;
				Update();
				return true;
			}
			return false;
		}

		bool CFileList::setActiveIndex(const int value)
		{
			if (value < 0 && m_iActiveIndex < 0)
				return false;
			if (value < (int)m_aItems.size() && value != m_iActiveIndex)
			{
				CLockRepaint lock{ this };
				if (m_iActiveIndex >= 0)
					m_aItems[m_iActiveIndex]->setActive(false);
				m_iActiveIndex = value >= 0 ? value : -1;
				if (m_iActiveIndex >= 0)
					m_aItems[m_iActiveIndex]->setActive(true);
				return true;
			}
			return false;
		}

		bool CFileList::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				m_sBorderWidth = value;
				Update();
				return true;
			}
			return false;
		}

		bool CFileList::setBorderRadius(const RectF &value)
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

		bool CFileList::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				m_sPadding = value;
				Update();
				return true;
			}
			return false;
		}

		bool CFileList::setSearchResetInterval(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fSearchResetInterval))
			{
				m_fSearchResetInterval = value;
				return true;
			}
			return false;
		}

		bool CFileList::setHorizontalScrollBar(const ScrollVisibility value)
		{
			if (value != m_eHorizontalScrollBar)
			{
				m_eHorizontalScrollBar = value;
				Update();
				return true;
			}
			return false;
		}

		bool CFileList::setVerticalScrollBar(const ScrollVisibility value)
		{
			if (value != m_eVerticalScrollBar)
			{
				m_eVerticalScrollBar = value;
				Update();
				return true;
			}
			return false;
		}

		bool CFileList::setColumns(const int value)
		{
			if (value >= 1 && value != m_iColumns)
			{
				m_iColumns = value;
				Update();
				return true;
			}
			return false;
		}

		bool CFileList::setMultiselect(const bool value)
		{
			if (value != m_bMultiselect)
			{
				m_bMultiselect = value;
				if (!m_bMultiselect)
				{
					CLockRepaint lock{ this };
					int found{ 0 };
					m_cOwner.setIgnoreSelect(true);
					for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
						if ((*pos)->isSelected() && found++ >= 1)
							(*pos)->setSelected(false);
					m_cOwner.setIgnoreSelect(false);
					if (found > 1)
					{
						if (m_pCanvas)
							m_pCanvas->setValid(false);
						Repaint(false);
					}
				}
				return true;
			}
			return false;
		}

		bool CFileList::setScrollInterval(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollInterval))
			{
				m_fScrollInterval = value;
				if (getForm())
				{
					CFileListService *service{ cast<CFileListService*>(QueryService()) };
					if (service->m_hTimer)
						getForm()->ResetTimer(service->m_hTimer, m_fScrollInterval);
				}
				return true;
			}
			return false;
		}

		bool CFileList::setShadowColor(const State state, const Color &value)
		{
			if (value != m_aShadowColor[(int)state])
			{
				m_aShadowColor[(int)state] = value;
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

		bool CFileList::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
					Repaint(false);
				m_aShadowShift[(int)state] = value;
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFileList::setShadowRadius(const State state, const int value)
		{
			if (value >= 1 && value != m_aShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
					Repaint(false);
				m_aShadowRadius[(int)state] = value;
				if (m_aShadowColor[(int)state].A > 0 && getState() == state)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFileList::setBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aBorderColor[(int)state])
			{
				m_aBorderColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CFileList::setLeftBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ value, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CFileList::setTopBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, value, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CFileList::setRightBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, value, m_aBorderColor[(int)state].Bottom });
		}

		bool CFileList::setBottomBorderColor(const State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, value });
		}

		bool CFileList::setBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aBackgroundColor[(int)state])
			{
				m_aBackgroundColor[(int)state] = value;
				if (getState() == state && m_aBackgroundGradient[(int)state].getPointCount() < 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CFileList::setCornerColor(const State state, const Color &value)
		{
			if (value != m_aCornerColor[(int)state])
			{
				m_aCornerColor[(int)state] = value;
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
	#pragma endregion

	#pragma region Items
		int CFileList::getItemIndex(IListItem *item)
		{
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				if (*pos == item)
					return int(pos - m_aItems.begin());
			return -1;
		}

		IListItem *CFileList::getActiveItem()
		{
			if (m_iActiveIndex >= 0)
				return m_aItems[m_iActiveIndex];
			return nullptr;
		}

		bool CFileList::DeleteItems()
		{
			if (m_aItems.size() > 0)
			{
				for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
					(*pos)->Release();
				m_aItems.clear();
				m_iActiveIndex = -1;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CFileList::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			getVScroll()->Refresh();
			getHScroll()->Refresh();
		}

		IBuiltInScroll *CFileList::getHScroll()
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

		IBuiltInScroll *CFileList::getVScroll()
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

		RectF CFileList::getRenderRect(const State state)
		{
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
		}

		IListItem *CFileList::getItemAtPoint(const PointF &position)
		{
			if (m_aItems.size() > 0)
			{
				RectF client{ getRealClientRect() };
				if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
				{
					Point p{ getGridCell(client, position) };
					if (p.X >= 0 && p.X < m_sGrid.X && p.Y >= 0 && p.Y < m_sGrid.Y)
					{
						int index{ p.Y * m_sGrid.X + p.X };
						if (index >= 0 && index < (int)m_aItems.size())
							return m_aItems[index];
					}
				}
			}
			return nullptr;
		}

		Point CFileList::getGridCell(const PointF &position)
		{
			if (m_aItems.size() > 0)
				return getGridCell(getRealClientRect(), position);
			return Point{ 0, 0 };
		}

		Point CFileList::getGridCell(const RectF &client, const PointF &position)
		{
			if (m_aItems.size() > 0)
			{
				PointF p{ position.X - client.Left + (getHScroll()->isEnabled() ? getHScroll()->getScroll() : 0), position.Y - client.Top + (getVScroll()->isEnabled() ? getVScroll()->getScroll() : 0) };
				return Point{ int(p.X / m_sItemSize.X), int(p.Y / m_sItemSize.Y) };
			}
			return{ 0, 0 };
		}

		RectF CFileList::getRealClientRect()
		{
			RectF client{ getClientRect() };
			if (m_bVScroll)
				client.Right -= getVScroll()->getSize().X;
			if (m_bHScroll)
				client.Bottom -= getHScroll()->getSize().Y;
			client.validate();
			return client;
		}

		Point CFileList::IndexToGrid(const int value)
		{
			return Point{ value % m_iColumns, int(value / m_iColumns) };
		}

		int CFileList::GridToIndex(const Point &value)
		{
			return value.Y * m_iColumns + value.X;
		}

		bool CFileList::ScrollToActiveItem()
		{
			if (m_iActiveIndex >= 0)
				return ScrollToItem(m_iActiveIndex);
			return false;
		}

		bool CFileList::ScrollToItem(const int index)
		{
			bool result{ false };
			RectF client{ getRealClientRect() };
			if (!client.is_empty())
			{
				// Item coords in control coordinates
				PointF pos1{ m_aItems[index]->getPosition() }, pos{ pos1 };
				if (getVScroll()->isEnabled())
					pos.Y -= getVScroll()->getScroll();
				if (getHScroll()->isEnabled())
					pos.X -= getHScroll()->getScroll();
				// HScroll
				if (getHScroll()->isEnabled())
				{
					if (pos.X + m_sItemSize.X > client.Right)
					{
						result = getHScroll()->setScroll(getHScroll()->getScroll() + pos.X + m_sItemSize.X - client.Right) || result;
						pos.X = pos1.X - getHScroll()->getScroll();
					}
					if (pos.X < client.Left)
						result = getHScroll()->setScroll(getHScroll()->getScroll() - client.Left + pos.X) || result;
				}
				// VScroll
				if (getVScroll()->isEnabled())
				{
					if (pos.Y < client.Top)
						result = getVScroll()->setScroll(getVScroll()->getScroll() - client.Top + pos.Y) || result;
					else if (pos.Y + m_sItemSize.Y > client.Bottom)
						result = getVScroll()->setScroll(getVScroll()->getScroll() + pos.Y + m_sItemSize.Y - client.Bottom) || result;
				}
			}
			return result;
		}

		void CFileList::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".BorderWidth", m_sBorderWidth);
			style->getOption(m_sClassName + L".BorderRadius", m_sBorderRadius);
			style->getOption(m_sClassName + L".Padding", m_sPadding);
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				String state;
				switch ((State)i)
				{
				case State::Hovered:
					state = L"Hovered";
					break;
				case State::Focused:
					state = L"Focused";
					break;
				case State::FocusedHovered:
					state = L"FocusedHovered";
					break;
				case State::Disabled:
					state = L"Disabled";
					break;
				default:
					state = L"Normal";
				}
				style->getOption(m_sClassName + L".ShadowColor[" + state + L"]", m_aShadowColor[i]);
				style->getOption(m_sClassName + L".ShadowShift[" + state + L"]", m_aShadowShift[i]);
				style->getOption(m_sClassName + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i]);
				style->getOption(m_sClassName + L".BorderColor[" + state + L"]", m_aBorderColor[i]);
				style->getOption(m_sClassName + L".BackgroundColor[" + state + L"]", m_aBackgroundColor[i]);
				style->getOption(m_sClassName + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]);
				style->getOption(m_sClassName + L".CornerColor[" + state + L"]", m_aCornerColor[i]);
			}
			getHScroll()->UpdateFromStyle(style, m_sClassName + L".Scroll");
			getVScroll()->UpdateFromStyle(style, m_sClassName + L".Scroll");
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				(*pos)->QueryService()->UpdateFromStyle();
			UpdateList();
			UpdateHoveredItem();
			m_bIgnoreGradient = false;
		}

		void CFileList::UpdateList()
		{
			// Item sizes
			m_sItemSize = PointF{ 0, 0 };
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
			{
				PointF size{ (*pos)->QueryService()->getRequiredSize() };
				m_sItemSize.X = ntl::Max<float>(m_sItemSize.X, size.X);
				m_sItemSize.Y = ntl::Max<float>(m_sItemSize.Y, size.Y);
			}
			// Grid
			if (m_aItems.size() > 0)
			{
				m_sGrid.X = ntl::Min<int>((int)m_aItems.size(), m_iColumns);
				m_sGrid.Y = (int)m_aItems.size() / m_iColumns;
				if ((int)m_aItems.size() % m_iColumns > 0)
					m_sGrid.Y++;
			}
			else
				m_sGrid = Point{ 0, 0 };
			// HScroll visibility
			RectF client{ getClientRect() };
			PointF grid_size{ (float)m_sGrid.X * m_sItemSize.X, (float)m_sGrid.Y * m_sItemSize.Y };
			switch (m_eHorizontalScrollBar)
			{
			case ScrollVisibility::None:
				m_bHScroll = false; // HScroll is never visible
				break;
			case ScrollVisibility::Visible:
				m_bHScroll = true; // HScroll is always visible
				break;
			default:
				if (ntl::IsGreater<float>(grid_size.X, client.width())) // Items width is greater then client area max width
					m_bHScroll = true;
				else if (ntl::IsLessOrEqual<float>(grid_size.X, client.width() - getVScroll()->getSize().X)) // Items width is less than client area min width
					m_bHScroll = false;
				else // HScroll visibility depends on VScroll visibility
					switch (m_eVerticalScrollBar)
					{
					case ScrollVisibility::None:
						m_bHScroll = false; // VScroll is invisible, so HScroll is invisible too
						break;
					case ScrollVisibility::Visible:
						m_bHScroll = true; // VScroll is visible, so HScroll is visible too
						break;
					default:
						m_bHScroll = ntl::IsGreater<float>(grid_size.Y, client.height()); // HScroll is visible only if items height is greater than client area max height
					}
			}
			// VScroll visibility
			switch (m_eVerticalScrollBar)
			{
			case ScrollVisibility::None:
				m_bVScroll = false; // VScroll is never visible
				break;
			case ScrollVisibility::Visible:
				m_bVScroll = true; // VScroll is always visible
				break;
			default:
				if (ntl::IsGreater<float>(grid_size.Y, client.height())) // Items height is greater than client area max height
					m_bVScroll = true;
				else if (ntl::IsLessOrEqual<float>(grid_size.Y, client.height() - getHScroll()->getSize().Y)) // Items height is less than client area min height
					m_bVScroll = false;
				else // Items height is somewhere between min and max client area height, so VScroll is visible only if HScroll is visible
					m_bVScroll = m_bHScroll;
			}
			// New client rect(without scrolls)
			RectF new_client{ client };
			if (m_bHScroll)
				new_client.Bottom -= getHScroll()->getSize().Y;
			if (m_bVScroll)
				new_client.Right -= getVScroll()->getSize().X;
			new_client.validate();
			// Scroll's params
			getHScroll()->setEnabled(ntl::IsGreater<float>(grid_size.X, new_client.width()));
			getVScroll()->setEnabled(ntl::IsGreater<float>(grid_size.Y, new_client.height()));
			if (getHScroll()->isEnabled())
				getHScroll()->setMax(grid_size.X - new_client.width());
			if (getVScroll()->isEnabled())
				getVScroll()->setMax(grid_size.Y - new_client.height());
			if (m_bHScroll)
				getHScroll()->setSize(PointF{ getWidth() - m_sBorderWidth.Left - m_sBorderWidth.Right - (m_bVScroll ? getVScroll()->getSize().X : 0), getHScroll()->getSize().Y });
			if (m_bVScroll)
				getVScroll()->setSize(PointF{ getVScroll()->getSize().X, getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom - (m_bHScroll ? getHScroll()->getSize().Y : 0) });
			// Adjust enabled state depending on control enabled state
			if (!isEnabled(false))
			{
				getHScroll()->setEnabled(false);
				getVScroll()->setEnabled(false);
			}
			// Adjust item width
			if (ntl::IsGreater<float>(new_client.width() / (float)m_iColumns, m_sItemSize.X))
				m_sItemSize.X = new_client.width() / (float)m_iColumns;
			// Set item sizes
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				(*pos)->QueryService()->setSize(m_sItemSize);
			// Set item positions
			int index{ 0 };
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++, index++)
				(*pos)->QueryService()->setPosition(PointF{ m_sBorderWidth.Left + m_sPadding.Left + float(index % m_iColumns) * m_sItemSize.X,
					m_sBorderWidth.Top + m_sPadding.Top + float(index / m_iColumns) * m_sItemSize.Y });
		}

		bool CFileList::UpdateHoveredItem()
		{
			if (getForm())
				return UpdateHoveredItem(FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())));
			return false;
		}

		bool CFileList::UpdateHoveredItem(const PointF &position)
		{
			IListItem *hovered{ getItemAtPoint(position) };
			bool result{ false };
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				if (*pos == hovered)
				{
					if (!hovered->isHovered())
					{
						hovered->QueryService()->setHovered(true);
						result = true;
					}
				}
				else if ((*pos)->isHovered())
				{
					(*pos)->QueryService()->setHovered(false);
					result = true;
				}
			return result;
		}

		void CFileList::Update()
		{
			if (m_iLockUpdate == 0)
			{
				UpdateList();
				UpdateHoveredItem();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			else
				m_bUpdateRequired = true;
		}

		int CFileList::Search(const String &search)
		{
			for (auto pos = m_aItems.begin(); pos != m_aItems.end(); pos++)
				if (ToLower((*pos)->getCaption()).find(search, 0) == 0)
					return int(pos - m_aItems.begin());
			return -1;
		}

		void CFileList::LockUpdate()
		{
			m_iLockUpdate++;
		}

		void CFileList::UnlockUpdate()
		{
			if (m_iLockUpdate > 0)
				if (--m_iLockUpdate == 0 && m_bUpdateRequired)
				{
					UpdateList();
					UpdateHoveredItem();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
		}

		CFileList::Element CFileList::getElement(const PointF &position)
		{
			if (position.X >= 0 && position.X < getWidth() && position.Y >= 0 && position.Y < getHeight())
			{
				if (m_bHScroll)
				{
					RectF client{ m_sBorderWidth.Left, getHeight() - m_sBorderWidth.Bottom - getHScroll()->getSize().Y, m_sBorderWidth.Left + getHScroll()->getSize().X, getHeight() - m_sBorderWidth.Bottom };
					if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
						return Element::HScroll;
				}
				if (m_bVScroll)
				{
					RectF client{ getWidth() - m_sBorderWidth.Right - getVScroll()->getSize().X, m_sBorderWidth.Top, getWidth() - m_sBorderWidth.Right, m_sBorderWidth.Top + getVScroll()->getSize().Y };
					if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
						return Element::VScroll;
				}
				RectF client{ getRealClientRect() };
				if (position.X >= client.Left && position.X < client.Right && position.Y >= client.Top && position.Y < client.Bottom)
					return Element::List;
			}
			return Element::None;
		}

		StringArray CFileList::FindFiles(const String &filter)
		{
			IFileSystem::SearchFilesResult list;
			StringArray result;
			if (Application->FileSystem->SearchFiles(filter, list))
				for (auto pos : list)
					if (!pos.Directory)
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

		bool CFileList::Rescan()
		{
			if (m_sDirectory.length() > 0 && Application->FileSystem->DirectoryExists(m_sDirectory))
			{
				DeleteItems();
				StringArray list{ FindFiles(m_sDirectory + (m_sFilter.length() > 0 ? m_sFilter : L"*")) };
				for (auto name : list)
				{
					CFileListItem *item{ new CFileListItem(name) };
					item->QueryService()->setOwner(&m_cOwner);
					m_aItems.push_back(item);
				}
				Update();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Paint
		void CFileList::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			State state{ getState() };
			PointF disp{ DispOnCanvas(m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };
				DrawBlockShadow(renderer, rect, m_sBorderRadius, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
				DrawSimpleBackground(renderer, rect, m_sBorderWidth, m_sBorderRadius, m_aBorderColor[(int)state], m_aBackgroundColor[(int)state], m_aBackgroundGradient[(int)state]);
				RenderItems(renderer, disp, rect);
				RenderScrolls(renderer, rect, disp);
				RenderCorner(renderer, state, rect, disp);

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}

		void CFileList::RenderItems(IRenderer *renderer, const PointF &disp, const RectF &rect)
		{
			if (m_aItems.size() > 0)
			{
				PointF p;
				RectF client{ getRealClientRect() };
				client += disp;
				RectF client_in_grid{ 0, 0, client.width(), client.height() };
				if (getHScroll()->isEnabled())
				{
					client_in_grid.Left += getHScroll()->getScroll();
					client_in_grid.Right += getHScroll()->getScroll();
				}
				if (getVScroll()->isEnabled())
				{
					client_in_grid.Top += getVScroll()->getScroll();
					client_in_grid.Bottom += getVScroll()->getScroll();
				}
				int
					x1{ ntl::Min<int>(m_sGrid.X - 1, ntl::Max<int>(0, int(client_in_grid.Left / m_sItemSize.X))) },
					x2{ ntl::Min<int>(m_sGrid.X - 1, ntl::Max<int>(0, int(client_in_grid.Right / m_sItemSize.X))) },
					y1{ ntl::Min<int>(m_sGrid.Y - 1, ntl::Max<int>(0, int(client_in_grid.Top / m_sItemSize.Y))) },
					y2{ ntl::Min<int>(m_sGrid.Y - 1, ntl::Max<int>(0, int(client_in_grid.Bottom / m_sItemSize.Y))) };
				Block b{ rect, RectF{ client.Left - rect.Left, client.Top - rect.Top, rect.Right - client.Right, rect.Bottom - client.Bottom }, m_sBorderRadius, PointLocation::Inside };
				ITexture *clip{ nullptr };
				for (int y = y1; y <= y2; y++)
					for (int x = x1; x <= x2; x++)
					{
						int index{ y * m_iColumns + x };
						if (index < (int)m_aItems.size())
						{
							p.X = m_aItems[index]->getPosition().X - (getHScroll()->isEnabled() ? getHScroll()->getScroll() : 0);
							p.Y = m_aItems[index]->getPosition().Y - (getVScroll()->isEnabled() ? getVScroll()->getScroll() : 0);
							m_aItems[index]->QueryService()->Render(ntl::Mat4Translate<float>(std::round(p.X + disp.X), std::round(p.Y + disp.Y), 0), &b, false, &clip);
						}
					}
				if (clip)
					clip->Release();
			}
		}

		void CFileList::RenderScrolls(IRenderer *renderer, const RectF &rect, const PointF &disp)
		{
			Block b{ rect, m_sBorderWidth, m_sBorderRadius, PointLocation::Inside };
			if (m_bHScroll)
				getHScroll()->Render(false, ntl::Mat4Translate<float>(m_sBorderWidth.Left + disp.X, getHeight() - m_sBorderWidth.Bottom - getHScroll()->getSize().Y + disp.Y, 0), &b);
			if (m_bVScroll)
				getVScroll()->Render(false, ntl::Mat4Translate<float>(getWidth() - m_sBorderWidth.Right - getVScroll()->getSize().X + disp.X, m_sBorderWidth.Top + disp.Y, 0), &b);
		}

		void CFileList::RenderCorner(IRenderer *renderer, const State state, const RectF &rect, const PointF &disp)
		{
			if (m_bVScroll && m_bHScroll && m_aCornerColor[(int)state].A > 0)
			{
				Block b{ rect, m_sBorderWidth, m_sBorderRadius, PointLocation::Inside };
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
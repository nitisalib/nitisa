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
	namespace ide
	{
	#pragma region Constructor & destructor
		CFormEditorService::CFormEditorService(CFormEditor *editor) :
			CControlService(editor),
			m_pEditor{ editor }
		{

		}
	#pragma endregion

	#pragma region Helpers
		void CFormEditorService::AttachControl(IControl *control)
		{
			IEditor *editor{ Application->Editor };
			m_pEditor->m_aControls.push_back({ control, false });
			if (editor && editor->getControl(control)->isDisplayIcon())
			{
				PointF p{ m_pEditor->FormToLocal(control->LocalToForm(PointF{ control->getTransform()->getTx(), control->getTransform()->getTy() })) };
				m_pEditor->m_aComponents.push_back({ nullptr, control, p });
			}
			for (int i = 0; i < control->getControlCount(); i++)
				AttachControl(control->getControl(i));
		}

		bool CFormEditorService::RemoveInvalidControls()
		{
			bool result{ false };
			{
				auto pos{ m_pEditor->m_aControls.begin() };
				while (pos != m_pEditor->m_aControls.end())
					if (!m_pEditor->hasChild(pos->Control))
					{
						if (pos->Selected && m_pEditor->OnDeselectControl)
							m_pEditor->OnDeselectControl(m_pEditor, pos->Control);
						pos = m_pEditor->m_aControls.erase(pos);
						result = true;
					}
					else
						pos++;
			}
			{
				auto pos{ m_pEditor->m_aComponents.begin() };
				while (pos != m_pEditor->m_aComponents.end())
					if (!pos->Component && !m_pEditor->hasChild(pos->Control))
					{
						pos = m_pEditor->m_aComponents.erase(pos);
						result = true;
					}
					else
						pos++;
			}
			return result;
		}

		void CFormEditorService::MouseDownCancel(const bool check_capture, const PointF &position)
		{
			m_pEditor->m_bMouseDown = false;
			bool changed{ m_pEditor->m_eOperation == CFormEditor::Part::Select };
			if (m_pEditor->m_eOperation == CFormEditor::Part::Select) // Send notifications about select/deselect component/control cause this notification isn't sent during mouse moving
			{
				for (auto pos = m_pEditor->m_aComponents.begin(); pos != m_pEditor->m_aComponents.end(); pos++)
					if (pos->Selected != pos->DownSelected)
					{
						if (pos->Component)
						{
							if (pos->Selected)
							{
								if (m_pEditor->OnSelectComponent)
									m_pEditor->OnSelectComponent(m_pEditor, pos->Component);
							}
							else
							{
								if (m_pEditor->OnDeselectComponent)
									m_pEditor->OnDeselectComponent(m_pEditor, pos->Component);
							}
						}
						else
						{
							if (pos->Selected)
							{
								if (m_pEditor->OnSelectControl)
									m_pEditor->OnSelectControl(m_pEditor, pos->Control);
							}
							else
							{
								if (m_pEditor->OnDeselectControl)
									m_pEditor->OnDeselectControl(m_pEditor, pos->Control);
							}
							for (auto &pos1 : m_pEditor->m_aControls)
								if (pos1.Control == pos->Control)
								{
									pos1.Selected = pos->Selected;
									break;
								}
						}
					}
				for (auto pos = m_pEditor->m_aControls.begin(); pos != m_pEditor->m_aControls.end(); pos++)
					if (pos->Selected != pos->DownSelected)
					{
						if (pos->Selected)
						{
							if (m_pEditor->OnSelectControl)
								m_pEditor->OnSelectControl(m_pEditor, pos->Control);
						}
						else
						{
							if (m_pEditor->OnDeselectControl)
								m_pEditor->OnDeselectControl(m_pEditor, pos->Control);
						}
						for (auto &pos1 : m_pEditor->m_aComponents)
							if (pos1.Control == pos->Control)
							{
								pos1.Selected = pos->Selected;
								break;
							}
					}
			}
			m_pEditor->m_eOperation = CFormEditor::Part::None;
			changed = m_pEditor->UpdateHoveredPart(position) || changed;
			changed = DeselectChildControls() || changed;
			if (changed)
				m_pEditor->Repaint(false);
			if (check_capture && m_pEditor->isCaptureMouse())
				m_pEditor->getForm()->ReleaseCaptureMouse();
		}

		void CFormEditorService::MouseDown(const MessageMouse &m)
		{
			bool pr{ false };
			if (m_pEditor->OnMouseDown && !m_pEditor->m_bMouseDown)
				m_pEditor->OnMouseDown(m_pEditor, m, pr);
			if (!m_pEditor->m_bMouseDown && !m.Middle && !m.Right && !pr)
			{
				// First, if only one control is selected and mouse over any transform control element, use it
				if (m_pEditor->m_eHoveredPart != CFormEditor::Part::None)
				{
					m_pEditor->m_eOperation = m_pEditor->m_eHoveredPart;
					m_pEditor->m_bMouseDown = true;
				}
				else
				{
					// Second, find component under the cursor and select/deselect
					int index{ m_pEditor->getComponent(m.Position) };
					if (index >= 0)
					{
						if (m.Shift && !m.Ctrl)
						{
							m_pEditor->m_aComponents[index].Selected = !m_pEditor->m_aComponents[index].Selected;
							if (m_pEditor->m_aComponents[index].Component)
							{
								if (m_pEditor->m_aComponents[index].Selected && m_pEditor->OnSelectComponent)
									m_pEditor->OnSelectComponent(m_pEditor, m_pEditor->m_aComponents[index].Component);
								else if (!m_pEditor->m_aComponents[index].Selected && m_pEditor->OnDeselectComponent)
									m_pEditor->OnDeselectComponent(m_pEditor, m_pEditor->m_aComponents[index].Component);
							}
							else
							{
								if (m_pEditor->m_aComponents[index].Selected && m_pEditor->OnSelectControl)
									m_pEditor->OnSelectControl(m_pEditor, m_pEditor->m_aComponents[index].Control);
								else if (!m_pEditor->m_aComponents[index].Selected && m_pEditor->OnDeselectControl)
									m_pEditor->OnDeselectControl(m_pEditor, m_pEditor->m_aComponents[index].Control);
								for (auto &pos : m_pEditor->m_aControls)
									if (pos.Control == m_pEditor->m_aComponents[index].Control)
									{
										pos.Selected = m_pEditor->m_aComponents[index].Selected;
										break;
									}
							}
						}
						else if (!m_pEditor->m_aComponents[index].Selected || !m_pEditor->isMultipleSelect())
							DeselectAllExceptComponent(index);
						m_pEditor->m_eOperation = CFormEditor::Part::Translate;
						m_pEditor->m_bMouseDown = true;
					}
					else
					{
						// At last, find the control under the cursor and select/deselect
						IControl *control{ m_pEditor->getControl(m.Position) };
						if (control)
						{
							if (control == m_pEditor)
							{
								if (!m.Shift)
									m_pEditor->DeselectAll();
								m_pEditor->m_eOperation = CFormEditor::Part::Select;
								m_pEditor->m_bMouseDown = true;
							}
							else
							{
								for (auto pos = m_pEditor->m_aControls.begin(); pos != m_pEditor->m_aControls.end(); pos++)
									if (pos->Control == control)
									{
										if (m.Shift && !m.Ctrl)
										{
											pos->Selected = !pos->Selected;
											if (pos->Selected && m_pEditor->OnSelectControl)
												m_pEditor->OnSelectControl(m_pEditor, pos->Control);
											else if (!pos->Selected && m_pEditor->OnDeselectControl)
												m_pEditor->OnDeselectControl(m_pEditor, pos->Control);
											for (auto &pos1 : m_pEditor->m_aComponents)
												if (pos1.Control == pos->Control)
												{
													pos1.Selected = pos->Selected;
													break;
												}
										}
										else if (!pos->Selected || !m_pEditor->isMultipleSelect())
											DeselectAllExceptControl(int(pos - m_pEditor->m_aControls.begin()));
										m_pEditor->m_eOperation = CFormEditor::Part::Translate;
										m_pEditor->m_bMouseDown = true;
										break;
									}
							}
						}
					}
				}
				if (m_pEditor->m_bMouseDown)
				{
					DeselectChildControls();
					StoreTransform(m.Position);
					m_pEditor->getForm()->CaptureMouse(m_pEditor, true);
					m_pEditor->Repaint(false);
				}
			}
			else
				MouseUp(m);
		}

		void CFormEditorService::MouseUp(const MessageMouse &m)
		{
			MouseDownCancel(true, m.Position);
		}

		void CFormEditorService::MouseMove(const MessageMouse &m)
		{
			if (m_pEditor->m_bMouseDown)
			{
				PointB grid_enabled{ m_pEditor->m_sGridEnabled };
				if ((grid_enabled.X || grid_enabled.Y) && !m_pEditor->getTransformControls()->isIdentity())
					grid_enabled.X = grid_enabled.Y = false;
				switch (m_pEditor->m_eOperation)
				{
				case CFormEditor::Part::ResizeLeft:
					ResizeLeft(m.Position, grid_enabled);
					break;
				case CFormEditor::Part::ResizeTop:
					ResizeTop(m.Position, grid_enabled);
					break;
				case CFormEditor::Part::ResizeRight:
					ResizeRight(m.Position, grid_enabled);
					break;
				case CFormEditor::Part::ResizeBottom:
					ResizeBottom(m.Position, grid_enabled);
					break;
				case CFormEditor::Part::ResizeLeftTop:
					ResizeLeftTop(m.Position, grid_enabled);
					break;
				case CFormEditor::Part::ResizeRightTop:
					ResizeRightTop(m.Position, grid_enabled);
					break;
				case CFormEditor::Part::ResizeRightBottom:
					ResizeRightBottom(m.Position, grid_enabled);
					break;
				case CFormEditor::Part::ResizeLeftBottom:
					ResizeLeftBottom(m.Position, grid_enabled);
					break;
				case CFormEditor::Part::Rotate:
					Rotate(m.Position);
					break;
				case CFormEditor::Part::Translate:
					Translate(m.Position, grid_enabled);
					break;
				case CFormEditor::Part::Select:
					Select(m.Position);
					break;
				default:
					break;
				}
			}
			else if (m_pEditor->UpdateHoveredPart(m.Position))
				m_pEditor->Repaint(false);
		}

		void CFormEditorService::StoreTransform(const PointF &position)
		{
			m_sFormToEditor = ntl::Inversed<float>(m_pEditor->getTransformMatrix() * m_pEditor->getTransformControls()->getMatrix());
			Vec4f v{ m_sFormToEditor * Vec4f{ position.X, position.Y, 0, 1 } };
			m_sDownPointEditor = PointF{ v.X, v.Y };
			m_sDownPoint = position;
			m_sSelectionRect = RectF{ position.X, position.Y, position.X, position.Y };
			for (auto pos = m_pEditor->m_aComponents.begin(); pos != m_pEditor->m_aComponents.end(); pos++)
			{
				pos->DownPosition = pos->Position;
				pos->DownSelected = pos->Selected;
			}
			for (auto pos = m_pEditor->m_aControls.begin(); pos != m_pEditor->m_aControls.end(); pos++)
			{
				pos->FormToLocal = ntl::Inversed<float>(pos->Control->getTransformMatrix());
				pos->DownPointLocal = pos->Control->FormToLocal(position);
				pos->DownPosition.X = pos->Control->getTransform()->getTx();
				pos->DownPosition.Y = pos->Control->getTransform()->getTy();
				pos->DownRotate = pos->Control->getTransform()->getRz();
				pos->DownSize = pos->Control->getSize();
				pos->DownSelected = pos->Selected;
				pos->ParentToForm = pos->Control->getParent()->getTransform()->getMatrix();
				pos->LocalToParent = pos->Control->getTransform()->getMatrix();
			}
		}

		void CFormEditorService::Translate(const PointF &position, const PointB &grid_enabled)
		{
			bool changed{ false };
			for (auto pos = m_pEditor->m_aComponents.begin(); pos != m_pEditor->m_aComponents.end(); pos++)
				if (pos->Selected)
				{
					Vec4f local_current_point{ m_sFormToEditor * Vec4f{ position.X, position.Y, 0, 1 } };
					PointF new_pos{ local_current_point.X - m_sDownPointEditor.X + pos->DownPosition.X, local_current_point.Y - m_sDownPointEditor.Y + pos->DownPosition.Y };
					if (grid_enabled.X)
						new_pos.X = std::round(new_pos.X / m_pEditor->m_sGridSize.X) * m_pEditor->m_sGridSize.X;
					if (grid_enabled.Y)
						new_pos.Y = std::round(new_pos.Y / m_pEditor->m_sGridSize.Y) * m_pEditor->m_sGridSize.Y;
					if (IsNotEqual(new_pos, pos->Position))
					{
						pos->Position = new_pos;
						if (pos->Component && m_pEditor->OnComponentTransform)
							m_pEditor->OnComponentTransform(m_pEditor, pos->Component);
						else if (pos->Control && m_pEditor->OnControlTransform)
							m_pEditor->OnControlTransform(m_pEditor, pos->Control);
						changed = true;
					}
				}
			for (auto pos = m_pEditor->m_aControls.begin(); pos != m_pEditor->m_aControls.end(); pos++)
				if (pos->Selected)
				{
					Vec4f local_current_point{ pos->FormToLocal * Vec4f{ position.X, position.Y, 0, 1 } };
					if (grid_enabled.X)
						local_current_point.X = std::round((local_current_point.X - pos->DownPointLocal.X) / m_pEditor->m_sGridSize.X) * m_pEditor->m_sGridSize.X + pos->DownPointLocal.X;
					if (grid_enabled.Y)
						local_current_point.Y = std::round((local_current_point.Y - pos->DownPointLocal.Y) / m_pEditor->m_sGridSize.Y) * m_pEditor->m_sGridSize.Y + pos->DownPointLocal.Y;
					if (ntl::IsNotEqual<float>(local_current_point.X + pos->DownPointLocal.X, 0) || ntl::IsNotEqual<float>(local_current_point.Y + pos->DownPointLocal.Y, 0))
					{
						Vec4f v{ pos->LocalToParent * Vec4f{ local_current_point.X - pos->DownPointLocal.X, local_current_point.Y - pos->DownPointLocal.Y, 0, 1 } };
						if (pos->Control->getTransform()->Translate(v.X, v.Y, pos->Control->getTransform()->getTz()))
						{
							if (m_pEditor->OnControlTransform)
								m_pEditor->OnControlTransform(m_pEditor, pos->Control);
							changed = true;
						}
					}
				}
			if (changed)
				m_pEditor->Repaint(false);
		}

		void CFormEditorService::ResizeLeft(const PointF &position, const PointB &grid_enabled)
		{
			CFormEditor::CONTROL control{ m_pEditor->m_aControls[m_pEditor->getFirstSelectedControl()] };
			Vec4f local_current_point{ control.FormToLocal * Vec4f{ position.X, position.Y, 0, 1 } };
			if (grid_enabled.X)
				local_current_point.X = std::round((local_current_point.X - control.DownPointLocal.X) / m_pEditor->m_sGridSize.X) * m_pEditor->m_sGridSize.X + control.DownPointLocal.X;
			Vec4f v{ control.LocalToParent * Vec4f{ local_current_point.X - control.DownPointLocal.X, 0, 0, 1 } };
			if (ntl::IsNotEqual<float>(local_current_point.X + control.DownPointLocal.X, 0)) // Only if width should be changed
			{
				bool changed{ false };
				if (control.Control->getTransform()->Translate(v.X, v.Y, control.Control->getTransform()->getTz()))
				{
					if (m_pEditor->OnControlTransform)
						m_pEditor->OnControlTransform(m_pEditor, control.Control);
					changed = true;
				}
				if (control.Control->setWidth(control.DownSize.X - local_current_point.X + control.DownPointLocal.X))
				{
					if (m_pEditor->OnControlResize)
						m_pEditor->OnControlResize(m_pEditor, control.Control);
					changed = true;
				}
				if (changed)
					m_pEditor->Repaint(false);
			}
		}

		void CFormEditorService::ResizeTop(const PointF &position, const PointB &grid_enabled)
		{
			CFormEditor::CONTROL control{ m_pEditor->m_aControls[m_pEditor->getFirstSelectedControl()] };
			Vec4f local_current_point{ control.FormToLocal * Vec4f{ position.X, position.Y, 0, 1 } };
			if (grid_enabled.X)
				local_current_point.Y = std::round((local_current_point.Y - control.DownPointLocal.Y) / m_pEditor->m_sGridSize.Y) * m_pEditor->m_sGridSize.Y + control.DownPointLocal.Y;
			Vec4f v{ control.LocalToParent * Vec4f{ 0, local_current_point.Y - control.DownPointLocal.Y, 0, 1 } };
			if (ntl::IsNotEqual<float>(local_current_point.Y + control.DownPointLocal.Y, 0)) // Only if width should be changed
			{
				bool changed{ false };
				if (control.Control->getTransform()->Translate(v.X, v.Y, control.Control->getTransform()->getTz()))
				{
					if (m_pEditor->OnControlTransform)
						m_pEditor->OnControlTransform(m_pEditor, control.Control);
					changed = true;
				}
				if (control.Control->setHeight(control.DownSize.Y - local_current_point.Y + control.DownPointLocal.Y))
				{
					if (m_pEditor->OnControlResize)
						m_pEditor->OnControlResize(m_pEditor, control.Control);
					changed = true;
				}
				if (changed)
					m_pEditor->Repaint(false);
			}
		}

		void CFormEditorService::ResizeRight(const PointF &position, const PointB &grid_enabled)
		{
			CFormEditor::CONTROL control{ m_pEditor->m_aControls[m_pEditor->getFirstSelectedControl()] };
			Vec4f local_current_point{ control.FormToLocal * Vec4f{ position.X, position.Y, 0, 1 } };
			if (grid_enabled.X)
				local_current_point.X = std::round((local_current_point.X - control.DownPointLocal.X) / m_pEditor->m_sGridSize.X) * m_pEditor->m_sGridSize.X + control.DownPointLocal.X;
			if (ntl::IsNotEqual<float>(local_current_point.X + control.DownPointLocal.X, 0) && control.Control->setWidth(control.DownSize.X + local_current_point.X - control.DownPointLocal.X)) // Only if width should be changed
			{
				if (m_pEditor->OnControlResize)
					m_pEditor->OnControlResize(m_pEditor, control.Control);
				m_pEditor->Repaint(false);
			}
		}

		void CFormEditorService::ResizeBottom(const PointF &position, const PointB &grid_enabled)
		{
			CFormEditor::CONTROL control{ m_pEditor->m_aControls[m_pEditor->getFirstSelectedControl()] };
			Vec4f local_current_point{ control.FormToLocal * Vec4f{ position.X, position.Y, 0, 1 } };
			if (grid_enabled.X)
				local_current_point.Y = std::round((local_current_point.Y - control.DownPointLocal.Y) / m_pEditor->m_sGridSize.Y) * m_pEditor->m_sGridSize.Y + control.DownPointLocal.Y;
			if (ntl::IsNotEqual<float>(local_current_point.Y + control.DownPointLocal.Y, 0) && control.Control->setHeight(control.DownSize.Y + local_current_point.Y - control.DownPointLocal.Y)) // Only if width should be changed
			{
				if (m_pEditor->OnControlResize)
					m_pEditor->OnControlResize(m_pEditor, control.Control);
				m_pEditor->Repaint(false);
			}
		}

		void CFormEditorService::ResizeLeftTop(const PointF &position, const PointB &grid_enabled)
		{
			CFormEditor::CONTROL control{ m_pEditor->m_aControls[m_pEditor->getFirstSelectedControl()] };
			Vec4f local_current_point{ control.FormToLocal * Vec4f{ position.X, position.Y, 0, 1 } };
			if (grid_enabled.X)
				local_current_point.X = std::round((local_current_point.X - control.DownPointLocal.X) / m_pEditor->m_sGridSize.X) * m_pEditor->m_sGridSize.X + control.DownPointLocal.X;
			if (grid_enabled.Y)
				local_current_point.Y = std::round((local_current_point.Y - control.DownPointLocal.Y) / m_pEditor->m_sGridSize.Y) * m_pEditor->m_sGridSize.Y + control.DownPointLocal.Y;
			Vec4f v{ control.LocalToParent * Vec4f{ local_current_point.X - control.DownPointLocal.X, local_current_point.Y - control.DownPointLocal.Y, 0, 1 } };
			if (ntl::IsNotEqual<float>(local_current_point.X + control.DownPointLocal.X, 0) || ntl::IsNotEqual<float>(local_current_point.Y + control.DownPointLocal.Y, 0)) // Only if width should be changed
			{
				bool changed{ false };
				if (control.Control->getTransform()->Translate(v.X, v.Y, control.Control->getTransform()->getTz()))
				{
					if (m_pEditor->OnControlTransform)
						m_pEditor->OnControlTransform(m_pEditor, control.Control);
					changed = true;
				}
				if (control.Control->setSize(PointF{ control.DownSize.X - local_current_point.X + control.DownPointLocal.X, control.DownSize.Y - local_current_point.Y + control.DownPointLocal.Y }))
				{
					if (m_pEditor->OnControlResize)
						m_pEditor->OnControlResize(m_pEditor, control.Control);
					changed = true;
				}
				if (changed)
					m_pEditor->Repaint(false);
			}
		}

		void CFormEditorService::ResizeRightTop(const PointF &position, const PointB &grid_enabled)
		{
			CFormEditor::CONTROL control{ m_pEditor->m_aControls[m_pEditor->getFirstSelectedControl()] };
			Vec4f local_current_point{ control.FormToLocal * Vec4f{ position.X, position.Y, 0, 1 } };
			if (grid_enabled.X)
				local_current_point.X = std::round((local_current_point.X - control.DownPointLocal.X) / m_pEditor->m_sGridSize.X) * m_pEditor->m_sGridSize.X + control.DownPointLocal.X;
			if (grid_enabled.Y)
				local_current_point.Y = std::round((local_current_point.Y - control.DownPointLocal.Y) / m_pEditor->m_sGridSize.Y) * m_pEditor->m_sGridSize.Y + control.DownPointLocal.Y;
			Vec4f v{ control.LocalToParent * Vec4f{ 0, local_current_point.Y - control.DownPointLocal.Y, 0, 1 } };
			if (ntl::IsNotEqual<float>(local_current_point.X + control.DownPointLocal.X, 0) || ntl::IsNotEqual<float>(local_current_point.Y + control.DownPointLocal.Y, 0)) // Only if width should be changed
			{
				bool changed{ false };
				if (control.Control->getTransform()->Translate(v.X, v.Y, control.Control->getTransform()->getTz()))
				{
					if (m_pEditor->OnControlTransform)
						m_pEditor->OnControlTransform(m_pEditor, control.Control);
					changed = true;
				}
				if (control.Control->setSize(PointF{ control.DownSize.X + local_current_point.X - control.DownPointLocal.X, control.DownSize.Y - local_current_point.Y + control.DownPointLocal.Y }))
				{
					if (m_pEditor->OnControlResize)
						m_pEditor->OnControlResize(m_pEditor, control.Control);
					changed = true;
				}
				if (changed)
					m_pEditor->Repaint(false);
			}
		}

		void CFormEditorService::ResizeRightBottom(const PointF &position, const PointB &grid_enabled)
		{
			CFormEditor::CONTROL control{ m_pEditor->m_aControls[m_pEditor->getFirstSelectedControl()] };
			Vec4f local_current_point{ control.FormToLocal * Vec4f{ position.X, position.Y, 0, 1 } };
			if (grid_enabled.X)
				local_current_point.X = std::round((local_current_point.X - control.DownPointLocal.X) / m_pEditor->m_sGridSize.X) * m_pEditor->m_sGridSize.X + control.DownPointLocal.X;
			if (grid_enabled.Y)
				local_current_point.Y = std::round((local_current_point.Y - control.DownPointLocal.Y) / m_pEditor->m_sGridSize.Y) * m_pEditor->m_sGridSize.Y + control.DownPointLocal.Y;
			if (ntl::IsNotEqual<float>(local_current_point.X + control.DownPointLocal.X, 0) || ntl::IsNotEqual<float>(local_current_point.Y + control.DownPointLocal.Y, 0)) // Only if width should be changed
				if (control.Control->setSize(PointF{ control.DownSize.X + local_current_point.X - control.DownPointLocal.X, control.DownSize.Y + local_current_point.Y - control.DownPointLocal.Y }))
				{
					if (m_pEditor->OnControlResize)
						m_pEditor->OnControlResize(m_pEditor, control.Control);
					m_pEditor->Repaint(false);
				}
		}

		void CFormEditorService::ResizeLeftBottom(const PointF &position, const PointB &grid_enabled)
		{
			CFormEditor::CONTROL control{ m_pEditor->m_aControls[m_pEditor->getFirstSelectedControl()] };
			Vec4f local_current_point{ control.FormToLocal * Vec4f{ position.X, position.Y, 0, 1 } };
			if (grid_enabled.X)
				local_current_point.X = std::round((local_current_point.X - control.DownPointLocal.X) / m_pEditor->m_sGridSize.X) * m_pEditor->m_sGridSize.X + control.DownPointLocal.X;
			if (grid_enabled.Y)
				local_current_point.Y = std::round((local_current_point.Y - control.DownPointLocal.Y) / m_pEditor->m_sGridSize.Y) * m_pEditor->m_sGridSize.Y + control.DownPointLocal.Y;
			Vec4f v{ control.LocalToParent * Vec4f{ local_current_point.X - control.DownPointLocal.X, 0, 0, 1 } };
			if (ntl::IsNotEqual<float>(local_current_point.X + control.DownPointLocal.X, 0) || ntl::IsNotEqual<float>(local_current_point.Y + control.DownPointLocal.Y, 0)) // Only if width should be changed
			{
				bool changed{ false };
				if (control.Control->getTransform()->Translate(v.X, v.Y, control.Control->getTransform()->getTz()))
				{
					if (m_pEditor->OnControlTransform)
						m_pEditor->OnControlTransform(m_pEditor, control.Control);
					changed = true;
				}
				if (control.Control->setSize(PointF{ control.DownSize.X - local_current_point.X + control.DownPointLocal.X, control.DownSize.Y + local_current_point.Y - control.DownPointLocal.Y }))
				{
					if (m_pEditor->OnControlResize)
						m_pEditor->OnControlResize(m_pEditor, control.Control);
					changed = true;
				}
				if (changed)
					m_pEditor->Repaint(false);
			}
		}

		void CFormEditorService::Rotate(const PointF &position)
		{
			CFormEditor::CONTROL control{ m_pEditor->m_aControls[m_pEditor->getFirstSelectedControl()] };
			Vec4f local_current_point{ control.FormToLocal * Vec4f{ position.X, position.Y, 0, 1 } };
			local_current_point.X -= control.DownPointLocal.X - control.DownSize.X;
			local_current_point.Y -= control.DownPointLocal.Y;
			if (ntl::Abs<float>(local_current_point.X) >= 1 || ntl::Abs<float>(local_current_point.Y) >= 1)
			{
				float alpha{ std::atan(local_current_point.Y / local_current_point.X) };
				if (local_current_point.X < 0)
					alpha += ntl::Pi<float>;
				if (m_pEditor->m_bRotateGridEnabled)
					alpha = std::round(alpha / m_pEditor->m_fRotateGridSize) * m_pEditor->m_fRotateGridSize;
				alpha += control.DownRotate;
				if (ntl::IsNotEqual<float>(alpha, control.Control->getTransform()->getRz()) && control.Control->getTransform()->setRz(alpha))
				{
					if (m_pEditor->OnControlTransform)
						m_pEditor->OnControlTransform(m_pEditor, control.Control);
					m_pEditor->Repaint(false);
				}
			}
		}

		void CFormEditorService::Select(const PointF &position)
		{
			m_sSelectionRect = RectF{ ntl::Min<float>(position.X, m_sDownPoint.X), ntl::Min<float>(position.Y, m_sDownPoint.Y), ntl::Max<float>(position.X, m_sDownPoint.X), ntl::Max<float>(position.Y, m_sDownPoint.Y) };
			for (auto pos = m_pEditor->m_aComponents.begin(); pos != m_pEditor->m_aComponents.end(); pos++)
			{
				RectF r{ pos->Position.X, pos->Position.Y, pos->Position.X + CFormEditor::ComponentIconSize.X, pos->Position.Y + CFormEditor::ComponentIconSize.Y };
				bool intersected{ Intersects(m_sSelectionRect, r, m_pEditor->getTransformMatrix()) };
				if (intersected)
					pos->Selected = true;
				else if (!pos->DownSelected)
					pos->Selected = false;
			}
			for (auto pos = m_pEditor->m_aControls.begin(); pos != m_pEditor->m_aControls.end(); pos++)
			{
				RectF r{ 0, 0, pos->Control->getWidth(), pos->Control->getHeight() };
				bool intersected{ Intersects(m_sSelectionRect, r, pos->Control->getTransformMatrix()) };
				if (intersected)
					pos->Selected = true;
				else if (!pos->DownSelected)
					pos->Selected = false;
			}
			m_pEditor->Repaint(false);
		}

		void CFormEditorService::DeselectAllExceptComponent(const int index)
		{
			for (auto pos = m_pEditor->m_aComponents.begin(); pos != m_pEditor->m_aComponents.end(); pos++)
				if (int(pos - m_pEditor->m_aComponents.begin()) == index)
				{
					if (!pos->Selected)
					{
						pos->Selected = true;
						if (pos->Component && m_pEditor->OnSelectComponent)
							m_pEditor->OnSelectComponent(m_pEditor, pos->Component);
						else if (pos->Control && m_pEditor->OnSelectControl)
							m_pEditor->OnSelectControl(m_pEditor, pos->Control);
					}
				}
				else if (pos->Selected)
				{
					pos->Selected = false;
					if (pos->Component && m_pEditor->OnDeselectComponent)
						m_pEditor->OnDeselectComponent(m_pEditor, pos->Component);
				}
			for (auto pos = m_pEditor->m_aControls.begin(); pos != m_pEditor->m_aControls.end(); pos++)
				if (!m_pEditor->m_aComponents[index].Component && pos->Control == m_pEditor->m_aComponents[index].Control)
					pos->Selected = m_pEditor->m_aComponents[index].Selected;
				else if (pos->Selected)
				{
					pos->Selected = false;
					if (m_pEditor->OnDeselectControl)
						m_pEditor->OnDeselectControl(m_pEditor, pos->Control);
				}
		}

		void CFormEditorService::DeselectAllExceptControl(const int index)
		{
			for (auto pos = m_pEditor->m_aControls.begin(); pos != m_pEditor->m_aControls.end(); pos++)
				if (int(pos - m_pEditor->m_aControls.begin()) == index)
				{
					if (!pos->Selected)
					{
						pos->Selected = true;
						if (m_pEditor->OnSelectControl)
							m_pEditor->OnSelectControl(m_pEditor, pos->Control);
					}
				}
				else if (pos->Selected)
				{
					pos->Selected = false;
					if (m_pEditor->OnDeselectControl)
						m_pEditor->OnDeselectControl(m_pEditor, pos->Control);
				}
			for (auto pos = m_pEditor->m_aComponents.begin(); pos != m_pEditor->m_aComponents.end(); pos++)
				if (!pos->Component && pos->Control == m_pEditor->m_aControls[index].Control)
					pos->Selected = m_pEditor->m_aControls[index].Selected;
				else if (pos->Selected)
				{
					pos->Selected = false;
					if (pos->Component && m_pEditor->OnDeselectComponent)
						m_pEditor->OnDeselectComponent(m_pEditor, pos->Component);
				}
		}

		bool CFormEditorService::DeselectChildControls()
		{
			bool result{ false };
			for (auto pos = m_pEditor->m_aControls.begin(); pos != m_pEditor->m_aControls.end(); pos++)
				if (pos->Selected)
				{
					for (auto pos1 = m_pEditor->m_aControls.begin(); pos1 != m_pEditor->m_aControls.end(); pos1++)
						if (pos1->Selected && pos1->Control->hasChild(pos->Control))
						{
							result = true;
							pos->Selected = false;
							if (m_pEditor->OnDeselectControl)
								m_pEditor->OnDeselectControl(m_pEditor, pos->Control);
							break;
						}
				}
			for (auto pos = m_pEditor->m_aComponents.begin(); pos != m_pEditor->m_aComponents.end(); pos++)
				if (pos->Selected && !pos->Component)
				{
					for (auto pos1 = m_pEditor->m_aComponents.begin(); pos1 != m_pEditor->m_aComponents.end(); pos1++)
						if (!pos1->Component && pos1->Selected && pos1->Control->hasChild(pos->Control))
						{
							result = true;
							pos->Selected = false;
							if (m_pEditor->OnDeselectComponent)
								m_pEditor->OnDeselectComponent(m_pEditor, pos->Component);
							break;
						}
				}
			return result;
		}

		void CFormEditorService::ProcessKeyUp()
		{
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (!alt)
			{
				bool changed{ DeselectChildControls() };
				if (!shift)
					for (auto pos = m_pEditor->m_aComponents.begin(); pos != m_pEditor->m_aComponents.end(); pos++)
						if (pos->Selected)
						{
							float new_y{ pos->Position.Y - ((ctrl && m_pEditor->m_sGridEnabled.Y) ? m_pEditor->m_sGridSize.Y : 1) };
							if (ctrl && m_pEditor->m_sGridEnabled.Y)
								new_y = std::round(new_y / m_pEditor->m_sGridSize.Y) * m_pEditor->m_sGridSize.Y;
							if (ntl::IsNotEqual<float>(new_y, pos->Position.Y))
							{
								pos->Position.Y = new_y;
								if (pos->Component && m_pEditor->OnComponentTransform)
									m_pEditor->OnComponentTransform(m_pEditor, pos->Component);
								else if (pos->Control && m_pEditor->OnControlTransform)
									m_pEditor->OnControlTransform(m_pEditor, pos->Control);
								changed = true;
							}
						}
				IEditor *editor{ Application->Editor };
				for (auto pos = m_pEditor->m_aControls.begin(); pos != m_pEditor->m_aControls.end(); pos++)
					if (pos->Selected)
					{
						if (shift)
						{
							if (editor && editor->getControl(pos->Control)->isTransformable())
							{
								float new_height{ ntl::Max<float>(0, pos->Control->getHeight() - ((ctrl && m_pEditor->m_sGridEnabled.Y) ? m_pEditor->m_sGridSize.Y : 1.0f)) };
								if (ntl::IsNotEqual<float>(new_height, pos->Control->getHeight()))
									if (pos->Control->setHeight(new_height))
									{
										if (m_pEditor->OnControlResize)
											m_pEditor->OnControlResize(m_pEditor, pos->Control);
										changed = true;
									}
							}
						}
						else
						{
							if (editor && editor->getControl(pos->Control)->isTransformable())
							{
								float new_y{ pos->Control->getTransform()->getTy() - ((ctrl && m_pEditor->m_sGridEnabled.Y) ? m_pEditor->m_sGridSize.Y : 1) };
								if (ctrl && m_pEditor->m_sGridEnabled.Y)
									new_y = std::round(new_y / m_pEditor->m_sGridSize.Y) * m_pEditor->m_sGridSize.Y;
								if (ntl::IsNotEqual<float>(new_y, pos->Control->getTransform()->getTy()) && pos->Control->getTransform()->setTy(new_y))
								{
									if (m_pEditor->OnControlTransform)
										m_pEditor->OnControlTransform(m_pEditor, pos->Control);
									changed = true;
								}
							}
						}
					}
				if (changed)
					m_pEditor->Repaint(false);
			}
		}

		void CFormEditorService::ProcessKeyDown()
		{
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (!alt)
			{
				bool changed{ DeselectChildControls() };
				if (!shift)
					for (auto pos = m_pEditor->m_aComponents.begin(); pos != m_pEditor->m_aComponents.end(); pos++)
						if (pos->Selected)
						{
							float new_y{ pos->Position.Y + ((ctrl && m_pEditor->m_sGridEnabled.Y) ? m_pEditor->m_sGridSize.Y : 1) };
							if (ctrl && m_pEditor->m_sGridEnabled.Y)
								new_y = std::round(new_y / m_pEditor->m_sGridSize.Y) * m_pEditor->m_sGridSize.Y;
							if (ntl::IsNotEqual<float>(new_y, pos->Position.Y))
							{
								pos->Position.Y = new_y;
								if (pos->Component && m_pEditor->OnComponentTransform)
									m_pEditor->OnComponentTransform(m_pEditor, pos->Component);
								else if (pos->Control && m_pEditor->OnControlTransform)
									m_pEditor->OnControlTransform(m_pEditor, pos->Control);
								changed = true;
							}
						}
				IEditor *editor{ Application->Editor };
				for (auto pos = m_pEditor->m_aControls.begin(); pos != m_pEditor->m_aControls.end(); pos++)
					if (pos->Selected)
					{
						if (shift)
						{
							if (editor && editor->getControl(pos->Control)->isTransformable())
							{
								float new_height{ ntl::Max<float>(0, pos->Control->getHeight() + ((ctrl && m_pEditor->m_sGridEnabled.Y) ? m_pEditor->m_sGridSize.Y : 1)) };
								if (ntl::IsNotEqual<float>(new_height, pos->Control->getHeight()) && pos->Control->setHeight(new_height))
								{
									if (m_pEditor->OnControlResize)
										m_pEditor->OnControlResize(m_pEditor, pos->Control);
									changed = true;
								}
							}
						}
						else
						{
							if (editor && editor->getControl(pos->Control)->isTransformable())
							{
								float new_y{ pos->Control->getTransform()->getTy() + ((ctrl && m_pEditor->m_sGridEnabled.Y) ? m_pEditor->m_sGridSize.Y : 1) };
								if (ctrl && m_pEditor->m_sGridEnabled.Y)
									new_y = std::round(new_y / m_pEditor->m_sGridSize.Y) * m_pEditor->m_sGridSize.Y;
								if (ntl::IsNotEqual<float>(new_y, pos->Control->getTransform()->getTy()) && pos->Control->getTransform()->setTy(new_y))
								{
									if (m_pEditor->OnControlTransform)
										m_pEditor->OnControlTransform(m_pEditor, pos->Control);
									changed = true;
								}
							}
						}
					}
				if (changed)
					m_pEditor->Repaint(false);
			}
		}

		void CFormEditorService::ProcessKeyLeft()
		{
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (!alt)
			{
				bool changed{ DeselectChildControls() };
				if (!shift)
					for (auto pos = m_pEditor->m_aComponents.begin(); pos != m_pEditor->m_aComponents.end(); pos++)
						if (pos->Selected)
						{
							float new_x{ pos->Position.X - ((ctrl && m_pEditor->m_sGridEnabled.X) ? m_pEditor->m_sGridSize.X : 1) };
							if (ctrl && m_pEditor->m_sGridEnabled.X)
								new_x = std::round(new_x / m_pEditor->m_sGridSize.X) * m_pEditor->m_sGridSize.X;
							if (ntl::IsNotEqual<float>(new_x, pos->Position.X))
							{
								pos->Position.X = new_x;
								if (pos->Component && m_pEditor->OnComponentTransform)
									m_pEditor->OnComponentTransform(m_pEditor, pos->Component);
								else if (pos->Control && m_pEditor->OnControlTransform)
									m_pEditor->OnControlTransform(m_pEditor, pos->Control);
								changed = true;
							}
						}
				IEditor *editor{ Application->Editor };
				for (auto pos = m_pEditor->m_aControls.begin(); pos != m_pEditor->m_aControls.end(); pos++)
					if (pos->Selected)
					{
						if (shift)
						{
							if (editor && editor->getControl(pos->Control)->isTransformable())
							{
								float new_width{ ntl::Max<float>(0, pos->Control->getWidth() - ((ctrl && m_pEditor->m_sGridEnabled.X) ? m_pEditor->m_sGridSize.X : 1)) };
								if (ntl::IsNotEqual<float>(new_width, pos->Control->getWidth()) && pos->Control->setWidth(new_width))
								{
									if (m_pEditor->OnControlResize)
										m_pEditor->OnControlResize(m_pEditor, pos->Control);
									changed = true;
								}
							}
						}
						else
						{
							if (editor && editor->getControl(pos->Control)->isTransformable())
							{
								float new_x{ pos->Control->getTransform()->getTx() - ((ctrl && m_pEditor->m_sGridEnabled.X) ? m_pEditor->m_sGridSize.X : 1) };
								if (ctrl && m_pEditor->m_sGridEnabled.X)
									new_x = std::round(new_x / m_pEditor->m_sGridSize.X) * m_pEditor->m_sGridSize.X;
								if (ntl::IsNotEqual<float>(new_x, pos->Control->getTransform()->getTx()) && pos->Control->getTransform()->setTx(new_x))
								{
									if (m_pEditor->OnControlTransform)
										m_pEditor->OnControlTransform(m_pEditor, pos->Control);
									changed = true;
								}
							}
						}
					}
				if (changed)
					m_pEditor->Repaint(false);
			}
		}

		void CFormEditorService::ProcessKeyRight()
		{
			bool ctrl, alt, shift;
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (!alt)
			{
				bool changed{ DeselectChildControls() };
				if (!shift)
					for (auto pos = m_pEditor->m_aComponents.begin(); pos != m_pEditor->m_aComponents.end(); pos++)
						if (pos->Selected)
						{
							float new_x{ pos->Position.X + ((ctrl && m_pEditor->m_sGridEnabled.X) ? m_pEditor->m_sGridSize.X : 1) };
							if (ctrl && m_pEditor->m_sGridEnabled.X)
								new_x = std::round(new_x / m_pEditor->m_sGridSize.X) * m_pEditor->m_sGridSize.X;
							if (ntl::IsNotEqual<float>(new_x, pos->Position.X))
							{
								pos->Position.X = new_x;
								if (pos->Component && m_pEditor->OnComponentTransform)
									m_pEditor->OnComponentTransform(m_pEditor, pos->Component);
								else if (pos->Control && m_pEditor->OnControlTransform)
									m_pEditor->OnControlTransform(m_pEditor, pos->Control);
								changed = true;
							}
						}
				IEditor *editor{ Application->Editor };
				for (auto pos = m_pEditor->m_aControls.begin(); pos != m_pEditor->m_aControls.end(); pos++)
					if (pos->Selected)
					{
						if (shift)
						{
							if (editor && editor->getControl(pos->Control)->isTransformable())
							{
								float new_width{ ntl::Max<float>(0, pos->Control->getWidth() + ((ctrl && m_pEditor->m_sGridEnabled.X) ? m_pEditor->m_sGridSize.X : 1)) };
								if (ntl::IsNotEqual<float>(new_width, pos->Control->getWidth()) && pos->Control->setWidth(new_width))
								{
									if (m_pEditor->OnControlResize)
										m_pEditor->OnControlResize(m_pEditor, pos->Control);
									changed = true;
								}
							}
						}
						else
						{
							if (editor && editor->getControl(pos->Control)->isTransformable())
							{
								float new_x{ pos->Control->getTransform()->getTx() + ((ctrl && m_pEditor->m_sGridEnabled.X) ? m_pEditor->m_sGridSize.X : 1) };
								if (ctrl && m_pEditor->m_sGridEnabled.X)
									new_x = std::round(new_x / m_pEditor->m_sGridSize.X) * m_pEditor->m_sGridSize.X;
								if (ntl::IsNotEqual<float>(new_x, pos->Control->getTransform()->getTx()) && pos->Control->getTransform()->setTx(new_x))
								{
									if (m_pEditor->OnControlTransform)
										m_pEditor->OnControlTransform(m_pEditor, pos->Control);
									changed = true;
								}
							}
						}
					}
				if (changed)
					m_pEditor->Repaint(false);
			}
		}

		void CFormEditorService::ProcessSelectAll()
		{
			bool changed{ false };
			for (auto pos : m_pEditor->m_aControls)
				if (pos.Control->getParent() == m_pEditor && !pos.Selected)
				{
					pos.Selected = true;
					changed = true;
					if (m_pEditor->OnSelectControl)
						m_pEditor->OnSelectControl(m_pEditor, pos.Control);
				}
				else if (pos.Control->getParent() != m_pEditor && pos.Selected)
				{
					pos.Selected = false;
					changed = true;
					if (m_pEditor->OnDeselectControl)
						m_pEditor->OnDeselectControl(m_pEditor, pos.Control);
				}
			for (auto pos : m_pEditor->m_aComponents)
				if (!pos.Selected)
				{
					if (!pos.Control || (pos.Control && pos.Control->getParent() == m_pEditor))
					{
						pos.Selected = true;
						changed = true;
						if (!pos.Control && m_pEditor->OnSelectComponent)
							m_pEditor->OnSelectComponent(m_pEditor, pos.Component);
					}
				}
				else if (pos.Control && pos.Control->getParent() != m_pEditor)
				{
					pos.Selected = false;
					changed = true;
				}
			if (changed)
				m_pEditor->Repaint(false);
		}
	#pragma endregion

	#pragma region State change notifications
		void CFormEditorService::NotifyOnAttach()
		{
			if (m_pEditor->getForm())
			{
				float x{ 10 }, y{ 10 };
				for (int i = 0; i < m_pEditor->getForm()->getComponentCount(); i++)
				{
					bool allowed{ true };
					if (m_pEditor->OnCheckComponentAllowed)
						m_pEditor->OnCheckComponentAllowed(m_pEditor, m_pEditor->getForm()->getComponent(i), allowed);
					else
						allowed = false;
					if (!allowed)
						continue;
					m_pEditor->m_aComponents.push_back({ m_pEditor->getForm()->getComponent(i), nullptr, PointF{ x, y }, false });
					y += CFormEditor::ComponentIconSize.Y + 2;
					if (y + CFormEditor::ComponentIconSize.Y >= m_pEditor->getHeight())
					{
						y = 10;
						x += CFormEditor::ComponentIconSize.X + 2;
					}
				}
			}
		}

		void CFormEditorService::NotifyOnDetach()
		{
			auto pos{ m_pEditor->m_aComponents.begin() };
			while (pos != m_pEditor->m_aComponents.end())
				if (pos->Component)
					pos = m_pEditor->m_aComponents.erase(pos);
				else
					pos++;
			RemoveInvalidControls();
		}

		void CFormEditorService::NotifyOnFreeResources()
		{
			if (m_pEditor->m_pCanvas)
			{
				m_pEditor->m_pCanvas->Release();
				m_pEditor->m_pCanvas = nullptr;
			}
			if (m_pEditor->m_pCanvasControl)
			{
				m_pEditor->m_pCanvasControl->Release();
				m_pEditor->m_pCanvasControl = nullptr;
			}
			if (m_pEditor->m_pCanvasControlBackground)
			{
				m_pEditor->m_pCanvasControlBackground->Release();
				m_pEditor->m_pCanvasControlBackground = nullptr;
			}
			if (m_pEditor->m_pMask)
			{
				m_pEditor->m_pMask->Release();
				m_pEditor->m_pMask = nullptr;
			}
		}
	#pragma endregion

	#pragma region Other components/controls/objects change notifications
		void CFormEditorService::NotifyOnComponentAttach(IComponent *component)
		{
			bool allowed{ true };
			if (m_pEditor->OnCheckComponentAllowed)
				m_pEditor->OnCheckComponentAllowed(m_pEditor, component, allowed);
			else
				allowed = false;
			if (allowed)
			{
				m_pEditor->m_aComponents.push_back({ component, nullptr, PointF{ 10, 10 }, false });
				m_pEditor->Repaint(false);
			}
		}

		void CFormEditorService::NotifyOnComponentDetach(IComponent *component)
		{
			for (auto pos = m_pEditor->m_aComponents.begin(); pos != m_pEditor->m_aComponents.end(); pos++)
				if (pos->Component == component)
				{
					if (pos->Selected && m_pEditor->OnDeselectComponent)
						m_pEditor->OnDeselectComponent(m_pEditor, pos->Component);
					m_pEditor->m_aComponents.erase(pos);
					m_pEditor->Repaint(false);
					break;
				}
		}

		void CFormEditorService::NotifyOnControlAttach(IControl *control)
		{
			if (m_pEditor->hasChild(control))
			{
				AttachControl(control);
				m_pEditor->Repaint(false);
			}
		}

		void CFormEditorService::NotifyOnControlDetach(IControl *control)
		{
			if (RemoveInvalidControls())
				m_pEditor->Repaint(true);
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CFormEditorService::NotifyOnParentStyleChange()
		{
			if (m_pEditor->getStyle())
			{
				m_pEditor->UpdateFromStyle(m_pEditor->getStyle());
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				if (m_pEditor->m_pCanvasControl)
					m_pEditor->m_pCanvasControl->setValid(false);
				if (m_pEditor->m_pCanvasControlBackground)
					m_pEditor->m_pCanvasControlBackground->setValid(false);
				if (m_pEditor->m_pMask)
					m_pEditor->m_pMask->setValid(false);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CFormEditorService::NotifyOnStyleChange()
		{
			if (m_pEditor->getStyle())
			{
				m_pEditor->UpdateFromStyle(m_pEditor->getStyle());
				if (m_pEditor->m_pCanvas)
					m_pEditor->m_pCanvas->setValid(false);
				if (m_pEditor->m_pCanvasControl)
					m_pEditor->m_pCanvasControl->setValid(false);
				if (m_pEditor->m_pCanvasControlBackground)
					m_pEditor->m_pCanvasControlBackground->setValid(false);
				if (m_pEditor->m_pMask)
					m_pEditor->m_pMask->setValid(false);
			}
		}

		void CFormEditorService::NotifyOnResize()
		{
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
			if (m_pEditor->m_pMask)
				m_pEditor->m_pMask->setValid(false);
		}

		void CFormEditorService::NotifyOnEnable()
		{
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
		}

		void CFormEditorService::NotifyOnDisable()
		{
			if (m_pEditor->m_pCanvas)
				m_pEditor->m_pCanvas->setValid(false);
		}

		void CFormEditorService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (!m_pEditor->m_bMouseDown && m_pEditor->UpdateHoveredPart(m.Position))
				m_pEditor->Repaint(false);
		}

		void CFormEditorService::NotifyOnMouseLeave()
		{
			if (!m_pEditor->m_bMouseDown && m_pEditor->m_eHoveredPart != CFormEditor::Part::None)
			{
				m_pEditor->m_eHoveredPart = CFormEditor::Part::None;
				m_pEditor->Repaint(false);
			}
		}

		void CFormEditorService::NotifyOnKillCaptureMouse()
		{
			MouseDownCancel(false, (PointF)m_pEditor->getForm()->ScreenToClient(Application->Mouse->getPosition()));
		}

		void CFormEditorService::NotifyOnTransformControls()
		{
			m_pEditor->Repaint(false);
		}
	#pragma endregion

	#pragma region Paint notifications
		void CFormEditorService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (ntl::IsGreater<float>(m_pEditor->getWidth(), 0) && ntl::IsGreater<float>(m_pEditor->getHeight(), 0))
			{
				m_bMaskActive = false;
				IRenderer *renderer{ m_pEditor->getForm()->getRenderer() };
				Mat4f matrix{ m_pEditor->getTransformMatrix() };
				if (!m.LastPass && (m_pEditor->m_cBackgroundGradient.getPointCount() >= 2 || m_pEditor->m_sBackgroundColor.A > 0))
					m_pEditor->Render(renderer, matrix);
				if (((!m.LastPass && (m_pEditor->getControlCount() > 0 || m_pEditor->m_aComponents.size() > 0)) || m_pEditor->m_eOperation == CFormEditor::Part::Select) && m_pEditor->m_bUseMask)
				{
					m_pEditor->RenderMask(renderer);
					if (m_pEditor->m_pMask)
					{
						renderer->PushMask(m_pEditor->m_pMask, matrix);
						m_bMaskActive = true;
					}
				}
			}
			else if (m_pEditor->m_bUseMask)
				draw_children = false;
		}

		void CFormEditorService::NotifyOnPaintEnd(const MessagePaint &m)
		{
			if (ntl::IsGreater<float>(m_pEditor->getWidth(), 0) && ntl::IsGreater<float>(m_pEditor->getHeight(), 0))
			{
				if (!m.LastPass)
				{
					IRenderer *renderer{ m_pEditor->getForm()->getRenderer() };
					m_pEditor->RenderComponents(renderer);
					m_pEditor->RenderSelection(renderer);
					if (m_pEditor->m_bMouseDown && m_pEditor->m_eOperation == CFormEditor::Part::Select && !m_sSelectionRect.is_zero())
						m_pEditor->RenderSelectionRectangle(renderer, m_sSelectionRect);
				}
				if (m_bMaskActive)
				{
					m_pEditor->getForm()->getRenderer()->PopMask();
					m_bMaskActive = false;
				}
			}
		}
	#pragma endregion

	#pragma region Input notifications
		void CFormEditorService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (!m_pEditor->m_bMouseDown)
			{
				switch (m.Key)
				{
				case Key::Up:
					ProcessKeyUp();
					break;
				case Key::Down:
					ProcessKeyDown();
					break;
				case Key::Left:
					ProcessKeyLeft();
					break;
				case Key::Right:
					ProcessKeyRight();
					break;
				case Key::Escape:
					m_pEditor->DeselectAll();
					break;
				case Key::A:
					if (Application->Keyboard->isDown(Key::Control))
						ProcessSelectAll();
					break;
				default:
					break;
				}
			}
		}

		void CFormEditorService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			MouseMove(m);
		}

		void CFormEditorService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			MouseDown(m);
		}

		void CFormEditorService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			MouseUp(m);
		}

		void CFormEditorService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			MouseUp(m);
		}

		void CFormEditorService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pEditor->OnMouseDown)
			{
				bool t;
				m_pEditor->OnMouseDown(m_pEditor, m, t);
			}
			MouseUp(m);
		}

		void CFormEditorService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(m);
		}

		void CFormEditorService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(m);
		}

		void CFormEditorService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pEditor->OnMouseDown)
			{
				bool t;
				m_pEditor->OnMouseDown(m_pEditor, m, t);
			}
			MouseUp(m);
		}

		void CFormEditorService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			MouseUp(m);
		}

		void CFormEditorService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			MouseUp(m);
		}
	#pragma endregion

	#pragma region Interceptors
		bool CFormEditorService::InterceptSetCursor(IControl *control)
		{
			return true;
		}

		bool CFormEditorService::InterceptMouseHover(IControl *control)
		{
			if (!m_pEditor->m_bMouseDown && m_pEditor->UpdateHoveredPart((PointF)m_pEditor->getForm()->ScreenToClient(Application->Mouse->getPosition())))
				m_pEditor->Repaint(false);
			return true;
		}

		bool CFormEditorService::InterceptShowHint(IControl *control, String &hint)
		{
			return true;
		}

		bool CFormEditorService::InterceptTabOrder()
		{
			return true;
		}

		bool CFormEditorService::InterceptHotkeys(IControl *control, const MessageHotkey &m)
		{
			return true;
		}

		bool CFormEditorService::InterceptKeyDown(IControl *control, const MessageKey &m)
		{
			return true;
		}

		bool CFormEditorService::InterceptKeyUp(IControl *control, const MessageKey &m)
		{
			return true;
		}

		bool CFormEditorService::InterceptChar(IControl *control, const MessageChar &m)
		{
			return true;
		}

		bool CFormEditorService::InterceptDeadChar(IControl *control, const MessageChar &m)
		{
			return true;
		}

		bool CFormEditorService::InterceptMouseMove(IControl *control, const MessageMouse &m)
		{
			MouseMove(m);
			return true;
		}

		bool CFormEditorService::InterceptLeftMouseButtonDown(IControl *control, const MessageMouse &m)
		{
			MouseDown(m);
			return true;
		}

		bool CFormEditorService::InterceptLeftMouseButtonUp(IControl *control, const MessageMouse &m)
		{
			MouseUp(m);
			return true;
		}

		bool CFormEditorService::InterceptLeftMouseButtonDoubleClick(IControl *control, const MessageMouse &m)
		{
			MouseUp(m);
			return true;
		}

		bool CFormEditorService::InterceptMiddleMouseButtonDown(IControl *control, const MessageMouse &m)
		{
			MouseUp(m);
			return true;
		}

		bool CFormEditorService::InterceptMiddleMouseButtonUp(IControl *control, const MessageMouse &m)
		{
			MouseUp(m);
			return true;
		}

		bool CFormEditorService::InterceptMiddleMouseButtonDoubleClick(IControl *control, const MessageMouse &m)
		{
			MouseUp(m);
			return true;
		}

		bool CFormEditorService::InterceptRightMouseButtonDown(IControl *control, const MessageMouse &m)
		{
			MouseUp(m);
			return true;
		}

		bool CFormEditorService::InterceptRightMouseButtonUp(IControl *control, const MessageMouse &m)
		{
			MouseUp(m);
			return true;
		}

		bool CFormEditorService::InterceptRightMouseButtonDoubleClick(IControl *control, const MessageMouse &m)
		{
			MouseUp(m);
			return true;
		}

		bool CFormEditorService::InterceptMouseVerticalWheel(IControl *control, const MessageMouseWheel &m)
		{
			return true;
		}

		bool CFormEditorService::InterceptMouseHorizontalWheel(IControl *control, const MessageMouseWheel &m)
		{
			return true;
		}

		bool CFormEditorService::InterceptDropFiles(IControl *control, const MessageDropFiles &m)
		{
			return true;
		}

		bool CFormEditorService::InterceptFocus(IControl *control, const FocusedBy focused_by)
		{
			return true;
		}
	#pragma endregion
	}
}
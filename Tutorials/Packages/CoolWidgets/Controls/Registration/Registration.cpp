#include "stdafx.h"

namespace nitisa
{
	namespace coolwidgets
	{
	#pragma region Constructor & destructor
		CRegistration::CRegistration():
			// Call parent class constructor
			CControl(L"Registration", true, true, false, true, false, true),
			// Set default values for properties
			m_sBackgroundColor{ 0, 0, 0, 0 },
			m_aInputBorderColor{ Color{ 127, 127, 127, 255 }, Color{ 127, 127, 255, 255 } },
			m_pInputFirstName{ nullptr },
			m_pInputLastName{ nullptr },
			m_pCalendar{ nullptr },
			m_eFocusedElement{ Element::InputFirstName },
			m_eHoveredElement{ Element::None },
			m_eDownElement{ Element::None },
			m_pCanvas{ nullptr },
			m_pCanvasCalendar{ nullptr },
			m_cTextInputListener{ this },
			m_cMonthCalendarListener{ this },
			m_bCalendarOpened{ false },
			m_sInputFirstNameRect{ 152, 0, 300, 24 },
			m_sInputLastNameRect{ 152, 28, 300, 52 },
			m_sDateRect{ 152, 56, 300, 80 },
			m_sCalendarBorderWidth{ 1, 1, 1, 1 },
			m_sCalendarPadding{ 5, 3, 5, 3 },
			m_sCalendarBorderColor{ 151, 151, 151, 255 },
			m_sCalendarBackgroundColor{ 255, 255, 255, 255 },
			OnChange{ nullptr }
		{
			setService(new CRegistrationService(this), true); // Create and set widget service additionally destroying default one
			CControl::setSize(PointF{ 300, 80 }); // Set size of the widget
		}

		CRegistration::CRegistration(IControl *parent) :CRegistration()
		{
			setParent(parent);
		}

		CRegistration::CRegistration(IForm *parent) : CRegistration()
		{
			setForm(parent);
		}

		CRegistration::~CRegistration()
		{
			if (m_pInputFirstName)
				m_pInputFirstName->Release();
			if (m_pInputLastName)
				m_pInputLastName->Release();
			if (m_pCalendar)
				m_pCalendar->Release();
		}
	#pragma endregion

	#pragma region IControl getters
		IControl *CRegistration::getControl(const PointF &position)
		{
			if (m_bCalendarOpened)
			{
				Vec4f v{ ntl::Inversed<float>(getTransformMatrix()) * Vec4f { position.X, position.Y, 0, 1 } }; // Convert "position" into widget coordinate space
				if (v.X >= m_sCalendarRect.Left && v.X < m_sCalendarRect.Right && v.Y >= m_sCalendarRect.Top && v.Y < m_sCalendarRect.Bottom) // Check whether position is inside calendar rectangle
					return this;
				if (v.X >= 0 && v.X < getWidth() && v.Y >= 0 && v.Y < getHeight()) // Check whether position is inside widget rectangle
					return this;
				return nullptr; // Position is neither in calendar nor in widget rectangle, return nullptr
			}
			return CControl::getControl(position); // If calendar is not shown, default getControl() is OK for us
		}

		CursorType CRegistration::getCursor()
		{
			switch (m_eHoveredElement)
			{
			// If hovered element is either of text inputs, return I-Beam cursor type
			case Element::InputFirstName:
			case Element::InputLastName:
				return CursorType::IBeam;
			// If hovered element is arrow for showing calendar, return Hand cursor type
			case Element::DateArrow:
				return CursorType::Hand;
			// In other cases return value assigned to Cursor property
			default:
				return CControl::getCursor();
			}
		}
	#pragma endregion

	#pragma region IControl setters
		bool CRegistration::setAlign(const Align value)
		{
			// Aligning is not supported
			return false;
		}

		bool CRegistration::setConstraints(const RectF &value)
		{
			// Constraints cannot be changed
			return false;
		}

		bool CRegistration::setSize(const PointF &value)
		{
			// Size cannot be changed
			return false;
		}

		bool CRegistration::setEnabled(const bool value)
		{
			// Widget is always enabled and this cannot be changed
			return false;
		}
	#pragma endregion

	#pragma region IRegistration getters
		IRegistration::RegistrationData CRegistration::getRegistrationData()
		{
			// Return widget data getting values directly from built-in controls
			return RegistrationData{
				getInputFirstName()->getText(),
				getInputLastName()->getText(),
				getCalendar()->getYear(),
				getCalendar()->getMonth(),
				getCalendar()->getDay() };
		}
	#pragma endregion

	#pragma region IRegistration setters
		bool CRegistration::setRegistrationData(const RegistrationData &value)
		{
			// Set widget values directly in controls
			CLockRepaint lock{ this };
			bool result{ false };
			result = getInputFirstName()->setText(value.FirstName) || result;
			result = getInputLastName()->setText(value.LastName) || result;
			result = getCalendar()->setYear(value.Year) || result;
			result = getCalendar()->setMonth(value.Month) || result;
			result = getCalendar()->setDay(value.Day) || result;
			if (result)
			{
				// Repaint only if something was really changed
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_bCalendarOpened && m_pCanvasCalendar)
					m_pCanvasCalendar->setValid(false);
				Repaint(false);
			}
			return result;
		}
	#pragma endregion

	#pragma region Getters
		Color CRegistration::getBackgroundColor()
		{
			return m_sBackgroundColor;
		}

		Color CRegistration::getInputBorderColor(const State state)
		{
			return m_aInputBorderColor[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CRegistration::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CRegistration::setInputBorderColor(const State state, const Color &value)
		{
			if (value != m_aInputBorderColor[(int)state])
			{
				m_aInputBorderColor[(int)state] = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		CRegistration::Element CRegistration::getElement(const PointF &p)
		{
			// Check whether point is inside calendar rectangle
			if (m_bCalendarOpened && p.X >= m_sCalendarRect.Left && p.X < m_sCalendarRect.Right && p.Y >= m_sCalendarRect.Top && p.Y < m_sCalendarRect.Bottom)
				return Element::Calendar;
			// Check whether point is inside first name built-in text input
			if (p.X >= m_sInputFirstNameRect.Left + 2 && p.X < m_sInputFirstNameRect.Right - 2 && p.Y >= m_sInputFirstNameRect.Top + 2 && p.Y < m_sInputFirstNameRect.Bottom - 2)
				return Element::InputFirstName;
			// Check whether point is inside last name built-in text input
			if (p.X >= m_sInputLastNameRect.Left + 2 && p.X < m_sInputLastNameRect.Right - 2 && p.Y >= m_sInputLastNameRect.Top + 2 && p.Y < m_sInputLastNameRect.Bottom - 2)
				return Element::InputLastName;
			// Check whether point is inside date of birth region
			if (p.X >= m_sDateRect.Left && p.X < m_sDateRect.Right && p.Y >= m_sDateRect.Top && p.Y < m_sDateRect.Bottom)
			{
				// Check whether point is inside calendar show arrow region
				if (p.X >= m_sDateRect.Right - m_sDateRect.height())
					return Element::DateArrow;
				return Element::Date;
			}
			return Element::None;
		}

		IBuiltInTextInput *CRegistration::getInputFirstName()
		{
			if (!m_pInputFirstName)
			{
				// If input is not yet created, create it and set its options
				m_pInputFirstName = new CTextInput(this);
				m_pInputFirstName->setSize(PointF{ m_sInputFirstNameRect.width() - 4, m_sInputFirstNameRect.height() - 4 });
				m_pInputFirstName->setPosition(PointF{ m_sInputFirstNameRect.Left + 2, m_sInputFirstNameRect.Top + 2 });
				m_pInputFirstName->setFocused(isFocused() && m_eFocusedElement == Element::InputFirstName);
				m_pInputFirstName->setListener(&m_cTextInputListener);
			}
			return m_pInputFirstName;
		}

		IBuiltInTextInput *CRegistration::getInputLastName()
		{
			if (!m_pInputLastName)
			{
				// If input is not yet created, create it and set its options
				m_pInputLastName = new CTextInput(this);
				m_pInputLastName->setSize(PointF{ m_sInputLastNameRect.width() - 4, m_sInputLastNameRect.height() - 4 });
				m_pInputLastName->setPosition(PointF{ m_sInputLastNameRect.Left + 2, m_sInputLastNameRect.Top + 2 });
				m_pInputLastName->setFocused(isFocused() && m_eFocusedElement == Element::InputLastName);
				m_pInputLastName->setListener(&m_cTextInputListener);
			}
			return m_pInputLastName;
		}

		IBuiltInMonthCalendar *CRegistration::getCalendar()
		{
			if (!m_pCalendar)
			{
				// If calendar is not yet created, create it and set its options
				m_pCalendar = new CMonthCalendar(this);
				m_pCalendar->setListener(&m_cMonthCalendarListener);
			}
			return m_pCalendar;
		}

		void CRegistration::OpenCalendar()
		{
			if (!m_bCalendarOpened)
			{
				m_bCalendarOpened = true; // Set flag indicating whether calendar is shown
				m_eDownElement = Element::None; // Down element can be input only, so reset it to None just in case
				PointF size{ getCalendar()->getRequiredSize() }; // Get calendar size
				PointF disp{ m_sCalendarBorderWidth.Left + m_sCalendarPadding.Left, m_sCalendarBorderWidth.Top + m_sCalendarPadding.Top }; // Calculate where built-in calendar is placed relative to calendar area
				float w{ disp.X + size.X + m_sCalendarBorderWidth.Right + m_sCalendarPadding.Right }; // Calculate total required width for calendar
				float h{ disp.Y + size.Y + m_sCalendarBorderWidth.Bottom + m_sCalendarPadding.Bottom }; // Calculate total required height for calendar
				// Update calendar rectangle with calculated values
				m_sCalendarRect.Left = m_sDateRect.Right - w;
				m_sCalendarRect.Right = m_sCalendarRect.Left + w;
				m_sCalendarRect.Top = m_sDateRect.Bottom;
				m_sCalendarRect.Bottom = m_sCalendarRect.Top + h;
				getCalendar()->setSize(size); // Set built-in calendar size
				getCalendar()->setPosition(disp); // Set built-in calendar position
				getForm()->CaptureMouse(this, true); // Request to capture mouse input
				if (m_pCanvasCalendar)
					m_pCanvasCalendar->setValid(false); // Invalidate calendar canvas
				Repaint(false); // Repaint widget
			}
		}

		void CRegistration::CloseCalendar()
		{
			if (m_bCalendarOpened)
			{
				CLockRepaint lock{ this }; // Lock form's repaint to prevent multiple drawing until we finish with changes
				Repaint(false); // Repaint widget area before hiding calendar
				m_bCalendarOpened = false; // Set flag indicating whether calendar is shown
				getCalendar()->NotifyOnFreeResources(); // Free resources used by built-in calendar
				if (m_pCanvasCalendar)
				{
					// Free calendar canvas
					m_pCanvasCalendar->Release();
					m_pCanvasCalendar = nullptr;
				}
				if (isCaptureMouse())
					getForm()->ReleaseCaptureMouse(); // Release mouse capture
			}
		}

		bool CRegistration::UpdateHoveredElement(const PointF &p)
		{
			Element element{ getElement(p) }; // Find which element is under the specified point
			if (element != m_eHoveredElement) // If current hovered element is different
			{
				switch (m_eHoveredElement) // Notify element which is loosing hovered state about it
				{
				case Element::InputFirstName:
					getInputFirstName()->NotifyOnMouseLeave();
					break;
				case Element::InputLastName:
					getInputLastName()->NotifyOnMouseLeave();
					break;
				case Element::Calendar:
					getCalendar()->NotifyOnMouseLeave();
					break;
				}
				m_eHoveredElement = element; // Update hovered element property
				switch (m_eHoveredElement) // Notify new hovered element that he have got hovered state
				{
				case Element::InputFirstName:
					getInputFirstName()->NotifyOnMouseHover(p - getInputFirstName()->getPosition());
					break;
				case Element::InputLastName:
					getInputLastName()->NotifyOnMouseHover(p - getInputLastName()->getPosition());
					break;
				case Element::Calendar:
					getCalendar()->NotifyOnMouseHover(p - m_sCalendarRect.LeftTop);
					break;
				}
				return true;
			}
			return false;
		}

		void CRegistration::UpdateFromStyle(IStyle *style)
		{
			// Update widget properties
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".InputBorderColor[Normal]", m_aInputBorderColor[0]);
			style->getOption(m_sClassName + L".InputBorderColor[Focused]", m_aInputBorderColor[1]);
			// Update built-in controls properties
			getInputFirstName()->UpdateFromStyle(style, m_sClassName + L".TextInput");
			getInputLastName()->UpdateFromStyle(style, m_sClassName + L".TextInput");
			getCalendar()->UpdateFromStyle(style, m_sClassName + L".MonthCalendar");
		}
	#pragma endregion

	#pragma region Render
		void CRegistration::RenderControl(IRenderer *renderer)
		{
			if (PrepareCanvas(renderer, &m_pCanvas, getSize())) // If we can draw on canvas
			{
				IFont *font{ getFont() }; // Store font instance
				IPlatformFont *pf{ font->getPlatformFont(renderer) }; // Store platform font instance
				String text_date{ nitisa::ToString(getCalendar()->getMonth()) + L"/" + nitisa::ToString(getCalendar()->getDay()) + L"/" + nitisa::ToString(getCalendar()->getYear()) }; // Make string with date in m/d/Y format
				PointF text_first_name_size{ pf->getStringSize(L"First name:", font->Distance) }; // Calculate size of "First name:" string
				PointF text_last_name_size{ pf->getStringSize(L"Last name:", font->Distance) }; // Calculate size of "Last name:" string
				PointF text_date_of_birth_size{ pf->getStringSize(L"Date of birth:", font->Distance) }; // Calculate size of "Date of birth:" string
				PointF text_date_size{ pf->getStringSize(text_date, font->Distance) }; // Calculate size of string with date
				BlockColors normal{ m_aInputBorderColor[0], m_aInputBorderColor[0], m_aInputBorderColor[0], m_aInputBorderColor[0], Color{ 255, 255, 255, 255 }, Color{ 0, 0, 0, 0 } }; // Normal state block colors
				BlockColors focused{ m_aInputBorderColor[1], m_aInputBorderColor[1], m_aInputBorderColor[1], m_aInputBorderColor[1], Color{ 255, 255, 255, 255 }, Color{ 0, 0, 0, 0 } }; // Focused state block colors
				CStoreTarget s_target{ renderer }; // Store active target
				CStorePrimitiveMatrix s_matrix{ renderer }; // Store active primitive matrix
				renderer
					->ActivateTarget(m_pCanvas) // Activate widget canvas to draw on it
					->Clear(Color{ 0, 0, 0, 0 }) // Clear canvas
					->DrawRectangle(getRect(), m_sBackgroundColor) // Draw widget background
					->DrawBlock( // Draw first name input border and background
						m_sInputFirstNameRect,
						RectF{ 1, 1, 1, 1 },
						RectF{ 0, 0, 0, 0 },
						(isFocused() && m_eFocusedElement == Element::InputFirstName) ? focused : normal)
					->DrawBlock( // Draw last name input border and background
						m_sInputLastNameRect,
						RectF{ 1, 1, 1, 1 },
						RectF{ 0, 0, 0, 0 },
						(isFocused() && m_eFocusedElement == Element::InputLastName) ? focused : normal)
					->DrawBlock( // Draw date of birth area border and background
						m_sDateRect,
						RectF{ 1, 1, 1, 1 },
						RectF{ 0, 0, 0, 0 },
						(isFocused() && m_eFocusedElement == Element::Date) ? focused : normal)
					// Draw first name input label
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(148 - text_first_name_size.X, std::roundf(12 - text_first_name_size.Y * 0.5f), 0))
					->DrawText(L"First name:", pf, font->Distance, CColors::Black)
					// Draw last name input label
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(148 - text_last_name_size.X, std::roundf(40 - text_last_name_size.Y * 0.5f), 0))
					->DrawText(L"Last name:", pf, font->Distance, CColors::Black)
					// Draw date of birth are label
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(148 - text_date_of_birth_size.X, std::roundf(68 - text_date_of_birth_size.Y * 0.5f), 0))
					->DrawText(L"Date of birth:", pf, font->Distance, CColors::Black)
					// Draw date of birth date
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(154, std::roundf(68 - text_date_size.Y * 0.5f), 0))
					->DrawText(text_date, pf, font->Distance, CColors::Black)
					// Draw calendar show/hide arrow
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(m_sDateRect.Right - m_sDateRect.height(), m_sDateRect.Top, 0))
					->DrawTriangle(PointF{ 6, 8 }, PointF{ m_sDateRect.height() - 6, 8 }, PointF{ m_sDateRect.height() * 0.5f, m_sDateRect.height() - 9 }, CColors::Black)
					// Set primitive matrix to identity before drawing built-in inputs
					->ActivatePrimitiveMatrix(nullptr);

				// Draw built-in inputs
				getInputFirstName()->Render(false, ntl::Mat4Translate<float>(m_sInputFirstNameRect.Left + 2, m_sInputFirstNameRect.Top + 2, 0), nullptr);
				getInputLastName()->Render(false, ntl::Mat4Translate<float>(m_sInputLastNameRect.Left + 2, m_sInputLastNameRect.Top + 2, 0), nullptr);

				// Make canvas valid
				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, PointF{ 0, 0 }); // Draw canvas on a form
		}

		void CRegistration::RenderCalendar(IRenderer *renderer)
		{
			if (!m_pCanvasCalendar || !m_pCanvasCalendar->isValid() || getCalendar()->isAnimating())
			{
				if (PrepareCanvas(renderer, &m_pCanvasCalendar, m_sCalendarRect))
				{
					CStoreTarget s_target{ renderer }; // Store active target
					// Draw calendar background
					renderer
						->ActivateTarget(m_pCanvasCalendar)
						->Clear(Color{ 0, 0, 0, 0 })
						->DrawBlock(
							RectF{ 0, 0, m_sCalendarRect.width(), m_sCalendarRect.height() },
							RectF{ 1, 1, 1, 1 },
							RectF{ 0, 0, 0, 0 },
							BlockColors{ m_sCalendarBorderColor, m_sCalendarBorderColor, m_sCalendarBorderColor, m_sCalendarBorderColor, m_sCalendarBackgroundColor, Color{ 0, 0, 0, 0 } });
					// Draw calendar built-in control
					getCalendar()->Render(false, ntl::Mat4Translate<float>(getCalendar()->getLeft(), getCalendar()->getTop(), 0), nullptr);
					m_pCanvasCalendar->setValid(true); // Make canvas valid
				}
			}
			DrawCanvas(renderer, getTransformMatrix() * ntl::Mat4Translate<float>(m_sCalendarRect.Left, m_sCalendarRect.Top, 0), m_pCanvasCalendar, PointF{ 0, 0 }); // Draw calendar canvas on a form
		}
	#pragma endregion
	}
}
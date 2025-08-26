#pragma once

#include "Nitisa/BuiltInControls/MonthCalendar/BuiltInMonthCalendar.h" // Built-in month calendar control is declared here
#include "Nitisa/BuiltInControls/TextInput/BuiltInTextInput.h" // Built-in text input control is declared here
#include "Nitisa/BuiltInControls/IBuiltInMonthCalendarListener.h" // Built-in month calendar control listener is declared here
#include "Nitisa/BuiltInControls/IBuiltInTextInputListener.h" // Built-in text input control listener is declared here
#include "Nitisa/Core/Align.h" // Align enumeration is declared here
#include "Nitisa/Core/Control.h" // CControl class is declared here
#include "Nitisa/Image/Color.h" // Color is declared here
#include "Nitisa/Math/PointF.h" // PointF is declared here
#include "Nitisa/Math/RectF.h" // RectF is declared here

#include "../IRegistration.h" // Include declaration of widget interface

namespace nitisa
{
	// Forward declaration of interfaces we use
	class IBuiltInTextInput;
	class IBuiltInMonthCalendar;
	class IControl;
	class IForm;
	class IRenderer;
	class IStyle;
	class ITexture;

	namespace coolwidgets
	{
		class CRegistrationService; // Forward declaration of widget service

		class CRegistration :public virtual IRegistration, public CControl // Widget class implement widget interface and is derived form default control implementation in CControl
		{
			friend CRegistrationService; // Widget service need to be a friend to have access to widget private properties and methods
		public:
			enum class State // Enumeration describing input states
			{
				Normal, // Normal state, not focused
				Active // Input is focused
			};
		private:
			enum class Element // Enumeration describing widget parts
			{
				None, // Nothing or irrelevant part
				InputFirstName, // Input where user can type his first name
				InputLastName, // Input where user can type his last name
				Date, // Area where current date of birth is displayed
				DateArrow, // Arrow which can be used to show calendar
				Calendar // Calendar
			};

			class CTextInput :public CBuiltInTextInput // Built-in text input derived from its base class
			{
			private:
				CRegistration *m_pControl;
			public:
				IControl *getControl() override; // Implement abstract method which should return parent widget

				CTextInput(CRegistration *control);
			};

			class CTextInputListener :public virtual IBuiltInTextInputListener // Built-in text input listener implementation class derived from corresponding interface
			{
			private:
				CRegistration *m_pControl;
			public:
				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override; // Notification called when repainting is required
				void NotifyOnTextChanged(IBuiltInControl *sender) override; // Notification called when text is changed in the input

				CTextInputListener(CRegistration *control);
			};

			class CMonthCalendar :public CBuiltInMonthCalendar // Built-in month calendar derived from its base class
			{
			private:
				CRegistration *m_pControl;
			public:
				IControl *getControl() override; // Implement abstract method which should return parent widget

				CMonthCalendar(CRegistration *control);
			};

			class CMonthCalendarListener :public virtual IBuiltInMonthCalendarListener // Built-in month calendar listener implementation class derived from corresponding interface
			{
			private:
				CRegistration *m_pControl;
			public:
				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override; // Notification called when repainting is required
				void NotifyOnChange(IBuiltInControl *sender) override; // Notification called when selected date is changed in month calendar

				CMonthCalendarListener(CRegistration *control);
			};
		private:
			Color m_sBackgroundColor; // We store BackgroundColor property value here
			Color m_aInputBorderColor[(int)State::Active + 1]; // We store InputBorderColor property here. It has two values for each of states

			IBuiltInTextInput *m_pInputFirstName; // We store built-in text input instance for first name here
			IBuiltInTextInput *m_pInputLastName; // We store built-in text input instance for last name here
			IBuiltInMonthCalendar *m_pCalendar; // We store built-in calendar instance here
			Element m_eFocusedElement; // We store currently focused element here. It can be first name input, last name input or date of birth area
			Element m_eHoveredElement; // We store element which is under mouse pointer here
			Element m_eDownElement; // We store element at which mouse pointer was down but not yet released. Can be either first name input or last name input
			ITexture *m_pCanvas; // Texture in which our widget will be drawn
			ITexture *m_pCanvasCalendar; // Texture in which calendar part will be drawn
			CTextInputListener m_cTextInputListener; // Listener for text inputs
			CMonthCalendarListener m_cMonthCalendarListener; // Listener for calendar
			bool m_bCalendarOpened; // It indicates whether calendar is shown or not
			RectF m_sInputFirstNameRect; // Rectangle of the area with first name input
			RectF m_sInputLastNameRect; // Rectangle of the area with last name input
			RectF m_sDateRect; // Rectangle of the area with date of birth
			RectF m_sCalendarBorderWidth; // Border widths of calendar
			RectF m_sCalendarPadding; // Padding between borders and calendar
			Color m_sCalendarBorderColor; // Color of calendar border
			Color m_sCalendarBackgroundColor; // Color of calendar background
			RectF m_sCalendarRect; // Calendar rectangle when it is shown

			Element getElement(const PointF &p); // Find which element is under the specified point (in widget coordinate system)
			IBuiltInTextInput *getInputFirstName(); // Return first name input. Create it if it was not created yet
			IBuiltInTextInput *getInputLastName(); // Return last name input. Create it if it was not created yet
			IBuiltInMonthCalendar *getCalendar(); // Return calendar. Create it if it was not created yet

			void OpenCalendar(); // Show calendar
			void CloseCalendar(); // Hide calendar

			void UpdateFromStyle(IStyle *style); // Update properties from style
			bool UpdateHoveredElement(const PointF &p); // Update m_eHoveredElement property when mouse pointer is in specified point (in widget coordinate system). Return true if hovered element was changed
			void RenderControl(IRenderer *renderer); // Render widget
			void RenderCalendar(IRenderer *renderer); // Render calendar
		public:
			void(*OnChange)(IControl *sender); // Event called when data is changed

			// IControl getters
			IControl *getControl(const PointF &position) override;
			CursorType getCursor() override;

			// IControl setters
			bool setAlign(const Align value) override;
			bool setConstraints(const RectF &value) override;
			bool setSize(const PointF &value) override;
			bool setEnabled(const bool value) override;

			// IRegistration getters
			RegistrationData getRegistrationData() override;

			// IRegistration setters
			bool setRegistrationData(const RegistrationData &value) override;

			// Constructors & destructor
			CRegistration();
			CRegistration(IControl *parent);
			CRegistration(IForm *parent);
			~CRegistration() override;

			// Layout property getters
			Color getBackgroundColor();
			Color getInputBorderColor(const State state);

			// Layout property setters
			bool setBackgroundColor(const Color &value);
			bool setInputBorderColor(const State state, const Color &value);
		};
	}
}
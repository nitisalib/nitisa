#pragma once

#include "Nitisa/Core/Strings.h" // We use String type declared here
#include "Nitisa/Interfaces/IControl.h" // IControl interface declaration is here

namespace nitisa // Everything should be in this global namespace
{
	namespace coolwidgets // Namespace of our package
	{
		class IRegistration :public virtual IControl // Widget interface should be derived from control interface
		{
		public:
			struct RegistrationData // Structure describing widget data
			{
				String FirstName;
				String LastName;
				// Date of birth
				int Year;
				int Month;
				int Day;
			};
		public:
			virtual RegistrationData getRegistrationData() = 0; // Getter method of RegistrationData property

			virtual bool setRegistrationData(const RegistrationData &value) = 0; // Setter method of RegistrationData property
		};
	}
}
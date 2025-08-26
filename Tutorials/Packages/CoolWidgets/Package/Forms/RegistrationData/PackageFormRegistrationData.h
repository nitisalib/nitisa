#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/Core/PackageForm.h"

namespace nitisa
{
	class IForm;
	class IEventList;
	class IPackage;
	class IPropertyList;
	class IRenderer;
	class IWindow;

	class Image;

	namespace coolwidgets
	{
		class CPackageFormRegistrationData :public CPackageForm
		{
		private:
			IForm *m_pForm;
		public:
			String getCategory() override;
			String getClassName() override;
			String getTitle() override;
			String getDescription() override;
			String getReferenceUrl() override;
			const Image *getIcon() override;
			IForm *getInstance() override;

			IForm *Create(IWindow *window, IRenderer *renderer) override;
			IPropertyList *CreatePropertyList(IForm *form) override;
			IEventList *CreateEventList(IForm *form) override;

			CPackageFormRegistrationData(IPackage *package);
		};
	}
}
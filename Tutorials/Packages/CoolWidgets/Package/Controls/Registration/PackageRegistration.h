#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/Image.h"
#include "Nitisa/Package/Core/PackageControl.h"

namespace nitisa
{
	class IControl;
	class IEventList;
	class IPackage;
	class IPropertyList;

	namespace coolwidgets
	{
		class CPackageRegistration :public CPackageControl
		{
		private:
			const Image m_cIcon;
		public:
			String getCategory() override;
			String getClassName() override;
			String getTitle() override;
			String getDescription() override;
			String getReferenceUrl() override;
			const Image *getIcon() override;
			bool isVisible() override;
			bool isDisplayIcon() override;
			bool isInstance(IControl *control) override;
			bool isTransformable() override;

			IControl *Create(IPropertyList **properties, IEventList **events) override;
			IPropertyList *CreatePropertyList(IControl *control) override;
			IEventList *CreateEventList(IControl *control) override;

			CPackageRegistration(IPackage *package);
		};
	}
}
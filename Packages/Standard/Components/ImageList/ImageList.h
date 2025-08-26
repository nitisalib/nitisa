// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Component.h"
#include "../IImageList.h"

namespace nitisa
{
	class IForm;
	class ITexture;

	class Image;

	namespace standard
	{
		class CImageListService;

		// After adding ImageData to this component it should not be changed or destroyed!
		class CImageList :public virtual IImageList, public CComponent
		{
			friend CImageListService;
		private:
			struct IMAGE
			{
				Image *Data;
				ITexture *Texture;
			};

			std::vector<IMAGE> m_aItems;
			bool m_bIgnoreChanges;
		protected:
			void BeforeRelease() override;
		public:
			CImageList();
			CImageList(IForm *parent);

			int getImageCount() override;
			Image *getImage(const int index) override;
			ITexture *getTexture(const int index) override;

			int AddImage(Image *data) override;
			bool DeleteImage(const int index) override;
			bool DeleteImages() override;
			void Update() override;
		};
	}
}
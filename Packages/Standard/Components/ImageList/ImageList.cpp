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
	#pragma region Constructor & destructor
		CImageList::CImageList() :
			CComponent(L"ImageList"),
			m_bIgnoreChanges{ false }
		{
			setService(new CImageListService(this), true);
		}

		CImageList::CImageList(IForm *parent) : CImageList()
		{
			setForm(parent);
		}

		void CImageList::BeforeRelease()
		{
			m_bIgnoreChanges = true;
			DeleteImages();
			CComponent::BeforeRelease();
		}
	#pragma endregion

	#pragma region Getters
		int CImageList::getImageCount()
		{
			return (int)m_aItems.size();
		}

		Image *CImageList::getImage(const int index)
		{
			if (index >= 0 && index < (int)m_aItems.size())
				return m_aItems[index].Data;
			return nullptr;
		}

		ITexture *CImageList::getTexture(const int index)
		{
			if (index >= 0 && index < (int)m_aItems.size() && getForm() && getForm()->getRenderer())
			{
				if (!m_aItems[index].Texture)
					m_aItems[index].Texture = getForm()->getRenderer()->CreateTextureFromImage(*m_aItems[index].Data, 1, TextureFormat::RGBA, true);
				return m_aItems[index].Texture;
			}
			return nullptr;
		}
	#pragma endregion

	#pragma region Images
		int CImageList::AddImage(Image *data)
		{
			int result{ -1 };
			if (data && data->Width > 0 && data->Height > 0)
			{
				m_aItems.push_back({ data, nullptr });
				if (!m_bIgnoreChanges)
					QueryService()->SendChangeNotification();
				return (int)m_aItems.size() - 1;
			}
			return result;
		}

		bool CImageList::DeleteImage(const int index)
		{
			if (index >= 0 && index < (int)m_aItems.size())
			{
				if (m_aItems[index].Texture)
					m_aItems[index].Texture->Release();
				delete m_aItems[index].Data;
				m_aItems.erase(m_aItems.begin() + index);
				if (!m_bIgnoreChanges)
					QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CImageList::DeleteImages()
		{
			if (m_aItems.size() == 0)
				return false;
			for (auto &pos : m_aItems)
			{
				if (pos.Texture)
					pos.Texture->Release();
				delete pos.Data;
			}
			m_aItems.clear();
			if (!m_bIgnoreChanges)
				QueryService()->SendChangeNotification();
			return true;
		}

		void CImageList::Update()
		{
			if (!m_bIgnoreChanges)
				QueryService()->SendChangeNotification();
		}
	#pragma endregion
	}
}
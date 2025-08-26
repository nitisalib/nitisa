// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace opengl
	{
	#pragma region Constructor & destructor
		CPlane::CPlane() :
			C3DControl(L"Plane"),
			m_cPrimitive{ this }
		{

		}

		CPlane::CPlane(IControl *parent) :CPlane()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IPlane getters
		float CPlane::getPlaneWidth()
		{
			return m_cPrimitive.Width;
		}

		float CPlane::getPlaneDepth()
		{
			return m_cPrimitive.Depth;
		}

		int CPlane::getWidthSegments()
		{
			return m_cPrimitive.WidthSegments;
		}

		int CPlane::getDepthSegments()
		{
			return m_cPrimitive.DepthSegments;
		}
	#pragma endregion

	#pragma region IPlane setters
		bool CPlane::setPlaneWidth(const float value)
		{
			if (m_cPrimitive.setWidth(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CPlane::setPlaneDepth(const float value)
		{
			if (m_cPrimitive.setDepth(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CPlane::setPlaneSize(const float width, const float depth)
		{
			if (m_cPrimitive.setSize(width, depth))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CPlane::setWidthSegments(const int value)
		{
			if (m_cPrimitive.setWidthSegments(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CPlane::setDepthSegments(const int value)
		{
			if (setDepthSegments(value))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool CPlane::setSegments(const int width, const int depth)
		{
			if (m_cPrimitive.setSegments(width, depth))
			{
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CPlane::FreeResources(COpenGL *graphics)
		{
			m_cPrimitive.FreeResources();
		}
	#pragma endregion

	#pragma region Render
		void CPlane::Render(COpenGL *graphics, IRenderer *renderer, ICamera *camera)
		{
			m_cPrimitive.Render();
		}
	#pragma endregion
	}
}
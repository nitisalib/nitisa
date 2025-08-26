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
	namespace opengl
	{
	#pragma region Constructor & destructor
		C3DControl::C3DControl(const String &class_name) :
			CControl(class_name, false, true, false, false, false, false),
			m_pModel{ new CModel(false, false) },
			m_pMaterial{ nullptr },
			m_eRenderMode{ RenderMode::Fill }
		{
			setService(new C3DControlService(this), true);
			CControl::setVisible(false);
		}

		C3DControl::~C3DControl()
		{
			m_pModel->Release();
		}
	#pragma endregion

	#pragma region IControl getters
		bool C3DControl::isAcceptControl()
		{
			return CControl::isAcceptControl();
		}

		bool C3DControl::isAcceptControl(IControl *control)
		{
			return CControl::isAcceptControl() && cast<IView*>(control) != nullptr;
		}
	#pragma endregion

	#pragma region IControl setters
		bool C3DControl::setVisible(const bool value)
		{
			return false;
		}
	#pragma endregion

	#pragma region I3DControl getters
		IModel *C3DControl::getModel()
		{
			return m_pModel;
		}

		IMaterialControl *C3DControl::getMaterial()
		{
			return m_pMaterial;
		}

		I3DControl::RenderMode C3DControl::getRenderMode()
		{
			return m_eRenderMode;
		}

		RotateOrder C3DControl::getRotateOrder()
		{
			return m_pModel->RotateOrder;
		}

		TransformOrder C3DControl::getTransformOrder()
		{
			return m_pModel->TransformOrder;
		}

		float C3DControl::getX()
		{
			return m_pModel->Tx;
		}

		float C3DControl::getY()
		{
			return m_pModel->Ty;
		}

		float C3DControl::getZ()
		{
			return m_pModel->Tz;
		}

		float C3DControl::getSx()
		{
			return m_pModel->Sx;
		}

		float C3DControl::getSy()
		{
			return m_pModel->Sy;
		}

		float C3DControl::getSz()
		{
			return m_pModel->Sz;
		}

		float C3DControl::getPitch()
		{
			return ntl::RadToDeg<float>(m_pModel->Rx);
		}

		float C3DControl::getYaw()
		{
			return ntl::RadToDeg<float>(m_pModel->Ry);
		}

		float C3DControl::getRoll()
		{
			return ntl::RadToDeg<float>(m_pModel->Rz);
		}
	#pragma endregion

	#pragma region I3DControl setters
		bool C3DControl::setMaterial(IMaterialControl *value)
		{
			if (value != m_pMaterial)
			{
				m_pMaterial = value;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool C3DControl::setRenderMode(const RenderMode value)
		{
			if (value != m_eRenderMode)
			{
				m_eRenderMode = value;
				QueryService()->SendChangeNotification();
				return true;
			}
			return false;
		}

		bool C3DControl::setRotateOrder(const RotateOrder value)
		{
			return m_pModel->setRotateOrder(value);
		}

		bool C3DControl::setTransformOrder(const TransformOrder value)
		{
			return m_pModel->setTransformOrder(value);
		}

		bool C3DControl::setX(const float value)
		{
			return m_pModel->setTx(value);
		}

		bool C3DControl::setY(const float value)
		{
			return m_pModel->setTy(value);
		}

		bool C3DControl::setZ(const float value)
		{
			return m_pModel->setTz(value);
		}

		bool C3DControl::setSx(const float value)
		{
			return m_pModel->setSx(value);
		}

		bool C3DControl::setSy(const float value)
		{
			return m_pModel->setSy(value);
		}

		bool C3DControl::setSz(const float value)
		{
			return m_pModel->setSz(value);
		}

		bool C3DControl::setPitch(const float value)
		{
			return m_pModel->setRx(ntl::DegToRad<float>(value));
		}

		bool C3DControl::setYaw(const float value)
		{
			return m_pModel->setRy(ntl::DegToRad<float>(value));
		}

		bool C3DControl::setRoll(const float value)
		{
			return m_pModel->setRz(ntl::DegToRad<float>(value));
		}
	#pragma endregion
	}
}
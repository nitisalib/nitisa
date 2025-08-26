// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/FormService.h"
#include "Nitisa/Core/Messages.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Math/Transform.h"
#include "../IFormTransform.h"
#include "IFormTransformProto.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IRenderer;
	class IWindow;

	namespace standard
	{
		class CFormTransform :public virtual IFormTransform, public IFormTransformProto
		{
		private:
			class CFormTransformService :public CFormService
			{
			private:
				CFormTransform * m_pForm;
			public:
				// Application notifications
				void NotifyOnTranslateChange() override;

				CFormTransformService(CFormTransform *form);
			};
		private:
			Transform m_sValue;
			bool m_bTx;
			bool m_bTy;
			bool m_bTz;
			bool m_bRx;
			bool m_bRy;
			bool m_bRz;
			bool m_bSx;
			bool m_bSy;
			bool m_bSz;
			bool m_bRotateOrder;
			bool m_bTransformOrder;
			bool m_bMinTx;
			bool m_bMinTy;
			bool m_bMinTz;
			bool m_bMinRx;
			bool m_bMinRy;
			bool m_bMinRz;
			bool m_bMinSx;
			bool m_bMinSy;
			bool m_bMinSz;
			bool m_bMaxTx;
			bool m_bMaxTy;
			bool m_bMaxTz;
			bool m_bMaxRx;
			bool m_bMaxRy;
			bool m_bMaxRz;
			bool m_bMaxSx;
			bool m_bMaxSy;
			bool m_bMaxSz;
			float m_fMinTx;
			float m_fMinTy;
			float m_fMinTz;
			float m_fMinRx;
			float m_fMinRy;
			float m_fMinRz;
			float m_fMinSx;
			float m_fMinSy;
			float m_fMinSz;
			float m_fMaxTx;
			float m_fMaxTy;
			float m_fMaxTz;
			float m_fMaxRx;
			float m_fMaxRy;
			float m_fMaxRz;
			float m_fMaxSx;
			float m_fMaxSy;
			float m_fMaxSz;

			void InitControls();
			void LoadTranslatableTexts();
		protected:
			void FormTransformProto_OnKeyUp(IForm *sender, const MessageKey &m) override;
			void EditTx_OnKillFocus(IControl *sender) override;
			void EditTy_OnKillFocus(IControl *sender) override;
			void EditTz_OnKillFocus(IControl *sender) override;
			void EditSx_OnKillFocus(IControl *sender) override;
			void EditSy_OnKillFocus(IControl *sender) override;
			void EditSz_OnKillFocus(IControl *sender) override;
			void EditRx_OnKillFocus(IControl *sender) override;
			void EditRy_OnKillFocus(IControl *sender) override;
			void EditRz_OnKillFocus(IControl *sender) override;
			void DropDownRO_OnSelect(IControl *sender, const int index) override;
			void DropDownTO_OnSelect(IControl *sender, const int index) override;
			void ButtonOk_OnClick(IControl *sender) override;
			void ButtonCancel_OnClick(IControl *sender) override;
		public:
			static const String ClassName; // Class name

			Transform getValue() override;
			bool isAllowedTx() const override;
			bool isAllowedTy() const override;
			bool isAllowedTz() const override;
			bool isAllowedSx() const override;
			bool isAllowedSy() const override;
			bool isAllowedSz() const override;
			bool isAllowedRx() const override;
			bool isAllowedRy() const override;
			bool isAllowedRz() const override;
			bool isAllowedRotateOrder() const override;
			bool isAllowedTransformOrder() const override;
			bool hasMinTx() const override;
			bool hasMinTy() const override;
			bool hasMinTz() const override;
			bool hasMinSx() const override;
			bool hasMinSy() const override;
			bool hasMinSz() const override;
			bool hasMinRx() const override;
			bool hasMinRy() const override;
			bool hasMinRz() const override;
			bool hasMaxTx() const override;
			bool hasMaxTy() const override;
			bool hasMaxTz() const override;
			bool hasMaxSx() const override;
			bool hasMaxSy() const override;
			bool hasMaxSz() const override;
			bool hasMaxRx() const override;
			bool hasMaxRy() const override;
			bool hasMaxRz() const override;
			float getMinTx() const override;
			float getMinTy() const override;
			float getMinTz() const override;
			float getMinSx() const override;
			float getMinSy() const override;
			float getMinSz() const override;
			float getMinRx() const override;
			float getMinRy() const override;
			float getMinRz() const override;
			float getMaxTx() const override;
			float getMaxTy() const override;
			float getMaxTz() const override;
			float getMaxSx() const override;
			float getMaxSy() const override;
			float getMaxSz() const override;
			float getMaxRx() const override;
			float getMaxRy() const override;
			float getMaxRz() const override;

			bool setValue(const Transform &value) override;
			bool setAllowedTx(const bool value) override;
			bool setAllowedTy(const bool value) override;
			bool setAllowedTz(const bool value) override;
			bool setAllowedSx(const bool value) override;
			bool setAllowedSy(const bool value) override;
			bool setAllowedSz(const bool value) override;
			bool setAllowedRx(const bool value) override;
			bool setAllowedRy(const bool value) override;
			bool setAllowedRz(const bool value) override;
			bool setAllowedRotateOrder(const bool value) override;
			bool setAllowedTransformOrder(const bool value) override;
			bool setHasMinTx(const bool value) override;
			bool setHasMinTy(const bool value) override;
			bool setHasMinTz(const bool value) override;
			bool setHasMinSx(const bool value) override;
			bool setHasMinSy(const bool value) override;
			bool setHasMinSz(const bool value) override;
			bool setHasMinRx(const bool value) override;
			bool setHasMinRy(const bool value) override;
			bool setHasMinRz(const bool value) override;
			bool setHasMaxTx(const bool value) override;
			bool setHasMaxTy(const bool value) override;
			bool setHasMaxTz(const bool value) override;
			bool setHasMaxSx(const bool value) override;
			bool setHasMaxSy(const bool value) override;
			bool setHasMaxSz(const bool value) override;
			bool setHasMaxRx(const bool value) override;
			bool setHasMaxRy(const bool value) override;
			bool setHasMaxRz(const bool value) override;
			bool setMinTx(const float value) override;
			bool setMinTy(const float value) override;
			bool setMinTz(const float value) override;
			bool setMinSx(const float value) override;
			bool setMinSy(const float value) override;
			bool setMinSz(const float value) override;
			bool setMinRx(const float value) override;
			bool setMinRy(const float value) override;
			bool setMinRz(const float value) override;
			bool setMaxTx(const float value) override;
			bool setMaxTy(const float value) override;
			bool setMaxTz(const float value) override;
			bool setMaxSx(const float value) override;
			bool setMaxSy(const float value) override;
			bool setMaxSz(const float value) override;
			bool setMaxRx(const float value) override;
			bool setMaxRy(const float value) override;
			bool setMaxRz(const float value) override;

			void ActivateFirstEnabledInput() override;

			CFormTransform(IWindow *window, IRenderer *renderer);
		};
	}
}
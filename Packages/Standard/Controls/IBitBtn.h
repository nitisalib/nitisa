// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	namespace standard
	{
		class IBitBtn :public virtual IControl
		{
		protected:
			IBitBtn() = default;
			~IBitBtn() = default;
			IBitBtn(const IBitBtn &other) = delete;
			IBitBtn(IBitBtn &&other) = delete;
			IBitBtn &operator=(const IBitBtn &other) = delete;
			IBitBtn &operator=(IBitBtn &&other) = delete;
		public:
			enum class Kind // BitBtn kind. Corresponding ModalResult will be send to parent modal form
			{
				Abord,
				All,
				Cancel,
				Close,
				Help, // This kind do not close modal form and perform any actions
				Ignore,
				No,
				Ok,
				Retry,
				Yes
			};
		public:
			virtual String getCaption() = 0; // Return caption
			virtual Kind getKind() = 0; // Return kind

			virtual bool setCaption(const String &value) = 0; // Set caption
			virtual bool setKind(const Kind value) = 0; // Set kind

			virtual void Click() = 0; // Emulate click
		};
	}
}
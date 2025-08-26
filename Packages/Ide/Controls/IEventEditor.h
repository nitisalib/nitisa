// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControl.h"

namespace nitisa
{
	class IClass;
	class IEvent;
	class IEventList;

	namespace ide
	{
		class IEventEditor :public virtual IControl
		{
		protected:
			IEventEditor() = default;
			~IEventEditor() = default;
			IEventEditor(const IEventEditor &other) = delete;
			IEventEditor(IEventEditor &&other) = delete;
			IEventEditor &operator=(const IEventEditor &other) = delete;
			IEventEditor &operator=(IEventEditor &&other) = delete;
		public:
			void(*OnEventChange)(IEventEditor *sender, IEvent *event, IEventList *event_list, IClass *parent); // Event called when event has been changed

			virtual int getEventListCount() = 0; // Return count of assigned event lists
			virtual IEventList *getEventList(const int index) = 0; // Return event list by index
			virtual int getEventCount() = 0; // Return count of common events for all attached event lists
			virtual IEvent *getEvent(const int index) = 0; // Return event by index
			virtual int getActiveEventIndex() = 0; // Return index of active event

			virtual bool AttachEventList(IEventList *list) = 0; // Attach event list
			virtual bool DetachEventList(const int index) = 0; // Detach event list by index
			virtual bool DetachEventList(IEventList *list) = 0; // Detach event list
			virtual bool DetachEventLists() = 0; // Detach all event lists
		};
	}
}